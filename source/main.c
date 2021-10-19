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

char* msgTitle = "";
char* msgMessage = "";
int msgButtons = 1;
bool madeTranslation = false;

C2D_Sprite cookie, shop;
static C2D_SpriteSheet spriteSheet;

static void initSprites() {
	// symbols
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);

	C2D_SpriteFromSheet(&cookie, spriteSheet, 0);
	C2D_SpriteSetPos(&cookie, 320/2 - 55, 70);

	C2D_SpriteFromSheet(&shop, spriteSheet, 1);
	C2D_SpriteSetPos(&shop, 320/2 - 60, 190);
	//C2D_SpriteScale(&cookie, 1.2, 1.2);
}

int main()
{
///////////////////////////////////////////
//                  C2D                  //
///////////////////////////////////////////	
	// Initialize the libs	
	romfsInit();
	gfxInitDefault();
	// gfxSet3D(true); // Enable stereoscopic 3D

	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();



	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);


	
	initSprites();
	initMainScreen();


	// Main loop
	while (aptMainLoop())
	{
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;

		
		getInput();

		app();

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(top, C2D_Color32(0x81, 0x81, 0xD9, 0xFF));
			C2D_TargetClear(bottom, C2D_Color32(0x81, 0x81, 0xD9, 0xFF));


			C2D_SceneBegin(top);
				renderMainScreen_Top(true);
				
			C2D_SceneBegin(bottom);
				if (mode == 1)
				{							
						C2D_DrawSprite(&cookie);
						C2D_DrawSprite(&shop);
						renderMainScreen_Bottom();
				}
				else if(mode == 2)
				{	
					if(madeTranslation == false)
					{
						for(int i=0; i<70; i++)
						{
							C2D_DrawSprite(&shop);
							C2D_SpriteMove(&shop, 0, -.5);
						}
						madeTranslation = true;
					}

					//renderShopScreen_Bottom();
				}
				else if (mode == 3)//Settings
				{
						renderBottomSettingsScreen();
					
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

void renderMsgBox(char* title, char* message, int buttons){
	msgTitle = title;
	msgMessage = message;
	msgButtons = buttons;
}





