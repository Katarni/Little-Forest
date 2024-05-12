//
// Created by Тимур Ахметзянов on 04.05.2024.
//

#pragma once

#include "KatLib.h"


class TreeNode : public kat::Button {
 public:
  TreeNode() : kat::Button(), key_(0), priority_(-1e18), scale_(1),
               left_child_(nullptr), right_child_(nullptr), lvl_(0),
               audio_id_(-1), rb_color_(-1) {}
  TreeNode(sf::RenderWindow* parent) : kat::Button(parent), key_(0), priority_(-1e18), scale_(1),
                                       left_child_(nullptr), right_child_(nullptr),
                                       lvl_(0), audio_id_(-1), rb_color_(-1) {}
  TreeNode(int64_t key, sf::RenderWindow* parent) : kat::Button(parent), scale_(1),
                                                    left_child_(nullptr), right_child_(nullptr),
                                                    lvl_(0), audio_id_(-1), rb_color_(-1) {
    setData(std::to_string(key));
    priority_ = -1e18;
    key_ = key;
  }

  int64_t getKey() const;
  void setKey(int64_t key);
  int64_t getPriority() const;
  void setPriority(int64_t priority);
  int getLvl() const;
  void setLvl(int lvl);

  TreeNode *&getLeftChild();
  void setLeftChild(TreeNode *leftChild);
  TreeNode *&getRightChild();
  void setRightChild(TreeNode *rightChild);

  static double dis(TreeNode* node1, TreeNode* node2) {
    return abs(node1->getCenterX() - node2->getCenterX()) +
           abs(node1->getCenterY() - node2->getCenterY());
  }

  static bool sortCmp(TreeNode* lhs, TreeNode* rhs) {
    return lhs->lvl_ > rhs->lvl_;
  }

  int getAudioId() const;

  void setAudioId(int audioId);

 private:
  float scale_;
  int lvl_, rb_color_;
  int64_t key_, priority_;
  TreeNode *left_child_, *right_child_;

  int audio_id_;
};


TreeNode *&TreeNode::getLeftChild() {
  return left_child_;
}

void TreeNode::setLeftChild(TreeNode *leftChild) {
  left_child_ = leftChild;
}

TreeNode *&TreeNode::getRightChild() {
  return right_child_;
}

void TreeNode::setRightChild(TreeNode *rightChild) {
  right_child_ = rightChild;
}

int64_t TreeNode::getKey() const {
  return key_;
}

void TreeNode::setKey(int64_t key) {
  key_ = key;
  if (priority_ != -1e18) {
    setData(std::to_string(key_) + "\n" + std::to_string(priority_));
  } else {
    setData(std::to_string(key_));
  }
}

int64_t TreeNode::getPriority() const {
  return priority_;
}

void TreeNode::setPriority(int64_t priority) {
  priority_ = priority;
  setData(std::to_string(key_) + "\n" + std::to_string(priority_));
}

int TreeNode::getLvl() const {
  return lvl_;
}

void TreeNode::setLvl(int lvl) {
  TreeNode::lvl_ = lvl;
}

int TreeNode::getAudioId() const {
  return audio_id_;
}

void TreeNode::setAudioId(int audioId) {
  audio_id_ = audioId;
}
