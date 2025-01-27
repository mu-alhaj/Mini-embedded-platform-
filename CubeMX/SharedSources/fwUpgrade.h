/*
 * fwUpgrade.h
 *
 *  Created on: Jan 15, 2025
 *      Author: wxj509
 */

#ifndef FWUPGRADE_H_
#define FWUPGRADE_H_

/*
 * Includes
 * */
#include <stdint.h>

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
 * desc   : Initialize the firmware upgrade module
 * param  : -
 * return : -
 * */
void fwUpgrade_init();

/*
 * desc   : erases the application memory area before flashing a new one.
 * param  : -
 * return : 0 if succeed.
 * */
uint8_t fwUpgrade_eraseApp();

/*
 * desc   : signal the start of application programming
 * param  :
 * 		- size of the application according to user.
 * 		- crc of application according to user.
 * return : -
 * */
void fwUpgrade_programAppStart( uint32_t size, uint32_t crt );

/*
 * desc   : signal the application programming is done and the time for verification.
 * param  : -
 * return : -
 * */
void fwUpgrade_programAppEnd();

/*
 * desc   :	calculate the checksum of the application and compare it with the one sent by the user.
 * param  : -
 * return : 0 if succeed, 1 otherwise.
 * */
uint8_t fwUpgrade_verifyApp();


#endif /* FWUPGRADE_H_ */
