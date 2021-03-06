
//
// Ref.: http://neuralnetworksanddeeplearning.com/index.html
//

#include "stdafx.h"

#include <assert.h>
#include <array>     
#include "NeuralNet.h"
#include "xy_pair.h"
#include <vector>


#include "San_CSV.h"

int main()
{

  San_CSV s;


  NeuralNet n;

  std::vector <xy_pair> train;
  std::vector <xy_pair> test;

  const int nTrain = 7;
  const int nTest = 3;

  // Generate dataset.
  // Random data X with hidden dependency to target y.

  for (int i = 0; i < nTrain; i++) {
    train.push_back(xy_pair());
  }

  for (int i = 0; i < nTest; i++) {
    test.push_back(xy_pair());
  }

  // Train

  n.fit(train);

  // Evaluate on test set.
 
  float mse = n.get_cost(test);

  printf("MSE = %f\r\n", mse);
 
  return 0;
}




