#include "Transmitter.h"


volatile uint8_t outchar_vector = 0;
volatile uint16_t outchar_frame = 0;
volatile uint8_t outchar_frame_ptr = 0;
volatile uint8_t outchar_frame_bit = 0;
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
    DAC_Init(DAC_OUT_STEADY);
    Transmitter_fifo_task = fifo_task;
    currDuration = 0;
    I = 0;
    outchar_vector = 0;
    outchar_frame_ptr = 0;
    outchar_frame_bit = 0;
    outchar_frame = 0;
    Timer_InitTask2(&Transmitter_output_handler, HIGH_FREQ);
}

// parity utility function
int getParity(unsigned int n){
    int parity = 0;
    while (n){
        parity = !parity;
        n = n & (n - 1);
    }
    return parity;
}

// timer handler
void Transmitter_output_handler(void) {
  if (currDuration > 0) {
      if (outchar_frame_bit == 0x01) {
          DAC_Out(SinWave[I]);
          I++;
          if (I >= 64) I = 0;
      } else DAC_Out(DAC_OUT_STEADY);
      currDuration--;
  } else {
      // currDuration = 0 --> steady state
      if (outchar_frame_ptr > 0) {
          outchar_frame_bit = (outchar_frame & 0x0001);
          currDuration = DEFAULT_LENGTH;
          outchar_frame = outchar_frame >> 1;
          outchar_frame_ptr--;
      } else {
          // outchar_frame_ptr = 0 --> steady state
          DAC_Out(DAC_OUT_STEADY);
          Transmitter_fifo_task();
      }
  }
}

void Transmitter_set_outchar_vector(uint8_t vector) {
    outchar_vector = vector;
    uint8_t parity_bit = (0x0001) & (getParity(outchar_vector));
    outchar_frame = 0;
    outchar_frame = (1 << 10) | (vector << 2) | (parity_bit << 1) | (1 << 0);
    outchar_frame_ptr = 11;
}
