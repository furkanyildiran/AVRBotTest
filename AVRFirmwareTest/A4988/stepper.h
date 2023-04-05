#ifndef STEPPER_H_
#define STEPPER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "stepper_config.h"
#include "gpio_custom.h"
#include "task.h"

#define A4988_490_Hz 255
#define A4988_555_Hz 225	//1.8ms period
#define A4988_588_Hz 211	//1.7ms period
#define A4988_625_Hz 199	//1.6ms period
#define A4988_666_Hz 187	//1.5ms period
#define A4988_714_Hz 174	//1.4ms period
#define A4988_771_Hz 161
#define A4988_833_Hz 149

//wheel
#define Circumference 22 //cm
#define radius 3.5
//vehicle
//60cm
//9.5 cm


#define A4988_SPEED_LEVEL1() do{OCR0A = A4988_490_Hz;}while(0)
#define A4988_SPEED_LEVEL2() do{OCR0A = A4988_555_Hz;}while(0)
#define A4988_SPEED_LEVEL3() do{OCR0A = A4988_588_Hz;}while(0)
#define A4988_SPEED_LEVEL4() do{OCR0A = A4988_625_Hz;}while(0)
#define A4988_SPEED_LEVEL5() do{OCR0A = A4988_666_Hz;}while(0)
#define A4988_SPEED_LEVEL6() do{OCR0A = A4988_714_Hz;}while(0)
#define A4988_SPEED_LEVEL7() do{OCR0A = A4988_771_Hz;}while(0)
#define A4988_SPEED_LEVEL8() do{OCR0A = A4988_833_Hz;}while(0)	

#define R_DDR_VAL			((1 << R_dir_pin)|(1 << R_sleep_pin)|(1 << R_step_pin))
#define L_DDR_VAL			((1 << L_dir_pin)|(1 << L_sleep_pin)|(1 << L_step_pin))

/*Timer0 settings for step pulse*/
#define TIMER0_CTC_MODE			(1 << WGM01)
#define TIMER0_PRESCALER_64		((1 << CS02) | (1 << CS00))
#define TIMER0_PRESCALER_256	(1 << CS02)
#define TIMER0_INT_ENBL			(1 << OCIE0A)

#define R_ON()	(GPIO_SET_PIN(R_A4988_PORT, R_sleep_pin))
#define R_OFF() (GPIO_CLEAR_PIN(R_A4988_PORT, R_sleep_pin))
#define L_ON()	(GPIO_SET_PIN(L_A4988_PORT, L_sleep_pin))
#define L_OFF() (GPIO_CLEAR_PIN(L_A4988_PORT, L_sleep_pin))

#define STEP_PULSE()		do{R_A4988_PORT ^= (1 << R_step_pin); L_A4988_PORT ^= (1 << L_step_pin);}while(0)
#define CHIP_SLEEP()		do{R_OFF(); L_OFF();}while(0)
#define CHIP_ACTIVE_FUNC()	do{R_ON(); L_ON();}while(0)

/*
#define FORWARD_DIRECTION()		do{CHIP_ACTIVE_FUNC(); GPIO_CLEAR_PIN(R_A4988_PORT, R_dir_pin); GPIO_CLEAR_PIN(L_A4988_PORT, L_dir_pin);}while(0)
#define BACKWARD_DIRECTION()	do{CHIP_ACTIVE_FUNC(); GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);   GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);}while(0)
#define RIGHT_DIRECTION()		do{CHIP_ACTIVE_FUNC(); GPIO_SET_PIN(R_A4988_PORT, R_dir_pin);   GPIO_CLEAR_PIN(L_A4988_PORT, L_dir_pin);}while(0)
#define LEFT_DIRECTION()		do{CHIP_ACTIVE_FUNC(); GPIO_CLEAR_PIN(R_A4988_PORT, R_dir_pin); GPIO_SET_PIN(L_A4988_PORT, L_dir_pin);}while(0)
#define	STOP_DIRECTION()		do{CHIP_SLEEP();}while(0)*/
	
#define MS1andMS2_maskVal	0b01011111

typedef enum{
	STOP,
	FORWARD,
	LEFT,
	RIGHT,
	BACKWARD
}Directions_t;

typedef enum{
	MS0,
	MS1,
	MS2,
	MS3,
	MS4,
	MS5,
	MS6,
	MS7	
}MicroStep_t;

typedef enum{
	FULL,
	HALF,
	LOW
}SPEED_t;


void A4988_init(void);
void A4988_forward(uint8_t distance);
void A4988_backward(void);
void A4988_left(void);
void A4988_right(void);
void A4988_stop();
void A4988_setSpeed();
void A4988_setMs(MicroStep_t ms);
void A4988_task(void);
	
#endif /* STEPPER_H_ */