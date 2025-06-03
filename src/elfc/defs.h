/*
 *	NMH's Simple C Compiler, 2011,2012,2022
 *	Definitions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* define this on 64-bit systems */
/* #define W64 */

/* define when linking against host's LIBC */
/* #define HOSTLIB */


#define PREFIX		'C'
#define LPREFIX		'L'

#ifndef SCCDIR
 #define SCCDIR		"."
#endif

#define ASCMD		"asm02 -L %s"

#define LDCMD		"link02 -e -s %s"
#define SYSLIBC	" -l lib\\elfc.lib"

#define SCCLIBC	" -l lib\\stdlib5.lib"

#define INTSIZE		2
#define PTRSIZE		INTSIZE
#define CHARSIZE	1

#define TEXTLEN		512
#define NAMELEN		16

#define MAXFILES	32

#define MAXIFDEF	16
#define MAXNMAC		32
#define MAXCASE		256
#define MAXBREAK	16
#define MAXLOCINIT	32
#define MAXFNARGS	32

#define NSYMBOLS	256
#define POOLSIZE	2048

/* types */
#define TVARIABLE	1
#define TARRAY		2
#define TFUNCTION	3
#define TCONSTANT	4
#define TMACRO		5

/* primitive types */
#define PCHAR	1
#define PINT	2
#define CHARPTR	3
#define INTPTR	4
#define CHARPP	5
#define INTPP	6
#define PVOID	7
#define VOIDPTR	8
#define VOIDPP	9
#define FUNPTR	10

/* storage classes */
#define CPUBLIC	1
#define CEXTERN	2
#define CSTATIC	3
#define CLSTATC	4
#define CAUTO	5

/* lvalue structure */
#define LVSYM	0
#define LVPRIM	1
#define LV	2

/* debug options */
#define D_LSYM	1
#define D_GSYM	2
#define D_STAT	4

enum {
	/* !!! The order of the following symbols must match
	   !!! the order of corresponding symbols in prec.h */
	SLASH, STAR, MOD, PLUS, MINUS, LSHIFT, RSHIFT,
	GREATER, GTEQ, LESS, LTEQ, EQUAL, NOTEQ, AMPER,
	CARET, PIPE, LOGAND, LOGOR,

	__ARGC, ASAND, ASM, ASXOR, ASLSHIFT, ASMINUS, ASMOD, ASOR,   //grw = added ASM keyword
	ASPLUS, ASRSHIFT, ASDIV, ASMUL, ASSIGN, BREAK, CASE,
	CHAR, COLON, COMMA, CONTINUE, DECR, DEFAULT, DO, ELLIPSIS,
	ELSE, ENUM, EXTERN, FOR, IDENT, IF, INCR, INT, INTLIT,
	LBRACE, LBRACK, LPAREN, NOT, QMARK, RBRACE, RBRACK,
	RETURN, RPAREN, SEMI, SIZEOF, STATIC, STRLIT, SWITCH,
	TILDE, VOID, WHILE, XEOF, XMARK,

	P_INCLUDE, P_DEFINE, P_ENDIF, P_ELSE, P_ELSENOT, P_IFDEF,
	P_IFNDEF, P_UNDEF
};
