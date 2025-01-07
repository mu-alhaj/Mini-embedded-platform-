/*
 * flash.c
 *
 *  Created on: Jan 7, 2025
 *      Author: wxj509
 */


/*
 * 		Flash map
 * 0x8080000		flash end.
 * 0x8040000		application starts
 * 0x8000000		boot start
 * */


// Includes
#include "flash.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_flash.h"
#include "stm32f3xx_hal_flash_ex.h"	// to get page size

//private defines.

#define HALF_WORD 	2
#define ONE_WORD 	4
#define DOUBLE_WORD 8

// private data types.

// private data.

// private functions prototypes

// public function defines:

/************************************
 * Function
 * **********************************
 */
uint8_t flash_write( uint32_t Address, uint8_t* pData, uint32_t size )
{
	// check if valid flash address.
	if ( Address < APP_START_ADD || Address > FLASH_END_ADD )
	{
		// return if address is not in application flash area.
		return 1;
	}

	// check for valid input
	if ( pData == NULL && size == 0 )
	{
		return 1;
	}

	// erase flash area before writing to it.
	flash_erasePage( Address );

	HAL_FLASH_Unlock();
	uint32_t remaining_bytes = size;
	HAL_StatusTypeDef status = HAL_ERROR;
	uint64_t inData= 0xffffffffffffffff;
	memcpy (&inData, pData, size);
	while( remaining_bytes )
	{
		// write double words as long it is possible.
		if ( remaining_bytes >= DOUBLE_WORD )
		{
			status = HAL_FLASH_Program( FLASH_TYPEPROGRAM_DOUBLEWORD, Address, inData );
			if ( status == HAL_OK )
			{
				remaining_bytes -= DOUBLE_WORD;
			}
		}
		// then write single word
		else if ( remaining_bytes >= ONE_WORD )
		{
			status = HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD, Address, inData );
			if ( status == HAL_OK )
			{
				remaining_bytes -= ONE_WORD;
			}
		}
		// lastly, write half word
		else
		{
			status = HAL_FLASH_Program( FLASH_TYPEPROGRAM_HALFWORD, Address, inData );
			if ( status == HAL_OK )
			{
				remaining_bytes -= HALF_WORD;
			}
		}

	}

	HAL_FLASH_Lock();

	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint8_t flash_read(uint32_t Address, uint8_t* pData, uint32_t size);

/************************************
 * Function
 * **********************************
 */
uint8_t flash_erasePage( uint32_t Address )
{
	// find page start address.
	uint32_t pageStartAddress = ( Address / FLASH_PAGE_SIZE ) * FLASH_PAGE_SIZE;
	uint8_t nrPages = 1;


	FLASH_EraseInitTypeDef eraseInit;
	eraseInit.NbPages 		= nrPages;
	eraseInit.PageAddress 	= pageStartAddress;
	eraseInit.TypeErase 	= FLASH_TYPEERASE_PAGES;

	uint32_t pageError;

	HAL_FLASH_Unlock();
	HAL_StatusTypeDef status = HAL_FLASHEx_Erase( &eraseInit, &pageError);
	HAL_FLASH_Lock();
	if ( status != HAL_OK )
		return 1;

	return 0;
}

// private function defines:
