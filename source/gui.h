#include <citro2d.h>
#include <3ds.h>
#include "control.h"
#ifndef GUI_H
#define GUI_H



extern C2D_TextBuf g_staticBuf, g_dynamicBuf;
// extern C2D_Text g_staticText[12];


void initializeData();


void renderMainScreen_Top();
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
