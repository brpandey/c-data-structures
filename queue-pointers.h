#ifndef QUEUE_POINTERS_H
#define QUEUE_POINTERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* T;
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
