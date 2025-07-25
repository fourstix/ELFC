/*
 *	NMH's Simple C Compiler, 2012,2014
 *	_vscan()
 */
#define _ELFCLIB_
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#pragma             extrn Cfgetc
#pragma             extrn Cungetc
#pragma             extrn Cstrchr
#pragma             extrn Cisspace
#pragma             extrn Cisdigit
#pragma             extrn Ctolower
#pragma             extrn C_lbuf

#pragma .link .library string.lib
#pragma .link .library ctype.lib
#pragma .link .requires Cctype

extern char *_lbuf;

static FILE	*inf;
static char	*inp;
static int	nchar;

static int next(void) {
	nchar++;
	if (inf) return fgetc(inf);
	if (!*inp) return EOF;
	return *inp++;
}

static void back(int c) {
	nchar--;
	if (inf)
		ungetc(c, inf);
	else
		inp--;
}

static int skip(void) {
	int	c;

	while (isspace(c = next()))
		;
	back(c);
}

static int scanchar(char *p, int len) {
	int	c;
	
	if (0 == len) len = 1;
	while (len--) {
		if ((c = next()) == EOF)
			return 0;
		if (p) *p++ = c;
	}
	return 1;
}

static int scanstr(char *p, int len) {
	int	k, c;
	k = len;
	//grw - spec says %s should skip any leading whitespace
	skip();
 	
	while (0 == len || k--) {
	  c = next();
		if (isspace(c) || EOF == c) 
			break;
		if (p) *p++ = c;
	}
	//grw - spec says string always adds null
	*p = 0;
	return 1;
}

static char *mkclass(char *fmt) {
	//grw - change to use line buffer
	//static char	clss[128];
	int		i = 0, j;
	char *clss;
	
	//grw - use line buffer for class
	clss = _lbuf;
	
	clss[0] = 0;
	if ('^' == *fmt) fmt++, clss[0] = 1;
	i = 1;
	while (*fmt && *fmt != ']' && i < 127) {
		clss[i++] = *fmt++;
		if (i > 127) i--;
		if ('-' == *fmt && fmt[1] && fmt[1] != ']') {
			for (j = fmt[-1]; j < fmt[1]; j++) {
				if (i < 127) clss[i] = j;
				i++;
			}
		}
	}
	clss[i] = 0;
	return clss;
}

static int nstrchr(char *s, int c) {
	return !strchr(s, c);
}

static int scanclass(char *p, char *clss, int len) {
	int	cmp, k, c;
	int	(*in)();

	k = len;
	in = *clss++? nstrchr: strchr;
	while ((0 == len || k--) && in(clss, c = next()))
		if (p) *p++ = c;
		
	//grw - spec says [] always adds null
	if (p) *p = 0;	
	return 1;
}

static int scannum(int *pi, int base, int len) {
	int	sign = 1, ok = 0, k;
	char	*p, *digits, *src;
	int	v = 0, c;

	k = len;
	skip();
	c = next();
	k--;
	if ('-' == c) sign = -1, k--, c = next();
	else if ('+' == c) c = next(), k--;
	if ((0 == base || 16 == base) && '0' == c) {
		if ((c = next()) == 'x' || 'X' == c) {
			base = 16;
			c = next();
			k--;
		}
		else {
			back(c);
			k++;
			if (0 == base) base = 8;
			c = '0';
		}
	}
	else if ((0 == base || 8 == base) && '0' == c) {
		base = 8;
		c = next();
		k--;
	}
	if (len && k < 1) return 0;
	if (0 == base) base = 10;
	digits = "0123456789abcdef";
	while (0 == len || k--) {
		p = strchr(digits, tolower(c));
		if (!p || p - digits >= base) break;
		v = v * base + p - digits;
		c = next();
		ok = 1;
	}
	if (c >= 0) back(c);
	if (!ok) return 0;
	if (pi) *pi = v * sign;
	return 1;
}

/*
 * Read and scan input in the style of SCANF.
 * When MODE==0, read input from SRC (assuming
 * that SRCis a CHAR*).
 * When MODE==1, assume that SRC is a FILE* and
 * read input from that stream.
 */

int _vscan(int mode, void *src, char *fmt, void **varg) {
	int	noasg, len, na = 0, c, pna;
	//char	*clss;
	void	*p;

	if (0 == mode) {
		inp = src;
		inf = NULL;
	}
	else {
		inf = src;
	}
	nchar = 0;
	while (*fmt) {
		noasg = 0;
		if ('%' == *fmt && fmt[1] != '%') {
			len = 0;
			fmt++;
			if ('*' == *fmt)
				fmt++, noasg = 1;
			while (isdigit(*fmt))
				len = len * 10 + *fmt++ - '0';
			p = NULL;
			pna = na;
			switch (*fmt++) {
			case 'c':
			  //grw - vargs go up not down
				//if (!noasg) p = *varg--;
				if (!noasg) p = *varg++;
				if (scanchar(p, len)) na++;
				break;
			case 'd':
			  //grw - vargs go up not down
			  //if (!noasg) p = *varg--;
				if (!noasg) p = *varg++;
				if (scannum(p, 10, len)) na++;
				break;
			case 'i':
				//grw - vargs go up not down
				//if (!noasg) p = *varg--;
				if (!noasg) p = *varg++;
				if (scannum(p, 0, len)) na++;
				break;
			case 'n':
				//grw - vargs go up not down
				//if (!noasg) p = *varg--;
 				if (!noasg) p = *varg++;
				*(int *)p = nchar;
				break;
			case 'o':
				//grw - vargs go up not down
				//if (!noasg) p = *varg--;
				if (!noasg) p = *varg++;
				if (scannum(p, 8, len)) na++;
				break;
			case 's':
				//grw - vargs go up not down
				//if (!noasg) p = *varg--;
				if (!noasg) p = *varg++;
				if (scanstr(p, len)) na++;
				break;
			case 'p':
			case 'x':
			case 'X':
				//grw - vargs go up not down
				//if (!noasg) p = *varg--;
				if (!noasg) p = *varg++;
				if (scannum(p, 16, len)) na++;
				break;
			case '[':
				//grw - vargs go up not down
				//if (!noasg) p = *varg--;
				if (!noasg) p = *varg++;
				if (scanclass(p, mkclass(fmt), len))
					na++;
				break;
			}
			if (pna == na) break;
		}
		else {
			if ('%' == *fmt) fmt++;
			if (isspace(*fmt)) {
				//grw - original code here was incorrect 
				//grw - c would always be 1 or 0, rather than char from next()
				//while ((c = isspace(next())) != 0)
				//	;
				skip();
			}
			else if (*fmt != next())
				break;
			*fmt++;
		}
	}
	return na;
}
