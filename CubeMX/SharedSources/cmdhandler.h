/*
 * cmdhandler.h
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
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
void cmdhandler_init( UART_HandleTypeDef* huart );

/*
 * desc   : Other modules will be able to register call backs with the
 * 			cmdhandler to be notified when needed.
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
uint8_t cmdhandler_registerModuleCmdHandler( tCmdhandler_moduleCmdHandler cmdhandler);


#endif /* CMDHANDLER_H_ */
