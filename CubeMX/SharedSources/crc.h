/*
 * crc.h
 *
 *  Created on: Jan 27, 2025
 *      Author: wxj509
 */

#ifndef CRC_H_
#define CRC_H_



/*
 * Includes
 * */
#include <stdint.h>

/*
 * Public defines
 * */

/*
 * Public data types.
 * */

/*
 * Public function prototypes.
 * */

/*
 * desc   : calculates crc32 for given data.
 * param  :
 * 			data: pointer to data.
 * 			length: length of data.
 * return : calculated crc.
 * */
uint32_t crc_calculate(uint8_t *data, uint32_t length);


#endif /* CRC_H_ */
