/*
 * cmdhandler.c
 * 			this module should be able to start a serial port and parse
 * 			the received data into commands and data.
 * 			other modules should be able to register call backs with the
 * 			cmdhandler to be notified when a related commands or data are
 * 			received.
 * 			Received commands should look like the follows:
 *
 * 			 uint8	   uint8	  uint16        uint8[]
 * 			new cmd		cmd 	data size 		  data
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

// commands
#define CMD_NEW			((unsigned char)0xabu)

/*
 * Private data types.
 * */


/*
 * Private data.
 * */
static uint8_t cbuff_data[CBUFF_DATA_SIZE];
static tCircularBuffer CBuffer;
static tCmdhandler_cmd inCmd;
static tCmdhandler_moduleCmdHandler cmdhandler_list[CMD_LIST_SIZE];

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
	// create a circular buffer
	circularBuffer_init( &CBuffer, cbuff_data, CBUFF_DATA_SIZE );

	// init uart.
	serial_uart_init(huart, &CBuffer );
	serial_uart_receiveToIdle( huart );

	// to let us know to uart received new data;
	serial_uart_registerCB( cmdhandler_processNewData );

	// initialize cmd list.
	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		cmdhandler_list[i].moduleId	= MODULE_ID_NONE;
		cmdhandler_list[i].funPtr 		= NULL;
	}
	return;
}

uint8_t cmdhandler_registerModuleCmdHandler( tCmdhandler_moduleCmdHandler handler )
{
	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		if ( cmdhandler_list[i].moduleId == MODULE_ID_NONE )
		{
			cmdhandler_list[i].moduleId = handler.moduleId;
			cmdhandler_list[i].funPtr 	 = handler.funPtr;
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
	uint8_t oneByte 	= 0;
	uint16_t dataSize 	= 0;
	uint8_t cmd[2] 		= {0};
	// find new command:
	while( !circularBuffer_isEmepty(&CBuffer) && oneByte != (uint8_t)CMD_NEW )
	{
		circularBuffer_pop( &CBuffer, &oneByte, 1 );
	}

	if ( oneByte != (uint8_t)CMD_NEW )
	{
		// the buffer is empty and we did not found a new command.
		return;
	}

	// read command
	circularBuffer_pop( &CBuffer, cmd, 2 );
	inCmd.id.module = cmd[1];
	inCmd.id.cmd 	= cmd[0];

	// read data size
	circularBuffer_pop( &CBuffer, (uint8_t*)&dataSize, 2 );
	inCmd.dataSize = dataSize;

	// read data
	if ( dataSize != 0 )
	{
		if ( circularBuffer_getSize(&CBuffer) >= dataSize )
		{
			circularBuffer_pop( &CBuffer, &inCmd.data, dataSize );
		}
	}

	// to this point we have a command, either with data or without.

	// send the command to the relevant module.

	for( uint8_t i = 0; i < CMD_LIST_SIZE; i += 1 )
	{
		if ( cmdhandler_list[i].funPtr != NULL && cmdhandler_list[i].moduleId == inCmd.id.module )
		{
			cmdhandler_list[i].funPtr( inCmd );
		}
	}

	return;
}
