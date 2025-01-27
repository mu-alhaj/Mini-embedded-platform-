/*
 * moduleID.h
 *
 * This file will hold unique modules IDs used by command handler to be able
 * to redirect incoming commands to the respective modules.
 *
 *  Created on: Jan 14, 2025
 *      Author: wxj509
 */

#ifndef MODULEID_H_
#define MODULEID_H_

// one byte module id, this will be enough for 256 ids.
#define MODULE_ID_NONE			((unsigned char)0x00u)
#define MODULE_ID_LED   		((unsigned char)0x01u)
#define MODULE_ID_FLASH   		((unsigned char)0x02u)
#define MODULE_ID_FW_UPGRADE	((unsigned char)0x03u)

#endif /* MODULEID_H_ */
