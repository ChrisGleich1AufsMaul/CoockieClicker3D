#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "control.h"
#include "input.h"
#include "gui.h"
#include <stdbool.h>
#include <citro2d.h>
#include <dirent.h>
#include <inttypes.h>
#include <math.h>
#include "main.h"



bool ignoreMessage = false;
int mode = 1;
bool msgbox = false;


int cookiesTotal = 0;
float cookiesPerSecond = 0;

int upgrade_total = 2;
char upgrade[2][20] = {"Autoclicker", "Clock"};
float upgrade_gain[2] = {.1, 			1};


u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame

//repeats
void app()
{
	u32 kDown = hidKeysDown();
	//hidKeysHeld returns information about which buttons have are held down in this frame
	u32 kHeld = hidKeysHeld();
	//hidKeysUp returns information about which buttons have been just released
	u32 kUp = hidKeysUp();

	bool justPressed = false;
	if(kDown && justPressed == false)
		justPressed = true;
	else
		justPressed = false;


	
	if (mode == 1)//App menu
	{
		// for(int i=9; i<360; i++){
		// 	float r = 55;
		// 	float pointX = cos(i);
		// 	float pointY = sin(i);
			// if (ButtonClick("Cookie_Click", 320/2 - 55, 60, 110, 110) && justPressed) {
		if (kDown != kDownOld || kHeld != kHeldOld)// || kUp != kUpOld)
		{
			if (ButtonClick("Cookie_Click", 320/2 - 55, 60, 110, 110)) {
					cookiesTotal++;
			}
			if (ButtonClick("openShop_Click", 320/2 - 60, 190, 120, 50)) {
					mode = 2;
			}
		}

		//Set keys old values for the next frame
		kDownOld = kDown;
		kHeldOld = kHeld;
		kUpOld = kUp;
		// }

	}
	else if (mode == 2) //Shop
	{		
		if (ButtonClick("closeShop_Click", 320/2 - 60, 5, 120, 50) && kDown) {
			mode = 1; 
		}

	


	}
}