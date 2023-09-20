#if !defined(__LIB_MY_FIFO__)
#define __LIB_MY_FIFO__
/*
 * ***********************************************************************************************************
 * File Name: libmyfifo.h
 * Project: Learning_Code
 * File Created: 20-09-2023  09:16:49:AM
 * Author: KhangKT
 * AuthorEmail: khangkieutrong@gmail.com
 * ***********************************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fifo_node
{
	void *data;
	int size;
	struct fifo_node *next;
} node_t;

typedef struct fifo_queue
{
	int maxSize;
	int currentSize;
	node_t *first;
	node_t *last;
} queue_t;

/**
 * @brief
 * Create and return the queue
 * @param maxSize
 * @return queue_t*
 */
queue_t *myFifoInit(int maxSize);

/**
 * @brief
 * Enqueue the data into queue
 * @param queue
 * @param[in] data
 * @param[in] dataSize
 * @return 0 : success, minus : fail
 */
int myFifoSend(queue_t *queue, void *data, int dataSize);

/**
 * @brief
 * Return the data from the queue and free up all the internally allocated memory but user have to free the returning data pointer
 * @param queue
 * @param[out] dataSize
 * @return void* data
 */
void *myFifoReceive(queue_t *queue, int *dataSize);

/**
 * @brief
 * destory the queue (free all the memory associate with the queue even the data)
 *
 * @param queue
 * @return 0 : success, minus : fail
 */
int myFifoFree(queue_t *queue);

/**
 * @brief
 * If que is empty return 1, else return 0
 * @param queue
 * @return int
 */
int myFifoEmpty(queue_t *queue);

/**
 * @brief
 * If que is full return 1, else return 0
 * @param queue
 * @return int
 */
int myFifoFull(queue_t *queue);

#endif // __LIB_MY_FIFO__
