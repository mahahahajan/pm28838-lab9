#include "Main.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Mod, SIZE, uint8_t, SUCCESS, FAIL);
AddPointerFifo(Final, SIZE, uint8_t, SUCCESS, FAIL);
char recovered_String[SIZE];

uint32_t period = 1100;
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
void printFinalBuffer(void){
    while(fifo_size != 0){
        //static int i = 0;
        uint8_t read_val = 0;
        FinalFifo_Get(&read_val);
        fifo_size--;
        UART_OutUDec(read_val);
        //recovered_String[i] = read_val;
        //i++;
    }
    OutCRLF();
}


int main(void){


  // test_main();  // un-comment to run adc test main

  PLL_Init(Bus80MHz);       // set system clock to 50 MHz
  DisableInterrupts();
  UART_Init();              // initialize UART
  UART_OutString(" UART0 is ready to use!"); OutCRLF();
  EnableInterrupts();
  DisableInterrupts();
  Receiver_init(&Receiver_decodeMessage);
  Timer_Init(period);
  ModFifo_Init();
  EnableInterrupts();       // Enable interrupts

  // test_main();  // un-comment to run decoder, decoder streaming, and display test mains

  while(1) {
      WaitForInterrupt();
  }
}

//Test to check ADC software
//Displays values that the ADC and displays them in 1s and 0s
void ADC_TestMain(void) {
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
    }
}

void test_main(void) {
    // try to comment out tests and only run one at a time

//    Decoder_TestMain();
//    DecoderStreaming_TestMain();
//    Display_TestMain();
    // ADC_TestMain();  // un-comment to run ADC_TestMain
}




