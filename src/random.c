#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const u64 MAX_FAILS = 10000;

u64 rand_int_max(u64 max) {
  u32 a = rand(), b = rand();
  return ((u64)a << 32 | b) % max;
}

typedef enum { CONTINUE, EXIT } Failure;

Failure process_failure(u64 expected_size, u64 real_size) {
  char line[256];

  for (;;) {
    printf("Reach limit number of tries (%lu) to generate random string with "
           "len=%lu. It could only generate a string with len=%lu. The "
           "remaining bits are unitialized if you want to continue anyway "
           "press [y]. Otherwise press [q] to exit.\n> ",
           MAX_FAILS, expected_size, real_size);

    if (fgets(line, sizeof(line), stdin)) {
      switch (line[0]) {
      case 'y':
        return CONTINUE;
      case 'q':
        return EXIT;
      }
    }
  }
}

char *generate_random_string(Generator *gen, u64 size) {
  char *str = malloc(size);
  if (str == NULL) {
    fprintf(
        stderr,
        "Couldn't allocate memory to generate random string with len = %lu\n",
        size);
    exit(1);
  }

  srand(time(NULL)); // Random seed

  u64 n = size, failed = 0;
  while (n > 0 && failed < MAX_FAILS) {
    u64 i = rand_int_max(gen->len(gen));

    char *ch = gen->get(gen, i);
    u64 len = gen->size_of(gen, i);

    if (len > n) { // Checks if word would fit
      failed++;
      continue;
    }

    memcpy(&str[n - 1], ch, len);
    free(ch);
    n -= len;
  }

  if (failed >= MAX_FAILS && process_failure(size, size - n) == EXIT) {
    exit(0);
  }

  return str;
}
