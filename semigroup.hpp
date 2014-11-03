#ifndef MONOID_HPP
#define MONOID_HPP

#include <cassert>
#include <cstdint>
#include <iostream>
#include <x86intrin.h>
#include "config.hpp"

using namespace std;

typedef uint8_t epi8 __attribute__ ((vector_size (16)));
typedef uint8_t dec_numbers[SIZE] __attribute__ ((aligned (16)));
typedef epi8 dec_blocks[NBLOCKS];
typedef uint_fast64_t ind_t;  // The type used for array indexes

struct Semigroup{
  union {
    dec_numbers decs;
    dec_blocks blocks;
  };
  ind_t conductor, min, genus;
};

class ALL {};
class CHILDREN {};

template <class T> class GeneratorIter{
private:
  const Semigroup &nsg;
  unsigned int mask;   // movemask_epi8 returns a 32 bits values
  ind_t iblock, gen, bound;
public:
  GeneratorIter(const Semigroup &mon);
  bool move_next();
  uint8_t count();
  ind_t get_gen() const;
};

void init_full_N(Semigroup &);
ostream& operator<<(ostream& os,const Semigroup& S);
void copy_blocks(dec_blocks &__restrict__ dst,const dec_blocks &__restrict__ src);
void remove_generator(Semigroup &__restrict__ dst,const Semigroup &__restrict__ src,ind_t gen);
Semigroup remove_generator(const Semigroup &src, ind_t gen);


//Constants 

const epi8 zero = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const epi8 block1 = zero + 1;
const uint8_t m1 = 255;
const epi8 shift16[16] =
  { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15},
    {m1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14},
    {m1,m1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13},
    {m1,m1,m1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
    {m1,m1,m1,m1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},
    {m1,m1,m1,m1,m1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},
    {m1,m1,m1,m1,m1,m1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {m1,m1,m1,m1,m1,m1,m1, 0, 1, 2, 3, 4, 5, 6, 7, 8},
    {m1,m1,m1,m1,m1,m1,m1,m1, 0, 1, 2, 3, 4, 5, 6, 7},
    {m1,m1,m1,m1,m1,m1,m1,m1,m1, 0, 1, 2, 3, 4, 5, 6},
    {m1,m1,m1,m1,m1,m1,m1,m1,m1,m1, 0, 1, 2, 3, 4, 5},
    {m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1, 0, 1, 2, 3, 4},
    {m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1, 0, 1, 2, 3},
    {m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1, 0, 1, 2},
    {m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1, 0, 1},
    {m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1, 0} };
const epi8 mask16[16] =
  { {m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0,m1,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0,m1,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0,m1,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0,m1,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,m1,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,m1,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,m1,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,m1,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,m1,m1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,m1} };

//Implementation here

extern inline epi8 load_unaligned_epi8(const uint8_t *t){ 
  return (epi8) _mm_loadu_si128((__m128i *) (t)); 
}

extern inline epi8 shuffle_epi8(epi8 b, epi8 sh){ 
  return (epi8) _mm_shuffle_epi8((__m128i) b, (__m128i) sh);
}

extern inline int movemask_epi8(epi8 b){ 
  return _mm_movemask_epi8((__m128i) b);
}

template<> inline 
GeneratorIter<ALL>::GeneratorIter(const Semigroup &S)
  : nsg(S), bound((S.conductor+S.min+15) >> 4){
  epi8 block;
  iblock = 0;
  block = nsg.blocks[0];
  mask  = movemask_epi8(block == block1);
  mask &= 0xFFFE; // 0 is not a generator
  gen = - 1;
}

template<> inline 
GeneratorIter<CHILDREN>::GeneratorIter(const Semigroup &S)
  : nsg(S), bound((S.conductor+S.min+15) >> 4){
  epi8 block;
  iblock = nsg.conductor >> 4;
  block = nsg.blocks[iblock] & mask16[nsg.conductor & 0xF];
  mask  = movemask_epi8(block == block1);
  gen = (iblock << 4) - 1;
}

template <class T> inline 
uint8_t GeneratorIter<T>::count(){
  uint8_t nbr = _mm_popcnt_u32(mask); // popcnt returns a 8 bits value
  for (iblock++; iblock < bound; iblock++)
    nbr += _mm_popcnt_u32(movemask_epi8(nsg.blocks[iblock] == block1));
  return nbr;
}

template <class T> inline 
ind_t GeneratorIter<T>::get_gen() const {
  return gen; 
}

template <class T> inline bool 
GeneratorIter<T>::move_next(){
  while (!mask)
    {
      iblock++;
      if (iblock > bound) return false;
      gen = (iblock << 4) - 1;
      mask  = movemask_epi8(nsg.blocks[iblock] == block1);
    }
  unsigned char shift = __bsfd (mask) + 1; // Bit Scan Forward
  gen += shift;
  mask >>= shift;
  return true;
};

inline void copy_blocks(dec_blocks &dst, dec_blocks const &src){
  for (ind_t i=0; i<NBLOCKS; i++) dst[i] = src[i];
}

inline void remove_generator(Semigroup &__restrict__ dst,const Semigroup &__restrict__ src,ind_t gen){
  ind_t start_block, decal;
  epi8 block;

  assert(src.decs[gen] == 1);

  dst.conductor = gen + 1;
  dst.genus = src.genus + 1;
  dst.min = (gen == src.min) ? dst.conductor : src.min;

  copy_blocks(dst.blocks, src.blocks);

  start_block = gen >> 4;
  decal = gen & 0xF;
  // Shift block by decal uchar
  block = shuffle_epi8(src.blocks[0], shift16[decal]);
  dst.blocks[start_block] -= ((block != zero) & block1);
#if NBLOCKS >= 5

#define CASE_UNROLL(i_loop)						\
  case i_loop :								\
    dst.blocks[i_loop+1] -= (load_unaligned_epi8(srcblock) != zero) & block1; \
    srcblock += sizeof(epi8);
  {
    const uint8_t *srcblock = src.decs + sizeof(epi8) - decal;
    switch(start_block){
      CASE_UNROLL(0);
#if NBLOCKS > 2
      CASE_UNROLL(1);
#endif
#if NBLOCKS > 3
      CASE_UNROLL(2);
#endif
#if NBLOCKS > 4
      CASE_UNROLL(3);
#endif
#if NBLOCKS > 5
      CASE_UNROLL(4);
#endif
#if NBLOCKS > 6
      CASE_UNROLL(5);
#endif
#if NBLOCKS > 7
      CASE_UNROLL(6);
#endif
#if NBLOCKS > 8
      CASE_UNROLL(7);
#endif
#if NBLOCKS > 9
      CASE_UNROLL(8);
#endif
#if NBLOCKS > 10
      CASE_UNROLL(9);
#endif
#if NBLOCKS > 11
      CASE_UNROLL(10);
#endif
#if NBLOCKS > 12
      CASE_UNROLL(11);
#endif
#if NBLOCKS > 13
      CASE_UNROLL(12);
#endif
#if NBLOCKS > 14
      CASE_UNROLL(13);
#endif
#if NBLOCKS > 15
      CASE_UNROLL(14);
#endif
#if NBLOCKS > 16
#error "Too many blocks"
#endif
    }
  }
#else
#warning "Loop not unrolled"
  
  for (auto i=start_block+1; i<NBLOCKS; i++){
    block = load_unaligned_epi8(src.decs + ((i-start_block)<<4) - decal);
    dst.blocks[i] -= ((block != zero) & block1);
  }
#endif
  
  assert(dst.decs[dst.conductor-1] == 0);
}

inline Semigroup remove_generator(const Semigroup &src, ind_t gen){
  Semigroup dst;
  remove_generator(dst, src, gen);
  return dst;
}

#endif
