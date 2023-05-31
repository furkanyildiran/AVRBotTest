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
#include <stdlib.h>
#include "pcd8544.h"
#include "gpio_custom.h"
#include "stepper.h"
#include "task.h"
#include "nrf24l01.h"
#include "qmc5883l.h"
#include "usart.h"
#include "hcsr04.h"
#include <util/atomic.h>
#include <stdlib.h>
#include <string.h>


char buff[20]="\0";
uint8_t nrfbuff[5]={0};
uint32_t prevTime;
uint8_t pipe[5]={0x00,0x00,0x00,0x00,0x01};
/*
void PCF_Task(void){
	prevTime = getMs();
	if((prevTime%3000)==0){
		sprintf(buff,"%ld",prevTime);
		PCD_text(buff,0,LINE_2);
	}
	qmc_read_axis();
	int16_t x = qmc_getx();
	int16_t y = qmc_gety();
	float heading = atan2((double)y,(double)x)*180.0/3.14;
	heading = (heading < 0)? 360 + heading:heading;
	if((prevTime%300)==0){
		PCD_clear(0,45,LINE_3);
		
		sprintf(buff,"%d",(int)heading);
		PCD_text(buff,0,LINE_3);
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
}*/
int16_t getHeading(void){
	qmc_read_axis();
	int16_t x = qmc_getx();
	int16_t y = qmc_gety();
	float heading = atan2((double)y,(double)x)*180.0/3.14;
	return (int16_t)((heading < 0)? 360 + heading:heading);
}


	



int main(void)
{
	
	SPI_master_init(SPI_SCK_DVDR16);
	//twi_master_init(200000);
	PCD_init((volatile uint8_t *const)GPIO_PORTL_ADDR, 5, 7, 6);
	PCD_contrast(65);
	USART_init(9600,USART_CHAR_SIZE8);
	A4988_init();
	
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	OCR1A=249;
	/*nRF24L01_init((volatile uint8_t*)GPIO_PORTG_ADDR,0,1);
	nRF24L01_open_pipe(PIPE_0, pipe, 108, PA_LEVEL_MAX);
	nRF24L01_data_rate(DEFAULT_DR_1Mbps);
	qmc_init(QMC_OSR_64,QMC_RNG_2G,QMC_ODR_50HZ,QMC_DSBL_INTRPT);
	*/
	sei();
	PCD_clear_all();
	char b[10]={"\0"};
	HCSR04_init();
    while (1) 
    {
		uint16_t distance = HCSR04_measure();
		if (distance > 30){
			A4988_forward(20);
			PCD_clear(0,40,LINE_2);
			while(A4988_movementControl()==NOT_MOVED){
				if(HCSR04_measure()<30){
					A4988_stop();
					break;
				}
			}
			
			PCD_clear(0,40,LINE_2);
			
		}
		else{
			A4988_left(10);
			PCD_clear(0,40,LINE_1);
			while(A4988_movementControl() != MOVED){
				PCD_text("burada",0,LINE_1);
			}
			PCD_clear(0,40,LINE_1);
		}
		PCD_clear(0,40,LINE_0);
		sprintf(b,"%d",distance);
		PCD_text(b,0,LINE_0);
    }
}

