#ifdef __cplusplus
extern "C"{
	#endif

	#ifndef __SPI_CUSTOM_H_
	#define __SPI_CUSTOM_H_
	#ifndef F_CPU
	#define F_CPU 16000000ul
	#endif
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdint.h>

	#define SPI_CPOL_LEDNG_EDG_RISNG  0
	#define SPI_CPOL_LEDNG_EDG_FLLNG  1
	#define SPI_CPHA_LEDNG_EDG_SMPLE  0
	#define SPI_CPHA_LEDNG_EDG_SETUP  1
	#define SPI_DORD_MSB_FIRST 0
	#define SPI_DORD_LSB_FIRST 1
	#define SPI_MASTER 1
	#define SPI_SLAVE 0
	#define SPI_SCK_DVDR4     0
	#define SPI_SCK_DVDR16    1
	#define SPI_SCK_DVDR64    2
	#define SPI_SCK_DVDR128   3
	#define SPI_SCK_DVDR2_2X  4
	#define SPI_SCK_DVDR8_2X  5
	#define SPI_SCK_DVDR32_2X 6
	#define SPI_SCK_DVDR64_2X 7
	#define SPI_SS_PIN_LOW (PORTB &= ~(1 << SS_pin))
	#define SPI_SS_PIN_HIGH (PORTB |= (1 << SS_pin))

	#if defined (__AVR_ATmega328P__)
	#define SCK_pin 5
	#define MISO_pin 4
	#define MOSI_pin 3
	#define SS_pin 2
	#elif defined (__AVR_ATmega2560__)
	#define SCK_pin 1
	#define MISO_pin 3
	#define MOSI_pin 2
	#define SS_pin 0
	#endif

	void SPI_master_init(uint8_t sck_dvdr);
	void SPI_slave_init(void);
	uint8_t SPI_transaction(uint8_t data);
	void SPI_dord(uint8_t dord);
	void SPI_master_cpol_cpha(uint8_t cpol, uint8_t cpha);

	#endif

	#ifdef __cplusplus
}
#endif
