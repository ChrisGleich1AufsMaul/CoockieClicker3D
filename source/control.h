#ifndef APP_H
#define APP_H

void app();
void StartUp();
void variableReset();
void doAppJump();
extern int checkStatus();

extern bool cookie_press;

extern float cookiesTotal;
extern float cookiesPerSecond;

extern char upgrade[2][20];
extern float upgrade_gain[2];
extern float upgrade_costs[2];
extern float upgradeInventar[2];
extern int upgrades_total;

extern int mode;
extern bool msgbox;
extern bool loading;


extern int day;
extern int month;
extern int year;
extern int hours;
extern int minutes;
extern int seconds;



extern bool logToggle;
#endif
