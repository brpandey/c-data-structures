#include "queue-pointers.h"

#define QUEUE_ERROR 0
#define QUEUE_EMPTY_ERROR 0

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

/* Add an element to the rear of the queue */
void q_enqueue(queue *q, T arrow_value)
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

  add->value = arrow_value;
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

/* Grab the element at the front of the queue */
T q_dequeue(queue *q)
{
  void* arrow_value;
  node* discard;

  if(q == NULL)
    {
      printf("Fatal error");
      return QUEUE_ERROR;
    }

  if(q_empty(q) == true) return QUEUE_EMPTY_ERROR;

  if(q_size(q) == 1) q->rear = NULL;

  discard = q->front;
  arrow_value = discard->value;

  q->front = q->front->next;
  q->size--;

  free(discard);

  return arrow_value;
}

/* Delete the linked list and the queue structure */
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

/* Peek at the element in the front w/o removing it */
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

  printf("enqueueing pointer to 22\n");
  q_enqueue(q, (T) &value22);  
  printf("front is: %p\n", (T) q_front(q));
  printf("rear is: %p\n", (T) q_rear(q));

  printf("enqueueing pointer to 33\n");
  q_enqueue(q, (T) &value33);  
  printf("front is: %p\n", (T) q_front(q));
  printf("rear is: %p\n", (T) q_rear(q));

  printf("enqueueing pointer to 44\n");
  q_enqueue(q, (T) &value44);  
  printf("front is: %p\n", (T) q_front(q));
  printf("rear is: %p\n", (T) q_rear(q));

  printf("dequeueing...\n");
  value = q_dequeue(q);  
  printf("dequeued pointer value is: %p\n", value);
  printf("front is: %p\n", (T) q_front(q));
  printf("rear is: %p\n", (T) q_rear(q));

  printf("enqueueing pointer to 55\n");
  q_enqueue(q, (T) &value55);
  printf("dequeued pointer value is: %p\n", (T) value);
  printf("front is: %p\n", (T) q_front(q));
  printf("rear is: %p\n", (T) q_rear(q));

  printf("dequeueing...\n");
  value = q_dequeue(q);
  printf("dequeued pointer value is: %p\n", (T) value);

  printf("dequeueing...\n");
  value = q_dequeue(q);
  printf("dequeued pointer value is: %p\n", (T) value);

  printf("front is: %p\n", (T) q_front(q));
  printf("rear is: %p\n", (T) q_rear(q));

  printf("dequeueing...\n");
  value = q_dequeue(q);
  printf("dequeued pointer value is: %p\n", (T) value);

  printf("front is: %p\n", (T) q_front(q));
  printf("rear is: %p\n", (T) q_rear(q));

  q_delete(q);
}
