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
	uint32_t read_offset = 0;
	uint32_t write_offset = 0;
	uint8_t oneByte= 0;
	while( remaining_bytes )
	{
		uint64_t inData= 0xffffffffffffffff;
		uint32_t writing_address = Address + write_offset;
		// write double words as long it is possible.
		if ( remaining_bytes >= DOUBLE_WORD )
		{
			memcpy (&inData, &pData[read_offset], DOUBLE_WORD);
			status = HAL_FLASH_Program( FLASH_TYPEPROGRAM_DOUBLEWORD, writing_address, inData );
			if ( status == HAL_OK )
			{
				remaining_bytes -= DOUBLE_WORD;
				read_offset 	+= DOUBLE_WORD;
				write_offset	+= DOUBLE_WORD;
			}
		}
		// then write single word
		else if ( remaining_bytes >= ONE_WORD )
		{
			memcpy (&inData, &pData[read_offset], ONE_WORD);
			status = HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD, writing_address, inData );
			if ( status == HAL_OK )
			{
				remaining_bytes -= ONE_WORD;
				read_offset 	+= ONE_WORD;
				write_offset	+= ONE_WORD;
			}
		}
		// lastly, write half word
		else
		{
			if ( remaining_bytes >= HALF_WORD )
				memcpy (&inData, &pData[read_offset], HALF_WORD);
			else
			{
				// if there is only one byte, move it to inData.
				memcpy (&inData, &pData[read_offset], 1);
				oneByte = 1;
			}
			status = HAL_FLASH_Program( FLASH_TYPEPROGRAM_HALFWORD, writing_address, inData );
			if ( status == HAL_OK )
			{
				if ( oneByte == 1 )
				{
					remaining_bytes -= 1;
					read_offset 	+= 1;
					write_offset	+= 1;
				}
				else
				{
					remaining_bytes -= HALF_WORD;
					read_offset 	+= HALF_WORD;
					write_offset	+= HALF_WORD;
				}

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
uint8_t flash_read(uint32_t address, uint8_t* pData, uint32_t size)
{
	memcpy( pData, address, size );
	return 0;
}

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
