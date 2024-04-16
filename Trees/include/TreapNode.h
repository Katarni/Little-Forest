//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "includes.h"


class TreapNode {
 public:
  TreapNode(int64_t key) : key_(key), height_(1), priority_(rnd()),
                           left_(nullptr), right_(nullptr) {}

  TreapNode*& getLeft() {
    return left_;
  }

  TreapNode*& getRight() {
    return right_;
  }

  void setLeft(TreapNode* left) {
    left_ = left;
  }

  void setRight(TreapNode* right) {
    right_ = right;
  }

  static int64_t getHeight(TreapNode* node) {
    if (node == nullptr) return 0;
    return node->height_;
  }

  static void updateHeight(TreapNode*& node) {
    if (node == nullptr) return;
    node->height_ = std::max(getHeight(node->getLeft()), getHeight(node->getRight())) + 1;
  }

  static void clear(TreapNode*& node) {
    if (node == nullptr) return;
    clear(node->left_);
    clear(node->right_);
    delete node;
  }

  int64_t getKey() const {
    return key_;
  }

 private:
  int64_t key_, height_, priority_;
  TreapNode *left_, *right_;
};
