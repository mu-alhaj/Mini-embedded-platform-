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
#define GO_APP	0xABB0ABB0
#define GO_BOOT	0xB001B001

/*
 * Public data types.
 * */

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
void fwUpgrade_init();

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
void fwUpgrade_eraseApp();

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
void fwUpgrade_programApp();

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
void fwUpgrade_jumpToApp();

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
void fwUpgrade_setFlag( uint32_t flag );

#endif /* FWUPGRADE_H_ */
