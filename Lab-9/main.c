#include <stdint.h>
#include "../inc/PLL.h"
#include "../inc/CortexM.h"
#include "../inc/UART0int.h"
#include "../inc/FIFO.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Raw, SIZE, char, SUCCESS, FAIL)

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}
//debug code
int main(void){
  PLL_Init(Bus80MHz);       // set system clock to 50 MHz
  UART_Init();              // initialize UART
  UART_OutString(" UART0 is ready to use!"); OutCRLF();
  EnableInterrupts();       // Enable interrupts
  RawFifo_Init();

  char string[20];  // global to assist in debugging
  char recovered_String[20*5];

  int i;
  for(i = 0; i < 5; i++){
      UART_OutString("InString: ");
          UART_InString(string,19);
          UART_OutString(" OutString="); UART_OutString(string);OutCRLF();

          // Store string in FIFO buffer
          int j = 0;
          while(string[j] != 0){
              RawFifo_Put(string[j]);
              j++;
          }
          RawFifo_Put(0);
  }

  while(RawFifo_Size() != 0){
      static int i = 0;
      char read_char = 0;
      RawFifo_Get(&read_char);
      UART_OutChar(read_char);
      recovered_String[i] = read_char;
      i++;
  }

  while(1){

  }

  // Print out contents of FIFO buffer;

  /*
  while(1){
    // Input user data
    UART_OutString("InString: ");
    UART_InString(string,19);
    UART_OutString(" OutString="); UART_OutString(string); OutCRLF();

    // Store string in FIFO buffer

  }
  */
}

