//
// Created by Тимур Ахметзянов on 10.05.2024.
//

#pragma once

#include "includes.h"

class Splay {
 public:

  class node {
   public:
    node(int64_t key) : key_(key), left_(nullptr), right_(nullptr) {}

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

   private:
    int64_t key_;
    node *left_, *right_;
  };


};
