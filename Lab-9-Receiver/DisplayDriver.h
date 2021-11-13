#ifndef DISPLAYDRIVER_H_
#define DISPLAYDRIVER_H_

#include "../inc/ST7735.h"

//This will just call ST7735_Init()
void DisplayInit(void);

void Display_Print(char c);

void Display_TestMain(void);


#endif /* DISPLAYDRIVER_H_ */
