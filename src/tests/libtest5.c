#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* test posix string functions */

int	Errors = 0;
int result = EXIT_SUCCESS;

char	v1[32], *pstr;
int   val;
char  *sep;

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
  result = EXIT_FAILURE;
}


void pr(char *name) {
  printf("%s\n", name);
}

int main() {


  pr("strnlen");
  if (strnlen("\0", 12) != 0) fail("strnlen-1");
  if (strnlen("0123456789", 10) != 10) fail("strnlen-2");
  if (strnlen("0123456789", 12) != 10) fail("strnlen-2");
  if (strnlen("0123456789abcdef", 12) != 12) fail("strnlen-2");

  pr("strlcpy");
  strcpy(v1, "0123456789");
  val = strlcpy(v1, "abcde", 6);
  //printf("s = %s, val =%d\n", v1, val);
  if (strcmp(v1, "abcde") || val != 5) fail("strlcpy-1");
  strcpy(v1, "0123456789");
  val = strlcpy(v1, "abcdef", 6);
  //printf("s = %s, val =%d\n", v1, val);
  if (strcmp(v1, "abcde") || val != 6) fail("strlcpy-2");
  strcpy(v1, "0123456789");
  val = strlcpy(v1, "abcdefgh", 8);
  //printf("s = %s, val =%d\n", v1, val);
  if (strcmp(v1, "abcdefg") || val != 8) fail("strlcpy-3");

  pr("strlcat");
  strcpy(v1, "012345");
  val = strlcat(v1, "6789", 6);
  //printf("s = %s, val =%d\n", v1, val);
  if (strcmp(v1, "012345") || val != 10) fail("strlcat-1");
  val = strlcat(v1, "6789", 11);
  //printf("s = %s, val =%d\n", v1, val);
  if (strcmp(v1, "0123456789") || val != 10) fail("strlcat-2");
  val = strlcat(v1, "abcdef0000", 17);
  //printf("s = %s, val =%d\n", v1, val);
  if (strcmp(v1, "0123456789abcdef") || val != 20) fail("strlcat-3");

  pr("strdup");
  pstr = strdup("0123456789");
	if (!pstr || strcmp(pstr, "0123456789")) fail("strdup-1");
  if (pstr)
    free(pstr);


  pr("strndup");
  pstr = strndup("0123456789", 6);
  if (!pstr || strcmp(pstr, "012345")) fail("strndup-1");
  if (pstr)
    free(pstr);

	pr("strcasecmp");
	if (strcasecmp("\0", "\0")) fail("strcmp-1");
	if (strcasecmp("abcdef", "abcdef")) fail("strcasecmp-2");
	if (strcasecmp("aBcDeF", "AbCdEf")) fail("strcasecmp-3");
	if (strcasecmp("aBcDeFg", "AbCdEf") != 'g') fail("strcasecmp-4");
	if (strcasecmp("abcdef0", "abcdef3") != -3) fail("strcasecmp-5");

	pr("strncasecmp");
	if (strncasecmp("abcdef", "abcdef", 6)) fail("strncasecmp-1");
	if (strncasecmp("abcdef", "ABCDEF", 6)) fail("strncasecmp-2");
	if (strncasecmp("AbCdEf", "aBcDeF", 6)) fail("strncasecmp-3");
	if (strncasecmp("ABcdxx", "abcdyy", 4)) fail("strncasecmp-4");
	if (strncasecmp("abcdy0", "abcdx9", 5) != 1) fail("strncasecmp-5");
	if (strncasecmp("ABcdx0", "abcdy9", 5) != -1) fail("strncasecmp-6");
	if (strncasecmp("abcdef", "abcdef", 10)) fail("strncasecmp-7");
	if (strncasecmp("AbCdEf", "aBcDeF", 10)) fail("strncasecmp-8");
	if (strncasecmp("AbCdEfg", "aBcDeF", 7) != 'g') fail("strncmp-9");
	if (strncasecmp("AbCdEf", "aBcDeFg", 7) != -'g') fail("strncmp-10");
	if (strncasecmp("AbCdEfg", "aBcDeF", 10) != 'g') fail("strncmp-11");
	if (strncasecmp("AbCdEf", "aBcDeFg", 10) != -'g') fail("strncmp-12");

	pr("strrev");
	strcpy(v1, "abcdef");
	if (strcmp(strrev(v1), "fedcba")) fail ("strrev-1");

	pr("strlwr");
	strcpy(v1,"AbCdEf");
	if (strcmp(strlwr(v1), "abcdef")) fail ("strlwr-1");

	pr("strupr");
	strcpy(v1,"AbCdEf");
	if (strcmp(strupr(v1), "ABCDEF")) fail ("strupr-1");


	pr("strsep");
	sep = "+-*";
	pstr = "foo+bar-baz*goo";

	if (strcmp(strsep(&pstr, sep), "foo")) fail("strsep-1");
	if (strcmp(strsep(&pstr, sep), "bar")) fail("strsep-2");
	if (strcmp(strsep(&pstr, sep), "baz")) fail("strsep-3");
	if (strcmp(strsep(&pstr, sep), "goo")) fail("strsep-4");
	if (strsep(&pstr, sep) != NULL) fail("strsep-5");
	if (strsep(NULL, sep) != NULL) fail("strsep-6");

	pr("strim");
	strcpy(v1, "  Oh, Hello!  ");
	if(strcmp(strim(v1), "Oh, Hello!")) fail("strim-1");

	pr("strnstr");
  strcpy(v1, "abcdefgh");
  if (strncmp(strnstr(v1, "def", 6), "def", 3)) fail("strnstr-1");
	if (strnstr(v1, "def", 5) != NULL) fail("strnstr-2");
  if (strnstr(v1, "ghi", 8) != NULL) fail("strnstr-3");

	pr("strcasestr");
  strcpy(v1, "aBcDeFgH");
  if (strncasecmp(strcasestr(v1, "dEf"), "def", 3)) fail("strcasestr-1");
  if (strstr(v1, "ghi") != NULL) fail("strcasestr-2");

  if (!Errors)
    printf("All tests passed.\n");

  return result;
}
