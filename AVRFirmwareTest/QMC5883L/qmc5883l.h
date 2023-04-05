#ifdef __cplusplus
extern "C" {
	#endif

	#ifndef __QMC5883L_H__
	#define __QMC5883L_H__

	#include <avr/interrupt.h>
	#include <stdint.h>
	#include <avr/io.h>
	#include <stdio.h>
	#include <util/atomic.h>
	#include "twi.h"
	#include "kalman_filter.h"
	
	#define QMC_ADDRESS 0x0D
	#define QMC_X_LSB_REG 0x00
	#define QMC_X_MSB_REG 0x01
	#define QMC_Y_LSB_REG 0x02
	#define QMC_Y_MSB_REG 0x03
	#define QMC_Z_LSB_REG 0x04
	#define QMC_Z_MSB_REG 0x05
	#define QMC_STATUS_REG 0x06
	#define QMC_TMPTR_LSB_REG 0x07
	#define QMC_TMPTR_MSB_REG 0x08
	#define QMC_CONTOL1_REG 0x09
	#define QMC_CONTOL2_REG 0x0A
	#define QMC_SETPRD_REG 0x0B
	#define QMC_OSR_64 0b11
	#define QMC_OSR_128 0b10
	#define QMC_OSR_256 0b01
	#define QMC_OSR_512 0b00
	#define QMC_RNG_8G 0b01
	#define QMC_RNG_2G 0b00
	#define QMC_ODR_200HZ 0b11
	#define QMC_ODR_100HZ 0b10
	#define QMC_ODR_50HZ 0b01
	#define QMC_ODR_10HZ 0b00
	#define QMC_MODE_CONTINUOUS 0b01
	#define QMC_MODE_STANDBY 0b00
	#define QMC_SOFT_RESET 0x80
	#define QMC_DSBL_INTRPT 1
	#define QMC_ENBL_INTRPT 0
	#define QMC_NOISE_VARIANCE 3000
	#define QMC_xoffset 708
	#define QMC_yoffset -993
	#define QMC_zoffset -310
	#define QMC_x_scale 0.992380261
	#define QMC_y_scale 1.00755204
	#define QMC_z_scale 0.999817218
		
	void qmc_init(uint8_t osr, uint8_t rng, uint8_t odr, uint8_t enbl_intr);
	void qmc_read_axis(void);
	void qmc_soft_reset(void);
	uint8_t qmc_check_drdy(void);
	int16_t qmc_getx(void);
	int16_t qmc_gety(void);
	int16_t qmc_getz(void);

	#endif
	#ifdef __cplusplus
}
#endif