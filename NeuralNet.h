#pragma once

#include <array>
#include <vector>
#include "xy_pair.h"

template <std::size_t N> class Neuron {

  std::array<float, N>      _w;
  float                     _b;

  static float sigmoid(float z) {
    float e = exp(-z);
    return 1.f / (1 + e);
  }

public:

  Neuron() {
    _w.fill(1.f);
    _b = 1.f;
  }

  float calculate(const std::array<float, N>& x) const {

    float sum = std::inner_product(x.begin(), x.end(), _w.begin(), 0.f);

    sum += _b;

    float s = sigmoid(sum);
    return s;
  }
};


class NeuralNet {

  std::array<Neuron<3>, 3>    _nLayer0;
  Neuron<3>                   _nLayer1;

  
  float           loss(const x_array& x, float y_true) const;
  
  static float    static_error_function(const float y_pred, const float y_true);

public:
                  NeuralNet();
  void            fit(const x_array& x, float y);
  void            fit(const std::vector <xy_pair> xy_set);

  float           get_cost(const std::vector <xy_pair> xy_set);


  float           predict(const x_array& x) const;
};
