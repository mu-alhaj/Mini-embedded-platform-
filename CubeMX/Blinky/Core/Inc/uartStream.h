/*
 * uartStream.h
 *
 *  Created on: Dec 13, 2024
 *      Author: wxj509
 */

#ifndef INC_UARTSTREAM_H_
#define INC_UARTSTREAM_H_

#include <stdint.h>
#include "usart.h"

void uartStream_init();
uint8_t uartStream_sendU32( uint32_t nr );


#endif /* INC_UARTSTREAM_H_ */
