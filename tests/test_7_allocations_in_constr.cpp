#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;

#include <omp.h>

#include "GridSIMD.hpp"


typedef vector<vReal1> vReal2;

struct TestStruct
{

  vReal1 v1;
  vReal1 v2;
  vReal1 v3;
  vReal1 v4;
  vReal1 v5;
  vReal1 v6;
  vReal1 v7;
  vReal1 v8;
  vReal1 v9;

  vReal2 vv1;


  TestStruct (const long length)
  {
    cout << "Constructing TestStruct" << endl;

    v1.resize (length);
    v2.resize (length);
    v3.resize (length);
    v4.resize (length);
    v5.resize (length);
    v6.resize (length);
    v7.resize (length);
    v8.resize (length);
    v9.resize (length);

    vv1.resize (length);

    for (long i = 0; i < length; i++)
    {
      vv1[i].resize (length);
    }

    cout << "TestStruct Constructed" << endl;
  }

};




int main ()
{

  long nthrds;
  long length;

# pragma omp parallel
  {
    nthrds = omp_get_num_threads ();
  }

  cout << "Give nthrds:" << endl;
  cin  >> nthrds;

  cout << "Give length:" << endl;
  cin  >> length;

  vector <TestStruct> ts (nthrds, TestStruct (length));

  cout << "ts size = " << ts.size () << endl;

  return (0);

}
