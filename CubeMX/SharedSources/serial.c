/*
 * serial.c
 *
 *  Created on: Jan 9, 2025
 *      Author: wxj509
 */



/*
 * Includes
 * */
#include "scheduler.h"
#include "led.h"
/*
 * Private defines.
 * */
#define RX_BUF_SIZE	64
/*
 * Private data types.
 * */


/*
 * Private data.
 * */
uint8_t uart_dma_rxBuf[RX_BUF_SIZE];
UART_HandleTypeDef* puart;
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
uint8_t serial_uart_receiveToIdle( UART_HandleTypeDef *huart )
{
	puart = huart;
	HAL_UARTEx_ReceiveToIdle_DMA( puart, uart_dma_rxBuf, RX_BUF_SIZE );

	  // not interested of half transfer interrupt.
	  __HAL_DMA_DISABLE_IT( puart->hdmarx, DMA_IT_HT );
	return 0;
}


/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if ( huart->Instance == USART2 )
	{
		// restart receiving data.
		HAL_UARTEx_ReceiveToIdle_DMA( puart, uart_dma_rxBuf, RX_BUF_SIZE);
		scheduler_runTask( led_run );
	}
	return;
}
