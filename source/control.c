#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <fat.h>
#include <stdbool.h>
#include <citro2d.h>
#include <dirent.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include "control.h"
#include "input.h"
#include "gui.h"
#include "main.h"




bool ignoreMessage = false;
int mode = 1;
bool msgbox = false;


float cookiesTotal = 180;
float cookiesPerSecond = 0;

int upgrades_total = 2;
char upgrade[2][20] = {"Autoclicker", "Clock"};
float upgrade_costs[2] = {50, 			200};
float upgrade_gain[2] = {.1, 			1};
float upgradeInventar[2] = {0, 			0};


u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame


int day;
int month;
int year;
int hours;
int minutes;
int seconds;
int seconds_old = -1;


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
		if (kDown != kDownOld || kHeld != kHeldOld)// || kUp != kUpOld)
		{
			if (ButtonClick("closeShop_Click", 320/2 - 60, 5, 120, 50)) {
				mode = 1; 
			}

			for (int i=0; i<upgrades_total; i++){
				//C2D_DrawRectSolid(20.0f, 85.0f + 25*i, 0.4f, 270.0f, 20.0f, C2D_Color32f(.5f,.5f,.5f,.5f));
				if (ButtonClick("upgrade", 20, 85 + 25*i, 270, 20)) {
					float upgradeCostsCalc = upgrade_costs[i] + upgrade_costs[i] * upgradeInventar[i];
					if(upgradeCostsCalc<cookiesTotal){
						if(upgradeInventar[i]!=0) cookiesTotal -= upgradeCostsCalc; else cookiesTotal -= upgrade_costs[i];
						upgradeInventar[i]++;
					}
				}
			}
		}
		if (kDown & KEY_SELECT){
			mode = 1;
		}

	


	}

	
	time_t unixTime = time(NULL);
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);

	day = timeStruct->tm_mday;
	month = timeStruct->tm_mon;
	year = timeStruct->tm_year +1900;
	hours = timeStruct->tm_hour;
	minutes = timeStruct->tm_min;
	seconds = timeStruct->tm_sec;
	if(seconds!=seconds_old){
		seconds_old = seconds;
		for (int i=0; i<upgrades_total; i++){
			cookiesTotal += upgrade_gain[i] * upgradeInventar[i];
		}
	}
	
}