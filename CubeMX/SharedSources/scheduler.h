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
typedef  void (*funcPtr)(void);

/*
 * Public function prototypes.
 * */

/*
 * desc  : initialize the scheduler module.
 * param : -
 * return: -
 * */
void scheduler_init( void );

/*
 * desc  : adds task to the scheduler to be performed periodically.
 * param :
 * 		delay : how often to execute.
 * 		pTask : the task to be executed.
 * returns true if added successfully.
 * */
uint8_t scheduler_addTask( uint32_t delay, void (*pTask)(void) );

/*
 * desc  : adds task to the scheduler to be performed once.
 * 		   gets useful when you want to place a task to be run after leaving interrupt context.
 * param :
 * 		pTask : the task to be executed.
 * returns true if added successfully.
 * */
uint8_t scheduler_pushTask( void (*pTask)(void) );

/*
 * desc  : Start the scheduler to start running the tasks.
 * 		   NOTICE: this function does not return.
 * */
void scheduler_run( void );

#endif /* INC_SCHEDULER_H_ */
