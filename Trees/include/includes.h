//
// Created by Тимур Ахметзянов on 15.04.2024.
//

#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <set>
#include <random>
#include <chrono>


std::mt19937_64 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

int64_t toInt(const std::string& s) {
  int num = 0, mn = 1;
  for (char i : s) {
    if (i == '-') mn = -mn;
    else num = num*10 + i - '0';
  }
  return num * mn;
}
