#include "DisplayDriver.h"



void DisplayInit(void) {
    ST7735_InitR(INITR_REDTAB);
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_SetTextColor(ST7735_WHITE);
}

void Display_Print(char c) {
    ST7735_OutChar(c);
}

void Display_TestMain(void) {
    DisplayInit();
    ST7735_DrawString(7, 8, "Hello World", ST7735_WHITE);
    //Could replace with ST7735_OutString
    Display_Print('!');
}
