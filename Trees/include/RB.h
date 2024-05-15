//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once

#include "includes.h"

class RB {
 public:

  enum class Color {
    Red, Black
  };

  struct node {
    node() : left(nullptr), right(nullptr), parent(nullptr), color(Color::Black) {}
    node(int64_t k) : key(k), left(nullptr), right(nullptr), parent(nullptr), color(Color::Red) {}

    static void clear(node* node) {
      if (node == nullptr) return;
      if (node->left != nullptr && (node->left->right != nullptr || node->left->left != nullptr)) {
        clear(node->left);
      }
      if (node->right != nullptr && (node->right->right != nullptr || node->right->left != nullptr)) {
        clear(node->right);
      }
      node->left = nullptr;
      node->right = nullptr;
      delete node;
    }

    int64_t key;
    Color color;
    node *left, *right, *parent;
  };

  node* kEmptyNode;

  RB() {
    kEmptyNode = new node();
    root_ = kEmptyNode;
  }

  void insert(int64_t key);
  void erase(int64_t key) {
    erase(root_, key);
  }
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

  node* getRoot() {
    return root_;
  }

  void clear() {
    node::clear(root_);
    root_ = kEmptyNode;
  }

 private:
  node *root_;

  void rightRotation(node* t);
  void leftRotation(node* t);

  void balanceInsert(node* t);
  void balanceErase(node* t);

  void erase(node* t, int64_t key);
  void moveNodes(node* t, node* s);

  node* maxNode(node* t);
  node* find(node* t, int64_t key);
};

RB::node* RB::find(node *t, int64_t key) {
  if (t == kEmptyNode) {
    return nullptr;
  }
  if (key == t->key) {
    return t;
  }
  if (key < t->key) {
    return find(t->left, key);
  }
  return find(t->right, key);
}

void RB::balanceErase(RB::node *t) {
  node* bro;
  while (t != root_ && t->color == Color::Black) {
    if (t == t->parent->left) {
      bro = t->parent->right;
      if (bro->color == Color::Red) {
        bro->color = Color::Black;
        t->parent->color = Color::Red;
        leftRotation(t->parent);
        bro = t->parent->right;
      }

      if (bro->left->color == Color::Black && bro->right->color == Color::Black) {
        bro->color = Color::Red;
        t = t->parent;
      } else {
        if (bro->right->color == Color::Black) {
          bro->left->color = Color::Black;
          bro->color = Color::Red;
          rightRotation(bro);
          bro = t->parent->right;
        }

        bro->color = t->parent->color;
        t->parent->color = Color::Black;
        bro->right->color = Color::Black;
        leftRotation(t->parent);
        t = root_;
      }
    } else {
      bro = t->parent->left;
      if (bro->color == Color::Red) {
        bro->color = Color::Black;
        t->parent->color = Color::Red;
        rightRotation(t->parent);
        bro = t->parent->left;
      }

      if (bro->right->color == Color::Black && bro->left->color == Color::Black) {
        bro->color = Color::Red;
        t = t->parent;
      } else {
        if (bro->left->color == Color::Black) {
          bro->right->color = Color::Black;
          bro->color = Color::Red;
          leftRotation(bro);
          bro = t->parent->left;
        }

        bro->color = t->parent->color;
        t->parent->color = Color::Black;
        bro->left->color = Color::Black;
        rightRotation(t->parent);
        t = root_;
      }
    }
  }
  t->color = Color::Black;
}

void RB::moveNodes(node *t, node *s) {
  if (t->parent == nullptr) {
    root_ = s;
  } else if (t == t->parent->left) {
    t->parent->left = s;
  } else {
    t->parent->right = s;
  }
  s->parent = t->parent;
}

RB::node *RB::maxNode(RB::node *t) {
  while (t->right != kEmptyNode) {
    t = t->right;
  }
  return t;
}

void RB::erase(node *t, int64_t key) {
  node *q = kEmptyNode;
  node *m, *r;
  while (t != kEmptyNode) {
    if (t->key == key) {
      q = t;
    }
    if (t->key <= key) {
      t = t->right;
    } else {
      t = t->left;
    }
  }
  if (q == kEmptyNode) {
    return;
  }
  r = q;
  Color r_color = r->color;
  if (q->left == kEmptyNode) {
    m = q->right;
    moveNodes(q, q->right);
  } else if (q->right == kEmptyNode) {
    m = q->left;
    moveNodes(q, q->left);
  } else {
    r = maxNode(q->left);
    r_color = r->color;
    m = r->left;
    if (r->parent == q) {
      m->parent = r;
    } else {
      moveNodes(r, r->left);
      r->left = q->left;
      r->left->parent = r;
    }

    moveNodes(q, r);
    r->right = q->right;
    r->right->parent = r;
    r->color = q->color;
  }
  delete q;
  q = nullptr;
  if (r_color == Color::Black) {
    balanceErase(m);
  }
}

void RB::balanceInsert(node *t) {
  node* unc;
  while (t->parent->color == Color::Red) {
    if (t->parent == t->parent->parent->right) {
      unc = t->parent->parent->left;
      if (unc->color == Color::Red) {
        unc->color = Color::Black;
        t->parent->color = Color::Black;
        t->parent->parent->color = Color::Red;
        t = t->parent->parent;
      } else {
        if (t == t->parent->left) {
          t = t->parent;
          rightRotation(t);
        }
        t->parent->color = Color::Black;
        t->parent->parent->color = Color::Red;
        leftRotation(t->parent->parent);
      }
    } else {
      unc = t->parent->parent->right;
      if (unc->color == Color::Red) {
        unc->color = Color::Black;
        t->parent->color = Color::Black;
        t->parent->parent->color = Color::Red;
        t = t->parent->parent;
      } else {
        if (t == t->parent->right) {
          t = t->parent;
          leftRotation(t);
        }
        t->parent->color = Color::Black;
        t->parent->parent->color = Color::Red;
        rightRotation(t->parent->parent);
      }
    }
    if (t == root_) {
      break;
    }
  }
  root_->color = Color::Black;
}

void RB::leftRotation(RB::node *t) {
  node* right = t->right;
  t->right = right->left;
  if (right->left != kEmptyNode) {
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

void RB::rightRotation(RB::node *t) {
  node *left = t->left;
  t->left = left->right;
  if (left->right != kEmptyNode) {
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

void RB::insert(int64_t key) {
  if (find(root_, key) != nullptr) return;
  node *t = new node(key);
  t->left = kEmptyNode;
  t->right = kEmptyNode;

  node *q = nullptr;
  node *r = root_;

  while (r != kEmptyNode) {
    q = r;
    if (t->key < r->key) {
      r = r->left;
    } else {
      r = r->right;
    }
  }

  t->parent = q;
  if (q == nullptr) {
    root_ = t;
  } else if (t->key < q->key) {
    q->left = t;
  } else {
    q->right = t;
  }

  if (t->parent == nullptr) {
    t->color = Color::Black;
    return;
  }

  if (t->parent->parent == nullptr) {
    return;
  }

  balanceInsert(t);
}


