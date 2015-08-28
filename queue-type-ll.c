#include <stdio.h>
#include <stdlib.h>

#include "queue-type.h"

#define QUEUE_ERROR -2
#define QUEUE_EMPTY_ERROR -1

struct queue_node_s {
  T value;
  struct queue_node_s *next;
};

typedef struct queue_node_s node;

struct queue_s {
  int size;
  node* front;
  node* rear;
};


queue* q_create()
{
  queue* q = (queue *) malloc(sizeof(queue));
  
  if(q == NULL)
    {
      printf("Fatal error");
      return NULL;
    }

  q->size = 0;
  q->front = NULL;
  q->rear = NULL;

  return q;
}

int q_size(queue *q)
{
  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  return q->size;
}

bool q_empty(queue *q)
{
  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  if(q->size == 0) return true;

  return false;
}

void q_enqueue(queue *q, T value)
{
  node* add;

  if(q == NULL)
    {
      printf("Fatal error");
    }

  add = (node *) malloc(sizeof(node));

  if(add == NULL)
    {
      printf("Fatal error");
    }

  add->value = value;
  add->next = NULL;

  if(q->front == NULL && q->rear == NULL)
    {
      q->front = add;
    }
  else
    {
      q->rear->next = add;
    }

  q->rear = add;
  q->size++;
}

T q_dequeue(queue *q)
{
  int value;
  node* discard;

  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  if(q_empty(q) == true) return QUEUE_EMPTY_ERROR;

  if(q_size(q) == 1) q->rear = NULL;

  discard = q->front;
  value = discard->value;

  q->front = q->front->next;
  q->size--;

  free(discard);

  return value;
}

void q_delete(queue *q)
{
  node *previous, *current;

  if(q == NULL || (q->front == NULL && q->front == NULL)) return;
  
  previous = q->front;
  
  while(previous != NULL)
    {
      current = previous->next;
      free(previous);
      previous = current;
    }

  free(q);
}

T q_front(queue *q)
{
  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  if(q->front == NULL)
    {
      return QUEUE_EMPTY_ERROR;
    }

  return q->front->value;
}

T q_rear(queue *q)
{
  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  if(q->rear == NULL)
    {
      return QUEUE_EMPTY_ERROR;
    }

  return q->rear->value;
}



int main()
{
  T value = 0;
  int value22 = 22, value33 = 33, value44 = 44, value55 = 55;

  queue* q = q_create();

  printf("enqueueing 22\n");
  q_enqueue(q, value22);  
  printf("front is: %d\n", (T) QueueFront(q));
  printf("rear is: %d\n", (T) QueueRear(q));

  printf("enqueueing 33\n");
  q_enqueue(q, value33);  
  printf("front is: %d\n", (T) QueueFront(q));
  printf("rear is: %d\n", (T) QueueRear(q));

  printf("enqueueing 44\n");
  q_enqueue(q, value44);  
  printf("front is: %d\n", (T) QueueFront(q));
  printf("rear is: %d\n", (T) QueueRear(q));

  printf("dequeueing...\n");
  value = q_dequeue(q);  
  printf("dequeued value is: %d\n", (T) value);
  printf("front is: %d\n", (T) q_front(q));
  printf("rear is: %d\n", (T) q_rear(q));

  printf("enqueueing 55\n");
  q_enqueue(q, value55);
  printf("dequeued value is: %d\n", (T) value);
  printf("front is: %d\n", (T) q_front(q));
  printf("rear is: %d\n", (T) q_rear(q));

  printf("dequeueing...\n");
  value = q_dequeue(q);
  printf("dequeued value is: %d\n", (T) value);

  printf("dequeueing...\n");
  value = q_dequeue(q);
  printf("dequeued value is: %d\n", (T) value);

  printf("front is: %d\n", (T) q_front(q));
  printf("rear is: %d\n", (T) q_rear(q));

  printf("dequeueing...\n");
  value = q_dequeue(q);
  printf("dequeued value is: %d\n", (T) value);

  printf("front is: %d\n", (T) q_front(q));
  printf("rear is: %d\n", (T) q_rear(q));

  q_delete(q);
}

