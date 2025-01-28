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
#include "crc.h"
#include "led.h"
/*
 * Private defines.
 * */
#define RX_BUF_SIZE	256
#define ACK		 	((unsigned char)0x06)
#define NACK	 	((unsigned char)0x15)
/*
 * Private data types.
 * */


struct
{
	UART_HandleTypeDef* pUart;
	tCmdqueue*			cmdq;
	uint8_t				pRxBuff[RX_BUF_SIZE];
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
uint32_t calculate_crc(uint8_t *data, uint32_t length);

/*
 * Public function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
void serial_uart_init(  UART_HandleTypeDef *huart, tCmdqueue* cmdq )
{
	serialVars.pUart  		= huart;
	serialVars.cmdq			= cmdq;

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



uint8_t confirm_crc()
{
	// extract crc from incoming data
	uint32_t received_crc = 0;
	uint32_t crcIx = serialVars.receivedSize - 4;
	memcpy( &received_crc, &serialVars.pRxBuff[crcIx], 4 );

	uint32_t calc_crc = crc_calculate( serialVars.pRxBuff, serialVars.receivedSize - 4  );

	if ( calc_crc == received_crc )
		return 0;
	else
		return 1;
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

		uint8_t res;
		if ( 0 == confirm_crc() )
		{
			// ack the received message.
			res = ACK;
			HAL_UART_Transmit( serialVars.pUart, &res, 1, HAL_MAX_DELAY );

			// copy in data to data buffer.
			cmdqueue_push( serialVars.cmdq, serialVars.pRxBuff );
			scheduler_pushTask( serialVars.pCmdHandlerCB );
			// toggle led to indicate receiving data
			scheduler_pushTask( led_run );
		}
		else
		{
			// reRequest
			res = NACK;
			HAL_UART_Transmit( serialVars.pUart, &res, 1, HAL_MAX_DELAY );
			res = 0;
		}

	}
	return;
}
