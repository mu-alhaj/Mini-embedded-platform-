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
 * desc   : not used.
 * param  : -
 * return : -
 * */
void fwUpgrade_programApp();

/*
 * desc   :	calculate the checksum of the application and compare it with the one sent by the user.
 * param  : -
 * return : 0 if succeed, 1 otherwise.
 * */
uint8_t fwUpgrade_verifyApp();


#endif /* FWUPGRADE_H_ */
