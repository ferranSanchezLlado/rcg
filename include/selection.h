#ifndef SELECTION_H_
#define SELECTION_H_

#include "chain_generator.h"
#include "generator.h"
#include <stdbool.h>

typedef enum {
  LowerCase = 1 << 0,
  UpperCase = 1 << 1,
  Digits = 1 << 2,
  Special = 1 << 3,
} DefaultOptions;

#define MAX_TYPES ((Special << 1) - 1)

Generator **select_base(u8 options);
ChainGenerator select_from_input();
u64 select_len_from_input();
bool select_again();

#endif
