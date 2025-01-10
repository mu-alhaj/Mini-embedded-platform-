/*
 * serial.c
 *
 *  Created on: Jan 9, 2025
 *      Author: wxj509
 */



/*
 * Includes
 * */
#include "serial.h"
#include "scheduler.h"
#include "led.h"
/*
 * Private defines.
 * */
#define RX_BUF_SIZE	128
/*
 * Private data types.
 * */
struct
{
	UART_HandleTypeDef* pUart;
	tCircularBuffer* 	pCBuff;
	uint8_t 			pRxBuff[RX_BUF_SIZE];
	uint8_t				receivedSize;
	void (*pCmdHandlerCB)(void);
}typedef tSerialVars;


/*
 * Private data.
 * */
static tSerialVars serialVars;

/*
 * Private function prototypes.
 * */
void pushRxToCBuff();
/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void serial_uart_init(  UART_HandleTypeDef *huart, tCircularBuffer* pCBuff )
{
	serialVars.pUart  = huart;
	serialVars.pCBuff = pCBuff;

	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
uint8_t serial_uart_receiveToIdle()
{
	HAL_UARTEx_ReceiveToIdle_DMA( serialVars.pUart, serialVars.pRxBuff, RX_BUF_SIZE );

	  // not interested of half transfer interrupt.
	  __HAL_DMA_DISABLE_IT( serialVars.pUart->hdmarx, DMA_IT_HT );
	return 0;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void serial_uart_registerCB( void (*pCB)(void) )
{
	serialVars.pCmdHandlerCB = pCB;
}

/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void pushRxToCBuff()
{
	circularBuffer_push( serialVars.pCBuff, serialVars.pRxBuff, serialVars.receivedSize );

	// notify cmdhandler about the new data.
	scheduler_runTask( serialVars.pCmdHandlerCB );
	return;
}

/*
 * ********************************************
 * 					function
 * ********************************************/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if ( huart->Instance == serialVars.pUart->Instance )
	{
		// restart receiving data.
		HAL_UARTEx_ReceiveToIdle_DMA( serialVars.pUart, serialVars.pRxBuff, RX_BUF_SIZE );
		serialVars.receivedSize = Size;

		// move received data from rxBuff to cBuffer out side of the interrupt context.
		scheduler_runTask( pushRxToCBuff );
	}
	return;
}
