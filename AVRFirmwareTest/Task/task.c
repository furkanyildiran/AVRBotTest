#include "task.h"

static volatile uint32_t counter;
static Tasks_t task;

ISR(TIMER1_COMPA_vect){
	counter++;
	Tasks_execute();
}

void Task_add(task_fn_ptr func){
	task.task_fn[task.task_number]=func;
	task.task_number++;
}
void Tasks_execute(void){
	for (uint8_t i=0; i < task.task_number; i++){
		task.task_fn[i]();
	}
}
/*getMs can be used as millis() func*/
uint32_t getMs(void){
	uint32_t temp=0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		temp = counter;
	}
	return temp;
}
