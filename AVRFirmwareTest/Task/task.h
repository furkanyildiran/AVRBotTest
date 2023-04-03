#ifdef __cplusplus
extern "C"{
	#endif
	#ifndef __TASK_H__
	#define __TASK_H__
	#include <stdint.h>
	#include "stepper.h"
	#include <util/atomic.h>
	#define MAX_TASK_NUM	5

	typedef void(*task_fn_ptr)(void);
	
	typedef struct{
		uint8_t task_number;
		task_fn_ptr task_fn[MAX_TASK_NUM];
	}Tasks_t;
	
	void Task_add(task_fn_ptr func);
	void Tasks_execute(void);
	uint32_t getMs(void);
	#endif
	#ifdef __cplusplus
};
#endif