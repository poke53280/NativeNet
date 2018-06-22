#pragma once

#include <array>
#include <vector>
#include <numeric>
#include "xy_pair.h"

class Neuron {

  std::array<float, 3>      _w;
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

  float calculate(const std::array<float, 3>& x, const std::array<float, 3>& w_delta, const float b_delta) const {

    float sum = std::inner_product(x.begin(), x.end(), _w.begin(), 0.f) + std::inner_product(x.begin(), x.end(), w_delta.begin(), 0.f);

    sum += _b;
    sum += b_delta;

    float s = sigmoid(sum);
    return s;
  }

  float calculate(const std::array<float, 3>& x) const {
    return calculate(x, { 0, 0, 0 }, 0);
  }



  std::array<float, 5> calculate_gradient(const std::array<float, 3>& x) const {

    static const float d = 0.001f;

    float y0 = calculate(x, { 0, 0, 0 }, 0);
    float y1 = calculate(x, { 0, 0, d }, 0);
    float y2 = calculate(x, { 0, d, 0 }, 0);
    float y3 = calculate(x, { d, 0, 0 }, 0);

    float yb = calculate(x, { 0, 0, 0 }, d);

    return { y0, y1, y2, y3, yb };
  }


};


class NeuralNet {

  std::array<Neuron, 3>    _nLayer0;
  Neuron                   _nLayer1;

  
  float           loss(const x_array& x, float y_true) const;
  
  static float    static_error_function(const float y_pred, const float y_true);

public:
                  NeuralNet();
  void            fit(const x_array& x, float y);
  void            fit(const std::vector <xy_pair> xy_set);

  float           get_cost(const std::vector <xy_pair> xy_set);


  float           predict(const x_array& x) const;
};
