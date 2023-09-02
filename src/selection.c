#include "selection.h"
#include "chain_generator.h"
#include "fixed_generator.h"
#include "range_generator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CHAR '\0'
#define BUFFER_LEN 256

#define EXIT 'q'
#define LOWER_CASE_OPTION '1'
#define UPPER_CASE_OPTION '2'
#define DIGITS_OPTION '3'
#define SPECIAL_OPTION '4'

#define MAX_U64 18446744073709551615UL
#define MAX_BUFFER_DIGIT 65 // 64 digits + endline

static const char *SPECIAL_CHARS = "@%+\\/'!#$^?:,(){}[]~-_.";

u8 count_bits(u8 value) {
  u8 count = 0;
  while (value != 0) {
    count++;
    value &= value - 1;
  }
  return count;
}

Generator **select_base(u8 options) {
  // Ignore bits that will not be used
  u64 count = count_bits(options & MAX_TYPES);
  Generator **gens = malloc(count * sizeof(Generator *));

  if (options & LowerCase) {
    gens[--count] = (Generator *)new_range_ptr('a', 'z', 1);
  }
  if (options & UpperCase) {
    gens[--count] = (Generator *)new_range_ptr('A', 'Z', 1);
  }
  if (options & Digits) {
    gens[--count] = (Generator *)new_range_ptr('0', '9', 1);
  }
  if (options & Special) {
    gens[--count] =
        (Generator *)new_fixed_ptr(SPECIAL_CHARS, strlen(SPECIAL_CHARS), 1);
  }

  assert(count == 0);
  return gens;
}

ChainGenerator select_from_input() {
  u8 options = 0;
  char line[BUFFER_LEN];

  memset(line, INIT_CHAR, sizeof(char) * BUFFER_LEN);

  while (options == 0) {
    printf("Select options specified below [any order]:\n"
           "%c) Lower case [a-z]\n"
           "%c) Upper case [A-Z]\n"
           "%c) Digits [0-9]\n"
           "%c) Special chars [%s]\n"
           "%c) EXIT PROGRAM\n> ",
           LOWER_CASE_OPTION, UPPER_CASE_OPTION, DIGITS_OPTION, SPECIAL_OPTION,
           SPECIAL_CHARS, EXIT);

    if (fgets(line, sizeof(line), stdin)) {
      for (u64 i = 0; i < sizeof(line); i++) {
        char c = line[i];

        switch (c) {
        case EXIT:
          exit(0);

        case LOWER_CASE_OPTION:
          options |= LowerCase;
          break;

        case UPPER_CASE_OPTION:
          options |= UpperCase;
          break;

        case DIGITS_OPTION:
          options |= Digits;
          break;

        case SPECIAL_OPTION:
          options |= Special;
          break;

        case INIT_CHAR:
        case '\n':
          break;

        default:
          options = 0;
          printf("Unknown option: %c\n", c);
          break;
        }
      }
    }
  }

  return new_chain(select_base(options), count_bits(options));
}

u64 select_len_from_input() {
  u64 len;
  char line[MAX_BUFFER_DIGIT];

  memset(line, INIT_CHAR, sizeof(char) * MAX_BUFFER_DIGIT);

  for (;;) {
    printf("Choose the desired lenght for the random string. The lenght can't "
           "be larger than a 64-bit unsigned integer [0 - %lu]. Otherwise "
           "press [%c] to exit the program.\n> ",
           MAX_U64, EXIT);

    if (fgets(line, sizeof(line), stdin)) {
      for (u64 i = 0; i < sizeof(line); i++) {
        if (line[i] == EXIT)
          exit(0);
      }

      if (1 == sscanf(line, "%lu", &len))
        return len;

      printf("Unknown option: ");
      fwrite(line, sizeof(char), MAX_BUFFER_DIGIT, stdout);
      printf("\n");
    }
  }
}

bool select_again() {
  char line[BUFFER_LEN];

  for (;;) {
    printf("Would you like to generate a new string? Type [y] for generate a "
           "new string and [n] or [q] to exit.\n> ");

    if (fgets(line, sizeof(line), stdin)) {
      switch (line[0]) {
      case 'y':
        return true;
      case 'n':
      case 'q':
        return false;
      }

      printf("Unknown option: %c\n", line[0]);
    }
  }
}
