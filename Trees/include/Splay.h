//
// Created by Тимур Ахметзянов on 10.05.2024.
//

#pragma once


#include "includes.h"

class Splay {
 public:

  Splay() {
    root_ = nullptr;
  }

  struct node {
    node(int64_t k) {
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      key = k;
    }

    static void clear(node*& t) {
      if (t == nullptr) return;

      clear(t->left);
      clear(t->right);
      t->left = nullptr;
      t->right = nullptr;
      delete t;
    }

    int64_t key;
    node *parent, *left, *right;
  };

  void insert(int64_t key);
  void erase(int64_t key);
  void insertNRandom(int64_t n) {
    int64_t key;
    while (n--) {
      key = rnd() % 100000;
      while (find(root_, key)) {
        key = rnd() % 100000;
      }
      insert(key);
    }
  }

  node *getRoot() const {
    return root_;
  }

  void clear() {
   node::clear(root_);
   root_ = nullptr;
  }

 private:
  node *root_;

  node *find(node *t, int64_t key);
  void erase(node *t, int64_t key);
  void leftRotation(node *t);
  void rightRotation(node *t);
  void splay(node *t);
  node *merge(node *a, node *b);
  void split(node *&t, node *&a, node *&b);
  static node *getMaximum(node *t);
};

void Splay::erase(int64_t key) {
  erase(root_, key);
}

void Splay::insert(int64_t key) {
  auto t = new node(key);
  node* b = nullptr;
  node* a = root_;

  while (a != nullptr) {
    b = a;
    if (t->key < a->key) {
      a = a->left;
    } else {
      a = a->right;
    }
  }
  t->parent = b;
  if (b == nullptr) {
    root_ = t;
  } else if (t->key < b->key) {
    b->left = t;
  } else {
    b->right = t;
  }
  splay(t);
}

Splay::node *Splay::getMaximum(node *t) {
  while (t->right != nullptr) {
    t = t->right;
  }
  return t;
}

void Splay::split(node *&t, node *&a, node *&b) {
  splay(t);
  if (t->right) {
    b = t->right;
    b->parent = nullptr;
  } else {
    b = nullptr;
  }
  a = t;
  a->right = nullptr;
  t = nullptr;
}

Splay::node *Splay::merge(node *a, node *b) {
  if (!a) {
    return b;
  }
  if (!b) {
    return a;
  }
  auto x = getMaximum(a);
  splay(x);
  x->right = b;
  b->parent = x;
  return x;
}

void Splay::leftRotation(node *t) {
  node *right = t->right;
  t->right = right->left;
  if (right->left != nullptr) {
    right->left->parent = t;
  }
  right->parent = t->parent;
  if (t->parent == nullptr) {
    root_ = right;
  } else if (t == t->parent->left) {
    t->parent->left = right;
  } else {
    t->parent->right = right;
  }
  right->left = t;
  t->parent = right;
}

void Splay::rightRotation(node *t) {
  node *left = t->left;
  t->left = left->right;
  if (left->right != nullptr) {
    left->right->parent = t;
  }
  left->parent = t->parent;
  if (t->parent == nullptr) {
    root_ = left;
  } else if (t == t->parent->right) {
    t->parent->right = left;
  } else {
    t->parent->left = left;
  }
  left->right = t;
  t->parent = left;
}

void Splay::splay(node *t) {
  while (t->parent) {
    if (!t->parent->parent) {
      if (t == t->parent->left) {
        rightRotation(t->parent);
      } else {
        leftRotation(t->parent);
      }
    } else if (t == t->parent->left && t->parent == t->parent->parent->left) {
      rightRotation(t->parent->parent);
      rightRotation(t->parent);
    } else if (t == t->parent->right && t->parent == t->parent->parent->right) {
      leftRotation(t->parent->parent);
      leftRotation(t->parent);
    } else if (t == t->parent->right && t->parent == t->parent->parent->left) {
      leftRotation(t->parent);
      rightRotation(t->parent);
    } else {
      rightRotation(t->parent);
      leftRotation(t->parent);
    }
  }
}

void Splay::erase(node *t, int64_t key) {
  node* q = nullptr;
  node *right, *left;
  while (t != nullptr) {
    if (t->key == key) {
      q = t;
    }
    if (t->key <= key) {
      t = t->right;
    } else {
      t = t->left;
    }
  }
  if (q == nullptr) {
    return;
  }
  split(q, left, right);
  if (left->left) {
    left->left->parent = nullptr;
  }
  root_ = merge(left->left, right);
  delete left;
  left = nullptr;
}

Splay::node *Splay::find(node *t, int64_t key) {
  if (t == nullptr || key == t->key) {
    return t;
  }
  if (key < t->key) {
    return find(t->left, key);
  }
  return find(t->right, key);
}
