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
void fwUpgrade_eraseApp()
{
	uint32_t address 	= APP_START_ADD;
	uint32_t eraseArea 	= FLASH_END_ADD - APP_START_ADD;
	uint32_t nrPages   	= eraseArea / FLASH_PAGE_SIZE ;

	flash_erasePage( address, nrPages );
	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void fwUpgrade_jumpToApp()
{
    // Function pointer to the application reset handler
    void (*app_reset_handler)(void);

    // De-initialize all peripherals, disable all interrupts
    HAL_DeInit();

    // Disable SysTick interrupt
    SysTick->CTRL = 0;

    // Set the vector table base address to the application address
    SCB->VTOR = APP_START_ADD;

    // Get the application reset handler address from the application's vector table
    app_reset_handler = (void (*)(void))(*((uint32_t *)(APP_START_ADD + 4)));

    // Set the main stack pointer to the application's stack pointer
    __set_MSP(*(uint32_t *)APP_START_ADD);

    // Jump to the application reset handler
    app_reset_handler();
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

	tCmdhandler_cmd cmd;
	memcpy( &cmd, (uint8_t*)&inCmd, sizeof(tCmdhandler_cmd) );

	switch( cmd.id.cmd )
	{
		case CMD_FW_UPGRADE_ERASE_APP:
		{
			fwUpgrade_eraseApp();
		}
		case CMD_FW_UPGRADE_PROGRAM_APP:
		{
			// extract parameter from data.
			// cmd.data : address 4 bytes + data cmd.dataSize - 4
			uint32_t address = 0;
			memcpy( &address, &cmd.data[0], 4);
			uint8_t* pData 	 = &cmd.data[4];

			// call write
			flash_write( address, pData, cmd.dataSize - 4 );
			break;
		}
		default:
			break;
	}

	return;
}
