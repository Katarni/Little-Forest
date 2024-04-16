//
// Created by Тимур Ахметзянов on 28.03.2024.
//

#pragma once

#include "Label.h"

namespace kat {
  class Button : public Label {
   public:
    Button() : Label() {}
    Button(float x, float y,
           float width, float height,
           const std::string &data, const sf::Font &font,
           sf::RenderWindow *parent) : Label(x, y, width, height, data, font, parent) {}

    virtual inline bool isPressed(float x, float y) {
      return Div::isHovered(x, y);
    }

    void render() override;
  };

  void Button::render() {
    auto text_params = getStringParams(getData());
    float text_x = (getWidth() - (float)text_params.first*(float)getFontSize()/1.6f)/ 2 + getX();
    float text_y = getY() +
                   (getHeight() - (float)text_params.second*(float)getFontSize()) / 2 -
                   (float)getFontSize()/5;

    sf::Text text;
    text.setFont(getFont());
    text.setFillColor(getColor());
    text.setCharacterSize(getFontSize());
    text.setString(getData());
    text.setPosition(text_x, text_y);

    sf::RectangleShape hor_rect, ver_rect;
    hor_rect.setPosition(getX(), getY() + getBorderRadius());
    hor_rect.setSize({getWidth(), getHeight() - 2*getBorderRadius()});
    hor_rect.setFillColor(getBackgroundColor());
    ver_rect.setPosition(getX() + getBorderRadius(), getY());
    ver_rect.setSize({getWidth() - 2*getBorderRadius(), getHeight()});
    ver_rect.setFillColor(getBackgroundColor());

    sf::CircleShape top_left_cir, top_right_cir;
    top_left_cir.setRadius(getBorderRadius());
    top_left_cir.setPosition(getX(), getY());
    top_left_cir.setFillColor(getBackgroundColor());
    top_right_cir.setRadius(getBorderRadius());
    top_right_cir.setPosition(getX() + getWidth() - 2*getBorderRadius(), getY());
    top_right_cir.setFillColor(getBackgroundColor());

    sf::CircleShape bottom_left_cir, bottom_right_cir;
    bottom_left_cir.setRadius(getBorderRadius());
    bottom_left_cir.setPosition(getX(), getY() + getHeight() - 2*getBorderRadius());
    bottom_left_cir.setFillColor(getBackgroundColor());
    bottom_right_cir.setRadius(getBorderRadius());
    bottom_right_cir.setPosition(getX() + getWidth() - 2*getBorderRadius(), getY() + getHeight() - 2*getBorderRadius());
    bottom_right_cir.setFillColor(getBackgroundColor());

    getParent()->draw(hor_rect);
    getParent()->draw(ver_rect);
    getParent()->draw(top_left_cir);
    getParent()->draw(top_right_cir);
    getParent()->draw(bottom_right_cir);
    getParent()->draw(bottom_left_cir);
    getParent()->draw(text);
  }
}
