#include <stdlib.h>
#include <stdio.h>

#include "queue-pointers.h"

struct binary_tree_node {
  int value;
  struct binary_tree_node *left;
  struct binary_tree_node *right;
};

typedef binary_tree_node TreeNode;

void BinaryTreeInsert(TreeNode **root, int value)
{
  Queue *q;
  TreeNode *temp_arrow, *insert_arrow;

  /*ensure param is not null so we can deref it later*/
  if(root == NULL) 
    {
      printf("Fatal error");
      return;
    }

  insert_arrow = (TreeNode *) malloc(sizeof(TreeNode));

  /*check malloc error condition*/
  if(insert_arrow == NULL)
    {
      printf("fatal error");
      return;
    }

  insert_arrow->value = value;
  insert_arrow->left = NULL;
  insert_arrow->right = NULL;

  /*empty tree, set node as root*/
  if(*root == NULL)
    {
      *root = insert_arrow;
      return;
    }

  q = QueueCreate();
  QueueEnqueue(q, (void *) *root);

  while(QueueEmpty(q) == false)
    {
      temp_arrow = (TreeNode *) QueueDequeue(q);

      if(temp_arrow->left != NULL)
	{
	  QueueEnqueue(q, temp_arrow->left);
	}
      else
	{
	  temp_arrow->left = insert_arrow;
	  QueueDelete(q);

	  return;
	}

      if(temp_arrow->right != NULL)
	{
	  QueueEnqueue(q, temp_arrow->right);
	}
      else
	{
	  temp_arrow->right = insert_arrow;
	  QueueDelete(q);
	  return;
	}
    }

  QueueDelete(q);
}
