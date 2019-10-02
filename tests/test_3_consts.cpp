#include <iostream>
using std::cout;
using std::endl;

#include "catch.hpp"

#include "GridSIMD.hpp"


double test_const (
    const vReal vec)
{
  double sum = 0;

  for (int lane; lane < n_simd_lanes; lane++)
  {
    sum += vec.getlane (lane);
  }


  return sum;

}


TEST_CASE ("function constants")
{

  cout << "Hello!" << endl;
  cout << "n SIMD lanes is " << n_simd_lanes << endl;


  const long N = 1000;

  vReal vec = 1.0;

  CHECK (test_const(vec) == 4.0);
}
