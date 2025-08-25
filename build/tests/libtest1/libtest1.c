/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 1014
 * In the public domain
 *
 * Test the stdlib memory, sort and search functions
 * Test 1 of 
 */
 
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 
 int	Errors = 0;
 char	v1[64];
 char	*segp[10];
 int  num[32];
 int result = EXIT_SUCCESS;
 
 void fail(char *name) {
 	printf("%s failed\n", name);
 	Errors++;
  result = EXIT_FAILURE;
 }
 
 void pr(char *s) {
 	printf("%s\n", s);
 }
 
 void test_memfn(void) {
 	char	*c1, *c2, *p;
 	int	i;
 
 	pr("memcmp");
 	c1 = "test01";
 	c2 = "test03";
 	if (memcmp(c1, c2, 5)) fail("memcmp-1");
 	if (!memcmp(c1, c2, 6)) fail("memcmp-2");
 	if (memcmp(c1, c2, 6) != -2) fail("memcmp-3");
 	if (memcmp(c2, c1, 6) != 2) fail("memcmp-4");
 
 	pr("memcpy");
 	c1 = "abcdefghijklmnopqrstuvwxyz0123456789";
 	memcpy(v1, c1, 36);
 	if (memcmp(c1, v1, 36)) fail("memcpy-1");
 	memcpy(v1+18, v1, 36);
 	if (memcmp(c1, v1+18, 18)) fail("memcpy-2");
 	memcpy(v1, v1+18, 36);
 	if (memcmp(c1, v1, 18)) fail("memcpy-3");
 
 	pr("memmove");
 	memcpy(v1, c1, 36);
 	memmove(v1+1, v1, 35);
 	if (memcmp(v1+1, c1, 35) || *v1 != 'a') fail("memmove-1");
 	memcpy(v1, c1, 36);
 	memmove(v1, v1+1, 35);
 	if (memcmp(v1, c1+1, 35) || v1[35] != '9') fail("memmove-2");
 
 	pr("memset");
 	for (i=0; i<64; i++) v1[i] = -1;
 	memset(v1, 0, 32);
 	if (v1[31]) fail("memset-1");
 	if (!v1[32]) fail("memset-2");
 	for (i=0; i<128; i++) v1[i] = -1;
 	memset(v1, 123, 32);
 	if (v1[31] != 123) fail("memset-3");
 	if (v1[32] == 123) fail("memset-4");
 
 	pr("memchr");
 	c1 = "...............X1";
 	p = memchr(c1, 'X', 16);
 	if (!p || *p != 'X' || p[1] != '1') fail("memchr-1");
 	if (memchr(c1, 'X', 15) != NULL) fail("memchr-2");
 }

 void test_dmem(void) {
 	char	*a;
 	int	i, j;
 
 	pr("malloc");
 	for (i=0; i<10; i++) {
 		if ((segp[i] = malloc(64)) == NULL)
 			break;
 		for (j=0; j<64; j++)
 			segp[i][j] = i;
 	}
 	if (i < 10) fail("malloc-1");
 	for (i=0; i<10; i++) {
 		for (j=0; j<64; j++)
 			if (segp[i][j] != i)
 				break;
 		if (j != 64)
 			break;
 	}
 	if (i < 10) fail("malloc-2");
 
 	pr("free");
 	for (j=0; j<i; j++)
 		free(segp[j]);
 
 	pr("calloc");
 	if ((a = calloc(i, 64)) == NULL)
 		fail("calloc-1");
 	for (i=0; i<64; i++)
 		if (a[i]) break;
 	if (i < 64)
 		fail("calloc-2");
 	free(a);
 
 	pr("realloc");
 	if ((a = malloc(123)) == NULL)
 		fail("malloc-3");
 	for (i=0; i<123; i++)
 		a[i] = i;
 	if ((a = realloc(a, 257)) == NULL)
 		fail("realloc-1");
 	for (i=0; i<123; i++)
 		if (a[i] != i)
 			break;
 	if (i < 123) fail("realloc-2");
 	if ((a = realloc(a, 97)) == NULL)
 		fail("realloc-3");
 	for (i=0; i<97; i++)
 		if (a[i] != i)
 			break;
 	if (i < 97) fail("realloc-4");
 	free(a);
 }
 
 
 int qcmp(int *a, int *b) {
 	return (*a < *b) ? -1: (*a > *b) ? 1: 0;
 }
 
 void test_sort(void) {
 	//int	array[128];
 	int	i, j;
 
 	pr("qsort");
 	for (i=0; i<32; i++)
 		num[i] = 32-i;
 
  qsort(num, 32, sizeof(int), qcmp);

	for (j=i=0; i<32; i++) {
 		if (num[i] < j) {
 			fail("qsort-1");
 			break;
 		}
 		j = num[i];
 	}
 }
 
 int	test_array[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 27 };
 
 void test_search(void) {
 	int	key;
 	int	*p;
 
 	pr("bsearch");
 	key = 13;
 	if ((p = bsearch(&key, test_array, 10, sizeof(int), qcmp)) == NULL)
 		fail("bsearch-1");
 	if (*p != 13) fail("bsearch-2");
 	key = 15;
 	if (bsearch(&key, test_array, 10, sizeof(int), qcmp) != NULL)
 		fail("bsearch-3");
 }

 
 int main(int argc, char **argv) {
  test_memfn();
  test_dmem();
  test_sort();
  test_search();
  return result;
}
