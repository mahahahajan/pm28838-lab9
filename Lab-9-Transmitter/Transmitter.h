#ifndef _TRANSMITTER_H_
#define _TRANSMITTER_H_

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "TimerDriver.h"

#include "DAC.h"

#define BUS 80000000
//#define DEFAULT_LENGTH 3000
#define DEFAULT_LENGTH 10000

//#define HIGH_PERIOD 1600
#define HIGH_PERIOD 1100

#define DAC_OUT_LOW 0

void Transmitter_Init(void(*fifo_task)(void));

int getParity(unsigned int n);

void Transmitter_output_handler(void);

void Transmitter_set_outchar_vector(uint8_t vector);

#endif
