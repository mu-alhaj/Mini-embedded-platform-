/*
 * serial.h
 *			handles serial communication via uart.
 *  Created on: Jan 9, 2025
 *      Author: wxj509
 */

#ifndef SERIAL_H_
#define SERIAL_H_


/*
 * Includes
 * */
#include "cmdqueue.h"
#include "usart.h"

/*
 * Public defines
 * */

/*
 * Public data types.
 * */

/*
 * Public function prototypes.
 * */

/*
 * desc   :	set up serial uart.
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
void serial_uart_init(  UART_HandleTypeDef *huart, tCmdqueue* cmdq );

/*
 * desc   :	set up serial uart.
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
uint8_t serial_uart_receiveToIdle( );

/*
 * desc   :	let other modules to register call backs to be called by this module.
 * param  :
 * 			cb : function pointer
 * 			param2 :
 * return : 0 if succeed.
 * */
void serial_uart_registerCB( void (*pCB)(void) );

uint32_t calculate_crc(uint8_t *data, uint32_t length);

#endif /* SERIAL_H_ */
