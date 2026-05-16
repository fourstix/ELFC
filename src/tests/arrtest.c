#include <stdio.h>

int  Errors = 0;
int result = EXIT_SUCCESS;


int a1[2][3] = {1, 2, 3, 4, 5, 6};
char c1[6] = {'a','b', 'c', 'd', 'e', 'f'};
char c2[3][2] = {'g', 'h','i','j','k', 'l'};
int  a3[4][2][3];


void fail(char *name) {
  printf("%s failed\n", name);
  Errors++;
  result = EXIT_FAILURE;
}

int testrow(int x[][3], int n, int offset) {
  int m;
  int i = 0;
  int result = 0;

  for (m=0; m<3; m++) {
    i = 3 * n + m + offset;
    printf("test x[%d][%d] = %d\n", n, m, i);
    //printf("x[%d][%d] = %d\n", n, m, x[n][m]);
    if (x[n][m] != i) {
      printf("Error: expected %d , found %d\n", i, x[n][m]);
      fail("testrow");
      result = 1;
      /* exit test after first error */
      break;
    }
  }
  printf("\n");
  return result;
}


int main() {
  int i, j, k;
  int *p, *expected;
  char c;
  int  v;

  //needs cast to prevent pointers warning
  expected = (int *) a1;

  printf("Test array pointer decay addresss a1 = %p\n", expected);


  //needs cast to prevent pointers warning
  p = (int *) &a1;
  printf("test &a1 %p == expected %p\n", p, expected);
  if (p != expected)
     fail("pointer &a1");

  p = a1[0];
  printf("test a1[0] %p == expected %p\n", p, expected);
  if (p != expected)
    fail("pointer a1[0]");

  //needs cast to prevent pointers warning
  p = (int *) &a1[0];
  printf("test &a1[0] %p == expected %p\n", p, expected);
  if (p != expected)
    fail("pointer &a1[0]");

  p = &a1[0][0];
  printf("test &a1[0][0] %p == expected %p\n", p, expected);
  if (p != expected)
    fail("pointer &a1[0][0]");

  printf("Test function with array parameter\n");
  for (i = 0; i < 2; i++) {
    if (testrow(a1, i, 1))
      fail("passing a1[][] as parameter");
      break;
  }
  printf("\n");


  printf("Change element in array c1[] and test\n");
  //grw - change element in array
  c1[4] = 'x';

  for (i = 0; i < 2; i++) {
    printf("testing c1[%d] = \'%c\'\n", i, c1[i]);
    if (i == 4) {
      /* verified element was changed */
      if (c1[i] != 'x') {
        fail("set char in c1[]");
        break;
      }
    } else {
      if (c1[i] != 'a' + i) {
        /* verified other elements are unchanged */
        fail("other char in c1[]");
        break;
      }
    }
  }


  printf("Change element in array c2[][] and test\n");
  c2[2][1] = 'y';


  for(i = 0; i < 3; i++)
    for(j = 0; j < 2; j++) {
      c = c2[i][j];
      printf("testing c2[%d][%d] = \'%c\'\n", i, j, c);

      if (2 == i && 1 == j) {
        /* verified element was changed */
        if (c != 'y') {
          fail("set char in array c2[][]");
          break;
        }
      } else {
        /* verified other elements are unchanged */
        if (c != ('g' + i*2 +j)) {
          fail("other char in array c2[][]");
          break;
        }
      }
    }
    /* fill 3 dimiensional array */

    for(i = 0; i < 4; i++)
      for(j = 0; j < 2; j++)
        for(k = 0; k < 3; k++) {
            a3[i][j][k] = i*6 + j*3 + k + 1;
            printf("set a3[%d][%d][%d] = %d\n", i, j, k, a3[i][j][k]);
        }

    printf("Test three dimensional array a3\n");

    for(i = 0; i < 4; i++)
      for(j = 0; j < 2; j++)
        for(k = 0; k < 3; k++) {
            v = i*6 + j*3 + k + 1;
            printf("test a3[%d][%d][%d] = %d\n", i, j, k, v);
            if (a3[i][j][k] != v) {
              fail("set char array a3[][][]");
              break;
            }
        }
    printf("Test function passing a3[] as x[][] parameter\n");

    for (i = 0; i < 4; i++)
      for (j = 0; j < 2; j++) {
        printf("Test function with array at a3[%d]\n", i);
        if (testrow(a3[i], j, i*6+1)) {
          fail("passing array a3[i] as parameter x[][]");
          break;
        }
      }
      printf("\n");

  if (!Errors)
    printf("All tests passed.\n");

  return result;
}
