#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_generator(Generator *gen, u64 i) {
  u64 len = (gen->len)(gen);
  char *ch = (gen->get)(gen, i);
  u64 size_of = (gen->size_of)(gen, i);

  // Adds null byte so it can be printed
  char *str = malloc((size_of + 1) * sizeof(char));
  memcpy(str, ch, size_of);
  str[size_of] = 0;

  printf("len = %lu\nelement=%lu:\n  - get: %s\n  - size_of: %lu\n", len, i,
         str, size_of);

  free(str);
  free(ch);
}
