/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 1014
 * In the public domain
 *
 * Test the file position functions
 * Test 2 of 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define TSTFILE4		"ftest4.tmp"

int Errors = 0;
int result = EXIT_SUCCESS;
pos_t filpos;


void fail(char *name) {
  printf("%s failed\n", name);
  Errors++;
  result = EXIT_FAILURE;
}

void pr(char *s) {
  printf("%s\n", s);
}

void test_stdio2(void) {
  FILE  *f;
  int   i, fd;
  pos_t *fpos;
  char  c;
  
  pr("fileno");
  if (fileno(stdin) != 0) fail("fileno-1");
  if (fileno(stdout) != 1) fail("fileno-2");
  if (fileno(stderr) != 2) fail("fileno-3");

  if ((f = fopen(TSTFILE4, "w+")) == NULL) {
    fail("fopen-1");
    return;
  }

  pr("fputc");
  for (i='A'; i<='Z'; i++)
    if (fputc(i, f) != i)
      fail("fputc-1");

  pr("fflush");
  if (fflush(f) < 0) fail("fflush-1");
  
  fclose(f);
  
  if ((f = fopen(TSTFILE4, "r")) == NULL) {
    fail("fopen-2");
    return;
  }    
  
  pr("lseek");
  fd = fileno(f);

  /* seek from end of file */
  if(lseek(fd, -1, SEEK_END) < 0) fail("lseek-1");
  else {
    c = fgetc(f);
    if(c != 'Z') { 
      fail("lseek-2");
      fclose(f);
      return;
    }    
  }

  /* seek to beginning */
  if(lseek(fd, 0, SEEK_SET) < 0) fail("lseek-3");
  else {
    c = fgetc(f);
    if(c != 'A') fail("lseek-4");
  }

  /* seek from current position */
  if(lseek(fd, 12, SEEK_CUR) < 0) fail("lseek-5");
  /* set up position pointer */
  else {
    c = fgetc(f);
    if(c != 'N') fail("lseek-6");
  }

  /* set up position pointer */
  fpos = &filpos;
  
  pr("fgetpos");
  if (fgetpos(f, fpos) < 0)  fail("fgetpos-1");
  
  if (fpos->hi != 0)  fail("fgetpos-2");
  if (fpos->lo != 14)  fail("fgetpos-3");
  
  pr("ftell");
  if (ftell(f) != 14)  fail("ftell-1");
  
  pr("fsetpos");
  fpos->lo = 20;
  fpos->hi = 0;
  if (fsetpos(f, fpos) < 0)  fail("fsetpos-1");
  if (ftell(f) != 20)  fail("fsetpos-2");
  
  pr("fseek");
  if(fseek(f, 2, SEEK_CUR) < 0) fail("fseek-1");
  if (ftell(f) != 22)  fail("fseek-2");

  pr("rewind");
  rewind(f);
  if (ftell(f) != 0)
    fail("rewind-1");

  pr("fgets");
  for (i='A'; i<='Z'; i++) {
    if (fgetc(f) != i) {
      fail("fgetc-1");
      break;
    }
  }

  if (fgetc(f) != EOF) fail("fgetc-2");
  pr("ungetc");
  clearerr(f);
  if (ungetc('X', f) != 'X') fail("ungetc-1");
  if (fgetc(f) != 'X') fail("ungetc-2");
  if (ungetc('X', f) != 'X') fail("ungetc-3");
  if (ungetc('X', f) != EOF) fail("ungetc-4");
  if (fgetc(f) != 'X') fail("ungetc-5");

  clearerr(f);
  if (fclose(f)) fail("fclose-5");

  unlink(TSTFILE4);
}


int main(int argc, char **argv) {
  test_stdio2();
  return result;
}
