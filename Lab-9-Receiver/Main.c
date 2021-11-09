#include "Main.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Mod, SIZE, uint8_t, SUCCESS, FAIL)
char recovered_String[SIZE];

uint32_t period = 1100;
int times = 0;

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}


void printModBuffer(void){
    while(ModFifo_Size() != 0){
        static int i = 0;
        uint32_t read_val = 0;
        ModFifo_Get(&read_val);
        UART_OutUDec(read_val);
        recovered_String[i] = read_val;
        i++;
    }
    OutCRLF();
}



extern uint8_t ready;

//debug code



int main(void){

  PLL_Init(Bus80MHz);       // set system clock to 50 MHz
  DisableInterrupts();


  setDoneTask(&printModBuffer);
  ADC0_InitSWTriggerSeq3_Ch9(); //Use pe4 as input for mic
  UART_Init();              // initialize UART
  UART_OutString(" UART0 is ready to use!");
  OutCRLF();

  Timer0_Init();
  Timer0A_SetPeriod(period);

//  Timer0A_Enable();
  ModFifo_Init();



      //Now that we've sampled, we want to wait until conversion is finished
  EnableInterrupts();       // Enable interrupts

  while(1){
        //IF VALUE < THRESHOLD -- > This is a zero, set ready to 1, start filling fifo
      WaitForInterrupt();
      /*
      if(ready){
//          printf("Test here ");
          if(times = 10){
              //wait till we get 8 values, then dump them, and do it again?
              printModBuffer();
              //decodeMessage();
              times = 0;
              ready = 0;
          }
      }
      */
  }
  //Init a hardware timer
  // read value of completed adc conversion into a fifo
  // construct into a character
  // append all characters together
  return 1;
}

