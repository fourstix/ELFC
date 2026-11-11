/*
 * Test the dirent library on ELF-DOS
 *
 *   dirtest [path]
 *
 * Lists the directory (the current directory without a path), then
 * checks the error cases, reading two directories at the same time
 * with other directory operations in between, and rewinddir.
 *
 * Build with: elfc -E dirtest.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math32.h>
#include <dirent.h>

#define TSTFILE   "dtest.tmp"

int Errors = 0;
char sizebuf[12];

void fail(char *name) {
  printf("%s failed\n", name);
  Errors++;
}

void pr(char *s) {
  printf("%s\n", s);
}

void list(char *path) {
  DIR *d;
  struct dirent *e;
  int n;

  d = opendir(path);
  if (d == NULL) {
    printf("opendir(\"%s\"): %s\n", path, strerror(errno));
    fail("list");
    return;
  }

  printf("Directory of \"%s\"\n", path);
  n = 0;
  while ((e = readdir(d)) != NULL) {
    if (DE_ISDIR(e))
      printf("  %-20s      <DIR> ", e->d_name);
    else
      printf("  %-20s %10s ", e->d_name, u32toa(e->d_size, sizebuf));
    printf("%04d-%02d-%02d %02d:%02d %c%c%c\n",
      DE_YEAR(e), DE_MONTH(e), DE_DAY(e), DE_HOUR(e), DE_MIN(e),
      (e->d_attr & _A_RDONLY) ? 'R' : '-',
      (e->d_attr & _A_HIDDEN) ? 'H' : '-',
      (e->d_attr & _A_SYSTEM) ? 'S' : '-');
    n++;
  }
  printf("  %d entries\n", n);

  if (closedir(d) != 0)
    fail("closedir");
}

/* count the entries of an open directory, from where it is */
int count(DIR *d) {
  int n;

  n = 0;
  while (readdir(d) != NULL)
    n++;
  return n;
}

void test_errors(void) {
  DIR *d;
  FILE *f;

  pr("opendir missing path");
  errno = 0;
  d = opendir("nosuchdir.xyz");
  if (d != NULL || errno != ENOENT)
    fail("opendir missing path");

  pr("opendir missing parent");
  errno = 0;
  d = opendir("nosuchdir.xyz/sub");
  if (d != NULL || errno != ENOENT)
    fail("opendir missing parent");

  pr("opendir file");
  f = fopen(TSTFILE, "w");
  if (f == NULL) {
    fail("fopen");
  } else {
    fputs("dirent test\n", f);
    fclose(f);
    errno = 0;
    d = opendir(TSTFILE);
    if (d != NULL || errno != ENOTDIR)
      fail("opendir file");
    remove(TSTFILE);
  }

  pr("opendir NULL");
  errno = 0;
  if (opendir(NULL) != NULL || errno != EINVAL)
    fail("opendir NULL");

  pr("readdir NULL");
  errno = 0;
  if (readdir(NULL) != NULL || errno != EBADF)
    fail("readdir NULL");

  pr("closedir NULL");
  errno = 0;
  if (closedir(NULL) != EOF || errno != EBADF)
    fail("closedir NULL");
}

void test_scan(char *path) {
  DIR *d1;
  DIR *d2;
  DIR *r;
  struct dirent *e1;
  struct dirent *e2;
  int n;
  int n1;
  int n2;

  d1 = opendir(path);
  if (d1 == NULL) {
    fail("opendir");
    return;
  }

  pr("readdir to end");
  n = count(d1);
  if (readdir(d1) != NULL)
    fail("readdir after end");

  pr("rewinddir");
  rewinddir(d1);
  if (count(d1) != n)
    fail("rewinddir");

  /*
   * Read the directory with two DIRs in turn, with a listing of the
   * root and a failed opendir in between, which use the kernel's
   * directory scan too.  Both must see the same entries in order.
   */
  pr("interleaved readdir");
  rewinddir(d1);
  d2 = opendir(path);
  if (d2 == NULL) {
    fail("opendir second");
    closedir(d1);
    return;
  }
  n1 = 0;
  n2 = 0;
  for (;;) {
    e1 = readdir(d1);
    r = opendir("/");
    if (r != NULL) {
      readdir(r);
      readdir(r);
      closedir(r);
    }
    opendir("nosuchdir.xyz");
    e2 = readdir(d2);
    if (e1 == NULL || e2 == NULL)
      break;
    n1++;
    n2++;
    if (strcmp(e1->d_name, e2->d_name) != 0) {
      printf("  \"%s\" != \"%s\"\n", e1->d_name, e2->d_name);
      fail("interleaved names");
      break;
    }
  }
  if (e1 != NULL || e2 != NULL || n1 != n)
    fail("interleaved count");

  closedir(d2);
  closedir(d1);
}

void test_paths(void) {
  DIR *d;

  pr("opendir root paths");
  d = opendir("/");
  if (d == NULL) fail("opendir /");
  else closedir(d);

  d = opendir("C:/");
  if (d == NULL) fail("opendir C:/");
  else closedir(d);

  d = opendir("C:");
  if (d == NULL) fail("opendir C:");
  else closedir(d);

  d = opendir(".");
  if (d == NULL) fail("opendir .");
  else closedir(d);

  /* ".." is a real entry in a subdirectory, and the root itself in the root */
  d = opendir("..");
  if (d == NULL) fail("opendir ..");
  else closedir(d);

  d = opendir("/bin");
  if (d == NULL) fail("opendir /bin");
  else closedir(d);

  d = opendir("/bin/");
  if (d == NULL) fail("opendir /bin/");
  else closedir(d);
}

int main(int argc, char **argv) {
  char *path;

  path = (argc > 1) ? argv[1] : "";

  list(path);
  test_errors();
  test_paths();
  test_scan(path);

  if (Errors)
    printf("%d test(s) failed\n", Errors);
  else
    pr("all tests passed");

  return Errors ? EXIT_FAILURE : EXIT_SUCCESS;
}
