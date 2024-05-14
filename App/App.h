//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "RebuildTree.h"
#include "MusicManager.h"


class App {
 public:
  App();

  void render();

 private:
  Treap treap_;
  AVL avl_tree_;
  RB rb_tree_;
  Splay splay_tree_;
  MusicManager music_manager_;

  float avl_scale_ = 1, treap_scale_ = 1, rb_scale_ = 1, splay_scale_ = 1;
  float node_radius_ = 30;

  std::pair<int, int> start_avl_pos_, start_treap_pos_, start_rb_pos_, start_splay_pos_;

  bool shift_key_, play_music_ = false, record_set_ = false;
  sf::Color main_violet_;
  sf::Font regular_font_;

  sf::RenderWindow* window_;
  kat::Div buttons_palette_;

  kat::Button clear_tree_, play_pause_btn_;

  kat::Label name_lbl_, author_lbl_;

  sf::SoundBuffer music_buffer_;
  sf::Texture cover_texture_, play_texture_, pause_texture_,
              vinyl_record_texture_, no_vinyl_record_texture_;
  sf::Sprite play_sprite_, pause_sprite_, cover_sprite_,
            vinyl_record_sprite_, no_vinyl_record_sprite_;
  sf::Sound music_sound_;

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

  void moveTreeX(float d);
  void moveTreeY(float d);
  void zoom(float d);

  void renderAVL();
  void renderTreap();
  void renderRBTree();
  void renderSplay();

  void replaceMusic(const std::vector<TreeNode*>& nodes, int64_t key);
  static void setOriginAndReadjust(sf::Transformable &object, const sf::Vector2f &newOrigin) {
    auto offset = newOrigin - object.getOrigin();
    object.setOrigin(newOrigin);
    object.move(offset);
  }

  void returnScale();
};


App::App() {
  shift_key_ = false;

  start_avl_pos_ = start_rb_pos_ = start_splay_pos_ = start_treap_pos_ = {600, 175};

  window_ = new sf::RenderWindow(sf::VideoMode(1200, 750), "My little forest");
  main_violet_ = sf::Color(235, 215, 245);
  regular_font_.loadFromFile("../assets/fonts/KodeMono.ttf");

  buttons_palette_ = kat::Div(5, 5, 235, 740, window_);
  buttons_palette_.setBackgroundColor(main_violet_);
  buttons_palette_.setBorderRadius(10);
  buttons_palette_.setNeedRender(false);

  name_lbl_ = kat::Label(5, 450, 215, 20, "", regular_font_, window_);
  name_lbl_.setFontSize(17);
  name_lbl_.setBackgroundColor(sf::Color::Transparent);

  author_lbl_ = kat::Label(8, 475, 215, 20, "", regular_font_, window_);
  author_lbl_.setFontSize(15);
  author_lbl_.setBackgroundColor(sf::Color::Transparent);

  vinyl_record_texture_.loadFromFile("../assets/vinyl-record.png");
  vinyl_record_sprite_.setTexture(vinyl_record_texture_);
  vinyl_record_sprite_.move({10, 510});

  no_vinyl_record_texture_.loadFromFile("../assets/no-vinyl-record.png");
  no_vinyl_record_sprite_.setTexture(no_vinyl_record_texture_);
  no_vinyl_record_sprite_.move({10, 510});

  play_pause_btn_ = kat::Button(20, 520, 25, 25, "", regular_font_, window_);
  play_pause_btn_.setBackgroundColor(sf::Color::Transparent);

  play_texture_.loadFromFile("../assets/play-button.png");
  play_sprite_.setTexture(play_texture_);
  play_sprite_.move({20, 520});

  pause_texture_.loadFromFile("../assets/pause-button.png");
  pause_sprite_.setTexture(pause_texture_);
  pause_sprite_.move({20, 520});

  cover_sprite_.move({88, 588});

  vertex_input_ = kat::TextInput(15, 55, 210, 40, regular_font_, window_);
  vertex_input_.setFontSize(20);
  vertex_input_.setBorderRadius(10);

  add_vertex_btn_ = kat::Button(15, 110, 210, 40, "add vertex", regular_font_, window_);
  add_vertex_btn_.setFontSize(20);
  add_vertex_btn_.setBorderRadius(10);

  number_vertex_input_ = kat::TextInput(15, 185, 210, 40, regular_font_, window_);
  number_vertex_input_.setFontSize(20);
  number_vertex_input_.setBorderRadius(10);

  number_vertex_btn_ = kat::Button(15, 240, 210, 40, "n vertices", regular_font_, window_);
  number_vertex_btn_.setFontSize(20);
  number_vertex_btn_.setBorderRadius(10);

  clear_tree_ = kat::Button(15, 315, 210, 40, "clear", regular_font_, window_);
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
  int iteration = 0;
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
            moveTreeX(10*sign(event.mouseWheelScroll.delta));
          } else {
            moveTreeY(10*sign(event.mouseWheelScroll.delta));
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
            zoom(1.1);
            break;
          case sf::Keyboard::Hyphen:
            if (vertex_input_.isSelected()) {
              addCharacter(event);
            } else {
              zoom(1/1.1);
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
      name_lbl_.render();
      author_lbl_.render();

      if (record_set_) {
        window_->draw(vinyl_record_sprite_);
      } else {
        window_->draw(no_vinyl_record_sprite_);
      }
      window_->draw(cover_sprite_);
      if (!play_music_) {
        window_->draw(play_sprite_);
      } else {
        window_->draw(pause_sprite_);
        if (iteration == 0) {
          cover_sprite_.rotate(1);
          setOriginAndReadjust(cover_sprite_,
                               {(float)cover_texture_.getSize().x/2, (float)cover_texture_.getSize().y/2});
        }
      }
    }

    avl_btn_.render();
    treap_btn_.render();
    rb_btn_.render();
    splay_btn_.render();

    window_->display();

    ++iteration;
    iteration %= 200;
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
  if (key >= 100000) return;
  if (treap_btn_.isSelected()) {
    treap_.insert(key);
    RebuildTree::rebuildTreap(treap_, treap_nodes_, 2*node_radius_,
                             regular_font_, start_treap_pos_, window_);
    music_manager_.setAudio(treap_nodes_);
  } else if (avl_btn_.isSelected()) {
    avl_tree_.insert(key);
    RebuildTree::rebuildAVL(avl_tree_, avl_nodes_, 2*node_radius_,
                            regular_font_, start_avl_pos_, window_);
    music_manager_.setAudio(avl_nodes_);
  } else if (rb_btn_.isSelected()) {
    rb_tree_.insert(key);
    RebuildTree::rebuildRB(rb_tree_, rb_nodes_, 2*node_radius_,
                            regular_font_, start_rb_pos_, window_);
    music_manager_.setAudio(rb_nodes_);
  } else {
    splay_tree_.insert(key);
    RebuildTree::rebuildSplay(splay_tree_, splay_nodes_, 2*node_radius_,
                              regular_font_, start_splay_pos_, window_);
    music_manager_.setAudio(splay_nodes_);
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
        RebuildTree::rebuildAVL(avl_tree_, avl_nodes_, 2*node_radius_,
                                regular_font_, start_avl_pos_, window_);
        music_manager_.setAudio(avl_nodes_);
      } else if (treap_btn_.isSelected()) {
        treap_.clear();
        RebuildTree::rebuildTreap(treap_, treap_nodes_, 2*node_radius_,
                                  regular_font_, start_treap_pos_, window_);
        music_manager_.setAudio(treap_nodes_);
      } else if (rb_btn_.isSelected()) {
        rb_tree_.clear();
        RebuildTree::rebuildRB(rb_tree_, rb_nodes_, 2*node_radius_,
                               regular_font_, start_rb_pos_, window_);
        music_manager_.setAudio(avl_nodes_);
      } else {
        splay_tree_.clear();
        RebuildTree::rebuildSplay(splay_tree_, splay_nodes_, 2*node_radius_,
                                  regular_font_, start_splay_pos_, window_);
        music_manager_.setAudio(splay_nodes_);
      }
    }
    if (record_set_ && play_pause_btn_.isPressed((float)e.mouseButton.x, (float)e.mouseButton.y)) {
      if (play_music_) {
        music_sound_.pause();
      } else {
        music_sound_.play();
      }
      play_music_ = !play_music_;
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

  if (avl_btn_.isSelected()) {
    for (auto& i : avl_nodes_) {
      if (i->isHovered((float)e.mouseButton.x, (float)e.mouseButton.y) && i->getKey() != -1e18) {
        deleteVertex(i->getKey());
      }
    }
  } else if (rb_btn_.isSelected()) {
    for (auto& i : rb_nodes_) {
      if (i->isHovered((float)e.mouseButton.x, (float)e.mouseButton.y) && i->getKey() != -1e18) {
        deleteVertex(i->getKey());
      }
    }
  } else if (treap_btn_.isSelected()) {
    for (auto& i : treap_nodes_) {
      if (i->isHovered((float)e.mouseButton.x, (float)e.mouseButton.y) && i->getKey() != -1e18) {
        deleteVertex(i->getKey());
      }
    }
  } else {
    for (auto& i : splay_nodes_) {
      if (i->isHovered((float)e.mouseButton.x, (float)e.mouseButton.y) && i->getKey() != -1e18) {
        deleteVertex(i->getKey());
      }
    }
  }
}

void App::deleteVertex(int64_t key) {
  if (avl_btn_.isSelected()) {
    avl_tree_.erase(key);
    replaceMusic(avl_nodes_, key);
    RebuildTree::rebuildAVL(avl_tree_, avl_nodes_, 2*node_radius_,
                            regular_font_, start_avl_pos_, window_);
    music_manager_.setAudio(avl_nodes_);
  } else if (rb_btn_.isSelected()) {
    rb_tree_.erase(key);
    replaceMusic(rb_nodes_, key);
    RebuildTree::rebuildRB(rb_tree_, rb_nodes_, 2*node_radius_,
                           regular_font_, start_rb_pos_, window_);
    music_manager_.setAudio(avl_nodes_);
  } else if (treap_btn_.isSelected()) {
    treap_.erase(key);
    replaceMusic(treap_nodes_, key);
    RebuildTree::rebuildTreap(treap_, treap_nodes_, 2*node_radius_,
                              regular_font_, start_treap_pos_, window_);
    music_manager_.setAudio(treap_nodes_);
  } else {
    splay_tree_.erase(key);
    replaceMusic(splay_nodes_, key);
    RebuildTree::rebuildSplay(splay_tree_, splay_nodes_, 2*node_radius_,
                              regular_font_, start_splay_pos_, window_);
    music_manager_.setAudio(splay_nodes_);
  }
  record_set_ = true;
}

void App::addNVertices() {
  int64_t n = toInt(number_vertex_input_.getData());
  if (n > 10000) {
    std::cout << "go away, fucking idiot";
    return;
  }
  if (avl_btn_.isSelected()) {
    avl_tree_.insertNRandom(n);
    RebuildTree::rebuildAVL(avl_tree_, avl_nodes_, 2*node_radius_,
                            regular_font_, start_avl_pos_, window_);
    music_manager_.setAudio(avl_nodes_);
  } else if (treap_btn_.isSelected()) {
    treap_.insertNRandom(n);
    RebuildTree::rebuildTreap(treap_, treap_nodes_, 2*node_radius_,
                              regular_font_, start_treap_pos_, window_);
    music_manager_.setAudio(treap_nodes_);
  } else if (rb_btn_.isSelected()) {
    rb_tree_.insertNRandom(n);
    RebuildTree::rebuildRB(rb_tree_, rb_nodes_, 2*node_radius_,
                           regular_font_, start_rb_pos_, window_);
    music_manager_.setAudio(avl_nodes_);
  } else {
    splay_tree_.insertNRandom(n);
    RebuildTree::rebuildSplay(splay_tree_, splay_nodes_, 2*node_radius_,
                              regular_font_, start_splay_pos_, window_);
    music_manager_.setAudio(splay_nodes_);
  }

  number_vertex_input_.clear();
}

void App::moveTreeX(float d) {
  if (avl_btn_.isSelected()) {
    start_avl_pos_.first += d;
    for (auto& avl_node : avl_nodes_) {
      avl_node->moveX(d);
    }
  } else if (treap_btn_.isSelected()) {
    start_treap_pos_.first += d;
    for (auto& treap_node : treap_nodes_) {
      treap_node->moveX(d);
    }
  } else if (rb_btn_.isSelected()) {
    start_rb_pos_.first += d;
    for (auto& rb_node : rb_nodes_) {
      rb_node->moveX(d);
    }
  } else {
    start_splay_pos_.first += d;
    for (auto& splay_node : splay_nodes_) {
      splay_node->moveX(d);
    }
  }
}

void App::moveTreeY(float d) {
  if (avl_btn_.isSelected()) {
    start_avl_pos_.second += d;
    for (auto& avl_node : avl_nodes_) {
      avl_node->moveY(d);
    }
  } else if (treap_btn_.isSelected()) {
    start_treap_pos_.second += d;
    for (auto& treap_node : treap_nodes_) {
      treap_node->moveY(d);
    }
  } else if (rb_btn_.isSelected()) {
    start_rb_pos_.second += d;
    for (auto& rb_node : rb_nodes_) {
      rb_node->moveY(d);
    }
  } else {
    start_splay_pos_.second += d;
    for (auto& splay_node : splay_nodes_) {
      splay_node->moveY(d);
    }
  }
}

void App::renderAVL() {
  kat::Line edge;
  for (auto & avl_node : avl_nodes_) {
    if (avl_node->getKey() == -1e18) continue;
    if (avl_node->getLeftChild() != nullptr && avl_node->getLeftChild()->getKey() != -1e18) {
      edge = {avl_node->getX() + node_radius_*avl_scale_, avl_node->getY() + node_radius_*avl_scale_,
              avl_node->getLeftChild()->getX() + node_radius_*avl_scale_,
              avl_node->getLeftChild()->getY() + node_radius_*avl_scale_,
              window_};
      edge.render();
    }
    if (avl_node->getRightChild() != nullptr && avl_node->getRightChild()->getKey() != -1e18) {
      edge = {avl_node->getX() + node_radius_*avl_scale_, avl_node->getY() + node_radius_*avl_scale_,
              avl_node->getRightChild()->getX() + node_radius_*avl_scale_,
              avl_node->getRightChild()->getY() + node_radius_*avl_scale_,
              window_};
      edge.render();
    }
  }
  for (auto& avl_node : avl_nodes_) {
    if (avl_node->getKey() == -1e18) continue;
    avl_node->render();
  }
}

void App::renderTreap() {
  kat::Line edge;
  for (auto & treap_node : treap_nodes_) {
    if (treap_node->getKey() == -1e18) continue;
    if (treap_node->getLeftChild() != nullptr && treap_node->getLeftChild()->getKey() != -1e18) {
      edge = {treap_node->getX() + node_radius_*treap_scale_, treap_node->getY() + node_radius_*treap_scale_,
              treap_node->getLeftChild()->getX() + node_radius_*treap_scale_,
              treap_node->getLeftChild()->getY() + node_radius_*treap_scale_,
              window_};
      edge.render();
    }
    if (treap_node->getRightChild() != nullptr && treap_node->getRightChild()->getKey() != -1e18) {
      edge = {treap_node->getX() + node_radius_*treap_scale_, treap_node->getY() + node_radius_*treap_scale_,
              treap_node->getRightChild()->getX() + node_radius_*treap_scale_,
              treap_node->getRightChild()->getY() + node_radius_*treap_scale_,
              window_};
      edge.render();
    }
  }
  for (auto & treap_node : treap_nodes_) {
    if (treap_node->getKey() == -1e18) continue;
    treap_node->render();
  }
}

void App::renderRBTree() {
  kat::Line edge;
  for (auto & rb_node : rb_nodes_) {
    if (rb_node->getKey() == -1e18) continue;
    if (rb_node->getLeftChild() != nullptr && rb_node->getLeftChild()->getKey() != -1e18) {
      edge = {rb_node->getX() + node_radius_*rb_scale_, rb_node->getY() + node_radius_*rb_scale_,
              rb_node->getLeftChild()->getX() + node_radius_*rb_scale_,
              rb_node->getLeftChild()->getY() + node_radius_*rb_scale_,
              window_};
      edge.render();
    }
    if (rb_node->getRightChild() != nullptr && rb_node->getRightChild()->getKey() != -1e18) {
      edge = {rb_node->getX() + node_radius_*rb_scale_, rb_node->getY() + node_radius_*rb_scale_,
              rb_node->getRightChild()->getX() + node_radius_*rb_scale_,
              rb_node->getRightChild()->getY() + node_radius_*rb_scale_,
              window_};
      edge.render();
    }
  }
  for (auto & rb_node : rb_nodes_) {
    if (rb_node->getKey() == -1e18) continue;
    rb_node->render();
  }
}

void App::renderSplay() {
  kat::Line edge;
  for (auto & splay_node : splay_nodes_) {
    if (splay_node->getKey() == -1e18) continue;
    if (splay_node->getLeftChild() != nullptr && splay_node->getLeftChild()->getKey() != -1e18) {
      edge = {splay_node->getX() + node_radius_*splay_scale_, splay_node->getY() + node_radius_*splay_scale_,
              splay_node->getLeftChild()->getX() + node_radius_*splay_scale_,
              splay_node->getLeftChild()->getY() + node_radius_*splay_scale_,
              window_};
      edge.render();
    }
    if (splay_node->getRightChild() != nullptr && splay_node->getRightChild()->getKey() != -1e18) {
      edge = {splay_node->getX() + node_radius_*splay_scale_, splay_node->getY() + node_radius_*splay_scale_,
              splay_node->getRightChild()->getX() + node_radius_*splay_scale_,
              splay_node->getRightChild()->getY() + node_radius_*splay_scale_,
              window_};
      edge.render();
    }
  }
  for (auto & splay_node : splay_nodes_) {
    if (splay_node->getKey() == -1e18) continue;
    splay_node->render();
  }
}

void App::zoom(float d) {
  if (avl_btn_.isSelected()) {
    avl_scale_ *= d;
    for (auto& avl_node : avl_nodes_) {
      avl_node->setX(avl_node->getX()*d);
      avl_node->setY(avl_node->getY()*d);
      avl_node->setWidth(avl_node->getWidth()*d);
      avl_node->setHeight(avl_node->getHeight()*d);
      avl_node->setBorderRadius(avl_node->getBorderRadius()*d);
      avl_node->setBorderBold(avl_node->getBorderBold()*d);
      if (d < 1) {
        avl_node->setFontSize(avl_node->getFontSize()*d);
      } else {
        avl_node->setFontSize(ceil(avl_node->getFontSize()*d));
      }
    }
  } else if (treap_btn_.isSelected()) {
    treap_scale_ *= d;
    for (auto& treap_node : treap_nodes_) {
      treap_node->setX(treap_node->getX() * d);
      treap_node->setY(treap_node->getY() * d);
      treap_node->setWidth(treap_node->getWidth() * d);
      treap_node->setHeight(treap_node->getHeight() * d);
      treap_node->setBorderRadius(treap_node->getBorderRadius() * d);
      treap_node->setBorderBold(treap_node->getBorderBold() * d);
      if (d < 1) {
        treap_node->setFontSize(treap_node->getFontSize() * d);
      } else {
        treap_node->setFontSize(ceil(treap_node->getFontSize() * d));
      }
    }
  } else if (rb_btn_.isSelected()) {
    rb_scale_ *= d;
    for (auto& rb_node : rb_nodes_) {
      rb_node->setX(rb_node->getX() * d);
      rb_node->setY(rb_node->getY() * d);
      rb_node->setWidth(rb_node->getWidth() * d);
      rb_node->setHeight(rb_node->getHeight() * d);
      rb_node->setBorderRadius(rb_node->getBorderRadius() * d);
      rb_node->setBorderBold(rb_node->getBorderBold() * d);
      if (d < 1) {
        rb_node->setFontSize(rb_node->getFontSize() * d);
      } else {
        rb_node->setFontSize(ceil(rb_node->getFontSize() * d));
      }
    }
  } else {
    splay_scale_ *= d;
    for (auto& splay_node : splay_nodes_) {
      splay_node->setX(splay_node->getX() * d);
      splay_node->setY(splay_node->getY() * d);
      splay_node->setWidth(splay_node->getWidth() * d);
      splay_node->setHeight(splay_node->getHeight() * d);
      splay_node->setBorderRadius(splay_node->getBorderRadius() * d);
      splay_node->setBorderBold(splay_node->getBorderBold() * d);
      if (d < 1) {
        splay_node->setFontSize(splay_node->getFontSize() * d);
      } else {
        splay_node->setFontSize(ceil(splay_node->getFontSize() * d));
      }
    }
  }
}

void App::replaceMusic(const std::vector<TreeNode *> &nodes, int64_t key) {
  for (auto& i : nodes) {
    if (i->getKey() == key) {
      auto paths = music_manager_.getPathsById(i->getAudioId());
      cover_texture_.loadFromFile(paths.first);
      cover_sprite_.setTexture(cover_texture_);
      music_buffer_.loadFromFile(paths.second);
      music_sound_.setBuffer(music_buffer_);
      music_sound_.setLoop(true);
      cover_sprite_.setRotation(0);
      auto info = music_manager_.getInformationById(i->getAudioId());
      name_lbl_.setData(info.first);
      author_lbl_.setData(info.second);
      play_music_ = false;
    }
  }
}

void App::returnScale() {
  if (avl_btn_.isSelected()) {
    for (auto& avl_node : avl_nodes_) {
      avl_node->setX(avl_node->getX()*avl_scale_);
      avl_node->setY(avl_node->getY()*avl_scale_);
      avl_node->setWidth(avl_node->getWidth()*avl_scale_);
      avl_node->setHeight(avl_node->getHeight()*avl_scale_);
      avl_node->setBorderRadius(avl_node->getBorderRadius()*avl_scale_);
      avl_node->setBorderBold(avl_node->getBorderBold()*avl_scale_);
      if (avl_scale_ < 1) {
        avl_node->setFontSize(avl_node->getFontSize()*avl_scale_);
      } else {
        avl_node->setFontSize(ceil(avl_node->getFontSize()*avl_scale_));
      }
    }
  } else if (treap_btn_.isSelected()) {
    for (auto& treap_node : treap_nodes_) {
      treap_node->setX(treap_node->getX() * treap_scale_);
      treap_node->setY(treap_node->getY() * treap_scale_);
      treap_node->setWidth(treap_node->getWidth() * treap_scale_);
      treap_node->setHeight(treap_node->getHeight() * treap_scale_);
      treap_node->setBorderRadius(treap_node->getBorderRadius() * treap_scale_);
      treap_node->setBorderBold(treap_node->getBorderBold() * treap_scale_);
      if (treap_scale_ < 1) {
        treap_node->setFontSize(treap_node->getFontSize() * treap_scale_);
      } else {
        treap_node->setFontSize(ceil(treap_node->getFontSize() * treap_scale_));
      }
    }
  } else if (rb_btn_.isSelected()) {
    for (auto& rb_node : rb_nodes_) {
      rb_node->setX(rb_node->getX() * rb_scale_);
      rb_node->setY(rb_node->getY() * rb_scale_);
      rb_node->setWidth(rb_node->getWidth() * rb_scale_);
      rb_node->setHeight(rb_node->getHeight() * rb_scale_);
      rb_node->setBorderRadius(rb_node->getBorderRadius() * rb_scale_);
      rb_node->setBorderBold(rb_node->getBorderBold() * rb_scale_);
      if (rb_scale_ < 1) {
        rb_node->setFontSize(rb_node->getFontSize() * rb_scale_);
      } else {
        rb_node->setFontSize(ceil(rb_node->getFontSize() * rb_scale_));
      }
    }
  } else {
    for (auto& splay_node : splay_nodes_) {
      splay_node->setX(splay_node->getX() * splay_scale_);
      splay_node->setY(splay_node->getY() * splay_scale_);
      splay_node->setWidth(splay_node->getWidth() * splay_scale_);
      splay_node->setHeight(splay_node->getHeight() * splay_scale_);
      splay_node->setBorderRadius(splay_node->getBorderRadius() * splay_scale_);
      splay_node->setBorderBold(splay_node->getBorderBold() * splay_scale_);
      if (splay_scale_ < 1) {
        splay_node->setFontSize(splay_node->getFontSize() * splay_scale_);
      } else {
        splay_node->setFontSize(ceil(splay_node->getFontSize() * splay_scale_));
      }
    }
  }
}
