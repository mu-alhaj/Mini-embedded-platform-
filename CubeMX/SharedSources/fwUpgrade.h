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

#endif /* FWUPGRADE_H_ */
