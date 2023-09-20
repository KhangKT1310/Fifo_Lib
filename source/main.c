

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "libmyfifo.h"

char *text = "xin_chao";
char *text_2 = "vietnam";
void *processTest(void *arg)
{
    while (1)
    {
        sleep(1);
        printf("processTest write to fifo\n");
        myFifoSend(arg, text, sizeof(*text));
    }

    return NULL;
}

void *processTest_2(void *arg)
{
    while (1)
    {
        sleep(2);
        printf("processTest_2 write to fifo\n");
        myFifoSend(arg, text_2, sizeof(*text_2));
    }

    return NULL;
}

int main()
{
    queue_t *a = myFifoInit(1024);
    if (a == NULL)
    {
        free(a);
        return -1;
    }
    int dataSize;
    char *data = NULL;
    pthread_t processID;

    pthread_create(&processID, NULL, processTest, a);
    pthread_create(&processID, NULL, processTest_2, a);

    while (1)
    {

        data = myFifoReceive(a, &dataSize);
        if (data != NULL)
        {
            printf("data is :%s\n", data);
        }

        usleep(1000);
    }
    myFifoFree(a);

    return 0;
}