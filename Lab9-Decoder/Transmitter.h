#ifndef _TRANSMITTER_H_
#define _TRANSMITTER_H_

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "TimerDriver.h"

#include "DAC.h"

#define BUS 80000000
#define SXTTH       BUS / 16
#define HALF        8  * SXTTH

#define DEFAULT_LENGTH HALF

#define BPM 120

#define HIGH_FREQ 700

void Transmitter_Init(void(*fifo_task)(void));

void Transmitter_output_handler(void);

void Transmitter_set_outchar_vector(uint8_t vector);

#endif
