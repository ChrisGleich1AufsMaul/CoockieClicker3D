#include <citro2d.h>
#include <3ds.h>
#ifndef GUI_H
#define GUI_H



extern C2D_TextBuf g_staticBuf, g_dynamicBuf;
// extern C2D_Text g_staticText[12];


void initializeData();


void renderMainScreen_Top(bool log);
void renderMainScreen_Bottom();

void renderShopScreen_Top(bool log);
void renderShopScreen_Bottom();



// void renderTopSettingsScreen();
// void renderBottomSettingsScreen();

void initBuffer();
void initMainScreen();
void InitSettingsScreen();
// void initImg();


void MessageBox(char* title, char* message, int buttons, int screen);

void exitScene();

#endif
