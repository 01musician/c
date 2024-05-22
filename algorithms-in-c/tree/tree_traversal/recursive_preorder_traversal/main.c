#include <stdlib.h>
#include <stdio.h> 
#include "item.h"
#include "list.h"

/*
                E
              /   \
	     /     \
            D       H
           / \     / \
          B       F
         / \     / \
        A   C       G
       / \ / \     / \

*/

void traverse(link h, void (*visit)(link))
{
  if (h == NULL)
    return;
  (*visit)(h);
  traverse(h->l, visit);
  traverse(h->r, visit);
}  

void print_node(link node)
{
  print_item(node->item);
}

int main(void) 
{
  link root, left, right;

  root = new_node('E');
  add_left_leaf(root, 'D');
  add_right_leaf(root, 'H');
  left = root->l;
  add_left_leaf(left, 'B');
  left = left->l;
  add_left_leaf(left, 'A');
  add_right_leaf(left, 'C');
  right = root->r;
  add_left_leaf(right, 'F');
  right = right->l;
  add_right_leaf(right, 'G');

  traverse(root, print_node);
  printf("\n");
  return 0;
}
