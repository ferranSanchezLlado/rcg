#ifndef RANGE_GENERATOR_H_
#define RANGE_GENERATOR_H_

#include "generator.h"

typedef struct {
  Generator generator;
  char start;
  char end;
  char sep;
} RangeGenerator;

RangeGenerator new_range(char start, char end, char sep);
RangeGenerator *new_range_ptr(char start, char end, char sep);

#endif
