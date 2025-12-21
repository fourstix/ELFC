#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* gloabal variables used in examples */
int a = 3;
int b = 9;
char str[] = "Testing!";

/*
 * This function uses a count value for passing
 * a number of variable arguments of the same type
 */
void testcnt(int count, ...) {
  va_list ap;

  int t, i;

  va_start(ap, count);

  //printf("&list = %p, arglist = %p\n", &count, ap);

  for(i = 0; i < count; i++) {
    t = va_arg(ap, int);

    /* print each integer passed to function */
    printf("t = %d\n", t);
  }
  va_end(ap);
}

/*
 * This function uses a format string for passing
 * variable arguments of different types
 */
void testfmt(char *myfmt, ...) {
  int i;
  char c;
  char *s;
  int  *p;
  void *x;
  char kind;


  va_list ap;
  va_start(ap, myfmt);

  while(*myfmt) {
    kind = *myfmt++;

    switch (kind) {
      case 'c':
        c = va_arg(ap, char);
        printf("char = %c\n", c);
      break;
      case 'i':
        i = va_arg(ap, int);
        printf("int = %d\n", i);
      break;
      case 'p':
        p = va_arg(ap, int *);
        printf("Pointer to int %d\n", *p);
      break;
      case 's':
        s = va_arg(ap, char *);
        printf("String %s\n", s);
      break;
      default:
        /* treat any other character as unknown pointer */
        x = va_arg(ap, void *);
        printf("Unknown pointer %p\n", x);
      break;
    }
  }

}

int main(){
  char c1 = 'm';
  int  n  = 100;
  int  *pi;

  /* set integer pointer to global value */
  pi = &b;

  /* using a count for passing variable arguments */
  testcnt(3, 1, 2, a);

  /* using a format string for passing variable arguments */
  testfmt("icpsq", n, c1, pi, str, &a);
}
