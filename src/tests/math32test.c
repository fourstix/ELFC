#include <stdio.h>
#include <math32.h>

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

  pr("cmp32");
  if (cmp32(a, n) <= 0) fail("cmp32-1");
  if (cmp32(b, n) >= 0) fail("cmp32-2");
  if (cmp32(a, b) <= 0) fail("cmp32-3");
  if (cmp32(b, a) >= 0) fail("cmp32-4");
  n = atoi32("60001");
  if (cmp32(a,n)) fail("cmp32-5");

  pr("add32");
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  n = add32(a, n);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0x0001 || n.low != 0xd4c2) fail("add32-1");
  n = add32(a, b);
  if (n.low != 0 || n.high != 0) fail("add32-2");
  n = add32(a,a);
  n = add32(a,n);
  if (n.high != 0x0002 || n.low != 0xbf23) fail("add32-3");
  pr("sub32");
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  n = sub32(n, a);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0x0001 || n.low != 0xd4c2) fail("sub32-1");
  n = sub32(n, b);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0x0002 || n.low != 0xbf23) fail("sub32-2");

  pr("to_int32");
  x = to_int32(5);
  if (x.low != 0x0005 || x.high != 0) fail("to_int32-1");

  x = to_int32(-5);
  if (x.low != 0xfffb || x.high != 0xffff) fail("to_int32-2");

  pr("mul32");
  x = to_int32(5);
  n = mul32(a, x);
  if (n.high != 0x0004 || n.low != 0x93e5) fail("mul32-1");

  n = mul32(b, x);
  if (n.high != 0xfffb || n.low != 0x6c1b) fail("mul32-2");

  x = to_int32(-5);
  n = mul32(b, x);
  if (n.high != 0x0004 || n.low != 0x93e5) fail("mul32-3");

  n = mul32(a, x);
  if (n.high != 0xfffb || n.low != 0x6c1b) fail("mul32-4");

  pr("neg32");
  //x = neg32(a);
  //printf("x.high = %04X, x.low = %04X\n", x.high, x.low);
  if (cmp32(neg32(a), b)) fail("neg32-1");
  //if (cmp32(x, b)) fail("neg32-1");

  //x = neg32(b);
  //printf("x.high = %04X, x.low = %04X\n", x.high, x.low);
  if (cmp32(a, neg32(b))) fail("neg32-2");
  //if (cmp32(a, x)) fail("neg32-2");


  x = neg32(n);
  //printf("x.high = %04X, x.low = %04X\n", x.high, x.low);
  if (cmp32(a, neg32(b))) fail("neg32-2");
  if (x.high != 0x0004 || x.low != 0x93e5) fail("neg32-3");

  n = neg32(x);
  //printf("n.high = %04X, n.low = %04X\n", n.high, n.low);
  if (n.high != 0xfffb || n.low != 0x6c1b) fail("neg32-4");


  pr("abs32");
	if (cmp32(a, abs32(b))) fail("abs32-1");
  if (cmp32(a, abs32(a))) fail("abs32-2");
	if (cmp32(abs32(x), abs32(n))) fail("abs32-3");

  pr("div32");
  a = atoi32("5120003");
	b = atoi32("10000");
	n = div32(a,b, &x);

	//printf("a = %04X:%04X / b %04X:%04X\n", a.high, a.low, b.high, b.low);
	//printf("quot = %04X:%04X, rem = %04X:%04X\n", n.high, n.low, x.high, x.low);

	if (n.high != 0 || n.low != 0x0200) fail("div32-1");
	if (x.high != 0 || x.low != 0x0003) fail("div32-2");


	a = atoi32("-5120003");
	b = atoi32("10000");
	n = div32(a,b, &x);

	//printf("a = %04X:%04X / b %04X:%04X\n", a.high, a.low, b.high, b.low);
	//printf("quot = %04X:%04X, rem = %04X:%04X\n", n.high, n.low, x.high, x.low);

	if (n.high != 0xffff || n.low != 0xfe00) fail("div32-3");
	if (x.high != 0xffff || x.low != 0xfffd) fail("div32-4");


	a = atoi32("-5120003");
	b = atoi32("-10000");
	n = div32(a,b, &x);

	//printf("a = %04X:%04X / b %04X:%04X\n", a.high, a.low, b.high, b.low);
	//printf("quot = %04X:%04X, rem = %04X:%04X\n", n.high, n.low, x.high, x.low);

	if (n.high != 0 || n.low != 0x0200) fail("div32-5");
	if (x.high != 0xffff || x.low != 0xfffd) fail("div32-6");

	pr("itoa32");
	itoa32(a, number);
	if (strcmp(number, "-5120003")) fail("itoa32-1");
	itoa32(n, number);
	if (strcmp(number, "512")) fail("itoa32-2");

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

	pr("shl32");
	a.high = 0x5555;
  a.low  = 0xaaaa;
	n = shl32(a);
	if (n.high != 0xaaab || n.low != 0x5554) fail("shl32-1");
  //printf("n = %04X:%04X\n", n.high, n.low, endp);

	pr("shr32");
	a.high = 0xaaaa;
	a.low  = 0x5555;
	n = shr32(a);
	if (n.high != 0x5555 || n.low != 0x2AAA) fail("shr32-1");
	//printf("n = %04X:%04X\n", n.high, n.low, endp);

  if (!Errors)
    printf("All tests passed.\n");

  return result;
}
