#include "kalman_filter.h"
#define calc_kalman_k(prev_p, R)        (prev_p / (prev_p + R))
#define calc_current_x(prev_x, k, val)  (prev_x + k*(val - prev_x))
#define calc_current_p(k, prev_p, q)    ((1 - k)*prev_p + Q)

int16_t kalman_calculate(struct KALMAN *kalman, int16_t val, int16_t R, int16_t Q){
	double current_X;
	double current_P;
	kalman->K = calc_kalman_k(kalman->previous_P, R);                    //(kalman->previous_P)/(kalman->previous_P + R);
	current_X = calc_current_x(kalman->previous_X, kalman->K, val);      //kalman->previous_X + kalman->K*(*axis_val - kalman->previous_X);
	current_P = calc_current_p(kalman->K, kalman->previous_P, Q);        //(1 - kalman->K)*kalman->previous_P + Q;
	kalman->previous_X = current_X;
	kalman->previous_P = current_P;
	return current_X;
}
