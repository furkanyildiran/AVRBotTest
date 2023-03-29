#ifndef STEPPER_CONFIG_H_
#define STEPPER_CONFIG_H_
#include "stepper_config.h"
#include "gpio_custom.h"

#define L_A4988_DDR		GPIO_DDRC
#define L_A4988_PORT	GPIO_PORTC
#define L_step_pin		GPIO_PIN2
#define L_dir_pin		GPIO_PIN0
#define L_sleep_pin		GPIO_PIN4
#define L_MS1			GPIO_PIN5//GPIOA
#define L_MS2			GPIO_PIN7//GPIOA
#define L_MS3			GPIO_PIN6//GPIOC

#define R_A4988_DDR		GPIO_DDRA
#define R_A4988_PORT	GPIO_PORTA
#define R_step_pin		GPIO_PIN2
#define R_dir_pin		GPIO_PIN0
#define R_sleep_pin		GPIO_PIN4
#define R_MS1			GPIO_PIN5//GPIOC
#define R_MS2			GPIO_PIN7//GPIOC
#define R_MS3			GPIO_PIN6//GPIOA

#endif /* STEPPER_CONFİG_H_ */