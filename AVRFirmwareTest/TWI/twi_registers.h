#ifndef TWI_REGISTERS_H_
#define TWI_REGISTERS_H_
#define TWBR_ADDR 0xB8
#define TWCR_ADDR 0xBC
#define TWSR_ADDR 0xB9
#define TWDR_ADDR 0xBB
#define TWAR_ADDR 0xBA
#define TWAMR_ADDR 0xBD

#ifndef TWBR 
#define TWBR (*(volatile uint8_t*)TWBR_ADDR)
#endif

#ifndef TWCR
#define TWCR (*(volatile uint8_t*)TWCR_ADDR)
#endif

#ifndef TWSR
#define TWSR (*(volatile uint8_t*)TWSR_ADDR)
#endif

#ifndef TWDR
#define TWDR (*(volatile uint8_t*)TWDR_ADDR)
#endif

#ifndef TWAR
#define TWAR (*(volatile uint8_t*)TWAR_ADDR)
#endif

#ifndef TWAMR
#define TWAMR (*(volatile uint8_t*)TWAMR_ADDR)
#endif

#endif /* TWI_REGISTERS_H_ */