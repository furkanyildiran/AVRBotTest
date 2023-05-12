#ifdef __cplusplus
extern "C"{
#endif

#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define USART_CHAR_SIZE5 0
#define USART_CHAR_SIZE6 1
#define USART_CHAR_SIZE7 2
#define USART_CHAR_SIZE8 3
#define TX_BUFF_SIZE 0x1F
#define RX_BUFF_SIZE 0x1F
#define RX_BUFF_FULL 1
#define USART_PARITY_ODD 0b11
#define USART_PARITY_EVEN 0b10
#define USART_open()   ()

void USART_init(uint32_t baudrate, uint8_t char_size);
void USART_transmit(uint8_t data[],uint8_t size);
uint8_t USART_receive(void);
uint8_t USART_available(void);
void USART_parity_enbl(uint8_t mode);
uint8_t USART_parity_err_check(void);
void USART_parity_err_clear(void);

#endif

#ifdef __cplusplus
}
#endif