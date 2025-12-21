/* Uncomment this line to turn off assert */
//#define NDEBUG 1

#include <stdio.h>
#include <assert.h>

/* multiline macro definition with parameters */
#define TEST( P1, P2, P3)  \
    P1+P2*P3

/* plain macro definition */
#define LIMIT  5

/* macro using paste operator */
#define COMMAND(Name)   Name  ##  _command

/* line below with macro will expand into int test_command(void); */
int COMMAND(test)(void);

int i = 0;

/* line-splicing */
char tst[] = " This is \
a valid string";

int main() {
  /* end of line continuation */
  int j = 1, \
    k = 2;

  j = LIMIT*2;

  i = TEST((13+2),2,6);

  /* nested macros */
  k = min(LIMIT, min(i, j));

  printf("i = %d, j = %d, k = %d\n", i, j, k);

  /* assertion macro (true condition) */
  assert( k < j );

  /* assertion macro (false condition) */
  /* uncomment to see error message */
  //assert( k < 5 );

  /* show line splicing in string is okay */
  printf("Test string: %s\n", tst);

  /* make sure pasted name has expectd value */
  k = test_command();

  return k;
}

/*
 * Text line below with macro will expand into
 * int test_command(void) {
 */
int COMMAND(test)(void) {
  return LIMIT*3;
}
