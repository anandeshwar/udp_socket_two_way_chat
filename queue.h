#ifndef _QUEUE_
#define _QUEUE_

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


#define MAX_STR_LEN 525
#define MAX_QUEUE_SIZE 100

typedef struct _node_
{
        int fd;
        char m_str[MAX_STR_LEN];
        int str_size;
}node;

void init_send_queue();
void delete_send_queue();
int send_queue_empty();
void send_queue_enqueue(node data);
void send_queue_dequeue();
node *send_queue_front();


#endif //_QUEUE_
