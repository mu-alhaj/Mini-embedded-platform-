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
	tCmdhandler_cmd cmd_set = { .cmd= 0x0001, .funPtr = led_cmd_set };

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
	counter ++;
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
void led_cmd_set( void *param, uint16_t size )
{
//	uint8_t set = (uint8_t)param;
//	HAL_GPIO_WritePin( LD2_GPIO_Port, LD2_Pin, set);
	led_run();
	return;
}

/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/



