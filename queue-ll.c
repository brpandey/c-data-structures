#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

#define QUEUE_ERROR -2
#define QUEUE_EMPTY_ERROR -1

struct queue_node {
  int value;
  struct queue_node *next;
};

typedef struct queue_node Node;

struct queue {
  int size;
  Node* front;
  Node* rear;
};

typedef struct queue Queue;

Queue* QueueCreate()
{
  Queue* q = (Queue *) malloc(sizeof(Queue));
  
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

int QueueSize(Queue *q)
{
  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  return q->size;
}

bool QueueEmpty(Queue *q)
{
  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  if(q->size == 0) return true;

  return false;
}

void QueueEnqueue(Queue *q, int value)
{
  Node* add;

  if(q == NULL)
    {
      printf("Fatal error");
    }

  add = (Node *) malloc(sizeof(Node));

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

int QueueDequeue(Queue *q)
{
  int value;
  Node* discard;

  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  if(QueueEmpty(q) == true) return QUEUE_EMPTY_ERROR;

  if(QueueSize(q) == 1) q->rear = NULL;

  discard = q->front;
  value = discard->value;

  q->front = q->front->next;
  q->size--;

  free(discard);

  return value;
}

void QueueDelete(Queue *q)
{
  Node *previous, *current;

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

int QueueFront(Queue *q)
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

int QueueRear(Queue *q)
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
  int value = 0;
  Queue* q = QueueCreate();

  printf("enqueueing 22\n");
  QueueEnqueue(q, 22);  
  printf("front is: %d\n", QueueFront(q));
  printf("rear is: %d\n", QueueRear(q));

  printf("enqueueing 33\n");
  QueueEnqueue(q, 33);  
  printf("front is: %d\n", QueueFront(q));
  printf("rear is: %d\n", QueueRear(q));

  printf("enqueueing 44\n");
  QueueEnqueue(q, 44);  
  printf("front is: %d\n", QueueFront(q));
  printf("rear is: %d\n", QueueRear(q));

  printf("dequeueing...\n");
  value = QueueDequeue(q);  
  printf("dequeued value is: %d\n", value);
  printf("front is: %d\n", QueueFront(q));
  printf("rear is: %d\n", QueueRear(q));

  printf("enqueueing 55\n");
  QueueEnqueue(q, 55);
  printf("dequeued value is: %d\n", value);
  printf("front is: %d\n", QueueFront(q));
  printf("rear is: %d\n", QueueRear(q));

  printf("dequeueing...\n");
  value = QueueDequeue(q);
  printf("dequeued value is: %d\n", value);

  printf("dequeueing...\n");
  value = QueueDequeue(q);
  printf("dequeued value is: %d\n", value);

  printf("front is: %d\n", QueueFront(q));
  printf("rear is: %d\n", QueueRear(q));

  printf("dequeueing...\n");
  value = QueueDequeue(q);
  printf("dequeued value is: %d\n", value);

  printf("front is: %d\n", QueueFront(q));
  printf("rear is: %d\n", QueueRear(q));

  QueueDelete(q);
}
