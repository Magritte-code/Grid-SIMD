#include <iostream>
using std::cout;
using std::endl;

#include <omp.h>

#include "GridSIMD.hpp"


void test ()
{

# pragma omp parallel
  {
    //vReal1 vec (1000);
    vector<double> vec (10000);
  }

}


int main ()
{

# pragma omp parallel
  {
    if (omp_get_thread_num() == 0)
    {
      cout << "n SIMD lanes = " << n_simd_lanes          << endl;
      cout << "n threads    = " << omp_get_num_threads() << endl;
    }
  }


  for (int n = 0; n < 1000; n++)
  {
    test ();
  }


  return (0);

}
