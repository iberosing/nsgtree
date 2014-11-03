#ifndef CONFIG_HPP
#define CONFIG_HPP
#define MAX_GENUS 40
#define STACK_SIZE MAX_GENUS*(MAX_GENUS+1)
#define SIZE_BOUND (3*(MAX_GENUS-1))
#define STACK_BOUND 11
#define NBLOCKS ((SIZE_BOUND+15) >> 4)
#define SIZE (NBLOCKS << 4)
#endif
