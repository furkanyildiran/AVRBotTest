#include "stepper.h"
#include <string.h>
#include <stdio.h>

#define PI										3.14159f
#define RadiusOfWheel							3.5f								
#define RadiusOfVehicle							9.5f								
#define CircumferenceOfWheel					(float)(2*PI*RadiusOfWheel)			
#define CircumferenceOfVehicle					(float)(2*PI*RadiusOfVehicle)			
#define CalculateArcLength(degree, radius)		(float)((2.0*PI*radius*degree)/360)
/*per 64 pulse is 5.625 degrees*/
#define DegressPer64Pulse						5.625f
#define PulsePer5degress625						64.0f
#define DistancePer64Pulse						(float)(CalculateArcLength(DegressPer64Pulse, RadiusOfWheel))				

#define STEP_PULSE_DELAY			10
#define OCR0A_MIN_VAL				36			/*top speed 844Hz*/
#define OCR0A_MAX_VAL				120			/*lower speed 258Hz*/
#define DIFF_OCROA_MINMAX			(OCR0A_MAX_VAL-OCR0A_MIN_VAL)
#define TIMER0_COMPA_INT_DSBL()		(TIMSK0 &=~(1 << OCIE0A))
#define TIMER0_COMPA_INT_EN()		(TIMSK0 |= (1 << OCIE0A))
#define CLEAR_COUNTERS()			do{pulseCounter=0; targetPulse=0;}while(0)

static volatile uint32_t pulseCounter, targetPulse;
static volatile SPEED_STATE_t speed_state = ACCELARATION;
static volatile MOVEMENT_FLAG_t movement_flag = NOT_MOVED;

ISR(TIMER0_COMPA_vect){
	STEP_PULSE();
	pulseCounter++;
	switch(speed_state){
		case ACCELARATION:
			if (!(pulseCounter%STEP_PULSE_DELAY) && (OCR0A > OCR0A_MIN_VAL))
			OCR0A--;
			else if(OCR0A==OCR0A_MIN_VAL)
			speed_state=CONSTANT_SPEED;
			break;
		case CONSTANT_SPEED:
			if(pulseCounter >= (targetPulse-STEP_PULSE_DELAY*DIFF_OCROA_MINMAX))
			speed_state=DECELARATION;
			break;
		case DECELARATION:
			if((pulseCounter%STEP_PULSE_DELAY)==0 && (OCR0A < OCR0A_MAX_VAL))
				OCR0A++;
			else if(OCR0A==OCR0A_MAX_VAL){
				TIMER0_COMPA_INT_DSBL();
				CHIP_SLEEP();
				CLEAR_COUNTERS();
				speed_state=ACCELARATION;
				movement_flag=MOVED;
			}
			break;
		default:break;
	}
}

void A4988_init(void){
	GPIO_SET_REG(R_A4988_DDR, R_DDR_VAL);
	GPIO_SET_REG(L_A4988_DDR, L_DDR_VAL);
	GPIO_SET_REG(R_MS1_and_MS2_DDR, (R_MS1_pin | R_MS2_pin));
	GPIO_SET_REG(R_MS3_DDR, R_MS3_pin);
	GPIO_SET_REG(L_MS1_and_MS2_DDR, (L_MS1_pin | L_MS2_pin));
	GPIO_SET_REG(L_MS3_DDR, L_MS3_pin);
	TCCR0A = TIMER0_CTC_MODE;
	TCCR0B = TIMER0_PRESCALER_256;
	OCR0A = OCR0A_MAX_VAL;/*lowest speed*/	
}
void A4988_forward(uint16_t distance){
	movement_flag=NOT_MOVED;
	CHIP_ACTIVE_FUNC();
	GPIO_CLEAR_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_CLEAR_PIN(L_A4988_PORT, L_dir_pin);
	float ratio = (float)(distance/DistancePer64Pulse);
	targetPulse = (uint32_t)round(ratio*PulsePer5degress625);
	TIMER0_COMPA_INT_EN();
}
void A4988_backward(uint16_t distance){
	movement_flag=NOT_MOVED;
	CHIP_ACTIVE_FUNC();
	GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);
	float ratio = (float)(distance/DistancePer64Pulse);
	targetPulse = (uint32_t)round(ratio*PulsePer5degress625);
	TIMER0_COMPA_INT_EN();
}
void A4988_left(uint16_t degree){
	movement_flag=NOT_MOVED;
	CHIP_ACTIVE_FUNC();
	GPIO_CLEAR_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);
	float distance = (float)CalculateArcLength(degree,RadiusOfVehicle);
	float ratio = (float)(distance/DistancePer64Pulse);
	targetPulse = (uint32_t)round(ratio*PulsePer5degress625);
	TIMER0_COMPA_INT_EN();
}
void A4988_right(uint16_t degree){
	movement_flag=NOT_MOVED;
	CHIP_ACTIVE_FUNC();
	GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_CLEAR_PIN(L_A4988_PORT, L_dir_pin);
	float distance = (float)CalculateArcLength(degree,RadiusOfVehicle);
	float ratio = (float)(distance/DistancePer64Pulse);
	targetPulse = (uint32_t)round(ratio*PulsePer5degress625);
	TIMER0_COMPA_INT_EN();
}

void A4988_stop(void){
	speed_state = DECELARATION;
}

uint16_t A4988_getDistance(void){
	return ((pulseCounter/PulsePer5degress625)*DistancePer64Pulse);
}

MOVEMENT_FLAG_t A4988_movementControl(void){
	return movement_flag;
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
	temp = L_MS1_and_MS2_PORT;
	temp = MS1andMS2_maskVal | (((ms>>1)&1)<<L_MS2_pin) | ((ms&1)<<L_MS1_pin);
	L_MS1_and_MS2_PORT = temp;
}

