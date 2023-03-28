#ifdef __cplusplus
extern "C"{
#endif
#ifndef PCD8544_H_
#define PCD8544_H_
#ifndef F_CPU
#define F_CPU 16000000ul
#endif
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "pcd8544_mnemonics.h"
#include "spi_custom.h"
#include "gpio_custom.h"

void PCD_init(volatile uint8_t *const port_addr, uint8_t dc_pin, uint8_t rst_pin, uint8_t ce_pin);
void PCD_clear(uint8_t x1_coor, uint8_t x2_coor, uint8_t y_line);
void PCD_text(const char *text, uint8_t x, uint8_t line);
void PCD_contrast(uint8_t contrast);
void PCD_clear_all(void);
void PCD_invert(void);

#endif
#ifdef __cplusplus
}
#endif
