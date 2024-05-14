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
                        is_black_(0) {}

    static void clear(node*& node) {
      if (node == nullptr) return;
      clear(node->left_);
      clear(node->right_);
      node->left_ = nullptr;
      node->right_ = nullptr;
      delete node;
    }

    static int isBlack(node* node) {
      if (node == nullptr) return true;
      return node->is_black_;
    }

    static void setBlack(node*& node, int black) {
      if (node == nullptr) return;
      node->is_black_ = black;
    }

    inline int64_t getKey() const {
      return key_;
    }

    void setKey(int64_t key) {
      key_ = key;
    }

    inline node* getLeft() const {
      return left_;
    }

    void setLeft(node *left) {
      left_ = left;
    }

    inline node* getRight() const {
      return right_;
    }

    void setRight(node *right) {
      right_ = right;
    }

    inline node* getParent() const {
      return parent_;
    }

    void setParent(node *parent) {
      parent_ = parent;
    }

    node*& left() {
      return left_;
    }

    node*& right() {
      return right_;
    }

   private:
    int64_t key_;
    node *left_, *right_, *parent_;
    int is_black_;
  };

  RB() : root_(nullptr) {}

  void insert(int64_t key);

  void erase(int64_t key);

  node*& getRoot() {
    return root_;
  }

  void clear() {
    node::clear(root_);
    root_ = nullptr;
  }

  void insertNRandom(int64_t n) {
    int64_t key;
    while (n--) {
      key = rnd() % 100000;
      while (find(root_, key)) {
        key = rnd() % 100000;
      }
      insert(key);
    }
  }

 private:
  node *root_;

  node* insert(node*& root, node*& t);

  void rightRotation(node*& t);
  void leftRotation(node*& t);

  void balanceInsert(node*& t);
  void balanceErase(node*& t);

  node* erase(node*& t, int64_t key);

  node* minNode(node*& t);

  bool find(node*& t, int64_t key);
};

void RB::insert(int64_t key) {
  node* t = new node(key);
  root_ = insert(root_, t);
  balanceInsert(t);
}

RB::node *RB::insert(RB::node *&root, RB::node *&t) {
  if (root == nullptr) {
    return t;
  }

  if (t->getKey() < root->getKey()) {
    root->setLeft(insert(root->left(), t));
    root->getLeft()->setParent(root);
  } else if (t->getKey() > root->getKey()) {
    root->setRight(insert(root->right(), t));
    root->getRight()->setParent(root);
  }

  return root;
}

void RB::rightRotation(RB::node *&t) {
  auto left = t->getLeft();
  t->setLeft(left->getRight());

  if (t->getLeft() != nullptr)
    t->getLeft()->setParent(t);

  left->setParent(t->getParent());

  if (t->getParent() == nullptr) {
    root_ = left;
  } else if (t == t->getParent()->getLeft()) {
    t->getParent()->setLeft(left);
  } else {
    t->getParent()->setRight(left);
  }

  left->setRight(t);
  t->setParent(left);
}

void RB::leftRotation(RB::node *&t) {
  auto right = t->getRight();
  t->setRight(right->getLeft());

  if (t->getRight() != nullptr)
    t->getRight()->setParent(t);

  right->setParent(t->getParent());

  if (t->getParent() == nullptr) {
    root_ = right;
  } else if (t == t->getParent()->getLeft()) {
    t->getParent()->setLeft(right);
  } else {
    t->getParent()->setRight(right);
  }

  right->setLeft(t);
  t->setParent(right);
}

void RB::balanceInsert(RB::node *&t) {
  node* parent;
  node* grand;
  while (t != root_ && !node::isBlack(t) && !node::isBlack(t->getParent())) {
    parent = t->getParent();
    grand = parent->getParent();
    if (parent == grand->getLeft()) {
      node* uncle = grand->getRight();
      if (!node::isBlack(uncle)) {
        node::setBlack(uncle, true);
        node::setBlack(parent, true);
        node::setBlack(grand, false);
        t = grand;
      } else {
        if (t == parent->getRight()) {
          leftRotation(parent);
          t = parent;
          parent = t->getParent();
        }
        rightRotation(grand);
        bool is_blk = node::isBlack(parent);
        node::setBlack(parent, node::isBlack(grand));
        node::setBlack(grand, is_blk);
        t = parent;
      }
    } else {
      node *uncle = grand->getLeft();
      if (!node::isBlack(uncle)) {
        node::setBlack(uncle, true);
        node::setBlack(parent, true);
        node::setBlack(grand, false);
        t = grand;
      } else {
        if (t == parent->getLeft()) {
          rightRotation(parent);
          t = parent;
          parent = t->getParent();
        }
        leftRotation(grand);
        bool is_blk = node::isBlack(parent);
        node::setBlack(parent, node::isBlack(grand));
        node::setBlack(grand, is_blk);
        t = parent;
      }
    }
  }
  node::setBlack(root_, true);
}

void RB::erase(int64_t key) {
  auto t = erase(root_, key);
  balanceErase(t);
}

RB::node *RB::erase(RB::node *&t, int64_t key) {
  if (t == nullptr) {
    return t;
  }

  if (key < t->getKey()) {
    return erase(t->left(), key);
  } else if (key > t->getKey()) {
    return erase(t->right(), key);
  }

  if (t->getLeft() == nullptr || t->getRight() == nullptr)
    return t;

  auto tmp = minNode(t->right());
  t->setKey(tmp->getKey());
  return erase(t->right(), tmp->getKey());
}

void RB::balanceErase(RB::node *&t) {
  if (t == nullptr)
    return;

  if (t == root_) {
    root_ = nullptr;
    return;
  }

  if (!node::isBlack(t) || !node::isBlack(t->getLeft()) || !node::isBlack(t->getRight())) {
    node* child = t->getLeft() != nullptr ? t->getLeft() : t->getRight();

    if (t == t->getParent()->getLeft()) {
      t->getParent()->setLeft(child);
      if (child != nullptr) {
        child->setParent(t->getParent());
      }
      node::setBlack(child, true);
      delete t;
    } else {
      t->getParent()->setRight(child);
      if (child != nullptr) {
        child->setParent(t->getParent());
      }
      node::setBlack(child, true);
      delete t;
    }
  } else {
    node *sibling;
    node *parent;
    node *ptr = t;
    node::setBlack(ptr, 2);
    while (ptr != root_ && node::isBlack(ptr) == 2) {
      parent = ptr->getParent();
      if (ptr == parent->getLeft()) {
        sibling = parent->getRight();
        if (!node::isBlack(sibling)) {
          node::setBlack(sibling, 1);
          node::setBlack(parent, 0);
          leftRotation(parent);
        } else {
          if (node::isBlack(sibling->getLeft()) == 1 && node::isBlack(sibling->getRight()) == 1) {
            node::setBlack(sibling, 0);
            if (!node::isBlack(parent)) {
              node::setBlack(parent, 1);
            } else {
              node::setBlack(parent, 2);
            }
            ptr = parent;
          } else {
            if (node::isBlack(sibling->getRight()) == 1) {
              node::setBlack(sibling->left(), 1);
              node::setBlack(sibling, 0);
              rightRotation(sibling);
              sibling = parent->getRight();
            }
            node::setBlack(sibling, node::isBlack(parent));
            node::setBlack(parent, 1);
            node::setBlack(sibling->right(), 1);
            leftRotation(parent);
            break;
          }
        }
      } else {
        sibling = parent->getLeft();
        if (!node::isBlack(sibling)) {
          node::setBlack(sibling, 1);
          node::setBlack(parent, 0);
          rightRotation(parent);
        } else {
          if (node::isBlack(sibling->getLeft()) == 1 && node::isBlack(sibling->getRight()) == 1) {
            node::setBlack(sibling, 0);
            if (!node::isBlack(parent)) {
              node::setBlack(parent, 1);
            } else {
              node::setBlack(parent, 2);
            }
            ptr = parent;
          } else {
            if (node::isBlack(sibling->getLeft()) == 1) {
              node::setBlack(sibling->right(), 1);
              node::setBlack(sibling, 0);
              leftRotation(sibling);
              sibling = parent->getLeft();
            }
            node::setBlack(sibling, node::isBlack(parent));
            node::setBlack(parent, 1);
            node::setBlack(sibling->left(), 1);
            rightRotation(parent);
            break;
          }
        }
      }
    }
    if (t == t->getParent()->getLeft()) {
      t->getParent()->setLeft(nullptr);
    } else {
      t->getParent()->setRight(nullptr);
    }
    delete t;
    node::setBlack(root_, 1);
  }
}

RB::node* RB::minNode(RB::node *&t) {
  if (t->left() == nullptr) return t;
  return minNode(t->left());
}

bool RB::find(RB::node *&t, int64_t key) {
  if (t == nullptr) return false;
  if (t->getKey() == key) return true;

  return find(t->getKey() < key ? t->right() : t->left(), key);
}
