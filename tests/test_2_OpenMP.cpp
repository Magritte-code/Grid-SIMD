#include <iostream>
using std::cout;
using std::endl;

#include <omp.h>

#include "catch.hpp"

#include "GridSIMD.hpp"


TEST_CASE ("Some simple OpenMP parallelised operations")
{

  cout << "Hello!" << endl;
  cout << "n SIMD lanes is " << n_simd_lanes << endl;


  const long N = 1000;

  vReal1 vec1;
  vReal1 vec2;
  vReal1 vec3;
  vReal1 vec4;

  vec1.resize (N);
  vec2.resize (N);
  vec3.resize (N);
  vec4.resize (N);



  long index = 0;


  for (long n = 0; n < N; n++)
  {
    index++;

    for (int lane = 0; lane < n_simd_lanes; lane++)
    {
      vec1[n].putlane(index, lane);
      vec2[n].putlane(index, lane);
    }
  }


  # pragma omp parallel
  {
    vReal1 vec5 (2000);

    vReal test = 58;

    long start =  (omp_get_thread_num()    * N) / omp_get_num_threads();
    long stop  = ((omp_get_thread_num()+1) * N) / omp_get_num_threads();

    vec5.resize (800000);

    for (long n = start; n < stop; n++)
    {
      vec3[n] = vec1[n] + vec2[n];
      vec4[n] = vec3[n] / vec1[n];
    }
  }

  for (long n = 0; n < N; n++)
  {
    for (int lane = 0; lane < n_simd_lanes; lane++)
    {
      double v3 = vec3[n].getlane(lane);
      double v4 = vec4[n].getlane(lane);

    CHECK (v4 == 2.0);
    }
  }

}
