#ifndef SOLUTIONS_DIJKSTRA_CLASS_TREE_H_
#define SOLUTIONS_DIJKSTRA_CLASS_TREE_H_
#include "stdio.h"
#include <algorithm>
#include <iostream>

struct avltree {
  int key;
  int value;
  int height;
  avltree *left;
  avltree *right;
};

avltree *avltree_create(int key, int value);
int avltree_height(avltree *tree);
avltree *avltree_add(avltree *tree, int key, int value);
int avltree_balance(avltree *tree);
avltree *avltree_right_rotate(avltree *tree);
avltree *avltree_min(avltree *tree, avltree **min);
avltree *avltree_left_rotate(avltree *tree);
avltree *avltree_leftright_rotate(avltree *tree);
avltree *avltree_rightleft_rotate(avltree *tree);
avltree *avltree_del(avltree *tree, int k, int t);
int proverka(avltree *tree, int k, int t);
int get_value(avltree *tree);

#endif  //  SOLUTIONS_DIJKSTRA_CLASS_TREE_H_
