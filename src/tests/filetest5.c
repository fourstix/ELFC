/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 1014
 * In the public domain
 *
 * Test the file position functions
 * Test 2 of
 */
#define _STGROM_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define TSTFILE		"ftest5.tmp"

int	Errors = 0;
int result = EXIT_SUCCESS;
char	s1[80], s2[80];

/* string data for format tests*/
char str1[] = "0---|----1----|----2----|----3----|----4----|----5\n";
char str2[] = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
char str3[] = "DDDDDDDDDDDDDDDDDDDDDDDD";
char str4[] = "EEEEEEEEEEEEEEEEEEEEEEEE";
char str5[] = "%%%%%%%%%%%%%%%%%%%%";

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
result = EXIT_FAILURE;
}

void pr(char *s) {
	printf("%s\n", s);
}

void test_fscan(void) {
  int i, j, k;
  char c;
  unsigned int u;
  FILE *f;

  pr("fscanf");
  if ((f = fopen("fscanf.tst", "w")) == NULL) {
    fail("fopen-1");
		return;
	}
  fprintf(f, "%d %x %o %u", -35, 0x0400, 0135, 60000);
  fprintf(f, "%s", "a\t100%  pass\n");
  rewind(f);
  /* read back test data we just wrote*/
  fscanf(f, "%d %x %o %u", &i, &j, &k, &u);
  /* read single character */
  fscanf(f, "%c", &c);
  /* whitespace seperates data string into two strings */
  fscanf(f, "%20s %20s", s1, s2);
  fclose(f);

  if (i != -35) fail("fcanf-1 (int)");
  if (j != 1024) fail("fcanf-2 (hex)");
  if (k != 93) fail("fcanf-3 (octal)");
  if (u != 60000) fail("fcanf-4 (unsigned int)");
  if (c != 'a') fail("fcanf-5 (char)");
  if (strcmp(s1, "100%")) fail("fcanf-6 (%%)");
  if (strcmp(s2, "pass")) fail("fcanf-7 (string)");
}


int main(int argc, char **argv) {
  test_fscan();
  if (!Errors) pr("okay");
  return result;
}
