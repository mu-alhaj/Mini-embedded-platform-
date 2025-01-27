/*
 * cmdqueue.h
 *
 *  Created on: Jan 20, 2025
 *      Author: wxj509
 *
 *	This module should be able to receive data from serial uart, parse it into commands
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

#define CMD_NEW			((unsigned char)0xabu)	// new command key
#define CMD_Q_SIZE		10						// size of the command queue

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
 * desc   : initialize the queue owned/created by other modules
 * param  :
 * 			cmdq : pointer to the command queue to be initialized.
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_init( tCmdqueue* cmdq );

/*
 * desc   : De-initialize the que
 * param  :
 * 			cmdq : pointer to the command queue to be De-initialized.
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_deinit( tCmdqueue* cmdq );

/*
 * desc   :	takes in new data, parse it into command and push it to the command queue.
 * param  :
 * 			cmdq : queue for the command to be pushed into.
 * 			pData : data to be parsed and pushed.
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_push( tCmdqueue* cmdq, uint8_t *pData );

/*
 * desc   : pops commands from queue
 * param  :
 * 			cmdq : the queue commands will be popped from
 * 			pCmd : pointer to the popped command
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_pop( tCmdqueue* cmdq, tCmdhandler_cmd** pCmd );

/*
 * desc   :	frees commands memory, should be used after the command was executed.
 * param  :
 * 			pCmd : the command to be freed.
 * return : 0 if succeed.
 * */
uint8_t cmdqueue_freeCmd( tCmdhandler_cmd* pCmd );



#endif /* CMDQUEUE_H_ */
