#include "Decoder.h"
//#include "ADCSWTrigger.c"
#include "../inc/PLL.h"
#include "../inc/CortexM.h"
#include "../inc/UART0int.h"
#include "../inc/FIFO.h"

#include "TimerDriver.h"

//#define SIZE 1024
//#define SUCCESS 1
//#define FAIL 0
//
////AddPointerFifo(Mod, SIZE, uint32_t, SUCCESS, FAIL)
////char recovered_String[SIZE];


uint16_t threshold = 165;
uint16_t threshold2 = 165 - 50;
uint8_t ready = 0;
#define COUNTER_RELOAD 10000
uint32_t counter = COUNTER_RELOAD;
volatile uint8_t bits = 0;
extern uint8_t times;
void (*doneTask)(void);

void Timer0A_Handler(void){

  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
//  int i = 0;
//  for(i = 0; i < 10; i++){
//      data = ADC0_InSeq3();
//                UART_OutString("\n\rADC data =");
//                UART_OutUDec(data);
//  }
  if(counter != 0){
      counter--;
  }
  else {
//      uint32_t data;
      uint32_t value = ADC0_InSeq3();
        //IF VALUE < THRESHOLD -- > This is a zero, set ready to 1, start filling fifo

        if(ready){
      //      printf("1");
//
            if(value > threshold2){
      //          printf("2");
                int x = 2;
                ModFifo_Put(1);
            } else{
                int y = 3;
                ModFifo_Put( 0 ); // everytime we hit this handler, put the new value into the fifo
            }
            counter = COUNTER_RELOAD;
            //times++;
            bits++;
            if (bits == 10) {
                ready = 0;
                doneTask();
            }
        } else if(value > threshold) {
            ready = 1;
            counter = COUNTER_RELOAD + (COUNTER_RELOAD/5);
            bits = 0;
            //times = 0;
            //Move ModFifo_Put and times++ into here after i get my threshold
        }
  }


//}
}

void decodeMessage(void) {
    //use Fifo and construct message
    printf("Test");
}

void setDoneTask(void(*task)(void)) {
    doneTask = task;
}
