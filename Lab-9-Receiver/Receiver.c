#include <Receiver.h>

volatile uint8_t ready_and_active = 0;
volatile uint32_t counter = COUNTER_RELOAD;
volatile uint8_t bits = 0;
//extern uint8_t times;
extern volatile int fifo_size;
void (*doneTask)(void);

void Timer0A_Handler(void) {
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;	// acknowledge timer0A timeout
	if (counter == 0) {
		uint32_t value = ADC0_InSeq3();
		if (ready_and_active) {
			if (value > data_bit_high_threshold) {
				ModFifo_Put(1);
			} else {
				ModFifo_Put(0);
			}
			fifo_size++;
			counter = COUNTER_RELOAD / COUNTER_RELOAD_DIV;
			//times++;
			bits++;
			if (bits == 10 * COUNTER_RELOAD_DIV) {
			    ready_and_active = 0;
				doneTask();
			}
		} else if (value > ready_bit_high_threshold) {
		    ready_and_active = 1;
			counter = (COUNTER_RELOAD / COUNTER_RELOAD_DIV); //+ 10;
			bits = 0;
			//times = 0;
		}
	} else counter--;
}

void Receiver_decodeMessage(void) {
	//use Fifo and construct message
	printf("Test");
}

void Receiver_init(void (*task)(void)) {
	doneTask = task;
	ADC0_InitSWTriggerSeq3_Ch9(); //Use pe4 as input for mic
}
