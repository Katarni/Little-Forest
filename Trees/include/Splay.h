//
// Created by Тимур Ахметзянов on 10.05.2024.
//

#pragma once

#include "includes.h"

class Splay {
 public:

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

 private:
  node *root_;

  static void leftRotate(node*& v);
  static void rightRotate(node*& v);

  static void splay(node*& v);
};

void Splay::leftRotate(Splay::node *&v) {
  auto parent = v->getParent();
  auto right = v->getRight();
  if (parent != nullptr) {
    if (parent->getLeft() == v) {
      parent->setLeft(right);
    } else {
      parent->setRight(right);
    }
  }
  auto q = right->getLeft();
  right->setLeft(v);
  v->setRight(q);
  v->setParent(right);
  right->setParent(parent);
  if (v->getRight() != nullptr) {
    v->getRight()->setParent(v);
  }
}

void Splay::rightRotate(Splay::node *&v) {
  auto parent = v->getParent();
  auto left = v->getLeft();
  if (parent != nullptr) {
    if (parent->getRight() == v) {
      parent->setRight(left);
    } else {
      parent->setLeft(left);
    }
  }
  auto q = left->getRight();
  left->setRight(v);
  v->setLeft(q);
  v->setParent(left);
  left->setParent(parent);
  if (v->getLeft() != nullptr) {
    v->getLeft()->setParent(v);
  }
}

void Splay::splay(Splay::node *&v) {
  if (v == nullptr) return;
  while (v->getParent() != nullptr) {
    if (v->getKey() == v->getParent()->getLeft()->getKey()) {
      if (v->getGrand() == nullptr) {
        rightRotate(v->getParent());
      } else if (v->getParent()->getKey() == v->getGrand()->getLeft()->getKey()) {
        rightRotate(v->getGrand());
        rightRotate(v->getParent());
      } else {
        rightRotate(v->getParent());
        leftRotate(v->getParent());
      }
    } else {
      if (v->getGrand() == nullptr) {
        leftRotate(v->getParent());
      } else if (v->getParent()->getKey() == v->getGrand()->getRight()->getKey()) {
        leftRotate(v->getGrand());
        leftRotate(v->getParent());
      } else {
        leftRotate(v->getParent());
        rightRotate(v->getParent());
      }
    }
  }
}
