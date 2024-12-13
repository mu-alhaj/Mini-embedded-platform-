/*
 * scheduler.h
 *
 *  Created on: Dec 12, 2024
 *      Author: wxj509
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stm32f3xx_hal.h"

// Defines

#define SCHEDULER_MAX_NR_TASKS	10

// public interface

void scheduler_init( void );

/*
 * desc  : adds task to the scheduler
 * param :
 * 		delay : how often to execute.
 * 		pTask : the task to be executed.
 * returns true if added successfully.
 * */
uint8_t scheduler_addTask( uint32_t delay, void (*pTask)(void) );

uint8_t scheduler_addTimer();

void scheduler_run( void );

#endif /* INC_SCHEDULER_H_ */
