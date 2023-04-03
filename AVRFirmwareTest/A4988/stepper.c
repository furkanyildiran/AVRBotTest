#include "stepper.h"
#define A4988_TASK_DELAY 10
static Directions_t current_dir=STOP, previous_dir=STOP;

static void forward(void);
static void backward(void);
static void right(void);
static void left(void);
static void stop(void);
static void setDirection(void);
void A4988_task(void);


ISR(TIMER0_COMPA_vect){
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
	TCCR0B = TIMER0_PRESCALER_256;
	TIMSK0 |= TIMER0_INT_ENBL;
	A4988_SPEED_LEVEL8();
	Task_add(A4988_task);
}
void A4988_stop(void){current_dir = STOP;}
void A4988_forward(void){current_dir = FORWARD;}
void A4988_backward(void){current_dir = BACKWARD;}
void A4988_left(void){current_dir = LEFT;}
void A4988_right(void){current_dir = RIGHT;}

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
	previous_dir = FORWARD;
}
static void backward(void){
	CHIP_ACTIVE_FUNC();
	GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);
	previous_dir = BACKWARD;
}
static void right(void){
	CHIP_ACTIVE_FUNC();
	GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_CLEAR_PIN(L_A4988_PORT, L_dir_pin);
	previous_dir = RIGHT;
}
static void left(void){
	CHIP_ACTIVE_FUNC();
	GPIO_CLEAR_PIN(R_A4988_PORT, R_dir_pin);
	GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);
	previous_dir = LEFT;
}
static void stop(void){
	CHIP_SLEEP();
	previous_dir=STOP;
}
static void setDirection(void){
	switch(current_dir)
	{
		case FORWARD:forward();break;
		case  BACKWARD:backward();break;
		case LEFT:left();break;
		case RIGHT:right();break;
		case STOP:stop();break;
		default:break;
	}
}
void A4988_task(void){
	if((getMs()%A4988_TASK_DELAY)==0)
	{
		if(current_dir!=previous_dir)
		{
			if(OCR0A<120) OCR0A++;
			else setDirection();
		}
		else if(OCR0A>36)OCR0A--;
	}
}