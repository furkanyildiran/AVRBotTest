/*
 * AVRFirmwareTest.c
 *
 * Created: 28.03.2023 16:51:18
 * Author : MONSTER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "pcd8544.h"
#include "gpio_custom.h"
#include "stepper.h"
char buff[20]="\0";
int main(void)
{
	/*SPI_master_init(SPI_SCK_DVDR16);
	PCD_init((volatile uint8_t *const)PORTL_ADDR, 5, 7, 6);
	PCD_contrast(65);
	PCD_text("HELLO",0,LINE_0);
	PCD_text("WORLD",0,LINE_1);
	PCD_clear_all();
	A4988_init();*/
	
	_delay_ms(5000);
	sei();
    while (1) 
    {
		/*A4988_SPEED_LEVEL5();
		A4988_forward();
		_delay_ms(5000);
		A4988_SPEED_LEVEL4();
		_delay_ms(5000);
		A4988_SPEED_LEVEL3();
		_delay_ms(5000);
		A4988_SPEED_LEVEL2();
		_delay_ms(5000);
		A4988_SPEED_LEVEL1();
		_delay_ms(5000);*/
		
    }
}

