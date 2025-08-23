/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 1014
 * In the public domain
 *
 * Test the stdout and math functions
 * Test 4 of 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX		10

int	rns[MAX];
char	buf[64];
int	Errors = 0;
int result = EXIT_SUCCESS;

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
result = EXIT_FAILURE;
}

void pr(char *s) {
	printf("%s\n", s);
}

void test_math(void) {
	#define unsigned	char *

	int	i, j, k;
	int	rns[MAX];
  
  i = 12345;

	pr("atoi");
	if (i != atoi("   12345")) fail("atoi-1");
	if (i != atoi("\t+12345")) fail("atoi-2");
	i = -i;
	if (i != atoi("-12345")) fail("atoi-3");
	if (i != atoi("  -12345")) fail("atoi-4");
	if (i != atoi("\t-12345")) fail("atoi-5");

	pr("abs");
	if (abs(0) != 0) fail("abs-1");
	if (abs(123) != 123) fail("abs-2");
	if (abs(-456) != 456) fail("abs-3");
	if (abs(INT_MIN) != INT_MAX) fail("abs-4"); /* man page says so */


 	pr("rand");  
  //grw - not sure if this is a valid test,since  pseudo-random numbers may repeat
  //grw - although 10 out of 65,000 is fairly low probability, it could happen...
	for (i=0; i<MAX; i++) {
		k = rand();
		for (j=0; j<i; j++)
			if (rns[j] == k) {
				fail("rand-1");
				break;
			}
		rns[i] = k;
    //grw - is unsigned even supported yet???
		if ((unsigned) k > (unsigned) RAND_MAX) fail("rand-2");
	}
  
  //grw - print the numbers to validate randomness
  for (i=0; i<MAX; i++) {
    if ((i % 5) == 0)
      printf("\n% 5d", rns[i]);
    else 
      printf(", % 5d", rns[i]);
  }
  puts("");  
}
void spfn_test(char *id, char *fmt, int v, char *res) {
  printf("sprintf test %s\n", id);
	sprintf(buf, fmt, v);
	if (strcmp(buf, res)) {
    printf("buf = %s (expected = %s)\n", buf, res);
		strcpy(buf, "sprintf(");
		strcat(buf, fmt);
		strcat(buf, ")-");
		strcat(buf, id);
		fail(buf);
	}
}

void spfs_test(char *id, char *fmt, char *v, char *res) {  
  printf("sprintf test %s\n", id);
	sprintf(buf, fmt, v);
	if (strcmp(buf, res)) {
    printf("buf = %s (expected = %s)\n", buf, res);
		strcpy(buf, "sprintf(");
		strcat(buf, fmt);
		strcat(buf, ")-");
		strcat(buf, id);
		fail(buf);
	}
}

void test_sprintf(void) {
	pr("sprintf");
  
	spfn_test("1", "%d", 12345, "12345");
	spfn_test("2", "%d", -12345, "-12345");
	spfn_test("3", "%+d", 12345, "+12345");
	spfn_test("4", "%+d", -12345, "-12345");
	spfn_test("5", "%10d", 12345, "     12345");
	spfn_test("6", "%10d", -12345, "    -12345");
	spfn_test("7", "%+10d", 12345, "    +12345");
	spfn_test("8", "%+10d", -12345, "    -12345");
	spfn_test("9", "%-10d", 12345, "12345     ");
	spfn_test("10", "%-10d", -12345, "-12345    ");
	spfn_test("11", "%-+10d", 12345, "+12345    ");
	spfn_test("12", "%-+10d", -12345, "-12345    ");
	spfn_test("13", "%+-10d", 12345, "+12345    ");
	spfn_test("14", "%+-10d", -12345, "-12345    ");
	spfn_test("15", "% 10d", 12345, "     12345");
	spfn_test("16", "% 10d", -12345, "    -12345");
	spfn_test("17", "%010d", 12345, "0000012345");
	spfn_test("18", "%010d", -12345, "-000012345");
	spfn_test("19", "%x", 0x2def, "2def");
	spfn_test("20", "%X", 0x2def, "2DEF");
	spfn_test("21", "%#x", 0x2def, "0x2def");
	spfn_test("22", "%#X", 0x2def, "0X2DEF");
  //grw - %x and %o are printed as unsigned values
	spfn_test("23", "%x", -0x2def, "d211");
	spfn_test("24", "%#x", -0x2def, "0xd211");
	spfn_test("25", "%+#X", 0x2def, "0X2DEF");
	spfn_test("26", "%#+X", 0x2def, "0X2DEF");
	spfn_test("27", "%#+X", 0x2def, "0X2DEF");
	spfn_test("28", "%10X", 0x2def, "      2DEF");
	spfn_test("29", "%010X", 0x2def, "0000002DEF");
	spfn_test("30", "%-10X", 0x2def, "2DEF      ");
	spfn_test("31", "%#10X", 0x2def, "    0X2DEF");
	spfn_test("32", "%#010X", 0x2def, "0X00002DEF");
	spfn_test("33", "%#-10X", 0x2def, "0X2DEF    ");
	spfn_test("34", "%10X", -0x2def, "      D211");
	spfn_test("35", "%010X", -0x2def, "000000D211");
	spfn_test("36", "%-10X", -0x2def, "D211      ");
	spfn_test("37", "%#10X", -0x2def, "    0XD211");
	spfn_test("38", "%#010X", -0x2def, "0X0000D211");
	spfn_test("39", "%#-10X", -0x2def, "0XD211    ");
	spfn_test("40", "%o", 0417, "417");
	spfn_test("41", "%o", -0417, "177361");
	spfn_test("42", "%#o", 0417, "0417");
	spfn_test("43", "%#o", -0417, "0177361");
	spfn_test("44", "%#+o", 0417, "0417");
	spfn_test("45", "%+#o", 0417, "0417");
	spfn_test("46", "%#10o", 0417, "      0417");
	spfn_test("47", "%#-10o", 0417, "0417      ");
	spfn_test("48", "%#010o", 0417, "0000000417");
	spfn_test("49", "%#10o", -0417, "   0177361");
	spfn_test("50", "%#-10o", -0417, "0177361   ");
	spfn_test("51", "%#010o", -0417, "0000177361");
	spfn_test("52", "%d", 0, "0");
	spfn_test("53", "%o", 0, "0");
	spfn_test("54", "%x", 0, "0");
	spfn_test("55", "%c", 'a', "a");
	spfn_test("56", "%10c", 'a', "         a");
	spfn_test("57", "%-10c", 'a', "a         ");
	spfs_test("58", "%s", "foo", "foo");
	spfs_test("59", "%10s", "foo", "       foo");
	spfs_test("60", "%-10s", "foo", "foo       ");
	spfn_test("61", "%1d", 12345, "12345");
	spfn_test("62", "%-1d", 12345, "12345");
	spfn_test("63", "%#1x", 0xabc, "0xabc");
	spfn_test("64", "%#-1x", -0xabc, "0xf544");
	spfs_test("65", "%1s", "foo", "foo");
	spfs_test("66", "%-1s", "foo", "foo");
}



int main(int argc, char **argv) {
  test_math();
  test_sprintf();
  return result;
}
