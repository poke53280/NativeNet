
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
    _w.fill(0.f);
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


void fill_random(std::array<float, 5>& x) {
  
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(0, 5); // guaranteed unbiased

  for (float& f : x) {
    f = float(uni(rng));
  }
}


int main()
{
  NeuralNet n;

  struct Pim {
    std::array<float, 5> X;
    float y;

  };

  Pim p;

  fill_random(p.X);

  p.y = std::accumulate(p.X.begin(), p.X.end(), 0.f);


  float y = n.calculate(p.X);

 
  return 0;
}

