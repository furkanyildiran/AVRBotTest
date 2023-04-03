#ifdef __cplusplus
extern "C"{
	#endif
	#ifndef NRF24L01_CONFIG_H_
	#define NRF24L01_CONFIG_H_
	#include "nRF24L01_mnemonics.h"
	
	#define PA_LEVEL_MAX  (0b11  << RF_PWR)
	#define PA_LEVEL_HIGH (0b10  << RF_PWR)
	#define PA_LEVEL_LOW  (0b01  << RF_PWR)
	#define PA_LEVEL_MIN  (0b00  << RF_PWR)
	#define _1Mbps_DR     0
	#define _2Mbps_DR     (1 << RF_DR_HIGH)
	#define _250Kbps_DR   (1 << RF_DR_LOW)

	#define POWER_UP_DELAY 10     //ms
	#define RX_SETTLING_DELAY 130 //us
	#define TX_SETTLING_DELAY 130 //us

	#define TX_DS_FLAG_IS_HIGH(status)		   (status &(1 << TX_DS))
	#define MAX_RT_FLAG_IS_HIGH(status)		   (status &(1 << MAX_RT))
	#define CSN_PIN_LOW()                      do{*nRF24L01_port_addr &= ~(1 << CSN_PIN); _delay_us(10);}while(0);
	#define CSN_PIN_HIGH()                     do{*nRF24L01_port_addr |= (1 << CSN_PIN);  _delay_us(10);}while(0);
	#define CE_PIN_LOW()                       do{*nRF24L01_port_addr &= ~(1 << CE_PIN);  _delay_us(10);}while(0);
	#define CE_PIN_HIGH()                      do{*nRF24L01_port_addr |= (1 << CE_PIN);   _delay_us(10);}while(0);
	#define EN_ALL_RX_ENAA                     0x3F
	#define ADDRESS_WIDTH                      0x05
	#define _6mS_ARD_15_ARC					   (5 << ARD) | (15 << ARC)
	#define DEFAULT_DR_1Mbps				   _1Mbps_DR
	#define RX_IS_NOT_LISTENING()			   (nrf_rx_on_listening = 1)
	#define RX_IS_LISTENING()			       (nrf_rx_on_listening = 0)
	#define RX_LISTENING_STATE()               (nrf_rx_on_listening ? 1 : 0)

	#endif /* NRF24L01_CONFIG_H_ */
	#ifdef __cplusplus
}
#endif