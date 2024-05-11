//
// Created by Тимур Ахметзянов on 11.05.2024.
//

#pragma once

#include "TreeNode.h"


class MusicManager {
 public:
  MusicManager() {
    std::ifstream is("../assets/music_list.txt");
    std::string line;
    while (getline(is, line)) {
      path_.push_back(line);
      auto info = parse(line);
      names_.push_back(info.first);
      authors_.push_back(info.second);
    }
  }

  void setAudio(std::vector<TreeNode*>& nodes) {
    for (auto& i : nodes) {
      if (i->getAudioId() == -1) {
        i->setAudioId(rnd() % names_.size());
      }
    }
  }

  std::pair<std::string, std::string> getPathsById(int id) {
    return {"../assets/covers/" + path_[id] + ".png",
            "../assets/audio/" + path_[id] + ".mp3"};
  }

  std::pair<std::string, std::string> getInformationById(int id) {
    return {names_[id], authors_[id]};
  }

 private:
  std::vector<std::string> names_, authors_, path_;

  static std::pair<std::string, std::string> parse(const std::string& str);
};

std::pair<std::string, std::string> MusicManager::parse(const std::string &str) {
  std::string name, author;
  bool author_flag = false;
  for (char c : str) {
    if (c == '-') {
      author_flag = true;
    } else if ('A' <= c && c <= 'Z') {
      if (author_flag) {
        author.push_back(' ');
        author.push_back(c);
      } else {
        name.push_back(' ');
        name.push_back(c);
      }
    } else {
      if (author_flag) {
        author.push_back(c);
      } else {
        name.push_back(c);
      }
    }
  }
  return {name, author};
}
