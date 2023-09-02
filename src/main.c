#include "chain_generator.h"
#include "fixed_generator.h"
#include "generator.h"
#include "random.h"
#include "range_generator.h"
#include "selection.h"
#include <stdio.h>
#include <stdlib.h>

void test() {
  RangeGenerator upper_case = new_range('A', 'Z', 1);
  RangeGenerator lower_case = new_range('a', 'z', 1);
  RangeGenerator digits = new_range('0', '9', 1);
  FixedGenerator special = new_fixed("@%+\\/'!#$^?:,(){}[]~-_.", 23, 1);

  Generator *generators[] = {(Generator *)&upper_case, (Generator *)&lower_case,
                             (Generator *)&digits, (Generator *)&special};

  ChainGenerator all = new_chain(generators, 4);

  unsigned i = 5;
  print_generator((Generator *)&upper_case, i);
  print_generator((Generator *)&lower_case, i);
  print_generator((Generator *)&digits, i);
  print_generator((Generator *)&special, i);
  print_generator((Generator *)&all, i);

  char *rand_str = generate_random_string((Generator *)&all, 101);
  rand_str[100] = 0;

  printf("Random string with everything: %s\n", rand_str);

  free(rand_str);
}

int main() {
  printf("---- Welcome to Random Character Generator (RCG) ----\n"
         "This program allows you to generate random strings using different "
         "generators.\n\n");

  for (;;) {
    u64 len = select_len_from_input();
    ChainGenerator gens = select_from_input();

    char *rand_str = generate_random_string((Generator *)&gens, len);

    printf("\nRANDOM STRING (len=%ld): ", len);
    fwrite(rand_str, sizeof(char), len, stdout);
    printf("\n\n");

    free_chain(gens);
    free(rand_str);

    if (!select_again())
      break;
  }

  return 0;
}
