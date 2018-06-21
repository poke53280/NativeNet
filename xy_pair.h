#pragma once

#include <array>

typedef std::array<float, 5>  x_array;

struct xy_pair {
  x_array _X;
  float _y;

  xy_pair();
  void fill_random();
  void calc_Y();

  void print() const;

};
