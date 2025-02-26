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
#include "cmdhandler.h"
#include "moduleId.h"
#include <string.h>


#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_flash.h"

//private defines.

#define HALF_WORD 	2
#define ONE_WORD 	4
#define DOUBLE_WORD 8

// command list
#define CMD_FLASH_WRITE				((unsigned char)0x01u)
#define CMD_FLASH_ERASE_PAGE		((unsigned char)0x02u)

// private data types.

// private data.

// private functions prototypes
void flash_cmd_handler( tCmdhandler_cmd inCmd );

// public function defines:

/************************************
 * Function
 * **********************************
 */
void flash_init()
{
	// register led commands with for the command handler to recognize.
	tCmdhandler_moduleCmdHandler cmd_handler = { .moduleId = MODULE_ID_FLASH, .funPtr = flash_cmd_handler };

	cmdhandler_registerModuleCmdHandler( cmd_handler );
}

/************************************
 * Function
 * **********************************
 */
uint8_t flash_write( uint32_t Address, uint8_t* pData, uint32_t size )
{
	// check if valid flash address.
	if ( Address < FLASH_EEPROM_START || Address > FLASH_END_ADD )
	{
		// return if address is within the boot area.
		return 1;
	}

	// check for valid input
	if ( pData == NULL && size == 0 )
	{
		return 1;
	}

	// Disable interrupts
	__disable_irq();

	HAL_FLASH_Unlock();
	uint32_t remaining_bytes = size;
	HAL_StatusTypeDef status = HAL_ERROR;
	uint32_t read_offset = 0;
	uint32_t write_offset = 0;
	uint8_t oneByte= 0;

	while( remaining_bytes )
	{
		uint16_t inData= 0xffff;
		uint32_t writing_address = Address + write_offset;

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

	HAL_FLASH_Lock();
	// Re-enable interrupts
	__enable_irq();

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
uint8_t flash_erasePage( uint32_t Address, uint32_t nrPages )
{
	// make sure we are not going to erase ourself
	if ( Address < FLASH_EEPROM_START )
	{
		printf( "trying to erase boot area 0x:%08x", Address );
		return 1;
	}

	// find page start address.
	uint32_t pageStartAddress = ( Address / FLASH_PAGE_SIZE ) * FLASH_PAGE_SIZE;

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

/************************************
 * Function
 * **********************************
 */
void flash_cmd_handler( tCmdhandler_cmd inCmd )
{
	if( inCmd.id.module !=  MODULE_ID_FLASH )
		return;

	switch( inCmd.id.cmd )
	{
		case CMD_FLASH_WRITE:
		{
			// extract parameter from data.
			// cmd.data : address 4 bytes + data cmd.dataSize - 4
			uint32_t address = 0;
			memcpy( &address, &inCmd.pData[0], 4);
			uint8_t* pData 	 = &inCmd.pData[4];

			// call write
			flash_write(address, pData, inCmd.dataSize - 4 );

			break;
		}
		case CMD_FLASH_ERASE_PAGE:
		{
			uint32_t address = 0;
			memcpy( &address, &inCmd.pData[0], 4 );
			flash_erasePage( address, 1 );
			break;
		}
		default:
			break;
	}

	return;
}





