/*
 *	NMH's Simple C Compiler, 2011--2014
 *	Code generator interface
 */

void cgadd(void);
//grw - removed cgalign
//void cgalign(void);
void cgand(void);
void cgbool(void);
void cgbreq(int n);
//grw - added short ciruit flag
void cgbrfalse(int n, int sc);
void cgbrge(int n);
void cgbrgt(int n);
void cgbrle(int n);
void cgbrlt(int n);
void cgbrne(int n);
//grw - added short ciruit flag
void cgbrtrue(int n, int sc);
void cgbruge(int n);
void cgbrugt(int n);
void cgbrule(int n);
void cgbrult(int n);
void cgcall(char *s);
//grw
//void cgcalr(void);
void cgcalr(int n);
void cgcalswtch(void);
void cgcase(int v, int l);
//grw - removed cgclear and cgclear2
//void cgclear(void);
//void cgclear2(void);
//grw - removed cgdata
//void cgdata(void);
void cgdec1ib(void);
void cgdec1iw(void);
void cgdec1pi(int v);
void cgdec2ib(void);
void cgdec2iw(void);
void cgdec2pi(int v);
void cgdecgb(char *s);
void cgdecgw(char *s);
void cgdeclb(int a);
void cgdeclw(int a);
void cgdecpg(char *s, int v);
void cgdecpl(int a, int v);
void cgdecps(int a, int v);
void cgdecsb(int a);
void cgdecsw(int a);
void cgdefb(int v);
void cgdefc(int c);
void cgdefl(int v);
void cgdefp(int v);
void cgdefs(char *s, int len);
void cgdefw(int v);
//grw - added support for signed and unsgined
void cgdiv(int sgn);
void cgentry(void);
void cgeq(void);
void cgexit(void);
void cggbss(char *s, int z);
void cgge(void);
void cggt(void);
void cginc1ib(void);
void cginc1iw(void);
void cginc1pi(int v);
void cginc2ib(void);
void cginc2iw(void);
void cginc2pi(int v);
void cgincgb(char *s);
void cgincgw(char *s);
void cginclb(int a);
void cginclw(int a);
void cgincpg(char *s, int v);
void cgincpl(int a, int v);
void cgincps(int a, int v);
void cgincsb(int a);
void cgincsw(int a);
//grw - added support for signed and unsigned
void cgindb(int sgn);
void cgindw(void);
void cginitlw(int v, int a);
void cgior(void);
void cgjump(int n);
void cglbss(char *s, int z);
void cgldga(char *s);
//grw - added support for signed and unsigned
void cgldgb(char *s, int sgn);
void cgldgw(char *s);
void cgldinc(void);
void cgldla(int n);
void cgldlab(int id);
//grw - added support for signed and unsigned
void cgldlb(int n, int sgn);
void cgldlw(int n);
void cgldsa(int n);
//grw - added support for signed and unsigned
void cgldsb(int n, int sgn);
void cgldsw(int n);
void cgldswtch(int n);
void cgle(void);
void cglit(int v);
int  cgload2(void);
void cglognot(void);
void cglt(void);
//grw - added support for signed and unsgined
void cgmod(int sgn);
//grw - added support for signed and unsgined
void cgmul(int sgn);
void cgne(void);
void cgneg(void);
void cgnot(void);
void cgpop2(void);
void cgpopptr(void);
void cgpostlude(void);
void cgprelude(void);
void cgpublic(char *s);
void cgpush(void);
void cgpushlit(int n);
void cgscale(void);
void cgscale2(void);
void cgscale2by(int v);
void cgscaleby(int v);
void cgshl(void);
void cgshr(void);
void cgstack(int n);
void cgstorgb(char *s);
void cgstorgw(char *s);
void cgstorib(void);
void cgstoriw(void);
void cgstorlb(int n);
void cgstorlw(int n);
void cgstorsb(int n);
void cgstorsw(int n);
void cgsub(void);
void cgswap(void);
void cgand(void);
void cgxor(void);
//grw - removed cgtext
//void cgtext(void);
void cguge(void);
void cgugt(void);
void cgule(void);
void cgult(void);
void cgunscale(void);
void cgunscaleby(int v);
void cgxor(void);
//grw - functions to get and save return value to expression stack
void cgpushd(void);
void cgpopd(void);
//grw - function to name a procedure
char *procname(char *file);
//grw - function to return entry point
int  cgentrypt(void);
//grw - set up handler for STG breakpoint
void cgsetup(void);
//grw - added support for user labels and goto
void cggoto(int n);
//grw - added support to return struct/union types
void cgcopy(int n);
