//
// Created by Тимур Ахметзянов on 10.05.2024.
//

#pragma once

#include "includes.h"

class Splay {
 public:
  Splay(): root_(nullptr) {}

  class node {
   public:
    node(int64_t key) : key_(key), left_(nullptr), right_(nullptr), parent_(nullptr) {}

    node*& getLeft() {
      return left_;
    }
    node*& getRight() {
      return right_;
    }
    void setLeft(node* left) {
      left_ = left;
    }
    void setRight(node* right) {
      right_ = right;
    }
    node *&getParent() {
      return parent_;
    }
    node *&getGrand() {
      return parent_->parent_;
    }
    void setParent(node *parent) {
      parent_ = parent;
    }

    static void clear(node*& node) {
      if (node == nullptr) return;
      clear(node->left_);
      clear(node->right_);
      delete node;
    }
    int64_t getKey() const {
      return key_;
    }

   private:
    int64_t key_;
    node *left_, *right_, *parent_;
  };

  bool find(int64_t key);

  void insert(int64_t key);
  void insertNRandom(int64_t n);

  void clear() {
    node::clear(root_);
    root_ = nullptr;
  }

  node *&getRoot();

 private:
  node *root_;

  static void leftRotate(node*& t);
  static void rightRotate(node*& t);

  static node* splay(node*& t);
  static node* find(node* t, int64_t key);
  static void insert(node*& t, int64_t key);
};

void Splay::leftRotate(Splay::node *&t) {
  auto parent = t->getParent();
  auto right = t->getRight();
  if (parent != nullptr) {
    if (parent->getLeft() == t) {
      parent->setLeft(right);
    } else {
      parent->setRight(right);
    }
  }
  auto q = right->getLeft();
  right->setLeft(t);
  t->setRight(q);
  t->setParent(right);
  right->setParent(parent);
  if (t != nullptr && t->getRight() != nullptr) {
    t->getRight()->setParent(t);
  }
}

void Splay::rightRotate(Splay::node *&t) {
  auto parent = t->getParent();
  auto left = t->getLeft();
  if (parent != nullptr) {
    if (parent->getRight() == t) {
      parent->setRight(left);
    } else {
      parent->setLeft(left);
    }
  }
  auto q = left->getRight();
  left->setRight(t);
  t->setLeft(q);
  t->setParent(left);
  left->setParent(parent);
  if (t != nullptr && t->getLeft() != nullptr) {
    t->getLeft()->setParent(t);
  }
}

Splay::node* Splay::splay(Splay::node *&t) {
  if (t == nullptr) return nullptr;
  while (t->getParent() != nullptr) {
    if (t == t->getParent()->getLeft()) {
      if (t->getGrand() == nullptr) {
        rightRotate(t->getParent());
      } else if (t->getParent() == t->getGrand()->getLeft()) {
        rightRotate(t->getGrand());
        rightRotate(t->getParent());
      } else {
        rightRotate(t->getParent());
        leftRotate(t->getParent());
      }
    } else {
      if (t->getGrand() == nullptr) {
        leftRotate(t->getParent());
      } else if (t->getParent() == t->getGrand()->getRight()) {
        leftRotate(t->getGrand());
        leftRotate(t->getParent());
      } else {
        leftRotate(t->getParent());
        rightRotate(t->getParent());
      }
    }
  }
  return t;
}

bool Splay::find(int64_t key) {
  auto node = find(root_, key);
  if (node == nullptr) return false;
  root_ = splay(node);
  return true;
}

Splay::node *Splay::find(Splay::node *t, int64_t key) {
  if (t == nullptr) return nullptr;
  if (t->getKey() == key) return t;
  return find(t->getKey() > key ? t->getLeft() : t->getRight(), key);
}

void Splay::insert(int64_t key) {
  if (find(key)) return;
  insert(root_, key);
  find(key);
}

void Splay::insert(Splay::node *&t, int64_t key) {
  if (t == nullptr) {
    t = new node(key);
    return;
  }
  if (t->getKey() > key) {
    insert(t->getLeft(), key);
    t->getLeft()->setParent(t);
  } else {
    insert(t->getRight(), key);
    t->getRight()->setParent(t);
  }
}

Splay::node *&Splay::getRoot() {
  return root_;
}

void Splay::insertNRandom(int64_t n) {
  int64_t key;
  while (n--) {
    key = rnd() % 100000;
    while (find(root_, key)) {
      key = rnd() % 100000;
    }
    insert(key);
  }
}
