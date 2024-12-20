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
 * gets the remaining size available to be utilized.
 * */
uint16_t get_availabe( tCircularBuffer* pBuffer );

// public function defines:

/************************************
 * Function
 * **********************************
 */
uint8_t circularBuffer_init( tCircularBuffer* pBuffer, uint8_t* pData, uint16_t size )
{
	// sanity check in parameters.
	if ( pBuffer == NULL || pData == NULL || size == 0 )
	{
		return 1;
	}

	// initialize the buffer
	pBuffer->size 		= size;
	pBuffer->start 	= 0;
	pBuffer->end   	= 0;
	pBuffer->pBuffer 	= pData;
	memset( pBuffer->pBuffer, 0, pBuffer->size );

	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint8_t circularBuffer_push( tCircularBuffer* pBuffer, uint8_t* pInData, uint16_t size )
{
	// sanity check in parameters.
	if( pBuffer == NULL || pInData == NULL || pBuffer->size < size )
	{
		return 1;
	}

	// check if there is enough place for the incoming data remaining in the buffer.
	if ( get_availabe( pBuffer ) < size )
	{
		// not enough
		return 1;
	}

	/*
	 * Buffer
	 * s: start, e: end, d: data, n:none.
	 * ix 0 1 2 3 4 5 6 7 8 9
	 *    s e n n n n n n n n
	 *    s d d d d d e n n n
	 *    n n s d d d d e n n
	 *    d d d e n n n s d d
	 * */

	// do we need to loop over the buffer?
	uint16_t toTheEnd = pBuffer->size - pBuffer->end;
	if ( toTheEnd < size )
	{
		// first copy from the end of the existing data to the end of the buffer
		memcpy( pBuffer->pBuffer[pBuffer->end], pInData, toTheEnd );
		// copy the reset of the inData from the beginning of the buffer.
		memcpy( pBuffer->pBuffer[0], pInData[toTheEnd], toTheEnd );
	}
	else
	{
		memcpy( pBuffer->pBuffer[pBuffer->end], pInData, size );
	}

	pBuffer->end = ( pBuffer->end + size ) % pBuffer->size;

	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint8_t circularBuffer_pop( tCircularBuffer* pBuffer, uint8_t* pOutData, uint16_t size )
{
	return 0;
}

/************************************
 * Function
 * **********************************
 */
uint16_t circularBuffer_filledSize( tCircularBuffer* pBuffer )
{
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

	// if start and end are both on 0 the whole buffer size if available
	if( pBuffer->start == 0 && pBuffer->end == 0 )
	{
		return pBuffer->size;
	}

	// added size in the beginning to avoid negative modulus.
	uint16_t available = ( pBuffer->size + pBuffer->end - pBuffer->start ) % pBuffer->size;
	return available;
}

