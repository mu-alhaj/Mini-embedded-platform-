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
 * 			huart : pointer to uart to receive data from.
 * 			cmdq : command queue pointer to save incoming commands into.
 * return : -
 * */
void serial_uart_init(  UART_HandleTypeDef *huart, tCmdqueue* cmdq );

/*
 * desc   :	start receiving data via uart.
 * param  : -
 * return : 0 if succeed.
 * */
uint8_t serial_uart_receiveToIdle( );

/*
 * desc   :	let command handler to register call backs to notified when new commands are available.
 * param  :
 * 			cb : function pointer
 * return : 0 if succeed.
 * */
void serial_uart_registerCB( void (*pCB)(void) );

#endif /* SERIAL_H_ */
