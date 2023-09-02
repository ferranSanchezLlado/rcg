#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "int_types.h"

typedef struct Generator Generator;

struct Generator {
  // Number of elements the generator can generate
  u64 (*len)(Generator *self);
  // Argument i must be lower than lenght of generator (obtained through size
  // function)
  char *(*get)(Generator *self, u64 i);
  // Argument i must be lower than lenght of generator (obtained through size
  // function)
  u64 (*size_of)(Generator *self, u64 i);
};

// Argument i must be lower than lenght of generator (obtained through size
// function)
void print_generator(Generator *gen, u64 i);

#endif
