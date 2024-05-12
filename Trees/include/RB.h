//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once

#include "includes.h"


class RB {
 public:

  class node {
   public:
    node(int64_t key) : key_(key), left_(nullptr), right_(nullptr), parent_(nullptr),
                        is_black_(false) {}

    static void clear(node*& node) {
      if (node == nullptr) return;
      clear(node->left_);
      clear(node->right_);
      delete node;
    }

    static bool isBlack(node* node) {
      if (node == nullptr) return true;
      return node->is_black_;
    }

    static void setBlack(node*& node, bool black) {
      if (node == nullptr) return;
      node->is_black_ = black;
    }

    inline int64_t getKey() const {
      return key_;
    }

    inline node* getLeft() const {
      return left_;
    }

    void setLeft(node *left) {
      left_ = left;
    }

    inline node* getRight() const {
      return right_;
    }

    void setRight(node *right) {
      right_ = right;
    }

    inline node* getParent() const {
      return parent_;
    }

    void setParent(node *parent) {
      parent_ = parent;
    }

    node*& left() {
      return left_;
    }

    node*& right() {
      return right_;
    }

   private:
    int64_t key_;
    node *left_, *right_, *parent_;
    bool is_black_;
  };


  RB() : root_(nullptr) {}

  void insert(int64_t key);

  node*& getRoot() {
    return root_;
  }

 private:
  node *root_;

  node* insert(node*& root, node*& t);

  void rightRotation(node*& t);
  void leftRotation(node*& t);

  void balanceInsert(node*& t);
};

void RB::insert(int64_t key) {
  node* t = new node(key);
  root_ = insert(root_, t);
  balanceInsert(t);
}

RB::node *RB::insert(RB::node *&root, RB::node *&t) {
  if (root == nullptr) {
    return t;
  }

  if (t->getKey() < root->getKey()) {
    root->setLeft(insert(root->left(), t));
    root->getLeft()->setParent(root);
  } else if (t->getKey() > root->getKey()) {
    root->setRight(insert(root->right(), t));
    root->getRight()->setParent(root);
  }

  return root;
}

void RB::rightRotation(RB::node *&t) {
  auto left = t->getLeft();
  t->setLeft(left->getRight());

  if (t->getLeft() != nullptr)
    t->getLeft()->setParent(t);

  left->setParent(t->getParent());

  if (t->getParent() == nullptr) {
    root_ = left;
  } else if (t == t->getParent()->getLeft()) {
    t->getParent()->setLeft(left);
  } else {
    t->getParent()->setRight(left);
  }

  left->setRight(t);
  t->setParent(left);
}

void RB::leftRotation(RB::node *&t) {
  auto right = t->getRight();
  t->setRight(right->getLeft());

  if (t->getRight() != nullptr)
    t->getRight()->setParent(t);

  right->setParent(t->getParent());

  if (t->getParent() == nullptr) {
    root_ = right;
  } else if (t == t->getParent()->getLeft()) {
    t->getParent()->setLeft(right);
  } else {
    t->getParent()->setRight(right);
  }

  right->setLeft(t);
  t->setParent(right);
}

void RB::balanceInsert(RB::node *&t) {
  node* parent = nullptr;
  node* grand = nullptr;
  while (t != root_ && !node::isBlack(t) && !node::isBlack(t->getParent())) {
    parent = t->getParent();
    grand = parent->getParent();
    if (parent == grand->getLeft()) {
      node* uncle = grand->getRight();
      if (!node::isBlack(uncle)) {
        node::setBlack(uncle, true);
        node::setBlack(parent, true);
        node::setBlack(grand, false);
        t = grand;
      } else {
        if (t == parent->getRight()) {
          leftRotation(parent);
          t = parent;
          parent = t->getParent();
        }
        rightRotation(grand);
        bool is_blk = node::isBlack(parent);
        node::setBlack(parent, node::isBlack(grand));
        node::setBlack(grand, is_blk);
        t = parent;
      }
    } else {
      node *uncle = grand->getLeft();
      if (!node::isBlack(uncle)) {
        node::setBlack(uncle, true);
        node::setBlack(parent, true);
        node::setBlack(grand, false);
        t = grand;
      } else {
        if (t == parent->getLeft()) {
          rightRotation(parent);
          t = parent;
          parent = t->getParent();
        }
        leftRotation(grand);
        bool is_blk = node::isBlack(parent);
        node::setBlack(parent, node::isBlack(grand));
        node::setBlack(grand, is_blk);
        t = parent;
      }
    }
  }
  node::setBlack(root_, true);
}
