#ifndef STEPPER_H_
#define STEPPER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <util/atomic.h>
#include "stepper_config.h"
#include "gpio_custom.h"
#include "pcd8544.h"

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
	
#define MS1andMS2_maskVal	0b01011111

typedef enum{
	ACCELARATION,
	CONSTANT_SPEED,
	DECELARATION
}SPEED_STATE_t;

typedef enum{
	NOT_MOVED,
	MOVED
}MOVEMENT_FLAG_t;

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
void A4988_forward(uint16_t distance);
void A4988_backward(uint16_t distance);
void A4988_left(uint16_t degree);
void A4988_right(uint16_t degree);
MOVEMENT_FLAG_t A4988_movementControl(void);
void A4988_setSpeed();
void A4988_setMs(MicroStep_t ms);
void A4988_task(void);
	
#endif /* STEPPER_H_ */