/*
 * cmdhandler.h
 *
 *	This module will create a command queue structure and pass it alongside a specific uart handle to the serial module,
 *	where from the command queue will be filled, the command will be redirected to the respective module to be executed.
 *	Other modules should be able to register its command handler, and the cmdhandler module will send related commands
 *	to that module.
 *
 *  Created on: Jan 10, 2025
 *      Author: wxj509
 */

#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_

/*
 * Includes
 * */
#include "stdint.h"
#include "serial.h"
#include "cmdqueue.h"

/*
 * Public defines
 * */

/*
 * Public data types.
 * */


// module command handler, used by other modules to connect a module id by a function.
struct{
	uint8_t moduleId;
	void (*funPtr)(tCmdhandler_cmd);
}typedef tCmdhandler_moduleCmdHandler;

/*
 * Public function prototypes.
 * */

/*
 * desc   : Initialize the command handler, by initializing a serial port and command queue.
 * param  :
 * 			huart : that point out the uart port that commands are coming from
 * return : -
 * */
void cmdhandler_init( UART_HandleTypeDef* huart );

/*
 * desc   : Other modules will be able to register call backs with the
 * 			cmdhandler to be notified when needed.
 * param  :
 * 			cmdhandler : the modules own command handler function pointer and module id.
 * return : 0 if succeed.
 * */
uint8_t cmdhandler_registerModuleCmdHandler( tCmdhandler_moduleCmdHandler cmdhandler);


#endif /* CMDHANDLER_H_ */
