/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 1014
 * In the public domain
 *
 * Test the character type functions
 * Test 2 of 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int	Errors = 0;
char	alpha[64], alnum[64], xnum[64];

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

void test_chrfn(void) {
	char	*c1, *p1;
	int	c;
	char	*num, *low, *upc, *wsp, *pun;

	pr("strchr");
	c1 = "...............X1..............X2";
	p1 = strchr(c1, 'X');
	if (!p1 || *p1 != 'X' || p1[1] != '1') fail("strchr-1");
	if (strchr(c1, 'Z')) fail("strchr-2");

	pr("strrchr");
	p1 = strrchr(c1, 'X');
	if (!p1 || *p1 != 'X' || p1[1] != '2') fail("strrchr-1");
	if (strrchr(c1, 'Z')) fail("strchr-2");

	pr("is*");
	num = "0123456789";
	low = "abcdefghijklmnopqrstuvwxyz";
	upc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	wsp = "\t\v\f\n\r ";
	pun = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

  strcpy(alpha, low);
	strcat(alpha, upc);
	strcpy(alnum, alpha);
	strcat(alnum, num);
	strcpy(xnum, num);
	strcat(xnum, "abcdefABCDEF");
	for (c=0; c<128; c++) {
    printf("isChar Tests: char(%d)\n", c);

		if (isalnum(c) && !strchr(alnum, c)) fail("isalnum-1");
		if (isalpha(c) && !strchr(alpha, c)) fail("isalpha-1");
		if (iscntrl(c) && c > 31 && c < 127) fail("iscrntl-1");
		if (isdigit(c) && !strchr(num, c)) fail("isdigit-1");
		if (isgraph(c) && c < 33 && c > 126) fail("isgraph-1");
		if (islower(c) && !strchr(low, c)) fail("islower-1");
		if (isprint(c) && (c < 32 || c > 126)) fail("isprint-1");
		if (ispunct(c) && !strchr(pun, c)) fail("ispunct-1");
		if (isspace(c) && !strchr(wsp, c)) fail("isspace-1");
		if (isupper(c) && !strchr(upc, c)) fail("isupper-1");
		if (isxdigit(c) && !strchr(xnum, c)) fail("isxdigit-1");
		if (!isalnum(c) && xstrchr(alnum, c)) fail("isalnum-2");
		if (!isalpha(c) && xstrchr(alpha, c)) fail("isalpha-2");
		if (!iscntrl(c) && (c < 32 || c > 126)) fail("iscrntl-2");
		if (!isdigit(c) && xstrchr(num, c)) fail("isdigit-2");
		if (!isgraph(c) && c > 32 && c < 127) fail("isgraph-2");
		if (!islower(c) && xstrchr(low, c)) fail("islower-2");
		if (!isprint(c) && c > 31 && c < 127) fail("isprint-2");
		if (!ispunct(c) && xstrchr(pun, c)) fail("ispunct-2");
		if (!isspace(c) && xstrchr(wsp, c)) fail("isspace-2");
		if (!isupper(c) && xstrchr(upc, c)) fail("isupper-2");
		if (!isxdigit(c) && xstrchr(xnum, c)) fail("isxdigit-2");
		if (isupper(c) && !islower(tolower(c))) fail("tolower-1");
		if (islower(c) && tolower(toupper(c)) != c) fail("tolower-2");
		if (islower(c) && !isupper(toupper(c))) fail("toupper-1");
		if (isupper(c) && toupper(tolower(c)) != c) fail("toupper-2");
	}
}


int main(int argc, char **argv) {
  test_chrfn();
  return result;
}
