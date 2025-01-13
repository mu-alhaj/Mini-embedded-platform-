/*
 * led.h
 *
 *  Created on: Jan 9, 2025
 *      Author: wxj509
 */

#ifndef LED_H_
#define LED_H_



/*
 * Includes
 * */
#include "gpio.h"

/*
 * Public defines
 * */

/*
 * Public data types.
 * */

/*
 * Public function prototypes.
 * */

void led_init();

/*
 * desc   :	toggle led
 * param  :
 * 			GPIOx 	 : port
 * 			GPIO_Pin : pin
 * */
void led_toggle( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin );

void led_run();

void led_cmd_set( void *param, uint16_t size );



#endif /* LED_H_ */
