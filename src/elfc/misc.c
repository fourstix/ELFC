/*
 *	NMH's Simple C Compiler, 2011,2014
 *	Miscellanea
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

void init(void) {
	Line = 1;
	Putback = '\n';
	Rejected = -1;
	Errors = 0;
	Mp = 0;
	Expandmac = 1;
	Syntoken = 0;
	Isp = 0;
	Inclev = 0;
	Globs = 0;
	Locs = NSYMBOLS;
	Nbot = 0;
	Ntop = POOLSIZE;
	Ndmax = 0;
	Bsp = 0;
	Csp = 0;
	//grw - removed Q_type added  Q_jmp and Q_push
	//Q_type = empty;
	Q_jmp = jnone;
	Q_push = pnone;
	Q_cmp = cnone;
	Q_bool = bnone;

	//grw - added string table
	str_idx = 0;

	//grw -  added support for local labels and goto
	llbl_idx = 0;

	addglob("", 0, 0, 0, 0, 0, NULL, 0);
	addglob("__SUBC__", 0, TMACRO, 0, 0, 0, globname(""), 0);
	if (!strcmp(OS, "DOS"))
		addglob("__dos", 0, TMACRO, 0, 0, 0, globname(""), 0);
	//grw - added macro def for Elf/OS
	else if (!strcmp(OS, "Elf/OS"))
			addglob("__elfos", 0, TMACRO, 0, 0, 0, globname(""), 0);
	else
		addglob("__unix", 0, TMACRO, 0, 0, 0, globname(""), 0);

	//grw - add predefined macros for line number and file name
	addglob("__LINE__", 0, TMACRO, 0, 0, 0, globname(""), 0);
	addglob("__FILE__", 0, TMACRO, 0, 0, 0, globname(""), 0);
	//grw - add predefined macro for function name
	addglob("__FUNCTION__", 0, TMACRO, 0, 0, 0, globname(""), 0);
	Infile = stdin;
	File = "(stdin)";
	Basefile = NULL;
	Outfile = stdout;
	opt_init();
}

int chrpos(char *s, int c) {
	char	*p;

	p = strchr(s, c);
	return (int)(p? p-s: -1);
}

void copyname(char *name, char *s) {
	strncpy(name, s, NAMELEN);
	name[NAMELEN] = 0;
}

void match(int t, char *what) {
	if (Token == t) {
		Token = scan();
	}
	else {
		error("%s expected", what);
	}
}

void lparen(void) {
	match(LPAREN, "'('");
}

void rparen(void) {
	match(RPAREN, "')'");
}

void lbrace(void) {
	match(LBRACE, "'{'");
}

void rbrace(void) {
	match(RBRACE, "'}'");
}

void rbrack(void) {
	match(RBRACK, "']'");
}

void semi(void) {
	match(SEMI, "';'");
}

void colon(void) {
	match(COLON, "':'");
}

void ident(void) {
	match(IDENT, "identifier");
}

int eofcheck(void) {
	if (XEOF == Token) {
		error("missing '}'", NULL);
		return 1;
	}
	return 0;
}

int inttype(int p) {
	//grw - added support for const keyword
	/* remove any type qualifier before comparing */
	p &= ~TQMASK;

	return PINT == p || PUINT == p || PCHAR == p || PSCHAR == p;
}

int comptype(int p) {
	p &= STCMASK;

	return p == PSTRUCT || p == PUNION;
}

void notvoid(int p) {
	if (PVOID == p)
		error("void value in expression", NULL);
}

int chartype(int p) {
	//grw - added support for const keyword
	/* remove any type qualifier bits before comparing */
	p &= ~TQMASK;
	return PCHAR == p || PSCHAR == p;
}

/* primitive int type */
int pinttype(int p) {
	/* remove any type qualifier before comparing */
	p &= ~TQMASK;
	return PINT == p || PUINT == p;
}

/* returns 1 if signed, 0 if unsigned */
int signtype(int p) {
	//grw - added support for const keyword
	/* remove any type qualifier before comparing */
	p &= ~TQMASK;
	/* only chararacter and unsigned integer are signed */
	return PCHAR != p && PUINT != p;
}

/* returns 1 if an unsgined opertor should be used */
int unsgnop(int p1, int p2) {
	//grw - added support for const keyword
	/* remove any type qualifier before comparing */
	p1 &= ~TQMASK;
	p2 &= ~TQMASK;
	/* unsigned op if either argument is an unsigned type */
	return (p1 == PUINT || p2 == PUINT || p1 == PCHAR || p2 == PCHAR);
}

/* returns the level of pointer indirection  */
/* 0 = not a pointer                         */
/* 1 = pointer to type                       */
/* 2 = pointer to pointer to type            */
/* 3 = pointer to pointer to ponter to type  */
/* and so on up to 15 levels                 */

int ptrlevel(int ptype) {
	int lvl;
	int stc;

	stc = ptype & STCMASK;

	if (stc) {
		if (stc == STCPTR || stc == UNIPTR) {
		  lvl = 1;
		} else if (stc == STCPP || stc == UNIPP) {
		  lvl = 2;
		} else {
			lvl = 0;
		}
	} else {
		if (FUNPTR == (ptype & TYPEMASK))
			lvl = 1;
		else
	    lvl = ((ptype & PTRMASK) >> 4);
	}
	return lvl;
}

/* Return the base type of indirect pointer */
int basetype(int ptype) {
	int stc;
	int btype = 0;

	stc = ptype & STCMASK;
	if (stc) {
		if (stc == STCPTR || 	stc == STCPP) {
			btype = PSTRUCT;
		} else if (stc == UNIPTR || stc == UNIPP) {
			btype = PUNION;
		} else {
			/* else it's PSTRUCT or PUNION */
			btype = stc;
		}
  } else {
		/* remove pointer count to get base type */
	    btype = ptype & TYPEMASK;
  }
	return btype;
}

/* Return true if ptype is a pointer to void */
int isvoidptr(int ptype) {
	int lvl;
	int vtype;
	lvl = ptrlevel(ptype);
	vtype = basetype(ptype);

	return ((lvl == 1) && (vtype == PVOID));
}

/* Return true if ptype is a pointer to function */
int isfunptr(int ptype) {
	/* int lvl; */
	int ftype;
	//grw - ignore multiple indirection for now
	/* lvl = ptrlevel(ptype); */
	ftype = basetype(ptype);

	return (ftype == FUNPTR);
}


/* Set the type with a new level of pointer indirection */
int setptrlevel(int ptype, int lvl) {
	int newval;

	/* shift level into second nibble position */
	newval = lvl << 4;

	/* clear out the old value */
	ptype &= ~PTRMASK;
	/* set the pointer level to new value */
	ptype |= newval;

	return ptype;
}

/* check to see if pointers are compatible */
int compatible(int p1, int p2) {
	int lvl_1;
	int lvl_2;
	int stc;

	/* get the level for the pointers */
	lvl_1 = ptrlevel(p1);
	lvl_2 = ptrlevel(p2);

	/* if either value is not a pointer,
	 *  then indicate compatible for pointer arithmetic
	 */
	if (!lvl_1 || !lvl_2)
	  return 1;

	/* If the pointers are different levels,
	 * then they are not compatible
	 */
	if (lvl_1 != lvl_2)
	  return 0;

	/* check to see if comparing struct/union pointers */
	stc = p1 & STCMASK;

	/* const keyword is ignored for pointers to struct/union */
	if (!stc) {
		/* constant pointers compatible with non-constant pointers */
   	/* so remove any constant bits before comparing */
    p1 &= ~TQMASK;
	  p2 &= ~TQMASK;
  }
 return (p1 == p2);
}
