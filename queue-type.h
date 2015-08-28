#ifndef QUEUE_TYPE_H
#define QUEUE_TYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int T;


typedef struct queue_s queue;


queue* q_create();
int q_size(queue *q);
bool q_empty(queue *q);
void q_enqueue(queue *q, T value);
T q_dequeue(queue *q);
void q_delete(queue *q);
T q_front(queue *q);
T q_rear(queue *q);


#endif
