/*
 * scheduler.c
 *
 *  Created on: Dec 12, 2024
 *      Author: wxj509
 */
#include "scheduler.h"



// private data types.
struct
{
	void (*pTask)();
	uint32_t delay;
	uint32_t lastExecutionTime;
}typedef tSchedulerTask;

struct
{
	tSchedulerTask taskList[SCHEDULER_MAX_NR_TASKS];
	uint8_t nrOfTasks;
}typedef tSchedulerVars;


static tSchedulerVars schedulerVars;


/*
 * function
 * */

void scheduler_init( void )
{
	schedulerVars.nrOfTasks = 0;
	for ( uint8_t i = 0; i < SCHEDULER_MAX_NR_TASKS; i += 1 )
	{
		schedulerVars.taskList[i].pTask = NULL;
		schedulerVars.taskList[i].delay = 0;
		schedulerVars.taskList[i].lastExecutionTime = 0;
	}
}

/*
 * function
 * */
uint8_t scheduler_addTask( uint32_t delay, void (*pTask)(void) )
{
	for ( uint8_t i = 0; i < SCHEDULER_MAX_NR_TASKS; i += 1 )
	{
		// search for available task.
		if ( schedulerVars.taskList[i].pTask == NULL )
		{
			schedulerVars.taskList[i].pTask = pTask;
			schedulerVars.taskList[i].delay = delay;
			schedulerVars.nrOfTasks += 1;
			return 1;
		}
	}
	// no available task was found
	return 0;
}

/*
 * function
 * */
void scheduler_run( void )
{
	uint32_t now = 0;
	while( 1 )
	{
		now = HAL_GetTick();
		for ( uint8_t i = 0; i < schedulerVars.nrOfTasks; i += 1 )
		{
			if ( now - schedulerVars.taskList[i].lastExecutionTime  >= schedulerVars.taskList[i].delay )
			{
				// execute task
				schedulerVars.taskList[i].pTask();
				schedulerVars.taskList[i].lastExecutionTime = now;
			}
		}
	}

}
