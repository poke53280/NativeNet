
#include "stdafx.h"
#include "xy_pair.h"
#include <random>
#include <numeric>


//////////////////////////////////////////////////////////////////////////////////
//
//    xy_pair()
//

xy_pair::xy_pair()
{
    fill_random();
    calc_Y();
}


//////////////////////////////////////////////////////////////////////////////////
//
//    fill_random()
//

void
xy_pair::fill_random()
{

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<float> uni(0, 1);

  for (float& f : _X) {
    f = float(uni(rng));
  }
}


//////////////////////////////////////////////////////////////////////////////////
//
//    calc_Y()
//

void
xy_pair::calc_Y()
{
  // The hidden dependency
  float sum = std::accumulate(_X.begin(), _X.end(), 0.f);
  _y = sum / _X.size();
}


//////////////////////////////////////////////////////////////////////////////////
//
//    print()
//

void
xy_pair::print() const
{
  printf("X: %f, %f, %f, %f, %f => y: %f\r\n", _X[0], _X[1], _X[2], _X[3], _X[4], _y);
}




