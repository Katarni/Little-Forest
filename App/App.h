//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "AVL.h"
#include "RB.h"
#include "Treap.h"
#include "KatLib.h"


class App {
 public:
  App();

  void render();

 private:
  Treap treap_;
  AVL avl_tree_;
  RB rb_tree_;

  float scale_ = 1;
  float node_radius_ = 30;

  bool shift_key_, redraw_trees_;
  bool need_interface_update_;
  sf::Color main_violet_;
  sf::Font regular_font_;

  sf::RenderWindow* window_;
  kat::Div buttons_palette_;

  kat::ScrollArea treap_area_;
  std::vector<kat::Line> treap_edges_;

  kat::ScrollArea avl_area_;
  std::vector<kat::Line> avl_edges_;

  kat::TextInput vertex_input_;
  kat::Button add_vertex_btn_;

  kat::SelectedItem avl_btn_, rb_btn_, treap_btn_, splay_btn_;

  void moveCursorLeft();
  void moveCursorRight();
  void enterPressed();
  void deleteCharacter();
  void addCharacter(sf::Event& e);
  void leftMousePressed(sf::Event& e);

  void addVertex();

  void drawTreap(TreapNode* t, float x = 600, float y = 175);
  void drawAVL(AVLNode* t, float x = 600, float y = 175);
  void drawRB(RBNode* t);
  void drawSplay();
};


App::App() {
  shift_key_ = false;
  redraw_trees_ = false;
  need_interface_update_ = true;

  window_ = new sf::RenderWindow(sf::VideoMode(1200, 750), "My little forest");
  main_violet_ = sf::Color(235, 215, 245);
  regular_font_.loadFromFile("../App/fonts/KodeMono.ttf");

  buttons_palette_ = kat::Div(5, 5, 190, 740, window_);
  buttons_palette_.setBackgroundColor(main_violet_);
  buttons_palette_.setBorderRadius(10);
  buttons_palette_.setNeedRender(false);

  vertex_input_ = kat::TextInput(15, 55, 170, 40, regular_font_, window_);
  vertex_input_.setFontSize(20);
  vertex_input_.setBorderRadius(10);

  add_vertex_btn_ = kat::Button(15, 110, 170, 40, "add vertex", regular_font_, window_);
  add_vertex_btn_.setFontSize(20);
  add_vertex_btn_.setBorderRadius(10);

  avl_btn_ = kat::SelectedItem(700, 0, 120, 25, "AVL", regular_font_, window_);
  avl_btn_.setSelectedColor(main_violet_);
  avl_btn_.setFontSize(18);
  avl_btn_.setBorderRadius(5);
  avl_btn_.setBorderBold(2);
  avl_btn_.setBorderColor(main_violet_);

  treap_btn_ = kat::SelectedItem(825, 0, 120, 25, "Treap", regular_font_, window_);
  treap_btn_.setSelectedColor(main_violet_);
  treap_btn_.setFontSize(18);
  treap_btn_.setBorderRadius(5);
  treap_btn_.setBorderBold(2);
  treap_btn_.setBorderColor(main_violet_);
  treap_btn_.setIsSelected(true);

  rb_btn_ = kat::SelectedItem(950, 0, 120, 25, "RB", regular_font_, window_);
  rb_btn_.setSelectedColor(main_violet_);
  rb_btn_.setFontSize(18);
  rb_btn_.setBorderRadius(5);
  rb_btn_.setBorderBold(2);
  rb_btn_.setBorderColor(main_violet_);

  splay_btn_ = kat::SelectedItem(1075, 0, 120, 25, "Splay", regular_font_, window_);
  splay_btn_.setSelectedColor(main_violet_);
  splay_btn_.setFontSize(18);
  splay_btn_.setBorderRadius(5);
  splay_btn_.setBorderBold(2);
  splay_btn_.setBorderColor(main_violet_);

  treap_area_ = kat::ScrollArea(0, 0, 1200, 750, window_);
  treap_area_.setBackgroundColor(sf::Color::Transparent);
  avl_area_ = kat::ScrollArea(0, 0, 1200, 750, window_);
  avl_area_.setBackgroundColor(sf::Color::Transparent);
}

void App::render() {
  need_interface_update_ = true;
  while (window_->isOpen()) {
    sf::Event event{};
    while (window_->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_->close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          leftMousePressed(event);
          need_interface_update_ = true;
        }
      }

      if (event.type == sf::Event::MouseMoved) {
        if (buttons_palette_.needRender()) {
          buttons_palette_.setNeedRender(buttons_palette_.isHovered((float)event.mouseMove.x,
                                                                    (float)event.mouseMove.y) ||
                                                                    (float)event.mouseMove.x <= 330);
        } else {
          buttons_palette_.setNeedRender(buttons_palette_.isHoverHorizontalPart(0.3, (float)event.mouseMove.x,
                                                                                  (float)event.mouseMove.y) ||
                                                                                  (float)event.mouseMove.x <= 5);
        }
        need_interface_update_ = true;
      }

      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Left:
            moveCursorLeft();
            break;
          case sf::Keyboard::Right:
            moveCursorRight();
            break;
          case sf::Keyboard::Enter:
            enterPressed();
            break;
          case sf::Keyboard::BackSpace:
            deleteCharacter();
            break;
          case sf::Keyboard::RShift | sf::Keyboard::LShift:
            shift_key_ = true;
            break;
          default:
            addCharacter(event);
        }
        need_interface_update_ = true;
      }

      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::RShift ||
            event.key.code == sf::Keyboard::LShift) {
          shift_key_ = false;
        }
      }

      if (event.type == sf::Event::MouseWheelMoved) {

      }
    }

    if (need_interface_update_) {
      window_->clear(sf::Color::White);

      buttons_palette_.render();
      if (buttons_palette_.needRender()) {
        vertex_input_.render();
        add_vertex_btn_.render();
      }

      if (redraw_trees_) {
        if (treap_btn_.isSelected()) {
          treap_area_.clear();
          treap_edges_.resize(0);
          drawTreap(treap_.getRoot());
          for (auto& i : treap_edges_) {
            i.render();
          }
          treap_area_.render();
        } else if (avl_btn_.isSelected()) {
          avl_area_.clear();
          avl_edges_.resize(0);
          drawAVL(avl_tree_.getRoot());
          for (auto& i : avl_edges_) {
            i.render();
          }
          avl_area_.render();
        } else if (rb_btn_.isSelected()) {
          drawRB(rb_tree_.getRoot());
        } else if (splay_btn_.isSelected()) {
          drawSplay();
        }
      }

      avl_btn_.render();
      treap_btn_.render();
      rb_btn_.render();
      splay_btn_.render();

      window_->display();
    }
    need_interface_update_ = false;
  }
}

void App::moveCursorRight() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      vertex_input_.moveCursorRight();
    }
  }
}

void App::moveCursorLeft() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      vertex_input_.moveCursorLeft();
    }
  }
}

void App::enterPressed() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      addVertex();
    }
  }
}

void App::deleteCharacter() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      vertex_input_.delCharacter();
    }
  }
}

void App::addCharacter(sf::Event &e) {
  char c = getCharFromEvent(e, shift_key_);
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected() && '0' <= c && c <= '9') {
      vertex_input_.addCharacter(c);
    }
  }
}

void App::addVertex() {
  int64_t key = std::stoi(vertex_input_.getData());
  if (treap_btn_.isSelected()) {
    treap_.insert(key);
    need_interface_update_ = true;
    redraw_trees_ = true;
  } else if (avl_btn_.isSelected()) {
    avl_tree_.insert(key);
    redraw_trees_ = true;
    need_interface_update_ = true;
  } else if (rb_btn_.isSelected()) {
    rb_tree_.insert(key);
    redraw_trees_ = true;
    need_interface_update_ = true;
  } else {
    redraw_trees_ = true;
    need_interface_update_ = true;
  }
}

void App::leftMousePressed(sf::Event& e) {
  if (buttons_palette_.needRender()) {
    if (add_vertex_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
      addVertex();
      vertex_input_.clear();
      return;
    }
    vertex_input_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y);
  }
  if (!avl_btn_.isSelected() && avl_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
    treap_btn_.setIsSelected(false);
    rb_btn_.setIsSelected(false);
    splay_btn_.setIsSelected(false);
    return;
  }
  if (!treap_btn_.isSelected() && treap_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
    avl_btn_.setIsSelected(false);
    rb_btn_.setIsSelected(false);
    splay_btn_.setIsSelected(false);
    return;
  }
  if (!rb_btn_.isSelected() && rb_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
    avl_btn_.setIsSelected(false);
    treap_btn_.setIsSelected(false);
    splay_btn_.setIsSelected(false);
    return;
  }
  if (!splay_btn_.isSelected() && splay_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
    avl_btn_.setIsSelected(false);
    treap_btn_.setIsSelected(false);
    rb_btn_.setIsSelected(false);
    return;
  }
}

void App::drawTreap(TreapNode* t, float x, float y) {
  if (t == nullptr) return;
  kat::Button node(x - node_radius_, y - node_radius_, 2*node_radius_, 2*node_radius_,
                   std::to_string(t->getKey()), regular_font_, window_);
  node.setBorderBold(2);
  node.setFontSize(18);
  node.setBorderRadius(node_radius_);
  node.setBorderColor(main_violet_);
  treap_area_.addElm(node);
  if (t->getLeft() != nullptr) {
    int64_t cnt = 1ll << TreapNode::getHeight(t->getLeft());
    int64_t len = node_radius_*cnt + (cnt - 1)*5;
    treap_edges_.emplace_back(x, y,  x - len/2.0, y + 2*node_radius_ + 20, window_);
    drawTreap(t->getLeft(), x - len/2.0, y + 2*node_radius_ + 20);
  }
  if (t->getRight() != nullptr) {
    int64_t cnt = 1ll << TreapNode::getHeight(t->getRight());
    int64_t len = node_radius_*cnt + (cnt - 1)*5;
    treap_edges_.emplace_back(x, y,  x + len/2.0, y + 2*node_radius_ + 20, window_);
    drawTreap(t->getRight(), x + len/2.0, y + 2*node_radius_ + 20);
  }
}

void App::drawAVL(AVLNode* t, float x, float y) {
  if (t == nullptr) return;
  kat::Button node(x - node_radius_, y - node_radius_, 2*node_radius_, 2*node_radius_,
                   std::to_string(t->getKey()), regular_font_, window_);
  node.setBorderBold(2);
  node.setFontSize(18);
  node.setBorderRadius(node_radius_);
  node.setBorderColor(main_violet_);
  avl_area_.addElm(node);
  if (t->getLeft() != nullptr) {
    int64_t cnt = 1ll << AVLNode::getHeight(t->getLeft());
    int64_t len = node_radius_*cnt + (cnt - 1)*5;
    avl_edges_.emplace_back(x, y,  x - len/2.0, y + 2*node_radius_ + 20, window_);
    drawAVL(t->getLeft(), x - len/2.0, y + 2*node_radius_ + 20);
  }
  if (t->getRight() != nullptr) {
    int64_t cnt = 1ll << AVLNode::getHeight(t->getRight());
    int64_t len = node_radius_*cnt + (cnt - 1)*5;
    avl_edges_.emplace_back(x, y,  x + len/2.0, y + 2*node_radius_ + 20, window_);
    drawAVL(t->getRight(), x + len/2.0, y + 2*node_radius_ + 20);
  }
}

void App::drawRB(RBNode* t) {

}

void App::drawSplay() {

}
