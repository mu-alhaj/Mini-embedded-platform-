/*
 * dataQ.c
 *
 *  Created on: Jan 20, 2025
 *      Author: wxj509
 */




/*
 * Includes
 * */
#include "cmdqueue.h"
#include <string.h>
#include <stdlib.h>

/*
 * Private defines.
 * */

/*
 * Private data types.
 * */


/*
 * Private data.
 * */

/*
 * Private function prototypes.
 * */

/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t cmdqueue_init( tCmdqueue* cmdq )
{

	cmdq->head = 0;
	cmdq->tail = 0;
	cmdq->count= 0;

    return 0;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t cmdqueue_deinit( tCmdqueue* cmdq )
{
    return 0;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t cmdqueue_push( tCmdqueue* cmdq, uint8_t *pData )
{
    if ( !pData || pData[0] != CMD_NEW )
    {
        return 1;
    }

    // create a new cmd and allocate memory for that.
    tCmdhandler_cmd* cmd = (tCmdhandler_cmd*)malloc(sizeof(tCmdhandler_cmd));

    // parse data into cmd

    cmd->id.module  = pData[2];
    cmd->id.cmd		= pData[1];

    memcpy( &cmd->dataSize, &pData[3], 2 );

	if ( cmd->dataSize != 0 )
	{
		cmd->pData = (uint8_t*) malloc( cmd->dataSize );
		memcpy( cmd->pData, &pData[5], cmd->dataSize );
	}
	else
	{
		cmd->pData = NULL;
	}

	cmdq->pCmdList[cmdq->tail] = cmd;

    cmdq->tail = (cmdq->tail + 1) % CMD_Q_SIZE;
    cmdq->count++;

    return 0;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t cmdqueue_pop( tCmdqueue* cmdq, tCmdhandler_cmd** pCmd )
{
    if ( cmdq->count == 0)
    {
        return 1;
    }

    *pCmd = cmdq->pCmdList[cmdq->head];
    cmdq->head = (cmdq->head + 1) % CMD_Q_SIZE;
    cmdq->count--;

    return 0;
}

uint8_t cmdqueue_freeCmd( tCmdhandler_cmd* pCmd )
{
	if( pCmd != NULL )
	{
		if ( pCmd->pData != NULL )
			free( pCmd->pData );
		free( pCmd );
	}
	return 0;
};
/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
