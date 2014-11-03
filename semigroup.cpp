#include <iostream>
#include "semigroup.hpp"

void init_full_N(Semigroup &S){
  epi8 block ={1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8};
  for(auto i=0; i<NBLOCKS; i++){
    S.blocks[i] = block;
    block = block + 8;
  }
  S.genus = 0;
  S.conductor = 1;
  S.min = 1;
}

ostream& operator<<(ostream& os,const Semigroup& S){
  ind_t i=1;
  for(;i<SIZE and S.decs[i]!=1;++i);
  os<<'<'<<(int)(i++);
  for(;i<SIZE;++i){
    if(S.decs[i]==1) os<<','<<(int)i;
  }
  return os<<'>'; 
}
