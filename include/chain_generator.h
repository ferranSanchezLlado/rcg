#ifndef CHAIN_H_
#define CHAIN_H_

#include "generator.h"
#include "int_types.h"

typedef struct {
  Generator generator;
  Generator **generators;
  u64 len;
} ChainGenerator;

ChainGenerator new_chain(Generator **generators, u64 len);
void free_chain(ChainGenerator generator);

#endif
