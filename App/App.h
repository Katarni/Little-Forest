//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "AVL/AVL.h"
#include "RB/RB.h"
#include "Button.h"
#include "Div.h"
#include "Label.h"


class App {
 public:
  App();

  void render();

 private:
  sf::RenderWindow* window_;
};

App::App() {
  window_ = new sf::RenderWindow(sf::VideoMode(800, 700), "My little forest");
}

void App::render() {
  bool need_upd = true;
  while (window_->isOpen()) {
    sf::Event event;
    while (window_->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_->close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {

      }

      if (event.type == sf::Event::KeyPressed) {

      }

      if (event.type == sf::Event::KeyReleased) {

      }

      if (event.type == sf::Event::MouseWheelMoved) {

      }
    }

    if (need_upd) {
      window_->clear(sf::Color::White);

      window_->display();
    }
    need_upd = false;
  }
}
