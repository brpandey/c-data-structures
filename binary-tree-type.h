#ifndef BINARY_TREE_TYPE_H
#define BINARY_TREE_TYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int TT;
typedef struct binary_tree_node tree_node;

/* ADT Operations */ 

/* Insert */
void tree_insert_level(tree_node **root, TT value);

/* Delete */
void tree_delete_node(tree_node **root, TT value);
void tree_delete(tree_node *node);

/* Search */
bool tree_find(tree_node *node, TT value);

/* Traverse */
void tree_inorder(tree_node *root);
void tree_preorder(tree_node *root);
void tree_postorder(tree_node *root);

/* Extra auxiliary operations */
int tree_height(tree_node *node);


#endif
