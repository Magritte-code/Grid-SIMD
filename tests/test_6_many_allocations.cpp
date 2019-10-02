#include <iostream>
using std::cout;
using std::endl;

#include <omp.h>

#include "GridSIMD.hpp"


void test ()
{

//# pragma omp parallel
//  {
    vReal1 v1 (40);
    vReal1 v2 (40);
    vReal1 v3 (40);
    vReal1 v4 (40);
    vReal1 v5 (40);
    vReal1 v6 (40);
    vReal1 v7 (40);
    vReal1 v8 (40);
    vReal1 v9 (40);

    v1.resize (90000);
    v2.resize (500);
    v3.resize (50000);
    v4.resize (700);
    v5.resize (50000);
    v6.resize (30000);
    v7.resize (50000);
    v8.resize (450);
    v9.resize (6000);
//  }

# pragma omp parallel
  {
    if (omp_get_thread_num() == 0)
    {
      cout << "n SIMD lanes = " << n_simd_lanes          << endl;
      cout << "n threads    = " << omp_get_num_threads() << endl;
    }
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


  for (int n = 0; n < 10000; n++)
  {
    test ();
  }


  return (0);

}
