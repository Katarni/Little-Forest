//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once

#include "includes.h"


class AVLNode {
 public:
  AVLNode(int64_t key) : key_(key), height_(1), left_(nullptr), right_(nullptr) {}

  AVLNode*& getLeft() {
    return left_;
  }

  AVLNode*& getRight() {
    return right_;
  }

  void setLeft(AVLNode* left) {
    left_ = left;
  }

  void setRight(AVLNode* right) {
    right_ = right;
  }

  static int64_t getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height_;
  }

  static void updateHeight(AVLNode*& node) {
    if (node == nullptr) return;
    node->height_ = std::max(getHeight(node->getLeft()), getHeight(node->getRight())) + 1;
  }

  static void clear(AVLNode*& node) {
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
  int64_t height_, key_;
  AVLNode *left_, *right_;
};
