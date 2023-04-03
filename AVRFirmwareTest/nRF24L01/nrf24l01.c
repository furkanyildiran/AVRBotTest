#include "nrf24l01.h"

static uint8_t selected_pipe;
static volatile uint8_t* nRF24L01_port_addr;
static uint8_t CE_PIN;
static uint8_t CSN_PIN;
static uint8_t nrf_rx_on_listening = 0;

static uint8_t get_status_reg(void);
static void clear_status_flags(void);
static void transfer_data(uint8_t command, uint8_t *data, uint8_t size);
static void flus_tx(void);
static void flus_rx(void);
/**
*@param void
*/
static void flus_tx(void){
	CSN_PIN_LOW();
	SPI_transaction(FLUSH_TX);
	CSN_PIN_HIGH();
}
static void flus_rx(void){
	CSN_PIN_LOW();
	SPI_transaction(FLUSH_RX);
	CSN_PIN_HIGH();
}
static uint8_t get_status_reg(void){
	uint8_t status=0;
	transfer_data(R_REGISTER(STATUS_REG_ADDR), &status, 1);
	return status;
}
static void transfer_data(uint8_t command, uint8_t *data, uint8_t size){
	CSN_PIN_LOW();
	SPI_transaction(command);
	for(uint8_t i = 0; i < size; i++){
		data[i] = SPI_transaction(data[i]);
	}
	CSN_PIN_HIGH();
}
static void clear_status_flags(void){
	uint8_t status = (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT);
	transfer_data(W_REGISTER(STATUS_REG_ADDR), &status, 1);
}
void nRF24L01_init(volatile uint8_t *const port_addr, uint8_t ce_pin, uint8_t csn_pin){
	nRF24L01_port_addr = port_addr;
	volatile uint8_t* nRF24L01_ddr_addr;
	nRF24L01_ddr_addr = (volatile uint8_t*)(port_addr + GPIO_DDR_ADDR_OFFSET);
	CE_PIN = ce_pin;
	CSN_PIN = csn_pin;
	*nRF24L01_ddr_addr |= (1 << CE_PIN) | (1 << CSN_PIN);
	CE_PIN_LOW();
	CSN_PIN_HIGH();
	_delay_ms(3000);//long delay for more stable voltage
}
void nRF24L01_open_pipe(uint8_t pipe, uint8_t *pipe_addr, uint8_t channel, uint8_t PA){
	selected_pipe = pipe;
	uint8_t pipe_address[5] = {0};
	
	uint8_t temp_buff = 0;
	temp_buff = (1  << EN_CRC) | (1 << CRCO);
	transfer_data(W_REGISTER(CONFIG_REG_ADDR), &temp_buff, 1);

	temp_buff = EN_ALL_RX_ENAA;
	transfer_data(W_REGISTER(EN_AA_REG_ADDR), &temp_buff, 1);

	temp_buff = ADDRESS_WIDTH;
	transfer_data(W_REGISTER(SETUP_AW_REG_ADDR), &temp_buff, 1);
	
	temp_buff = _6mS_ARD_15_ARC;
	transfer_data(W_REGISTER(SETUP_RETR_REG_ADDR), &temp_buff ,1);
	
	temp_buff = channel;
	transfer_data(W_REGISTER(RF_CH_REG_ADDR), &temp_buff, 1);
	
	temp_buff = (DEFAULT_DR_1Mbps | PA);
	transfer_data(W_REGISTER(RF_SETUP_REG_ADDR), &temp_buff, 1);
	
	clear_status_flags();
	
	for(uint8_t i = 0; i < ADDRESS_WIDTH; i++)
	pipe_address[i] = pipe_addr[i];
	transfer_data(W_REGISTER(RX_ADDR_P0_REG_ADDR + selected_pipe), pipe_address, 5);
	
	for(uint8_t i = 0; i < ADDRESS_WIDTH; i++)
	pipe_address[i] = pipe_addr[i];
	transfer_data(W_REGISTER(TX_ADDR_REG_ADDR), pipe_address, 5);
	
	temp_buff = (1 << selected_pipe);
	transfer_data(W_REGISTER(DYNPD_REG_ADDR), &temp_buff, 1);
	
	temp_buff = (1 << EN_DPL);
	transfer_data(W_REGISTER(FEATURE_REG_ADDR), &temp_buff, 1);
	
	transfer_data(FLUSH_TX,0,0);
	transfer_data(FLUSH_RX,0,0);
	
	transfer_data(R_REGISTER(CONFIG_REG_ADDR), &temp_buff, 1);
	temp_buff |= (1 << PWR_UP);
	transfer_data(W_REGISTER(CONFIG_REG_ADDR), &temp_buff, 1);
	_delay_ms(POWER_UP_DELAY);
	RX_IS_NOT_LISTENING();
}
void nRF24L01_listen(void){
	if(RX_LISTENING_STATE()){
		RX_IS_LISTENING();
		uint8_t temp_buff;
		temp_buff = (1 << selected_pipe);
		transfer_data(W_REGISTER(EN_RXADDR_REG_ADDR), &temp_buff, 1);
		transfer_data(R_REGISTER(CONFIG_REG_ADDR),&temp_buff,1);
		temp_buff |= (1 << PRIM_RX);
		transfer_data(W_REGISTER(CONFIG_REG_ADDR),&temp_buff,1);
		CE_PIN_HIGH();
		_delay_us(RX_SETTLING_DELAY);
	}
}
uint8_t nRF24L01_available(void){
	if(get_status_reg()&(1 << RX_DR)){
		clear_status_flags();
		uint8_t temp_buff;
		temp_buff = 0;
		transfer_data(W_REGISTER(EN_RXADDR_REG_ADDR), &temp_buff, 1);
		CE_PIN_LOW();
		RX_IS_NOT_LISTENING();
		return 1;
	}
	return 0;
}
uint8_t nRF24L01_payload_width(void){
	uint8_t payload_width = 0;
	transfer_data(R_RX_PL_WID, &payload_width, 1);
	return payload_width;
}
void nRF24L01_payload(uint8_t buff[], uint8_t payload_width){
	transfer_data(R_RX_PAYLOAD, buff, payload_width);
}
uint8_t nRF24L01_transmit(uint8_t data[], uint8_t data_size){
	RX_IS_NOT_LISTENING();
	CE_PIN_LOW();
	flus_tx();
	flus_rx();
	clear_status_flags();
	uint8_t buff[data_size];
	for(uint8_t i = 0; i < data_size; i++)
	buff[i] = data[i];
	uint8_t config = 0;
	transfer_data(R_REGISTER(CONFIG_REG_ADDR), &config, 1);
	config &= ~(1 << PRIM_RX);
	transfer_data(W_REGISTER(CONFIG_REG_ADDR), &config, 1);
	transfer_data(W_TX_PAYLOAD, buff, data_size);
	CE_PIN_HIGH();
	_delay_us(15);
	CE_PIN_LOW();
	uint8_t status;
	do
	{
		status = get_status_reg();
		if(MAX_RT_FLAG_IS_HIGH(status)) return 0;
	} while (!TX_DS_FLAG_IS_HIGH(status));
	return 1;
}
void nRF24L01_data_rate(uint8_t data_rate){
	uint8_t setup_reg_buff;
	transfer_data(R_REGISTER(RF_SETUP_REG_ADDR), &setup_reg_buff, 1);
	setup_reg_buff |= data_rate;
	transfer_data(W_REGISTER(RF_SETUP_REG_ADDR), &setup_reg_buff, 1);
}
