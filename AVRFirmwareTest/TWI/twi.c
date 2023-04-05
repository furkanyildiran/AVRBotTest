#define max_loop_counter 18900 //for 20ms waiting
#include "twi.h"

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

uint8_t twi_mode = 0;
uint8_t slave_addressed = 0;
uint8_t twi_ovf_flag = 1;



void twi_master_init(uint32_t SCLK){
	TWSR = 0x00;
	//Because pow func is too large for rom memory, not prefer using in this line
	//TWBR = ((F_CPU / SCLK) - 16) / (2 * pow(4, (TWSR & ((1 << TWPS0) | (1 << TWPS1)))));
	//prescaler bits always assumed as 0 therefore prescaler is 1
	TWBR = ((F_CPU / (2 * SCLK)) - 8);
	TWCR = (1 << TWINT) | (1 << TWEN);
	#if defined (__AVR_ATmega328P__)
	PORTC |= (1 << PORTC4) | (1 << PORTC5);
	#elif defined (__AVR_ATmega2560__)
	PORTD |= (1 << PORTD1) | (1 << PORTD0);
	#else
	PORTC |= (1 << PORTC4) | (1 << PORTC5);
	#endif
}
void twi_send_start(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	twi_wait_flag(TWINT);
}
void twi_send_address(uint8_t device_addr, uint8_t operation) {
	TWDR = (device_addr << 1) | operation;
	TWCR = (1 << TWINT) | (1 << TWEN);
	twi_wait_flag(TWINT);
}
void twi_send_byte_with_ack(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	twi_wait_flag(TWINT);
}
void twi_send_byte_with_nack(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	twi_wait_flag(TWINT);
}
uint8_t twi_read_byte_ret_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	twi_wait_flag(TWINT);
	return TWDR;
}
uint8_t twi_read_byte_ret_nack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	twi_wait_flag(TWINT);
	return TWDR;
}
void twi_send_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
void twi_master_reset(void) {
	twi_ovf_flag = 0;
	TWCR = 0;
	
	#if defined (__AVR_ATmega328P__)
	PORTC &= ~((1 << PORTC4) | (1 << PORTC5));
	#elif defined (__AVR_ATmega2560__)
	PORTD &= ~((1 << PORTD1) | (1 << PORTD0));
	#else
	PORTC &= ~((1 << PORTC4) | (1 << PORTC5));
	#endif
	_delay_ms(50);
	#if defined (__AVR_ATmega328P__)
	PORTC |= (1 << PORTC4) | (1 << PORTC5);
	#elif defined (__AVR_ATmega2560__)
	PORTD |= (1 << PORTD1) | (1 << PORTD0);
	#else
	PORTC |= (1 << PORTC4) | (1 << PORTC5);
	#endif
	TWCR = (1 << TWINT) | (1 << TWEN);
}


__attribute__((noinline)) void twi_wait_flag(uint8_t flag)
{
	uint32_t loop_counter = 0;
	while (!(TWCR & (1 << flag))) {
		loop_counter++;
		if(loop_counter >= max_loop_counter){
			twi_ovf_flag = 1;
			break;
		}
	}
}
void twi_master_release_bus(void) {
	TWCR = 0;
	#if defined (__AVR_ATmega328P__)
	PORTC &= ~((1 << PORTC4) | (1 << PORTC5));
	#elif defined (__AVR_ATmega2560__)
	PORTD &= ~((1 << PORTD1) | (1 << PORTD0));
	#else
	PORTC &= ~((1 << PORTC4) | (1 << PORTC5));
	#endif
}
void twi_slave_init(uint8_t slave_addr){
	TWAR = (slave_addr << 1);
}
uint8_t twi_slave_listen(void)
{
	if (!slave_addressed) {
		TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
		slave_addressed = 1;
		return -1;
	}
	if (!(TWCR & (1 << TWINT)))
		return -1;
	if ((TWSR & 0xF8) == 0xA8)
		twi_mode = TWI_SR;
	else if ((TWSR & 0xF8) == 0x60)
		twi_mode = TWI_SW;
	slave_addressed = 0;
	return twi_mode;
}
uint8_t twi_control_ovf(){
	return twi_ovf_flag;
}