#include "input.h"
#include <3ds.h>
#include <stdio.h>

//Variables
u32 input;
u16 posX;
u16 posY;
u16 oldposX;
u16 oldposY;

void getInput()
{
	//Touch input
	touchPosition myTouchPosition;
	hidTouchRead(&myTouchPosition);

	posX = myTouchPosition.px;
	posY = myTouchPosition.py;

	//HID Input
	hidScanInput();
	input = hidKeysDown();
}

//####################################################################################################
//									Touch button event checker
//####################################################################################################
// int ButtonClick(char* name, int posX, int posY, int width, int height, int touchX, int touchY) {
int ButtonClick(char* name, int startX, int startY, int width, int height) {
	int endX = startX + width - 1;
	int endY = startY + height - 1;

	if (posX >= startX && posY >= startY && posX <= endX && posY <= endY) {
		return true; //TRUE
	} else {
		return false; //FALSE
	}
}