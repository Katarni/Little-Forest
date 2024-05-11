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
                        is_black_(false), black_height_(0) {}

    static void clear(node*& node) {
      if (node == nullptr) return;
      clear(node->left_);
      clear(node->right_);
      delete node;
    }

    static int64_t getBlackHeight(node* node) {
      if (node == nullptr) return 1;
      return node->black_height_;
    }

    static void updateHeight(node*& node) {
      if (node == nullptr) return;
      node->black_height_ = getBlackHeight(node->left_) + node->is_black_;
    }

    static bool isBlack(node* node) {
      if (node == nullptr) return true;
      return node->is_black_;
    }

    void setBlack(bool is_black) {
      is_black_ = is_black;
    }

    inline int64_t getKey() const {
      return key_;
    }

    inline node*& getLeft() {
      return left_;
    }

    void setLeft(node *left) {
      left_ = left;
    }

    inline node*& getRight() {
      return right_;
    }

    void setRight(node *right) {
      right_ = right;
    }

    inline node*& getParent() {
      return parent_;
    }

    void setParent(node *parent) {
      parent_ = parent;
    }

    inline node*& getGrandparent() {
      return parent_->parent_;
    }

    inline node*& getUncle() {
      auto grandparent = getGrandparent();
      if (parent_->key_ == grandparent->left_->key_) return grandparent->right_;
      return grandparent->left_;
    }

    inline bool isLeftChild() {
      return parent_->left_->key_ == key_;
    }

   private:
    int64_t key_, black_height_;
    node *left_, *right_, *parent_;
    bool is_black_;
  };


  RB() : root_(nullptr) {}

  void insert(int64_t key);

  node *&getRoot();

 private:
  node *root_;

  bool find(node* node, int64_t key);
  void insert(node*& node, int64_t key);

  static void balanceInsert(node*& node);

  static void leftRotation(node*& t);
  static void rightRotation(node*& t);
};

bool RB::find(node* node, int64_t key) {
  if (node == nullptr) return false;
  if (node->getKey() == key) return true;
  return find(key > node->getKey() ? node->getRight() : node->getLeft(), key);
}

void RB::insert(node*& node, int64_t key) {
  if (node == nullptr) {
    node = new RB::node(key);
    balanceInsert(node);
  }

  if (key > node->getKey()) {
    if (node->getRight() == nullptr) {
      node->setRight(new RB::node(key));
      node->getRight()->setParent(node);
      balanceInsert(node->getRight());
    } else {
      insert(node->getRight(), key);
    }
  } else {
    if (node->getLeft() == nullptr) {
      node->setLeft(new RB::node(key));
      node->getLeft()->setParent(node);
      balanceInsert(node->getLeft());
    } else {
      insert(node->getLeft(), key);
    }
  }
}

void RB::insert(int64_t key) {
  if (find(root_, key)) return;
  insert(root_, key);
}

void RB::balanceInsert(node *&node) {
  while (true) {
    if (node == nullptr) return;

    if (node->getParent() == nullptr) {
      node->setBlack(true);
      node::updateHeight(node->getLeft());
      node::updateHeight(node->getRight());
      node::updateHeight(node);
      return;
    }

    if (node::isBlack(node->getParent())) return;

    if (!node::isBlack(node->getUncle())) {
      node->getGrandparent()->setBlack(false);
      node->getParent()->setBlack(true);
      node->getUncle()->setBlack(true);
      node::updateHeight(node);
      node::updateHeight(node->getParent());
      node::updateHeight(node->getUncle());
      node::updateHeight(node->getGrandparent());
      node = node->getGrandparent();
      continue;
    }

    if (node->getParent()->isLeftChild() == node->isLeftChild()) {
      node->getParent()->setBlack(true);
      node->getGrandparent()->setBlack(false);
      if (node->isLeftChild()) {
        rightRotation(node->getGrandparent());
      } else {
        leftRotation(node->getGrandparent());
      }

      node::updateHeight(node->getUncle());
      node::updateHeight(node);
      node::updateHeight(node->getParent());
      node::updateHeight(node->getGrandparent());
    }

    // 3.2.2
  }
}

void RB::rightRotation(node *&t) {
  auto p = t->getLeft();
  p->getRight()->setParent(p->getParent());
  p->setParent(t->getParent());
  p->setRight(t);
  t->setParent(p);
  t = p;
}

void RB::leftRotation(node *&t) {
  auto p = t->getRight();
  p->getLeft()->setParent(p->getParent());
  p->setParent(t->getParent());
  p->setLeft(t);
  t->setParent(p);
  t = p;
}

RB::node *&RB::getRoot() {
  return root_;
}
