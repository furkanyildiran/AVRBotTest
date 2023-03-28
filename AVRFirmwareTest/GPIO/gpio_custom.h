#ifdef __cplusplus
extern "C"{
	#endif

	#ifndef GPIO_CUSTOM_H_
	#define GPIO_CUSTOM_H_
	#define PIN_ADDR_OFFSET -2
	#define DDR_ADDR_OFFSET -1

	#if defined (__AVR_ATmega328P__)
	#define PORTD_ADDR 0x2B
	#define DDRD_ADDR  0x2A
	#define PIND_ADDR  0x29
	#define PORTC_ADDR 0x28
	#define DDRC_ADDR  0x27
	#define PINC_ADDR  0x26
	#define PORTB_ADDR 0x25
	#define DDRB_ADDR  0x24
	#define PINB_ADDR  0x23
	#define GPIO_PORTD (*(gpio_ptr_u)PORTD_ADDR)
	#define GPIO_DDRD  (*(gpio_ptr_u)DDRD_ADDR)
	#define GPIO_PIND  (*(gpio_ptr_u)PIND_ADDR)
	#define GPIO_PORTC (*(gpio_ptr_u)PORTC_ADDR)
	#define GPIO_DDRC  (*(gpio_ptr_u)DDRC_ADDR)
	#define GPIO_PINC  (*(gpio_ptr_u)PINC_ADDR)
	#define GPIO_PORTB (*(gpio_ptr_u)PORTB_ADDR)
	#define GPIO_DDRB  (*(gpio_ptr_u)DDRB_ADDR)
	#define GPIO_PINB  (*(gpio_ptr_u)PINB_ADDR)
	
	#elif defined (__AVR_ATmega2560__)
	#define PORTA_ADDR 0x22
	#define PORTB_ADDR 0x25
	#define PORTC_ADDR 0x28
	#define PORTD_ADDR 0x2B
	#define PORTE_ADDR 0x2E
	#define PORTF_ADDR 0x31
	#define PORTG_ADDR 0x34
	#define PORTH_ADDR 0x102
	#define PORTJ_ADDR 0x105
	#define PORTK_ADDR 0x108
	#define PORTL_ADDR 0x10B
	#define GPIO_PORTA (*(gpio_ptr_u)PORTA_ADDR)
	#define GPIO_DDRA  (*(gpio_ptr_u)DDRA_ADDR)
	#define GPIO_PINA  (*(gpio_ptr_u)PINA_ADDR)
	#define GPIO_PORTB (*(gpio_ptr_u)PORTB_ADDR)
	#define GPIO_DDRB  (*(gpio_ptr_u)DDRB_ADDR)
	#define GPIO_PINB  (*(gpio_ptr_u)PINB_ADDR)
	#define GPIO_PORTC (*(gpio_ptr_u)PORTC_ADDR)
	#define GPIO_DDRC  (*(gpio_ptr_u)DDRC_ADDR)
	#define GPIO_PINC  (*(gpio_ptr_u)PINC_ADDR)
	#define GPIO_PORTD (*(gpio_ptr_u)PORTD_ADDR)
	#define GPIO_DDRD  (*(gpio_ptr_u)DDRD_ADDR)
	#define GPIO_PIND  (*(gpio_ptr_u)PIND_ADDR)
	#define GPIO_PORTE (*(gpio_ptr_u)PORTE_ADDR)
	#define GPIO_DDRE  (*(gpio_ptr_u)DDRE_ADDR)
	#define GPIO_PINE  (*(gpio_ptr_u)PINE_ADDR)
	#define GPIO_PORTF (*(gpio_ptr_u)PORTF_ADDR)
	#define GPIO_DDRF  (*(gpio_ptr_u)DDRF_ADDR)
	#define GPIO_PINF  (*(gpio_ptr_u)PINF_ADDR)
	#define GPIO_PORTG (*(gpio_ptr_u)PORTG_ADDR)
	#define GPIO_DDRG  (*(gpio_ptr_u)DDRG_ADDR)
	#define GPIO_PING  (*(gpio_ptr_u)PING_ADDR)
	#define GPIO_PORTH (*(gpio_ptr_u)PORH_ADDR)
	#define GPIO_DDRH  (*(gpio_ptr_u)DDRH_ADDR)
	#define GPIO_PINH  (*(gpio_ptr_u)PINH_ADDR)
	#define GPIO_PORTJ (*(gpio_ptr_u)PORTJ_ADDR)
	#define GPIO_DDRJ  (*(gpio_ptr_u)DDRJ_ADDR)
	#define GPIO_PINJ  (*(gpio_ptr_u)PINJ_ADDR)
	#define GPIO_PORTK (*(gpio_ptr_u)PORTK_ADDR)
	#define GPIO_DDRK  (*(gpio_ptr_u)DDRK_ADDR)
	#define GPIO_PINK  (*(gpio_ptr_u)PINK_ADDR)
	#define GPIO_PORTL (*(gpio_ptr_u)PORTL_ADDR)
	#define GPIO_DDRL  (*(gpio_ptr_u)DDRL_ADDR)
	#define GPIO_PINL  (*(gpio_ptr_u)PINL_ADDR)
	#endif

	typedef struct
	{
		uint8_t p0:1;
		uint8_t p1:1;
		uint8_t p2:1;
		uint8_t p3:1;
		uint8_t p4:1;
		uint8_t p5:1;
		uint8_t p6:1;
		uint8_t p7:1;
	}pins_t,*pins_ptr_t;
	
	typedef union{
		pins_t pins;
		volatile uint8_t byte;
	}gpio_u, *gpio_ptr_u;
	
	#endif  /*end of GPIO_CUSTOM_H_ */
	#ifdef __cplusplus
}
#endif
