#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <citro2d.h>
#include "gui.h"
#include "control.h"

#define ctablesize 3
#define posxysize 240


char buffer[100];
static char CC_Headline[64];

//C3D
C3D_BufInfo g_drawBufInfo;
static drawVertex_s* s_drawBuffer;
static int s_drawBufferPos;
static float s_drawBufferZ = 0.5;

///////////////////////////////////////////
//                 menues                //
///////////////////////////////////////////
C2D_TextBuf g_dynamicBuf, g_staticBuf;
C2D_Text g_headlineText[3], g_staticText[13];

///////////////////////////////////////////
//                  C2D                  //
///////////////////////////////////////////
void initBuffer()
{
	g_staticBuf  = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
	g_dynamicBuf = C2D_TextBufNew(4096);

	
	// Create vertex buffer
	s_drawBuffer = (drawVertex_s*)linearAlloc(sizeof(drawVertex_s)*DRAWING_MAX_VERTICES);
	
	// Configure buffer informations
	BufInfo_Init(&g_drawBufInfo);
	BufInfo_Add(&g_drawBufInfo, s_drawBuffer, sizeof(drawVertex_s), 2, 0x10);

	BufInfo_Add(&g_drawBufInfo, s_drawBuffer, sizeof(drawVertex_s), 2, 0x10);
}
void initMainScreen(void)
{
	//Top screen
	C2D_TextParse(&g_headlineText[0], g_staticBuf, "CookieClicker3D");
	C2D_TextOptimize(&g_headlineText[0]);

	
	// sprintf(CC_Headline, "CookieClicker3D \xEE\x80\x9D");
	sprintf(CC_Headline, "CookieClicker3D");

}
void InitSettingsScreen(void)
{
	C2D_TextParse(&g_staticText[11], g_staticBuf, "");
	C2D_TextOptimize(&g_staticText[11]);
}

///////////////////////////////////////////
//                  C3D                  //
///////////////////////////////////////////
// void drawingSubmitPrim(GPU_Primitive_t prim, int vertices)
// {
// 	C3D_DrawArrays(prim, s_drawBufferPos-vertices, vertices);
// }
// void drawingAddVertex(float vx, float vy, float tx, float ty)
// {
// 	drawVertex_s* vtx = &s_drawBuffer[s_drawBufferPos++];
// 	vtx->position[0] = vx;
// 	vtx->position[1] = vy;
// 	vtx->position[2] = s_drawBufferZ;
// 	vtx->texcoord[0] = tx;
// 	vtx->texcoord[1] = ty;
// }

// void textDraw(float x, float y, float scaleX, float scaleY, bool baseline, const char* text)
// {
	
// 	static float s_textScale;


// 	ssize_t  units;
// 	uint32_t code;

// 	const uint8_t* p = (const uint8_t*)text;
// 	float firstX = x;
// 	u32 flags = GLYPH_POS_CALC_VTXCOORD | (baseline ? GLYPH_POS_AT_BASELINE : 0);
// 	scaleX *= s_textScale;
// 	scaleY *= s_textScale;
// 	do
// 	{
// 		if (!*p) break;
// 		units = decode_utf8(&code, p);
// 		if (units == -1)
// 			break;
// 		p += units;
// 		if (code == '\n')
// 		{
// 			x = firstX;
// 			y += ceilf(scaleY*fontGetInfo(NULL)->lineFeed);
// 		}
// 		else if (code > 0)
// 		{
// 			int glyphIdx = fontGlyphIndexFromCodePoint(NULL, code);
// 			fontGlyphPos_s data;
// 			fontCalcGlyphPos(&data, NULL, glyphIdx, flags, scaleX, scaleY);

// 			// Draw the glyph
// 			// drawingSetTex(&s_glyphSheets[data.sheetIndex]);
// 			drawingAddVertex(x+data.vtxcoord.left,  y+data.vtxcoord.bottom, data.texcoord.left,  data.texcoord.bottom);
// 			drawingAddVertex(x+data.vtxcoord.right, y+data.vtxcoord.bottom, data.texcoord.right, data.texcoord.bottom);
// 			drawingAddVertex(x+data.vtxcoord.left,  y+data.vtxcoord.top,    data.texcoord.left,  data.texcoord.top);
// 			drawingAddVertex(x+data.vtxcoord.right, y+data.vtxcoord.top,    data.texcoord.right, data.texcoord.top);
// 			drawingSubmitPrim(GPU_TRIANGLE_STRIP, 4);

// 			x += data.xAdvance;

// 		}
// 	} while (code > 0);
// }

// textDrawInBox(CC_Headline, 1, 0.5f, 0.5f, 200.0f, 80.0f, logo_right);
// void textDrawInBox(const char* text, int orientation, float scaleX, float scaleY, float baseline, float left, float right)


//Renderfunctions

/////////////////////////////////////////				Main Screen 			////////////////////////////
void renderMainScreen_Top(float iod)
{
	C2D_DrawText(&g_headlineText[0], C2D_AtBaseline | C2D_WithColor, 60.0f + iod, 100.0f, .2f, 1.4f, 1.4f, C2D_Color32f(1.0f,.6f,.2f,1.0f));	
	
	float scale = 1;
	// textDraw(100, 100, scale, scale, true, CC_Headline);

	//dynamic text
	C2D_TextBufClear(g_dynamicBuf);
	
	char buf[160];
	C2D_Text dynText;

	if(logToggle){
		C2D_DrawRectSolid(0.0, 150., 0.4, 150, 60, C2D_Color32f(0,0,0,1));
		float fontSize = .5;

		// snprintf(buf, sizeof(buf), "msgButton: %i", msgButtonOkay);
		// C2D_TextParse(&dynText, g_dynamicBuf, buf);
		// C2D_TextOptimize(&dynText);
		// C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 10.0f, 165.0f, 0.5f, fontSize, fontSize, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));	

		//snprintf(buf, sizeof(buf), "%d", sizeof(upgrade));
		snprintf(buf, sizeof(buf), "%i", seconds);
		C2D_TextParse(&dynText, g_dynamicBuf, buf);
		C2D_TextOptimize(&dynText);
		C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 10.0f, 180.0f, 0.5f, fontSize, fontSize, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));	

		snprintf(buf, sizeof(buf), "AutClic: %.f", upgradeInventar[0]);
		C2D_TextParse(&dynText, g_dynamicBuf, buf);
		C2D_TextOptimize(&dynText);
		C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 10.0f, 195.0f, 0.5f, fontSize, fontSize, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));	
	}

}
void renderMainScreen_Bottom()
{
	//dynamic text
	C2D_TextBufClear(g_dynamicBuf);

	char buf[160];
	C2D_Text dynText;

	//Cookies total
	snprintf(buf, sizeof(buf), "%.f Cookies", cookiesTotal);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 10.0f, 25.0f, 0.5f, 1.2f, 1.2f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));	
	
	//Cookies per second
	//char* string;//char string[5];
	//string.Format("%.2f", cookiesPerSecond);

	snprintf(buf, sizeof(buf), "%f C/s", cookiesPerSecond);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 10.0f, 40.0f, 0.5f, .7f, .7f, C2D_Color32f(.8f, .8f, .8f, 1.0f));	
}
/////////////////////////////////////////				Shop Screen 			////////////////////////////
void renderShopScreen_Top()
{
	// C2D_DrawText(&g_headlineText[0], C2D_AtBaseline | C2D_WithColor, 60.0f, 100.0f, 0.5f, 1.4f, 1.4f, C2D_Color32f(1.0f,.6f,.2f,1.0f));	


	// //dynamic text
	// C2D_TextBufClear(g_dynamicBuf);
	
	// char buf[160];
	// C2D_Text dynText;

	// if(logToggle){
	// 	C2D_DrawRectSolid(0.0, 160., 0.4, 150, 60, C2D_Color32f(0,0,0,1));

	// 	snprintf(buf, sizeof(buf), "%li", hidKeysDown());
	// 	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	// 	C2D_TextOptimize(&dynText);
	// 	C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 10.0f, 190.0f, 0.5f, 0.8f, 0.8f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));	
	// }

}
void renderShopScreen_Bottom()
{
	//dynamic text
	C2D_TextBufClear(g_dynamicBuf);

	char buf[160];
	C2D_Text dynText;

	snprintf(buf, sizeof(buf), "%.2f Cookies", cookiesTotal);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 5.0f, 15.0f, 0.5f, .6f, .6f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));


	//int upgrades_total = 2;//sizeof(upgrade);
	for (int i=0; i<upgrades_total; i++){
		C2D_DrawRectSolid(20.0f, 85.0f + 25*i, 0.4f, 270.0f, 20.0f, C2D_Color32f(.5f,.5f,.5f,.5f));

		snprintf(buf, sizeof(buf), "%s", upgrade[i]);
		C2D_TextParse(&dynText, g_dynamicBuf, buf);
		C2D_TextOptimize(&dynText);
		C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 25.0f, 100.0f + 25*i, 0.5f, .6f, .6f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
		
		snprintf(buf, sizeof(buf), "%.2fc/s", upgrade_gain[i]);
		C2D_TextParse(&dynText, g_dynamicBuf, buf);
		C2D_TextOptimize(&dynText);
		C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 130.0f, 100.0f + 25*i, 0.5f, .6f, .6f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
		
		float upgradeCostsCalc = upgrade_costs[i] + upgrade_costs[i] * upgradeInventar[i];
		int color;
		if(upgradeCostsCalc>cookiesTotal)
			color = C2D_Color32f(1.0f,.2f,0.2f,1.0f);
		else
			color = C2D_Color32f(.2f,1.0f,0.2f,1.0f);
		snprintf(buf, sizeof(buf), "%.fc", upgradeCostsCalc);
		C2D_TextParse(&dynText, g_dynamicBuf, buf);
		C2D_TextOptimize(&dynText);
		C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 200.0f, 100.0f + 25*i, 0.5f, .6f, .6f, color);
		
		snprintf(buf, sizeof(buf), "Buy");
		C2D_TextParse(&dynText, g_dynamicBuf, buf);
		C2D_TextOptimize(&dynText);
		C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 260.0f, 100.0f + 25*i, 0.5f, .6f, .6f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
	}
}

/////////////////////////////////////////				Settings Screen 			////////////////////////////
	// void renderBottomSettingsScreen()
	// {   
	// 	C2D_DrawRectSolid(10.0f, 10.0f, 0.0f, 30.0f, 30.0f, C2D_Color32f(0.3f,0.3f,0.3f,1.0f));//maps symbol
	// 	C2D_DrawRectSolid(12.0f, 12.0f, 0.0f, 26.0f, 26.0f, C2D_Color32f(0.8f,0.8f,0.8f,0.9f));

	// 	C2D_DrawRectSolid(50.0f, 10.0f, 0.0f, 200.0f, 30.0f, C2D_Color32f(0.7f,0.7f,0.7f,0.8f));//textbox

	// 	C2D_DrawRectSolid(10.0f, 50.0f, 0.0f, 50.0f, 30.0f, C2D_Color32f(0.3f,0.3f,0.3f,1.0f));//selection
	// 	C2D_DrawRectSolid(12.0f, 52.0f, 0.0f, 46.0f, 26.0f, C2D_Color32f(0.8f,0.8f,0.8f,0.9f));

	// 	C2D_TextBufClear(g_dynamicBuf);
		
	// 	// char buf[160];
	// 	// C2D_Text dynText;
	// 	// snprintf(buf, sizeof(buf), "%s", town);
	// 	// C2D_TextParse(&dynText, g_dynamicBuf, buf);
	// 	// C2D_TextOptimize(&dynText);
	// 	// C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 55.0f, 35.0f, 0.1f, 0.9f, 0.9f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// 	//maps symbol	
	// 	// snprintf(buf, sizeof(buf), "");
	// 	// C2D_TextParse(&dynText, g_dynamicBuf, buf);
	// 	// C2D_TextOptimize(&dynText);
	// 	// C2D_DrawText(&dynText, C2D_AtBaseline | C2D_WithColor, 12.0f, 35.0f, 0.1f, 1.1f, 1.1f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
	// }




void MessageBox(char* title, MSG_BOX_ALIGN msgAlign, char* message, MSG_BOX_BUTTON msgButtons, int screen)
{
	C2D_TextBufClear(g_dynamicBuf);
	
	char buf[160];
	C2D_Text messageText;
	C2D_Text titleText;
	C2D_Text buttonsText;

	C2D_DrawRectSolid(0.0f, 0.0f, 0.7f, 400.0f, 240.0f, C2D_Color32f(0.2f,0.2f,0.2f,0.3f));//Background dimmed
	C2D_DrawRectSolid(30.0f, 30.0f, 0.8f, 340.0f, 180.0f, C2D_Color32f(0.8f,0.8f,0.8f,1.0f)); 

	snprintf(buf, sizeof(buf), "%s", title);
	C2D_TextParse(&titleText, g_dynamicBuf, buf);
	C2D_TextOptimize(&titleText); 
	C2D_DrawText(&titleText, C2D_AtBaseline | C2D_WithColor, 40.0f, 60.0f, 0.9f, 1.0f, 1.0f, C2D_Color32f(0.0f,0.0f,0.0f,1.0f));


	snprintf(buf, sizeof(buf), "%s", message);
	C2D_TextParse(&messageText, g_dynamicBuf, buf);
	C2D_TextOptimize(&messageText); 
	C2D_DrawText(&messageText, C2D_AtBaseline | C2D_WithColor, 40.0f, 90.0f, 0.9f, 0.6f, 0.6f, C2D_Color32f(0.0f,0.0f,0.0f,1.0f));

	if (msgButtons == msgButtonOkay){		
		snprintf(buf, sizeof(buf), "%s", " Okay");
		C2D_TextParse(&buttonsText, g_dynamicBuf, buf);
		C2D_TextOptimize(&buttonsText); 
		C2D_DrawText(&buttonsText, C2D_AtBaseline | C2D_WithColor, 170.0f, 200.0f, 0.9f, 0.6f, 0.6f, C2D_Color32f(0.0f,0.0f,0.0f,1.0f));
	} else 	if (msgButtons == msgButtonOkayAbort){		
		snprintf(buf, sizeof(buf), "%s", " Okay");
		C2D_TextParse(&buttonsText, g_dynamicBuf, buf);
		C2D_TextOptimize(&buttonsText); 
		C2D_DrawText(&buttonsText, C2D_AtBaseline | C2D_WithColor, 100.0f, 200.0f, 0.9f, 0.6f, 0.6f, C2D_Color32f(0.0f,0.0f,0.0f,1.0f));

		snprintf(buf, sizeof(buf), "%s", " Abort");
		C2D_TextParse(&buttonsText, g_dynamicBuf, buf);
		C2D_TextOptimize(&buttonsText); 
		C2D_DrawText(&buttonsText, C2D_AtBaseline | C2D_WithColor, 240.0f, 200.0f, 0.9f, 0.6f, 0.6f, C2D_Color32f(0.0f,0.0f,0.0f,1.0f));
	}

}   

 
void exitScene(void)
{
	// Delete the text buffers
	C2D_TextBufDelete(g_dynamicBuf);
	C2D_TextBufDelete(g_staticBuf);
}