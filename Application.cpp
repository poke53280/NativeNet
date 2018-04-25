
//
// Ref.: http://neuralnetworksanddeeplearning.com/index.html
//

#include "stdafx.h"

#include <cmath>
#include <array>
#include <numeric>
#include <assert.h>
#include <random>




static const int N = 3;

class Neuron {
  
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

  std::array<Neuron, 3> _nLayer0;

  Neuron _nLayer1;

public:

  NeuralNet() {
    // ...
  }

  // predict
  float calculate(std::array<float, 5> x) const {

    static const int nLayer0 = 3;

    std::array<float, nLayer0> outputs;

    for (int iNode = 0; iNode < nLayer0; iNode++) {

      const Neuron& n = _nLayer0[iNode];

      std::array<float, 3> input;

      std::copy(x.begin() + iNode, x.begin() + iNode + 3, input.begin());

      outputs[iNode] = n.calculate(input);
    }

    float res = _nLayer1.calculate(outputs);

    return res;
  }


};


struct xy_pair {
  std::array<float, 5> _X;
  float _y;

  xy_pair() {
    fill_random();
    calc_Y();
  }

  void fill_random() {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, 5);

    for (float& f : _X) {
      f = float(uni(rng));
    }
  }

  void calc_Y() {
    // The hidden dependency
    _y = std::accumulate(_X.begin(), _X.end(), 0.f);
  }

};

class XY {
public:
  std::vector <xy_pair> _data;

  XY(int n) {
    for (int i = 0; i < n; i++) {
      _data.push_back(xy_pair());
    }
  }

};

int main()
{
  NeuralNet n;

  XY xy(5);

  const std::vector <xy_pair>& d = xy._data;

  for (const xy_pair& p : d) {

    const std::array<float, 5>& x = p._X;
    const float y_true = p._y;

    const float y_pred = n.calculate(x);

    const float diff = abs(y_pred - y_true);

    printf("true: %f pred: %f diff: %f\r\n", y_true, y_pred, diff);

  }
 
  return 0;
}

