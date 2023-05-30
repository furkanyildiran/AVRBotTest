#include "hcsr04.h"

void HCSR04_init(void){
	HCSR04_DDR |= (1 << HCSR04_TRIG_PIN);
	HCSR04_DDR &= ~(1 << HCSR04_ECHO_PIN);
}

__attribute__((noinline))uint16_t HCSR04_measure(void){
	uint32_t loop_counter=0;
	while(ECHO_PIN_CONTROL());
	TRIG_PULSE();
	while(!ECHO_PIN_CONTROL());
	while(ECHO_PIN_CONTROL()){
		loop_counter++;
		if(loop_counter > 28000){
			loop_counter=0;
			break;
		}
	}
	uint32_t command_num = (loop_counter*15)+19;
	uint16_t dist = (uint16_t)(command_num*ConstantForDist);
	return dist;
}
