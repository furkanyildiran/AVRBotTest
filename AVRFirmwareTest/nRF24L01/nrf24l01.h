#ifdef __cplusplus
extern "C"{
#endif
#ifndef NRF24L01_H_
#define NRF24L01_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "nRF24L01_config.h"
#include "nRF24L01_mnemonics.h"
#include "spi_custom.h"
#include "gpio_custom.h"

void nRF24L01_init(volatile uint8_t *const port_addr, uint8_t ce_pin, uint8_t csn_pin);
void nRF24L01_open_pipe(uint8_t pipe, uint8_t *pipe_addr, uint8_t channel, uint8_t PA);
uint8_t nRF24L01_available(void);
void nRF24L01_listen(void);
uint8_t nRF24L01_payload_width(void);
void nRF24L01_payload(uint8_t buff[], uint8_t payload_width);
uint8_t nRF24L01_transmit(uint8_t data[], uint8_t data_size);
void nRF24L01_data_rate(uint8_t data_rate);

#endif
#ifdef __cplusplus
}
#endif
