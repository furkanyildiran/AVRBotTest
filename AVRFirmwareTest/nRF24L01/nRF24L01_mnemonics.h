#ifdef __cplusplus
extern "C"{
	#endif

	#ifndef NRF24L01_MNEMONICS_H_
	#define NRF24L01_MNEMONICS_H_

	#define R_REGISTER(register_addr)(register_addr)
	#define W_REGISTER(register_addr)(0x20 | register_addr)
	#define R_RX_PAYLOAD 0x61
	#define W_TX_PAYLOAD 0xA0
	#define FLUSH_TX 0xE1
	#define FLUSH_RX 0xE2
	#define REUSE_TX_PL 0xE3
	#define R_RX_PL_WID 0x60
	#define W_ACK_PAYLOAD(pipe)(0XA8 | pipe)
	#define W_TX_PAYLOAD_NO_ACK 0xB0
	#define NOP 0xFF

	#define CONFIG_REG_ADDR		0x00
	#define MASK_RX_DR			6
	#define MASK_TX_DS			5
	#define MASK_MAX_RT			4
	#define EN_CRC				3
	#define CRCO				2
	#define	PWR_UP				1
	#define PRIM_RX				0
	
	#define EN_AA_REG_ADDR      0x01
	#define ENAA_P5				5
	#define ENAA_P4				4
	#define ENAA_P3			    3
	#define ENAA_P2				2
	#define ENAA_P1				1
	#define ENAA_P0				0

	#define EN_RXADDR_REG_ADDR  0x02
	#define ERX_P5		        5
	#define ERX_P4			    4
	#define ERX_P3				3
	#define ERX_P2				2
	#define ERX_P1				1
	#define ERX_P0				0

	#define SETUP_AW_REG_ADDR   0x03
	#define AW					0

	#define SETUP_RETR_REG_ADDR 0x04
	#define ARD					4
	#define ARC					0

	#define RF_CH_REG_ADDR      0x05
	#define RF_CH				0

	#define RF_SETUP_REG_ADDR   0x06
	#define CONT_WAVE           7
	#define RF_DR_LOW           5
	#define PLL_LOCK            4
	#define RF_DR_HIGH          3
	#define RF_PWR              1

	#define STATUS_REG_ADDR     0x07
	#define RX_DR               6
	#define TX_DS               5
	#define MAX_RT				4
	#define RX_P_NO				1
	#define TX_FULL             0

	#define OBSERVE_TX_ADDR     0x08
	#define PLOS_CNT            4
	#define ARC_CNT             0

	#define RPD_REG_ADDR		0x09

	#define RX_ADDR_P0_REG_ADDR 0x0A
	#define RX_ADDR_P1_REG_ADDR 0x0B
	#define RX_ADDR_P2_REG_ADDR 0x0C
	#define RX_ADDR_P3_REG_ADDR 0x0D
	#define RX_ADDR_P4_REG_ADDR 0x0E
	#define RX_ADDR_P5_REG_ADDR 0x0F

	#define TX_ADDR_REG_ADDR    0x10

	#define RX_PW_P0_REG_ADDR   0x11
	#define RX_PW_P1_REG_ADDR   0x12
	#define RX_PW_P2_REG_ADDR   0x13
	#define RX_PW_P3_REG_ADDR   0x14
	#define RX_PW_P4_REG_ADDR	0x15
	#define RX_PW_P5_REG_ADDR	0x16

	#define FIFO_STATS_REG_ADDR 0x17
	#define TX_REUSE			6
	#define TX_FULL				5
	#define TX_EMPTY			4
	#define RX_FULL				1
	#define RX_EMPTY			0

	#define DYNPD_REG_ADDR		0x1C
	#define DPL_P5				5
	#define DPL_P4				4
	#define DPL_P3				3
	#define DPL_P2				2
	#define DPL_P1				1
	#define DPL_P0				0

	#define FEATURE_REG_ADDR    0x1D
	#define EN_DPL				2
	#define EN_ACK_PAY			1
	#define EN_DYN_ACK			0
	
	#define PIPE_0        0
	#define PIPE_1        1
	#define PIPE_2        2
	#define PIPE_3        3
	#define PIPE_4        4
	#define PIPE_5        5

	#endif /* NRF24L01_MNEMONİCS_H_ */
	#ifdef __cplusplus
}
#endif
