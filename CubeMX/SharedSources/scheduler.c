/*
 * scheduler.c
 *
 *  Created on: Dec 12, 2024
 *      Author: wxj509
 */
#include "scheduler.h"


// Defines
#define SCHEDULER_MAX_NR_TASKS				10
#define SCHEDULER_MAX_NR_RUN_ONCE_TASKS		10

// private data types.
struct
{
	void (*pTask)();
	uint32_t delay;
	uint32_t lastExecutionTime;
}typedef tSchedulerTask;

struct
{
	void (*pTask)();
}typedef tSchedulerRunOnceTask;

struct
{
	tSchedulerTask taskList[SCHEDULER_MAX_NR_TASKS];
	tSchedulerRunOnceTask runOnceTaskList[SCHEDULER_MAX_NR_RUN_ONCE_TASKS];
	uint8_t nrOfTasks;
	uint8_t nrOfRunOnceTasks;
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

uint8_t scheduler_runTask( void (*pTask)(void) )
{
	for ( uint8_t i = 0; i < SCHEDULER_MAX_NR_RUN_ONCE_TASKS; i += 1 )
	{
		// search for available task.
		if ( schedulerVars.runOnceTaskList[i].pTask == NULL )
		{
			schedulerVars.runOnceTaskList[i].pTask = pTask;
			schedulerVars.nrOfRunOnceTasks += 1;
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
		// run once tasks:
		for ( uint8_t i = 0; i < SCHEDULER_MAX_NR_RUN_ONCE_TASKS; i += 1 )
		{
			// execute task
			if ( schedulerVars.runOnceTaskList[i].pTask != NULL )
			{
				schedulerVars.runOnceTaskList[i].pTask();
				// remove task from list:
				schedulerVars.runOnceTaskList[i].pTask = NULL;
				schedulerVars.nrOfRunOnceTasks -= 1;
			}

		}

		// repeated tasks:
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
