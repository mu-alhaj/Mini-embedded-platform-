/*
 * scheduler.h
 *
 *  Created on: Dec 12, 2024
 *      Author: wxj509
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stm32f3xx_hal.h"

/*
 * Public defines
 * */

/*
 * Public data types.
 * */
//typedef functionPointer void (*pTask)(void);

/*
 * Public function prototypes.
 * */

void scheduler_init( void );

/*
 * desc  : adds task to the scheduler
 * param :
 * 		delay : how often to execute.
 * 		pTask : the task to be executed.
 * returns true if added successfully.
 * */
uint8_t scheduler_addTask( uint32_t delay, void (*pTask)(void) );

/*
 * desc  : ask the scheduler to run som task once.
 * 		   gets useful when you want to place a task to be run after leaving interrupt context.
 * param :
 * 		pTask : the task to be executed.
 * returns true if added successfully.
 * */
uint8_t scheduler_runTask( void (*pTask)(void) );

uint8_t scheduler_addTimer();

/*
 * desc  : Start the scheduler to start running the tasks.
 * */
void scheduler_run( void );

#endif /* INC_SCHEDULER_H_ */
