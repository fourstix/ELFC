/*
 *	NMH's Simple C Compiler, 2011,2012,2022
 *	Binary operator precedence
 */

/* !!! The order of thes symbols must match the
   !!! order of corresponding symbols in defs.h */

static int Prec[] = {
	7, /* SLASH */
	7, /* STAR */
	7, /* MOD */
	6, /* PLUS */
	6, /* MINUS */
	5, /* LSHIFT */
	5, /* RSHIFT */
	4, /* GREATER */
	4, /* GTEQ */
	4, /* LESS */
	4, /* LTEQ */
	3, /* EQUAL */
	3, /* NOTEQ */
	2, /* AMPER */
	1, /* CARET */
	0, /* PIPE */
};
