/*
 * circularBuffer.h
 * This module is meant to be used by other modules. other modules should be able to create its own buffers,
 * and pass it to this module to be able to initiate and manipulate it.
 *  Created on: Dec 20, 2024
 *      Author: wxj509
 */

#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H_
#define CIRCULARBUFFER_CIRCULARBUFFER_H_

// Includes
#include <stdint.h>

// Public data types.
struct
{
	uint16_t capacity;			// maximum size of the pBuffer.
	uint16_t tail;			// index of last element +1 in buffer, always available to write.
	uint16_t head;			// index of first element in buffer
	uint8_t* pBuffer;
}typedef tCircularBuffer;


// Public function prototypes.

/*
 * initiate a circular buffer.
 * in parameters:
 * - data    : pointer to data array to be handled by the buffer.
 * - capacity: size of the data buffer.
 * return 0 if succeed, 1 otherwise.
 * */
uint8_t circularBuffer_init( tCircularBuffer* pBuffer, uint8_t* pData, uint16_t capacity );

/*
 * push data into the buffer.
 * in parameters:
 * - input: pointer to data array for the data to be pushed in.
 * - size : of the new data.
 * return 0 if succeed, 1 otherwise.
 * */
uint8_t circularBuffer_push( tCircularBuffer* pBuffer, uint8_t* pInData, uint16_t size );

/*
 * pop oldest data from the buffer.
 * in parameters:
 * - out : pointer to the data array for the popped data to be placed in.
 * - size: of the data that will be popped out
 * return 0 if succeed, 1 otherwise.
 * */
uint8_t circularBuffer_pop( tCircularBuffer* pBuffer, uint8_t* pOutData, uint16_t size );

/*
 * Size of the data stored in the buffer
 * in parameters:
 * - buffer: pointer to the circular buffer
 * return size of the data stored in the buffer.
 * */
uint16_t circularBuffer_getSize( tCircularBuffer* pBuffer );

/*
 * Check if the buffer is full
 * in parameters:
 * - buffer: pointer to the circular buffer
 * return 1 if true 0 otherwise.
 * */
uint16_t circularBuffer_isFull( tCircularBuffer* pBuffer );

/*
 * Check if the buffer is empty
 * in parameters:
 * - buffer: pointer to the circular buffer
 * return 1 if true 0 otherwise.
 * */
uint16_t circularBuffer_isEmepty( tCircularBuffer* pBuffer );

#endif /* CIRCULARBUFFER_CIRCULARBUFFER_H_ */
