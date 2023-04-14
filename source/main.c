#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "main.h"
#include "control.h"
#include "input.h"
#include "gui.h"
#include <citro2d.h>

#define RENDERING_3D false

#define UPGRADES_TOTAL			2
#define MAX_FALLING_COOKIES		10
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

// Simple sprite struct
typedef struct
{
	C2D_Sprite spr;
	float dx, dy; // velocity
	float rot; // rotation
} Sprites_;


char* msgTitle = "";
MSG_BOX_ALIGN msgAlign;
char* msgMessage = "";
MSG_BOX_BUTTON msgButtons = 1;
bool madeTranslation = false;

C2D_Sprite cookie, shop_icon, shop_tab;
static Sprites_ cartSprites[UPGRADES_TOTAL];
static Sprites_ fallingCookies[MAX_FALLING_COOKIES];
static C2D_SpriteSheet spriteSheet;

static void initSprites() {
	// symbols
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);

	C2D_SpriteFromSheet(&cookie, spriteSheet, 0);
	C2D_SpriteSetCenterRaw(&cookie, 55, 55);
	C2D_SpriteSetPos(&cookie, 320/2, 120);

	C2D_SpriteFromSheet(&shop_icon, spriteSheet, 1);
	C2D_SpriteSetPos(&shop_icon, 320/2 - 60, 190);
	//C2D_SpriteScale(&cookie, 1.2, 1.2);

	C2D_SpriteFromSheet(&shop_tab, spriteSheet, 2);
	C2D_SpriteSetPos(&shop_tab, 0, 0);

	//initialize carts 
	for(int i=0; i<UPGRADES_TOTAL; i++){
		Sprites_* carts = &cartSprites[i];

		C2D_SpriteFromSheet(&carts->spr, spriteSheet, 3);
		C2D_SpriteSetPos(&carts->spr, 250, 80 + i*30);
		C2D_SpriteScale(&carts->spr, .75, .75);
		C2D_SpriteSetDepth(&carts->spr, .6);
	}

	//initialize falling cookies 
	for(int i=0; i<MAX_FALLING_COOKIES; i++){
		Sprites_* f_cookies = &fallingCookies[i];

		C2D_SpriteFromSheet(&f_cookies->spr, spriteSheet, 0);
		C2D_SpriteSetPos(&f_cookies->spr, rand() % SCREEN_WIDTH, rand() % -60);
		C2D_SpriteScale(&f_cookies->spr, .3, .3);
		C2D_SpriteSetDepth(&f_cookies->spr, .2);
		C2D_SpriteSetCenter(&f_cookies->spr, 0.5f, 0.5f);
		f_cookies->rot = RandomNumber(-2.f, 2.f);
	}
}

//---------------------------------------------------------------------------------
static void moveSprites() {
//---------------------------------------------------------------------------------
	for (size_t i = 0; i < MAX_FALLING_COOKIES; i++)
	{
		Sprites_* f_cookies = &fallingCookies[i];
		C2D_SpriteMove(&f_cookies->spr, 0, f_cookies->dy);
		C2D_SpriteRotateDegrees(&f_cookies->spr, f_cookies->rot);

		// Check for collision with the screen edge
		if (f_cookies->spr.params.pos.y > (SCREEN_HEIGHT-(f_cookies->spr.params.pos.h / 2.0f)) + 40){
			C2D_SpriteSetPos(&f_cookies->spr, rand() % SCREEN_WIDTH, (rand() % 50)-50);
		} else {
			f_cookies->dy = 3;
		}
		
	}
}

int main()
{
///////////////////////////////////////////
//                  C2D                  //
///////////////////////////////////////////	
	// Initialize the libs	
	romfsInit();
	gfxInitDefault();
	gfxSet3D(true); // Enable stereoscopic 3D

	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();



	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	C3D_RenderTarget* top;
	C3D_RenderTarget* targetLeft;
	C3D_RenderTarget* targetRight;
	if(!RENDERING_3D){	
		top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	}else{

		// Initialize the render targets
		targetLeft  = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
		targetRight = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
		C3D_RenderTargetSetOutput(targetLeft,  GFX_TOP, GFX_LEFT,  DISPLAY_TRANSFER_FLAGS);
		C3D_RenderTargetSetOutput(targetRight, GFX_TOP, GFX_RIGHT, DISPLAY_TRANSFER_FLAGS);
	}


	initBuffer();
	initSprites();
	initMainScreen();


	// Main loop
	while (aptMainLoop())
	{
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;


		float iod = osGet3DSliderState();
		
		getInput();

		app();

		moveSprites();

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(bottom, C2D_Color32(0x81, 0x81, 0xD9, 0xFF));
			if(!RENDERING_3D){	
				C2D_TargetClear(top, C2D_Color32(0x81, 0x81, 0xD9, 0xFF));

				
				C2D_SceneBegin(top);
					for (size_t i = 0; i < MAX_FALLING_COOKIES; i ++)
							C2D_DrawSprite(&fallingCookies[i].spr);

					renderMainScreen_Top(-iod);
					if(msgbox)
					{
						MessageBox(msgTitle, msgAlign, msgMessage, msgButtons, 1);
					}
			}else{
				//left eye
				C3D_RenderTargetClear(targetLeft, C3D_CLEAR_ALL,  0x8181D9FF, 0);
				C3D_FrameDrawOn(targetLeft);
					for (size_t i = 0; i < MAX_FALLING_COOKIES; i ++)
							C2D_DrawSprite(&fallingCookies[i].spr);

					renderMainScreen_Top(iod);
					if(msgbox)
					{
						MessageBox(msgTitle, msgAlign, msgMessage, msgButtons, 1);
					}

				//right eye
				if (iod > 0.0f)
				{
					C3D_RenderTargetClear(targetRight, C3D_CLEAR_ALL,  0x8181D9FF, 0);
					C3D_FrameDrawOn(targetRight);
					for (size_t i = 0; i < MAX_FALLING_COOKIES; i ++)
							C2D_DrawSprite(&fallingCookies[i].spr);

					renderMainScreen_Top(-iod);
					if(msgbox)
					{
						MessageBox(msgTitle, msgAlign, msgMessage, msgButtons, 1);
					}
				}
			}
			

				//log cookie behavior
				// char buf[160];
				// C2D_Text dynText;
				// float fontSize = .5;

				// snprintf(buf, sizeof(buf), "cookie: %x", &fallingCookies[0].spr.params.pos.y);
				// C2D_TextParse(&dynText, g_dynamicBuf, buf);
				// C2D_TextOptimize(&dynText);
				// C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 10.0f, 165.0f, 0.5f, fontSize, fontSize, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));	

				
				
				
			C2D_SceneBegin(bottom);
				if (mode == 1)
				{	
					//small "pumping"-animation when pressing cookie
					if(cookie_press)
					{
						C2D_SpriteSetScale(&cookie, .75, .75);
						cookie_press = false;
					} else {
						C2D_SpriteSetScale(&cookie, 1, 1);
					}
					C2D_DrawSprite(&cookie);
					C2D_DrawSprite(&shop_icon);
					renderMainScreen_Bottom();
				}
				else if(mode == 2)
				{	
					// if(madeTranslation == false)
					// {
					// 	for(int i=0; i<70; i++)
					// 	{
					// 		C2D_DrawSprite(&shop_icon);
					// 		C2D_SpriteMove(&shop_icon, 0, -.5);
					// 	}
					// 	madeTranslation = true;
					// }
					// C2D_DrawSprite(&shop_icon);
					// C2D_DrawSprite(&cookie);
					C2D_DrawSprite(&shop_tab);

					renderShopScreen_Bottom();

					for(int i=0; i<UPGRADES_TOTAL; i++){
						Sprites_* carts = &cartSprites[i];
						C2D_DrawSprite(&carts->spr);
					}
				}
				else if (mode == 3)//Settings
				{
					// renderBottomSettingsScreen();
					
				}

				
		C3D_FrameEnd(0);
///////////		






		//Exit code
		if (mode==0) break;

		
		// Flush and swap framebuffers
		gfxFlushBuffers();

		//Wait for VBlank
		gspWaitForVBlank();	


	}	
	//delete sprites
	C2D_SpriteSheetFree(spriteSheet);
	// Deinitialize the scene
	exitScene();
	// Deinitialize the libs
	C2D_Fini();
	C3D_Fini();	
	gfxExit();

	return 0;
}

void prepMsgBox(Message_Box Msg){
	msgTitle = Msg.msgTitle;
	msgAlign = Msg.msgAlign;
	msgMessage = Msg.msgMessage;
	msgButtons = Msg.msgButtons;
	msgbox = Msg.show;
}





