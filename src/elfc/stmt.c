/*
 *	NMH's Simple C Compiler, 2011--2016
 *	Statement parser
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

static void stmt(void);

/*
 * compound :=
 *	  { stmt_list }
 *	| { }
 *
 * stmt_list:
 *	  stmt
 *	| stmt stmt_list
 */

void compound(int lbr) {
	if (lbr) Token = scan();
	while (RBRACE != Token) {
		if (eofcheck()) return;
		stmt();
	}
	Token = scan();
}

static void pushbrk(int id) {
	if (Bsp >= MAXBREAK)
		fatal("too many nested loops/switches");
	Breakstk[Bsp++] = id;
}

static void pushcont(int id) {
	if (Csp >= MAXBREAK)
		fatal("too many nested loops/switches");
	Contstk[Csp++] = id;
}

/*
 * break_stmt := BREAK ;
 */

static void break_stmt(void) {
	//grw - trace
	gen(";----- begin break");

	Token = scan();
	if (!Bsp) error("'break' not in loop/switch context", NULL);
	genjump(Breakstk[Bsp-1]);
	semi();
	//grw - trace
	gen(";----- end break");
}

/*
 * continue_stmt := CONTINUE ;
 */

static void continue_stmt(void) {
	//grw - trace
	gen(";----- begin coninue");

	Token = scan();
	if (!Csp) error("'continue' not in loop context", NULL);
	genjump(Contstk[Csp-1]);
	semi();
	//grw - trace
	gen(";----- end continue");
}

/*
 * do_stmt := DO stmt WHILE ( expr ) ;
 */

static void do_stmt(void) {
	int	ls, lb, lc;
	//grw - trace
	gen(";----- begin do");

	Token = scan();
	ls = label();
	pushbrk(lb = label());
	pushcont(lc = label());
	genlab(ls);
	stmt();
	match(WHILE, "'while'");
	lparen();
	genlab(lc);
	rexpr();
	genbrtrue(ls);
	//grw - removed clear logic
	//clear(1);
	genlab(lb);
	rparen();
	semi();
	Bsp--;
	Csp--;
	//grw - trace
	gen(";----- end do");
}

/*
 * for_stmt :=
 *	FOR ( opt_expr ; opt_expr ; opt_expr ) stmt
 *
 * opt_expr :=
 *	| expr
 */

static void for_stmt(void) {
	int	ls, lbody, lb, lc;
	//grw - trace
	gen(";----- begin for");

	Token = scan();
	ls = label();
	lbody = label();
	pushbrk(lb = label());
	pushcont(lc = label());
	lparen();
	if (Token != SEMI) {
		rexpr();
		//grw - removed clear logic
		//clear(1);
		//grw - clean up expression stack after init clause
		genpopd();
	}
	semi();
	genlab(ls);
	if (Token != SEMI) {
		rexpr();
		genbrfalse(lb);
		//grw - removed clear logic
		//clear(1);
	}
	genjump(lbody);
	semi();
	genlab(lc);
	if (Token != RPAREN) {
		rexpr();
		//grw - clean up expression stack after inc clause
		genpopd();
	}
	//grw - removed clear logic
	//clear(1);
	genjump(ls);
	rparen();
	genlab(lbody);
	stmt();
	genjump(lc);
	genlab(lb);
	Bsp--;
	Csp--;

	//grw - trace
	gen(";----- end for");
}

/*
 * if_stmt :=
 *	  IF ( expr ) stmt
 *	| IF ( expr ) stmt ELSE stmt
 */

static void if_stmt(void) {
	int	l1, l2;
	//grw - trace
	gen(";----- begin if");

	Token = scan();
	lparen();
	rexpr();
	l1 = label();
	genbrfalse(l1);
	//grw - removed clear logic
	//clear(1);
	rparen();
	stmt();
	if (ELSE == Token) {
		l2 = label();
		genjump(l2);
		genlab(l1);
		l1 = l2;
		Token = scan();
		stmt();
	}
	genlab(l1);
	//grw - trace
	gen(";----- end if");

}

/*
 * asm_stmt :=
 *	  asm ( string )
 * Output a string literal directly as a line of assembly text.
 */

static void asm_stmt(void) {
	Token = scan();
	lparen();
	//grw - for now, only accept string literals
	if (STRLIT == Token) {
		genasm(Text);
		Token = scan();
	}	else
	  error("asm statement requires string literal", NULL);
	//grw - removed clear logic
	//clear(1);
	rparen();
	semi();
}

/*
 * return_stmt :=
 *	  RETURN ;
 *	| RETURN expr ;
 */

static void return_stmt(void) {
	int	lv[LV];
	//grw - trace
	gen(";----- begin return");

	Token = scan();
	if (Token != SEMI) {
		expr(lv, 1);
		if (!typematch(lv[LVPRIM], Prims[Thisfn]))
			error("incompatible type in 'return'", NULL);
	}
	else {
		if (Prims[Thisfn] != PVOID)
			error("missing value after 'return'", NULL);
	}
	//grw - get return result from expression stack
	if (Prims[Thisfn] != PVOID)
		genpopd();

	genjump(Retlab);
	semi();
	//grw - trace
	gen(";----- end return");
}

/*
 * switch_stmt :=
 *	  SWITCH ( expr ) { switch_block }
 *
 * switch_block :=
 *	  switch_block_stmt
 *	| switch_block_stmt switch_block
 *
 * switch_block_stmt :=
 *	  CASE constexpr :
 *	| DEFAULT :
 *	| stmt
 */

static void switch_block(void) {
	int	lb, ls, ldflt = 0;
	int	cval[MAXCASE];
	int	clab[MAXCASE];
	int	nc = 0;
	//grw - trace
	gen(";----- begin switch block");

	Token = scan();
	pushbrk(lb = label());
	ls = label();
	genjump(ls);
	while (RBRACE != Token) {
		if (eofcheck()) return;
		if ((CASE == Token || DEFAULT == Token) && nc >= MAXCASE) {
			error("too many 'case's in 'switch'", NULL);
			nc = 0;
		}
		if (CASE == Token) {
			Token = scan();
			cval[nc] = constexpr();
			genlab(clab[nc++] = label());
			colon();
		}
		else if (DEFAULT == Token) {
			Token = scan();
			ldflt = label();
			genlab(ldflt);
			colon();
		}
		else
			stmt();
	}
	if (!nc) {
		if (ldflt) {
			cval[nc] = 0;
			clab[nc++] = ldflt;
		}
		else
			error("empty switch", NULL);
	}
	genjump(lb);
	genlab(ls);
	genswitch(cval, clab, nc, ldflt? ldflt: lb);
	//grw -- text directive not needed
	//gentext();
	genlab(lb);
	Token = scan();
	Bsp--;
	//grw - trace
	gen(";----- end switch block");

}

static void switch_stmt(void) {
	//grw - trace
	gen(";----- begin switch");

	Token = scan();
	lparen();
	rexpr();
	commit();
	//grw - removed clear logic
	//clear(0);
	rparen();
	if (Token != LBRACE)
		error("'{' expected after 'switch'", NULL);
	switch_block();
	//grw - trace
	gen(";----- end switch");

}

/*
 * while_stmt := WHILE ( expr ) stmt
 */

static void while_stmt(void) {
	int	lb, lc;
	//grw - trace
	gen(";----- begin while");

	Token = scan();
	pushbrk(lb = label());
	pushcont(lc = label());
	genlab(lc);
	lparen();
	rexpr();
	genbrfalse(lb);
	//grw - removed clear logic
	//clear(1);
	rparen();
	stmt();
	genjump(lc);
	genlab(lb);
	Bsp--;
	Csp--;
	//grw - trace
	gen(";----- end while");
}

static void wrong_ctx(int t) {
	if (DEFAULT == t) {
		error("'default' not in 'switch' context", NULL);
		Token = scan();
		colon();
	}
	else {
		error("'case' not in 'switch' context", NULL);
		Token = scan();
		constexpr();
		colon();
	}
}

/*
 * stmt :=
 *	  break_stmt
 *	| continue_stmt
 *	| do_stmt
 *	| for_stmt
 *	| if_stmt
 *	| return_stmt
 *	| switch_stmt
 *	| while_stmt
 *	| compound
 *	| ;
 *	| expr ;
 */

static void stmt(void) {
	int	lv[LV];
	//grw - trace
	gen(";----- begin stmt ------");

	switch (Token) {
	//grw -- added asm statement
	case ASM:	asm_stmt(); break;
	case BREAK:	break_stmt(); break;
	case CONTINUE:	continue_stmt(); break;
	case DO:	do_stmt(); break;
	case FOR:	for_stmt(); break;
	case IF:	if_stmt(); break;
	case RETURN:	return_stmt(); break;
	case SWITCH:	switch_stmt(); break;
	case WHILE:	while_stmt(); break;
	case LBRACE:	compound(1); break;
	case SEMI:	Token = scan(); break;
	case DEFAULT:	wrong_ctx(DEFAULT); break;
	case CASE:	wrong_ctx(CASE); break;
	//grw - added logic to get result from expression stack
	//grw - genpopd will eliminate a redundant push/pop then do a commit
	default:	expr(lv, 0); semi(); genpopd(); break;
	//default:	expr(lv, 0); semi(); genpopd(); commit(); break;

	}
	//grw - removed clear logic
	//clear(1);
	//grw - trace
	gen(";----- end stmt ------");
}
