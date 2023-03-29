#ifndef STEPPER_H_
#define STEPPER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "stepper_config.h"
#include "gpio_custom.h"

#define A4988_555_Hz 225	//1.8ms period
#define A4988_588_Hz 211	//1.7ms period
#define A4988_625_Hz 199	//1.6ms period
#define A4988_666_Hz 187	//1.5ms period
#define A4988_714_Hz 174	//1.4ms period

typedef enum{
	STOP,
	FORWARD,
	LEFT,
	RIGHT,
	BACKWARD
}Directions_t;

typedef enum{
	FULL,
	HAL,
	MC	
}MicroStep_t;

typedef enum{
	FULL,
	HALF,
	LOW
}SPEED_t;
	
void A4988_init(void);
void A4988_forward(void);
void A4988_backward(void);
void A4988_left(void);
void A4988_right(void);
void A4988_stop();
void A4988_setSpeed();
	
#endif /* STEPPER_H_ */