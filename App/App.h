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
  AVL avl_tree_;
  RB rb_tree_;
  Treap treap_;

  bool shift_key_;
  sf::Color main_violet_;
  sf::Font regular_font_;

  sf::RenderWindow* window_;
  kat::Div buttons_palette_;

  kat::TextInput vertex_input_;

  kat::ErrorMessage error_message_win_;

  void moveCursorLeft();
  void moveCursorRight();
  void enterPressed();
  void deleteCharacter();
  void addCharacter(sf::Event& e);
  void leftMousePressed(sf::Event& e);

  void addVertex();
};

App::App() {
  shift_key_ = false;

  window_ = new sf::RenderWindow(sf::VideoMode(900, 700), "My little forest");
  main_violet_ = sf::Color(235, 215, 245);
  regular_font_.loadFromFile("../App/fonts/KodeMono.ttf");

  buttons_palette_ = kat::Div(10, 10, 190, 680, window_);
  buttons_palette_.setBackgroundColor(main_violet_);
  buttons_palette_.setBorderRadius(15);
  buttons_palette_.setNeedRender(false);

  vertex_input_ = kat::TextInput(25, 25, 160, 40, regular_font_, window_);
  vertex_input_.setFontSize(20);
  vertex_input_.setBorderRadius(10);

  error_message_win_ = kat::ErrorMessage(300, 250, 200, 100, "", regular_font_, window_);
  error_message_win_.switchNeedRender();
}

void App::render() {
  bool need_interface_update_ = true;
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
        buttons_palette_.setNeedRender(buttons_palette_.isHovered((float)event.mouseMove.x,
                                                                  (float)event.mouseMove.y));
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
      error_message_win_.render();
      if (buttons_palette_.needRender()) {
        vertex_input_.render();
      }

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
  if (!isNumber(vertex_input_.getData())) {
    error_message_win_.setData("incorrect number");
    error_message_win_.setNeedRender(true);
    return;
  }
}

void App::leftMousePressed(sf::Event& e) {
  if (buttons_palette_.needRender()) {
    vertex_input_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y);
  }
}
