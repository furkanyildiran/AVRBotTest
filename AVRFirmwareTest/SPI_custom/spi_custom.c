#include "spi_custom.h"
#define DELAY_3CYCLES() do{asm volatile("NOP\n\tNOP\n\tNOP\n\t");}while(0)


void SPI_dord(uint8_t dord){
	SPCR |= (dord << DORD);
}
void SPI_master_cpol_cpha(uint8_t cpol, uint8_t cpha){
	SPCR |= (cpol << CPOL) | (cpha << CPHA);
}
uint8_t SPI_transaction(uint8_t data){
	SPDR = data;
	DELAY_3CYCLES();
	while(!(SPSR & (1 << SPIF)));
	DELAY_3CYCLES();
	data = SPDR;
	return data;
}
void SPI_master_init(uint8_t sck_dvdr){
	switch(sck_dvdr){
		case SPI_SCK_DVDR2_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR4:
		SPCR &= ~((1 << SPR1) | (1 << SPR0));
		break;
		
		case SPI_SCK_DVDR8_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR16:
		SPCR &= ~(1 << SPR1);
		SPCR |= (1 << SPR0);
		break;
		
		case SPI_SCK_DVDR32_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR64:
		SPCR |= (1 << SPR1);
		SPCR &= ~(1 << SPR0);
		break;
		
		case SPI_SCK_DVDR64_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR128:
		SPCR |= (1 << SPR1) | (1 << SPR0);
		break;
	}
	DDRB |= (1 << MOSI_pin) | (1 << SS_pin) | (1 << SCK_pin);
	SPCR |= (1 << MSTR) | (1 << SPE);
	SPI_SS_PIN_HIGH;
}
void SPI_slave_init(void){
	DDRB |= (1 << MISO_pin);
	SPCR |= (1 << SPE) | (1 << SPIE);
}
