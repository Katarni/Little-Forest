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

  static void setCoordinates(TreeNode*& node, std::pair<float, float>& pos,
                             float size, float scale, sf::Font& font, std::vector<TreeNode*>& nodes);
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

void RebuildTree::setCoordinates(TreeNode *&node, std::pair<float, float> &pos,
                                 float size, float scale, sf::Font& font, std::vector<TreeNode*>& nodes) {
  node->setWidth(size*scale);
  node->setHeight(size*scale);
  node->setBorderRadius(size*scale / 2);
  node->setBorderColor(sf::Color(235, 215, 245));
  node->setBorderBold(2*scale);
  if (scale < 1) {
    node->setFontSize(15 * scale);
  } else {
    node->setFontSize(ceil(15 * scale));
  }
  node->setFont(font);

  if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
    node->setX(pos.first);
    node->setY(pos.second);
    pos.first += 1.75*size*scale;
    nodes.push_back(node);
    return;
  }

  setCoordinates(node->getLeftChild(), pos, size, scale, font, nodes);
  setCoordinates(node->getRightChild(), pos, size, scale, font, nodes);
  node->setX((node->getRightChild()->getX() - node->getLeftChild()->getX()) / 2 +
              node->getLeftChild()->getX());
  node->setY(node->getRightChild()->getY() - 1.5 * size*scale);
  nodes.push_back(node);
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

  std::pair<float, float> pos = {0, 0};
  setCoordinates(node, pos, size, scale, font, nodes);

  for (auto& item : nodes) {
    item->moveX(start.first - node->getX());
    item->moveY(start.second - node->getY());
  }
}

void RebuildTree::rebuildRB(RB &rb, std::vector<TreeNode *> &nodes,
                            float size, sf::RenderWindow* window) {

}
