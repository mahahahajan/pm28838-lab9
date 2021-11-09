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

uint8_t ready = 1;


void Timer0A_Handler(void){

  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
  uint32_t value = ADC0_InSeq3();
  //IF VALUE < THRESHOLD -- > This is a zero, set ready to 1, start filling fifo
  if(value < 2000) {
      ready = 1;
      //Move ModFifo_Put and times++ into here after i get my threshold
  }
  ModFifo_Put( value ); // everytime we hit this handler, put the new value into the fifo
  times++;
}

void decodeMessage(void) {
    //use Fifo and construct message
}


