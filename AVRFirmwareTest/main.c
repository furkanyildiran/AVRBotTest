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
uint8_t counter;
char buff[20]="\0";
int main(void)
{
	SPI_master_init(SPI_SCK_DVDR16);
	PCD_init((volatile uint8_t *const)PORTL_ADDR, 5, 7, 6);
	PCD_contrast(65);
	PCD_text("HELLO",0,LINE_0);
	PCD_text("WORLD",0,LINE_1);
	PCD_clear_all();
	A4988_init();
	DDRA |= (1 << 5) | (1 << 6) | (1 << 7);
	DDRC |= (1 << 5) | (1 << 6) | (1 << 7);
	PORTA &= ~((1 << 5) | (1 << 6) | (1 << 7));
	PORTC &= ~((1 << 5) | (1 << 6) | (1 << 7));
	_delay_ms(5000);
    while (1) 
    {
		
		FORWARD_DIRECTION();
		while(1){
			STEP_PULSE();
			_delay_us(800);
			//sprintf(buff,"counter : %d", counter);
			//PCD_text(buff,0,LINE_3);
		}
    }
}

