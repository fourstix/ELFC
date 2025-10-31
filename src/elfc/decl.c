/*
 *	NMH's Simple C Compiler, 2011--2022
 *	Declaration parser
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

static int declarator(int arg, int scls, char *name, int *pprim, int *psize,
			int *pval, int *pinit);

/*
 * enumdecl := { enumlist } ;
 *
 * enumlist :=
 *	  enumerator
 *	| enumerator , enumlist
 *
 * enumerator :=
 *	  IDENT
 *	| IDENT = constexpr
 */

static void enumdecl(int glob) {
	int	v = 0;
	char	name[NAMELEN+1];

	Token = scan();
	if (IDENT == Token)
		Token = scan();
	lbrace();
	while (RBRACE != Token) {
		copyname(name, Text);
		ident();
		if (ASSIGN == Token) {
			Token = scan();
			v = constexpr();
		}
		if (glob)
			addglob(name, PINT, TCONSTANT, 0, 0, v++, NULL, 0);
		else
			addloc(name, PINT, TCONSTANT, 0, 0, v++, 0);
		if (Token != COMMA)
			break;
		Token = scan();
		if (eofcheck()) return;
	}
	rbrace();
	semi();
}

/*
 * initlist :=
 *	  { const_list }
 *	| STRLIT
 *
 * const_list :=
 *	  constexpr
 *	| constexpr , const_list
 */

static int initlist(char *name, int prim) {
	int	n = 0, v;
	char	buf[30];

	//grw - removed gendata
	//gendata();
	genname(name);
	if (STRLIT == Token) {
		// if (PCHAR != prim)
		if (!chartype(prim))
			error("initializer type mismatch: %s", name);
    //grw - update to allow concatenation of string literals
		v = 0;
		while (STRLIT == Token) {
			gendefs(Text, Value);
			v += Value;
			Token = scan();
		}
		gendefb(0);

		//grw - update to allow concatenation of string literals
		//gendefs(Text, Value);
		//gendefb(0);

		//grw - removed genalign
		//genalign(Value-1);

		//grw - update to allow concatenation of string literals
		//Token = scan();
		//return Value-1;
		return v-1;
	}
	lbrace();
	while (Token != RBRACE) {
		v = constexpr();
		//grw - add support for const keyword
		/* if (PCHAR == prim) { */
		if (PCHAR == (prim & ~CNSTMASK)) {
			if (v < 0 || v > 255) {
				sprintf(buf, "%d", v);
				error("initializer out of range: %s", buf);
			}
			gendefb(v);
		} else if (PSCHAR == (prim & ~CNSTMASK)) {
			//grw - add support for const keyword
		/* } else if (PSCHAR == prim) { */
			if (v < -128 || v > 127) {
				sprintf(buf, "%d", v);
				error("initializer out of range: %s", buf);
			}
			gendefb(v);
		} else {
			gendefw(v);
		}
		n++;
		if (COMMA == Token)
			Token = scan();
		else
			break;
		if (eofcheck()) return 0;
	}
	//grw - removed genalign
	//if (PCHAR == prim) genalign(n);
	Token = scan();
	if (!n) error("too few initializers", NULL);
	return n;
}

int primtype(int t, char *s) {
	int	p, y;
	char	sname[NAMELEN+1];
  //grw - added signed and unsigned types
	p = t == CHAR? PCHAR:
	  t == SCHAR? PSCHAR:
		t == INT? PINT:
		t == UINT? PUINT:
		t == STRUCT? PSTRUCT:
		t == UNION? PUNION:
		PVOID;
	if (PUNION == p || PSTRUCT == p) {
		if (!s) {
			Token = scan();
			copyname(sname, Text);
			s = sname;
			if (IDENT != Token) {
				error("struct/union name expected: %s", Text);
				return p;
			}
		}
		if ((y = findstruct(s)) == 0 || Prims[y] != p)
			error("no such struct/union: %s", s);
		p |= y;
	}
	return p;
}

int usertype(char *s) {
	int	y;
	if ((y = findsym(s)) == 0)
		return 0;
	return CTYPE == Stcls[y]? y: 0;
}

/*
 * pmtrdecl :=
 *	  ( )
 *	| ( pmtrlist )
 *	| ( pmtrlist , ... )
 *
 * pmtrlist :=
 *	  primtype declarator
 *	| primtype declarator , pmtrlist
 *	| usertype declarator
 *	| usertype declarator , pmtrlist
 *
 * usertype :=
 *	  TYPEDEF_NAME
 */

static int pmtrdecls(void) {
	char	name[NAMELEN+1];
	int	utype, prim, type, size, na, addr;
	int	dummy;
	//grw - added support for const keyword
	int cnst;

	if (RPAREN == Token)
		return 0;
	na = 0;
	//grw - our stack frome does not include ret address nor frame address
	//addr = 2*BPW;
	addr = 0;
	//grw - added support for const keyword
	cnst = 0;
	for (;;) {
		utype = 0;
		if (na > 0 && ELLIPSIS == Token) {
			Token = scan();
			na = -(na + 1);
			break;
		}
		else if (CONST == Token) {
			cnst = 1;
			Token = scan();
			continue;
		}
		else if (IDENT == Token &&
			 (utype = usertype(Text)) == 0)
		{
			prim = PINT;
			if (cnst)
			  prim |= CNSTMASK;
		}
		else {
			//grw - added signed and unsigned types
			if (	CHAR == Token || INT == Token ||
				SCHAR == Token || UINT == Token || VOID == Token ||
				STRUCT == Token || UNION == Token ||
				(IDENT == Token && utype != 0)
			) {
				name[0] = 0;
				prim = utype? Prims[utype]:
					primtype(Token, NULL);
				//grw - added support for const keyword
				//grw - in a function, the const value is considered initialized
				if (cnst) {
					if (prim & STCMASK)
						warn("const keyword ignored for struct/union types", NULL);
					else if (utype) {
					  error("const keyword not valid before user defined types", NULL);
					} else
						prim |= CNSTMASK;
				}
				Token = scan();
				if (RPAREN == Token && prim == PVOID && !na)
					return 0;
			}
			else {
				error("type specifier expected at: %s", Text);
				Token = synch(RPAREN);
				return na;
			}
		}
		size = 1;
		type = declarator(1, CAUTO, name, &prim, &size, &dummy,
				&dummy);
		if ((utype && TARRAY == Types[utype]) || TARRAY == type) {
			prim = pointerto(prim);
			type = TVARIABLE;
		}
		addloc(name, prim, type, CAUTO, size, addr, 0);
		addr += BPW;
		na++;
		if (COMMA == Token) {
			Token = scan();
			//grw - added support for const keyword
			/* reset constant flag */
			cnst = 0;
		}	else
			break;
	}
	return na;
}

int pointerto(int prim) {
	int	y;
	//grw - added support for multiple pointer indirection
	int lvl;

	lvl = ptrlevel(prim);

	if (lvl >= MAXPTR || (prim & TYPEMASK) == FUNPTR ||
	    (prim & STCMASK) == STCPP || (prim & STCMASK) == UNIPP )
		error("too many levels of indirection", NULL);

	/*
	if (CHARPP == prim || INTPP == prim || VOIDPP == prim ||
	    SCHARPP == prim || UINTPP == prim ||FUNPTR == prim ||
	    (prim & STCMASK) == STCPP || (prim & STCMASK) == UNIPP
	)
		error("too many levels of indirection", NULL);
	*/
	y = prim & ~STCMASK;
	switch (prim & STCMASK) {
	case PSTRUCT:	return STCPTR | y;
	case STCPTR:	return STCPP | y;
	case PUNION:	return UNIPTR | y;
	case UNIPTR:	return UNIPP | y;
	}
	//grw - added support for multiple pointer indirection
	if (lvl < MAXPTR)
	  lvl++;
	return setptrlevel(prim, lvl);
/*
	return PINT == prim? INTPTR:
	  PUINT == prim? UINTPTR:
		PCHAR == prim? CHARPTR:
		PSCHAR == prim? SCHARPTR:
		PVOID == prim? VOIDPTR:
		INTPTR == prim? INTPP:
		UINTPTR == prim? UINTPP:
		CHARPTR == prim? CHARPP:
		SCHARPTR == prim? SCHARPP: VOIDPP;
*/
}

/*
 * declarator :=
 *	  IDENT
 *	| * IDENT
 *	| * * IDENT
 *	| * IDENT [ constexpr ]
 *	| IDENT [ constexpr ]
 *	| IDENT = constexpr
 *	| IDENT [ ] = initlist
 *	| IDENT pmtrdecl
 *	| IDENT [ ]
 *	| * IDENT [ ]
 *	| ( * IDENT ) ( )
 */

static int declarator(int pmtr, int scls, char *name, int *pprim, int *psize,
			int *pval, int *pinit)
{
	int	type = TVARIABLE;
	int	ptrptr = 0;
	char	*unsupp;

	unsupp = "unsupported typedef syntax";
	if (STAR == Token) {
		Token = scan();
		*pprim = pointerto(*pprim);
		//grw - added support for multiple pointer indirection
		while (STAR == Token) {
			Token = scan();
			*pprim = pointerto(*pprim);
			ptrptr++;
		}
/*
		if (STAR == Token) {
			Token = scan();
			*pprim = pointerto(*pprim);
			ptrptr = 1;
		}
*/
	}
	else if (LPAREN == Token) {
		if (CTYPE == scls)
			error(unsupp, NULL);
		if (*pprim != PINT)
			error("function pointers are limited to type 'int'",
				NULL);
		Token = scan();
		*pprim = FUNPTR;
		match(STAR, "(*name)()");
	}
	if (IDENT != Token) {
		error("missing identifier at: %s", Text);
		name[0] = 0;
	}
	else {
		copyname(name, Text);
		Token = scan();
	}
	if (FUNPTR == *pprim) {
		rparen();
		lparen();
		rparen();
	}
	if (!pmtr && ASSIGN == Token) {
		if (CTYPE == scls)
			error(unsupp, NULL);
		Token = scan();
		*pval = constexpr();
		//grw - convert to use chartype()
		/* if (PCHAR == *pprim || PSCHAR == *pprim) */

		if (chartype(*pprim))
			*pval &= 0xff;
		//grw - allow non-zero pointer initialization
	 	/*	if (*pval && !inttype(*pprim))
		  error("non-zero pointer initialization", NULL);	*/
		*pinit = 1;
		//grw - added support for const keyword
		if (CNST == (*pprim & CNSTMASK))
			*pprim |= CINIT;
	}
	else if (!pmtr && LPAREN == Token) {
		if (CTYPE == scls)
			error(unsupp, NULL);
		Token = scan();
		*psize = pmtrdecls();
		rparen();
		return TFUNCTION;
	}
	else if (LBRACK == Token) {
		//grw - added support for multiple pointer indirection
		/* if (ptrptr) */
		if (ptrptr > MAXPTR)
			error("too many levels of indirection: %s", name);
    if (*pprim & CNSTMASK) {
			//grw - clear unused constant bits for array types
			*pprim &= ~CNSTMASK;
  		warn("const keyword ignored for array %s", name);
    }
		Token = scan();
		if (RBRACK == Token) {
			if (CTYPE == scls)
				error(unsupp, NULL);
			Token = scan();
			if (pmtr) {
				*pprim = pointerto(*pprim);
			}
			else {
				type = TARRAY;
				*psize = 1;
				if (ASSIGN == Token) {
					Token = scan();
					if (!inttype(*pprim))
						error("initialization of"
							" pointer array not"
							" supported",
							NULL);
					*psize = initlist(name, *pprim);
					if (CAUTO == scls)
						error("initialization of"
							" local arrays"
							" not supported: %s",
							name);
					*pinit = 1;
				}
				else if (CEXTERN != scls) {
					error("automatically-sized array"
						" lacking initialization: %s",
						name);
				}
			}
		}
		else {
			*psize = constexpr();
			if (*psize < 1) {
				error("invalid array size", NULL);
				*psize = 0;
			}
			type = TARRAY;
			rbrack();
		}
	}
	if (PVOID == *pprim)
		error("'void' is not a valid type: %s", name);
	return type;
}

int upgrade_array(int utype, int type, int *size) {
	if (utype && TARRAY == Types[utype]) {
		if (TARRAY == type)
			error("unsupported typedef (array of array)", NULL);
		*size = *size? *size * Sizes[utype]: Sizes[utype];
		return TARRAY;
	}
	return type;
}

/*
 * localdecls :=
 *        ldecl
 *      | ldecl localdecls
 *
 * ldecl :=
 *	  primtype ldecl_list ;
 *	| usertype ldecl_list ;
 *	| lclass primtype ldecl_list ;
 *	| lclass ldecl_list ;
 *	| enum_decl
 *	| struct_decl
 *
 * lclass :=
 *	| AUTO
 *	| EXTERN
 *	| REGISTER
 *	| STATIC
 *	| VOLATILE
 *	| CONST
 *
 * ldecl_list :=
 *	  declarator
 *	| declarator , ldecl_list
 */

static int localdecls(void) {
	char	name[NAMELEN+1];
	int	utype, prim, type, size, addr = 0, val, ini;
	//grw - added support for const keyword
	int	stat, extn, cnst, rgstr;
	int	pbase, rsize;

	Nli = 0;
	utype = 0;
	//grw - added signed and unsigned types
	//grw - added support for const keyword
	while ( AUTO == Token || EXTERN == Token || REGISTER == Token ||
		STATIC == Token || VOLATILE == Token || CONST == Token ||
		INT == Token || CHAR == Token || VOID == Token ||
		SCHAR == Token || UINT == Token ||
		ENUM == Token ||
		STRUCT == Token || UNION == Token ||
		(IDENT == Token && (utype = usertype(Text)) != 0)
	) {
		if (ENUM == Token) {
			enumdecl(0);
			continue;
		}
		extn = stat = 0;
		//grw - added support for const keyword
		cnst = rgstr = 0;
		if (AUTO == Token || REGISTER == Token || STATIC == Token ||
			//grw - added support for const keyword
			VOLATILE == Token || CONST == Token || EXTERN == Token ) {
			stat  = STATIC == Token;
			extn  = EXTERN == Token;
			//grw - added support for const keyword
			cnst  = CONST == Token;
			rgstr = REGISTER == Token;
			Token = scan();
			//grw - added support for const keyword
			/* static/extern const, const static/extern are valid qualifiers */
			if ((stat || extn) && (CONST == Token)) {
				cnst = 1;
				Token = scan();
			} else if (cnst) {
				  if (STATIC == Token || EXTERN == Token) {
						stat = STATIC == Token;
						extn = EXTERN == Token;
						Token = scan();
			    } else if (REGISTER == Token){
					  error ("\'const register\' is not a legal type qualifier", NULL);
						Token = scan();
					}
			} else if (cnst && (AUTO == Token || VOLATILE == Token)) {
				/* auto and volatile after const are valid, but ignored */
				Token = scan();
			} else if (!cnst && (Token == CONST)) {
				/* const after (ignored) auto and volatile is valid */
				cnst = 1;
				Token = scan();
				/* but const and register are not valid together */
				if (rgstr) {
					error ("\'register const\' is not a legal type qualifier", NULL);
				}
			}

			//grw - const is not valid before user types (but okay within)
			if (cnst && utype)
				error("const keyword not valid with user defined types", NULL);

			if (INT == Token || CHAR == Token ||
				//grw - added signed and unsigned types
        SCHAR == Token || UINT == Token ||
				VOID == Token ||
				STRUCT == Token || UNION == Token
			) {
				prim = primtype(Token, NULL);
				//grw - added support for const keyword
				if (cnst) {
					if (prim & STCMASK)
					  warn("const keyword ignored for struct/union types", NULL);
					else
				    prim |= CNST;
				}
				Token = scan();
			}
			else if (utype) {
				prim = Prims[utype];
			}
			else {
  		  prim = PINT;
				//grw - added support for const keyword
				if (cnst)
					prim |= CNST;
			}
		}
		else if (utype) {
			prim = Prims[utype];
			Token = scan();
		}
		else {
			prim = primtype(Token, NULL);
			Token = scan();
		}
		pbase = prim;
		for (;;) {
			prim = pbase;
			if (eofcheck()) return 0;
			size = 1;
			ini = val = 0;
			type = declarator(0, CAUTO, name, &prim, &size,
					&val, &ini);
			type = upgrade_array(utype, type, &size);
			rsize = objsize(prim, type, size);
			rsize = (rsize + INTSIZE-1) / INTSIZE * INTSIZE;
			if (stat) {
				addloc(name, prim, type, CLSTATC, size,
					label(), val);
			}
			else if (extn) {
				addloc(name, prim, type, CEXTERN, size,
					0, val);
			}
			else {
				//grw - need to pad struct/union at top of list in case its returned
				if (!addr && (prim & STCMASK)) {
					addloc("_pad", PINT, TVARIABLE, CAUTO, 2, 0, 0);
					addr -= BPW;
				}
				addr -= rsize;
				addloc(name, prim, type, CAUTO, size, addr, 0);
			}
			if (ini && !stat) {
				if (Nli >= MAXLOCINIT) {
					error("too many local initializers",
						NULL);
					Nli = 0;
				}
				LIaddr[Nli] = addr;
				LIval[Nli++] = val;
			}
			if (COMMA == Token)
				Token = scan();
			else
				break;
		}
		semi();
		utype = 0;
	}
	return addr;
}

static int intcmp(int *x1, int *x2) {
	while (*x1 && *x1 == *x2)
		x1++, x2++;
	return *x1 - *x2;
}

static void signature(int fn, int from, int to) {
	int	types[MAXFNARGS+1], i;

	if (to - from > MAXFNARGS)
		error("too many function parameters", Names[fn]);
	for (i=0; i<MAXFNARGS && from < to; i++)
		types[i] = Prims[--to];
	types[i] = 0;
	if (NULL == Mtext[fn]) {
		Mtext[fn] = galloc((i+1) * sizeof(int), 1);
		memcpy(Mtext[fn], types, (i+1) * sizeof(int));
	}
	else if (intcmp((int *) Mtext[fn], types))
		error("declaration does not match prior prototype: %s",
			Names[fn]);
}

/*
 * decl :=
 *	  declarator { localdecls stmt_list }
 *	| decl_list ;
 *
 * decl_list :=
 *	  declarator
 *	| declarator , decl_list
 */

void decl(int clss, int prim, int utype) {
	char	name[NAMELEN+1];
	int	pbase, type, size = 0, val, init;
	int	lsize;

	pbase = prim;
	for (;;) {
		prim = pbase;
		val = 0;
		init = 0;
		type = declarator(0, clss, name, &prim, &size, &val, &init);
		type = upgrade_array(utype, type, &size);
		if (TFUNCTION == type) {
			clss = clss == CSTATIC? CSPROTO: CEXTERN;
			Thisfn = addglob(name, prim, type, clss, size, 0,
					NULL, 0);
			signature(Thisfn, Locs, NSYMBOLS);
			if (LBRACE == Token) {
				clss = clss == CSPROTO? CSTATIC:
					clss == CEXTERN? CPUBLIC: clss;
				Thisfn = addglob(name, prim, type, clss, size,
					0, NULL, 0);
				Token = scan();
				lsize = localdecls();
				//grw - no need for text label in Asm/02
				//gentext();
				if (CPUBLIC == clss) genpublic(name);
				//grw - no need for alignment
				//genaligntext();
				genname(name);
				genentry();
				genstack(lsize);
				genlocinit();
				Retlab = label();
				compound(0);
				genlab(Retlab);
				genstack(-lsize);
				genexit(Thisfn);
				if (O_debug & D_LSYM)
					dumpsyms("LOCALS: ", name, Locs,
						NSYMBOLS);
			}
			else {
				semi();
			}
			clrlocs();
			return;
		}
		if (CEXTERN == clss && init) {
			error("initialization of 'extern': %s", name);
		}
		addglob(name, prim, type, clss, size, val, NULL, init);
		if (COMMA == Token)
			Token = scan();
		else
			break;
	}
	semi();
}

/*
 * structdecl :=
 *	  STRUCT IDENT { member_list } opt_decl ;
 *	| UNION IDENT { member_list } opt_decl ;
 *	| STRUCT { member_list } opt_decl ;
 *	| UNION { member_list } opt_decl ;
 *
 * opt_decl :=
 *      | decl
 *
 * member_list :=
 *	  primtype mdecl_list ;
 *	| primtype mdecl_list ; member_list
 *	| usertype mdecl_list ;
 *	| usertype mdecl_list ; member_list
 *
 * mdecl_list :=
 *	  declarator
 *	| declatator , mdecl_list
 */

void structdecl(int clss, int uniondecl) {
	int	utype, base, prim, size, dummy, type, addr = 0;
	char	name[NAMELEN+1], sname[NAMELEN+1];
	int	y, usize = 0;

	Token = scan();
	if (IDENT == Token) {
		copyname(sname, Text);
		Token = scan();
	}
	else {
		sname[0] = 0;
	}
	if (Token != LBRACE) {
		prim = primtype(uniondecl? UNION: STRUCT, sname);
		decl(clss, prim, 0);
		return;
	}
	y = addglob(sname, uniondecl? PUNION: PSTRUCT, TSTRUCT,
			CMEMBER, 0, 0, NULL, 0);
	Token = scan();
	utype = 0;
	//grw - added signed and unsigned types
	//grw - added support to ignore const keyword
	while (	INT == Token || CHAR == Token || VOID == Token ||
		UINT == Token || SCHAR == Token || CONST == Token ||
		STRUCT == Token || UNION == Token ||
		(IDENT == Token && (utype = usertype(Text)) != 0)
	) {
		if (CONST == Token) {
			//grw - ignore const keyword in member fields
			warn("const keyword ignored for struct/union members", NULL);
			Token = scan();
			continue;
		}
		base = utype? Prims[utype]: primtype(Token, NULL);
		size = 0;
		Token = scan();
		for (;;) {
			if (eofcheck()) return;
			prim = base;
			type = declarator(1, CMEMBER, name, &prim, &size,
						&dummy, &dummy);
			addglob(name, prim, type, CMEMBER, size, addr,
				NULL, 0);
			size = objsize(prim, type, size);
			if (size < 1)
				error("size of struct/union member"
					" is unknown: %s",
					name);
			if (uniondecl) {
				usize = size > usize? size: usize;
			}
			else {
				addr += size;
				addr = (addr + INTSIZE-1) / INTSIZE * INTSIZE;
			}
			if (Token != COMMA) break;
			Token = scan();
		}
		semi();
		utype = 0;
	}
	rbrace();
	Sizes[y] = uniondecl? usize: addr;
	if (Token != SEMI)
		decl(clss, Prims[y] | y, y);
	else
		semi();
}

/*
 * typedecl :=
 *	  TYPEDEF primtype decl
 *	| TYPEDEF usertype decl
 *	| TYPEDEF structdecl
 */

void typedecl(void) {
	int	utype, prim, cnst;
	//grw - added support for const keyword
	cnst = 0;
	Token = scan();

	if(CONST == Token) {
    cnst = 1;
		Token = scan();
	}
	if (STRUCT == Token || UNION == Token) {
		structdecl(CTYPE, UNION == Token);
		if (cnst)
		  warn("const keyword ignored for struct/union types", NULL);
	}
	else if ((utype = usertype(Text)) != 0) {
		Token = scan();
		decl(CTYPE, Prims[utype], utype);
	}
	else {
		prim = primtype(Token, NULL);
		if (cnst)
		  prim |= CNST;
		Token = scan();
		decl(CTYPE, prim, 0);
	}
}

/*
 * top :=
 *	  ENUM enumdecl
 *	| decl
 *	| primtype decl
 *	| storclass decl
 *	| storclass primtype decl
 *	| typedecl
 *	| usertype decl
 *	| storclass usertype decl
 *
 * storclass :=
 *	  EXTERN
 *	| STATIC
 */
void top(void) {
	int	utype, prim, clss = CPUBLIC;
	//grw - added support for const keyword
	int cnst;

	cnst = 0;

	//grw - added support for const keyword
	if (CONST == Token) {
		cnst = 1;
		Token = scan();
	}
	switch (Token) {
	case EXTERN:	clss = CEXTERN; Token = scan(); break;
	case STATIC:	clss = CSTATIC; Token = scan(); break;
	case VOLATILE:	Token = scan(); break;
	}
	/* const may also follow the extern/static/volatile keywords */
	if (!cnst && (CONST == Token)){
		cnst = 1;
		Token = scan();
	}
	switch (Token) {
	case ENUM:
		enumdecl(1);
		break;
	case TYPEDEF:
		typedecl();
		break;
	case STRUCT:
	case UNION:
		structdecl(clss, UNION == Token);
		if (cnst)
		  warn("const keyword ignored for struct/union types", NULL);
		break;

	case CHAR:
	case INT:
	case SCHAR:
	case UINT:
	case VOID:
		prim = primtype(Token, NULL);
		if (cnst)
		  prim |= CNST;
		Token = scan();
		decl(clss, prim, 0);
		break;

	case IDENT:
		if ((utype = usertype(Text)) != 0) {
			Token = scan();
			decl(clss, Prims[utype], utype);
			if (cnst && utype)
			  error("const keyword not valid before user defined type", NULL);
		}
		else {
			//grw - added support for const keyword
			/* decl(clss, PINT, 0); */
			prim = PINT;
			if (cnst)
			  prim |= CNST;
			decl(clss, prim, 0);
		}
		break;
	case ULABEL:
	    error("invalid location for local label: %s", Text);
			Token = scan();
			break;
	default:
		error("type specifier expected at: %s", Text);
		Token = synch(SEMI);
		break;
	}
}

static void stats(void) {
	printf(	"Memory usage: "
		"Symbols: %5d/%5d, "
		"Names: %5d/%5d, "
		"Nodes: %5d/%5d\n",
		Globs, NSYMBOLS,
		Nbot, POOLSIZE,
		Ndmax, NODEPOOLSZ);
}

void defarg(char *s) {
	char	*p;

	if (NULL == s) return;
	if ((p = strchr(s, '=')) != NULL)
		*p++ = 0;
	else
		p = "";
	addglob(s, 0, TMACRO, 0, 0, 0, globname(p), 0);
	if (*p) *--p = '=';
}

void program(char *name, FILE *in, FILE *out, char *def) {
	init();
	defarg(def);
	Infile = in;
	Outfile = out;
	File = Basefile = name;
	genprelude();
	Token = scan();
	while (XEOF != Token)
		top();
	genpostlude();
	if (O_debug & D_GSYM) dumpsyms("GLOBALS", "", 1, Globs);
	if (O_debug & D_STAT) stats();
}
