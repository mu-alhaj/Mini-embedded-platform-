/*
 * eeprom.c
 *
 *  Created on: Jan 27, 2025
 *      Author: wxj509
 */


/*
 * Includes
 * */
#include "eeprom.h"
#include "flash.h"

/*
 * Private defines.
 * */
#define EEPROM_KEY 0xABCDABCD
/*
 * Private data types.
 * */
struct
{
	uint32_t	secretKey;			// to recognize written address.
	uint32_t	systemRestartFlag;
	uint32_t    appSize;
	uint32_t    appCrc;
}typedef tEepromData;

struct
{
	uint8_t validReadBlock;
	uint8_t storeNeeded;
	uint32_t readAdd;
	uint32_t writeAdd;
}typedef tEepromVars;

/*
 * Private data.
 * */
static tEepromData eepromData;
static tEepromVars eepromVars;

/*
 * Private function prototypes.
 * */
uint8_t findEepromReadAdd( uint32_t* readAdd );
uint8_t findEepromWriteAdd( uint32_t* writeAdd);

/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void eeprom_init()
{
	eepromData.secretKey = EEPROM_KEY;

	uint32_t readAdd = 0;
	uint32_t writeAdd = 0;

	if ( 0 == findEepromReadAdd( &readAdd ) )
	{
		eepromVars.validReadBlock = 1;
		eepromVars.readAdd = readAdd;
		flash_read( eepromVars.readAdd, (uint8_t*)&eepromData, sizeof( tEepromData ) );
	}
	else
	{
		eeprom_erase();
		eepromVars.validReadBlock = 0;
		eepromVars.writeAdd = FLASH_EEPROM_START;
	}

	if ( 0 == findEepromWriteAdd( &writeAdd ) )
	{
		eepromVars.writeAdd = writeAdd;
	}
	else
	{
		// eeprom is full, or not been used yet. erase and re-write the block from ram if valid.
		eeprom_erase();
		if ( eepromVars.validReadBlock )
		{
			eepromVars.writeAdd = FLASH_EEPROM_START;
			eeprom_store();


		}

	}
	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void eeprom_erase()
{
	flash_erasePage( FLASH_EEPROM_START, 1);
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void eeprom_setSystemRestartFlag( uint32_t flag)
{
	if ( eepromData.systemRestartFlag != flag )
	{
		eepromData.systemRestartFlag = flag;
		eepromVars.storeNeeded = 1;
	}
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t eeprom_getSystemRestartFlag( uint32_t *flag)
{
	if ( eepromVars.validReadBlock )
	{
		*flag = eepromData.systemRestartFlag;
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void eeprom_setAppSize( uint32_t appSize)
{
	if ( eepromData.appSize != appSize )
	{
		eepromData.appSize = appSize;
		eepromVars.storeNeeded = 1;
	}
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t eeprom_getAppSize( uint32_t *appSize)
{
	if ( eepromVars.validReadBlock )
	{
		*appSize = eepromData.appSize;
		return 0;
	}
	else
	{
		return 1;
	}
}
/*
 * ********************************************
 * 					function
 * ********************************************/
void eeprom_setAppCrc( uint32_t crc)
{
	if ( eepromData.appCrc != crc )
	{
		eepromData.appCrc = crc;
		eepromVars.storeNeeded = 1;
	}
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t eeprom_getAppCrc( uint32_t *crc)
{
	if ( eepromVars.validReadBlock )
	{
		*crc = eepromData.appCrc;
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void eeprom_store()
{
	if ( eepromVars.storeNeeded )
	{
		// write data from ram struct to flash
		flash_write( eepromVars.writeAdd, (uint8_t*)&eepromData, sizeof( tEepromData ) );

		// update read and write addresses.
		findEepromReadAdd( &eepromVars.readAdd );
		findEepromWriteAdd( &eepromVars.writeAdd );
		eepromVars.storeNeeded = 0;
	}
	else
		return;
}

/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t findEepromReadAdd( uint32_t *readAdd )
{
	// find the last written data in eeprom.
	// first address of all eepromData saved to flash should be the secret key,
	// if no secret key was found, then the struct address before is wh

	uint32_t startAdd = FLASH_EEPROM_START;
	uint32_t key = * (uint32_t*) startAdd;

	while ( key == EEPROM_KEY )
	{
		startAdd += sizeof( tEepromData );
		if ( startAdd < FLASH_EEPROM_END )
		{
			key = * (uint32_t*) startAdd;
		}
		else
		{
			// came to the end of eeprom area without finding any valid data to read.
			return 1;
		}
	}

	// the last written struct is the one before the available one.
	if ( startAdd - sizeof( tEepromData ) >= FLASH_EEPROM_START )
	{
		*readAdd = startAdd - sizeof( tEepromData );
		return 0;
	}
	else
	{
		return 1;
	}

}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t findEepromWriteAdd( uint32_t *writeAdd )
{
	uint32_t startAdd = FLASH_EEPROM_START;
	uint32_t key = * (uint32_t*) startAdd;

	while ( key == EEPROM_KEY )
	{
		startAdd += sizeof( tEepromData );
		if ( startAdd < FLASH_EEPROM_END )
		{
			key = * (uint32_t*) startAdd;
		}
		else
		{
			// came to the end of eeprom area without finding any valid data to write
			return 1;
		}
	}

	// make sure this place is empty
	if ( key == 0xffffffff  )
	{
		*writeAdd = startAdd;
		return 0;
	}
	else
	{
		return 1;
	}


}
