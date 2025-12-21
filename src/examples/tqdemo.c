#include <assert.h>

/* auto and register declarations are invalid in global scope */
/* auto int bad1; */
/* register int bad2; */



/* both const & volatile supported inside a user defined type */
typedef const volatile int ktype;

/* const array must be initialized */
const int a1[2] = {6,7};

volatile int a2[2]; /* allowed, all elements in array are volatile */

/* const array must be initialized */
const int a3[] = {1,2,3};

/* not allowed, arrays must be initialized */
/* const int a4[5]; */

struct s_struct {
  int a;
  volatile int b;
  const int c;
};

/* global constant variable */
const int g1 = 0;

/* allowed, k1 is a const volatile global variable */
ktype k1 = 2;

/* const keyword supported before user defined types */
const ktype k2 = 2;

/* volatile keyword supported before user defined types */
volatile ktype k3 = 3; /*  warning: ignored */

/* volatile and const keywords ignored before struct/union */
const struct s_struct s1; /*  warning: ignored */

volatile struct s_struct s2; /*  warning: ignored */

/* allowed */
/*
 * Per the C89 spec, const is ignored for function return values, since
 * a function can never be an lvalue.  Mo warning is generated when
 * const is ignored in this case.  A const function parameter is
 * considered initialized before the call and can never be modified
 * with the function.
 */
const int sumstr(const char *s) {
  int i = 0;
  /* not allowed */
  /* cannot modify a const parameter */
  /* *s = 'c'; */

  while(*s) {
    i += *s++;
  }
  return i;
}

/* allowed */
/*
 * Per the C89 spec, volatile is ignored for function return values and
 * function parameters, as they are considered to be copies of values
 * of already read variables. No warnings are generated when
 * when volatile is ignored in these cases.
 */
volatile int test(volatile int a) {
  /* optimized, since volatile is ignored on parameter per C89 spec */
  return a*(4+1);
}


int main() {
  /* local volatile and const variables */
  volatile const int x = 5;  /* volatile constant is same as const volatile */
  const int *p;     /* pointer to constant variable */
  volatile v = 1;  /* volatile variable */

  /* const keyword is not allowed with register storage class */
  /* register const r; */

  /* const keyword not supported before user defined types */
  /* const ktype k4 = 4; */

  /* volatile keyword ignored before user defined types */
  volatile ktype k5 = 5; /*  warning: ignored */

  int y  = 3;  /* (plain) int */
  int *q;      /* (plain) pointer */

  /* local const arrays must be static and initialized */
  static const int la1[] = {2,4,6,8};
  static const int la2[3] = {1, 4, 9};

  /* not allowed */
  /* const int la3[]; */

  /* not allowed */
  /* const int la4[2]; */

  /* not allowed */
  /* const int la5[] = {0,0}; */

  /* constant pointers to (varying) variables is not supported by ElfC */
  /* int * const p1; */

  /* allowed, const struct member initialized */
  s1.c = 3;

  /* not allowed, cannot assign value to initialized const member */
  /* s1.c = 6; */

  /* not allowed, cannot assign value to initialized array element */
  /* a1[0] = 1; */

  /* volatile array elements, no optimizations are done */
  a2[0] = 5+1;
  assert(a2[0]== 6);
  a2[1] = a2[0] * 2 * 4;
  assert(a2[1]== 48);

  /* cannot update const variables after initialization */

  /* not allowed */
  /*  k1 = 6; */

  /* not allowed */
  /*  k2 = 7; */

  /* not allowed */
  /*  g1 = 3; */

  /* not allowed */
  /* x = 4; */

  p = &x; /* allowed, assigning pointer to constant */
  assert(*p == 5);

  /* not allowed */
  /* *p = 6; */

  p = &y; /* allowed, assigning pointer value to pointer to constant */
  assert(*p == 3);

  /* not allowed, update through pointer to constant */
  /* *p = 8; */

  q = p; /* allowed, assigning pointer */
  assert(*q == 3);

  /* not allowed, update through pointer to constant */
  /* *p = 9; */

  /* allowed, update through (plain) pointer */
  *q = 9;
  assert(y == 9);

  q = &g1; /* allowed, but plain pointers over-ride const behavior */
  assert(*q == 0);

  p = q;  /* allowed, assigning pointer to constant  */

  /* not allowed */
  /* *p = 9; */

  *q = 9; /* allowed, plain pointer over-rides const behavior */
  assert(g1 == 9);

  /* allowed */
  y = sumstr("hello");
  assert(y == 532);

  /* allowed */
  y = test(x);
  assert(y == 25);

  /* allowed, but no optimizations are done */
  v = x*2*3;
  assert(v == 30);

  /* allowed, but no optimizations are done */
  y = v + 2 + 1;
  assert(y == 33);

  return 1;
}
