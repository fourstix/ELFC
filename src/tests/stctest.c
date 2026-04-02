//#define _STGROM_
#include <stdio.h>

int	Errors = 0;
int result = EXIT_SUCCESS;


struct point {
  int x;
  int y;
};

/* global point */
struct point gp;

/* array of points */
struct point a[2];

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
  result = EXIT_FAILURE;
}

struct point testglobal() {
  gp.x = 20;
  gp.y = 23;

  //printf("gp.x = %d gp.y = %d\n", gp.x, gp.y);

  if (gp.x != 20 || gp.y != 23) fail("testglobal-1");

  return gp;
}


struct point *testptr(struct point * p2){
  static struct point val;

  //printf("p2->x = %d p2->y = %d\n", p2->x, p2->y);
  if (p2->x != 16 || p2->y != 64) fail("testptr-1");

  val.x = 100;
  val.y = 200;

  //printf("val.x = %d val.y = %d\n", val.x, val.y);
  if (val.x != 100 || val.y != 200) fail("testptr-2");

  return &val;
}

struct point testloc(void){
  struct point loc;

  loc.x = 3;
  loc.y = 5;

  //printf("loc.x = %d loc.y = %d\n", loc.x, loc.y);

  if (loc.x != 3 || loc.y != 5) fail("testloc-1");

  //printf("Test direct assignment: gp = loc\n");
  gp = loc;
  //printf("After gp.x = %d gp.y = %d\n", gp.x, gp.y);
  if (gp.x != 3 || gp.y != 5) fail("testloc-2");

  //BRKPT
  return loc;
}


struct point testarg(int n, int m, struct point t) {
  //printf("t.x = %d t.y = %d\n", t.x, t.y);
  if (t.x != -120 || t.y != 360) fail("testarg-1");

  //printf("n = %d m = %d\n", n, m);
  if (n != 19 || m != -41) fail("testarg-3");
  t.x = n;
  t.y = m;
  if (t.x != n || t.y != m) fail("testarg-4");

  return t;
}

int testxy(int x, int y) {
  //printf("x = %d, y = %d\n", x, y);
  if (x != 19 || y != -41) return -1;
  return 0;
}

int testpxy(struct point *ptr) {
  //printf("p->x = %d, p->y = %d\n", ptr->x, ptr->y);
  if (ptr->x != 19 || ptr->y != -41) return -1;
  return 0;
}


int testpt(struct point pt) {
  //printf("pt.x = %d, pt.y = %d\n", pt.x, pt.y);
  if (pt.x != 19 || pt.y != -41) return -1;
  return 0;
}

struct point getpt() {
  static struct point val;
  val.x = 19;
  val.y = -41;
  return val;
}


/* Test that structure by value doesn't step on other arguments */
struct point testguard(int n, struct point t, int m) {
  if (n != 19 || m != -41) fail("testguard-1");

  //printf("t.x = %d t.y = %d\n", t.x, t.y);
  if (t.x != -120 || t.y != 360) fail("testguard-2");
  t.x = n;
  t.y = m;
  return t;
}

int main() {
struct point ret;
struct point *p;
struct point t2;

printf("Test setting and returning a global structure\n");
t2 = testglobal();
//printf("t2.x = %d t2.y = %d\n", t2.x, t2.y);
if (t2.x != 20 || t2.y != 23) fail("testglobal-2");

printf("Test assigning from a structure to structure\n");
ret = t2;
//printf("ret.x = %d ret.y = %d\n", ret.x, ret.y);
if (ret.x != 20 || ret.y != 23) fail("testglobal-3");

printf("Test assigning structure to array elements\n");

t2.x = 16;
t2.y = 64;

a[0] = ret;
a[1] = t2;

if (a[0].x != 20 || a[0].y != 23) fail("testarray-1");
if (a[1].x != 16 || a[1].y != 64) fail("testarray-2");

printf("Test assigning array element returned by function\n");
a[0] = getpt();
if (a[0].x != 19 || a[0].y != -41) fail("testarray-3");

printf("Test passing and returning pointers to struct\n");
//printf("Passing t2.x = %d t2.y = %d as pointer argument\n", t2.x, t2.y);
p = testptr(&t2);
//printf("p->x = %d p->y = %d\n", p->x, p->y);
if (p->x != 100 || p->y != 200) fail("testptr-3");

printf("Test assigning to structure from pointer\n");
ret = *p;
//printf("ret.x = %d ret.y = %d\n", ret.x, ret.y);
if (ret.x != 100 || ret.y != 200) fail("testptr-4");


printf("Test returning a local struct\n");
t2 = testloc();

//printf("t2.x = %d t2.y = %d\n", t2.x, t2.y);
if (t2.x != 3 || t2.y != 5) fail("testloc-3");

printf("Test assigning to a structure through pointer reference\n");
p = &ret;
*p = t2;

//printf("p->x = %d p->y = %d\n", p->x, p->y);
if (p->x != 3 || p->y != 5) fail("testloc-4");

//printf("ret.x = %d ret.y = %d\n", ret.x, ret.y);
if (ret.x != 3 || ret.y != 5) fail("testloc-5");

printf("Test passing and returning a structure by value\n");
ret.x = -120;
ret.y = 360;
t2 = testarg(19, -41, ret);

//printf("t2.x = %d t2.y = %d\n", t2.x, t2.y);
if (t2.x != 19 || t2.y != -41) fail("testarg-5");

printf("Test struct field values as arguments\n");
if (testxy(t2.x, t2.y)) fail("testdot-1");


printf("Test struct pointer field values as arguments\n");
p = &t2;
if (testxy(p->x, p->y)) fail("testptr-1");
if (testxy((&t2)->x, (&t2)->y)) fail("testptr-2");
if(testpxy(p)) fail("testptr-3");
if(testpt(*p)) fail("testptr-4");

printf("Test structure argument doesn't step on other arguments\n");
ret.x = -120;
ret.y = 360;
t2 = testguard(19, ret, -41);
if (t2.x != 19 || t2.y != -41) fail("testguard-3");
//printf("t2.x = %d t2.y = %d\n", t2.x, t2.y);
if(testpt(t2)) fail("testguard-4");

printf("Test argument as function returning structure\n");
if(testpt(getpt())) fail("testfunc-1");

if(testpt(testguard(19, ret, -41))) fail("testfunc-2");

printf("Test passing structure from array element as argument\n");
if(testpt(a[0])) fail("testfunc-3");

if (!Errors)
  printf("All tests passed.\n");

return result;
}
