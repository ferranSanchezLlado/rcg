#ifndef RANDOM_H_
#define RANDOM_H_

#include "generator.h"
#include "int_types.h"

// Doesn't include a null terminated byted
char *generate_random_string(Generator *generator, u64 size);

#endif
