# Random Charcter Generator

Simple shell program that allow you generate random string with any lenght through the use of different generators, such as:
- Lower case [`a-z`]
- Upper case [`A-Z`]
- Digits [`0-9`]
- Special chars [`@%+\/'!#$^?:,(){}[]~-_.`]

This projects allows for easy implementation of new generators by using a common interface used to generate random characters with any size. For example, it should be possible to create a generator of emojis. Even, it could allow to ask the user for a set charcters to create a new generator.

Moreover, the current implementation allows for the creation of variable lenght generators. Meaning a generator could remove charecters that already used.

## Installation

Download the project and run using make:
```shell
git clone https://github.com/ferranSanchezLlado/rcg.git
cd rcg
make run
```


## Usage

Example of a basic interaction, when '>' appears it means that an input from the user is required:

```
---- Welcome to Random Character Generator (RCG) ----
This program allows you to generate random strings using different generators.

Choose the desired lenght for the random string. The lenght can't be larger than a 64-bit unsigned integer [0 - 18446744073709551615]. Otherwise press [q] to exit the program.
> 100
Select options specified below [any order]:
1) Lower case [a-z]
2) Upper case [A-Z]
3) Digits [0-9]
4) Special chars [@%+\/'!#$^?:,(){}[]~-_.]
q) EXIT PROGRAM
> 123

RANDOM STRING (len=100): 7nbGnBfRFItVdS5j6UDhF5ttL2gBhqEDC2DeyATHmVgoyjXLNEkAwbAvUkjax2hF4Mxn8U45pCn7T3JfPCCdpSlvmPbEoheymB8w

Would you like to generate a new string? Type [y] for generate a new string and [n] or [q] to exit.
> y
Choose the desired lenght for the random string. The lenght can't be larger than a 64-bit unsigned integer [0 - 18446744073709551615]. Otherwise press [q] to exit the program.
> 10
Select options specified below [any order]:
1) Lower case [a-z]
2) Upper case [A-Z]
3) Digits [0-9]
4) Special chars [@%+\/'!#$^?:,(){}[]~-_.]
q) EXIT PROGRAM
> 41

RANDOM STRING (len=10): r?u(kqr_!\

Would you like to generate a new string? Type [y] for generate a new string and [n] or [q] to exit.
> n
```

## Generator Interface

Interface:
```c
struct Generator {
  // Number of elements the generator can generate
  u64 (*len)(Generator *self);
  // Argument i must be lower than lenght of generator (obtained through size
  // function)
  char *(*get)(Generator *self, u64 i);
  // Argument i must be lower than lenght of generator (obtained through size
  // function)
  u64 (*size_of)(Generator *self, u64 i);
};
```

Example of implementation:
```c
typedef struct {
  Generator generator;
  char start;
  char end;
  char sep;
} RangeGenerator;
```

## License

This project is licensed under the dual MIT/Apache-2.0 license. For more
information, see [LICENSE-APACHE](LICENSE-APACHE) and [LICENSE-MIT](LICENSE-MIT).
