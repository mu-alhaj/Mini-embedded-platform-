/*
 * cmdqueue.h
 *
 *  Created on: Jan 20, 2025
 *      Author: wxj509
 *
 *	This module should be able to receive data from serial uart and convert it into commands
 *	and place them in a queue to be processed later.
 *
 */

#ifndef CMDQUEUE_H_
#define CMDQUEUE_H_

/*
 * Includes
 * */
#include <stdint.h>
#include <string.h>


/*
 * Public defines
 * */
// new command key
#define CMD_NEW			((unsigned char)0xabu)
#define CMD_Q_SIZE		10

/*
 * Public data types.
 * */
struct{
	uint8_t module;
	uint8_t cmd;
} typedef tCmdhandler_id;

struct {
	tCmdhandler_id 		id;
	uint16_t 			dataSize;
	uint8_t* 			pData;
} typedef tCmdhandler_cmd;

struct {
	tCmdhandler_cmd* 	pCmdList[CMD_Q_SIZE];
    uint32_t 			head;
    uint32_t 			tail;
    uint32_t 			count;
}typedef tCmdqueue;

/*
 * Public function prototypes.
 * */

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_init( tCmdqueue* cmdq );

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_deinit( tCmdqueue* cmdq );

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_push( tCmdqueue* cmdq, uint8_t *pData );

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_pop( tCmdqueue* cmdq, tCmdhandler_cmd** pCmd );

/*
 * desc   :
 * param  :
 * 			param1 :
 * 			param2 :
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_freeCmd( tCmdhandler_cmd* pCmd );



#endif /* CMDQUEUE_H_ */
