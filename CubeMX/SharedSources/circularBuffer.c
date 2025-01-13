/*
 * circularBuffer.c
 *
 *  Created on: Dec 20, 2024
 *      Author: wxj509
 */

// Includes
#include "circularBuffer.h"
#include <string.h>

//private defines.

// private data types.

// private data.

// private functions prototypes

/*
 * gets the remaining capacity available to be utilized.
 * */
uint16_t get_availabe( tCircularBuffer* pBuffer );

// public function defines:

/************************************
 * Function
 * **********************************
 */
uint8_t circularBuffer_init( tCircularBuffer* pBuffer, uint8_t* pData, uint16_t capacity )
{
	// sanity check in parameters.
	if ( pBuffer == NULL || pData == NULL || capacity == 0 )
	{
		return 1;
	}

	// initialize the buffer
	pBuffer->capacity 		= capacity;
	pBuffer->head 			= 0;
	pBuffer->tail   		= 0;
	pBuffer->pBuffer 		= pData;
	memset( pBuffer->pBuffer, 1, pBuffer->capacity );

	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint8_t circularBuffer_push( tCircularBuffer* pCbuffer, uint8_t* pInData, uint16_t length )
{
	// sanity check in parameters.
	if( pCbuffer == NULL || pInData == NULL || pCbuffer->capacity < length )
	{
		return 1;
	}

	// check if there is enough place for the incoming data remaining in the buffer.
//	if ( get_availabe( pCbuffer ) < length )
//	{
//		// not enough
//		return 1;
//	}

	/*
	 * Buffer
	 * s: head, e: tail, d: data, n:none.
	 * ix 0 1 2 3 4 5 6 7 8 9
	 *    s e n n n n n n n n
	 *    s d d d d d e n n n
	 *    n n s d d d d e n n
	 *    d d d e n n n s d d
	 * */

	// do we need to loop over the buffer?
	uint16_t toTheEnd = pCbuffer->capacity - pCbuffer->tail;
	uint8_t* pDes = &(*pCbuffer).pBuffer[pCbuffer->tail];
	if ( toTheEnd < length )
	{
		// first copy from the end of the existing data to the end of the buffer
		memcpy( pDes, pInData, toTheEnd );
		// copy the reset of the inData from the beginning of the buffer.
		memcpy( (*pCbuffer).pBuffer, &pInData[toTheEnd], ( length - toTheEnd ) );
	}
	else
	{
		memcpy( pDes, pInData, length );
		//pBuffer->pBuffer[pBuffer->end] = pInData[0];
	}

	pCbuffer->tail = ( pCbuffer->tail + length ) % pCbuffer->capacity;

	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint8_t circularBuffer_pop( tCircularBuffer* pCbuffer, uint8_t* pOutData, uint16_t length )
{
	if ( circularBuffer_isEmepty(pCbuffer) )
		return 1;
	// do we need to loop over the buffer?
	uint16_t toTheEnd = pCbuffer->capacity - pCbuffer->head;
	uint8_t* pSource = &(*pCbuffer).pBuffer[pCbuffer->head];
	if ( toTheEnd < length )
	{
		// first copy from the end of the existing data to the end of the buffer
		memcpy( pOutData, pSource, toTheEnd );
		// copy the reset of the inData from the beginning of the buffer.
		memcpy( &pOutData[toTheEnd], (*pCbuffer).pBuffer, ( length - toTheEnd ) );
	}
	else
	{
		memcpy( pOutData, pSource, length );
	}

	pCbuffer->head = ( pCbuffer->head + length ) % pCbuffer->capacity;

	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint16_t circularBuffer_getSize( tCircularBuffer* pBuffer )
{
	uint16_t size = ( pBuffer->capacity + pBuffer->head - pBuffer->tail ) % pBuffer->capacity;
	return size;
}

/************************************
 * Function
 * **********************************
 */
uint16_t circularBuffer_isFull( tCircularBuffer* pBuffer )
{
	if ( get_availabe(pBuffer) == 0 )
		return 1;
	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint16_t circularBuffer_isEmepty( tCircularBuffer* pBuffer )
{
	if( pBuffer->head == pBuffer->tail )
		return 1;

	return 0;
}

// private function defines:

/************************************
 * Function
 * **********************************
 */
uint16_t get_availabe( tCircularBuffer* pBuffer )
{
	/*
	 * Buffer
	 * s: start, e: end, d: data, n:none.
	 * ix 0 1 2 3 4 5 6 7 8 9
	 *    s e n n n n n n n n 			available = ( 10 + 1 - 0 ) % 10 = 6	, keep in mind e points on empty element.
	 *    s d d d d d e n n n			available = ( 10 + 6 - 0 ) % 10 = 6
	 *    n n s d d d d e n n			available = ( 10 + 7 - 2 ) % 10 = 5
	 *    d d d e n n n s d d			available = ( 10 + 3 - 7 ) % 10 = 6
	 * */

	// if head and tail are both on 0 the whole buffer capacity if available
	if( pBuffer->head == 0 && pBuffer->tail == 0 )
	{
		return pBuffer->capacity;
	}

	// added capacity in the beginning to avoid negative modulus.
	uint16_t available = ( pBuffer->capacity + pBuffer->head - pBuffer->tail ) % pBuffer->capacity;
	return available;
}

