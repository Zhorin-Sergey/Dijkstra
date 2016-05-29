#include "tree.h"

avltree *avltree_create(int key, int value) {
  struct avltree *node;
  node = new avltree;
  if (node != NULL) {
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
  }
  return node;
}

int avltree_height(avltree *tree) {
  if (tree != NULL)
    return tree->height;
  return -1;
}

int avltree_balance(avltree *tree) {
  return avltree_height(tree->left) -
    avltree_height(tree->right);
}

avltree *avltree_add(avltree *tree, int key, int value) {
  if (tree == NULL) {
    return avltree_create(key, value);
  }
  if (key <= tree->key) {
    tree->left = avltree_add(tree->left, key, value);
    if (avltree_height(tree->left) -
    avltree_height(tree->right) == 2) {
      if (avltree_height(tree->left->right)
        < avltree_height(tree->left->left)) {
        tree = avltree_right_rotate(tree);
      } else {
        tree = avltree_leftright_rotate(tree);
      }
    }
  } else {
    tree->right = avltree_add(tree->right, key, value);
    if (avltree_height(tree->right) - avltree_height(tree->left) == 2) {
      if (avltree_height(tree->right->right)
        > avltree_height(tree->right->left)) {
        tree = avltree_left_rotate(tree);
      } else {
        tree = avltree_rightleft_rotate(tree);
      }
    }
  }
  tree->height = std::max(avltree_height(tree->left),
  avltree_height(tree->right)) + 1;
  return tree;
}

avltree *avltree_right_rotate(avltree *tree) {
  avltree *left;
  left = tree->left;
  tree->left = left->right;
  left->right = tree;
  tree->height = std::max(
  avltree_height(tree->left),
  avltree_height(tree->right)) + 1;
  left->height = std::max(
  avltree_height(left->left),
  tree->height) + 1;
  return left;
}

avltree *avltree_left_rotate(avltree *tree) {
  avltree *right1;
  right1 = tree->right;
  tree->right = right1->left;
  right1->left = tree;
  tree->height = std::max(
  avltree_height(tree->left),
  avltree_height(tree->right)) + 1;
  right1->height = std::max(
  avltree_height(right1->right),
  tree->height) + 1;
  return right1;
}

avltree *avltree_leftright_rotate(avltree *tree) {
  tree->left = avltree_left_rotate(tree->left);
  return avltree_right_rotate(tree);
}

avltree *avltree_rightleft_rotate(avltree *tree) {
  tree->right = avltree_right_rotate(tree->right);
  return avltree_left_rotate(tree);
}

avltree *avltree_min(avltree *tree, avltree **min) {
  if (tree->left == 0) {
    *min = tree;
    tree = 0;
    return tree;
  }
  if (tree->left->left == NULL) {
    *min = (tree->left);
    if (tree->left->right != NULL) {
      tree->left = tree->left->right;
    } else {
      tree->left = NULL;
    }
    return tree;
  }
  tree->left = avltree_min(tree->left, min);
  if (avltree_height(tree->left) -
  avltree_height(tree->right) == -2) {
    tree = avltree_left_rotate(tree);
  }
  tree->height = std::max(
  avltree_height(tree->left),
  avltree_height(tree->right)) + 1;
  return tree;
}

avltree *avltree_del(avltree *tree, int k, int t) {
  if (tree->left == 0 && tree->right == 0) {
    tree->height = 0;
    return tree;
  }
  if (tree->left != 0) {
    if (tree->left->value == k) {
      if (tree->left->left == 0 && tree->left->right == 0) {
        tree->left = 0;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
    if (tree->left->value == k) {
      if (tree->left->left != 0 && tree->left->right != 0) {
        avltree *tmp = 0;
        tree->left->right = avltree_min(tree->left->right, &tmp);
        tmp->left = tree->left->left;
        tmp->right = tree->left->right;
        tree->left = tmp;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
    if (tree->left->value == k) {
      if (tree->left->left == 0 && tree->left->right != 0) {
        tree->left = tree->left->right;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
    if (tree->left->value == k) {
      if (tree->left->left != 0 && tree->left->right == 0) {
        tree->left = tree->left->left;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
  }
  if (tree->right != 0) {
    if (tree->right->value == k) {
      if (tree->right->left != 0 && tree->right->right == 0) {
        tree->right = tree->right->left;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
    if (tree->right->value == k) {
      if (tree->right->left != 0 && tree->right->right != 0) {
        avltree *tmp = 0;
        tree->right->right = avltree_min(tree->right->right, &tmp);
        tmp->left = tree->right->left;
        tmp->right = tree->right->right;
        tree->right = tmp;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
    if (tree->right->value == k) {
      if (tree->right->left == 0 && tree->right->right == 0) {
        tree->right = 0;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
    if (tree->right->value == k) {
      if (tree->right->left == 0 && tree->right->right != 0) {
        tree->right = tree->right->right;
        tree->height = std::max(
          avltree_height(tree->left),
          avltree_height(tree->right)) + 1;
        return tree;
      }
    }
  }
  if (tree->left != 0)
    tree->left = avltree_del(tree->left, k, t);
  if (tree->right != 0)
    tree->right = avltree_del(tree->right, k, t);
  if (avltree_height(tree->right) - avltree_height(tree->left) == 2) {
    if (avltree_height(tree->right->right)
      > avltree_height(tree->right->left)) {
      tree = avltree_left_rotate(tree);
    } else {
      tree = avltree_rightleft_rotate(tree);
    }
  }
  if (avltree_height(tree->left) -
  avltree_height(tree->right) == 2) {
    if (avltree_height(tree->left->right)
      < avltree_height(tree->left->left)) {
      tree = avltree_right_rotate(tree);
    } else {
      tree = avltree_leftright_rotate(tree);
    }
  }

  tree->height = std::max(
  avltree_height(tree->left),
  avltree_height(tree->right)) + 1;
  return tree;
}

int get_value(avltree *tree) {
  return(tree->value);
}
