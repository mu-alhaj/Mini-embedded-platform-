/*
 * systemRestart.h
 *
 *  Created on: Jan 27, 2025
 *      Author: wxj509
 */

#ifndef SYSTEMRESTART_H_
#define SYSTEMRESTART_H_



/*
 * Includes
 * */
#include <stdint.h>

/*
 * Public defines
 * */
#define GO_APP	0xABB0ABB0
#define GO_BOOT	0xB001B001

/*
 * Public data types.
 * */

/*
 * Public function prototypes.
 * */

/*
 * desc   : sets a flag in flash to tell boot if it should continue to app or stay in boot.
 * param  :flag
 * return : 0 if succeed.
 * */
void systemRestart_setFlag( uint32_t flag );

/*
 * desc   : gets flag from flash to tell boot if it should continue to app or stay in boot.
 * param  :flag
 * return : 0 if succeed.
 * */
void systemRestart_getFlag( uint32_t* flag );

/*
 * desc   : Jumps to the application.
 * param  : -
 * return : -
 * */
void systemRestart_jumpToApp();

/*
 * desc   : Perform a restart.
 * param  : -
 * return : -
 * */
void systemRestart_restart();

#endif /* SYSTEMRESTART_H_ */
