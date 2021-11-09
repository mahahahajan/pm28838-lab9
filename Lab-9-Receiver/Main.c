#include "Main.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Mod, SIZE, uint8_t, SUCCESS, FAIL)
char recovered_String[SIZE];

uint32_t period = 1100;
int times = 0;
volatile int fifo_size = 0;
extern uint8_t ready_and_waiting;


// Output a CR,LF to UART to go to a new line
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}

// Print out current FIFO
void printModBuffer(void){
    while(fifo_size != 0){
        //static int i = 0;
        uint8_t read_val = 0;
        ModFifo_Get(&read_val);
        fifo_size--;
        UART_OutUDec(read_val);
        //recovered_String[i] = read_val;
        //i++;
    }
    OutCRLF();
}

int main(void){

  PLL_Init(Bus80MHz);       // set system clock to 50 MHz
  DisableInterrupts();
  UART_Init();              // initialize UART
  UART_OutString(" UART0 is ready to use!"); OutCRLF();
  EnableInterrupts();
  DisableInterrupts();
  Receiver_init(&printModBuffer);
  Timer_Init(period);
  ModFifo_Init();
  EnableInterrupts();       // Enable interrupts

  while(1) {
      WaitForInterrupt();
      /*
      if(ready_and_waiting){
          // printf("Test here ");
          if(times = 10){
              //wait till we get 8 values, then dump them, and do it again?
              printModBuffer();
              //decodeMessage();
              times = 0;
              ready_and_waiting = 0;
          }
      }
      */
  }
}

