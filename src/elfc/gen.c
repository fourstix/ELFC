/*
 *	NMH's Simple C Compiler, 2011--2016
 *	Code generator (emitter)
 */

#include "defs.h"
#include "data.h"
#include "decl.h"
#include "cgen.h"

//grw - removed clear logic
//int	Acc = 0;

//grw - removed clear logic
//void clear(int q) {
//	Acc = 0;
//	if (q) {
//		Q_type = empty;
//		Q_cmp = cnone;
//		Q_bool = bnone;
//	}
//}

//grw - removed load
//void load(void) {
//	Acc = 1;
//}

int label(void) {
	static int id = 1;

	return id++;
}

//grw - removed spill
//void spill(void) {
//	if (Acc) {
//		gentext();
//		cgpush();
//	}
//}

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

void sgen2(char *s, char *inst, int v, char *s2) {
	if (NULL == Outfile) return;
	fputc('\t', Outfile);
	fprintf(Outfile, s, inst, v, s2);
	fputc('\n', Outfile);
}

void genlab(int id) {
	if (NULL == Outfile) return;
	//grw - refactored Q_type to Q_jmp
	if (Q_jmp == jump) {
		if (Q_dest == id) {
			//grw - print comment instead of jump to next stmt
			ngen(";---- %s L%d falls through", "lbr", id);
		} else {
			//grw - if jump is to another label, output jump
			cgjump(Q_dest);
		}
		Q_jmp = jnone;
	}
	commit();
	//grw - proceed label with new line
	fprintf(Outfile, "\n%c%d:\n", LPREFIX, id);
}

char *labname(int id) {
	static char	name[100];

	sprintf(name, "%c%d", LPREFIX, id);
	return name;
}

char *gsym(char *s) {
	static char	name[NAMELEN+2];

	name[0] = PREFIX;
	copyname(&name[1], s);
	return name;
}

/* administrativa */

//grw - removed gendata
//void gendata(void) {
//	if (Textseg) cgdata();
//	Textseg = 0;
//}

//grw - removed gentext
//void gentext(void) {
//	if (!Textseg) cgtext();
//	Textseg = 1;
//}

void genprelude(void) {
	cgprelude();
	//grw - removed gentext
	//Textseg = 0;
	//gentext();
}

void genpostlude(void) {
	cgpostlude();
}

void genname(char *name) {
	char* pname;
	//grw - process name for library entry point and other lables
	if (O_library) {
	  pname = procname(Basefile);
		//grw - debug
		if (pname == NULL)
		  error("Proc Name is Null.", NULL);
			
	  if (!strcmp(gsym(name), pname)) {
		ngen(";---- library entry point %s", pname, 0);
		genlab(cgentrypt());
		return;
		} else {
		//grw - debug
		//printf("Other name: %s\n", name);
		//grw - commit any queued jump before generating label
		commit();
		}		
	}		
	//grw - debug 
	//printf("Generate %s name\n", name);
	genraw(gsym(name));
	genraw(":");
}

void genpublic(char *name) {
	char* pname;
	//grw - don't declare library entry point publics
	if (O_library) {
		pname = procname(Basefile);
		//grw - debug
		if (pname == NULL)
			error("Proc Name is Null.", NULL);

		if (!strcmp(gsym(name), pname)) {
			//grw - debug
			//printf("Public label supressed\n");
			return;
		}
  }
	cgpublic(gsym(name));
}


/* loading values */
void commit(void) {

	if (Q_cmp != cnone) {
		commit_cmp();
		return;
	}
	if (Q_bool != bnone) {
		commit_bool();
		return;
	}
	//grw - refactored Q_type to Q_jmp
	//if (empty == Q_type) return;
	
	if (Q_jmp != jnone) {
		cgjump(Q_dest);
		Q_jmp = jnone;
		return;
	}
	
	if (Q_push != pnone) {
		gen(";------ commit push");
		cgpushd();
		Q_push = pnone;
	}
	// grw - remove logic to queue address modes
  /*
  spill();
	switch (Q_type) {
	case addr_auto:		cgldla(Q_val); break;
	case addr_static:	cgldsa(Q_val); break;
	case addr_globl:	cgldga(gsym(Q_name)); break;
	case addr_label:	cgldlab(Q_val); break;
	case literal:		cglit(Q_val); break;
	case auto_byte:		cgclear(); cgldlb(Q_val); break;
	case auto_word:		cgldlw(Q_val); break;
	case static_byte:	cgclear(); cgldsb(Q_val); break;
	case static_word:	cgldsw(Q_val); break;
	case globl_byte:	cgclear(); cgldgb(gsym(Q_name)); break;
	case globl_word:	cgldgw(gsym(Q_name)); break;
	default:		fatal("internal: unknown Q_type");
	}
	*/
	//grw - remove load
	//load();
	//grw - refactored Q_type to Q_jmp
	//Q_type = empty;
}

//grw - remove logic to queue address modes
//grw - added logic to queue jump to label
//void queue(int type, int val, char *name) {
//	commit();
//	Q_type = type;
//	Q_val = val;
//	if (name) copyname(Q_name, name);
//}

void queue_jmp(int val) {
	commit();
	//grw - debug
	ngen(";---- queue %s L%d", "lbr", val);
	Q_jmp = jump;
	Q_dest = val;
}


void queue_push() {
	commit();
	//grw - debug
	gen(";---- queue dpush");
	Q_push = push;
}

void genaddr(int y) {
	//grw - removed gentext
	//gentext();
	if (CAUTO == Stcls[y])
		cgldla(Vals[y]);
		//grw - remove queue
		//queue(addr_auto, Vals[y], NULL);
	else if (CLSTATC == Stcls[y])
		cgldsa(Vals[y]);
  	//grw - remove queue
		//queue(addr_static, Vals[y], NULL);
	else
		cgldga(gsym(Names[y]));
	  //grw - remove queue
		//queue(addr_globl, 0, Names[y]);
}

void genldlab(int id) {
	//grw - remove queue
	//gentext();
	//queue(addr_label, id, NULL);
	cgldlab(id);
}

void genlit(int v) {
	//grw - remove queue
	//gentext();
	//queue(literal, v, NULL);
	cglit(v);
}

/* binary ops */

void genand(void) {
	//grw - removed gentext
	//gentext();
	cgand();
}

void genior(void) {
	//grw - removed gentext
	//gentext();
	cgior();
}

void genxor(void) {
	//grw - removed gentext
	//gentext();
	cgxor();
}

void genshl(int swapped) {
	//grw - removed gentext
	//gentext();
	//grw - removed cgload2 from logic
	//if (cgload2() || !swapped) cgswap();
	if (!swapped) cgswap();
	cgshl();
}

void genshr(int swapped) {
	//grw - removed gentext
	//gentext();
	//grw - removed cgload2 logic
	//if (cgload2() || !swapped) cgswap();
	if (!swapped) cgswap();
	cgshr();
}

static int ptr(int p) {
	int	sp;

	sp = p & STCMASK;
	return INTPTR == p || INTPP == p ||
		CHARPTR == p || CHARPP == p ||
		VOIDPTR == p || VOIDPP == p ||
		STCPTR == sp || STCPP == sp ||
		UNIPTR == sp || UNIPP == sp ||
		FUNPTR == p;
}

static int needscale(int p) {
	int	sp;

	sp = p & STCMASK;
	return INTPTR == p || INTPP == p || CHARPP == p || VOIDPP == p ||
		STCPTR == sp || STCPP == sp || UNIPTR == sp || UNIPP == sp;
}

int genadd(int p1, int p2, int swapped) {
 	int	rp = PINT, t;
  //grw - removed gentext
	//gentext();
	//grw - removed cgload2 logic
	//if (cgload2() || !swapped) {
	if (!swapped) {
		t = p1;
		p1 = p2;
		p2 = t;
	}
	if (ptr(p1)) {
		if (needscale(p1)) {
			if (	(p1 & STCMASK) == STCPTR ||
				(p1 & STCMASK) == UNIPTR
			)
				cgscale2by(objsize(deref(p1), TVARIABLE, 1));
			else
				cgscale2();
		}
		rp = p1;
	}
	else if (ptr(p2)) {
		if (needscale(p2)) {
			if (	(p2 & STCMASK) == STCPTR ||
				(p2 & STCMASK) == UNIPTR
			)
				cgscaleby(objsize(deref(p2), TVARIABLE, 1));
			else
				cgscale();
		}
		rp = p2;
	}
	cgadd();
	return rp;
}

int gensub(int p1, int p2, int swapped) {
	int	rp = PINT;
	//grw - removed gentext
	//gentext();
	//grw - removed cgload2 logic
	//if (cgload2() || !swapped) cgswap();
	if (!swapped) cgswap();
	if (!inttype(p1) && !inttype(p2) && p1 != p2)
		error("incompatible pointer types in binary '-'", NULL);
	if (ptr(p1) && !ptr(p2)) {
		if (needscale(p1)) {
			if (	(p1 & STCMASK) == STCPTR ||
				(p1 & STCMASK) == UNIPTR
			)
				cgscale2by(objsize(deref(p1), TVARIABLE, 1));
			else
				cgscale2();
		}
		rp = p1;
	}
	cgsub();
	if (needscale(p1) && needscale(p2)) {
		if (	(p1 & STCMASK) == STCPTR ||
			(p1 & STCMASK) == UNIPTR
		)
			cgunscaleby(objsize(deref(p1), TVARIABLE, 1));
		else
			cgunscale();
	}
	
	return rp;
}

void genmul(void) {
	//grw - removed gentext
	//gentext();
	//grw - removed cgload2 from logic
	//cgload2();
	cgmul();
}

void gendiv(int swapped) {
	//grw - removed gentext
	//gentext();
	//grw - removed cgload2 logic
	//if (cgload2() || !swapped) cgswap();
	if (!swapped) cgswap();
	cgdiv();
}

void genmod(int swapped) {
	//grw - removed gentext
	//gentext();
	//grw - removed cgload2 logic
	//if (cgload2() || !swapped) cgswap();
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
	else if (comptype(p1) || comptype(p2))
		/* fail */;
	else if (PVOID == p1 || PVOID == p2)
		/* fail */;
	else if (PLUS == op && (inttype(p1) || inttype(p2)))
		return;
	else if (MINUS == op && (!inttype(p1) || inttype(p2)))
		return;
	else if ((EQUAL == op || NOTEQ == op || LESS == op ||
		 GREATER == op || LTEQ == op || GTEQ == op)
		&&
		(p1 == p2 ||
		 (VOIDPTR == p1 && !inttype(p2)) ||
		 (VOIDPTR == p2 && !inttype(p1)))
	)
		return;
	error("invalid operands to binary operator", NULL);
}

void commit_cmp(void) {
	//grw
	gen(";----- commit_cmp");
	switch (Q_cmp) {
  	case equal:		cgeq(); break;
  	case not_equal:		cgne(); break;
  	case less:		cglt(); break;
  	case greater:		cggt(); break;
  	case less_equal:	cgle(); break;
  	case greater_equal:	cgge(); break;
  	case below:		cgult(); break;
  	case above:		cgugt(); break;
  	case below_equal:	cgule(); break;
  	case above_equal:	cguge(); break;
	}
	Q_cmp = cnone;
}

void queue_cmp(int op) {
  //grw  - debug
	gen(";----- queue_cmp");
	commit();
	Q_cmp = op;
}

int binoptype(int op, int p1, int p2) {
	binopchk(op, p1, p2);
	if (PLUS == op) {
		if (!inttype(p1)) return p1;
		if (!inttype(p2)) return p2;
	}
	else if (MINUS == op) {
		if (!inttype(p1)) {
			if (!inttype(p2)) return PINT;
			return p1;
		}
	}
	return PINT;
}

/* unary ops */
void commit_bool(void) {
	//grw
	gen(";----- commit_bool");
	switch (Q_bool) {
    case lognot:	cglognot(); break;
    case normalize:	cgbool(); break;
	}
	Q_bool = bnone;
}

void queue_bool(int op) {
  //grw  - debug
	gen(";----- queue_bool");	
	commit();
	Q_bool = op;
}

void genbool(void) {
	queue_bool(normalize);
}

void genlognot(void) {
	queue_bool(lognot);
}

void genind(int p) {
	//grw - removed gentext
	//gentext();
	commit();
	if (PCHAR == p)
		cgindb();
	else
		cgindw();
}

void genneg(void) {
	//grw - removed gentext
	//gentext();
	commit();
	cgneg();
}

void gennot(void) {
	//grw - removed gentext
	//gentext();
	commit();
	cgnot();
}

void genscale(void) {
	//grw - removed gentext
	//gentext();
	commit();
	cgscale();
}

void genscale2(void) {
	//grw - removed gentext
	//gentext();
	commit();
	cgscale2();
}

void genscaleby(int v) {
	//grw - removed gentext
	//gentext();
	commit();
	cgscaleby(v);
}

/* jump/call/function ops */

void genjump(int dest) {
	//grw - removed gentext
	//gentext();
	commit();
	//grw - added logic to queue jump to label
	//cgjump(dest);
	queue_jmp(dest);
}

void genbranch(int dest, int inv) {
	gen(";----- genbranch");
	if (inv) {
		switch (Q_cmp) {
		case equal:		cgbrne(dest); break;
		case not_equal:		cgbreq(dest); break;
		case less:		cgbrge(dest); break;
		case greater:		cgbrle(dest); break;
		case less_equal:	cgbrgt(dest); break;
		case greater_equal:	cgbrlt(dest); break;
		case below:		cgbruge(dest); break;
		case above:		cgbrule(dest); break;
		case below_equal:	cgbrugt(dest); break;
		case above_equal:	cgbrult(dest); break;
		}
	}
	else {
		switch (Q_cmp) {
		case equal:		cgbreq(dest); break;
		case not_equal:		cgbrne(dest); break;
		case less:		cgbrlt(dest); break;
		case greater:		cgbrgt(dest); break;
		case less_equal:	cgbrle(dest); break;
		case greater_equal:	cgbrge(dest); break;
		case below:		cgbrult(dest); break;
		case above:		cgbrugt(dest); break;
		case below_equal:	cgbrule(dest); break;
		case above_equal:	cgbruge(dest); break;
		}
	}
	Q_cmp = cnone;
}

void genlogbr(int dest, int inv) {
	if (normalize == Q_bool) {
		if (inv)
			cgbrfalse(dest);
		else
			cgbrtrue(dest);
	}
	else if (lognot == Q_bool) {
		if (inv)
			cgbrtrue(dest);
		else
			cgbrfalse(dest);
	}
	Q_bool = bnone;
}


void genbrfalse(int dest) {
	//grw - removed gentext
	//gentext();
	if (Q_cmp != cnone) {
		genbranch(dest, 0);
		return;
	}
	if (Q_bool != bnone) {
		genlogbr(dest, 1);
		return;
	}
	commit();
	cgbrfalse(dest);
}

void genbrtrue(int dest) {
	//grw - removed gentext
	//gentext();
	if (Q_cmp != cnone) {
		genbranch(dest, 1);
		return;
	}
	if (Q_bool != bnone) {
		genlogbr(dest, 0);
		return;
	}
	commit();
	cgbrtrue(dest);
}

void gencall(int y) {
	//grw - removed gentext
	//gentext();
	commit();
	cgcall(gsym(Names[y]));
	//grw - remove load
	//load();
}

void gencalr(void) {
	int n = label();
	//grw - removed gentext
	//gentext();
	commit();
	cgcalr(n);
	//grw - remove laod
	//load();
}

void genentry(void) {
	//grw - removed gentext
	//gentext();
	cgentry();
}

void genexit(void) {
	//grw - removed gentext
	//gentext();
	cgexit();
}

void genpush(void) {
	//grw - removed gentext
	//gentext();
	commit();
	cgpush();
}

void genpushlit(int n) {
	//grw - removed gentext
	//gentext();
	commit();
	//grw - removed spill
	//spill();
	cgpushlit(n);
}

void genstack(int n) {
	if (n) {
		//grw - removed gentext
		//gentext();
		cgstack(n);
	}
}

void genlocinit(void) {
	int	i;
  //grw - removed gentext
	//gentext();
	for (i=0; i<Nli; i++)
		cginitlw(LIval[i], LIaddr[i]);
}

/* data definitions */

void genbss(char *name, int len, int statc) {
	//grw - removed gendata
	//gendata();
  //grw - commit jump to entry point in library object
	if (O_library)
		commit();
	
	if (statc)
		cglbss(name, (len + INTSIZE-1) / INTSIZE * INTSIZE);
	else
		cggbss(name, (len + INTSIZE-1) / INTSIZE * INTSIZE);
}
//grw - removed genalign
//void genalign(int k) {
	//grw - removed gendata
	//gendata();
//	while (k++ % INTSIZE)
//		cgdefb(0);
//}
//grw - removed genaligntext
//void genaligntext() {
//	cgalign();
//}

void gendefb(int v) {
	//grw - removed gendata
	//gendata();
	//grw - commit jump to entry point in library object
	if (O_library)
		commit();

	cgdefb(v);
}

void gendefp(int v) {
	//grw - removed gendata
	//gendata();
	//grw - commit jump to entry point in library object
	if (O_library)
		commit();

	cgdefp(v);
}

void gendefs(char *s, int len) {
	//grw - replace with function for ASM/02
	/*
	int	i;

	gendata();
	for (i=1; i<len-1; i++) {
		if (isalnum(s[i]))
			cgdefc(s[i]);
		else
			cgdefb(s[i]);
	}
	*/
	//grw - commit jump to entry point in library object
	if (O_library)
		commit();

	cgdefs(s, len);	
}

void gendefw(int v) {
	//grw - removed gendata
	//gendata();
	//grw - commit jump to entry point in library object
	if (O_library)
		commit();

	cgdefw(v);
}

/* increment ops */

static void genincptr(int *lv, int inc, int pre) {
	int	y, size;

	size = objsize(deref(lv[LVPRIM]), TVARIABLE, 1);
	//grw - removed gentext
	//gentext();
	y = lv[LVSYM];
	commit();
	if (!y && !pre) cgldinc();
	if (!pre) {
		genrval(lv);
		commit();
	}
	if (!y) {
		if (pre)
			if (inc)
				cginc1pi(size);
			else
				cgdec1pi(size);
		else
			if (inc)
				cginc2pi(size);
			else
				cgdec2pi(size);
	}
	else if (CAUTO == Stcls[y]) {
		if (inc)
			cgincpl(Vals[y], size);
		else
			cgdecpl(Vals[y], size);
	}
	else if (CLSTATC == Stcls[y]) {
		if (inc)
			cgincps(Vals[y], size);
		else
			cgdecps(Vals[y], size);
	}
	else {
		if (inc)
			cgincpg(gsym(Names[y]), size);
		else
			cgdecpg(gsym(Names[y]), size);
	}
	if (pre) genrval(lv);
}

void geninc(int *lv, int inc, int pre) {
	int	y, b;

  //grw - removed gentext
	//gentext();
	y = lv[LVSYM];
	if (needscale(lv[LVPRIM])) {
		genincptr(lv, inc, pre);
		return;
	}
	b = PCHAR == lv[LVPRIM];
	/* will duplicate move to aux register in (*char)++ */
	commit();
	if (!y && !pre) cgldinc();
	if (!pre) {
		genrval(lv);
		commit();
	}
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
	if (pre) genrval(lv);
}

/* switch table generator */

void genswitch(int *vals, int *labs, int nc, int dflt) {
	int	i, ltbl;

	ltbl = label();
	//grw - removed gentext
	//gentext();
	cgldswtch(ltbl);
	cgcalswtch();
	genlab(ltbl);
	cgdefw(nc);
	for (i = 0; i < nc; i++)
		cgcase(vals[i], labs[i]);
	cgdefl(dflt);
}

/* assigments */

void genstore(int *lv) {
	if (NULL == lv) return;
	//grw - debug
	//ngen(";----- genstore %s = %d", "swapped", swapped);
	//ngen2(";----- genstore %s: lv = %d lv2 = %d", "lvars", lv[LVSYM], lv2[LVSYM]);
	//ngen2(";----- genstore %s: lv = %d lv2 = %d", "prim", lv[LVPRIM], lv2[LVPRIM]);
  //grw - removed gentext
	//gentext();
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

/* genrval computation */

void genrval(int *lv) {
	if (NULL == lv) return;
	//grw - removed gentext
	//gentext();
	if (!lv[LVSYM]) {
		genind(lv[LVPRIM]);
	}
	else if (CAUTO == Stcls[lv[LVSYM]]) {
		if (PCHAR == lv[LVPRIM])
		  //grw - remove queue
			//queue(auto_byte, Vals[lv[LVSYM]], NULL);
			cgldlb(Vals[lv[LVSYM]]);
		else
		  //grw - remove queue
			//queue(auto_word, Vals[lv[LVSYM]], NULL);
			cgldlw(Vals[lv[LVSYM]]);
	}
	else if (CLSTATC == Stcls[lv[LVSYM]]) {
		if (PCHAR == lv[LVPRIM])
		  //grw - remove queue
			//queue(static_byte, Vals[lv[LVSYM]], NULL);
			cgldsb(Vals[lv[LVSYM]]);
		else
		  //grw - remove queue
			//queue(static_word, Vals[lv[LVSYM]], NULL);
			cgldsw(Vals[lv[LVSYM]]);			
	}
	else {
		if (PCHAR == lv[LVPRIM])
		  //grw - remove queue
			//queue(globl_byte, 0, Names[lv[LVSYM]]);
			cgldgb(gsym(Names[lv[LVSYM]]));
		else
			//grw -remove queue
			//queue(globl_word, 0, Names[lv[LVSYM]]);
			cgldgw(gsym(Names[lv[LVSYM]]));
	}
}

//grw - added push data statement
/* 
 * Push  the value in the accumulator register, RA
 * to the TOS of the expression stack
 */
void genpushd() {
	commit();
	//grw - added logic to eliminate push followed by immediate pop
	//cgpushd();
	queue_push();
}

//grw - added pop data statement
/* 
 * Pop the value from the TOS of the expression stack
 * into the accumulator register, RA.
 */
void genpopd() {
	if (Q_push == push) {
		gen(";----- push + pop data not required, data remains unchanged in RA");
	  Q_push = pnone;
		commit();
	} else {
	  commit();
	  cgpopd();
	}
}

//grw - added gen asm code statement
/* 
 * Print a string literal directly into the ouptput file
 * as a line of assembly language text
 */
void genasm(char * strlit) {
	char  asmText[TEXTLEN-2];
	char* p;
	commit(); 
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
