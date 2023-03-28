#include "stepper.h"

static volatile uint8_t direction = 0;
extern uint8_t counter;
ISR(TIMER0_COMPA_vect){
	switch(direction){
		case FORWARD:
		counter++;
		FORWARD_DIRECTION();
		break;
		case  BACKWARD:
		BACKWARD_DIRECTION();
		break;
		case LEFT:
		LEFT_DIRECTION();
		break;
		case RIGHT:
		RIGHT_DIRECTION();
		break;
		case STOP:
		STOP_DIRECTION();
		break;
	}
	if(direction!=STOP)
		STEP_PULSE();
}

void A4988_init(void){
	R_SET_PINS_OUTPUT();
	L_SET_PINS_OUTPUT();
	TCCR0A = TIMER0_CTC_MODE;
	TCCR0B = TIMER0_PRESCALER_64;
	TIMSK0 |= TIMER0_INT_ENBL;
	A4988_SPEED_LEVEL5();
}
void A4988_stop(void){
	CHIP_SLEEP();
	direction = STOP;
}
void A4988_forward(void){
	direction = FORWARD;
}
void A4988_backward(void){
	direction = BACKWARD;
}
void A4988_left(void){
	direction = LEFT;
}
void A4988_right(void){
	direction = RIGHT;
}