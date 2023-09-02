#include "fixed_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u64 fixed_generator_len(Generator *self) {
  FixedGenerator *gen = (FixedGenerator *)self;
  return gen->len / gen->sep;
}

char *fixed_generator_get(Generator *self, u64 i) {
  FixedGenerator *gen = (FixedGenerator *)self;
  u64 n = gen->sep;

  char *c = malloc(n * sizeof(char));
  memcpy(c, &gen->chars[i * n], n);
  return c;
}

u64 fixed_generator_size_of(Generator *self, __attribute__((unused)) u64 i) {
  FixedGenerator *gen = (FixedGenerator *)self;
  return gen->sep;
}

static const Generator generator = {
    .len = fixed_generator_len,
    .get = fixed_generator_get,
    .size_of = fixed_generator_size_of,
};

// Seperation must be bigger than 0
// Separtation must be lower than lenght
FixedGenerator new_fixed(const char *chars, u64 len, u64 sep) {
  return (FixedGenerator){
      .generator = generator,
      .chars = chars,
      .len = len,
      .sep = sep,
  };
}

FixedGenerator *new_fixed_ptr(const char *chars, u64 len, u64 sep) {
  FixedGenerator *gen = malloc(sizeof(FixedGenerator));
  if (gen == NULL) {
    fprintf(stderr,
            "Couldn't allocate memory for Range generator with chars = %s, len "
            "= %lu, sep = %lu\n",
            chars, len, sep);
    exit(1);
  }

  gen->generator = generator;
  gen->chars = chars;
  gen->len = len;
  gen->sep = sep;

  return gen;
}
