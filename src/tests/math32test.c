#include <stdio.h>
#include <mathi32.h>

int	Errors = 0;
int result = EXIT_SUCCESS;

char number[20];

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
  result = EXIT_FAILURE;
}

void pr(char *s) {
	printf("%s\n", s);
}


int32_t a;
int32_t b;

int main() {
  int32_t n;
  int32_t x;

	char *endp;

  pr("atoi32");
  a = atoi32("60001");
  if (a.low != 0xea61 || a.high != 0) fail("atoi32-1");
  b = atoi32("-60001");
  if (b.low != 0x159f || b.high != 0xffff) fail("atoi32-2");
  n = atoi32("0");
  if (n.low != 0 || n.high != 0) fail("atoi32-3");

  pr("cmpi32");
  if (cmpi32(a, n) <= 0) fail("cmpi32-1");
  if (cmpi32(b, n) >= 0) fail("cmpi32-2");
  if (cmpi32(a, b) <= 0) fail("cmpi32-3");
  if (cmpi32(b, a) >= 0) fail("cmpi32-4");
  n = atoi32("60001");
  if (cmpi32(a,n)) fail("cmpi32-5");

  pr("addi32");
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  n = addi32(a, n);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0x0001 || n.low != 0xd4c2) fail("addi32-1");
  n = addi32(a, b);
  if (n.low != 0 || n.high != 0) fail("addi32-2");
  n = addi32(a,a);
  n = addi32(a,n);
  if (n.high != 0x0002 || n.low != 0xbf23) fail("addi32-3");
  pr("subi32");
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  n = subi32(n, a);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0x0001 || n.low != 0xd4c2) fail("subi32-1");
  n = subi32(n, b);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0x0002 || n.low != 0xbf23) fail("subi32-2");

  pr("toi32");
  x = toi32(5);
  if (x.low != 0x0005 || x.high != 0) fail("toi32-1");

  x = toi32(-5);
  if (x.low != 0xfffb || x.high != 0xffff) fail("toi32-2");

  pr("muli32");
  x = toi32(5);
  n = muli32(a, x);
  if (n.high != 0x0004 || n.low != 0x93e5) fail("muli32-1");

  n = muli32(b, x);
  if (n.high != 0xfffb || n.low != 0x6c1b) fail("muli32-2");

  x = toi32(-5);
  n = muli32(b, x);
  if (n.high != 0x0004 || n.low != 0x93e5) fail("muli32-3");

  n = muli32(a, x);
  if (n.high != 0xfffb || n.low != 0x6c1b) fail("muli32-4");

  pr("negi32");
  //x = negi32(a);
  //printf("x.high = %04X, x.low = %04X\n", x.high, x.low);
  if (cmpi32(negi32(a), b)) fail("negi32-1");
  //if (cmpi32(x, b)) fail("negi32-1");

  //x = negi32(b);
  //printf("x.high = %04X, x.low = %04X\n", x.high, x.low);
  if (cmpi32(a, negi32(b))) fail("negi32-2");
  //if (cmpi32(a, x)) fail("negi32-2");


  x = negi32(n);
  //printf("x.high = %04X, x.low = %04X\n", x.high, x.low);
  if (cmpi32(a, negi32(b))) fail("negi32-2");
  if (x.high != 0x0004 || x.low != 0x93e5) fail("negi32-3");

  n = negi32(x);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0xfffb || n.low != 0x6c1b) fail("negi32-4");


  pr("absi32");
	if (cmpi32(a, absi32(b))) fail("absi32-1");
  if (cmpi32(a, absi32(a))) fail("absi32-2");
	if (cmpi32(absi32(x), absi32(n))) fail("absi32-3");

  pr("divi32");
  a = atoi32("5120003");
	b = atoi32("10000");
	n = divi32(a,b, &x);

	//printf("a = %04X:%04X / b %04X:%04X\n", a.high, a.low, b.high, b.low);
	//printf("quot = %04X:%04X, rem = %04X:%04X\n", n.high, n.low, x.high, x.low);

	if (n.high != 0 || n.low != 0x0200) fail("divi32-1");
	if (x.high != 0 || x.low != 0x0003) fail("divi32-2");


	a = atoi32("-5120003");
	b = atoi32("10000");
	n = divi32(a,b, &x);

	//printf("a = %04X:%04X / b %04X:%04X\n", a.high, a.low, b.high, b.low);
	//printf("quot = %04X:%04X, rem = %04X:%04X\n", n.high, n.low, x.high, x.low);

	if (n.high != 0xffff || n.low != 0xfe00) fail("divi32-3");
	if (x.high != 0xffff || x.low != 0xfffd) fail("divi32-4");


	a = atoi32("-5120003");
	b = atoi32("-10000");
	n = divi32(a,b, &x);

	//printf("a = %04X:%04X / b %04X:%04X\n", a.high, a.low, b.high, b.low);
	//printf("quot = %04X:%04X, rem = %04X:%04X\n", n.high, n.low, x.high, x.low);

	if (n.high != 0 || n.low != 0x0200) fail("divi32-5");
	if (x.high != 0xffff || x.low != 0xfffd) fail("divi32-6");

	pr("i32toa");
	i32toa(a, number);
	if (strcmp(number, "-5120003")) fail("i32toa-1");
	i32toa(n, number);
	if (strcmp(number, "512")) fail("i32toa-2");

	pr("strtoi32");
	n = strtoi32("-5120003junk", &endp, 10);
	if (n.high != 0xffb1 || n.low != 0xdffd) fail("strtoi32-3");
	if (!endp) fail("strtoi32-2");
	if (strcmp(endp, "junk")) fail("strtoi32-3");
	//printf("n = %04X:%04X  endp = %s\n", n.high, n.low, endp);

	n = strtoi32("030d416F", &endp, 16);
	if (n.high != 0x030d || n.low != 0x416f) fail("strtoi32-4");
	if (!endp) fail("strtoi32-5");
	if (strlen(endp)) fail("strtoi32-6");
	//printf("n = %04X:%04X  endp = %s\n", n.high, n.low, endp);

	pr("shli32");
	a.high = 0x5555;
  a.low  = 0xaaaa;
	n = shli32(a, 1);
	if (n.high != 0xaaab || n.low != 0x5554) fail("shli32-1");
  //printf("n = %04X:%04X\n", n.high, n.low, endp);

	pr("shri32");
	a.high = 0xaaaa;
	a.low  = 0x5555;
	n = shri32(a, 1);
	if (n.high != 0x5555 || n.low != 0x2AAA) fail("shri32-1");
	//printf("n = %04X:%04X\n", n.high, n.low, endp);

  if (!Errors)
    printf("All tests passed.\n");

  return result;
}
