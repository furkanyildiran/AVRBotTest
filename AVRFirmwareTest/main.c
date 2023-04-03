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
#include "task.h"
#include "nrf24l01.h"
#include <util/atomic.h>

char buff[20]="\0";
uint8_t nrfbuff[5]={0};
uint32_t prevTime;
uint8_t pipe[5]={0x00,0x00,0x00,0x00,0x01};
void PCF_Task(void){
	prevTime = getMs();
	if((prevTime%3000)==0){
		sprintf(buff,"%ld",prevTime);
		PCD_text(buff,0,LINE_2);
	}	
}
void Nrf_Task(void){
	nRF24L01_listen();
	if(nRF24L01_available()){
		uint8_t width = nRF24L01_payload_width();
		nRF24L01_payload(nrfbuff,width);
		sprintf(buff,"%d",nrfbuff[0]);
		//PCD_text(buff,0,LINE_3);
		if(nrfbuff[0]==1)A4988_forward();
		else if(nrfbuff[0]==2)A4988_backward();
		else if(nrfbuff[0]==4)A4988_left();
		else if(nrfbuff[0]==8)A4988_right();
		else if(nrfbuff[0]==16)A4988_stop();
	}
}

int main(void)
{
	SPI_master_init(SPI_SCK_DVDR16);
	PCD_init((volatile uint8_t *const)GPIO_PORTL_ADDR, 5, 7, 6);
	PCD_contrast(65);
	PCD_text("HELLO",0,LINE_0);
	PCD_text("WORLD",0,LINE_1);

	A4988_init();
	A4988_stop();
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	OCR0A=120;
	OCR1A=249;
	
	A4988_stop();
	Task_add(PCF_Task);
	Task_add(Nrf_Task);
	nRF24L01_init((volatile uint8_t*)GPIO_PORTG_ADDR,0,1);
	nRF24L01_open_pipe(PIPE_0, pipe, 108, PA_LEVEL_MAX);
	nRF24L01_data_rate(DEFAULT_DR_1Mbps);
	sei();
	/*DDRA=0x00;
	PORTA=0XFF;
	DDRB=0xff;
	nRF24L01_init((volatile uint8_t*)GPIO_PORTG_ADDR,0,1);
	nRF24L01_open_pipe(PIPE_0, pipe, 108, PA_LEVEL_MAX);
	nRF24L01_data_rate(DEFAULT_DR_1Mbps);*/
    while (1) 
    {
		
		
		/*uint8_t val[1]={0};
		val[0]=PINA;
		if((PINA&1)==0){val[0] = 1; nRF24L01_transmit(val,1);}
		else if((PINA&2)==0){val[0] = 2; nRF24L01_transmit(val,1);}
		else if((PINA&4)==0){val[0] = 4; nRF24L01_transmit(val,1);}
		else if((PINA&8)==0){val[0] = 8; nRF24L01_transmit(val,1);PORTB=0xff;}
		else if((PINA&128)==0){val[0] = 16; nRF24L01_transmit(val,1); PORTB=0xff;}else PORTB=0;*/
		
		
    }
}

