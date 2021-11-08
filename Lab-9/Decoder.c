#include "Decoder.h"
//#include "ADCSWTrigger.c"




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

    //Now that we've sampled, we want to wait until conversion is finished


    //Init a hardware timer
    // read value of completed adc conversion into a fifo
    // construct into a character
    // append all characters together
    return 1;
}

void Timer0A_Handler(void){

  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout


}

