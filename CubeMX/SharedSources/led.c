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
void led_toggle( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin )
{
	HAL_GPIO_TogglePin( GPIOx, GPIO_Pin );
	return;
}


void led_run()
{
	led_toggle( LD2_GPIO_Port, LD2_Pin);
}

/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
