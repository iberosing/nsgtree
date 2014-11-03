#include <iostream>
#include <iomanip>
#include <cpuid.h>
#include <cilk/cilk_api.h>
#include "treewalk.hpp"

using namespace std;

ResultsReducer cilk_results;

void walk_children_stack(Semigroup S, ResultsType &res){
  unsigned long int nbr;
  Semigroup data[STACK_SIZE-1], *stack[STACK_SIZE], *current;
  Semigroup **stack_pointer = stack + 1;
  // Nathann's trick to avoid copy
  for (ind_t i=1; i<STACK_SIZE; i++) stack[i] = &(data[i-1]); 
  stack[0] = &S;
  while(stack_pointer != stack){
    --stack_pointer;
    current = *stack_pointer;
    if (current->genus < MAX_GENUS){
      nbr = 0;
      auto it = GeneratorIter<CHILDREN>(*current);
      while (it.move_next()){
	// exchange top with top+1
	stack_pointer[0] = stack_pointer[1];
	remove_generator(**stack_pointer, *current, it.get_gen());
	test_semigroup(**stack_pointer);
	stack_pointer++;
	nbr++;
      }
      *stack_pointer = current;
      res[current->genus] += nbr;
    }
  }
}

void walk_children(const Semigroup &S){
  test_semigroup(S);
  unsigned long int nbr = 0;
  if (S.genus < MAX_GENUS - STACK_BOUND){
      auto it = GeneratorIter<CHILDREN>(S);
      while (it.move_next()){
	cilk_spawn walk_children(remove_generator(S, it.get_gen()));
	nbr++;
      }
      cilk_results[S.genus] += nbr;
  }
  else{
    walk_children_stack(S, cilk_results.get_results());
  }
}

int main(int argc, char **argv){
  Semigroup N;
  unsigned long int total = 0;
  string nproc = "0";
  cout << "Exploring numerical semigroups for genus <= "<< MAX_GENUS;
  cout << " using " << __cilkrts_get_nworkers() << " workers" << endl;

  init_full_N(N);
  walk_children(N);

  cout << endl << "============================" << endl << endl;
  for (unsigned int i=0; i<MAX_GENUS; i++){
    cout << cilk_results[i] << " ";
    total += cilk_results[i];
  }
  cout << endl;
  cout << "Total = " << total << endl;  
  return EXIT_SUCCESS;
}

