#include "Encoder.h"


extern uint16_t values[100];
extern uint8_t valIndex;

uint16_t encodedVals[100];

uint16_t EncodeValue(uint16_t value){
	//TODO: Encoding Scheme
	return value;
}

//3
// Test Encoding 
int EncoderMain(void) {
	for(int i = 0; i < valIndex; i++){
		encodedVals[i] = EncodeValue(values[i]);
	}
}	