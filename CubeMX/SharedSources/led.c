/*
 * led.c
 *
 *  Created on: Jan 9, 2025
 *      Author: wxj509
 */




/*
 * Includes
 * */
#include "led.h"
#include "cmdhandler.h"
/*
 * Private defines.
 * */
#define CMD_LED_SET		0x01u
#define CMD_LED_TOGGLE	0x02u
/*
 * Private data types.
 * */


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
void led_init()
{
	// register led commands with for the command handler to recognize.
	tCmdhandler_registerCmd cmd_set = { .funPtr = led_cmd_handler };

	cmdhandler_registerCmd( cmd_set );
	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
static uint8_t counter = 0;
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
void led_cmd_handler( void *param )
{
	tCmdhandler_cmd cmd;
	memcpy( &cmd, (uint8_t*)param, sizeof(tCmdhandler_cmd) );
	switch( cmd.cmd )
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

/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/



