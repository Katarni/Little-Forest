//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "includes.h"


class Treap {
 public:

  class node {
   public:
    node(int64_t key) : key_(key), priority_(rnd() % 100000),
                        left_(nullptr), right_(nullptr) {}

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

    static void clear(node*& node) {
      if (node == nullptr) return;
      clear(node->left_);
      clear(node->right_);
      delete node;
    }

    int64_t getKey() const {
      return key_;
    }

    int64_t getPriority() const {
      return priority_;
    }

   private:
    int64_t key_, priority_;
    node *left_, *right_;
  };


  Treap() : root_(nullptr) {}
  ~Treap() {
    node::clear(root_);
  }

  void insert(int64_t key);
  void insertNRandom(int64_t n);

  void erase(int64_t key);

  node *&getRoot();

  void clear();

 private:
  node *root_;

  static std::pair<node*, node*> split(node* treap, int64_t key);
  static node* merge(node* lower, node* upper);

  bool find(node* treap, int64_t elm);
  void erase(node*& treap, int64_t key);

  void clear(node*& node);
};

std::pair<Treap::node *, Treap::node *> Treap::split(node *treap, int64_t key) {
  if (treap == nullptr) return {nullptr, nullptr};
  if (treap->getKey() > key) {
    auto treap_s = split(treap->getLeft(), key);
    treap->setLeft(treap_s.second);
    return {treap_s.first, treap};
  }

  auto treap_s = split(treap->getRight(), key);
  treap->setRight(treap_s.first);
  return {treap, treap_s.second};
}

Treap::node *Treap::merge(node *lower, node *upper) {
  if (lower == nullptr || upper == nullptr) {
    return lower == nullptr ? upper : lower;
  }

  if (lower->getPriority() > upper->getPriority()) {
    lower->setRight(merge(lower->getRight(), upper));
    return lower;
  }

  upper->setLeft(merge(lower, upper->getLeft()));
  return upper;
}

bool Treap::find(node *treap, int64_t elm) {
  if (treap == nullptr) return false;
  if (treap->getKey() == elm) return true;
  return find(treap->getKey() < elm ? treap->getRight() : treap->getLeft(), elm);
}

void Treap::insert(int64_t key) {
  if (find(root_, key)) return;
  auto treap_s = split(root_, key);
  root_ = merge(merge(treap_s.first, new node(key)), treap_s.second);
}

Treap::node *&Treap::getRoot() {
  return root_;
}

void Treap::erase(int64_t key) {
  if (!find(root_, key)) return;

  erase(root_, key);
}

void Treap::erase(node *&treap, int64_t key) {
  if (treap == nullptr) return;
  if (treap->getKey() == key) {
    auto q = treap;
    treap = merge(treap->getLeft(), treap->getRight());
    delete q;
    return;
  }
  if (key < treap->getKey()) {
    erase(treap->getLeft(), key);
  } else {
    erase(treap->getRight(), key);
  }
}

void Treap::insertNRandom(int64_t n) {
  int64_t key;
  while (n--) {
    key = rnd() % 100000;
    while (find(root_, key)) {
      key = rnd() % 100000;
    }
    insert(key);
  }
}

void Treap::clear() {
  clear(root_);
  root_ = nullptr;
}

void Treap::clear(node *&node) {
  if (node == nullptr) return;
  clear(node->getLeft());
  clear(node->getRight());
  delete node;
}
