#ifndef FIXED_GENERATOR_H_
#define FIXED_GENERATOR_H_

#include "generator.h"
#include "int_types.h"

typedef struct {
  Generator generator;
  const char *chars;
  u64 len;
  u64 sep;
} FixedGenerator;

FixedGenerator new_fixed(const char *chars, u64 len, u64 sep);
FixedGenerator *new_fixed_ptr(const char *chars, u64 len, u64 sep);

#endif
