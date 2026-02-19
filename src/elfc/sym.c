/*
 *	NMH's Simple C Compiler, 2011--2021
 *	Symbol table management
 */

#include "defs.h"
#include "data.h"
#include "decl.h"
#include "cgen.h"

int findglob(char *s) {
	int	i;

	for (i=0; i<Globs; i++) {
		if (	Types[i] != TMACRO && Stcls[i] != CMEMBER &&
			*s == *Names[i] && !strcmp(s, Names[i])
		)
			return i;
	}
	return 0;
}

int findloc(char *s) {
	int	i;

	for (i=Locs; i<NSYMBOLS; i++) {
		if (	Stcls[i] != CMEMBER &&
			*s == *Names[i] && !strcmp(s, Names[i])
		)
			return i;
	}
	return 0;
}

int findsym(char *s) {
	int	y;

	if ((y = findloc(s)) != 0) return y;
	return findglob(s);
}

int findmac(char *s) {
	int	i;

	for (i=0; i<Globs; i++)
		if (	TMACRO == Types[i] &&
			*s == *Names[i] && !strcmp(s, Names[i])
		)
			return i;
	return 0;
}

int findstruct(char *s) {
	int	i;

	for (i=Locs; i<NSYMBOLS; i++)
		if (	TSTRUCT == Types[i] &&
			*s == *Names[i] && !strcmp(s, Names[i])
		)
			return i;
	for (i=0; i<Globs; i++)
		if (	TSTRUCT == Types[i] &&
			*s == *Names[i] && !strcmp(s, Names[i])
		)
			return i;
	return 0;
}

int findmem(int y, char *s) {
	y++;
	while (	(y < Globs ||
		 (y >= Locs && y < NSYMBOLS)) &&
		CMEMBER ==  Stcls[y]
	) {
		if (*s == *Names[y] && !strcmp(s, Names[y]))
			return y;
		y++;
	}
	return 0;
}

int newglob(void) {
	int	p;

	if ((p = Globs++) >= Locs)
		fatal("too many global symbols");
	return p;
}

int newloc(void) {
	int	p;

	if ((p = --Locs) <= Globs)
		fatal("too many local symbols");
	return p;
}

#ifdef __SUBC__
 #define PTR_INT_CAST	(int)
#else
 #define PTR_INT_CAST	(int) (long long)
#endif

char *galloc(int k, int align) {
	int	p, mask;

	k += align * sizeof(int);
	if (Nbot + k >= Ntop)
		fatal("out of space for symbol names");
	p = Nbot;
	Nbot += k;
	mask = sizeof(int)-1;
	if (align)
		while (PTR_INT_CAST &Nlist[p] & mask)
			p++;
	return &Nlist[p];
}

char *globname(char *s) {
	char	*p;

	p = galloc((int)strlen(s)+1, 0);
	strcpy(p, s);
	return p;
}

char *locname(char *s) {
	int	p, k;

	k = (int)(strlen(s) + 1);
	if (Nbot + k >= Ntop)
		fatal("out of space for symbol names");
	Ntop -= k;
	p = Ntop;
	strcpy(&Nlist[p], s);
	return &Nlist[p];
}

static void defglob(char *name, int prim, int type, int size, int val,
			int scls, int init)
{
	int	st;

	if (TCONSTANT == type || TFUNCTION == type) return;

	st = scls == CSTATIC;
	if (CPUBLIC == scls) genpublic(name);

	if (init && TARRAY == type)
	  return;

	if (TARRAY != type && !(prim & STCMASK)) genname(name);
	if (prim & STCMASK) {
		if (TARRAY == type)
			genbss(gsym(name), objsize(prim, TARRAY, size), st);
		else
			genbss(gsym(name), objsize(prim, TVARIABLE, size), st);
	}
	/* check to see if char ptr initialized with string */
	if (prim == (PCHAR | 0x0010) && init == -1)
		gendefpstr(val);
	else if (chartype(prim)) {
		if (TARRAY == type)
			genbss(gsym(name), size, st);
		else {
			  gendefb(val);
		}
	}
	else if (pinttype(prim)) {
		if (TARRAY == type)
			genbss(gsym(name), size*INTSIZE, st);
		else
			gendefw(val);
	}
	else {
		if (TARRAY == type)
			genbss(gsym(name), size*PTRSIZE, st);
		else
			gendefp(val);
	}
}

int redeclare(char *name, int oldcls, int newcls) {
	switch (oldcls) {
	case CEXTERN:
		if (newcls != CPUBLIC && newcls != CEXTERN)
			error("extern symbol redeclared static: %s", name);
		return newcls;
	case CPUBLIC:
		if (CEXTERN == newcls)
			return CPUBLIC;
		if (newcls != CPUBLIC) {
			error("extern symbol redeclared static: %s", name);
			return CPUBLIC;
		}
		break;
	case CSPROTO:
		if (newcls != CSTATIC && newcls != CSPROTO)
			error("static symbol redeclared extern: %s", name);
		return newcls;
	case CSTATIC:
		if (CSPROTO == newcls)
			return CSTATIC;
		if (newcls != CSTATIC) {
			error("static symbol redeclared extern: %s", name);
			return CSTATIC;
		}
		break;
	case CTYPE:
		error("redefinition of typedef name", Text);
		return CTYPE;
		break;
	}
	error("redefined symbol: %s", name);
	return newcls;
}

int addglob(char *name, int prim, int type, int scls, int size, int val,
		char *mtext, int init)
{
	int	y;
	if (0 == *name)
		y = 0;
	else if ((y = findglob(name)) != 0) {
		scls = redeclare(name, Stcls[y], scls);
		if (CTYPE == scls) return y;
		if (TFUNCTION == Types[y])
			mtext = Mtext[y];
	}
	if (0 == y) {
 		y = newglob();
		Names[y] = globname(name);
	}
	else if (TFUNCTION == Types[y] || TMACRO == Types[y]) {
		if (Prims[y] != prim || Types[y] != type)
			error("redefinition does not match prior type: %s",
				name);
	}
	if (CPUBLIC == scls || CSTATIC == scls)
		defglob(name, prim, type, size, val, scls, init);
	Prims[y] = prim;
	Types[y] = type;
	Stcls[y] = scls;
	Sizes[y] = size;
	Vals[y] = val;
	Mtext[y] = mtext;
	return y;
}

static void defloc(int prim, int type, int size, int val, int init) {
	if (type != TARRAY && !(prim &STCMASK)) genlab(val);
	if (prim & STCMASK) {
		if (TARRAY == type)
			genbss(labname(val), objsize(prim, TARRAY, size), 1);
		else
			genbss(labname(val), objsize(prim, TVARIABLE, size),1);
	} else if (prim == (PCHAR | 0x0010)) {
		if (init) {
			gendefpstr(init);
		} else {
			gendefw(init);
		}

  } else if (chartype(prim)) {
	//grw - added support to iniitialze global and static arrays
		/* if (TARRAY == type) */
		if (TARRAY == type) {
			/* if not initialized, reserve space */
			if(!init)
			  genbss(labname(val), size, 1);
		} else {
			gendefb(init);
			//grw - removed genalign
			//genalign(1);
		}
	}
	//grw - update to use pinttype
	else if (pinttype(prim)) {
	/* else if (PINT == prim) { */
	//grw - added support to iniitialze global and static arrays
		/* if (TARRAY == type) */
		if (TARRAY == type) {
			/* if not initialized, reserve space */
			if(!init)
			  genbss(labname(val), size*INTSIZE, 1);
		} else {
			gendefw(init);
		}
	}
	else {
		/* arrays of pointers are not initialized */
		if (TARRAY == type)
			genbss(labname(val), size*PTRSIZE, 1);
		else
			gendefp(init);
	}
}

int addloc(char *name, int prim, int type, int scls, int size, int val,
		int init)
{
	int	y;

	if (findloc(name))
		error("redefinition of: %s", name);
 	y = newloc();
	if (CLSTATC == scls) defloc(prim, type, size, val, init);
	Names[y] = locname(name);
	Prims[y] = prim;
	Types[y] = type;
	Stcls[y] = scls;
	Sizes[y] = size;
	Vals[y] = val;
	return y;
}

void clrlocs(void) {
	Ntop = POOLSIZE;
	Locs = NSYMBOLS;
}

int objsize(int prim, int type, int size) {
	int	k = 0, sp;

	sp = prim & STCMASK;

	//grw - converted to use chartype and pinttype
	if (chartype(prim))
		k = CHARSIZE;
  else if (pinttype(prim))
  	k = INTSIZE;
	else if (STCPTR == sp || STCPP == sp)
		k = PTRSIZE;
	else if (UNIPTR == sp || UNIPP == sp)
		k = PTRSIZE;
	else if (PSTRUCT == sp || PUNION == sp)
		k = Sizes[prim & ~STCMASK];
	/* ptrlevel covers function pointer case */
	else if (ptrlevel(prim) > 0)
	  k = PTRSIZE;
	if (TFUNCTION == type || TCONSTANT == type || TMACRO == type)
		return -1;
	if (TARRAY == type)
		k *= size;
	return k;
}

static char *typename(int p) {
	//grw - added support for multiple pointer indirection
  static char tname[12];
	int lvl;
	int btype;

	switch (p & STCMASK) {
	case PSTRUCT:	return "STRUCT";
	case STCPTR:	return "STCT*";
	case STCPP:	return "STCT**";
	case PUNION:	return "UNION";
	case UNIPTR:	return "UNIO*";
	case UNIPP:	return "UNIO**";
	}
	lvl = ptrlevel(p);
	btype = basetype(p);

	if (btype == PINT) strcpy(tname, "INT");
	else if (btype == PUINT) strcpy(tname, "UINT");
	else if (btype == PCHAR) strcpy(tname, "CHAR");
	else if (btype == PSCHAR) strcpy(tname, "SCHAR");
	else if (btype == PVOID) strcpy(tname, "VOID");
	else if (btype == FUNPTR) return "FUN*";
	else return "n/a";

	if (lvl > 3) {
		/* indicate higher than triple pointer */
		strcat(tname, "***+");
	} else {
		/* add up to 3 stars */
  	while (lvl > 1) {
	  	strcat(tname, "*");
			lvl--;
		}
	}
  return tname;
	//grw - added support for signed and unsigned
  /*
	return	PINT    == p? "INT":
		PCHAR   == p? "CHAR":
		PSCHAR   == p? "SCHAR":
 	  PUINT    == p? "UINT":
		INTPTR  == p? "INT*":
		CHARPTR == p? "CHAR*":
		UINTPTR  == p? "UINT*":
		SCHARPTR == p? "SCHAR*":
		VOIDPTR == p? "VOID*":
		FUNPTR  == p? "FUN*":
		INTPP   == p? "INT**":
		CHARPP  == p? "CHAR**":
		UINTPP   == p? "UINT**":
		SCHARPP  == p? "SCHAR**":
		VOIDPP  == p? "VOID**":
		PVOID   == p? "VOID": "n/a";
		*/
}

void dumpsyms(char *title, char *sub, int from, int to) {
	int	i;
	int	*p;

	printf("\n===== %s%s =====\n", title, sub);
	printf(	"PRIM    TYPE  STCLS   SIZE  VALUE  NAME [MVAL]/(SIG)\n"
		"------  ----  -----  -----  -----  -----------------\n");
	for (i = from; i < to; i++) {
		printf("%-6s  %s  %s  %5d  %5d  %s",
			typename(Prims[i]),
			TVARIABLE == Types[i]? "VAR ":
				TARRAY == Types[i]? "ARRY":
				TFUNCTION == Types[i]? "FUN ":
				TCONSTANT == Types[i]? "CNST":
				TMACRO == Types[i]? "MAC ":
				TSTRUCT == Types[i]? "STCT": "n/a",
			CPUBLIC == Stcls[i]? "PUBLC":
				CEXTERN == Stcls[i]? "EXTRN":
				CSTATIC == Stcls[i]? "STATC":
				CSPROTO == Stcls[i]? "STATP":
				CLSTATC == Stcls[i]? "LSTAT":
				CAUTO   == Stcls[i]? "AUTO ":
				CMEMBER == Stcls[i]? "MEMBR":
				CTYPE   == Stcls[i]? "TYPE ": "n/a  ",
			Sizes[i],
			Vals[i],
			Names[i]);
		if (TMACRO == Types[i])
			printf(" [\"%s\"]", Mtext[i]);
		if (TFUNCTION == Types[i]) {
			printf(" (");
			for (p = (int *) Mtext[i]; *p; p++) {
				printf("%s", typename(*p));
				if (p[1]) printf(", ");
			}
			putchar(')');
		}
		putchar('\n');
	}
}

//grw - added support for local labels and goto
int findLocalLabel(int scope, char *text) {
	int idx;
	int llid = 0;

	for (idx = 0; idx < llbl_idx; idx++) {
		/* find the matching label in the function */
		if ((lcl_lbls[idx].scope == scope) && !strcmp(lcl_lbls[idx].text, text)) {
			llid = idx + 1;
			break;
		}
	}
	return llid;
}

//grw - moved warning suppression to NMake file

//grw - added support for local labels and goto
int addLocalLabel(int fn, char *text, int defined) {
	int llid = 0;

	if (llbl_idx < MAXUSRLBL) {
		lcl_lbls[llbl_idx].scope = fn;
		/* need to duplicate strings since text is overwritten */
		lcl_lbls[llbl_idx].text  = strdup(text);
		lcl_lbls[llbl_idx].defined = defined;
		llbl_idx++;
		llid = llbl_idx;
	} else {
		error("Too many local labels.", NULL);
	}
return llid;
}

/*
 * find arguments for a macro and
 * load arguments into mhide array
 */
int findargs(int id) {
	int idx;
	int count = 0;
	for(idx = 0; idx < Margp; idx++) {
		if (Margs[idx].id == id) {
			Mhide[count] = Margs[idx].text;
			count++;
		}
	}
	return count;
}

/*
 * Test for global Types
 */
int isglobal(int scls) {
	return (CPUBLIC == scls || CSTATIC == scls);
}
