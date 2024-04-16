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

 private:
  TreapNode *root_;

  static std::pair<TreapNode*, TreapNode*> split(TreapNode* treap, int64_t key);
  static TreapNode* merge(TreapNode* lower, TreapNode* upper);

  bool find(TreapNode* treap, int64_t elm);
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
