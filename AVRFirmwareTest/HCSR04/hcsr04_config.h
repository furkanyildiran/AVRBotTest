/*
 * hcsr04_config.h
 *
 * Created: 30.05.2023 23:38:54
 *  Author: MONSTER
 */ 

#ifdef __cplusplus
extern "C"{
#endif	
#ifndef __HCSR04_CONFIG_H__
#define __HCSR04_CONFIG_H__
#define F_CPU 16000000UL
#include "gpio_custom.h"
#include <util/delay.h>

#define ConstantForDist		0.0010725
#define HCSR04_DDR			GPIO_DDRL_U.reg
#define HCSR04_PORT			GPIO_PORTL_U.reg
#define HCSR04_PIN			GPIO_PINL_U.reg
#define HCSR04_TRIG_PIN		GPIO_PIN2
#define HCSR04_ECHO_PIN		GPIO_PIN4
#define TRIG_PIN_HIGH()		(HCSR04_PORT |=  (1 << HCSR04_TRIG_PIN))
#define TRIG_PIN_LOW()		(HCSR04_PORT &= ~(1 << HCSR04_TRIG_PIN))
#define TRIG_PULSE()		do{TRIG_PIN_HIGH(); _delay_us(10); TRIG_PIN_LOW();}while(0)
#define ECHO_PIN_CONTROL()	(HCSR04_PIN  &	 (1 << HCSR04_ECHO_PIN))

#endif /* HCSR04_CONFIG_H_ */
#ifdef __cplusplus
}
#endif