#ifndef _DECODER_H_
#define _DECODER_H_


#include <stdint.h> // C99 variable types
#include "../inc/ADCSWTrigger.h"
#include "TimerDriver.h"

#define COUNTER_RELOAD 10000
//#define COUNTER_RELOAD_DIV 100
#define COUNTER_RELOAD_DIV 5

//#include "ADCSWTrigger.c"
#include "../inc/PLL.h"
#include "../inc/CortexM.h"
#include "../inc/UART0int.h"
#include "../inc/FIFO.h"

#include "TimerDriver.h"

#endif
