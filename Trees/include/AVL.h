//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once

#include "AVLNode.h"


class AVL {
 public:
  AVL() : root_(nullptr) {}
  ~AVL() {
    AVLNode::clear(root_);
  }

  AVLNode*& getRoot() {
    return root_;
  }

  void insert(int64_t key);

  void insertNRandom(int64_t n);

  void erase(int64_t key);

  int64_t getHeight() const {
    return AVLNode::getHeight(root_);
  }

  int64_t getSize() const {
    return AVLNode::getSize(root_);
  }

  void clear();

 private:
  AVLNode *root_;

  bool find(AVLNode* node, int64_t key);
  void insert(AVLNode*& node, int64_t key);
  void erase(AVLNode*& node, int64_t key);
  int64_t delMin(AVLNode*& node);
  void clear(AVLNode*& node);

  static void smallLeftRotation(AVLNode*& t);
  static void smallRightRotation(AVLNode*& t);
  static void bigLeftRotation(AVLNode*& t);
  static void bigRightRotation(AVLNode*& t);

  static void balance(AVLNode *&node);
};


bool AVL::find(AVLNode* node, int64_t key) {
  if (node == nullptr) return false;
  if (node->getKey() == key) return true;
  return find(key > node->getKey() ? node->getRight() : node->getLeft(), key);
}

void AVL::insert(AVLNode*& node, int64_t key) {
  if (node == nullptr) {
    node = new AVLNode(key);
    return;
  }

  insert(key > node->getKey() ? node->getRight() : node->getLeft(), key);
  balance(node);
}

void AVL::insertNRandom(int64_t n) {
  int64_t key;
  while (n--) {
    key = rnd() % 100000;
    while (find(root_, key)) {
      key = rnd() % 100000;
    }
    insert(key);
  }
}

void AVL::insert(int64_t key) {
  if (find(root_, key)) return;
  insert(root_, key);
}

void AVL::balance(AVLNode*& node) {
  if (node == nullptr) return;
  AVLNode::update(node);
  if (abs(AVLNode::getHeight(node->getLeft()) - AVLNode::getHeight(node->getRight())) <= 1) return;

  if (AVLNode::getHeight(node->getLeft()) < AVLNode::getHeight(node->getRight())) {
    if (AVLNode::getHeight(node->getRight()->getLeft()) > AVLNode::getHeight(node->getRight()->getRight())) {
      bigLeftRotation(node);
    } else {
      smallLeftRotation(node);
    }
  } else {
    if (AVLNode::getHeight(node->getLeft()->getRight()) > AVLNode::getHeight(node->getLeft()->getLeft())) {
      bigRightRotation(node);
    } else {
      smallRightRotation(node);
    }
  }
  AVLNode::update(node->getLeft());
  AVLNode::update(node->getRight());
  AVLNode::update(node);
}

void AVL::smallLeftRotation(AVLNode *&t) {
  auto p = t->getRight();
  t->setRight(p->getLeft());
  p->setLeft(t);
  t = p;
}

void AVL::smallRightRotation(AVLNode *&t) {
  auto p = t->getLeft();
  t->setLeft(p->getRight());
  p->setRight(t);
  t = p;
}

void AVL::bigLeftRotation(AVLNode *&t) {
  auto p = t->getRight();
  auto q = p->getLeft();
  t->setRight(q->getLeft());
  p->setLeft(q->getRight());
  q->setLeft(t);
  q->setRight(p);
  t = q;
}

void AVL::bigRightRotation(AVLNode *&t) {
  auto p = t->getLeft();
  auto q = p->getRight();
  t->setLeft(q->getRight());
  p->setRight(q->getLeft());
  q->setRight(t);
  q->setLeft(p);
  t = q;
}

void AVL::erase(int64_t key) {
  erase(root_, key);
}

void AVL::erase(AVLNode *&node, int64_t key) {
  if (node == nullptr) return;
  if (key == node->getKey()) {
    if (node->getRight() != nullptr) {
      node->setKey(delMin(node->getRight()));
    } else if (node->getLeft() != nullptr) {
      node->setKey(node->getLeft()->getKey());
      delete node->getLeft();
      node->setLeft(nullptr);
    } else {
      delete node;
      node = nullptr;
    }
    balance(node);
    return;
  }

  if (key < node->getKey()) {
    erase(node->getLeft(), key);
  } else {
    erase(node->getRight(), key);
  }
  balance(node);
}

int64_t AVL::delMin(AVLNode *&node) {
  if (node == nullptr) return -1e18;
  if (node->getLeft() != nullptr) {
    int64_t key = delMin(node->getLeft());
    balance(node);
    return key;
  }

  int64_t key = node->getKey();
  if (node->getRight() != nullptr) {
    node->setKey(node->getRight()->getKey());
    delete node->getRight();
    node->setRight(nullptr);
  } else {
    delete node;
    node = nullptr;
  }
  return key;
}

void AVL::clear() {
  clear(root_);
  root_ = nullptr;
}

void AVL::clear(AVLNode *&node) {
  if (node == nullptr) return;
  clear(node->getLeft());
  clear(node->getRight());
  delete node;
}
