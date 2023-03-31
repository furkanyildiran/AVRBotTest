#ifndef STEPPER_CONFIG_H_
#define STEPPER_CONFIG_H_
#include "stepper_config.h"
#include "gpio_custom.h"

#define L_A4988_DDR				GPIO_DDRC_U.reg
#define L_A4988_PORT			GPIO_PORTC_U.reg
#define L_step_pin				GPIO_PIN2
#define L_dir_pin				GPIO_PIN0
#define L_sleep_pin				GPIO_PIN4
#define L_MS1_and_MS2_DDR		GPIO_DDRA_U.reg
#define L_MS1_and_MS2_PORT		GPIO_PORTA_U.reg
#define L_MS3_DDR				GPIO_DDRC_U.reg
#define L_MS3_PORT				GPIO_PORTC_U.reg
#define L_MS1_pin				GPIO_PIN5//GPIOA
#define L_MS2_pin				GPIO_PIN7//GPIOA
#define L_MS3_pin				GPIO_PIN6//GPIOC

#define R_A4988_DDR				GPIO_DDRA_U.reg
#define R_A4988_PORT			GPIO_PORTA_U.reg
#define R_step_pin				GPIO_PIN2
#define R_dir_pin				GPIO_PIN0
#define R_sleep_pin				GPIO_PIN4

#define R_MS1_and_MS2_DDR		GPIO_DDRC_U.reg
#define R_MS1_and_MS2_PORT		GPIO_PORTC_U.reg
#define R_MS3_DDR				GPIO_DDRA_U.reg
#define R_MS3_PORT				GPIO_PORTA_U.reg
#define R_MS1_pin				GPIO_PIN5//GPIOC
#define R_MS2_pin				GPIO_PIN7//GPIOC
#define R_MS3_pin				GPIO_PIN6//GPIOA

#endif /* STEPPER_CONFİG_H_ */