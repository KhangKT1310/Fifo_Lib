

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "fifo.h"


int main()
{
    queue *a = fifo_init(256);

    fifo_free(a);
    return 0;
}