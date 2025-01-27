/*
 * fwUpgrade.c
 *
 *  Created on: Jan 15, 2025
 *      Author: wxj509
 */


/*
 * Includes
 * */
#include "fwUpgrade.h"
#include "moduleId.h"
#include "cmdhandler.h"
#include "flash.h"
#include "crc.h"
#include "eeprom.h"

/*
 * Private defines.
 * */
#define CMD_FW_UPGRADE_ERASE_APP		((unsigned char)0x01u)
#define CMD_FW_UPGRADE_PROG_APP			((unsigned char)0x02u)
#define CMD_FW_UPGRADE_PROG_APP_START  	((unsigned char)0x03u)
#define CMD_FW_UPGRADE_PROG_APP_END  	((unsigned char)0x04u)

/*
 * Private data types.
 * */
struct
{
	uint32_t appSize;
	uint32_t appCRC;
	uint8_t  appOk;
} typedef tFwUpgradeVars;

/*
 * Private data.
 * */
static tFwUpgradeVars fwUpgradeVars;

/*
 * Private function prototypes.
 * */
void fwUpgrade_cmd_handler( tCmdhandler_cmd inCmd );

/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void fwUpgrade_init()
{
	// register led commands with for the command handler to recognize.
	tCmdhandler_moduleCmdHandler cmd_handler = { .moduleId = MODULE_ID_FW_UPGRADE, .funPtr = fwUpgrade_cmd_handler };

	cmdhandler_registerModuleCmdHandler( cmd_handler );

	uint32_t appSize;
	uint32_t appCrc;
	if ( 0 == eeprom_getAppSize( &appSize ) )
	{
		fwUpgradeVars.appSize = appSize;
	}
	if ( 0 == eeprom_getAppCrc( &appCrc ) )
	{
		fwUpgradeVars.appCRC = appCrc;
	}

	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t fwUpgrade_eraseApp()
{
	uint32_t address 	= APP_START_ADD;
	uint32_t eraseArea 	= FLASH_END_ADD - APP_START_ADD;
	uint32_t nrPages   	= eraseArea / FLASH_PAGE_SIZE ;

	return flash_erasePage( address, nrPages );
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void fwUpgrade_programAppStart( uint32_t size, uint32_t crc )
{
	fwUpgradeVars.appSize 	= size;
	fwUpgradeVars.appCRC 	= crc;
	fwUpgradeVars.appOk 	= 0;

	// save size and crc received by the user to be used in future.
	eeprom_setAppCrc( fwUpgradeVars.appCRC );
	eeprom_setAppSize( fwUpgradeVars.appSize );
	eeprom_store();
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void fwUpgrade_programAppEnd()
{
	if ( 0 == fwUpgrade_verifyApp() )
	{
		fwUpgradeVars.appOk = 1;
	}
	else
	{
		fwUpgradeVars.appOk = 0;
	}
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t fwUpgrade_verifyApp()
{
	// this function will be used before the initialization of the module, it should not be dependent of the init function.
	uint32_t appSize = 0;
	uint32_t appCrc = 0;
	if ( 0 == eeprom_getAppSize( &appSize ) )
	{
		fwUpgradeVars.appSize = appSize;
	}
	if ( 0 == eeprom_getAppCrc( &appCrc ) )
	{
		fwUpgradeVars.appCRC = appCrc;
	}

	if ( fwUpgradeVars.appSize == 0 || fwUpgradeVars.appCRC == 0 )
		return 1;

	uint8_t *data = (uint8_t*) APP_START_ADD;
	uint32_t crc = crc_calculate( data, fwUpgradeVars.appSize );

	if ( crc == fwUpgradeVars.appCRC )
	{
		fwUpgradeVars.appOk = 1;
		return 0;
	}
	else
	{
		fwUpgradeVars.appOk = 0;
		return 1;
	}
}

/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void fwUpgrade_cmd_handler( tCmdhandler_cmd inCmd )
{
	// make sure the command is for us.
	if ( inCmd.id.module != MODULE_ID_FW_UPGRADE )
		return;

	switch( inCmd.id.cmd )
	{
		case CMD_FW_UPGRADE_ERASE_APP:
		{
			fwUpgrade_eraseApp();
			break;
		}
		case CMD_FW_UPGRADE_PROG_APP:
		{
			// extract parameter from data.
			// cmd.data : address 4 bytes + data cmd.dataSize - 4
			uint32_t address = 0;
			memcpy( &address, &inCmd.pData[0], 4);
			uint8_t* pData 	 = &inCmd.pData[4];

			// call write
			flash_write( address, pData, inCmd.dataSize - 4 );
			break;
		}
		case CMD_FW_UPGRADE_PROG_APP_START:
		{
			uint32_t size, crc;
			memcpy( &size, &inCmd.pData[0], 4);
			memcpy( &crc, &inCmd.pData[4], 4);
			fwUpgrade_programAppStart( size, crc );
			break;
		}
		case CMD_FW_UPGRADE_PROG_APP_END:
		{
			fwUpgrade_programAppEnd();
			break;
		}
		default:
			break;
	}

	return;
}
