#ifdef __cplusplus
extern "C"{
	#endif

	#ifndef GPIO_CUSTOM_H_
	#define GPIO_CUSTOM_H_
	#define GPIO_PIN_ADDR_OFFSET -2
	#define GPIO_DDR_ADDR_OFFSET -1

	#define GPIO_PORTD_ADDR 0x2B
	#define GPIO_DDRD_ADDR  0x2A
	#define GPIO_PIND_ADDR  0x29
	#define GPIO_PORTC_ADDR 0x28
	#define GPIO_DDRC_ADDR  0x27
	#define GPIO_PINC_ADDR  0x26
	#define GPIO_PORTB_ADDR 0x25
	#define GPIO_DDRB_ADDR  0x24
	#define GPIO_PINB_ADDR  0x23
	
	#define GPIO_PORTD (*(gpio_ptr_u)GPIO_PORTD_ADDR)
	#define GPIO_DDRD  (*(gpio_ptr_u)GPIO_DDRD_ADDR)
	#define GPIO_PIND  (*(gpio_ptr_u)GPIO_PIND_ADDR)
	#define GPIO_PORTC (*(gpio_ptr_u)GPIO_PORTC_ADDR)
	#define GPIO_DDRC  (*(gpio_ptr_u)GPIO_DDRC_ADDR)
	#define GPIO_PINC  (*(gpio_ptr_u)GPIO_PINC_ADDR)
	#define GPIO_PORTB (*(gpio_ptr_u)GPIO_PORTB_ADDR)
	#define GPIO_DDRB  (*(gpio_ptr_u)GPIO_DDRB_ADDR)
	#define GPIO_PINB  (*(gpio_ptr_u)GPIO_PINB_ADDR)
	
	#ifdef (__AVR_ATmega2560__)
		#define GPIO_PORTA_ADDR 0x22
		#define GPIO_DDRA_ADDR	0x21
		#define GPIO_PINA_ADDR	0x20
		#define GPIO_PORTE_ADDR 0x2E
		#define GPIO_DDRE_ADDR	0x2D
		#define GPIO_PINE_ADDR	0x2C
		#define GPIO_PORTF_ADDR 0x31
		#define GPIO_DDRF_ADDR	0x30
		#define GPIO_PINF_ADDR	0x2F
		#define GPIO_PORTG_ADDR 0x34
		#define GPIO_DDRG_ADDR	0x33
		#define GPIO_PING_ADDR	0x32
		#define GPIO_PORTH_ADDR 0x102
		#define GPIO_DDRH_ADDR	0x101
		#define GPIO_PINH_ADDR	0x100
		#define GPIO_PORTJ_ADDR 0x105
		#define GPIO_DDRJ_ADDR	0x103
		#define GPIO_PINJ_ADDR	0x102
		#define GPIO_PORTK_ADDR 0x108
		#define GPIO_DDRK_ADDR	0x107
		#define GPIO_PINK_ADDR	0x108
		#define GPIO_PORTL_ADDR 0x10B
		#define GPIO_DDRL_ADDR	0x10A
		#define GPIO_PINL_ADDR	0x109
		
		#define GPIO_PORTA (*(gpio_ptr_u)GPIO_PORTA_ADDR)
		#define GPIO_DDRA  (*(gpio_ptr_u)GPIO_DDRA_ADDR)
		#define GPIO_PINA  (*(gpio_ptr_u)GPIO_PINA_ADDR)
		#define GPIO_PORTE (*(gpio_ptr_u)GPIO_PORTE_ADDR)
		#define GPIO_DDRE  (*(gpio_ptr_u)GPIO_DDRE_ADDR)
		#define GPIO_PINE  (*(gpio_ptr_u)GPIO_PINE_ADDR)
		#define GPIO_PORTF (*(gpio_ptr_u)GPIO_PORTF_ADDR)
		#define GPIO_DDRF  (*(gpio_ptr_u)GPIO_DDRF_ADDR)
		#define GPIO_PINF  (*(gpio_ptr_u)GPIO_PINF_ADDR)
		#define GPIO_PORTG (*(gpio_ptr_u)GPIO_PORTG_ADDR)
		#define GPIO_DDRG  (*(gpio_ptr_u)GPIO_DDRG_ADDR)
		#define GPIO_PING  (*(gpio_ptr_u)GPIO_PING_ADDR)
		#define GPIO_PORTH (*(gpio_ptr_u)GPIO_PORH_ADDR)
		#define GPIO_DDRH  (*(gpio_ptr_u)GPIO_DDRH_ADDR)
		#define GPIO_PINH  (*(gpio_ptr_u)GPIO_PINH_ADDR)
		#define GPIO_PORTJ (*(gpio_ptr_u)GPIO_PORTJ_ADDR)
		#define GPIO_DDRJ  (*(gpio_ptr_u)GPIO_DDRJ_ADDR)
		#define GPIO_PINJ  (*(gpio_ptr_u)GPIO_PINJ_ADDR)
		#define GPIO_PORTK (*(gpio_ptr_u)GPIO_PORTK_ADDR)
		#define GPIO_DDRK  (*(gpio_ptr_u)GPIO_DDRK_ADDR)
		#define GPIO_PINK  (*(gpio_ptr_u)GPIO_PINK_ADDR)
		#define GPIO_PORTL (*(gpio_ptr_u)GPIO_PORTL_ADDR)
		#define GPIO_DDRL  (*(gpio_ptr_u)GPIO_DDRL_ADDR)
		#define GPIO_PINL  (*(gpio_ptr_u)GPIO_PINL_ADDR)
	#endif

	typedef enum{
		GPIO_PIN0,
		GPIO_PIN1,
		GPIO_PIN2,
		GPIO_PIN3,
		GPIO_PIN4,
		GPIO_PIN5,
		GPIO_PIN6,
		GPIO_PIN7,	
	}GPIO_PIN_t;

	typedef struct{
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
