#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

#define STACK_ERROR -2
#define STACK_EMPTY_ERROR -1

struct listnode {
  int value;
  struct listnode *next;
};

typedef struct listnode Node;

struct stack {
  int size;
  Node* top;
};

typedef struct stack Stack;

Stack* StackCreate()
{
  Stack* stk = (Stack *) malloc(sizeof(Stack));
  
  if(stk == NULL)
    {
      printf("Fatal error");
      return NULL;
    }

  stk->size = 0;
  stk->top = NULL;
  return stk;
}

void StackPush(Stack *stack, int value)
{
  Node *tmp, *top;

  if(stack == NULL)
    {
      printf("Fatal error");
      return;
    }

  tmp = (Node *) malloc(sizeof(Node));
  
  if(tmp == NULL)
    {
      printf("Fatal error");
      return;
    }
  
  tmp->value = value;
  tmp->next = stack->top;
  stack->top = tmp;
  stack->size++;
}

void StackPush2(Node** top, int value)
{

}

int StackPop(Stack *stack)
{
  int value;
  Node* discard;

  if(stack == NULL)
    {
      printf("Fatal error");
      return STACK_ERROR;
    }

  if(stack->top == NULL) 
    {
      printf("Stack empty, nothing to pop");
      return STACK_EMPTY_ERROR;
    }

  discard = stack->top;
  value = discard->value;
  stack->top = stack->top->next;

  free(discard);

  return value;
}

int StackPop2(Node** top)
{
  return 0;
}


void StackDelete(Stack *stack)
{
  Node *previous, *current;

  if(stack == NULL)
    {
      printf("Fatal error");
      return;
    }

  previous = stack->top;
  
  while(previous != NULL)
    {
      current = previous->next;
      free(previous);
      previous = current;
    }

  free(stack);
}

void StackDelete2(Node* top)
{
  Node *previous, *current;

  if(top == NULL)
    {
      printf("Fatal error");
      return;
    }

  previous = top;

  while(previous != NULL)
    {
      current = previous->next;
      free(previous);
      previous = current;
    }
}

bool StackEmpty(Stack* stk)
{
  if(stk == NULL || stk->size == 0) return true;

  return false;
}

int StackTop(Stack* stk)
{
  if(stk == NULL) 
    {
      printf("Fatal error");
      return STACK_ERROR;
    }

  if(stk->size == 0 || stk->top == NULL)
    {
      printf("Empty");
      return STACK_ERROR;
    }

  return stk->top->value;
}


int main()
{
  Stack *stk = StackCreate();
  StackPush(stk, 4);
  StackPush(stk, 11);
  StackPush(stk, 13);
  StackPush(stk, 8);

  printf("top is: %d\n", StackTop(stk));
  
  StackPop(stk);
  StackPop(stk);
  StackPop(stk);

  printf("top is: %d\n", StackTop(stk));

  StackPush(stk, 2);
  StackPush(stk, 1);

  StackPop(stk);
  StackPop(stk);
  StackPop(stk);

  printf("top is: %d\n", StackTop(stk));

  StackPush(stk, 5);
  StackPush(stk, 32);


  StackPush(stk, 3);
  StackPush(stk, 16);
  printf("top is: %d\n", StackTop(stk));

  StackPop(stk);
  printf("top is: %d\n", StackTop(stk));

  StackPop(stk);
  printf("top is: %d\n", StackTop(stk));

  StackPop(stk);
  printf("top is: %d\n", StackTop(stk));

  StackPop(stk);
  printf("top is: %d\n", StackTop(stk));

  StackDelete(stk);
}
