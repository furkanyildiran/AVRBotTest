#include "stepper.h"
#include "pcd8544.h"
#include <stdio.h>
#include <math.h>
#define A4988_TASK_DELAY 10
#define CM_PER_64PULSE	0.3434375
static Directions_t current_dir=STOP, previous_dir=STOP;

static void forward(void);
static void backward(void);
static void right(void);
static void left(void);
static void stop(void);
static void setDirection(void);
void A4988_task(void);

volatile uint32_t pulseCounter, targetPulse;
typedef enum{
	State1,
	State2,
	State3	
}states;
states state = State1;
char data[20]={"\0"};
ISR(TIMER0_COMPA_vect){
	STEP_PULSE();
	pulseCounter++;

	if(state==State1){
		if ((pulseCounter%10)==0 && (OCR0A > 36)){
			OCR0A--;
		}else if(OCR0A==36){
			state=State2;
			sprintf(data,"%ld",pulseCounter);
			PCD_text(data,0,LINE_0);
		}
	}
	else if(state==State2){
		if(pulseCounter >= (targetPulse-10*84))state=State3;
	}
	else if(state==State3){
		if((pulseCounter%10)==0 && (OCR0A < 120)){
			OCR0A++;
		}else if(OCR0A==120){
			TIMSK0 &= ~(1 << OCIE0A);
			CHIP_SLEEP();
			targetPulse = 0;
			pulseCounter = 0;
		}
	}
}
uint32_t A4988_getTargetPulseCounter(void){
	return targetPulse;
}
uint32_t A4988_getPulse(void){
	uint32_t temp=0; 
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		temp = pulseCounter;
	}
	return temp;
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
	
	A4988_SPEED_LEVEL8();
	Task_add(A4988_task);
}
void A4988_stop(void){
	CHIP_SLEEP();
}
void A4988_forward(uint8_t distance){
	CHIP_ACTIVE_FUNC();
	float ratio = (float)(distance/CM_PER_64PULSE);
	targetPulse = (uint32_t)round(ratio*64);
	current_dir = FORWARD;
	pulseCounter=0;
	TIMSK0 |= TIMER0_INT_ENBL;
}
void A4988_backward(void){
	
}
void A4988_left(void){
	
}
void A4988_right(void){
	
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

static void forward(void){
	CHIP_ACTIVE_FUNC();
	GPIO_CLEAR_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_CLEAR_PIN(L_A4988_PORT, L_dir_pin);
}
static void backward(void){
	CHIP_ACTIVE_FUNC();
	GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);
}
static void right(void){
	CHIP_ACTIVE_FUNC();
	GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_CLEAR_PIN(L_A4988_PORT, L_dir_pin);
}
static void left(void){
	CHIP_ACTIVE_FUNC();
	GPIO_CLEAR_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);
}
static void stop(void){
	
}
