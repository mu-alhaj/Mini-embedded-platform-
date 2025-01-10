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
#include "cmdhandler.h"
#include "circularBuffer.h"
#include "led.h"

/*
 * Private defines.
 * */
#define CBUFF_DATA_SIZE 256

/*
 * Private data types.
 * */

/*
 * Private data.
 * */
static uint8_t cbuff_data[CBUFF_DATA_SIZE];
static tCircularBuffer CBuffer;

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
	return;
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
	led_run();
	return;
}
