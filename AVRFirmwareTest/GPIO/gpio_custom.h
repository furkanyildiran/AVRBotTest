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
	
	#define _GPIO_PORTB		(*((volatile uint8_t*)GPIO_PORTB_ADDR))
	#define _GPIO_DDRB		(*((volatile uint8_t*)GPIO_DDRB_ADDR))
	#define _GPIO_PINB		(*((volatile uint8_t*)GPIO_PINB_ADDR))
	#define _GPIO_PORTC		(*((volatile uint8_t*)GPIO_PORTC_ADDR))
	#define _GPIO_DDRC		(*((volatile uint8_t*)GPIO_DDRC_ADDR))
	#define _GPIO_PINC		(*((volatile uint8_t*)GPIO_PINC_ADDR))
	#define _GPIO_PORTD		(*((volatile uint8_t*)GPIO_PORTD_ADDR))
	#define _GPIO_DDRD		(*((volatile uint8_t*)GPIO_DDRD_ADDR))
	#define _GPIO_PIND		(*((volatile uint8_t*)GPIO_PIND_ADDR))
	
	#define GPIO_PORTB_U (*(gpio_ptr_u)GPIO_PORTB_ADDR)
	#define GPIO_DDRB_U  (*(gpio_ptr_u)GPIO_DDRB_ADDR)
	#define GPIO_PINB_U  (*(gpio_ptr_u)GPIO_PINB_ADDR)
	#define GPIO_PORTC_U (*(gpio_ptr_u)GPIO_PORTC_ADDR)
	#define GPIO_DDRC_U  (*(gpio_ptr_u)GPIO_DDRC_ADDR)
	#define GPIO_PINC_U  (*(gpio_ptr_u)GPIO_PINC_ADDR)
	#define GPIO_PORTD_U (*(gpio_ptr_u)GPIO_PORTD_ADDR)
	#define GPIO_DDRD_U  (*(gpio_ptr_u)GPIO_DDRD_ADDR)
	#define GPIO_PIND_U  (*(gpio_ptr_u)GPIO_PIND_ADDR)
	
	#if defined(__AVR_ATmega2560__)
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
	
	#define _GPIO_PORTA		(*((volatile uint8_t*)GPIO_PORTA_ADDR))
	#define _GPIO_DDRA		(*((volatile uint8_t*)GPIO_DDRA_ADDR))
	#define _GPIO_PINA		(*((volatile uint8_t*)GPIO_PINA_ADDR))
	#define _GPIO_PORTE		(*((volatile uint8_t*)GPIO_PORTE_ADDR))
	#define _GPIO_DDRE		(*((volatile uint8_t*)GPIO_DDRE_ADDR))
	#define _GPIO_PINE		(*((volatile uint8_t*)GPIO_PINE_ADDR))
	#define _GPIO_PORTF		(*((volatile uint8_t*)GPIO_PORTF_ADDR))
	#define _GPIO_DDRF		(*((volatile uint8_t*)GPIO_DDRF_ADDR))
	#define _GPIO_PINF		(*((volatile uint8_t*)GPIO_PINF_ADDR))
	#define _GPIO_PORTG		(*((volatile uint8_t*)GPIO_PORTG_ADDR))
	#define _GPIO_DDRG		(*((volatile uint8_t*)GPIO_DDRG_ADDR))
	#define _GPIO_PING		(*((volatile uint8_t*)GPIO_PING_ADDR))
	#define _GPIO_PORTH		(*((volatile uint8_t*)GPIO_PORTH_ADDR))
	#define _GPIO_DDRH		(*((volatile uint8_t*)GPIO_DDRH_ADDR))
	#define _GPIO_PINH		(*((volatile uint8_t*)GPIO_PINH_ADDR))
	#define _GPIO_PORTJ		(*((volatile uint8_t*)GPIO_PORTJ_ADDR))
	#define _GPIO_DDRJ		(*((volatile uint8_t*)GPIO_DDRJ_ADDR))
	#define _GPIO_PINJ		(*((volatile uint8_t*)GPIO_PINJ_ADDR))
	#define _GPIO_PORTK		(*((volatile uint8_t*)GPIO_PORTK_ADDR))
	#define _GPIO_DDRK		(*((volatile uint8_t*)GPIO_DDRK_ADDR))
	#define _GPIO_PINK		(*((volatile uint8_t*)GPIO_PINK_ADDR))
	#define _GPIO_PORTL		(*((volatile uint8_t*)GPIO_PORTL_ADDR))
	#define _GPIO_DDRL		(*((volatile uint8_t*)GPIO_DDRL_ADDR))
	#define _GPIO_PINL		(*((volatile uint8_t*)GPIO_PINL_ADDR))
		
	#define GPIO_PORTA_U (*(gpio_ptr_u)GPIO_PORTA_ADDR)
	#define GPIO_DDRA_U  (*(gpio_ptr_u)GPIO_DDRA_ADDR)
	#define GPIO_PINA_U  (*(gpio_ptr_u)GPIO_PINA_ADDR)
	/*#define GPIO_PORTB_U (*(gpio_ptr_u)GPIO_PORTB_ADDR)
	#define GPIO_DDRB_U  (*(gpio_ptr_u)GPIO_DDRB_ADDR)
	#define GPIO_PINB_U  (*(gpio_ptr_u)GPIO_PINB_ADDR)
	#define GPIO_PORTC_U (*(gpio_ptr_u)GPIO_PORTC_ADDR)
	#define GPIO_DDRC_U  (*(gpio_ptr_u)GPIO_DDRC_ADDR)
	#define GPIO_PINC_U  (*(gpio_ptr_u)GPIO_PINC_ADDR)
	#define GPIO_PORTD_U (*(gpio_ptr_u)GPIO_PORTD_ADDR)
	#define GPIO_DDRD_U  (*(gpio_ptr_u)GPIO_DDRD_ADDR)
	#define GPIO_PIND_U  (*(gpio_ptr_u)GPIO_PIND_ADDR)*/
	#define GPIO_PORTE_U (*(gpio_ptr_u)GPIO_PORTE_ADDR)
	#define GPIO_DDRE_U  (*(gpio_ptr_u)GPIO_DDRE_ADDR)
	#define GPIO_PINE_U  (*(gpio_ptr_u)GPIO_PINE_ADDR)
	#define GPIO_PORTF_U (*(gpio_ptr_u)GPIO_PORTF_ADDR)
	#define GPIO_DDRF_U  (*(gpio_ptr_u)GPIO_DDRF_ADDR)
	#define GPIO_PINF_U  (*(gpio_ptr_u)GPIO_PINF_ADDR)
	#define GPIO_PORTG_U (*(gpio_ptr_u)GPIO_PORTG_ADDR)
	#define GPIO_DDRG_U  (*(gpio_ptr_u)GPIO_DDRG_ADDR)
	#define GPIO_PING_U  (*(gpio_ptr_u)GPIO_PING_ADDR)
	#define GPIO_PORTH_U (*(gpio_ptr_u)GPIO_PORTH_ADDR)
	#define GPIO_DDRH_U  (*(gpio_ptr_u)GPIO_DDRH_ADDR)
	#define GPIO_PINH_U  (*(gpio_ptr_u)GPIO_PINH_ADDR)
	#define GPIO_PORTJ_U (*(gpio_ptr_u)GPIO_PORTJ_ADDR)
	#define GPIO_DDRJ_U  (*(gpio_ptr_u)GPIO_DDRJ_ADDR)
	#define GPIO_PINJ_U  (*(gpio_ptr_u)GPIO_PINJ_ADDR)
	#define GPIO_PORTK_U (*(gpio_ptr_u)GPIO_PORTK_ADDR)
	#define GPIO_DDRK_U  (*(gpio_ptr_u)GPIO_DDRK_ADDR)
	#define GPIO_PINK_U  (*(gpio_ptr_u)GPIO_PINK_ADDR)
	#define GPIO_PORTL_U (*(gpio_ptr_u)GPIO_PORTL_ADDR)
	#define GPIO_DDRL_U  (*(gpio_ptr_u)GPIO_DDRL_ADDR)
	#define GPIO_PINL_U  (*(gpio_ptr_u)GPIO_PINL_ADDR)
	#endif
	
	#define GPIO_SET_PIN(gpio, pin)		(gpio |= (1 << pin))
	#define GPIO_CLEAR_PIN(gpio, pin)	(gpio &= ~(1 << pin))
	#define GPIO_SET_REG(gpio, reg_val) (gpio |= reg_val)
	#define GPIO_CLEAR_REG(gpio, reg_val) (gpio &= ~reg_val)

	typedef enum{
		GPIO_PIN0,
		GPIO_PIN1,
		GPIO_PIN2,
		GPIO_PIN3,
		GPIO_PIN4,
		GPIO_PIN5,
		GPIO_PIN6,
		GPIO_PIN7	
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
		volatile uint8_t port;
	}gpio_u, *gpio_ptr_u;
	
	#endif  /*end of GPIO_CUSTOM_H_ */
	#ifdef __cplusplus
	}
	#endif

