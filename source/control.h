#ifndef APP_H
#define APP_H

void app();
void StartUp();
void getWeather();
void variableReset();
void doAppJump();
extern int checkStatus();


extern int cookiesTotal;
extern float cookiesPerSecond;

extern char upgrade[2][20];
extern float upgrade_gain[2];

extern int mode;
extern bool loading;

#endif
