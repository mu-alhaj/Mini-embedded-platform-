/*
 * systemRestart.c
 *
 *  Created on: Jan 27, 2025
 *      Author: wxj509
 */


/*
 * Includes
 * */
#include "systemRestart.h"
#include "eeprom.h"
#include "flash.h"
/*
 * Private defines.
 * */

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

/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void systemRestart_setFlag( uint32_t flag )
{
	eeprom_setSystemRestartFlag(flag);
	eeprom_store();
}

void systemRestart_getFlag( uint32_t* flag )
{
	eeprom_getSystemRestartFlag( flag );
	if( *flag == GO_APP )
	{
		// for demonstration:
		// invalidate application flag to stay in boot next time.
		systemRestart_setFlag( GO_BOOT );
	}

}

/*
 * ********************************************
 * 					function
 * ********************************************/
void systemRestart_jumpToApp()
{

	// Start address of your application
    uint32_t app_start_address = APP_START_ADD;

    // Reset handler
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
void systemRestart_restart()
{
	NVIC_SystemReset();
}
/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
