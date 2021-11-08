#include <stdint.h>
#include "../inc/PLL.h"
#include "../inc/CortexM.h"
#include "../inc/UART0int.h"
#include "../inc/FIFO.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Raw, SIZE, char, SUCCESS, FAIL)
char recovered_String[SIZE];

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}

void printBuffer(void){
    while(RawFifo_Size() != 0){
        static int i = 0;
        char read_char = 0;
        RawFifo_Get(&read_char);
        UART_OutChar(read_char);
        recovered_String[i] = read_char;
        i++;
    }
}

//debug code
int main(void){
  PLL_Init(Bus80MHz);       // set system clock to 50 MHz
  UART_Init();              // initialize UART
  UART_OutString(" UART0 is ready to use!"); OutCRLF();
  EnableInterrupts();       // Enable interrupts
  RawFifo_Init();
  int read_words = 0;

  char string[20];  // global to assist in debugging

  while(1){
      if(read_words < 5){

          UART_OutString("InString: ");
          UART_InString(string,19);

          // Store string in FIFO buffer
          int j = 0;
          while(string[j] != 0){
              int check = RawFifo_Put(string[j]);
              j++;
              UART_OutUDec(check);
          }
          RawFifo_Put(0);
          read_words++;
          OutCRLF();


      } else {
          printBuffer();
      }
  }

}

