//
// Created by Тимур Ахметзянов on 11.05.2024.
//

#pragma once

#include "TreeNode.h"
#include "includes.h"


class MusicManager {
 public:
  static void setAudio(std::vector<TreeNode*>& nodes) {
    for (auto& i : nodes) {
      if (i->getAudioId() == -1) {
        i->setAudioId(rnd() % 2);
      }
    }
  }

  std::pair<std::string, std::string> getPathsById(int id) {
    return {"../assets/audio/" + paths_[id], "../assets/img/" + paths_[id]};
  }

  std::pair<std::string, std::string> getInformationById(int id) {
    return {names_[id], authors_[id]};
  }

 private:
  std::unordered_map<int, std::string> paths_;
  std::unordered_map<int, std::string> names_;
  std::unordered_map<int, std::string> authors_;
};
