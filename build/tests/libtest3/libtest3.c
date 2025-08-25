/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 1014
 * In the public domain
 *
 * Test the string functions
 * Test 3 of 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int	Errors = 0;
char	v1[64];

int result = EXIT_SUCCESS;

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
result = EXIT_FAILURE;
}

void pr(char *s) {
	printf("%s\n", s);
}


char *xstrchr(char *s, int c) {
	if (c == 0) return NULL;
	return strchr(s, c);
}


void test_str(void) {
	char	*sep;

	pr("strlen");
	if (strlen("\0") != 0) fail("strlen-1");
	if (strlen("0123456789abcdef") != 16) fail("strlen-2");

	pr("strcmp");
  if (strcmp("\0", "\0")) fail("strcmp-1");
  if (strcmp("abcdef", "abcdef")) fail("strcmp-2");
  if (strcmp("abcdef", "abcdefg") != -'g') fail("strcmp-3");
  if (strcmp("abcdefg", "abcdef") != 'g') fail("strcmp-4");
  if (strcmp("abcdef0", "abcdef3") != -3) fail("strcmp-5");

	pr("strcpy");
	strcpy(v1, "0123456789ABCDEF");
	if (strcmp(v1, "0123456789ABCDEF")) fail("strcpy-1");
	strcpy(v1, "ABCDEF");
	if (strcmp(v1, "ABCDEF")) fail("strcpy-2");
	if (v1[7] != '7') fail("strcpy-3");

	pr("strcat");
	strcpy(v1, "abcXXXXX"); v1[3] = 0;
	strcat(v1, "DEF");
	if (strcmp(v1, "abcDEF")) fail("strcat-1");
	if (v1[7] != 'X') fail("strcat-2");

	pr("strncmp");
  if (strncmp("abcdef", "abcdef", 6)) fail("strncmp-1");
	if (strncmp("abcdxx", "abcdyy", 4)) fail("strncmp-2");
	if (strncmp("abcdx0", "abcdy9", 5) != -1) fail("strncmp-3");
	if (strncmp("abcdy0", "abcdx9", 5) != 1) fail("strncmp-4");
	if (strncmp("abcdef", "abcdef", 10)) fail("strncmp-5");
	if (strncmp("abcdefg", "abcdef", 7) != 'g') fail("strncmp-6");
	if (strncmp("abcdef", "abcdefg", 7) != -'g') fail("strncmp-7");
	if (strncmp("abcdefg", "abcdef", 10) != 'g') fail("strncmp-8");
	if (strncmp("abcdef", "abcdefg", 10) != -'g') fail("strncmp-9");

	pr("strncpy");
	strcpy(v1, "0123456789");
	strncpy(v1, "abcdef", 6);
	if (strcmp(v1, "abcdef6789")) fail("strncpy-1");
	strcpy(v1, "0123456789");
	strncpy(v1, "0123", 5);
	if (memcmp(v1, "0123\00056789", 10)) fail("strncpy-2");
	strncpy(v1, "0123", 10);
	if (memcmp(v1, "0123\000\000\000\000\000\000", 10)) fail("strncpy-3");

	pr("strncat");
	strcpy(v1, "012345");
	strncat(v1, "6789", 5);
	if (strcmp(v1, "0123456789")) fail("strncat-1");
	strncat(v1, "abcdef0000", 6);
	if (strcmp(v1, "0123456789abcdef")) fail("strncat-2");

	pr("strspn");
	if (strspn("abcdefg", "abc") != 3) fail("strspn-1");
	if (strspn("abcabcabcdefg", "abc") != 9) fail("strspn-2");
	if (strspn("abcdefg", "") != 0) fail("strspn-3");

	pr("strcspn");
	if (strcspn("abcdefg", "def") != 3) fail("strcspn-1");
	if (strcspn("abcabcabcdefg", "def") != 9) fail("strcspn-2");
	if (strcspn("abcdefg", "") != 7) fail("strcspn-2");
	if (strcspn("abcdefg", "xyz") != 7) fail("strcspn-3");

	pr("strpbrk");
	if (strcmp(strpbrk("abcdef", "def"), "def")) fail("strpbrk-1");
	if (strcmp(strpbrk("abcabcabcdef", "def"), "def")) fail("strpbrk-2");
	if (strpbrk("abcdef", "") != NULL) fail("strpbrk-2");
	if (strpbrk("abcdef", "xyz") != NULL) fail("strpbrk-3");

	pr("strtok");
	sep = "+-*";
	strcpy(v1, "foo++bar---baz*goo");
	if (strcmp(strtok(v1, sep), "foo")) fail("strtok-1");
	if (strcmp(strtok(NULL, sep), "bar")) fail("strtok-2");
	if (strcmp(strtok(NULL, sep), "baz")) fail("strtok-3");
	if (strcmp(strtok(NULL, sep), "goo")) fail("strtok-4");
	if (strtok(NULL, sep) != NULL) fail("strtok-5");
	if (strtok(NULL, sep) != NULL) fail("strtok-6");
}

int main(int argc, char **argv) {
  test_str();
  return result;
}
