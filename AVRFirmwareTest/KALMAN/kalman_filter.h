#ifdef __cplusplus
extern "C"{
#endif
#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_
#include <stdint.h>
#include <avr/interrupt.h>

struct KALMAN{
	double previous_X;
	double previous_P;
	double K;		
};
int16_t kalman_calculate(struct KALMAN *kalman, int16_t val, int16_t R, int16_t Q);

#endif
#ifdef __cplusplus
}
#endif