//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "RebuildTree.h"


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

  std::pair<int, int> start_avl_pos_, start_treap_pos_, start_rb_pos_, start_splay_pos_;

  bool shift_key_;
  sf::Color main_violet_;
  sf::Font regular_font_;

  sf::RenderWindow* window_;
  kat::Div buttons_palette_;

  kat::Button clear_tree_;

  kat::TextInput vertex_input_;
  kat::Button add_vertex_btn_;

  kat::TextInput number_vertex_input_;
  kat::Button number_vertex_btn_;

  kat::SelectedItem avl_btn_, rb_btn_, treap_btn_, splay_btn_;
  std::vector<TreeNode*> treap_nodes_, avl_nodes_, rb_nodes_, splay_nodes_;

  void moveCursorLeft();
  void moveCursorRight();
  void enterPressed();
  void deleteCharacter();
  void addCharacter(sf::Event& e);
  void leftMousePressed(sf::Event& e);

  void addVertex();
  void addNVertices();
  void deleteVertex(int64_t key);

  void moveTree(float d);
  void renderAVL();
  void renderTreap();
  void renderRBTree();
  void renderSplay();
};


App::App() {
  shift_key_ = false;

  start_avl_pos_ = start_rb_pos_ = start_splay_pos_ = start_treap_pos_ = {600, 175};

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

  number_vertex_input_ = kat::TextInput(15, 185, 170, 40, regular_font_, window_);
  number_vertex_input_.setFontSize(20);
  number_vertex_input_.setBorderRadius(10);

  number_vertex_btn_ = kat::Button(15, 240, 170, 40, "n vertices", regular_font_, window_);
  number_vertex_btn_.setFontSize(20);
  number_vertex_btn_.setBorderRadius(10);

  clear_tree_ = kat::Button(15, 315, 170, 40, "clear", regular_font_, window_);
  clear_tree_.setFontSize(20);
  clear_tree_.setBorderRadius(10);

  avl_btn_ = kat::SelectedItem(700, 0, 120, 25, "AVL", regular_font_, window_);
  avl_btn_.setSelectedColor(main_violet_);
  avl_btn_.setFontSize(18);
  avl_btn_.setBorderRadius(5);
  avl_btn_.setBorderBold(2);
  avl_btn_.setBorderColor(main_violet_);
  avl_btn_.setIsSelected(true);

  treap_btn_ = kat::SelectedItem(825, 0, 120, 25, "Treap", regular_font_, window_);
  treap_btn_.setSelectedColor(main_violet_);
  treap_btn_.setFontSize(18);
  treap_btn_.setBorderRadius(5);
  treap_btn_.setBorderBold(2);
  treap_btn_.setBorderColor(main_violet_);

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
}

void App::render() {
  while (window_->isOpen()) {
    sf::Event event{};
    while (window_->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_->close();
      }

      if (event.type == sf::Event::MouseWheelScrolled) {
        if ((!buttons_palette_.needRender() ||
            !buttons_palette_.isHovered(event.mouseWheelScroll.x, event.mouseWheelScroll.y)) &&
            event.mouseWheelScroll.delta != 0) {

          if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
            moveTree(10*sign(event.mouseWheelScroll.delta));
          } else {
            moveTree(10*sign(event.mouseWheelScroll.delta));
          }
        }
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          leftMousePressed(event);
        }
      }

      if (event.type == sf::Event::MouseMoved) {
        if (buttons_palette_.needRender()) {
          buttons_palette_.setNeedRender(buttons_palette_.isHovered((float)event.mouseMove.x,
                                                                    (float)event.mouseMove.y) ||
                                                                    (float)event.mouseMove.x <= 330);
        } else {
          buttons_palette_.setNeedRender(buttons_palette_.isHoverHorizontalPart(0.1, (float)event.mouseMove.x,
                                                                                  (float)event.mouseMove.y) ||
                                                                                  (float)event.mouseMove.x <= 5);
        }
        if (!buttons_palette_.needRender()) {
          vertex_input_.setSelected(false);
          number_vertex_input_.setSelected(false);
        }
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
          case sf::Keyboard::Equal:
            scale_ *= 1.1;
            break;
          case sf::Keyboard::Hyphen:
            if (vertex_input_.isSelected()) {
              addCharacter(event);
            } else {
              scale_ /= 1.1;
            }
            break;
          default:
            addCharacter(event);
        }
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

    window_->clear(sf::Color::White);

    if (avl_btn_.isSelected()) {
      renderAVL();
    } else if (treap_btn_.isSelected()) {
      renderTreap();
    } else if (rb_btn_.isSelected()) {
      renderRBTree();
    } else {
      renderSplay();
    }

    buttons_palette_.render();
    if (buttons_palette_.needRender()) {
      vertex_input_.render();
      add_vertex_btn_.render();
      number_vertex_input_.render();
      number_vertex_btn_.render();
      clear_tree_.render();
    }

    avl_btn_.render();
    treap_btn_.render();
    rb_btn_.render();
    splay_btn_.render();

    window_->display();
  }
}

void App::moveCursorRight() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      vertex_input_.moveCursorRight();
    }
    if (number_vertex_input_.isSelected()) {
      number_vertex_input_.moveCursorRight();
    }
  }
}

void App::moveCursorLeft() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      vertex_input_.moveCursorLeft();
    }
    if (number_vertex_input_.isSelected()) {
      number_vertex_input_.moveCursorLeft();
    }
  }
}

void App::enterPressed() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      addVertex();
    }
    if (number_vertex_input_.isSelected()) {
      addNVertices();
    }
  }
}

void App::deleteCharacter() {
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected()) {
      vertex_input_.delCharacter();
    }
    if (number_vertex_input_.isSelected()) {
      number_vertex_input_.delCharacter();
    }
  }
}

void App::addCharacter(sf::Event &e) {
  char c = getCharFromEvent(e, shift_key_);
  if (buttons_palette_.needRender()) {
    if (vertex_input_.isSelected() && (('0' <= c && c <= '9') || c == '-')) {
      vertex_input_.addCharacter(c);
    }
    if (number_vertex_input_.isSelected() && (('0' <= c && c <= '9') || c == '-')) {
      number_vertex_input_.addCharacter(c);
    }
  }
}

void App::addVertex() {
  int64_t key = toInt(vertex_input_.getData());
  if (treap_btn_.isSelected()) {
    treap_.insert(key);
  } else if (avl_btn_.isSelected()) {
    avl_tree_.insert(key);
    RebuildTree::rebuildAVL(avl_tree_, avl_nodes_, 2*node_radius_, window_);
  } else if (rb_btn_.isSelected()) {
//    rb_tree_.insert(key);
  } else {
  }
  vertex_input_.clear();
}

void App::leftMousePressed(sf::Event& e) {
  if (buttons_palette_.needRender()) {
    if (add_vertex_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
      addVertex();
      return;
    }
    if (number_vertex_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
      addNVertices();
      number_vertex_input_.clear();
      return;
    }
    if (clear_tree_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
      if (avl_btn_.isSelected()) {
        avl_tree_.clear();
        RebuildTree::rebuildAVL(avl_tree_, avl_nodes_, 2*node_radius_, window_);
      } else if (treap_btn_.isSelected()) {
        treap_.clear();
      } else if (rb_btn_.isSelected()) {

      } else {

      }
    }
    vertex_input_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y);
    number_vertex_input_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y);
    return;
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

void App::deleteVertex(int64_t key) {
  if (avl_btn_.isSelected()) {
    avl_tree_.erase(key);
  } else if (rb_btn_.isSelected()) {

  } else if (treap_btn_.isSelected()) {
    treap_.erase(key);
  } else {

  }
}

void App::addNVertices() {
  int64_t n = toInt(number_vertex_input_.getData());
  if (n > 10000) {
    std::cout << "вперед, в пешее эротическое";
    return;
  }
  if (avl_btn_.isSelected()) {
    avl_tree_.insertNRandom(n);
    RebuildTree::rebuildAVL(avl_tree_, avl_nodes_, node_radius_*2, window_);
  } else if (treap_btn_.isSelected()) {
    treap_.insertNRandom(n);
  } else if (rb_btn_.isSelected()) {

  } else {

  }
}

void App::moveTree(float d) {

}

void App::renderAVL() {
  for (auto & avl_node : avl_nodes_) {
    if (avl_node->getKey() == -1e18) continue;
    avl_node->render();
    if (avl_node->getLeftChild() != nullptr && avl_node->getLeftChild()->getKey() != -1e18) {

    }
    if (avl_node->getRightChild() != nullptr && avl_node->getRightChild()->getKey() != -1e18) {

    }
  }
}

void App::renderTreap() {

}

void App::renderRBTree() {

}

void App::renderSplay() {

}
