#ifdef __cplusplus
extern "C"{
	#endif
	#ifndef TWI_H_
	#define TWI_H_
	#ifndef F_CPU
	#define F_CPU 16000000UL
	#endif
	#include <stdint.h>
	#include <avr/io.h>
	#include <util/delay.h>
	#include "twi_registers.h"

	#define TWI_STOP 1
	#define TWI_RSTART 0
	#define TWI_MW 0
	#define TWI_MR 1
	#define TWI_SW 2
	#define TWI_SR 3
	#define TWI_WRITE 0
	#define TWI_READ 1
	#define twi_ovf_ms 25
	
	void twi_master_init(uint32_t SCLK);
	void twi_send_start(void);
	void twi_send_address(uint8_t device_addr, uint8_t operation);
	void twi_send_byte_with_ack(uint8_t data);
	void twi_send_byte_with_nack(uint8_t data);
	uint8_t twi_read_byte_ret_ack(void);
	uint8_t twi_read_byte_ret_nack(void);
	void twi_send_stop(void);
	void twi_master_reset(void);
	void twi_wait_flag(uint8_t flag);
	void twi_master_release_bus(void);
	void twi_slave_init(uint8_t device_addr);
	uint8_t twi_slave_listen(void);
	uint8_t twi_control_ovf(void);
	void twi_write_reg_byte(uint8_t device_addr, uint8_t reg_addr, uint8_t reg_val);

	#endif
	#ifdef __cplusplus
}
#endif