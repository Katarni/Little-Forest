//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once

#include "includes.h"

class AVL {
 public:


  class node {
   public:
    node(int64_t key) : key_(key), height_(1), left_(nullptr), right_(nullptr), size_(1), leafs_(1) {}

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

    static int64_t getHeight(node* node) {
      if (node == nullptr) return 0;
      return node->height_;
    }

    static int64_t getLeafs(node* node) {
      if (node == nullptr) return 0;
      return node->leafs_;
    }

    static int64_t getSize(node* node) {
      if (node == nullptr) return 0;
      return node->size_;
    }

    static void update(node*& node) {
      if (node == nullptr) return;
      node->height_ = std::max(getHeight(node->getLeft()), getHeight(node->getRight())) + 1;
      node->size_ = getSize(node->getLeft()) + getSize(node->getRight()) + 1;
      node->leafs_ = getLeafs(node->getLeft()) + getLeafs(node->getRight()) + (node->getRight() == nullptr &&
                                                                               node->getLeft() == nullptr);
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

    void setKey(int64_t key) {
      key_ = key;
    }

   private:
    int64_t height_, key_, size_, leafs_;
    node *left_, *right_;
  };


  AVL() : root_(nullptr) {}
  ~AVL() {
    node::clear(root_);
  }

  node*& getRoot() {
    return root_;
  }

  void insert(int64_t key);

  void insertNRandom(int64_t n);

  void erase(int64_t key);

  int64_t getHeight() const {
    return node::getHeight(root_);
  }

  int64_t getSize() const {
    return node::getSize(root_);
  }

  void clear();

 private:
  node *root_;

  bool find(node* node, int64_t key);
  void insert(node*& node, int64_t key);
  void erase(node*& node, int64_t key);
  int64_t delMin(node*& node);
  void clear(node*& node);

  static void smallLeftRotation(node*& t);
  static void smallRightRotation(node*& t);
  static void bigLeftRotation(node*& t);
  static void bigRightRotation(node*& t);

  static void balance(node *&node);
};


bool AVL::find(node* node, int64_t key) {
  if (node == nullptr) return false;
  if (node->getKey() == key) return true;
  return find(key > node->getKey() ? node->getRight() : node->getLeft(), key);
}

void AVL::insert(node*& node, int64_t key) {
  if (node == nullptr) {
    node = new AVL::node(key);
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

void AVL::balance(node*& node) {
  if (node == nullptr) return;
  node::update(node);
  if (abs(node::getHeight(node->getLeft()) - node::getHeight(node->getRight())) <= 1) return;

  if (node::getHeight(node->getLeft()) < node::getHeight(node->getRight())) {
    if (node::getHeight(node->getRight()->getLeft()) > node::getHeight(node->getRight()->getRight())) {
      bigLeftRotation(node);
    } else {
      smallLeftRotation(node);
    }
  } else {
    if (node::getHeight(node->getLeft()->getRight()) > node::getHeight(node->getLeft()->getLeft())) {
      bigRightRotation(node);
    } else {
      smallRightRotation(node);
    }
  }
  node::update(node->getLeft());
  node::update(node->getRight());
  node::update(node);
}

void AVL::smallLeftRotation(node *&t) {
  auto p = t->getRight();
  t->setRight(p->getLeft());
  p->setLeft(t);
  t = p;
}

void AVL::smallRightRotation(node *&t) {
  auto p = t->getLeft();
  t->setLeft(p->getRight());
  p->setRight(t);
  t = p;
}

void AVL::bigLeftRotation(node *&t) {
  auto p = t->getRight();
  auto q = p->getLeft();
  t->setRight(q->getLeft());
  p->setLeft(q->getRight());
  q->setLeft(t);
  q->setRight(p);
  t = q;
}

void AVL::bigRightRotation(node *&t) {
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

void AVL::erase(node *&node, int64_t key) {
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

int64_t AVL::delMin(node *&node) {
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

void AVL::clear(node *&node) {
  if (node == nullptr) return;
  clear(node->getLeft());
  clear(node->getRight());
  delete node;
}
