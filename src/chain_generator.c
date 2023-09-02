#include "chain_generator.h"
#include "generator.h"
#include <stdlib.h>

u64 chain_generator_len(Generator *self) {
  ChainGenerator *gens = (ChainGenerator *)self;

  u64 size = 0;
  for (u64 i = 0; i < gens->len; i++) {
    Generator *gen = gens->generators[i];
    size += gen->len(gen);
  }

  return size;
}

typedef struct Index {
  u64 gen;
  u64 i;
} Index;

Index find_index(ChainGenerator *gens, u64 i) {
  for (u64 j = 0; j < gens->len; j++) {
    Generator *gen = gens->generators[j];
    u64 size = gen->len(gen);

    if (i < size) {
      Index index = {.gen = j, .i = i};
      return index;
    }

    i -= size;
  }
  Index index = {.gen = -1, .i = -1};
  return index;
}

char *chain_generator_get(Generator *self, u64 i) {
  ChainGenerator *gens = (ChainGenerator *)self;

  Index index = find_index(gens, i);
  Generator *gen = gens->generators[index.gen];
  return gen->get(gen, index.i);
}

u64 chain_generator_size_of(Generator *self, u64 i) {
  ChainGenerator *gens = (ChainGenerator *)self;

  Index index = find_index(gens, i);
  Generator *gen = gens->generators[index.gen];
  return gen->size_of(gen, index.i);
}

const Generator generator = {
    .len = chain_generator_len,
    .get = chain_generator_get,
    .size_of = chain_generator_size_of,
};

ChainGenerator new_chain(Generator **generators, u64 len) {
  return (ChainGenerator){
      .generator = generator,
      .generators = generators,
      .len = len,
  };
}

void free_chain(ChainGenerator generator) {
  for (u64 i = 0; i < generator.len; ++i) {
    free(generator.generators[i]);
  }

  free(generator.generators);
}
