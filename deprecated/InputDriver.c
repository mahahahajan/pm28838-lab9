#include "InputDriver.h"
#include "SwitchDriver.h"

uint16_t values[100];
uint8_t valIndex = -1;

//Currently Assuming Switch input, not keyboard input
//1
//Test Input Task (use Switch Driver? or Keyboard)
int InputMain(void){
	valIndex = 0;
	Switches_Init();
	uint8_t oldVal = 0;
	// TODO: Modify Switch Driver to return certain values to shared array / fifo queue
	while(1) {
		int tempVal = -1;
		if(oldVal != valIndex){
				for(int i = 0; i < 101; i++){
					tempVal = values[i]; // see what values are there
				}
		}
		oldVal = valIndex;
	}
}
	
//2
// Test Streaming to Encoder
int StreamMain(void){
	//Don't really need this one beccause we are going to extern the values array
	return 1;
}