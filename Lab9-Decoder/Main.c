#include "Main.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Raw, SIZE, char, SUCCESS, FAIL)
char recovered_String[SIZE];
char recovered_Word[20];
int read_words = 0;
char string[20];  // global to assist in debugging



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

void printWord(void){
    int end_flag = 1;
    while(end_flag){
        static int i = 0;
        char read_char = 0;
        RawFifo_Get(&read_char);
        UART_OutChar(read_char);
        recovered_Word[i] = read_char;
        i++;
        if(read_char == 0){
            end_flag = 0;
        }
    }
}

void readUART(void){
    UART_OutString("InString: ");
    UART_InString(string,19);

    // Store string in FIFO buffer
    int j = 0;
    while(string[j] != 0){
        RawFifo_Put(string[j]);
        j++;
    }
    RawFifo_Put(0);
    read_words++;
    OutCRLF();
}

void Transmitter_output_fifo_task(void) {
    if (RawFifo_Size() > 0) {
        char output_char = 0;
        RawFifo_Get(&output_char);
        Transmitter_set_outchar_vector((uint8_t) output_char);
    }
}

//debug code
int main(void){
  PLL_Init(Bus80MHz);       // set system clock to 50 MHz
  UART_Init();              // initialize UART
  UART_OutString(" UART0 is ready to use!"); OutCRLF();
  EnableInterrupts();       // Enable interrupts
  RawFifo_Init();

  // Initialize a timer that sends 1 packet to DAC.
  Transmitter_Init(&Transmitter_output_fifo_task);

  while(1){
      if(RawFifo_Size() < SIZE){
          readUART();
      } else {
          UART_OutString("The UART Buffer is full, please wait \n");
      }
  }

}

