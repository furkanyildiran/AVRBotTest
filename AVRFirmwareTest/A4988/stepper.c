#include "stepper.h"
#define MS1andMS2_maskVal	0b01011111
static volatile uint8_t direction = 0;

ISR(TIMER0_COMPA_vect){
	switch(direction){
		case FORWARD:
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
	GPIO_SET_REG(R_A4988_DDR, R_DDR_VAL);
	GPIO_SET_REG(L_A4988_DDR, L_DDR_VAL);
	GPIO_SET_REG(R_MS1_and_MS2_DDR, (R_MS1_pin | R_MS2_pin));
	GPIO_SET_REG(R_MS3_DDR, R_MS3_pin);
	GPIO_SET_REG(L_MS1_and_MS2_DDR, (L_MS1_pin | L_MS2_pin));
	GPIO_SET_REG(L_MS3_DDR, L_MS3_pin);
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

void A4988_setMs(MicroStep_t ms){
	if(ms<MS4){
		GPIO_CLEAR_PIN(L_MS3_PORT, L_MS3_pin);
		GPIO_CLEAR_PIN(R_MS3_PORT, R_MS3_pin);
	}else{
		GPIO_SET_PIN(L_MS3_PORT, L_MS3_pin);
		GPIO_SET_PIN(R_MS3_PORT, R_MS3_pin);
	}
	uint8_t temp = R_MS1_and_MS2_PORT;
	temp = MS1andMS2_maskVal | (((ms>>1)&1)<<R_MS2_pin) | ((ms&1)<<R_MS1_pin);
	R_MS1_and_MS2_PORT = temp;
	L_MS1_and_MS2_PORT = temp;
}