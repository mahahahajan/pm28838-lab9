#ifndef _DECODER_H_
#define _DECODER_H_


#include <stdint.h> // C99 variable types

#include "inc/PLL.h"
#include "inc/CortexM.h"
#include "inc/UART0int.h"
#include "inc/FIFO_CCS.h"
#include "inc/ADCSWTrigger.h"

#include "TimerDriver.h"


#define COUNTER_RELOAD 10000
//#define COUNTER_RELOAD_DIV 100
#define COUNTER_RELOAD_DIV 20

#define ready_bit_high_threshold 130
#define data_bit_high_threshold ready_bit_high_threshold - 10

void Receiver_init(void (*task)(void));

int ModFifo_Put(uint8_t);
int ModFifo_Get(uint8_t*);

#endif
