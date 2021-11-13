#include "Main.h"

#define SIZE 1024
#define SUCCESS 1
#define FAIL 0

AddPointerFifo(Raw, SIZE, char, SUCCESS, FAIL)
extern volatile uint16_t outchar_frame;
char recovered_String[SIZE];
char recovered_Word[20];
int read_words = 0;
char string[20];  // global to assist in debugging



//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void) {
  UART_OutChar(CR);
  UART_OutChar(LF);
}

void printBuffer(void) {
    while(RawFifo_Size() != 0) {
        static int i = 0;
        char read_char = 0;
        RawFifo_Get(&read_char);
        UART_OutChar(read_char);
        recovered_String[i] = read_char;
        i++;
    }
}

void printWord(void) {
    int end_flag = 1;
    while(end_flag) {
        static int i = 0;
        char read_char = 0;
        RawFifo_Get(&read_char);
        UART_OutChar(read_char);
        recovered_Word[i] = read_char;
        i++;
        if(read_char == 0) {
            end_flag = 0;
        }
    }
}

uint16_t fifo_size = 0;

void readUART(void) {
    UART_OutString("InString: ");
    UART_InString(string,19);

    // Store string in FIFO buffer
    int j = 0;
    while(string[j] != 0) {
        RawFifo_Put(string[j]);
        fifo_size++;
        j++;
    }
    RawFifo_Put(0);
    fifo_size++;
    read_words++;
    OutCRLF();
}

void printBitVector(uint16_t vector) {
    uint8_t z = 0;
    for (z = 11; z >= 1; z--) {
        UART_OutUDec((vector & 0x0400) >> 10);
        vector = vector << 1;
    }
    UART_OutChar('\r');
    UART_OutChar('\n');
}

void Transmitter_output_fifo_task(void) {
    if (fifo_size > 0) {
        char output_char = 0;
        RawFifo_Get(&output_char);
        fifo_size--;
        Transmitter_set_outchar_vector((uint8_t) output_char);
    }
}

//debug code
int main(void) {
  PLL_Init(Bus80MHz);       // set system clock to 50 MHz
  DisableInterrupts();
  UART_Init();              // initialize UART
  UART_OutString(" UART0 is ready to use!"); OutCRLF();
  EnableInterrupts();       // Enable interrupts
  RawFifo_Init();

//  test_main();  // un-comment to run input, encoder streaming, encoder, dac, dac streaming, and end-to-end test mains


  // main program, same as e2e test
  // Initialize a timer that sends 1 packet to DAC.
  Transmitter_Init(&Transmitter_output_fifo_task, 0);
  EnableInterrupts();       // Enable interrupts

  while(1) {
      if(RawFifo_Size() < SIZE) {
          readUART();
      } else {
          UART_OutString("The UART Buffer is full, please wait \n");
      }
  }

}

void Input_TestMain(void){

    //To test input, we want to input something and see that we stored it
    UART_OutString("InString: ");
    UART_InString(string,19);
    UART_OutChar('\r');
    UART_OutChar('\n');
    UART_OutString(string);
    UART_OutChar('\r');
    UART_OutChar('\n');
}



char testString[] = "hello";
//Test ADC -> Decoder and make sure data is streamed properly (Test Main 10)
void Transmitter_Streaming_TestMain(void) {

    UART_OutString("Test String: ");
    UART_OutString(testString);
    UART_OutChar('\r');
    UART_OutChar('\n');

    //RawFifo_Init();
    //This is to test our fifo (put stuff in and get stuff out is our streaming?)
    int i = 0;
    //Put our test values into the fifo
    for(i = 0; i < 6; i++){
        RawFifo_Put(testString[i]);
        fifo_size++;
    }
    uint8_t val = 0;
    for(i = 0; i < fifo_size; i++){
        RawFifo_Get(&val);
        UART_OutString("Fifo In was ");
        UART_OutUDec(testString[i]);
        UART_OutChar('=');
        UART_OutChar(testString[i]);
        UART_OutString(", Fifo out was ");
        UART_OutUDec(val);
        UART_OutChar('=');
        UART_OutChar(val);
        UART_OutChar('\r');
        UART_OutChar('\n');
    }
}

void Transmitter_Encoder_TestMain(void) {
     int i = 0;
     //Put our test values into the encoder
     for(i = 0; i < 6; i++){
         UART_OutChar(testString[i]);
         UART_OutChar('=');
         Transmitter_set_outchar_vector(testString[i]);
         printBitVector(outchar_frame);
     }
     //Verify that it was properly debugged via UART
 }

char testString2[] = "hi";
void Transmitter_DACStreaming_TestMain(void) {
    Transmitter_Init(&Transmitter_output_fifo_task, 0);
    EnableInterrupts();       // Enable interrupts

    UART_OutString("Test String 2: ");
    UART_OutString(testString2);
    UART_OutChar('\r');
    UART_OutChar('\n');

    //RawFifo_Init();
    //This is to test our fifo (put stuff in and get stuff out is our streaming?)
    int i = 0;
    //Put our test values into the fifo
    for(i = 0; i < 3; i++){
        RawFifo_Put(testString2[i]);
        fifo_size++;
    }

    // allow timer to call Transmitter_output_fifo_task(); and verify audio output

}


void Transmitter_DAC_TestMain(void) {
    Transmitter_Init(&Transmitter_output_fifo_task, 1);
    EnableInterrupts();       // Enable interrupts
}

// run the system normally and verify via UART and audio
void Transmitter_E2E_TestMain(void) {
      Transmitter_Init(&Transmitter_output_fifo_task, 0);
      EnableInterrupts();       // Enable interrupts
}

void test_main() {
    // try to comment out tests and only run one at a time

//    Input_TestMain();
//    Transmitter_Streaming_TestMain();
//    Transmitter_Encoder_TestMain();
//    Transmitter_DAC_TestMain();
    Transmitter_E2E_TestMain();
//    Transmitter_DACStreaming_TestMain(); // un-comment to run Transmitter_DACStreaming_TestMain
}
