/*
 *	NMH's Simple C Compiler, 2011,2012,2014
 *	Preprocessor
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

char	mbuf[TEXTLEN+1];

void playmac(char *s) {
	if (Mp >= MAXNMAC) fatal("too many nested macros");
	Macc[Mp] = next();
	Macp[Mp++] = s;
}

int getln(char *buf, int max) {
	int	k;

	k = 1;
	//grw - updated logic to handle a backslash at end of lines
	do {
		if (fgets(buf + k - 1, max - k + 1, Infile) == NULL) return 0;
		k = (int) strlen(buf);
		/* remove newline at end of string */
		if (k) buf[--k] = 0;
		/* remove carriage return before newline */
		if (k && '\r' == buf[k-1]) buf[--k] = 0;
	} while(k && '\\' == buf[k-1]);

	return k;
}

static void defmac(void) {
	char	name[NAMELEN+1];
	char	*p;
	int	  y;
	int   margc = 0;
	char  *margs[MAXMARGS];
	int   idx;
	int   prev;

	Token = scanraw();
	if (Token != IDENT)
		error("identifier expected after '#define': %s", Text);
	copyname(name, Text);
	if ('\n' == Putback) {
		mbuf[0] = 0;
	} else if ('(' == Putback) {
		prev = 0;
		Token = scanraw();

 		while(Token = scanraw()) {
			if (Token == IDENT) {
				if (margc < MAXMARGS) {
				  margs[margc] = strdup(Text);
			    margc++;
			  } else {
					error("Too many arguments in macro %s\n", name);
				}
				prev = 0;
			} else if (Token == COMMA) {
				if (prev == COMMA) {
				  error("Invalid arguments in macro %s\n", name);
					getln(mbuf, TEXTLEN-1);
					break;
				}
				/* set previous token to comma */
				prev = COMMA;
			  continue;
			} else if (Token == RPAREN) {
				prev = 0;
				/* handle empty (void) parameter list */
				if (margc == 0) {
					margs[margc] = 0;
					margc++;
				}
				getln(mbuf, TEXTLEN-1);
			  break;
			}	else {
			  error("Invalid arguments for macro %s\n", name);
				getln(mbuf, TEXTLEN-1);
				break;
			}
		}
	} else {
		getln(mbuf, TEXTLEN-1);
	}
	/* skip over whitespace before macro text */
	for (p = mbuf; isspace(*p); p++)
		;
	if ((y = findmac(name)) != 0) {
		//grw - added check for maxro params
		if (strcmp(Mtext[y], mbuf) || Sizes[y] != margc)
			error("macro redefinition: %s", name);
	}	else {
		y = addglob(name, 0, TMACRO, 0, 0, margc, globname(p), 0);

		for (idx = 0; idx < margc; idx++){
			if (Margp >= MAXNMAC) {
				error("Too many global macro arguments.\n", NULL);
			} else {
				/* Add macro argument to global list */
			  Margs[Margp].id = y;
			  Margs[Margp].text = margs[idx];
			  Margp++;
		  }
		}
  }
	Line++;
}

static void undef(void) {
	char	name[NAMELEN+1];
	int	y;

	Token = scanraw();
	copyname(name, Text);
	if (IDENT != Token)
		error("identifier expected after '#undef': %s", Text);
	if ((y = findmac(name)) != 0)
		Names[y] = "#undef'd";
}

static void include(void) {
	char	file[TEXTLEN+1], path[TEXTLEN+1];
	int	c, k;
	FILE	*inc, *oinfile;
	char	*ofile;
	int	oc, oline;

	if ((c = skip()) == '<')
		c = '>';
	//grw - change SCCDIR to Fpath to use path from command string
	//k = getln(file, TEXTLEN-strlen(SCCDIR)-9);
	k = getln(file, (int)(TEXTLEN-strlen(Fpath)-9));
	Line++;
	if (!k || file[k-1] != c)
		error("missing delimiter in '#include'", NULL);
	if (k) file[k-1] = 0;
	if (c == '"')
		strcpy(path, file);
	else {
		//grw - change SCCDIR to Fpath to use path from command string
		strcpy(path, Fpath);
		strcat(path, "include/");
		strcat(path, file);
	}
	if ((inc = fopen(path, "r")) == NULL)
		error("cannot open include file: %s", path);
	else {
		Inclev++;
		oc = next();
		oline = Line;
		ofile = File;
		oinfile = Infile;
		Line = 1;
		putback('\n');
		File = path;
		Infile = inc;
		Token = scan();
		while (XEOF != Token)
			top();
		Line = oline;
		File = ofile;
		Infile = oinfile;
		fclose(inc);
		putback(oc);
		Inclev--;
	}
}

static void ifdef(int expect) {
	char	name[NAMELEN+1];

	if (Isp >= MAXIFDEF)
		fatal("too many nested '#ifdef's");
	Token = scanraw();
	copyname(name, Text);
	if (IDENT != Token)
		error("identifier expected in '#ifdef'", NULL);
	if (frozen(1))
		Ifdefstk[Isp++] = P_IFNDEF;
	else if ((findmac(name) != 0) == expect)
		Ifdefstk[Isp++] = P_IFDEF;
	else
		Ifdefstk[Isp++] = P_IFNDEF;
}

static void p_else(void) {
	if (!Isp)
		error("'#else' without matching '#ifdef'", NULL);
	else if (frozen(2))
		;
	else if (P_IFDEF == Ifdefstk[Isp-1])
		Ifdefstk[Isp-1] = P_ELSENOT;
	else if (P_IFNDEF == Ifdefstk[Isp-1])
		Ifdefstk[Isp-1] = P_ELSE;
	else
		error("'#else' without matching '#ifdef'", NULL);

}

static void endif(void) {
	if (!Isp)
		error("'#endif' without matching '#ifdef'", NULL);
	else
		Isp--;
}

static void pperror(void) {
	char	buf[TEXTLEN+1];

	if ('\n' == Putback)
		buf[0] = 0;
	else
		getln(buf, TEXTLEN-1);
	error("#error: %s", buf);
	exit(1);
}

static char FNbuf[TEXTLEN];

static void setline(void) {
	char	buf[TEXTLEN+1], *p, *q;

	if ('\n' == Putback)
		buf[0] = 0;
	else
		getln(buf, TEXTLEN-1);
	Line = atoi(buf) - 1;
	if ((p = strchr(buf, '"')) != NULL) {
		p++;
		if ((q = strchr(p, '"')) != NULL) {
			*q = 0;
			File = strcpy(FNbuf, p);
		}
	}
}

static void junkln(void) {
	while (!feof(Infile) && fgetc(Infile) != '\n')
		;
	Line++;
}

/* function to emit line to assembly file */
static void emitln(void) {
		char	buf[TEXTLEN+1];
		getln(buf, TEXTLEN-1);
		genraw("\n");  //grw - make sure text is on its own line
		genraw(buf);
		genraw("\n");
		Line++;
}

int frozen(int depth) {
	return Isp >= depth &&
		(P_IFNDEF == Ifdefstk[Isp-depth] ||
		P_ELSENOT == Ifdefstk[Isp-depth]);
}

void preproc(void) {
	putback('#');
	Token = scanraw();
	if (	frozen(1) &&
		P_IFDEF != Token && P_IFNDEF != Token &&
		P_ELSE != Token && P_ENDIF != Token
	) {
		junkln();
		return;
	}
	switch (Token) {
	case P_DEFINE:	defmac(); break;
	case P_UNDEF:	undef(); break;
	case P_INCLUDE:	include(); break;
	case P_IFDEF:	ifdef(1); break;
	case P_IFNDEF:	ifdef(0); break;
	case P_ELSE:	p_else(); break;
	case P_ENDIF:	endif(); break;
	case P_ERROR:	pperror(); break;
	case P_LINE:	setline(); break;
	//grw - change PRAGMA to emit line directly to asm file
	//case P_PRAGMA:	junkln(); break;
	case P_PRAGMA: emitln(); break;
	default:	junkln(); break;
			break;
	}
}
