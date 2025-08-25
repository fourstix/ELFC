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

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
result = EXIT_FAILURE;
}

void pr(char *s) {
	printf("%s\n", s);
}


void test_sio3(void) {
	FILE	*f;
	static char	buf[256];
	int	i, j;

 
	if ((f = fopen(TSTFILE, "w+")) == NULL) {
		fail("fopen-1");
		return;
	}
	pr("fwrite");
	for (i=31; i<=131; i += 31) {
		memset(buf, i, i);
		if (fwrite(buf, 1, i, f) != i)
			fail("fwrite-1");
	}
	rewind(f);
	pr("fread");
	for (i=31; i<=131; i += 31) {
		memset(buf, i, i);
		if (fread(buf, 1, i, f) != i)
			fail("fread-1");
		for (j=0; j<i; j++) {
			if (buf[j] != i % 256)
				break;
		}
		if (j < i) {
			fail("fread-2");
			break;
		}
	}

  pr("fclose");
	if (fclose(f)) fail("fclose-1");
  
  pr("fopen");
  if ((f = fopen(TSTFILE, "w+")) == NULL) {
		fail("fopen-2");
		return;
	}
  
	for (i=0; i<256; i++)
		buf[i] = '5';
    
  pr("fwrite");  
	for (i=0; i<16; i++) {
		if (fwrite(buf, 1, 256, f) != 256) {
			fail("fwrite-2");
			break;
		}
	}
  pr("rewind");
	rewind(f);
  pr("fread");
	for (i=0; i<16; i++) {
		if (fread(buf, 1, 256, f) != 256) {
			fail("fread-3");
			break;
		}
	}
  pr("fgetc(eof)");
	if (fgetc(f) != EOF) fail("feof");

	clearerr(f);
  pr("fclose");
  if (fclose(f)) fail("fclose-2");
  
  pr("fopen");
  if ((f = fopen(TSTFILE, "r")) == NULL) {
		fail("fopen-3");
		return;
	}
  
	pr("ftell");
  if (ftell(f) != 0) fail("ftell-1");

  pr("fseek");
  if (fseek(f, 0, SEEK_END) != 0) fail("fseek-1");  
	if (ftell(f) != 4096) fail("ftell-2");
  
  pr("fseek");
	if (fseek(f, 2025, SEEK_SET) != 0) fail("fseek-2");
	if (ftell(f) != 2025) fail("fseek-3");

  pr("fseek");  
	if (fseek(f, 475, SEEK_CUR) != 0) fail("fseek-4");
	if (ftell(f) != 2500) fail("fseek-5");

  pr("fclose");
  fclose(f);
	unlink(TSTFILE);
}


int main(int argc, char **argv) {
  test_sio3();
  return result;
}
