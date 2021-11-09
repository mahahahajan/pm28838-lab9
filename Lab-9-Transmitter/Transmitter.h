#ifndef _TRANSMITTER_H_
#define _TRANSMITTER_H_

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "TimerDriver.h"

#include "DAC.h"

#define BUS 80000000
#define DEFAULT_LENGTH 20000

#define BPM 120

#define HIGH_FREQ 700

#define DAC_OUT_STEADY 0

void Transmitter_Init(void(*fifo_task)(void));

int getParity(unsigned int n);

void Transmitter_output_handler(void);

void Transmitter_set_outchar_vector(uint8_t vector);

#endif
