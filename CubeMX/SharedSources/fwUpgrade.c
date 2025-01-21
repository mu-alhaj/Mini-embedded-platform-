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
typedef void (application_t)(void);

typedef struct
{
    uint32_t		stack_addr;     // Stack Pointer
    application_t*	func_p;        // Program Counter
} JumpStruct;

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
	// Start address of your application
    uint32_t app_start_address = APP_START_ADD;

    // Reset vector
    uint32_t reset_handler = *(volatile uint32_t*)(app_start_address + 4);

    // Stack pointer
    uint32_t stack_pointer = (uint32_t) *((__IO uint32_t*) app_start_address );

    // Set application function.
    void (*app_reset_handler)(void) = (void (*)(void))( reset_handler );


	// Set the vector table base address to the application address

    // no need to set VTOR since USER_VECT_TAB_ADDRESS is defined in applications Gcc compiler/preprocessor
    // so it will be updated on the run.
	//SCB->VTOR = stack_pointer;

    // Set the stack pointer to the application's stack pointer
    __set_MSP(stack_pointer);

    // Call the application
    app_reset_handler();
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void fwUpgrade_setFlag( uint32_t flag )
{
	uint32_t set_flag = (uint32_t) flag;
	flash_erasePage( (uint32_t) APP_BOOT_FLAG_ADD, 1);
	flash_write( (uint32_t)APP_BOOT_FLAG_ADD, (uint8_t*)&set_flag, 4 );
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
