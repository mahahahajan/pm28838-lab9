#ifndef _SWITCHDRIVER_H_
#define _SWITCHDRIVER_H_

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/CortexM.h"

#include "AudioDriver.h"
//#include "Music.h"


void Switches_Init(void);

void Switches_Loop(void);

void TogglePlayPause(void);

void Mode(void);

#endif
