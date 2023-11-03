#include "queue.h"

node *send_queue;

int sq_front, sq_rear, sq_capacity;

void init_send_queue()
{
	sq_front = sq_rear = 0;
        sq_capacity = MAX_QUEUE_SIZE - 1;
        send_queue = malloc(sizeof(node) * (MAX_QUEUE_SIZE -1));
}

void delete_send_queue()
{
	if(send_queue){
		free(send_queue);
		send_queue = NULL;
	}
}
int send_queue_empty()
{
	if (sq_front == sq_rear) {
                return 1;
        } else {
                return 0;
        }
}
void send_queue_enqueue(node data)
{
	// check queue is full or not
        if (sq_capacity == sq_rear) {
        	printf("\nQueue is full\n");
            	return;
        }

        	// insert element at the rear
        else {
        	send_queue[sq_rear] = data;
        	sq_rear++;
        }
        return;
}
void send_queue_dequeue()
{
	// if queue is empty
        if (sq_front == sq_rear) {
            //printf("\nQueue is  empty\n");
            return;
        }

        // shift all the elements from index 2 till rear
        // to the left by one
        else {
            for (int i = 0; i < sq_rear - 1; i++) {
                send_queue[i] = send_queue[i + 1];
            }

            // decrement rear
            sq_rear--;
        }
        return;
}

node *send_queue_front()
{
	if (sq_front == sq_rear) {
            //printf("\nQueue is Empty\n");
            return NULL;
        }
        return &send_queue[sq_front];
}
