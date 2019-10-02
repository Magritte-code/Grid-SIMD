#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;

#include <omp.h>

#include "GridSIMD.hpp"


typedef vector<vReal1> vReal2;
typedef vector<long> Long1;

///  Raypair: data structure for a pair of rays
///////////////////////////////////////////////

struct RayPair
{

  vReal1 chi;      ///< opacities
  Long1  nrs;      ///< corresponding cell indices

  vReal denominator;           ///< helper variable


  RayPair (const long length)
  // int resize (const long length)
  {
    cout << "In Raypair resizer..." << endl;

    chi.resize (length);
    nrs.resize (length);

    cout << "End of RayPair resizer" << endl;
  }


};





int main ()
{

  long nthrds;

# pragma omp parallel
  {
    nthrds = omp_get_num_threads ();
  }

  const long length     = 100;
  const long n_off_diag =   0;

  nthrds = 4;// = get_nthreads ();

  cout << "number of threads = " << nthrds << endl;
  cout << omp_get_num_threads ()           << endl;


  vector <RayPair> rayPairs (nthrds, RayPair (length));

  // // --- Solution ---
  // vector <RayPair> rayPairs (nthrds);
  //
  // for (int i = 0; i < rayPairs.size(); i++)
  // {
  //  rayPairs[i].resize (length);
  // }
  // // --- Solution ---



  for (RayPair &rp : rayPairs)
  {
    cout << &rp << endl;
  }

  return (0);

}
