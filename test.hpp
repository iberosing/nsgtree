#include <cilk/reducer_ostream.h>
#include <iostream>
#include "semigroup.hpp"

using namespace std;

inline void test_semigroup(const Semigroup& S){
  //Comment the next line to test Wilf conjecture
  return;
  long int c=S.conductor;
  long int g=S.genus;
  long int m=S.min;
  auto it1=GeneratorIter<CHILDREN>(S);
  long int degree=it1.count();
  auto it2=GeneratorIter<ALL>(S);
  long int dimension=it2.count();
  long int Wilf=(c-g)*dimension-c;
  if(Wilf<0){
    cout<<" => Counter example to Wilf conjecture found <= "<<endl;
    cout<<" S = "<<S<<endl;
    cout<<" c = "<<c<<endl;
    cout<<" g = "<<g<<endl;
    cout<<" m = "<<m<<endl;
    cout<<" deg = "<<degree<<endl;
    cout<<" dim = "<<dimension<<endl;
    cout<<" Wilf = "<<Wilf<<endl;
   }
};
