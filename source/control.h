#ifndef APP_H
#define APP_H

typedef enum{
    msgButtonOkay,
    msgButtonOkayAbort
}MSG_BOX_BUTTON;

typedef enum{
    alignLeft,
    alignCenter,
    alignRight
}MSG_BOX_ALIGN;

// typedef enum{
//     alignLeft = 1,
//     alignCenter = 2,
//     alignRight = 3
// }MSG_BOX_STYLE;

typedef struct{
    // MSG_BOX_BUTTON MessageBoxButtons;
    MSG_BOX_BUTTON MessageBoxButtonsOkay;
    MSG_BOX_BUTTON MessageBoxButtonsOkayAbort;
    MSG_BOX_ALIGN MessageBoxAlignLeft;
    MSG_BOX_ALIGN MessageBoxAlignCenter;
    MSG_BOX_ALIGN MessageBoxAlignRight;
} MSG_BOX_STYLE;


typedef struct {
	char* msgTitle;
	MSG_BOX_ALIGN msgAlign;
	char* msgMessage;
	MSG_BOX_BUTTON msgButtons;
	bool show;
}Message_Box;

// predefine a "normal" "style-object"
extern MSG_BOX_STYLE msgBoxStyle;


// extern MSG_BOX_STYLE msgBoxStyle;
// extern MSG_BOX_BUTTON MessageBoxButtonsOkay;
// extern MSG_BOX_BUTTON MessageBoxButtonsOkayAbort;
// extern MSG_BOX_ALIGN MessageBoxAlignLeft;
// MSG_BOX_ALIGN MessageBoxAlignCenter;
// MSG_BOX_ALIGN MessageBoxAlignRight;


void app();
void StartUp();
void variableReset();
void doAppJump();
extern int checkStatus();

extern bool cookie_press;

extern float cookiesTotal;
extern float cookiesPerSecond;

extern const char upgrade[2][20];
extern float upgrade_gain[2];
extern float upgrade_costs[2];
extern float upgradeInventar[2];
extern const int upgrades_total;

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
