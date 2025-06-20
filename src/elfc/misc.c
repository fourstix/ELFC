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
	Infile = stdin;
	File = "(stdin)";
	Basefile = NULL;
	Outfile = stdout;
	opt_init();
}

int chrpos(char *s, int c) {
	char	*p;

	p = strchr(s, c);
	return p? p-s: -1;
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
	return PINT == p || PCHAR == p;
}

int comptype(int p) {
	p &= STCMASK;
	return p == PSTRUCT || p == PUNION;
}

void notvoid(int p) {
	if (PVOID == p)
		error("void value in expression", NULL);
}
