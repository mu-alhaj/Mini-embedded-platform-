/*
 * led.c
 *
 *  Created on: Jan 9, 2025
 *      Author: wxj509
 */




/*
 * Includes
 * */
#include <moduleId.h>
#include "led.h"
#include "cmdhandler.h"
#include <string.h>
/*
 * Private defines.
 * */
#define CMD_LED_SET		((unsigned char)0x01u)
#define CMD_LED_TOGGLE	((unsigned char)0x02u)
/*
 * Private data types.
 * */


/*
 * Private data.
 * */

/*
 * Private function prototypes.
 * */
void led_cmd_handler( tCmdhandler_cmd inCmd );
/*
 * Public function definitions.
 * */
/*
 * ********************************************
 * 					function
 * ********************************************/
void led_init()
{
	// register led commands with for the command handler to recognize.
	tCmdhandler_moduleCmdHandler cmd_handler = { .moduleId = MODULE_ID_LED, .funPtr = led_cmd_handler };

	cmdhandler_registerModuleCmdHandler( cmd_handler );
	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void led_toggle( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin )
{
	HAL_GPIO_TogglePin( GPIOx, GPIO_Pin );
	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void led_run()
{
	led_toggle( LD2_GPIO_Port, LD2_Pin);
}

/*
 * ********************************************
 * 					function
 * ********************************************/


/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void led_cmd_handler( tCmdhandler_cmd inCmd )
{
	// make sure the command is for us.
	if ( inCmd.id.module != MODULE_ID_LED )
		return;

	tCmdhandler_cmd cmd;
	memcpy( &cmd, (uint8_t*)&inCmd, sizeof(tCmdhandler_cmd) );

	switch( cmd.id.cmd )
	{
		case CMD_LED_SET:
		{
			uint8_t set = 0;// (uint8_t)param;
			memcpy(&set, &cmd.data, cmd.dataSize );
			HAL_GPIO_WritePin( LD2_GPIO_Port, LD2_Pin, set);
			break;
		}
		case CMD_LED_TOGGLE:
		{
			led_toggle( LD2_GPIO_Port, LD2_Pin);
			break;
		}
		default:
			break;
	}

	return;
}

