/*
 * cmdhandler.c
 * 			this module should be able to start a serial port and parse
 * 			the received data into commands and data.
 * 			other modules should be able to register call backs with the
 * 			cmdhandler to be notified when a related commands or data are
 * 			received.
 * 			Received commands should look like the follows:
 *
 * 			 uint8	   		uint16		  uint16        uint8[]
 * 			new cmd		mouleid-cmdid 	 data size 		  data
 *
 *  Created on: Jan 10, 2025
 *      Author: wxj509
 */




/*
 * Includes
 * */
#include <string.h>  // Include this header for memcpy
#include "cmdhandler.h"
#include "circularBuffer.h"
#include "led.h"
#include "moduleId.h"

/*
 * Private defines.
 * */
#define CBUFF_DATA_SIZE 256
#define CMD_LIST_SIZE 	10


/*
 * Private data types.
 * */
struct
{
	tCmdqueue cmdq;
	tCmdhandler_moduleCmdHandler cmdhandler_list[CMD_LIST_SIZE];
}typedef tCmdhandler_vars;

/*
 * Private data.
 * */
static tCmdhandler_vars cmdhandler_vars;

/*
 * Private function prototypes.
 * */
void cmdhandler_processNewData();
/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void cmdhandler_init( UART_HandleTypeDef* huart )
{
	// create a data queue
	cmdqueue_init( &cmdhandler_vars.cmdq );

	// init uart.
	serial_uart_init(huart, &cmdhandler_vars.cmdq );
	serial_uart_receiveToIdle( huart );

	// to let us know to uart received new data;
	serial_uart_registerCB( cmdhandler_processNewData );

	// initialize cmd list.
	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		cmdhandler_vars.cmdhandler_list[i].moduleId	= MODULE_ID_NONE;
		cmdhandler_vars.cmdhandler_list[i].funPtr 		= NULL;
	}
	return;
}

uint8_t cmdhandler_registerModuleCmdHandler( tCmdhandler_moduleCmdHandler handler )
{
	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		if ( cmdhandler_vars.cmdhandler_list[i].moduleId == MODULE_ID_NONE )
		{
			cmdhandler_vars.cmdhandler_list[i].moduleId = handler.moduleId;
			cmdhandler_vars.cmdhandler_list[i].funPtr 	 = handler.funPtr;
			return 0;
		}
	}

	// if we looped through the whole list without finding an empty slot.
	return 1;
}
/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void cmdhandler_processNewData()
{
	tCmdhandler_cmd* pCmd;

	if ( 1 == cmdqueue_pop( &cmdhandler_vars.cmdq, &pCmd ) )
		return;


	// send the command to the relevant module.

	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		if ( cmdhandler_vars.cmdhandler_list[i].funPtr != NULL && cmdhandler_vars.cmdhandler_list[i].moduleId == pCmd->id.module )
		{
			cmdhandler_vars.cmdhandler_list[i].funPtr( *pCmd );
			cmdqueue_freeCmd( pCmd );
		}
	}

	return;
}
