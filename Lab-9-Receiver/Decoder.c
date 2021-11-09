#include "Decoder.h"

//#define SIZE 1024
//#define SUCCESS 1
//#define FAIL 0
//
////AddPointerFifo(Mod, SIZE, uint32_t, SUCCESS, FAIL)
////char recovered_String[SIZE];

uint16_t threshold = 165;
uint16_t threshold2 = 165 - 50;
uint8_t ready = 0;

uint32_t counter = COUNTER_RELOAD;
volatile uint8_t bits = 0;
extern uint8_t times;
extern volatile int fifo_size;
void (*doneTask)(void);

void Timer0A_Handler(void) {
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;	// acknowledge timer0A timeout
	if (counter != 0) {
		counter--;
	} else {
		uint32_t value = ADC0_InSeq3();
		//IF VALUE < THRESHOLD -- > This is a zero, set ready to 1, start filling fifo
		if (ready) {
			if (value > threshold2) {
				int x = 2;
				ModFifo_Put(1);
			} else {
				int y = 3;
				ModFifo_Put(0);	 // every time we hit this handler, put the new value into the fifo
			}
			fifo_size++;
			counter = COUNTER_RELOAD / COUNTER_RELOAD_DIV;
			//times++;
			bits++;
			if (bits == 10 * COUNTER_RELOAD_DIV) {
				ready = 0;
				doneTask();
			}
		} else if (value > threshold) {
			ready = 1;
			counter = (COUNTER_RELOAD / COUNTER_RELOAD_DIV) + 10;
			bits = 0;
			//times = 0;
		}
	}
}

void decodeMessage(void) {
	//use Fifo and construct message
	printf("Test");
}

void setDoneTask(void (*task)(void)) {
	doneTask = task;
}
