#include "Decoder.h"
//#include "ADCSWTrigger.c"
#include "../inc/PLL.h"
#include "../inc/CortexM.h"
#include "../inc/UART0int.h"
#include "../inc/FIFO.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Mod, SIZE, uint32_t, SUCCESS, FAIL)
char recovered_String[SIZE];

int times = 0;


void printModBuffer(void){
    while(ModFifo_Size() != 0){
        static int i = 0;
        uint32_t read_val = 0;
        ModFifo_Get(&read_val);
        UART_OutChar(read_val);
        recovered_String[i] = read_val;
        i++;
    }
}


int decoderMain(void) {
    uint32_t period = 2000000; // random number for now
    //Init ADC -- this will sample at the given inputs
    // Max sample rate: <=125,000 samples/second
    // Sequencer 0 priority: 1st (highest)
    // Sequencer 1 priority: 2nd
    // Sequencer 2 priority: 3rd
    // Sequencer 3 priority: 4th (lowest)
    // SS3 triggering event: software trigger
    // SS3 1st sample source: Ain9 (PE4)
    // SS3 interrupts: enabled but not promoted to controller
    DisableInterrupts();
    ADC0_InitSWTriggerSeq3_Ch9(); //Use pe4 as input for mic
    Timer0_Init();
    Timer0A_SetPeriod(period);
    ModFifo_Init();

    //Now that we've sampled, we want to wait until conversion is finished

    while(1){
        if(times > 8){
            //wait till we get 8 values, then dump them, and do it again?
            printModBuffer();
            times = 0;
        }
    }


    //Init a hardware timer
    // read value of completed adc conversion into a fifo
    // construct into a character
    // append all characters together
    return 1;
}

void Timer0A_Handler(void){

  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
  uint32_t value = ADC0_InSeq3();
  ModFifo_Put( value ); // everytime we hit this handler, put the new value into the fifo
  times++;
}

