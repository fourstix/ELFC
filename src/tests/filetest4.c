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

void test_sio4(void) {
	FILE	*t, *f;
	int	err, lno;
  int	i;

	err = lno = 0;
  
  
  pr("fprintf");
  
  if ((f = fopen("fprintf.out", "w")) == NULL) {
    fail("fopen-1");
		return;
	}
  printf("Writing test file....\n");
	fputs(str1, f);
	for (i=0; i<50; i++) putc('A', f);
  putc('\n',f);
	for (i=0; i<50; i++) fputc('B', f);
  fputc('\n',f);
	fprintf(f, "%s", str2);
	fprintf(f,"|%48s|\n", str3);
	fprintf(f,"|%-48s|\n", str4);
	for (i=0; i<5; i++)
		fprintf(f, "%c%c%c%c%c%c%c%c%c%c",
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0' );
  fputs("\n", f);  
	fprintf(f, "%50d\n", -12345);
	fprintf(f, "%-49d|\n", -12345);
	fprintf(f, "%050d\n", 12345);
	fprintf(f, "0x%x %15s%d%16s 0%o\n", 0x7BCD, "", 0x7BCD, "", 0x7BCD);
	for (i=0; i<5; i++) fprintf(f, str5);
	fputs("\n", f);
	fputs(str1, f);

  fclose(f);
  
	if ((f = fopen("stdio.ok", "r")) == NULL) {
		fputs("missing file: stdio.ok\n", stdout);
		Errors++;
	} else if ((t = fopen("fprintf.out", "r")) == NULL) {
			fputs("could not open test file: fprintf.out\n",
				stdout);
      Errors++;
	}	else {
    puts("comparing lines");
		fgets(s1, 80, t);
		for (;;) {
			++lno;
			fgets(s2, 80, f);
			if (feof(t)) break;
			if (feof(f)) break;
			if (memcmp(s1, s2, 50)) {
        ++err;
        printf("%2d Error\n", lno);
      } else {
        printf("%2d: %s", lno, s1);
      }     
			fgets(s1, 80, t);
		}
    /* stdio.ok may have padding characters from xmodem */
    /* so make sure fprintf.out is done */
    if (!feof(t) || !feof(f)) {
			puts("files have different sizes");
			++err;
		}
		fclose(t);
	}
		fclose(f);
    //if (!err) unlink(TMPFILE);
    if (err) fail("fprintf");
}

void test_printf(void) {
	int	i;
  pr("printf");
  
	puts(str1);
	for (i=0; i<50; i++) putc('A', stdout);
	puts("");
	for (i=0; i<50; i++) putchar('B');
	puts("");
	printf(str2);
	printf("|%48s|\n", str3);
	printf("|%-48s|\n", str4);
	for (i=0; i<5; i++)
		printf("%c%c%c%c%c%c%c%c%c%c",
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0' );
	puts("");
	printf("%50d\n", -12345);
	printf("%-49d|\n", -12345);
	printf("%050d\n", 12345);
	printf("0x%x %15s%d%16s 0%o\n", 0x7BCD, "", 0x7BCD, "", 0x7BCD);
	for (i=0; i<5; i++) printf(str5);
	puts("");
	puts(str1);
}

int main(int argc, char **argv) {
  test_printf();
  test_sio4();
  if (!Errors) pr("okay");
  return result;
}
