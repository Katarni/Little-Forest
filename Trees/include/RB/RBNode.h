//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once


#include "../includes.h"

class RBNode {
 public:
  RBNode(int64_t key) : key_(key), left_(nullptr), right_(nullptr), parent_(nullptr),
                        is_black_(false), black_height_(0), height_(0) {}

  static void clear(RBNode*& node) {
    if (node == nullptr) return;
    clear(node->left_);
    clear(node->right_);
    delete node;
  }

  static int64_t getBlackHeight(RBNode* node) {
    if (node == nullptr) return 1;
    return node->black_height_;
  }

  static void updateHeight(RBNode*& node) {
    if (node == nullptr) return;
    node->black_height_ = getBlackHeight(node->left_) + node->is_black_;
    node->height_ = std::max(getHeight(node->left_), getHeight(node->right_)) + 1;
  }

  static int64_t getHeight(RBNode* node) {
    if (node == nullptr) return 1;
    return node->height_;
  }

  static bool isBlack(RBNode* node) {
    if (node == nullptr) return true;
    return node->is_black_;
  }

  void setBlack(bool is_black) {
    is_black_ = is_black;
  }

  inline int64_t getKey() const {
    return key_;
  }

  inline RBNode*& getLeft() {
    return left_;
  }

  void setLeft(RBNode *left) {
    left_ = left;
  }

  inline RBNode*& getRight() {
    return right_;
  }

  void setRight(RBNode *right) {
    right_ = right;
  }

  inline RBNode*& getParent() {
    return parent_;
  }

  void setParent(RBNode *parent) {
    parent_ = parent;
  }

  inline RBNode*& getGrandparent() {
    return parent_->parent_;
  }

  inline RBNode*& getUncle() {
    auto grandparent = getGrandparent();
    if (parent_->key_ == grandparent->left_->key_) return grandparent->right_;
    return grandparent->left_;
  }

  inline bool isLeftChild() {
    return parent_->left_->key_ == key_;
  }

 private:
  int64_t key_, black_height_, height_;
  RBNode *left_, *right_, *parent_;
  bool is_black_;
};
