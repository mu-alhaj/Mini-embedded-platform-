/*
 * eeprom.h
 *	This module should simulate an eeprom on a dedicated flash page to be able to save data over a restart.
 *  Created on: Jan 27, 2025
 *      Author: wxj509
 */

#ifndef EEPROM_H_
#define EEPROM_H_

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
 * desc   : Initialize the eeprom, find read and write address and read data from flash.
 * param  : -
 * return : -
 * */
void eeprom_init();

/*
 * desc   : erase whole eeprom.
 * param  : -
 * return : -
 * */
void eeprom_erase();

/*
 * desc   : save system restart flag to eeprom
 * param  :
 * 			flag : system restart flag.
 * return : -
 * */
void eeprom_setSystemRestartFlag( uint32_t flag);

/*
 * desc   :	get system restart flag from eeprom
 * param  :
 * 			flag : pointer to flag.
 * return : 0 if succeed.
 * */
uint8_t eeprom_getSystemRestartFlag( uint32_t *flag);

/*
 * desc   : save application size to eeprom
 * param  :
 * 			appSize : application size to be saved to eeprom
 * return : -
 * */
void eeprom_setAppSize( uint32_t appSize);

/*
 * desc   : get application size from eeprom
 * param  :
 * 			appSize : pointer to appSize.
 * return : 0 if succeed.
 * */
uint8_t eeprom_getAppSize( uint32_t *appSize);

/*
 * desc   : save application crc to eeprom
 * param  :
 * 			crc : application crc
 * return : 0 if succeed.
 * */
void eeprom_setAppCrc( uint32_t crc);

/*
 * desc   : get application crc from eeprom
 * param  :
 * 			crc : pointer to crc
 * return : 0 if succeed.
 * */
uint8_t eeprom_getAppCrc( uint32_t *crc);

/*
 * desc   : stores data from ram to flash.
 * param  : -
 * return : 0 if succeed.
 * */
void eeprom_store();


#endif /* EEPROM_H_ */
