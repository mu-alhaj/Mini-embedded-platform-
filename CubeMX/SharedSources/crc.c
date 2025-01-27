/*
 * crc.c
 *
 *  Created on: Jan 27, 2025
 *      Author: wxj509
 */




/*
 * Includes
 * */
#include "crc.h"

/*
 * Private defines.
 * */

/*
 * Private data types.
 * */


/*
 * Private data.
 * */

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
uint32_t crc_calculate(uint8_t *data, uint32_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0x04C11DB7;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc ^ 0xFFFFFFFF;
}
/*
 * Private function definitions.
 * */

/*
 * ********************************************
 * 					function
 * ********************************************/
