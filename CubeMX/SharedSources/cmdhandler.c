/*
 * cmdhandler.c
 * 			this module should be able to start a serial port and re-direct
 * 			the received commands to the relevant modules to be executed.
 * 			other modules should be able to register call backs with the
 * 			cmdhandler to be notified when a related commands or data are
 * 			received.
 *
 * 			Received commands should look like:
 *
 * 			 uint8	   		uint16		  uint16        uint8[]		uint32
 * 			new cmd		mouleid-cmdid 	 data size 		  data		  crc
 *
 *  Created on: Jan 10, 2025
 *      Author: wxj509
 */




/*
 * Includes
 * */
#include <string.h>  // Include this header for memcpy
#include "cmdhandler.h"
#include "moduleId.h"

/*
 * Private defines.
 * */
#define CMD_LIST_SIZE 	10			// number of command handlers from other modules that can be registered by the cmdhandler.

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

/*
 * desc   : Reads commands from the command queue and redirect them to the respective modules.
 * param  : -
 * return : -
 * */
void cmdhandler_redirectCmds();
/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void cmdhandler_init( UART_HandleTypeDef* huart )
{
	// create a commands queue
	cmdqueue_init( &cmdhandler_vars.cmdq );

	// set up uart port.
	serial_uart_init(huart, &cmdhandler_vars.cmdq );
	serial_uart_receiveToIdle( huart );

	// to let us know to uart received new data;
	serial_uart_registerCB( cmdhandler_redirectCmds );

	// initialize cmd handlers list.
	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		cmdhandler_vars.cmdhandler_list[i].moduleId		= MODULE_ID_NONE;
		cmdhandler_vars.cmdhandler_list[i].funPtr 		= NULL;
	}
	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t cmdhandler_registerModuleCmdHandler( tCmdhandler_moduleCmdHandler handler )
{
	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		// find empty handler.
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
void cmdhandler_redirectCmds()
{
	tCmdhandler_cmd* pCmd;

	// if there is commands in queue, pop the latest.
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
		else
		{
			// commands module is unknown for us, free the cmd.
			cmdqueue_freeCmd( pCmd );
		}
	}

	return;
}
