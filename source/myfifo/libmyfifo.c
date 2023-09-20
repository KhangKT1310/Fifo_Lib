/*
 * ***********************************************************************************************************
 * File Name: libmyfifo.c
 * Project: Learning_Code
 * File Created: 20-09-2023  09:16:33:AM
 * Author: KhangKT
 * AuthorEmail: khangkieutrong@gmail.com
 * ***********************************************************************************************************
 */


#include <pthread.h>
#include <time.h>
#include <libmyfifo.h>

// #define FIFO_DEBUG
#ifdef FIFO_DEBUG
#define print printf
#else
#define print(...)
#endif

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int myFifoFull(queue_t *queue)
{
    return (queue->maxSize <= queue->currentSize);
}

int myFifoEmpty(queue_t *queue)
{
    return (queue->currentSize > 0 ? 0 : 1);
}

queue_t *myFifoInit(int maxSize)
{
    queue_t *newQueue = malloc(sizeof(queue_t));
    if (newQueue == NULL)
    {
        print("Malloc failed creating the queue\n");
        return NULL;
    }
    newQueue->maxSize = maxSize;
    newQueue->first = NULL;
    newQueue->last = NULL;
    newQueue->currentSize = 0;
    print("Generated the queue @ %p\n", newQueue);

    return newQueue;
}

/**
 * queue is a queue pointer
 * data is a heap allocated memory pointer
 **/
int myFifoSend(queue_t *queue, void *data, int dataSize)
{
    print("Enterd to fifo_push...\n");
    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL)
    {
        print("Malloc failed createing a node\n");
        return -1;
    }
    // assumming data is in heap
    newNode->data = data;
    newNode->size = dataSize;
    pthread_mutex_lock(&mutex);
    if (queue->first == NULL)
    {
        queue->first = newNode;
        queue->last = newNode;
    }
    else
    {
        queue->last->next = newNode;
        queue->last = newNode;
    }
    queue->currentSize++;
    pthread_mutex_unlock(&mutex);
    print("fifo_push() : push a node\n");

    return 0;
}

void *myFifoReceive(queue_t *queue, int *dataSize)
{
    print("Enterd to fifo_pop\n");
    if (queue == NULL)
    {
        print("queue is null exiting...");
        return NULL;
    }

    pthread_mutex_lock(&mutex);
    if (queue->first == NULL)
    {
        pthread_mutex_unlock(&mutex);
        print("queue->first is NULL exiting...\n");
        return NULL;
    }

    void *data;
    node_t *_node = queue->first;
    if (queue->first == queue->last)
    {
        queue->first = NULL;
        queue->last = NULL;
    }
    else
    {
        queue->first = _node->next;
    }

    data = _node->data;
    *dataSize = _node->size;
    print("Freeing _node@ %p\n", _node);
    free(_node);
    queue->currentSize--;
    pthread_mutex_unlock(&mutex);
    print("fifo_pop() : pop the first node\n");

    return data;
}

int myFifoFree(queue_t *queue)
{
    print("Enterd to queue_destroy\n");
    if (queue == NULL)
    {
        return 0;
    }
    print("queue is not null, queue = %p\n", queue);
    pthread_mutex_lock(&mutex);
    if (queue->first == NULL)
    {
        print("queue->first == NULL...\n");
        free(queue);
        pthread_mutex_unlock(&mutex);
        return 0;
    }
    print("queue is there lets try to free it...\n");
    node_t *node = queue->first;
    while (node != NULL)
    {
        print("freeing : %s\n", (char *)node->data);
        free(node->data);
        node_t *tmp = node->next;
        free(node);
        node = tmp;
    }
    free(queue);
    pthread_mutex_unlock(&mutex);
    return 0;
}
