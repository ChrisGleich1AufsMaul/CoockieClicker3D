#ifndef INPUT_H
#define INPUT_H
#include <3ds.h>

void getInput();
int ButtonClick(char* name, int startX, int startY, int width, int height);

extern u32 input;
extern u16 posX;
extern u16 posY;
extern u16 oldposX;
extern u16 oldposY;

#endif
