/*
 * circularBuffer.h
 * This module is meant to be used by other modules. other modules should be able to create its own buffers,
 * and pass it to this module to be able to initiate and manipulate it.
 *  Created on: Dec 20, 2024
 *      Author: wxj509
 */

#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H_
#define CIRCULARBUFFER_CIRCULARBUFFER_H_

// Public data types.
struct
{
	uint16_t size;
	uint16_t end;
	uint16_t start;
	uint8_t* p_buffer;
}typedef tCircularBuffer;


// Public function prototypes.

/*
 * initiate a circular buffer.
 * in parameters:
 * - buffer
 * - size
 * return 0 if succeed, 1 otherwise.
 * */
uint8_t circularBuffer_init( tCircularBuffer* buffer, uint8_t* buffer, uint16_t size );

/*
 * push data into the buffer.
 * in parameters:
 * - input: pointer to data array for the data to be pushed in.
 * - size : of the new data.
 * return 0 if succeed, 1 otherwise.
 * */
uint8_t circularBuffer_push( tCircularBuffer* buffer, uint8_t* input, uint16_t size );

/*
 * pop oldest data from the buffer.
 * in parameters:
 * - out : pointer to the data array for the popped data to be placed in.
 * - size: of the data that will be popped out
 * return 0 if succeed, 1 otherwise.
 * */
uint8_t circularBuffer_pop( tCircularBuffer* buffer, uint8_t* out, uint16_t size );

/*
 * Size of the data stored in the buffer
 * in parameters:
 * - buffer: pointer to the circular buffer
 * return size of the data stored in the buffer.
 * */
uint16_t circularBuffer_filledSize( tCircularBuffer* buffer );



#endif /* CIRCULARBUFFER_CIRCULARBUFFER_H_ */
