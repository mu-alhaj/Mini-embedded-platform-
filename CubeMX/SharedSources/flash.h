/*
 * flash.h
 *
 *  Created on: Jan 7, 2025
 *      Author: wxj509
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

// Includes
#include <stdint.h>
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_flash_ex.h"	// to get page size

// Public defines
#define BOOT_START_ADD 0x8000000
#define APP_START_ADD  0x8040000	// 128 pages from base/boot start
#define FLASH_END_ADD  0x8080000	// 128 pages from app start

#define FLASH_EEPROM_START ( APP_START_ADD - FLASH_PAGE_SIZE )	// reserve the last page of boot area for the simulated eeprom
#define FLASH_EEPROM_END ( APP_START_ADD )

// Public data types.

// Public function prototypes.

void flash_init();

/*
 * write data to flash.
 * this function can only handle uint16 aligned data.
 * make sure the area you want to write is already erased.
 * in parameters:
 * - Address: Address in flash memory to write to.
 * - Data: pointer to data to be written.
 * - Size: data size.
 * return 0 if succeed, 1 otherwise.
 * */

uint8_t flash_write( uint32_t Address, uint8_t* pData, uint32_t size );

/*
 * read data from flash.
 * in parameters:
 * - Address: Address in flash memory to read from.
 * - Data: pointer to save read data to.
* - Data: data size.
 * return 0 if succeed, 1 otherwise.
 * */

uint8_t flash_read(uint32_t Address, uint8_t* pData, uint32_t size);

/*
 * erase specific flash page that contains the address required.
 * in parameters:
 * - Address: Address in flash to erase.
 * - nrPages: number of pages to be erased.
 * return 0 if succeed, 1 otherwise.
 * */

uint8_t flash_erasePage(uint32_t Address, uint32_t nrPages);

#endif /* INC_FLASH_H_ */
