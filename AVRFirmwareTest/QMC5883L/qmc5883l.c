#include "qmc5883l.h"

static struct KALMAN kx = {0,1,0}, ky = {0,1,0}, kz = {0,1,0};
static int16_t x,y,z;
void write_reg_byte(uint8_t reg_addr, uint8_t reg_val){
	twi_send_start();
	twi_send_address(QMC_ADDRESS, TWI_WRITE);
	twi_send_byte_with_nack(reg_addr);
	twi_send_byte_with_nack(reg_val);
	twi_send_stop();
}

void qmc_init(uint8_t osr, uint8_t rng, uint8_t odr, uint8_t intrpt){
	uint8_t control1_val = (osr << 6) | (rng << 4) | (odr << 2) | QMC_MODE_CONTINUOUS;
	uint8_t control2_val = (1 << 6 ) | intrpt;
	write_reg_byte(QMC_CONTOL1_REG, control1_val);
	write_reg_byte(QMC_CONTOL2_REG, control2_val);
	write_reg_byte(QMC_SETPRD_REG, 1);              //recommended setting by qmc datasheet
}

void qmc_read_axis(void){
	int16_t data[7] = {0};
	twi_send_start();
	twi_send_address(QMC_ADDRESS, TWI_WRITE);
	twi_send_byte_with_nack(QMC_X_LSB_REG);
	twi_send_start();
	twi_send_address(QMC_ADDRESS, TWI_READ);

	for(uint8_t i = 0; i < 6; i++){
		data[i] = twi_read_byte_ret_ack();
	}
	data[6] = twi_read_byte_ret_nack();
	twi_send_stop();
	
	x = (data[1] << 8) | data[0];
	y = (data[3] << 8) | data[2];
	z = (data[5] << 8) | data[4];
	
	if (twi_control_ovf()){
		twi_master_reset();
		x = 0;
		y = 0;
		z = 0;
	}
	x = kalman_calculate(&kx, x, QMC_NOISE_VARIANCE, 10);
	y = kalman_calculate(&ky, y, QMC_NOISE_VARIANCE, 10);
	z = kalman_calculate(&kz, z, QMC_NOISE_VARIANCE, 10);
	x = (x - QMC_xoffset);
	y = (y - QMC_yoffset);
	z = (z - QMC_zoffset);
	x = x * QMC_x_scale;
	y = y * QMC_y_scale;
	z = z * QMC_z_scale;
}
int16_t qmc_getx(){
	return x;
}
int16_t qmc_gety(){
	return y;
}
int16_t qmc_getz(){
	return z;
}
void qmc_soft_reset(void){
	write_reg_byte(QMC_CONTOL2_REG, (1<<7));
}