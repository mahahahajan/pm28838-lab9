#include <Receiver.h>

volatile uint8_t ready_and_active = 0;
volatile uint32_t counter = COUNTER_RELOAD * 5;
uint8_t calibrating = 0;
uint32_t sum = 0;
volatile uint8_t bits = 0;
uint32_t threshold = 0;

//extern uint8_t times;
extern volatile int fifo_size;
void (*doneTask)(void);

void Timer0A_Handler(void) {
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;	// acknowledge timer0A timeout
	if (counter == 0) {
		uint32_t value = ADC0_InSeq3();
		if (ready_and_active) {
			if (value > threshold + 250) {
				ModFifo_Put(1);
			} else {
				ModFifo_Put(0);
			}
			fifo_size++;
			counter = COUNTER_RELOAD / COUNTER_RELOAD_DIV;
			//times++;
			bits++;
			if (bits == NUM_BITS * COUNTER_RELOAD_DIV) {
			    ready_and_active = 0;
				doneTask();
//			    Receiver_decodeMessage();
			}
		} else if (calibrating == 0){
            calibrating = 1;
            counter = COUNTER_RELOAD;
        } else if (calibrating == 1){
            calibrating = 2;
            uint32_t avg = sum / COUNTER_RELOAD;
            threshold = avg + 30;
        } else if (value > (threshold + 250) /*|| value < (threshold - 50) */) {
		    ready_and_active = 1;
			counter = COUNTER_RELOAD / COUNTER_RELOAD_DIV + 10;//+ COUNTER_RELOAD / 4;
			bits = 0;
			//times = 0;
		}
	} else if(calibrating == 1) {
	    counter--;
	    uint32_t value = ADC0_InSeq3();
	    sum += value;
	} else counter--;
}

void Receiver_decodeMessage(void) {
	//use Fifo and construct message
    uint8_t numZero = 0;
    uint8_t numOne = 0;
    uint8_t finalFifoSize = 0;
    int i = 0;
    uint16_t vector = 0;

	while(fifo_size != 0){
	    numOne = 0;
	    for(i = 0; i < COUNTER_RELOAD_DIV; i++){
	        uint8_t read_val = 0;
	        ModFifo_Get(&read_val);
	        fifo_size--;
	        if(read_val == 1){
	            numOne++;
	        }
	    }
	    if(numOne >= 3){
	        vector = (vector << 1) | 0x0001;
	    } else vector = (vector << 1) & (~0x0001);
	    finalFifoSize++;
	}
//	Disregard first bit
//	Disregard message end bit?
//	uint16_t charVal = 0;
//	uint8_t n = 0;
//	for(i = 1; i < 10; i++){
//	    uint8_t read_val = 0;
//	    FinalFifo_Get(&read_val);
//	    finalFifoSize--;
//
//	}

	uint8_t parityBit = vector & (0x0002) >> 1;
	vector = (vector & (0x3FC)) >> 2;
	char tempChar = (char) vector;
	UART_OutChar(tempChar);
}

void Receiver_init(void (*task)(void)) {
	doneTask = task;
	ADC0_InitSWTriggerSeq3_Ch9(); //Use pe4 as input for mic
}
//
//Stuff for test main
uint8_t testNums[] = {1,0,1,1,0,0,1,1,0,0, 1,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,
                  1,0,0,1,1,0,0,1,0,1,
                  0,0,0,0,0,0,0,0,0,0,
                  1,0,0,1,1,0,0,1,0,1,
                  0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,
                  0,1,0,0,1,1,0,0,1,1,
                  0,0,1,0,0,1,1,0,0,1};

//Test Decoder to see if decode process works (Test Main 11)
 void Decoder_main() {
     ModFifo_Init();
     int i = 0;
     //Put our test values into the fifo
     for(i = 0; i < 110; i++){
         ModFifo_Put(testNums[i]);
         fifo_size++;
     }
     //Run decoder task
     Receiver_decodeMessage();
     //Verify that it was properly debugged via UART
 }

 //Test ADC -> Decoder and make sure data is streamed properly (Test Main 10)
 void DecoderStreaming_main(){
     ModFifo_Init();
     //This is to test our fifo (put stuff in and get stuff out is our streaming?)
     int i = 0;
     //Put our test values into the fifo
     for(i = 0; i < 110; i++){
         ModFifo_Put(testNums[i]);
         fifo_size++;
     }
     uint8_t val = 0;
     for(i = 0; i < fifo_size; i++){
         ModFifo_Get(&val);
         UART_OutString("Fifo In was %s, Fifo out was %s");
         UART_OutChar(testNums[i]);
         UART_OutChar('\t');
         UART_OutChar(val);
     }
 }

