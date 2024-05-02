//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "TreapNode.h"


class Treap {
 public:
  Treap() : root_(nullptr) {}
  ~Treap() {
    TreapNode::clear(root_);
  }

  int64_t getHeight() const {
    return TreapNode::getHeight(root_);
  }

  void insert(int64_t key);
  void insertNRandom(int64_t n);

  void erase(int64_t key);

  TreapNode *&getRoot();

  void clear();

 private:
  TreapNode *root_;

  static std::pair<TreapNode*, TreapNode*> split(TreapNode* treap, int64_t key);
  static TreapNode* merge(TreapNode* lower, TreapNode* upper);

  bool find(TreapNode* treap, int64_t elm);
  void erase(TreapNode*& treap, int64_t key);

  void clear(TreapNode*& node);
};

std::pair<TreapNode *, TreapNode *> Treap::split(TreapNode *treap, int64_t key) {
  if (treap == nullptr) return {nullptr, nullptr};
  if (treap->getKey() > key) {
    auto treap_s = split(treap->getLeft(), key);
    treap->setLeft(treap_s.second);
    TreapNode::updateHeight(treap);
    return {treap_s.first, treap};
  }

  auto treap_s = split(treap->getRight(), key);
  treap->setRight(treap_s.first);
  TreapNode::updateHeight(treap);
  return {treap, treap_s.second};
}

TreapNode *Treap::merge(TreapNode *lower, TreapNode *upper) {
  if (lower == nullptr || upper == nullptr) {
    return lower == nullptr ? upper : lower;
  }

  if (lower->getPriority() > upper->getPriority()) {
    lower->setRight(merge(lower->getRight(), upper));
    TreapNode::updateHeight(lower);
    return lower;
  }

  upper->setLeft(merge(lower, upper->getLeft()));
  TreapNode::updateHeight(upper);
  return upper;
}

bool Treap::find(TreapNode *treap, int64_t elm) {
  if (treap == nullptr) return false;
  if (treap->getKey() == elm) return true;
  return find(treap->getKey() < elm ? treap->getRight() : treap->getLeft(), elm);
}

void Treap::insert(int64_t key) {
  if (find(root_, key)) return;
  auto treap_s = split(root_, key);
  root_ = merge(merge(treap_s.first, new TreapNode(key)), treap_s.second);
}

TreapNode *&Treap::getRoot() {
  return root_;
}

void Treap::erase(int64_t key) {
  if (!find(root_, key)) return;

  erase(root_, key);
}

void Treap::erase(TreapNode *&treap, int64_t key) {
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
  TreapNode::updateHeight(treap);
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

void Treap::clear(TreapNode *&node) {
  if (node == nullptr) return;
  clear(node->getLeft());
  clear(node->getRight());
  delete node;
}
