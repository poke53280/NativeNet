
#include "stdafx.h"
#include "NeuralNet.h"  
#include <numeric>

/*

In    L0            L1

0

1    N(0,1,2)

2    N(1,2,3)       L0 (3 in)   => y

3    N(2,3,4)

4

*/


//////////////////////////////////////////////////////////////////////////////////
//
//    NeuralNet()
//

NeuralNet::NeuralNet() {
  AI_NOP;
}


//////////////////////////////////////////////////////////////////////////////////
//
//    predict
//

float
NeuralNet::predict(const x_array& x) const {

  static const int nLayer0 = 3;

  std::array<float, nLayer0> outputs;

  // Layer 0

  for (int iNode = 0; iNode < nLayer0; iNode++) {

    const Neuron& n = _nLayer0[iNode];

    std::array<float, 3> input;

    std::copy(x.begin() + iNode, x.begin() + iNode + 3, input.begin());

    outputs[iNode] = n.calculate(input);
  }

  // Layer 1

  float res = _nLayer1.calculate(outputs);

  return res;
}

//////////////////////////////////////////////////////////////////////////////////
//
//    static_error_function
//

float
NeuralNet::static_error_function(const float y_pred, const float y_true)
{
  const float diff = abs(y_pred - y_true);
  return diff;
}

//////////////////////////////////////////////////////////////////////////////////
//
//    loss
//

float
NeuralNet::loss(const x_array& x, float y_true) const {

  const float y_pred = predict(x);
  const float error = static_error_function(y_pred, y_true);

  return error;
}

//////////////////////////////////////////////////////////////////////////////////
//
//    fit
//

void
NeuralNet::fit(const x_array& x, float y) {

  const float y_pred = predict(x);
  const float diff = loss(x, y);

  printf("   Y true: %f pred: %f diff: %f\r\n", y, y_pred, diff);

  // Todo: Make loss smaller...

}

//////////////////////////////////////////////////////////////////////////////////
//
//    fit
//

void
NeuralNet::fit(const std::vector <xy_pair> xy_set) {

  for (const xy_pair& p : xy_set) {

    const x_array& x = p._X;
    const float y_true = p._y;

    p.print();

    fit(x, y_true);
  }
}

//////////////////////////////////////////////////////////////////////////////////
//
//    get_cost
//
//   C = C (w,b)
//

float
NeuralNet::get_cost(const std::vector <xy_pair> xy_set) {

  float error_sum = 0.f;

  const int n = int(xy_set.size());

  for (const xy_pair& p : xy_set) {

    const x_array& x = p._X;
    const float y_true = p._y;

    p.print();

    const float a = predict(x);

    error_sum += ((y_true - a) * (y_true - a));
  }

  const float mse = error_sum / (2 * n);

  return mse;
}



