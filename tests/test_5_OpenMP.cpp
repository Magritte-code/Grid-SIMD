#include <iostream>
using std::cout;
using std::endl;

#include <omp.h>

#include "GridSIMD.hpp"


struct many_vReals
{
    vReal vec1;
    vReal vec2;
    vReal vec3;
    vReal vec4;
    vReal vec5;
    vReal vec6;
    vReal vec7;
    vReal vec8;
    vReal vec9;
    vReal vec10;
    vReal vec11;
    vReal vec12;
    vReal vec13;
    vReal vec14;
    vReal vec15;
    vReal vec16;
    vReal vec17;
    vReal vec18;
    vReal vec19;
    vReal vec20;
    vReal vec21;
    vReal vec22;
    vReal vec23;
    vReal vec24;
    vReal vec25;
    vReal vec26;
    vReal vec27;
    vReal vec28;
    vReal vec29;
    vReal vec30;
    vReal vec31;
    vReal vec32;
    vReal vec33;
    vReal vec34;
    vReal vec35;
    vReal vec36;
    vReal vec37;
    vReal vec38;
    vReal vec39;
    vReal vec40;
    vReal vec41;
    vReal vec42;
    vReal vec43;
    vReal vec44;
    vReal vec45;
    vReal vec46;
    vReal vec47;
    vReal vec48;
    vReal vec49;
    vReal vec50;
};

struct many_many_vReals
{
    many_vReals mv1;
    many_vReals mv2;
    many_vReals mv3;
    many_vReals mv4;
    many_vReals mv5;
    many_vReals mv6;
    many_vReals mv7;
    many_vReals mv8;
    many_vReals mv9;
    many_vReals mv10;
    many_vReals mv11;
    many_vReals mv12;
    many_vReals mv13;
    many_vReals mv14;
    many_vReals mv15;
    many_vReals mv16;
    many_vReals mv17;
    many_vReals mv18;
    many_vReals mv19;
    many_vReals mv20;
};


void test ()
{

# pragma omp parallel
  {
    many_many_vReals mv1;
    many_many_vReals mv2;
    many_many_vReals mv3;
    many_many_vReals mv4;
    many_many_vReals mv5;
    many_many_vReals mv6;
    many_many_vReals mv7;
    many_many_vReals mv8;
    many_many_vReals mv9;
    many_many_vReals mv10;
    many_many_vReals mv11;
    many_many_vReals mv12;
    many_many_vReals mv13;
    many_many_vReals mv14;
    many_many_vReals mv15;
    many_many_vReals mv16;
    many_many_vReals mv17;
    many_many_vReals mv18;
    many_many_vReals mv19;
    many_many_vReals mv20;
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
