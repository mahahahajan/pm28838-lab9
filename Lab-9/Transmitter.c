#include "Transmitter.h"


volatile uint8_t outchar_vector = 0;
volatile uint8_t outchar_vector_ptr = 0;
volatile uint8_t outchar_vector_bit = 0;
volatile long currDuration = 0;
volatile uint16_t I = 0;

const unsigned short SinWave[64] = {
  2048,2409,2756,3076,3356,3586,3757,3862,3898,3862,3757,
  3586,3356,3076,2756,2409,2048,1687,1340,1020,740,510,
  339,234,198,234,339,510,740,1020,1340,1687,
  2048,2409,2756,3076,3356,3586,3757,3862,3898,3862,
  3757,3586,3356,3076,2756,2409,2048,1687,1340,1020,740,510,339,234,198,
  234,339,510,740,1020,1340,1687
};

void (*Transmitter_fifo_task)(void);

void Transmitter_Init(void(*fifo_task)(void)) {
    DAC_Init(0);
    Transmitter_fifo_task = fifo_task;
    currDuration = DEFAULT_LENGTH;
    I = 0;
    outchar_vector = 0;
    outchar_vector_ptr = 0;
    outchar_vector_bit = 0;
    Timer_InitTask2(&Transmitter_output_handler, HIGH_FREQ);
}

// timer handler
void Transmitter_output_handler(void) {
  if (currDuration > 0) {
      DAC_Out(SinWave[I]);
      I++;
      if (I >= 64) I = 0;
      currDuration--;
  } else {
      if (outchar_vector_ptr > 0) {
          outchar_vector_bit = (outchar_vector | 0x0001);
          currDuration = DEFAULT_LENGTH;
          outchar_vector = outchar_vector >> 1;
          outchar_vector_ptr--;
      } else {
          DAC_Out(0);
          Transmitter_fifo_task();
      }
  }
}

void Transmitter_set_outchar_vector(uint8_t vector) {
    outchar_vector = vector;
    outchar_vector_ptr = 8;
}
