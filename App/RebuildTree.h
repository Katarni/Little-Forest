//
// Created by Тимур Ахметзянов on 04.05.2024.
//

#pragma once

#include "AVL.h"
#include "RB.h"
#include "Treap.h"
#include "TreeNode.h"


class RebuildTree {
 public:
  static void rebuildTreap(Treap& treap, std::vector<TreeNode*>& nodes, sf::RenderWindow* window);
  static void rebuildAVL(AVL& avl, std::vector<TreeNode*>& nodes, float size, float scale,
                         sf::Font& font, std::pair<float, float> start, sf::RenderWindow* window);
  static void rebuildRB(RB& rb, std::vector<TreeNode*>& nodes, float size, sf::RenderWindow* window);

 private:
  static TreeNode* rebuildAVL(AVL::node*& avl, sf::RenderWindow* window, int lvl = 2);
  static void fillAVL(TreeNode*& node, std::vector<TreeNode*>& nodes,
                      int max_lvl, sf::RenderWindow* window);
  static int getMaxLvl(TreeNode*& node);
};


TreeNode *RebuildTree::rebuildAVL(AVL::node *&avl, sf::RenderWindow *window, int lvl) {
  if (avl == nullptr) return nullptr;
  auto node = new TreeNode(avl->getKey(), window);
  node->setLvl(lvl);
  node->setLeftChild(rebuildAVL(avl->getLeft(), window, lvl + 1));
  node->setRightChild(rebuildAVL(avl->getRight(), window, lvl + 1));
  return node;
}

int RebuildTree::getMaxLvl(TreeNode *&node) {
  if (node == nullptr) return 0;
  return std::max(node->getLvl(), std::max(getMaxLvl(node->getLeftChild()), getMaxLvl(node->getRightChild())));
}

void RebuildTree::fillAVL(TreeNode *&node, std::vector<TreeNode *> &nodes, int max_lvl, sf::RenderWindow *window) {
  nodes.push_back(node);
  if (node->getLvl() == max_lvl) return;

  if (node->getLeftChild() == nullptr) {
    node->setLeftChild(new TreeNode(-1e18, window));
    node->getLeftChild()->setLvl(node->getLvl() + 1);
  }

  if (node->getRightChild() == nullptr) {
    node->setRightChild(new TreeNode(-1e18, window));
    node->getRightChild()->setLvl(node->getLvl() + 1);
  }

  fillAVL(node->getLeftChild(), nodes, max_lvl, window);
  fillAVL(node->getRightChild(), nodes, max_lvl, window);
}

void RebuildTree::rebuildTreap(Treap &treap, std::vector<TreeNode *> &nodes, sf::RenderWindow* window) {

}

void RebuildTree::rebuildAVL(AVL &avl, std::vector<TreeNode *> &nodes, float size, float scale,
                             sf::Font& font, std::pair<float, float> start, sf::RenderWindow* window) {
  for (auto& i : nodes) {
    delete i;
  }
  nodes.resize(0);
  if (avl.getRoot() == nullptr) return;
  auto node = new TreeNode(avl.getRoot()->getKey(), window);
  node->setLvl(1);
  node->setLeftChild(rebuildAVL(avl.getRoot()->getLeft(), window));
  node->setRightChild(rebuildAVL(avl.getRoot()->getRight(), window));

  int max_lvl = getMaxLvl(node);

  fillAVL(node, nodes, max_lvl, window);

  std::sort(nodes.begin(), nodes.end(), TreeNode::sortCmp);

  std::pair<float, float> prev = {0, 0};
  for (auto & item : nodes) {
    if (item->getLvl() == max_lvl) {
      item->setX(prev.first);
      item->setY(prev.second);
      prev.first += 1.75*size*scale;
    } else {
      item->setX((item->getRightChild()->getX() - item->getLeftChild()->getX()) / 2 +
                 item->getLeftChild()->getX());
      item->setY(item->getRightChild()->getY() - 1.5 * size*scale);
    }
    item->setWidth(size*scale);
    item->setHeight(size*scale);
    item->setBorderRadius(size*scale / 2);
    item->setBorderColor(sf::Color(235, 215, 245));
    item->setBorderBold(2*scale);
    if (scale < 1) {
      item->setFontSize(floor(15 * scale));
    } else {
      item->setFontSize(ceil(15 * scale));
    }
    item->setFont(font);
  }

  for (auto& item : nodes) {
    item->moveX(start.first - nodes.back()->getX());
    item->moveY(start.second - nodes.back()->getY());
  }
}

void RebuildTree::rebuildRB(RB &rb, std::vector<TreeNode *> &nodes,
                            float size, sf::RenderWindow* window) {

}
