/*
 *	NMH's Simple C Compiler, 2011--2021
 *	Lexical analysis (scanner)
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

//grw - add static buffer for predefined macros and macro parameters
/* buffer includes room for added quote marks and null */
char pbuf[MAXPARAMLEN+3];
char playbuf[TEXTLEN+1];

char macro_badop[] = "Operator %s is not used corectly in macro";

int next(void) {
	int	c;

	if (Putback) {
		c = Putback;
		Putback = 0;
		return c;
	}
	if (Mp) {
		if ('\0' == *Macp[Mp-1]) {
			Macp[Mp-1] = NULL;
			return Macc[--Mp];
		}
		else {
			return *Macp[Mp-1]++;
		}
	}
	c = fgetc(Infile);
	if ('\n' == c) Line++;
  /* support backslash at end of line as line continuation */
  if ('\\' == c) {
    /* peek at next char */
    c = fgetc(Infile);
    /* ignore newline, otherwise pushback */
    if ('\n' == c) {
			/* per C18, line count gets incremented even if spliced */
			Line++;
      c = fgetc(Infile);
    } else {
      /* if not end of line, push back character and return backslash */
      ungetc(c, Infile);
			c = '\\';
    }
  }
	return c;
}

void putback(int c) {
	Putback = c;
}

static int hexchar(void) {
	int	c, h, n = 0, f = 0;

	while (isxdigit(c = next())) {
		h = chrpos("0123456789abcdef", tolower(c));
		n = n * 16 + h;
		f = 1;
	}
	putback(c);
	if (!f)
		error("missing digits after '\\x'", NULL);
	if (n > 255)
		error("value out of range after '\\x'", NULL);
	return n;
}

static int scanch(void) {
	int	i, c, c2;

	c = next();

	if ('\\' == c) {
		switch (c = next()) {
		case 'a': return '\a';
		case 'b': return '\b';
		//grw - added escape character escape sequence
		case 'e': return '\033';
		case 'f': return '\f';
		case 'n': return '\n';
		case 'r': return '\r';
		case 't': return '\t';
		case 'v': return '\v';
		case '\\': return '\\';
		/* added case for line splicing inside string */
		case '\n': return ' ';
		case '"': return '"' | 256;
		case '\'': return '\'';
		case '0': case '1': case '2':
		case '3': case '4': case '5':
		case '6': case '7':
			for (i = c2 = 0; isdigit(c) && c < '8'; c = next()) {
				if (++i > 3) break;
				c2 = c2 * 8 + (c - '0');
			}
			putback(c);
			return c2;
		case 'x':
			return hexchar();
		default:
			scnerror("unknown escape sequence: %s", c);
			return ' ';
		}
	}
	else {
		return c;
	}
}

static int scanint(int c) {
	int	val, radix, k, i = 0;

	val = 0;
	radix = 10;
	if ('0' == c) {
		Text[i++] = '0';
		if ((c = next()) == 'x') {
			radix = 16;
			Text[i++] = c;
			c = next();
		}
		else {
			radix = 8;
		}
	}
	while ((k = chrpos("0123456789abcdef", tolower(c))) >= 0) {
		Text[i++] = c;
		if (k >= radix)
			scnerror("invalid digit in integer literal: %s", c);
		val = val * radix + k;
		c = next();
	}
	putback(c);
	Text[i] = 0;
	return val;
}

static int scanstr(char *buf) {
	int	i, c;

	buf[0] = '"';
	for (i=1; i<TEXTLEN-2; i++) {
		if ((c = scanch()) == '"') {
			buf[i++] = '"';
			buf[i] = 0;
			return Value = i;
		}
		buf[i] = c;
	}
	fatal("string literal too long");
	return 0;
}

static int scanident(int c, char *buf, int lim) {
	int	i = 0;

	while (isalpha(c) || isdigit(c) || '_' == c) {
		if (lim-1 == i) {
			error("identifier too long", NULL);
			i++;
		}
		else if (i < lim-1) {
			buf[i++] = c;
		}
		c = next();
	}
	putback(c);
	buf[i] = 0;
	return i;
}

int skip(void) {
	int	c, p, nl;

	c = next();
	nl = 0;
	for (;;) {
		if (EOF == c) {
			strcpy(Text, "<EOF>");
			return EOF;
		}
		while (' ' == c || '\t' == c || '\n' == c ||
			'\r' == c || '\f' == c
		) {
			if ('\n' == c) nl = 1;
			c = next();
		}
		if (nl && c == '#') {
			preproc();
			c = next();
			continue;
		}
		nl = 0;
		if (c != '/')
			break;
		c = next();
		if (c != '*' && c != '/') {
			putback(c);
			c = '/';
			break;
		}
		if (c == '/') {
			while ((c = next()) != EOF) {
				if (c == '\n') break;
			}
                }
                else {
			p = 0;
			while ((c = next()) != EOF) {
				if ('/' == c && '*' == p) {
					c = next();
					break;
				}
				p = c;
			}
		}
	}
	return c;
}

static int keyword(char *s) {
	switch (*s) {
	case '#':
		switch (s[1]) {
		case 'd':
			if (!strcmp(s, "#define")) return P_DEFINE;
			break;
		case 'e':
			if (!strcmp(s, "#else")) return P_ELSE;
			if (!strcmp(s, "#endif")) return P_ENDIF;
			if (!strcmp(s, "#error")) return P_ERROR;
			break;
		case 'i':
			if (!strcmp(s, "#ifdef")) return P_IFDEF;
			if (!strcmp(s, "#ifndef")) return P_IFNDEF;
			if (!strcmp(s, "#include")) return P_INCLUDE;
			break;
		case 'l':
			if (!strcmp(s, "#line")) return P_LINE;
			break;
		case 'p':
			if (!strcmp(s, "#pragma")) return P_PRAGMA;
			break;
		case 'u':
			if (!strcmp(s, "#undef")) return P_UNDEF;
			break;
		}
		break;
	case 'a':
		if (!strcmp(s, "auto")) return AUTO;
		//grw - added asm statement
		if (!strcmp(s, "asm")) return ASM;
		break;
	case 'b':
		if (!strcmp(s, "break")) return BREAK;
		break;
	case 'c':
		if (!strcmp(s, "case")) return CASE;
		if (!strcmp(s, "char")) return CHAR;
		if (!strcmp(s, "const")) return CONST;
		if (!strcmp(s, "continue")) return CONTINUE;
		break;
	case 'd':
		if (!strcmp(s, "default")) return DEFAULT;
		if (!strcmp(s, "do")) return DO;
		break;
	case 'e':
		if (!strcmp(s, "else")) return ELSE;
		if (!strcmp(s, "enum")) return ENUM;
		if (!strcmp(s, "extern")) return EXTERN;
		break;
	case 'f':
		if (!strcmp(s, "for")) return FOR;
		break;
	//grw - added support for local labels and goto
	case 'g':
		if (!strcmp(s, "goto")) return GOTO;
		break;
	case 'i':
		if (!strcmp(s, "if")) return IF;
		if (!strcmp(s, "int")) return INT;
		break;
	case 'r':
		if (!strcmp(s, "register")) return REGISTER;
		if (!strcmp(s, "return")) return RETURN;
		break;
	case 's':
	  if (!strcmp(s, "signed")) return SIGNED;
		if (!strcmp(s, "sizeof")) return SIZEOF;
		if (!strcmp(s, "static")) return STATIC;
		if (!strcmp(s, "struct")) return STRUCT;
		if (!strcmp(s, "switch")) return SWITCH;
		break;
	case 't':
		if (!strcmp(s, "typedef")) return TYPEDEF;
		break;
	case 'u':
		if (!strcmp(s, "union")) return UNION;
		if (!strcmp(s, "unsigned")) return UNSIGNED;
		break;
	case 'v':
		if (!strcmp(s, "void")) return VOID;
		if (!strcmp(s, "volatile")) return VOLATILE;
		break;
	case 'w':
		if (!strcmp(s, "while")) return WHILE;
		break;
	}
	return 0;
}

static int macro(char *name) {
	int	y;
	int  mparamc;
	int  margcnt;
	char *pfname;

	y = findmac(name);

	if (!y || Types[y] != TMACRO)
		return 0;
	if (!strcmp(name, "__LINE__")) {
		//grw - print line number as raw number in source
		sprintf(pbuf, "%d", Line);
		playmac(pbuf);
	} else if (!strcmp(name, "__FILE__")){
		/* we need to strip off any path info to find file name at end of string */
		/* search for Linux separator nearest end of string */
    pfname = strrchr(File, '/');
		/* if we found a slash, name is one past */
		if (pfname) {
		  pfname++;
		}	else {
			/* else, try backslash near the end for windows path */
			pfname = strrchr(File, '\\');
		  /* if we found slash, name is one past */
		  /* else, just use entire file string as file name */
		  if (pfname) pfname++;
		  else pfname = File;
	  }
		/* copy print filename as C string (double quotes) */
		sprintf(pbuf, "\"%s\"", pfname);
		playmac(pbuf);
	} else if (!strcmp(name, "__FUNCTION__")){
		//grw - print function name as C string in source (double quoted)
		sprintf(pbuf, "\"%s\"", Thisfn ? Names[Thisfn] : "(none)");
		playmac(pbuf);
	} else {
		margcnt = findargs(y);
		if (margcnt > 0) {
			//grw - parse params into Mshow array
			mparamc = scanparams(name);

			/* verify margc matches count of args */
			if (margcnt != mparamc)
			  error("Invalid number of parameters in marco %s", name);

			/* verify empty list does not match single (non-blank) parameter */
			if ((margcnt == 1) && !Mhide[0] && !blank(Mshow[0]))
  			error("Non-empty parameter list in marco %s", name);

			//grw - substitue params for arguments in Macro text
			prepmac(playbuf, Mtext[y], margcnt);

			//grw - show expanded macro text
			if (O_playmac)
			  printf("Expanded Macro %s: \"%s\"\n", name, playbuf);
			/* play expanded macro */
			playmac(playbuf);
		} else {
			//grw - show emacro text
			if (O_playmac)
			  printf("Macro %s: \"%s\"\n", name, Mtext[y]);
			/* if no arguments, play macro text directly */
			playmac(Mtext[y]);
		}
	}
	return 1;
}

static int scanpp(void) {
	int	c, t, peek;
	//grw - added support for local labels and goto
	static int ternary = 0;
	//grw - added support for macro operaters

	if (Rejected != -1) {
		t = Rejected;
		Rejected = -1;
		strcpy(Text, Rejtext);
		Value = Rejval;
		return t;
	}
	for (;;) {
		Value = 0;
		c = skip();
		memset(Text, 0, 4);
		Text[0] = c;
		switch (c) {
		case '!':
			if ((c = next()) == '=') {
				Text[1] = '=';
				return NOTEQ;
			}
			else {
				putback(c);
				return XMARK;
			}
		case '%':
			if ((c = next()) == '=') {
				Text[1] = '=';
				return ASMOD;
			}
			else {
				putback(c);
				return MOD;
			}
		case '&':
			if ((c = next()) == '&') {
				Text[1] = '&';
				return LOGAND;
			}
			else if ('=' == c) {
				Text[1] = '=';
				return ASAND;
			}
			else {
				putback(c);
				return AMPER;
			}
		case '(':
			return LPAREN;
		case ')':
			return RPAREN;
		case '*':
			if ((c = next()) == '=') {
				Text[1] = '=';
				return ASMUL;
			}
			else {
				putback(c);
				return STAR;
			}
		case '+':
			if ((c = next()) == '+') {
				Text[1] = '+';
				return INCR;
			}
			else if ('=' == c) {
				Text[1] = '=';
				return ASPLUS;
			}
			else {
				putback(c);
				return PLUS;
			}
		case ',':
			return COMMA;
		case '-':
			if ((c = next()) == '-') {
				Text[1] = '-';
				return DECR;
			}
			else if ('=' == c) {
				Text[1] = '=';
				return ASMINUS;
			}
			else if ('>' == c) {
				Text[1] = '>';
				return ARROW;
			}
			else {
				putback(c);
				return MINUS;
			}
		case '/':
			if ((c = next()) == '=') {
				Text[1] = '=';
				return ASDIV;
			}
			else {
				putback(c);
				return SLASH;
			}
		case ':':
		  ternary--;
			return COLON;
		case ';':
			return SEMI;
		case '<':
			if ((c = next()) == '<') {
				Text[1] = '<';
				if ((c = next()) == '=') {
					Text[2] = '=';
					return ASLSHIFT;
				}
				else {
					putback(c);
					return LSHIFT;
				}
			}
			else if ('=' == c) {
				Text[1] = '=';
				return LTEQ;
			}
			else {
				putback(c);
				return LESS;
			}
		case '=':
			if ((c = next()) == '=') {
				Text[1] = '=';
				return EQUAL;
			}
			else {
				putback(c);
				return ASSIGN;
			}
		case '>':
			if ((c = next()) == '>') {
				Text[1] = '>';
				if ((c = next()) == '=') {
					Text[1] = '=';
					return ASRSHIFT;
				}
				else {
					putback(c);
					return RSHIFT;
				}
			}
			else if ('=' == c) {
				Text[1] = '=';
				return GTEQ;
			}
			else {
				putback(c);
				return GREATER;
			}
		case '?':
			ternary++;
			return QMARK;
		case '[':
			return LBRACK;
		case ']':
			return RBRACK;
		case '^':
			if ((c = next()) == '=') {
				Text[1] = '=';
				return ASXOR;
			}
			else {
				putback(c);
				return CARET;
			}
		case '{':
			return LBRACE;
		case '|':
			if ((c = next()) == '|') {
				Text[1] = '|';
				return LOGOR;
			}
			else if ('=' == c) {
				Text[1] = '=';
				return ASOR;
			}
			else {
				putback(c);
				return PIPE;
			}
		case '}':
			return RBRACE;
		case '~':
			return TILDE;
		case EOF:
			strcpy(Text, "<EOF>");
			return XEOF;
		case '\'':
			Text[1] = Value = scanch();
			if ((c = next()) != '\'')
				error(
				 "expected '\\'' at end of char literal",
					NULL);
			Text[2] = '\'';
			return INTLIT;
		case '"':
			Value = scanstr(Text);
			return STRLIT;
		case '#':
			Text[0] = '#';
			scanident(next(), &Text[1], TEXTLEN-1);
      /* Updated logic to not consider # in hidden macro an error */
			if ((t = keyword(Text)) != 0) {
				return t;
      } else if (!frozen(1)) {
			  error("unknown preprocessor command: %s", Text);
      }
			return IDENT;
		case '.':
			if ((c = next()) == '.') {
				Text[1] = Text[2] = '.';
				Text[3] = 0;
				if ((c = next()) == '.')
					return ELLIPSIS;
				putback(c);
				error("incomplete '...'", NULL);
				return ELLIPSIS;
			}
			putback(c);
			return DOT;
		default:
			if (isdigit(c)) {
				Value = scanint(c);
				return INTLIT;
			}
			else if (isalpha(c) || '_' == c) {
				Value = scanident(c, Text, TEXTLEN);
				if (Expandmac && macro(Text))
					break;
				if ((t = keyword(Text)) != 0) {
					/* if signed or unsigned peek ahead to determine token */
					if (SIGNED == t || UNSIGNED == t) {
						/* get next non-whitespace char */
						c = skip();
						if ('c' == c || 'i' == c) {
							/* check to see if next token is int or char */
							Value = scanident(c, Text, TEXTLEN);
							peek = keyword(Text);
							/* only int or char are compound tokens */
							if (INT == peek || CHAR == peek) {
								if (SIGNED == t && CHAR == peek) {
									t = SCHAR;
								} else if (UNSIGNED == t && INT == peek) {
									t = UINT;
								} else {
									t = peek;
								} //if else t && peek
							} else {
								/* put back any non-keyword token as ident */
								if (0 == peek)
								  Token = IDENT;
								reject();
								/* assume (signed) integer or unsigned integer */
								if (UNSIGNED == t) {
									t = UINT;
								} else {
									t = INT;
								} // if else t UNSIGNED
							} // if else INT || CHAR
						} else {
							/*
							 * if next char not part of int or char keyword
							 * so put it back and assume (signed) integer or unsigned integer
							 */
							putback(c);
							if (UNSIGNED == t) {
								t = UINT;
							} else {
								t = INT;
							} // if else t UNSIGNED
						} //if else 'c' || 'i'
					} //if SIGNED || UNSIGNED
					return t;
				} // if keyword(Text)
        //grw - added support for local labels and goto
				c = next();
				/* a local label is an identifier that ends in a colon */
				/* but not inside a ternary statement */
				if (':' == c && !ternary) {
					return ULABEL;
				} else {
					putback(c);
				}
				return IDENT;
			}
			else {
				scnerror("funny input character: %s", c);
				break;
			}
		}
	}
}

int scan(void) {
	int	t;

	do {
		t = scanpp();
		if (!Inclev && Isp && XEOF == t)
			fatal("missing '#endif'");
	} while (frozen(1));
	if (t == Syntoken)
		Syntoken = 0;
	return t;
}

int scanraw(void) {
	int	t, oisp;

	oisp = Isp;
	Isp = 0;
	Expandmac = 0;
	t = scan();
	Expandmac = 1;
	Isp = oisp;
	return t;
}

void reject(void) {
	Rejected = Token;
	Rejval = Value;
	strcpy(Rejtext, Text);
}

/*
 * Scan for macro parameters
 * Note that parameters may contain whitespace,
 * parenthesis and commas
 * So we must track the level or nesting
 */
int scanparams(char *name) {
	int nest = 0;
	int idx = 0;
	int cnt = 0;
	char ch;


	ch = next();
	if (ch != '(') {
	  error("Macro %s requires parameters\n", name);
		return 0;
	}

	do {
		while((ch = next())) {
			if (ch == '(')
			  nest++;
			if (ch == ')') {
				if (nest) {
				  --nest;
				} else {
					/* unnested rparen marks end of parameter list */
				  break;
				} //if-else
			}
			/* ignore commas in nested parameters */
			if (!nest && ch == ',')
			  break;
			/* if we hit end of line something went wrong */
			if (ch == '\n') {
				error("Invalid parameter list for macro %s\n", name);
				break;
			}
			pbuf[idx++] = ch;
			if (idx >= MAXPARAMLEN) {
				error("Parameter too long in marco %s\n", name);
				break;
			}

		} //while
		/* end string for param */
		pbuf[idx] = '\0';
		Mshow[cnt++] = strdup(pbuf);

		/* reset character index for next parameter */
		idx = 0;
  } while(ch != ')');

	return cnt;
}

/*
 * Replace the argument with the matching macro parameter,
 * if found, remove leading and trailing whitespace for pasting.
 */
int replace(char *pb, int max) {
	int i = 0;
  char *m;
	int j = 0;

	for (i = 0; i < max; i++) {
		/* if buffer matchs an argument, replace with parameter */
    if (*pb == *Mhide[i] && !strcmp(pb, Mhide[i])) {
      /* We need to trim the matching param */
			m = Mshow[i];
      while(isspace(*m)) m++;
      /* copy remaining param string into buffer */
      while(*m) {
          pb[j++] = *m++;
      }
      /* remove whitespace form the end */
      while(isspace(pb[--j]));

      /* terminate string with null */
      pb[++j] = 0;
			break;
		}
	}
	return (i < max);
}

/*
 * Replace the argument with the matching macro parameter,
 * formatted as a string literal.  Any embedded backslash
 * or double quote marks are escaped.
 */
int stringify(char *pb, int max) {
	int i = 0;
	char *m;
	int j = 0;

	for (i = 0; i < max; i++) {
		/* if buffer matchs an argument, replace with parameter as string*/
    if (*pb == *Mhide[i] && !strcmp(pb, Mhide[i])) {
			m = Mshow[i];
			/* string starts with double quote mark */
			pb[j++] = '"';
			/* skip over leading whitespace in param */
			while(isspace(*m)) m++;
			/* copy remaining param string into buffer */
		  while(*m) {
					/* escape any backslash or double quote in param text */
				  if (*m == '\\' || *m == '\"')
					  pb[j++] = '\\';

					pb[j++] = *m++;
			}
			/* remove whitespace form the end */
			while(isspace(pb[--j]));
			/* string ends with double quote mark */
			pb[++j] = '"';

			/* terminate string literal with null */
			pb[++j] = 0;
			break;
		}
	}
	/* return false if argument was never found */
	return (i < max);
}


char *getparam(char *p, char *m) {
  int cnt = 0;
	while (isalnum(*m) || *m == '_') {
		*p++ = *m++;
		cnt++;
		/* don't scan more than param size */
		if (cnt == MAXPARAMLEN)
		  break;
  }
	*p = 0;
return m;
}

void prepmac(char *mb, char *m, int nargs) {
	char cm;
	int  mi = 0;
	int  pi = 0;

	/* handle case of empty (void) parameter list */
	if (nargs == 1 && !Mhide[0]) {
	  strcpy(mb, m);
		return;
	}

	while(*m) {
		cm = *m;

		/* check for beginning of argument */
		if (isalpha(cm) || cm == '_') {
			m = getparam(pbuf, m);
			replace(pbuf, nargs);
			/* copy param string into macro buffer */
			pi = 0;
			while(pbuf[pi])
				mb[mi++] = pbuf[pi++];

		} else if (cm == '#') {
			/* skip over hash mark */
			m++;
			cm = *m;

			if (cm == '#') {
				/* skip over second hash mark */
        m++;
        cm = *m;
        /* remove spaces before paste operator */
        while(isspace(mb[--mi]));
        /* we are now at the first non-space so move after it */
        mi++;

        /* skip over spaces after paste operator */
        while(isspace(cm)) {
          m++;
          cm = *m;
        }
        /* get next string of identifier text (can be numeric) */
				if (isalnum(cm) || cm == '_') {
					m = getparam(pbuf, m);
					/* trim parameter for pasting */
					replace(pbuf, nargs);
					/* copy trimmed param string into macro buffer */
					pi = 0;
					while(pbuf[pi])
					  mb[mi++] = pbuf[pi++];
				} else {
				  error(macro_badop, "##");
			  } // if stringify - else
			} else if (isalpha(cm) || cm == '_') {
				m = getparam(pbuf, m);

				if (stringify(pbuf, nargs)) {
					/* copy param as string literal into macro buffer */
					pi = 0;
					while(pbuf[pi])
						mb[mi++] = pbuf[pi++];
				} else {
	        error(macro_badop, "#");
				} // if paste - else
		  } else {
			error(macro_badop, "#");
		  }
		} else {
			mb[mi++] = cm;
			m++;
		}
	} //while
	/* end string in buffer */
	mb[mi] = 0;
}
