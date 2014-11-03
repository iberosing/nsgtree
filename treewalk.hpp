#ifndef TREEWALK_HPP
#define TREEWALK_HPP

#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include <cilk/reducer_list.h>
#include "semigroup.hpp"
#include "test.hpp"

typedef unsigned long int ResultsType[MAX_GENUS];

struct Results{
  ResultsType values;
  Results();
  void reset();
};

struct MonoidReducer:cilk::monoid_base<Results>{
  static void reduce (Results *left, Results *right);
};

class ResultsReducer{
private:
  cilk::reducer<MonoidReducer> imp_;
public:
  ResultsReducer();
  unsigned long int& operator[](ind_t i);
  ResultsType &get_results();
  void reset();
};

extern ResultsReducer cilk_results;

void walk_children(const Semigroup &S);
void list_children(const Semigroup &S,ind_t bound);
void walk_children_stack(Semigroup S,ind_t bound,ResultsType &res);

inline void MonoidReducer::reduce (Results *left, Results *right){
  for(auto i=0; i<MAX_GENUS; i++) left->values[i] += right->values[i];
}

inline Results::Results(){
  reset();
}

inline void Results::reset(){
   for(int i=0; i<MAX_GENUS; i++) values[i] = 0;
}

inline ResultsReducer::ResultsReducer():imp_(){
}

inline unsigned long int& ResultsReducer::operator[](ind_t i){
  return imp_.view().values[i]; 
} 
inline ResultsType& ResultsReducer::get_results(){
  return imp_.view().values;
} 

inline void ResultsReducer::reset(){
  imp_.view().reset();
}

#endif
