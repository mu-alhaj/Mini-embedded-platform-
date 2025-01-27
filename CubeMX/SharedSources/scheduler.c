/*
 * scheduler.c
 *
 * Other modules should be able to register task to be executed periodically by the scheduler.
 * Other modules should also be able to push tasks to be executed once by the scheduler, this is
 * mainly to avoid running tasks in interrupt context.
 *
 *  Created on: Dec 12, 2024
 *      Author: wxj509
 */
#include "scheduler.h"


// Defines
#define SCHEDULER_MAX_NR_TASKS				10
#define SCHEDULER_MAX_NR_RUN_ONCE_TASKS		20

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
	uint8_t head;
	uint8_t tail;
	uint8_t full;
	uint8_t empty;
	uint8_t size;
	tSchedulerRunOnceTask runOnceTaskList[SCHEDULER_MAX_NR_RUN_ONCE_TASKS];
}typedef tSchedulerRunOnceQueue ;

struct
{
	uint8_t nrOfTasks;
	uint8_t nrOfRunOnceTasks;
	tSchedulerTask taskList[SCHEDULER_MAX_NR_TASKS];
	tSchedulerRunOnceQueue RunOnceQueue;
}typedef tSchedulerVars;


static tSchedulerVars schedulerVars;

/*
 * Private function prototypes.
 * */
// only scheduler module should be able to pop tasks.
uint8_t scheduler_popTask( void (**pTask)(void) );

/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void scheduler_init( void )
{
	schedulerVars.nrOfTasks = 0;
	for ( uint8_t i = 0; i < SCHEDULER_MAX_NR_TASKS; i += 1 )
	{
		schedulerVars.taskList[i].pTask = NULL;
		schedulerVars.taskList[i].delay = 0;
		schedulerVars.taskList[i].lastExecutionTime = 0;
	}

	// init run once queue.
	schedulerVars.RunOnceQueue.head  = 0;
	schedulerVars.RunOnceQueue.tail  = 0;
	schedulerVars.RunOnceQueue.full  = 0;
	schedulerVars.RunOnceQueue.empty = 1;
	schedulerVars.RunOnceQueue.size  = 0;
	for ( uint8_t i = 0; i < SCHEDULER_MAX_NR_RUN_ONCE_TASKS; i += 1 )
	{
		schedulerVars.RunOnceQueue.runOnceTaskList[i].pTask = NULL;
	}
}

/*
 * ********************************************
 * 					function
 * ********************************************/
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
 * ********************************************
 * 					function
 * ********************************************/
uint8_t scheduler_pushTask( void (*pTask)(void) )
{
	// is queue full?
	if ( schedulerVars.RunOnceQueue.full )
		return 1;

	// if not, add task.
	schedulerVars.RunOnceQueue.runOnceTaskList[ schedulerVars.RunOnceQueue.tail ].pTask = pTask;

	// increase tail index and size.
	schedulerVars.RunOnceQueue.tail = ( schedulerVars.RunOnceQueue.tail + 1 ) % SCHEDULER_MAX_NR_RUN_ONCE_TASKS;
	schedulerVars.RunOnceQueue.size += 1;

	// if queue was empty, it is not now.
	if ( schedulerVars.RunOnceQueue.empty )
	{
		schedulerVars.RunOnceQueue.empty = 0;
	}

	// check if full and update full.
	if( schedulerVars.RunOnceQueue.size == SCHEDULER_MAX_NR_RUN_ONCE_TASKS )
	{
		schedulerVars.RunOnceQueue.full = 1;
	}

	return 0;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void scheduler_run( void )
{
	uint32_t now = 0;
	while( 1 )
	{
		// run once tasks:
		while ( !schedulerVars.RunOnceQueue.empty )
		{
			void (*pRunOnce)(void) = NULL;

			if ( 0 == scheduler_popTask( &pRunOnce ) )
				if ( pRunOnce != NULL )
					{
						pRunOnce();
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

/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t scheduler_popTask( void (**pTask)(void) )
{
	// is queue empty?
	if ( schedulerVars.RunOnceQueue.empty )
		return 1;

	// pick that oldest task.
	*pTask = schedulerVars.RunOnceQueue.runOnceTaskList[ schedulerVars.RunOnceQueue.head ].pTask;

	// update head index
	schedulerVars.RunOnceQueue.head = ( schedulerVars.RunOnceQueue.head + 1 ) % SCHEDULER_MAX_NR_RUN_ONCE_TASKS;
	schedulerVars.RunOnceQueue.size -= 1;

	// if it was full, it is not now
	if ( schedulerVars.RunOnceQueue.full == 1 )
	{
		schedulerVars.RunOnceQueue.full = 0;
	}

	// check if empty
	if ( schedulerVars.RunOnceQueue.size == 0 )
	{
		schedulerVars.RunOnceQueue.empty = 1;
	}
	return 0;
}


