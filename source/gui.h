#include <citro2d.h>
#include <3ds.h>
#include "control.h"
#ifndef GUI_H
#define GUI_H

#define DRAWING_MAX_VERTICES 8192

typedef struct
{
	float position[3];
	float texcoord[2];
} drawVertex_s;

extern C2D_TextBuf g_staticBuf, g_dynamicBuf;
// extern C2D_Text g_staticText[12];


void initializeData();


void renderMainScreen_Top(float iod);
void renderMainScreen_Bottom();

void renderShopScreen_Top();
void renderShopScreen_Bottom();



// void renderTopSettingsScreen();
// void renderBottomSettingsScreen();

void initBuffer();
void initMainScreen();
void InitSettingsScreen();
// void initImg();


void MessageBox(char* title, MSG_BOX_ALIGN msgAlign, char* message, MSG_BOX_BUTTON msgButtons, int screen);

void exitScene();

#endif
