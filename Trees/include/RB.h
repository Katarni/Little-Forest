//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once

#include "RBNode.h"


class RB {
 public:
  RB() : root_(nullptr) {}

  bool find(int64_t key);
  void insert(int64_t key);

 private:
  RBNode *root_;

  bool find(RBNode* node, int64_t key);
  void insert(RBNode*& node, int64_t key);

  static void balanceInsert(RBNode*& node);

  static void leftRotation(RBNode*& t);
  static void rightRotation(RBNode*& t);
};

bool RB::find(RBNode* node, int64_t key) {
  if (node == nullptr) return false;
  if (node->getKey() == key) return true;
  return find(key > node->getKey() ? node->getRight() : node->getLeft(), key);
}

bool RB::find(int64_t key) {
  return find(root_, key);
}

void RB::insert(RBNode*& node, int64_t key) {
  if (node == nullptr) {
    node = new RBNode(key);
    balanceInsert(node);
  }

  if (key > node->getKey()) {
    if (node->getRight() == nullptr) {
      node->setRight(new RBNode(key));
      node->getRight()->setParent(node);
      balanceInsert(node->getRight());
    } else {
      insert(node->getRight(), key);
    }
  } else {
    if (node->getLeft() == nullptr) {
      node->setLeft(new RBNode(key));
      node->getLeft()->setParent(node);
      balanceInsert(node->getLeft());
    } else {
      insert(node->getLeft(), key);
    }
  }
}

void RB::insert(int64_t key) {
  if (find(key)) return;
  insert(root_, key);
}

void RB::balanceInsert(RBNode *&node) {
  while (true) {
    if (node == nullptr) return;

    if (node->getParent() == nullptr) {
      node->setBlack(true);
      RBNode::updateHeight(node->getLeft());
      RBNode::updateHeight(node->getRight());
      RBNode::updateHeight(node);
      return;
    }

    if (RBNode::isBlack(node->getParent())) return;

    if (!RBNode::isBlack(node->getUncle())) {
      node->getGrandparent()->setBlack(false);
      node->getParent()->setBlack(true);
      node->getUncle()->setBlack(true);
      RBNode::updateHeight(node);
      RBNode::updateHeight(node->getParent());
      RBNode::updateHeight(node->getUncle());
      RBNode::updateHeight(node->getGrandparent());
      node = node->getGrandparent();
      continue;
    }

    if (node->getParent()->isLeftChild() == node->isLeftChild()) {
      node->getParent()->setBlack(true);
      node->getGrandparent()->setBlack(false);
      if (node->isLeftChild()) {
        rightRotation(node->getGrandparent());
      } else {
        leftRotation(node->getGrandparent());
      }

      RBNode::updateHeight(node->getUncle());
      RBNode::updateHeight(node);
      RBNode::updateHeight(node->getParent());
      RBNode::updateHeight(node->getGrandparent());
    }

    // 3.2.2
  }
}

void RB::rightRotation(RBNode *&t) {
  auto p = t->getLeft();
  p->getRight()->setParent(p->getParent());
  p->setParent(t->getParent());
  p->setRight(t);
  t->setParent(p);
  t = p;
}

void RB::leftRotation(RBNode *&t) {
  auto p = t->getRight();
  p->getLeft()->setParent(p->getParent());
  p->setParent(t->getParent());
  p->setLeft(t);
  t->setParent(p);
  t = p;
}
