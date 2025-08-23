/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 1014
 * In the public domain
 *
 * Test the open, close and temp file functions
 * Test 1 of 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define TSTFILE		"ftest.tmp"
#define TSTFILE2	"ftest2.tmp"
#define TSTFILE3	"ftest3.tmp"


char	buf[128];
char	tn1[L_tmpnam], tn2[L_tmpnam];
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


void test_file(void) {
	FILE	*f;

  pr("remove");
  f = fopen(TSTFILE, "w");
  if (f == NULL) { 
    fail("fopen-1");
    perror("remove");
  }
  fclose(f);
	if (remove(TSTFILE) < 0) fail("remove-1");
	if (remove(TSTFILE) >= 0) fail("remove-2");

	pr("rename");
	if (rename(TSTFILE, TSTFILE2) >= 0) fail("rename-1");
  f = fopen(TSTFILE, "w");
  if (f == NULL) {
    fail("fopen-2");
    perror("rename");
  }
	fclose(f);
	if (rename(TSTFILE, TSTFILE2) < 0) fail("rename-2");
	if (rename(TSTFILE, TSTFILE2) >= 0) fail("rename-3");
	remove(TSTFILE2);

	pr("tmpfile");
	if ((f = tmpfile()) == NULL) {
    fail("tmpfile-1");
    perror("tmpfile");
  } else {
  	memset(buf, 0xa5, 128);
  	if (fwrite(buf, 1, 128, f) != 128) fail("tmpfile-2");
  	rewind(f);
  	if (fread(buf, 1, 128, f) != 128) fail("tmpfile-3");
    //grw save file name for testing later
    sprintf(tn1, TMP_FMT, f->tmpid);
    //grw - fclose should delete temp file without error
    if (fclose(f) == -1) fail("tmpfile-4");
    //grw - verify temp file is gone 
    if (fopen(tn1, "r") != NULL) fail("tmpfile-5");
  }

	pr("tmpnam");
	if (tmpnam(tn1) == NULL) fail("tmpnam-1");
  f = fopen(tn1, "w");
  if (f == NULL) {
    fail("fopen-3");
    perror("tmpnam");
  }
	fclose(f);
	if (tmpnam(tn2) == NULL) fail("tmpnam-2");
	if (!strcmp(tn1, tn2)) fail("tmpnam-3");
	remove(tn1);
}


void test_stdio(void) {
	FILE	*f;
	int	i, j, ok;
	int	fd;

	pr("fopen");
	if ((f = fopen(TSTFILE3, "w+")) == NULL) {
		perror("stdio-1");
    fail("fopen-1");
	}
	else {
    pr("feof");
		fgetc(f);
    if (!feof(f)) fail("feof-1");
		fclose(f);
	}
	if ((f = fopen(TSTFILE3, "w")) == NULL) {
    perror("stdio-2");
		fail("fopen-2");
	}
	else {
		pr("fputs");
		if (fputs("1111111111\n", f) == EOF) fail("fputs-1");
		if (fputs("2222222222\n", f) == EOF) fail("fputs-2");
		if (fputs("3333333333\n", f) == EOF) fail("fputs-3");
		if (fputs("4444444444\n", f) == EOF) fail("fputs-4");
		if (fputs("5555555555\n", f) == EOF) fail("fputs-5");
		fd = fileno(f);
		pr("fclose");
		if (fclose(f)) fail("fclose-1");
		if (close(fd) == 0) fail("fclose-2");

		if ((f = fopen(TSTFILE3, "r")) == NULL) {
      perror("stdio-3");
      fail("fopen-3");
		}
		else {
			pr("fgets");
			fgets(buf, 80, f);
			i = '1';
			ok = 1;
      while (!feof(f) && ok) {
				for (j=0; j<10; j++) {
					if (buf[j] != i) {
  					fail("fgets-1");
            ok = 0; //grw - end while loop after first error
						break;
					}
				}
				i++;
				fgets(buf, 80, f);
			}
			fd = fileno(f);
			if (fclose(f)) fail("fclose-3");
			if (close(fd) == 0) fail("fclose-4");
		}
	}
	unlink(TSTFILE3);
}


int main(int argc, char **argv) {
  test_file();
  test_stdio();
  return result;
}
