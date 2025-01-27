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

/*
 * Private defines.
 * */
#define CMD_FW_UPGRADE_ERASE_APP		((unsigned char)0x01u)
#define CMD_FW_UPGRADE_PROGRAM_APP  	((unsigned char)0x02u)

/*
 * Private data types.
 * */


/*
 * Private data.
 * */

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
uint8_t fwUpgrade_verifyApp()
{
	uint8_t *data = (uint8_t*) APP_START_ADD;
	uint32_t crc = calculate_crc( data, 16131 );

	if ( crc == 0xffbd47d9 )		// TODO: shoudl be able to receive and spare crc from the user.
		return 1;
	else
		return 0;
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
		case CMD_FW_UPGRADE_PROGRAM_APP:
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
		default:
			break;
	}

	return;
}
