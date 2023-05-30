/*
 * hcsr04.h
 *
 * Created: 30.05.2023 23:36:57
 *  Author: MONSTER
 */ 

#ifdef __cplusplus
extern "C"{
#endif
#ifndef __HCSR04_H__
#define __HCSR04_H__
#include "hcsr04_config.h"
#include <stdint.h>

void HCSR04_init(void);
__attribute__((noinline))uint16_t HCSR04_measure(void);

#endif /* HCSR04_H_ */
#ifdef __cplusplus
}
#endif