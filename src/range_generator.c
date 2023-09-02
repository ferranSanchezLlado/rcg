#include "range_generator.h"
#include <stdio.h>
#include <stdlib.h>

u64 range_generator_len(Generator *self) {
  RangeGenerator *gen = (RangeGenerator *)self;
  return (gen->end - gen->start) / gen->sep;
}

char *range_generator_get(Generator *self, u64 i) {
  RangeGenerator *gen = (RangeGenerator *)self;
  char *c = malloc(sizeof(char));
  *c = gen->start + gen->sep * i;
  return c;
}

u64 range_generator_size_of(__attribute__((unused)) Generator *self,
                            __attribute__((unused)) u64 i) {
  return 1;
}

static const Generator generator = {
    .len = range_generator_len,
    .get = range_generator_get,
    .size_of = range_generator_size_of,
};

// Start must be lower than end
// Seperation must be lower than (end - start)
RangeGenerator new_range(char start, char end, char sep) {
  return (RangeGenerator){
      .generator = generator, .start = start, .end = end, .sep = sep};
  ;
}

RangeGenerator *new_range_ptr(char start, char end, char sep) {
  RangeGenerator *gen = malloc(sizeof(RangeGenerator));
  if (gen == NULL) {
    fprintf(stderr,
            "Couldn't allocate memory for Range generator with start = %c, end "
            "= %c, sep = %c\n",
            start, end, sep);
    exit(1);
  }

  gen->generator = generator;
  gen->start = start;
  gen->end = end;
  gen->sep = sep;

  return gen;
}
