/*
 * uartStream.c
 *
 *  Created on: Dec 13, 2024
 *      Author: wxj509
 */

#include "uartStream.h"

void uartStream_init()
{
	// Initiate uart here if not initiated in main.c
}

uint8_t uartStream_sendU32( uint32_t nr )
{
	uint8_t out[6];	// start byte , nr, nr, nr, nr, end byte.
	out[0] = 's'; // start indicator
	memcpy( &out[1], &nr, 4 );
	out[5] = 'e'; // end indicator
	HAL_UART_Transmit(&huart2, out, 6, 10);
	return 0;
}


