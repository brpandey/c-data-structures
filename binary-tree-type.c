#include "binary-tree-type.h"
#include "queue-pointers.h"


struct binary_tree_node {
  TT value;
  struct binary_tree_node *left;
  struct binary_tree_node *right;
};


void tree_insert_level(tree_node **node_double_arrow, TT value)
{
  queue *q;
  tree_node *temp_arrow, *insert_arrow;

  /*ensure param is not null so we can deref it later*/
  if(node_double_arrow == NULL) 
    {
      printf("Fatal error 1\n");
      return;
    }

  insert_arrow = (tree_node *) malloc(sizeof(tree_node));

  /*check malloc error condition*/
  if(insert_arrow == NULL)
    {
      printf("Fatal error 2\n");
      return;
    }

  insert_arrow->value = value;
  insert_arrow->left = NULL;
  insert_arrow->right = NULL;

  /*empty tree, set node as node*/
  if(*node_double_arrow == NULL)
    {
      *node_double_arrow = insert_arrow;
      return;
    }

  q = q_create();
  q_enqueue(q, (void *) *node_double_arrow);

  while(q_empty(q) == false)
    {
      temp_arrow = (tree_node *) q_dequeue(q);

      if(temp_arrow->left != NULL)
	{
	  q_enqueue(q, temp_arrow->left);
	}
      else
	{
	  temp_arrow->left = insert_arrow;
	  q_delete(q);

	  return;
	}

      if(temp_arrow->right != NULL)
	{
	  q_enqueue(q, temp_arrow->right);
	}
      else
	{
	  temp_arrow->right = insert_arrow;
	  q_delete(q);
	  return;
	}
    }

  q_delete(q);
}


void tree_inorder_traverse(tree_node *node)
{
  if(node == NULL)
    {
      return;
    }

  tree_inorder_traverse(node->left);
  printf("Inorder node: %d\n", node->value);
  tree_inorder_traverse(node->right);
}


void tree_preorder_traverse(tree_node *node)
{
  if(node == NULL)
    {
      return;
    }

  printf("Preorder node: %d\n", node->value);
  tree_preorder_traverse(node->left);
  tree_preorder_traverse(node->right);
}


void tree_postorder_traverse(tree_node *node)
{
  if(node == NULL)
    {
      return;
    }

  tree_postorder_traverse(node->left);
  tree_postorder_traverse(node->right);
  printf("Postorder node: %d\n", node->value);

}

void tree_delete(tree_node *node)
{
  if(node == NULL)
    {
      return;
    }

  tree_delete(node->left);
  tree_delete(node->right);

  free(node);
}

/* find the node we want to delete, find the deepest node,
   swap the values of the two, 
   delete the bottom rightmost deepest node, use a queue
   as we are enqueuing nodes onto queue, check the node
   if it is the node to be delete and keep a pointer to it.

   Once at the deepest node, swap values, delete the node, 
   and set the parent pointer left or right accordingly*/
void tree_delete_node(tree_node **node, TT value)
{

}

bool tree_find(tree_node *node, TT value)
{
  bool found = false;

  if(node == NULL) return false;

  if(node->value == value) return true;

  found = tree_find(node->left, value);

  if(found == false) 
    {
      found = tree_find(node->right, value);
    }

  return found;
}


int tree_height(tree_node *node)
{
  int left_height, right_height;

  if(node == NULL)
    {
      return 0;
    }

  left_height = tree_height(node->left);
  right_height = tree_height(node->right);

  if(left_height > right_height) return left_height + 1;

  return right_height + 1;
}



int main(int argc, char* argv[])
{
  bool found = false;
  tree_node* root = NULL;

  printf("inserting 22\n");
  tree_insert_level(&root, 22);
  printf("inserting 33\n");
  tree_insert_level(&root, 33);
  printf("inserting 44\n");
  tree_insert_level(&root, 44);
  printf("inserting 55\n");
  tree_insert_level(&root, 55);

  found = tree_find(root, 33);
  printf("value 33 in tree? y/n: %d\n", found);

  found = tree_find(root, 88);
  printf("value 88 in tree? y/n: %d\n", found);

  printf("inserting 66\n");
  tree_insert_level(&root, 66);
  printf("inserting 77\n");
  tree_insert_level(&root, 77);
  printf("inserting 88\n");
  tree_insert_level(&root, 88);

  found = tree_find(root, 88);
  printf("value 88 in tree? y/n: %d\n", found);
  
  tree_preorder(root);

  printf("tree height is %d\n", tree_height(root));
  tree_delete(root);
}

/*
                22
	    33      44

        55    66  77   88

 */
