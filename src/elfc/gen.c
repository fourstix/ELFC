/*
 *	NMH's Simple C Compiler, 2011,2012
 *	Code generator (emitter)
 */

#include "defs.h"
#include "data.h"
#include "decl.h"
#include "cgen.h"

int	Acc = 0;

void clear(void) {
	Acc = 0;
}

void load(void) {
	Acc = 1;
}

int label(void) {
	static int id = 1;

	return id++;
}

void spill (void) {
	if (Acc) genpush();
}

void genraw(char *s) {
	if (NULL == Outfile) return;
	fprintf(Outfile, "%s", s);
}

//grw - need ngen function without tab
void ngenraw(char *s, char *inst, int n) {
	if (NULL == Outfile) return;
	fprintf(Outfile, s, inst, n);
}
//grw - fuunction to output character 
void cgenraw(char *s, char ch) {
	if (NULL == Outfile) return;
	fprintf(Outfile, s, ch);
}
//grw - fuunction to output string 
void sgenraw(char *s, char *inst, char *s2) {
	if (NULL == Outfile) return;
	fprintf(Outfile, s, inst, s2);
}

void gen(char *s) {
	if (NULL == Outfile) return;
	fprintf(Outfile, "\t%s\n", s);
}

void ngen(char *s, char *inst, int n) {
	if (NULL == Outfile) return;
	fputc('\t', Outfile);
	fprintf(Outfile, s, inst, n);
	fputc('\n', Outfile);
}

void ngen2(char *s, char *inst, int n, int a) {
	if (NULL == Outfile) return;
	fputc('\t', Outfile);
	fprintf(Outfile, s, inst, n, a);
	fputc('\n', Outfile);
}

void lgen(char *s, char *inst, int n) {
	if (NULL == Outfile) return;
	fputc('\t', Outfile);
	fprintf(Outfile, s, inst, LPREFIX, n);
	fputc('\n', Outfile);
}

void lgen2(char *s, int v1, int v2) {
	if (NULL == Outfile) return;
	fputc('\t', Outfile);
	fprintf(Outfile, s, v1, LPREFIX, v2);
	fputc('\n', Outfile);
}

void sgen(char *s, char *inst, char *s2) {
	if (NULL == Outfile) return;
	fputc('\t', Outfile);
	fprintf(Outfile, s, inst, s2);
	fputc('\n', Outfile);
}

void genlab(int id) {
	if (NULL == Outfile) return;
	//grw - proceed label with new line
	fprintf(Outfile, "\n%c%d:", LPREFIX, id);
}

char *labname(int id) {
	static char	name[100];

	sprintf(name, "%c%d", LPREFIX, id);
	return name;
}

char *gsym(char *s) {
	static char	name[NAMELEN+2];

	name[0] = PREFIX;
	name[1] = 0;
	strcat(name, s);
	return name;
}

/* administrativa */

void gendata(void) {
//	if (Textseg) cgdata();
//	Textseg = 0;
}

//void gentext(void) {
//	if (!Textseg) cgtext();
//	Textseg = 1;
//}

void genprelude(void) {
	Textseg = 0;
//	gentext();
	cgprelude();
}

void genpostlude(void) {
	cgpostlude();
}

void genname(char *name) {
	genraw(gsym(name));
	genraw(":");
}

//grw - no need to mark public in ASM/02
//void genpublic(char *name) {
//	cgpublic(gsym(name));
//}

/* loading values */

void genaddr(int y) {
	//gentext();
	//spill();
	if (CAUTO == Stcls[y])
		cgldla(Vals[y]);
	else if (CLSTATC == Stcls[y])
		cgldsa(Vals[y]);
	else
		cgldga(gsym(Names[y]));
	//load();
}

void genldlab(int id) {
	//gentext();
	//spill();
	cgldlab(id);
	//load();
}

void genlit(int v) {
	//gentext();
	//spill();
	cglit(v);
	//load();
}

void genargc(void) {
	//gentext();
	//spill();
	cgargc();
	//load();
}

/* binary ops */

void genand(void) {
	//gentext();
	//cgpop2();
	cgand();
}

void genior(void) {
	//gentext();
	//cgpop2();
	cgior();
}

void genxor(void) {
	//gentext();
	//cgpop2();
	cgxor();
}

void genshl(int swapped) {
	//gentext();
	//cgpop2();
	// grw - change sense of swap flag
	//if (swapped) cgswap();
	if (!swapped) cgswap();
	cgshl();
}

void genshr(int swapped) {
	//gentext();
	//cgpop2();
	// grw - change sense of swap flag
	//if (swapped) cgswap();
	if (!swapped) cgswap();
	cgshr();
}

static int ptr(int p) {
	return INTPTR == p || INTPP == p ||
		CHARPTR == p || CHARPP == p ||
		VOIDPTR == p || VOIDPP == p ||
		FUNPTR == p;
}

static int needscale(int p) {
	return INTPTR == p || INTPP == p || CHARPP == p || VOIDPP == p;
}

int genadd(int p1, int p2, int swapped) {
	int	rp = PINT, t;

	//gentext();
	//cgpop2();
	//grw - change sense of swapped flag
	//if (!swapped) {
	if (swapped) {
		t = p1;
		p1 = p2;
		p2 = t;
	}
	if (ptr(p1)) {
		//grw - p1 is at sos 
		//if (needscale(p1)) cgscale();
		if (needscale(p1)) cgscale2();
		//grw debug
		if (needscale(p1)) genraw("; genadd scale p1");
		rp = p1;
	}
	else if (ptr(p2)) {
		//grw - p2 is at tos 
		//if (needscale(p2)) cgscale2();
		if (needscale(p2)) cgscale();
		//grw debug
		if (needscale(p2)) genraw("; genadd scale p2");
		rp = p2;
	}
	cgadd();
	return rp;
}

int gensub(int p1, int p2, int swapped) {
	int	rp = PINT;

	//gentext();
	//cgpop2();
	//grw - changed sense of swapped flag
	//if (swapped) cgswap();
	if (!swapped) cgswap();
	if (!inttype(p1) && !inttype(p2) && p1 != p2)
		error("incompatible pointer types in binary '-'", NULL);
	if (ptr(p1) && !ptr(p2)) {
		//grw after swapping - p2 is on TOS 
		//if (needscale(p1)) cgscale2();
		if (needscale(p1)) cgscale();
		rp = p1;
	}
	cgsub();
	if (needscale(p1) && needscale(p2))
		cgunscale();
	return rp;
}

void genmul(void) {
	//gentext();
	//cgpop2();
	cgmul();
}

void gendiv(int swapped) {
	//gentext();
	//cgpop2();
	//grw - changed sense of swapped flag
	//if (swapped) cgswap();
	if (!swapped) cgswap();
	cgdiv();
}

void genmod(int swapped) {
	//gentext();
	//cgpop2();
	//grw - changed sense of swapped flag
	//if (swapped) cgswap();
	if (!swapped) cgswap();
	cgmod();
}

static void binopchk(int op, int p1, int p2) {
	if (ASPLUS == op)
		op = PLUS;
	else if (ASMINUS == op)
		op = MINUS;
	if (inttype(p1) && inttype(p2))
		return;
	if (PLUS == op && (inttype(p1) || inttype(p2)))
		return;
	if (MINUS == op && (!inttype(p1) || inttype(p2)))
		return;
	if (	(EQUAL == op || NOTEQ == op || LESS == op ||
		 GREATER == op || LTEQ == op || GTEQ == op)
		&&
		(p1 == p2 ||
		 VOIDPTR == p1 && !inttype(p2) ||
		 VOIDPTR == p2 && !inttype(p1))
	)
		return;
	error("invalid operands to binary operator", NULL);
}

int genbinop(int op, int p1, int p2) {
	binopchk(op, p1, p2);
	switch (op) {
	case PLUS:	return genadd(p1, p2, 1);
	case MINUS:	return gensub(p1, p2, 1);
	case STAR:	genmul(); break;
	case SLASH:	gendiv(1); break;
	case MOD:	genmod(1); break;
	case LSHIFT:	genshl(1); break;
	case RSHIFT:	genshr(1); break;
	case AMPER:	genand(); break;
	case CARET:	genxor(); break;
	case PIPE:	genior(); break;
	case EQUAL:	cgeq(); break;
	case NOTEQ:	cgne(); break;
	case LESS:	cglt(); break;
	case GREATER:	cggt(); break;
	case LTEQ:	cgle(); break;
	case GTEQ:	cgge(); break;
	}
	return PINT;
}

/* unary ops */

void genbool(void) {
	//gentext();
	cgbool();
}

void genind(int p) {
	//gentext();
	if (PCHAR == p)
		cgindb();
	else
		cgindw();
}

void genlognot(void) {
	//gentext();
	cglognot();
}

void genneg(void) {
	//gentext();
	cgneg();
}

void gennot(void) {
	//gentext();
	cgnot();
}

void genscale(void) {
	//gentext();
	cgscale();
}

void genscale2(void) {
	//gentext();
	cgscale2();
}

/* jump/call/function ops */

void genjump(int dest) {
	//gentext();
	cgjump(dest);
}

void genbrfalse(int dest) {
	//gentext();
	cgbrfalse(dest);
}

void genbrtrue(int dest) {
	//gentext();
	cgbrtrue(dest);
}

void gencall(int y) {
	//gentext();
	cgcall(gsym(Names[y]));
	//load();
}

void gencalr(void) {
	//gentext();
	int n = label();
	cgcalr(n);
	//load();
}

void genentry(void) {
	//gentext();
	cgentry();
}

void genexit(void) {
	//gentext();
	cgexit();
}

void genpush(void) {
	//gentext();
	cgpush();
}

void genpushlit(int n) {
	//gentext();
	//spill();
	cgpushlit(n);
}

void genstack(int n) {
	if (n) {
		//gentext();
		cgstack(n);
	}
}

void genlocinit(void) {
	int	i;
	genraw(";----- genlocinit\n");
	//gentext();
	for (i=0; i<Nli; i++)
		cginitlw(LIval[i], LIaddr[i]);
}

/* data definitions */

void genbss(char *name, int len) {
	gendata();
	cgbss(name, len);
}

void gendefb(int v) {
	//gendata();
	cgdefb(v);
}

void gendefl(int id) {
	//gendata();
	cgdefl(id);
}

void gendefp(int v) {
	//gendata();
	cgdefp(v);
}

void gendefs(char *s, int len) {
//grw - replace with function for ASM/02
/*	int	i;

	gendata();
	for (i=1; i<len-1; i++) {
		if (isalnum(s[i]))
			cgdefc(s[i]);
		else
			cgdefb(s[i]);
	}
*/	
	cgdefs(s, len);
}

void gendefw(int v) {
	//gendata();
	cgdefw(v);
}

/* increment ops */

static void genincptr(int *lv, int inc, int pre) {
	int	y;

	//gentext();
	y = lv[LVSYM];
	if (!y && !pre) cgldinc();
	if (!pre) rvalue(lv);
	if (!y) {
		if (pre)
			if (inc)
				cginc1pi();
			else
				cgdec1pi();
		else
			if (inc)
				cginc2pi();
			else
				cgdec2pi();
	}
	else if (CAUTO == Stcls[y]) {
		if (inc)
			cgincpl(Vals[y]);
		else
			cgdecpl(Vals[y]);
	}
	else if (CLSTATC == Stcls[y]) {
		if (inc)
			cgincps(Vals[y]);
		else
			cgdecps(Vals[y]);
	}
	else {
		if (inc)
			cgincpg(gsym(Names[y]));
		else
			cgdecpg(gsym(Names[y]));
	}
	if (pre) rvalue(lv);
}

void geninc(int *lv, int inc, int pre) {
	int	y, b;

	//gentext();
	y = lv[LVSYM];
	if (needscale(lv[LVPRIM])) {
		genincptr(lv, inc, pre);
		return;
	}
	b = PCHAR == lv[LVPRIM];
	/* will duplicate move to aux register in (*char)++ */
	if (!y && !pre) cgldinc();
	if (!pre) rvalue(lv);
	if (!y) {
		if (pre)
			if (inc)
				b? cginc1ib(): cginc1iw();
			else
				b? cgdec1ib(): cgdec1iw();
		else
			if (inc)
				b? cginc2ib(): cginc2iw();
			else
				b? cgdec2ib(): cgdec2iw();
	}
	else if (CAUTO == Stcls[y]) {
		if (inc)
			b? cginclb(Vals[y]): cginclw(Vals[y]);
		else
			b? cgdeclb(Vals[y]): cgdeclw(Vals[y]);
	}
	else if (CLSTATC == Stcls[y]) {
		if (inc)
			b? cgincsb(Vals[y]): cgincsw(Vals[y]);
		else
			b? cgdecsb(Vals[y]): cgdecsw(Vals[y]);
	}
	else {
		if (inc)
			b? cgincgb(gsym(Names[y])):
			   cgincgw(gsym(Names[y]));
		else
			b? cgdecgb(gsym(Names[y])):
			   cgdecgw(gsym(Names[y]));
	}
	if (pre) rvalue(lv);
}

/* switch table generator */

void genswitch(int *vals, int *labs, int nc, int dflt) {
	int	i, ltbl;

	ltbl = label();
	//gentext();
	cgldswtch(ltbl);
	cgcalswtch();
	//gendata();
	genlab(ltbl);
	// gendefw(nc);
	for (i = 0; i < nc; i++)
		cgcase(vals[i], labs[i]);
	gendefl(dflt);
}

/* assigments */

void genasop(int op, int p1, int p2, int swapped) {
	binopchk(op, p1, p2);
	//grw - debugging
	//ngen(";----- genasop: %s = %d", "swapped", swapped);
	//ngen(";-----   %s = %d", "op", op);
	//ngen2(";-----   %s p1 = %d p2 = %d", "args", p1, p2);

	switch (op) {
	case ASDIV:	gendiv(swapped); break;
	case ASMUL:	genmul(); break;
	case ASMOD:	genmod(swapped); break;
	case ASPLUS:	genadd(p1, p2, swapped); break;
	case ASMINUS:	gensub(p1, p2, swapped); break;
	case ASLSHIFT:	genshl(swapped); break;
	case ASRSHIFT:	genshr(swapped); break;
	case ASAND:	genand(); break;
	case ASXOR:	genxor(); break;
	case ASOR:	genior(); break;
	}
}

void genstore(int op, int *lv, int *lv2) {
	int	swapped = 1;
	//grw DEBUG
	//ngen(";----- genstore %s = %d", "swapped", swapped);
	//ngen2(";----- genstore %s: lv = %d lv2 = %d", "lvars", lv[LVSYM], lv2[LVSYM]);
	//ngen2(";----- genstore %s: lv = %d lv2 = %d", "prim", lv[LVPRIM], lv2[LVPRIM]);

	//gentext();
	if (ASSIGN != op) {
		if (lv[LVSYM]) {
			rvalue(lv);
			swapped = 0;
		}
		genasop(op, lv[LVPRIM], lv2[LVPRIM], swapped);
	}
	if (!lv[LVSYM]) {
		cgpopptr();
		if (PCHAR == lv[LVPRIM])
			cgstorib();
		else
			cgstoriw();

	}
	else if (CAUTO == Stcls[lv[LVSYM]]) {
		if (PCHAR == lv[LVPRIM])
			cgstorlb(Vals[lv[LVSYM]]);
		else
			cgstorlw(Vals[lv[LVSYM]]);
	}
	else if (CLSTATC == Stcls[lv[LVSYM]]) {
		if (PCHAR == lv[LVPRIM])
			cgstorsb(Vals[lv[LVSYM]]);
		else
			cgstorsw(Vals[lv[LVSYM]]);
	}
	else {
		if (PCHAR == lv[LVPRIM])
			cgstorgb(gsym(Names[lv[LVSYM]]));
		else
			cgstorgw(gsym(Names[lv[LVSYM]]));
	}
}

/* rvalue computation */

void rvalue(int *lv) {
	//gentext();

	if (!lv[LVSYM]) {
		genind(lv[LVPRIM]);
	}
	else if (CAUTO == Stcls[lv[LVSYM]]) {
		//spill();
		if (PCHAR == lv[LVPRIM]) {
			//cgclear();
			cgldlb(Vals[lv[LVSYM]]);
		}
		else {
			cgldlw(Vals[lv[LVSYM]]);
		}
	}
	else if (CLSTATC == Stcls[lv[LVSYM]]) {
		//spill();
		if (PCHAR == lv[LVPRIM]) {
			//cgclear();
			cgldsb(Vals[lv[LVSYM]]);
		}
		else
			cgldsw(Vals[lv[LVSYM]]);
	}
	else {
		//spill();
		if (PCHAR == lv[LVPRIM]) {
			//cgclear();
			cgldgb(gsym(Names[lv[LVSYM]]));
		}
		else
			cgldgw(gsym(Names[lv[LVSYM]]));
	}
	//load();
}

//grw - added push data statement
/* 
 * Push  the value in the accumulator register, RA
 * to the TOS of the expression stack
 */
void genpushd() {
	cgpushd();
}

//grw - added pop data statement
/* 
 * Pop the value from the TOS of the expression stack
 * into the accumulator register, RA.
 */
void genpopd() {
	cgpopd();
}

//grw - added gen asm code statement
/* 
 * Print a string literal directly into the ouptput file
 * as a line of assembly language text
 */
void genasm(char * strlit) {
	char  asmText[TEXTLEN-2];
	char* p;
	
	/* find double quote at beginning of string literal */
	p = strchr(strlit, '"');
	/* if found, skip over, else set ptr to beginning of string literal */
	if (p)
	  p++; 
	else 
	  p = strlit;
			
	/* copy text into assembly buffer */
	strcpy(asmText, p);

	/* find the double quote at end of string literal */
	p = strrchr(asmText, '"');
	
	/* replace double quote at end with null */
	if (p) 
		*p = '\0';
	
	/* print the asm buffer text directly to file as a line */	
	if (NULL == Outfile) return;
	fprintf(Outfile, "%s\n", asmText);	
}
