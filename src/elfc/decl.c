/*
 *  NMH's Simple C Compiler, 2011--2022
 *  Declaration parser
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

static int declarator(int arg, int scls, char *name, int *pprim, int *psize,
      int *pval, int *pinit);

static int array_elements(int dimensions[], int order, int global,  char *aname, int aprim, int *asize);

static int initstruct(char *name, int prim, int *pinit);
static int linitstruct(int prim, int *pinit, int nstart, int outer);
static int sinitstruct(int prim, int *pval, int *pinit);
static int linitlist(int size, int mprim, int *pinit, int nstart, int outer);
static void writeldata(int n);

/* define static type qualifier messages used in warnings and errors */
static char invalid[] = "type qualifier \'%s\' not valid";
static char ignored[] = "type qualifier \'%s\' ignored";
static char bad_cls[] = "storage class \'%s\' not valid for global scope";
static char max_lvl[] = "too many levels of indirection in %s";

/* stack move for local variables */
static int mstack = 0;

/* initialization values for local structures */
int  vbuf[MAXLOCINIT];
int  pbuf[MAXLOCINIT];

/*
 * Commit the stack moves for previous local variables
 */
void commitmoves() {
  if (mstack != 0) {
    gen(";---- move stack for auto variables");
    /* adjust stack for size (dynamic int) */
    genstack(mstack);
    mstack = 0;
  }
}
/*
 * Move stack for local variables
 */
void movestack(int n) {
  mstack += n;
}

void clearmoves() {
  mstack = 0;
}

/*
 * enumdecl := { enumlist } ;
 *
 * enumlist :=
 *    enumerator
 *  | enumerator , enumlist
 *
 * enumerator :=
 *    IDENT
 *  | IDENT = constexpr
 */

static void enumdecl(int glob) {
  int  v = 0;
  char  name[NAMELEN+1];

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
 * Initialization for global (public and static) arrays
 *
 * initlist :=
 *    { const_list }
 *  | STRLIT
 *
 * const_list :=
 *    constexpr
 *  | constexpr , const_list
 */

static int initlist(char *name, int prim, int *pinit) {
  int  n = 0;
  int v = 0;
  char  buf[30];
  int nest = 0;

  if (NULL != name) {
    genname(name);
  } else {
    *pinit = label();
    genlab(*pinit);
  }
  /* debugging */
  //printf("initlist prim = %d Token = %d (STRLIT = %d)\n", prim, Token, STRLIT);
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

    return v-1;
  }
  lbrace();
  while (Token != RBRACE || nest) {
    /* debugging */
//    if (LBRACE == Token) {
//      nest++;
//      Token = scan();
//    }
    if (prim & STCMASK) {
      initstruct(NULL, prim, &v);
    } else if (CHARPTR == (prim & ~TQMASK)) {
      v = strexpr();
    } else {
      v = constexpr();
    }
    //grw - add support for type qualifiers
    /*
     * type qualifiers do not affect type matching
     * so remove any type qualifier bits from primitive type before comparing
     */
    if (prim & STCMASK) {
      /* debugging */
      printf("initlist (complex) v = %d\n", v);
      /* don't do anything for structures */
    } else if (PCHAR == (prim & ~TQMASK)) {
      if (v < 0 || v > 255) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
    }
      gendefb(v);
    } else if (PSCHAR == (prim & ~TQMASK)) {
      //grw - add support for type qualifiers
      if (v < -128 || v > 127) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
      }
      gendefb(v);
    } else if (CHARPTR == (prim & ~TQMASK)){
      gendefpstr(v);
    } else {
      gendefw(v);
    }
    n++;
    /* debugging */
    //grw - todo add nesting and test
    //if (nest && RBRACE == Token) {
    //  nest--;
    //  Token = scan();
    //}
    if (COMMA == Token)
      Token = scan();
    else
      break;
    if (eofcheck()) return 0;
  }
  Token = scan();
  if (!n) error("too few initializers", NULL);
  return n;
}

/*
 * Initialization for static local arrays
 *
 *  :=
 *    { const_list }
 *  | STRLIT
 *
 * const_list :=
 *    constexpr
 *  | constexpr , const_list
 */

static int sinitlist(int size, int prim, int *pinit) {
  int   n = 0;
  int  v = 0;
  int  len = 0;
  int  i = 0;
  char errbuf[30];
  int  *ibuf;
  char *sbuf;
  void *buf;
  char *str_err = "Local static string initializer is too long";

  /* allocate buffer for initialization values */
  buf = malloc(MAXLOCSTR);
  sbuf = (char *) buf;
  ibuf = (int *) buf;

//grw - update to allow concatenation of string literals
  if (STRLIT == Token) {
    v = 0;

    if (!chartype(prim)) {
      error("initializer type mismatch", NULL);
    }
    /* concatenate string literals */
    while (STRLIT == Token) {
      /* length includes two quote marks */
      len = strlen(Text);
      /* check to see if string goes past limit */
      if ((v + len - 2) > MAXLOCSTR) {
        /* if too long, exit with error */
        error(str_err, NULL);
        break;
      }
      /* don't process empty strings */
      if (len > 2) {
        /* copy characters in string, skipping quote marks at end */
        for(i = 1; i < len-1; i++){
          sbuf[v+i-1] = Text[i];
        }
        v += (Value-2);
      }
      Token = scan();
    }

    if (v >= MAXLOCSTR) {
      v = MAXLOCSTR - 1;
      error(str_err, NULL);
    }
    /* set null at end of concatenated string */
    sbuf[v] = '\0';
    v++;
   if (size && v > size) {
      error(str_err, NULL);
      ls_objs[lso_idx].isize = 0;
      ls_objs[lso_idx].ilist = NULL;
      free(buf);
    } else {
      ls_objs[lso_idx].isize = v;
      ls_objs[lso_idx].ilist = buf;
    }
    /* mark init for label to be assigned */
    *pinit = 0;
    /* return size of string + 1 for null */
    return v;
  }
  lbrace();
  while (Token != RBRACE) {

    if (prim & STCMASK) {
      /* debugging */
      printf("sinitlist 1 before call to sinitstruct\n");
      sinitstruct(prim, &v, &i);
      printf("sinitlist 1 after call to sinitstruct\n");
    } else if (CHARPTR == (prim & ~TQMASK)) {
      v = strexpr();
    } else {
      v = constexpr();
    }
    //grw - add support for type qualifiers
    /* if (PCHAR == prim) { */
    /*
     * type qualifiers do not affect type matching
     * so remove any type qualifier bits from primitive type before comparing
     */

     if (prim & STCMASK) {
       /* debugging */
       printf("sinitlist (complex) v = %d\n", v);
     } else if (PCHAR == (prim & ~TQMASK)) {
      if (v < 0 || v > 255) {
        sprintf(errbuf, "%d", v);
        error("initializer out of range: %s", errbuf);
    }
      /* add to the character array buffer */
      sbuf[n] = v;
    } else if (PSCHAR == (prim & ~TQMASK)) {
      //grw - add support for type qualifiers
    /* } else if (PSCHAR == prim) { */
      if (v < -128 || v > 127) {
        sprintf(errbuf, "%d", v);
        error("initializer out of range: %s", errbuf);
      }
      /* add to the character array buffer */
      sbuf[n] = v;
    } else {
      /* add to the integer array buffer */
      ibuf[n] = v;
    }
    n++;
    if (COMMA == Token)
      Token = scan();
    else
      break;
    if (eofcheck()) return 0;
  }
  Token = scan();
  /* check for no initializers or too many initializers */
  if (!n || (size && n > size)) {
    /* show corrrect error message */
    if (!n) {
      error("no initializers", NULL);
    } else {
      error(str_err, NULL);
    }
    ls_objs[lso_idx].isize = 0;
    ls_objs[lso_idx].ilist = NULL;
    free(buf);
  } else {
    ls_objs[lso_idx].isize = n;
    ls_objs[lso_idx].ilist = buf;
  }
  /* mark init to be assigned */
  *pinit = 0;

  return n;
}

int primtype(int t, char *s) {
  int  p, y;
  char  sname[NAMELEN+1];
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
  int  y;
  if ((y = findsym(s)) == 0)
    return 0;
  return CTYPE == Stcls[y]? y: 0;
}

/*
 * pmtrdecl :=
 *    ( )
 *  | ( pmtrlist )
 *  | ( pmtrlist , ... )
 *
 * pmtrlist :=
 *    primtype declarator
 *  | primtype declarator , pmtrlist
 *  | usertype declarator
 *  | usertype declarator , pmtrlist
 *
 * usertype :=
 *    TYPEDEF_NAME
 */

static int pmtrdecls(void) {
  char  name[NAMELEN+1];
  int  utype, prim, type, size, na, addr;
  int  dummy;
  //grw - added support for const keyword
  int cnst;
  //grw - add support for multidimensional arrays
  int order = 0;

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
    else if (VOLATILE == Token) {
      /* Volatile is ignored */
      Token = scan();
      continue;
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
      /* function parameters are already initialized, so set both const bits */
      if (cnst)
        prim |= CNSTMASK;
    }
    else {
      //grw - added signed and unsigned types
      if (  CHAR == Token || INT == Token ||
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
          else
             /* function parameters are already initialized, so set both const bits */
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

    //grw - adjust type for typedef arrays
    type = upgrade_array(utype, type, &size);


    /* array parameters decay into pointer variables */
    //grw - adjust type of parameter passed to function
    order = arrayorder(type);
    /* order = 0 is not an array */
    if (order > 0) {
      if (order < 2) {
        /* first order arrays decay into primative pointers */
        prim = pointerto(prim, name);
        type = TVARIABLE;
      } else {
        /* multidimensional arrays are passed by array pointer */
        /* set bit to avoid wiping out associated dimension types */
        type |= TARRPTRBIT;
      }
    }

    addloc(name, prim, type, CAUTO, size, addr, 0);
    //grw - add support to pass struct/union by value
    if (comptype(prim)) {
      size = objsize(prim, type, size);
      size = ALIGNED(size);
      addr += size;
    } else {
      addr += BPW;
    }

    na++;

    if (COMMA == Token) {
      Token = scan();
      //grw - added support for const keyword
      /* reset constant flag */
      cnst = 0;
    }  else
      break;
  }

  return na;
}

int pointerto(int prim, char *name) {
  int  y;
  //grw - added support for multiple pointer indirection
  int lvl, stc;

  lvl = ptrlevel(prim);
  /* check to see if struct/union type */
  stc = (prim & STCMASK);

  /* if no name set to generic */
  if (!name)
    name = "pointer";

  if (stc) {
    y = prim & ~STCMASK;
    switch (stc) {
      case PSTRUCT:  return STCPTR | y;
      case STCPTR:  return STCPP | y;
      case PUNION:  return UNIPTR | y;
      case UNIPTR:  return UNIPP | y;
      case STCPP:   /* falls through */
      case UNIPP: {
        error(max_lvl, name);
        return prim;
      }
    }
  } else if (lvl >= MAXPTR || ((prim & TYPEMASK) == FUNPTR)) {
    error(max_lvl, name);
  }
  //grw - added support for multiple pointer indirection
  if (lvl < MAXPTR)
    lvl++;
  return setptrlevel(prim, lvl);
}

/*
 * declarator :=
 *    IDENT
 *  | * IDENT
 *  | * * IDENT
 *  | * IDENT [ constexpr ]
 *  | IDENT [ constexpr ]
 *  | IDENT = constexpr
 *  | IDENT [ ] = initlist
 *  | IDENT pmtrdecl
 *  | IDENT [ ]
 *  | * IDENT [ ]
 *  | ( * IDENT ) ( )
 */

 /*
  * Init values used in functions
  * -1 - string initialization deferred for string table
  *  0 - uninitialized
  *  1 - initialized static or global (public)
  *  2 - initialized local (auto)
  */

static int declarator(int pmtr, int scls, char *name, int *pprim, int *psize,
      int *pval, int *pinit)
{
  int  type = TVARIABLE;
  int  ptrptr = 0;
  char *unsupp;
  //grw - added support to initialize global or static arrays
  int  isize = 0;
  int  rsize = 0;
  //grw - fixed error where array of structures falsely considered const
  int stc = (*pprim & STCMASK);
  //grw - added support for mutlidimensional arrays
  int dim[15];
  int autosize = 0;

  unsupp = "unsupported typedef syntax";

  if (STAR == Token) {
    Token = scan();
    *pprim = pointerto(*pprim, name);
    //grw - added support for multiple pointer indirection
    while (STAR == Token) {
      Token = scan();
      *pprim = pointerto(*pprim, name);
      ptrptr++;
    }
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
  }  else {
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

    /* need to emit error for struct/union */
    if (comptype(*pprim)) {
      /* debugging */
      Token = scan();

      if (PSTRUCT == stc) {
        if (CAUTO == scls) {
          //grw - commit stack moves for previous local variables
          commitmoves();
          sgen(";---- initialize local %s %s", "structure", name);
          linitstruct(*pprim, pinit, 0, 1);
          gen(";---- initialized structure on stack");
        } else if (CLSTATC == scls) {
          sgen(";---- initialize local static %s %s", "struct", name);
          /* debugging */
          printf("declarator before sinitstruct val = %d, init = %d\n", *pval, *pinit);
          sinitstruct(*pprim, pval, pinit);
          /* debugging */
          printf("declarator after sinitstruct val = %d, init = %d\n", *pval, *pinit);
        } else {
          sgen(";---- initialize global %s %s", "structure", name);
          isize = initstruct(name, *pprim, pinit);
          rsize = objsize(*pprim, TSTRUCT, 1);
          if (isize < rsize) {
            gendata(rsize - isize);
          } else if (isize > rsize) {
            error("Initialization list is larger than structure.", NULL);
          }
        }

        if (isglobal(scls)) {
          /* debugging */
          printf("declarator 1: setting *pinit = 1 for global\n");
          *pinit = 1;
        }
      } else if (PUNION == stc) {
        /* Unions are initialized by the first type */
        *pval = constexpr();
        if (isglobal(scls)) {
          /* debugging */
          printf("declarator 2: setting *pinit = 1 for global\n");
          *pinit = 1;
        }
      } else {
        error("Initialization of %s is not supported", name);
      }
      return TSTRUCT;
    }

    Token = scan();
    /* check for initializing char ptr with string literal address */
    if (*pprim == CHARPTR && STRLIT == Token) {

      /* generate string and set value to label number */
      *pval = strexpr();
      /* static string initialization has address as value */
      lgen(";---- init pointer with %s %c%d", "string", *pval);
      *pinit = -1;
    } else if (CAUTO == scls) {
        //grw - commit stack moves for previous local variables
        commitmoves();
        gen(";---- local init");
        initexpr();
        commit();
        gen(";---- local init result is on stack");
        *pval = 0;
        *pinit = 2;
    } else {
      *pval = constexpr();
    }

    if (chartype(*pprim))
      *pval &= 0xff;
    //grw - allow non-zero pointer initialization
     /*  if (*pval && !inttype(*pprim))
      error("non-zero pointer initialization", NULL);  */
    //grw - do not change pinit for static variables
    if (*pinit == 0 && CLSTATC != scls) {
      /* debugging */
      printf("declarator 3: setting *pinit = 1\n");
      *pinit = 1;
    }

      //grw - added support for const keyword
    if (!stc && CNST == (*pprim & CNSTMASK))
      *pprim |= CINIT;
  }  else if (!pmtr && LPAREN == Token) {
    if (CTYPE == scls)
      error(unsupp, NULL);
    Token = scan();
    *psize = pmtrdecls();
    rparen();
    return TFUNCTION;
  } else if (LBRACK == Token) {
    //grw -- add support for multidimensional arrays
    while(LBRACK == Token) {
      ptrptr++;
      //grw - added support for multiple pointer indirection
      if (ptrptr > MAXPTR)
        error(max_lvl, name);

      //grw - moving const warning to non-initialized arrays
      Token = scan();
      if (RBRACK == Token) {
        autosize = 1;

        if (CTYPE == scls)
          error(unsupp, NULL);
        Token = scan();
        if (ptrptr > 1)
          error("only the first dimension of incopmlete array %s can be omitted", name);

        /* set incomplete dimension to 1 */
        dim[ptrptr-1] = 1;
        continue;
      }  else {
        *psize = constexpr();

        if (*psize < 1) {
          error("invalid array size", NULL);
          *psize = 0;
        }
        rbrack();

        /* set the dimension value */
        dim[ptrptr-1] = *psize;
      }
    } // while
    /* after array definitions */
    type = array_elements(dim, ptrptr, pmtr, name, *pprim, psize);
    //grw - initialization of global and local arrays
    if (ASSIGN == Token) {
      Token = scan();
      //grw - allow pointer arrays to be initialized by string or constant
      /*
      if (!inttype(*pprim))
        error("initialization of"
          " pointer array not"
          " supported",
          NULL);
      */
      if (pmtr)
        error("initialization is not allowed for function paramater %s\n", name);
      //grw - added initialization for local static arrays
      //grw - added support for initialization of local arrays
      if (CAUTO == scls) {
        //grw - commit stack moves for previous local variables
        commitmoves();
        sgen(";---- initialize local %s %s", "array", name);
        //isize = linitlist(autosize ? 0 : *psize, *pprim, pinit);
        isize = linitlist(autosize ? 0 : *psize, *pprim, pinit, 0, 1);
        gen(";---- initialized array on stack");
      } else if (CLSTATC == scls) {
        sgen(";---- initialize local static %s %s", "array", name);
        /* debugging */
        printf("declarator before sinitlist *pval = %d, *pinit = %d\n", *pval, *pinit);
        isize = sinitlist(autosize ? 0 : *psize, *pprim, pinit);
        /* debugging */
        printf("declarator after sinitlist *psize = %d, *pval = %d, init = %d\n",
        *psize, *pval, *pinit);

      } else {
        sgen(";---- initialize global %s %s", "array", name);
        isize = initlist(name, *pprim, pinit);
      }

      //grw - set ini to 1 for initialized global static and public arrays
      if (isglobal(scls)) {
        /* debugging */
        printf("declarator 1: setting *pinit = 1 for global\n");
        *pinit = 1;
      }
      //grw - set value to 1 for initialized array
      *pval  = 1;

      //grw - added support for const keyword
      if (!stc && CNST == (*pprim & CNSTMASK))
        *pprim |= CINIT;

      //grw - update this logic for multidimensional arrays
      if (autosize) {
        //grw - size for multidimensional array must be even multiple specified elements
        if (*psize > 1 && ptrptr > 1) {
          //grw - fix logic to not wipe ot isize
          //isize %= *psize;
          if ((isize % *psize) == 0) {
            *psize = isize;
          } else {
            error("initialization list size must be multiple of the specified dimensions of array %s", name);
          }
        } else {
          //grw - set the size value
          *psize = isize;
        }
      } else if (isize < *psize) {
        /* pad the rest of array elements with zero's */
        isize = *psize - isize;
        rsize = objsize(*pprim, type, isize);
        /* local objects already have padding */
        if (isglobal(scls)) {
          gendata(rsize);
        }
      }  else if (!autosize && isize > *psize) {
          error("initialization list size larger than size of array %s", name);
      }
    }  else if (CEXTERN != scls && autosize && !pmtr) {
    error("automatically-sized array"
      " lacking initialization: %s",
      name);
    }  else if (!stc && (*pprim & CNSTMASK)) {
      //grw - changed this to error instead of clearing bits
      error("const keyword not supported for non-initialized array %s", name);
    }
  }

  if (PVOID == *pprim)
    error("'void' is not a valid type: %s", name);

  return type;
}

/*
 * Upgrate type for user defined array types
 */
int upgrade_array(int utype, int type, int *size) {
  if (utype && isArray(Types[utype])) {
    *size = *size ? (*size * Sizes[utype]) : Sizes[utype];
    if (isArray(type))
      error("unsupported array of typedef array", NULL);
    type = Types[utype];
  }
  return type;
}

/*
 * localdecls :=
 *        ldecl
 *      | ldecl localdecls
 *
 * ldecl :=
 *    primtype ldecl_list ;
 *  | usertype ldecl_list ;
 *  | lclass primtype ldecl_list ;
 *  | lclass ldecl_list ;
 *  | enum_decl
 *  | struct_decl
 *
 * lclass :=
 *  | AUTO
 *  | EXTERN
 *  | REGISTER
 *  | STATIC
 *  | VOLATILE
 *  | CONST
 *
 * ldecl_list :=
 *    declarator
 *  | declarator , ldecl_list
 */

static int localdecls(void) {
  char  name[NAMELEN+1];
  int  utype, prim, type, size, addr = 0, val, ini;
  //grw - added support for const keyword
  int  stat, extn, cnst, rgstr, vltl;
  int  pbase, rsize;
  //grw - added support for dynamic init
  //grw - add support for local static objects
  //int lab;

  Nlsi = 0;
  utype = 0;
  //grw - add support for local static objects
  lso_idx = 0;

  //grw -set stack to zero initially
  clearmoves();

  //grw - added signed and unsigned types
  //grw - added support for const keyword
  while ( AUTO == Token || EXTERN == Token || REGISTER == Token ||
    STATIC == Token || VOLATILE == Token || CONST == Token ||
    INT == Token || CHAR == Token || VOID == Token ||
    SCHAR == Token || UINT == Token ||
    ENUM == Token ||
    STRUCT == Token || UNION == Token ||
    (IDENT == Token && (utype = usertype(Text)) != 0)) {
    if (ENUM == Token) {
      enumdecl(0);
      continue;
    }
    extn = stat = 0;
    //grw - added support for const and volatile keywords
    cnst = rgstr = vltl = 0;
    if (AUTO == Token || REGISTER == Token || STATIC == Token ||
      //grw - added support for const keyword
      VOLATILE == Token || CONST == Token || EXTERN == Token ||
      (IDENT == Token && (utype = usertype(Text)) != 0)) {
      stat  = STATIC == Token;
      extn  = EXTERN == Token;
      //grw - added support for const and volatile keywords
      cnst  = CONST == Token;
      rgstr = REGISTER == Token;
      vltl  = VOLATILE == Token;

      Token = scan();
      //grw - added support for const and volatile keywords
      if (CONST == Token) {
        if (cnst)
          error(invalid, "const");
        cnst  = 1;
        if (rgstr)
          error (invalid, "const");
        Token = scan();
        if (VOLATILE == Token || (IDENT == Token && (utype = usertype(Text)) != 0)) {
          if (VOLATILE == Token) {
            if (vltl)
              error(invalid, "volatile");
            else vltl = 1;
          }
          Token = scan();
        }
      } else if (VOLATILE == Token) {
            if (vltl)
              error(invalid, "volatile");
            else vltl = 1;
            Token = scan();
            if (CONST == Token) {
              if (cnst)
                 error(invalid, "const");
              else cnst = 1;
                Token = scan();
            }
            if (IDENT == Token && (utype = usertype(Text)) != 0) {
               Token = scan();
            }
      //grw - updated logic to skip if user type already encountered
      //grw - otherwise could be static (or even extern) followed by user type
      /* } else if (IDENT == Token && (utype = usertype(Text)) != 0) { */
      } else if (utype == 0) {
        if (IDENT == Token && (utype = usertype(Text)) != 0) {
        Token = scan();
      }
    }
    if (INT == Token || CHAR == Token ||
      //grw - added signed and unsigned types
      SCHAR == Token || UINT == Token ||
      VOID == Token ||
      STRUCT == Token || UNION == Token) {
      prim = primtype(Token, NULL);
      //grw - added support for const keyword
      if (cnst) {
        if (prim & STCMASK)
          warn(ignored,"const");
        else
          prim |= CNST;
      }
      //grw - added support for volatile keyword
      if (vltl) {
        if (prim & STCMASK)
          warn(ignored, "volatile");
        else
          prim |= VLTL;
      }
      Token = scan();
    }  else if (utype) {
        prim = Prims[utype];
        //grw - added support for const keyword
        if (cnst) {
          if (prim & STCMASK)
            warn(ignored,"const");
          else
            prim |= CNST;
        }
        //grw - added support for volatile keyword
        if (vltl) {
          if (prim & STCMASK)
            warn(ignored, "volatile");
          else
            prim |= VLTL;
        }
    }  else {
      prim = PINT;
      //grw - added support for const and volatile keywords
      if (cnst)
        prim |= CNST;
      if (vltl)
        prim |= VLTL;
    }
  }  else if (utype) {
    prim = Prims[utype];
    //grw - added support for const keyword
    if (cnst) {
      if (prim & STCMASK)
        warn(ignored,"const");
      else
        prim |= CNST;
    }
    //grw - added support for volatile keyword
    if (vltl) {
      if (prim & STCMASK)
        warn(ignored, "volatile");
      else
        prim |= VLTL;
    }
    Token = scan();
  }  else {
      prim = primtype(Token, NULL);
      //grw - added support for const and volatile keywords
      if (cnst)
        prim |= CNST;
      if (vltl)
        prim |= VLTL;
      Token = scan();
  }
  pbase = prim;
  for (;;) {
    prim = pbase;
    if (eofcheck()) return 0;
    size = 1;
    ini = val = 0;
    //grw - add support to initialize local static arrays
    if (stat) {
      //grw - moved static definitions to local static object space

      //grw - set the static init fields to zero
      ls_objs[lso_idx].isize = 0;
      ls_objs[lso_idx].ilist = NULL;

      type = declarator(0, CLSTATC, name, &prim, &size,  &val, &ini);
      /* debugging */
      printf("after declarator 1: prim = %d, size = %d, val = %d, ini = %d\n", prim, size, val, ini);

    } else {
      /* need to pad struct/union at top of list in case its returned */
      if (!addr && (prim & STCMASK)) {
        addloc("_pad", PINT, TVARIABLE, CAUTO, 2, 0, 0);
        addr -= BPW;
        genstack(addr);
      }
      type = declarator(0, CAUTO, name, &prim, &size,  &val, &ini);
      /* debugging */
      printf("after declarator 2: prim = %d, size = %d, val = %d, ini = %d\n", prim, size, val, ini);

    }
    type = upgrade_array(utype, type, &size);
    rsize = objsize(prim, type, size);
    //grw - created macro for alignment size
    rsize = ALIGNED(rsize);
    /* debugging */
    printf("prim = %d, size = %d, rsize = %d, ini = %d, stat = %d\n",
    prim, size, rsize, ini, stat);

    //grw - and pass new label, value to addloc for uninitialized array
    if (stat) {
      /* generate label for static declaration */
      /* debugging */
      printf("before addloc ini = %d, val = %d\n", ini, val);
      if (!ini)
        ini = label();
      addloc(name, prim, type, CLSTATC, size,  ini, val);
      //grw - moved static definitions to local static object space
    }  else if (extn) {
      addloc(name, prim, type, CEXTERN, size,  0, val);
    }  else {
      //grw - moved to before auto declarator
      /* need to pad struct/union at top of list in case its returned */
      //if (!addr && (prim & STCMASK)) {
      //  addloc("_pad", PINT, TVARIABLE, CAUTO, 2, 0, 0);
      //  addr -= BPW;
      //  genstack(addr);
      //}
      /* debugging */
      //printf("prim = %d, size = %d, rsize = %d, ini = %d\n", prim, size, rsize, ini);

      addr -= rsize;
      addloc(name, prim, type, CAUTO, size, addr, 0);
      ngen(";---- local variable %s on the stack at %d", name, addr);

      if (rsize > LGOBJSIZE)
        warn("Large local object %s should be declared static\n", name);
    }
    if (ini != 2 && !stat) {
      //grw - consolidate multiple local variable stack moves
      //gen(";---- move stack for auto variable");
      //genstack(-rsize);
      /* adjust stack for size (dynamic int) */
      movestack(-rsize);
    }

    /* process delayed inits */
    if (ini && !stat) {
        if (Nlsi >= MAXLOCINIT) {
        error("too many local initializers", NULL);
        Nlsi = 0;
      }

      if (ini == -1) {
        gen(";----- local string init deferred");
        LSaddr[Nlsi] = addr;
        LSval[Nlsi++] = val;
      } else if (ini == 1) {
        //grw - removed unused constant initialization
        error("Unsupported local initialization constant expression.", NULL);
        //LSaddr[Nlsi] = addr;
        //LSval[Nlsi++] = val;
      }
    }
    if (COMMA == Token)
      Token = scan();
    else
      break;
    }
    semi();
    utype = 0;
  }
  //grw - commit any pending stack moves for local variables
  commitmoves();
  return addr;
}

static int intcmp(int *x1, int *x2) {
  while (*x1 && *x1 == *x2)
    x1++, x2++;
  return *x1 - *x2;
}

static void signature(int fn, int from, int to) {
  int  types[MAXFNARGS+1], i;

  if (to - from > MAXFNARGS)
    error("too many function parameters", Names[fn]);
  for (i=0; i<MAXFNARGS && from < to; i++) {
    //grw - updated for multidimensional arrays
    //types[i] = Prims[--to];
    //grw - decay an array paramter into an array pointer here?
    --to;
    if (isArray(Types[to])) {
      types[i] = arrayptr(Prims[to], Types[to], Names[to]);
    } else {
      types[i] = Prims[to];
    }
  }
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
 *    declarator { localdecls stmt_list }
 *  | decl_list ;
 *
 * decl_list :=
 *    declarator
 *  | declarator , decl_list
 */

void decl(int clss, int prim, int utype) {
  char  name[NAMELEN+1];
  int  pbase, type, size = 0, val, init;
  int  lsize;

  pbase = prim;
  for (;;) {
    prim = pbase;
    val = 0;
    init = 0;

    type = declarator(0, clss, name, &prim, &size, &val, &init);
    type = upgrade_array(utype, type, &size);

    if (isFunction(type)) {
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

        if (CPUBLIC == clss) genpublic(name);
        genname(name);
        genentry();

        lsize = localdecls();
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
 *    STRUCT IDENT { member_list } opt_decl ;
 *  | UNION IDENT { member_list } opt_decl ;
 *  | STRUCT { member_list } opt_decl ;
 *  | UNION { member_list } opt_decl ;
 *
 * opt_decl :=
 *      | decl
 *
 * member_list :=
 *    primtype mdecl_list ;
 *  | primtype mdecl_list ; member_list
 *  | usertype mdecl_list ;
 *  | usertype mdecl_list ; member_list
 *
 * mdecl_list :=
 *    declarator
 *  | declatator , mdecl_list
 */

void structdecl(int clss, int uniondecl) {
  int  utype, base, prim, size, dummy, type, addr = 0;
  char  name[NAMELEN+1], sname[NAMELEN+1];
  int  y, usize = 0;
  int cnst, vltl;

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
  //grw - added support for const and volatile keywords
  cnst = 0;
  vltl = 0;

  while (  INT == Token || CHAR == Token || VOID == Token ||
    UINT == Token || SCHAR == Token || CONST == Token ||
    VOLATILE == Token || STRUCT == Token || UNION == Token ||
    (IDENT == Token && (utype = usertype(Text)) != 0)
  ) {
    if (CONST == Token) {
      if (cnst)
        error(invalid, "const");
      cnst = 1;
      Token = scan();
      continue;
    } else if (VOLATILE == Token) {
      if (vltl)
        error(invalid, "volatile");
      vltl = 1;
      Token = scan();
      continue;
    }

    base = utype? Prims[utype]: primtype(Token, NULL);

    if (utype) {
      //grw - added support for const keyword
      if (cnst) {
        if (base & STCMASK)
          warn(ignored,"const");
        else
          base |= CNST;
      }
      //grw - added support for volatile keyword
      if (vltl) {
        if (base & STCMASK)
          warn(ignored, "volatile");
        else
          base |= VLTL;
      }
    } else if ((base & STCMASK) != 0) {
      if (cnst)
        warn(ignored, "const");
      if (vltl)
        warn(ignored, "volatile");
    } else {
      /* allowed, if not a struct/union */
      if (cnst) {
        base |= CNST;
      }
      if (vltl) {
        base |= VLTL;
      }
    }

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
        //grw - created macro for alignment size
        //addr = (addr + INTSIZE-1) / INTSIZE * INTSIZE;
        addr = ALIGNED(addr);

      }
      if (Token != COMMA) break;
      Token = scan();
    }
    semi();
    utype = 0;
    cnst = 0;
    vltl = 0;
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
 *    TYPEDEF primtype decl
 *  | TYPEDEF usertype decl
 *  | TYPEDEF structdecl
 */

void typedecl(void) {
  int  utype, prim;
  //grw - added support for const and volatile keywords
  int cnst, vltl;

  cnst = vltl = 0;
  Token = scan();

  if (CONST == Token || VOLATILE == Token) {
    cnst = CONST == Token;
    vltl = VOLATILE == Token;
    Token = scan();
    if (CONST == Token) {
     if (cnst)
       error(invalid, "const");
     cnst = 1;
     Token = scan();
   } else if (VOLATILE == Token) {
     if (vltl)
       error(invalid, "volatile");
     vltl = 1;
     Token = scan();
   }
  }
  if (STRUCT == Token || UNION == Token) {
    structdecl(CTYPE, UNION == Token);
    if (cnst)
      warn("ignored", "const");
    if (vltl)
      warn("ignored", "volatile");
  }
  else if ((utype = usertype(Text)) != 0) {
    //grw - added support for const keyword
    prim =  Prims[utype];
    if (cnst) {
      if (prim & STCMASK)
        warn(ignored,"const");
      else
        prim |= CNST;
    }
    //grw - added support for volatile keyword
    if (vltl) {
      if (prim & STCMASK)
        warn(ignored, "volatile");
      else
        prim |= VLTL;
    }
    Token = scan();
    /* decl(CTYPE, Prims[utype], utype); */
    //grw - can declare new type as const or volatile user type
    decl(CTYPE, prim, utype);
  }
  else {
    prim = primtype(Token, NULL);
    if (cnst)
      prim |= CNST;
    if (vltl)
      prim |= VLTL;
    Token = scan();
    decl(CTYPE, prim, 0);
  }
}

/*
 * top :=
 *    ENUM enumdecl
 *  | decl
 *  | primtype decl
 *  | storclass decl
 *  | storclass typequal decl
 *  | typequal decl
 *  | storclass primtype decl
 *  | storclass typequal primtype decl
 *  | typequal primtype decl
 *  | typedecl
 *  | usertype decl
 *  | storclass usertype decl
 *
 * storclass :=
 *    EXTERN
 *  | STATIC
 * typequal :=
 *    CONST
 *  | CONST VOLATILE
 *  | VOLATILE
 *  | VOLATILE CONST
 */
void top(void) {
  int  utype, prim, clss = CPUBLIC;
  //grw - added support for const and volatile keywords
  int cnst, vltl;

  cnst = vltl = 0;

  switch (Token) {
  case EXTERN:  clss = CEXTERN; Token = scan(); break;
  case STATIC:  clss = CSTATIC; Token = scan(); break;
  case VOLATILE:  vltl = 1; Token = scan(); break;
  case CONST:  cnst = 1; Token = scan(); break;
  case AUTO: error(bad_cls, "auto"); Token = scan(); break;
  case REGISTER: error(bad_cls, "register"); Token = scan(); break;
  }
  /* const/volatile may also follow the extern/static keywords */
  if (CONST == Token) {
    if (cnst)
      error(invalid, "const");
    else
      cnst = 1;
    Token = scan();
    if (VOLATILE == Token) {
      if (vltl)
        error(invalid, "volatile");
      else
        vltl = 1;
      Token = scan();
    }
  } else if (VOLATILE == Token) {
    if (vltl)
      error(invalid, "volatile");
    else
      vltl = 1;
    Token = scan();
    if (CONST == Token) {
      if (cnst)
        error(invalid, "volatile");
      else
        cnst = 1;
      Token = scan();
    }
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
      warn(ignored, "const");
    if (vltl)
      warn(ignored, "volatile");
    break;

  case CHAR:
  case INT:
  case SCHAR:
  case UINT:
  case VOID:
    prim = primtype(Token, NULL);
    /* set constant bit */
    if (cnst)
      prim |= CNST;
    /* set volatile bit */
    if (vltl)
      prim |= VLTL;

    Token = scan();
    decl(clss, prim, 0);
    break;

  case IDENT:
    if ((utype = usertype(Text)) != 0) {
      Token = scan();
      //grw - added support for const keyword
      prim =  Prims[utype];
      if (cnst) {
        if (prim & STCMASK)
          warn(ignored,"const");
        else
          prim |= CNST;
      }
      //grw - added support for volatile keyword
      if (vltl) {
        if (prim & STCMASK)
          warn(ignored, "volatile");
        else
          prim |= VLTL;
      }
      decl(clss, prim, utype);
      /* decl(clss, Prims[utype], utype); */
    }
    else {
      //grw - added support for const and volatile keywords
      /* decl(clss, PINT, 0); */
      prim = PINT;
      if (cnst)
        prim |= CNST;
      if (vltl)
        prim |= VLTL;
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
  printf(  "Memory usage: "
    "Symbols: %5d/%5d, "
    "Names: %5d/%5d, "
    "Nodes: %5d/%5d\n",
    Globs, NSYMBOLS,
    Nbot, POOLSIZE,
    Ndmax, NODEPOOLSZ);
}

void defarg(char *s) {
  char  *p;

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

/*
 * Create the name for an element(n) in a multi dimensional array
 */
static char *element_name(char *aname, int n, int fc) {
  char dname[NAMELEN+9];
  int  i;
  char ftag[8];

  strcpy(dname, aname);
  for (i = 0; i < n; i++) {
      strcat(dname, "[]");
  }
  /* if this is a function parameter, tag them so they are unique */
  if (fc) {
    sprintf(ftag, "(%d)", fc);
    strcat(dname, ftag);
  }
  dname[NAMELEN+8] = '\0';

  return strdup(dname);
}

/*
 * Create symbols for the dimensions of a multidimensional array
 * for the dimensions after the first.
 */
static int array_elements(int dimensions[], int order, int param,  char *aname, int aprim, int *asize) {
  int tdim = TARRAY;
  int yd = 0;
  int i, k;
  char *dname;
  int size = 1;
  int prim = aprim;
  static int fcnt = 0;

  /* if this is a function paramter need to make cdim arguments unique */
  if (param)
    fcnt++;

  for (i = 0; i < order; i++) {
    k = order - 1 - i;
    tdim = TARRAY | yd;
    size *= dimensions[k];
    dname = element_name(aname, k, fcnt);


    if (k > 0) {
      /* set all element primatives to same value */
      yd = addglob(dname, prim, tdim, CDIM, size, 0, NULL, 0);
    }
  }
  /* set new values for array */
  *asize = size;
  return tdim;
}


/*
 * Initialization for global (public and static) structures
 *
 * initstruct :=
 *    { struct_list }
 *
 * struct_list :=
 *   constexpr | STRLIT
 *   constexpr | STRLIT , struct_list
 */

static int initstruct(char *name, int prim, int *pinit) {
  int y = 0;
  int v = 0;
  int nsize = 0;
  int mtype = 0;
  int mprim = 0;
  int msize = 0;
  char buf[30];
  int isize = 0;
  int rsize = 0;

  y = prim & ~STCMASK;

  if (!y) {
    error("Structure %s not found", name);
    return 0;
  }

  if (NULL != name) {
    genname(name);
  } else {
    *pinit = label();
    genlab(*pinit);
  }

  lbrace();

  while (Token != RBRACE) {
    y = nextmember(y);
    if (!y) {
      error("Initialization list too long", NULL);
      break;
    }
    mtype = Types[y];
    mprim = Prims[y];
    msize = Sizes[y];

    /* debugging */
    //printf("initstruct 1 mprim = %d, mtype = %d, msize = %d\n", mprim, mtype, msize);

    //if ((mprim & STCMASK) || isArray(mtype)) {
    //  error("Complex structure initializations are not supported.", NULL);
    //  break;
    //}
    /*
     * type qualifiers do not affect type matching
     * so remove any type qualifier bits from primitive type before comparing
     */
    mprim &= ~TQMASK;
    /* debugging */
    //printf("initstruct 2 mprim = %d, mtype = %d, msize = %d\n", mprim, mtype, msize);

    if (mprim & STCMASK) {
      /* debugging */
      //printf("initstruct 3 before call to initstruct\n");
      initstruct(NULL, mprim, &v);
      //printf("initstruct 4 after call to initstruct\n");
      //printf("LBRACE = %d RBRACE =%d COMMA = %d\n", LBRACE, RBRACE, COMMA);
      //printf("initstruct 4a Token = %d\n", Token);
    } else if (isArray(mtype)) {
      /* debugging */
      //printf("initstruct 5 before call to initlist mprim = %d\n", mprim);
      isize = initlist(NULL, mprim, &v);
      //printf("initstruct 6 after call to initlist\n");

      rsize = objsize(mprim, mtype, msize);
      rsize = ALIGNED(rsize);
      if (rsize > isize) {
        rsize -= isize;
        gendata(rsize);
      }
    } else if (CHARPTR == mprim) {
    //if (CHARPTR == mprim) {
      v = strexpr();
    } else {
      v = constexpr();
    }
    //grw - add support for type qualifiers
    if (isArray(mtype) || mprim & STCMASK) {
      /* debugging */
      //printf("after complex init v = %d\n", v);
    } else if (PCHAR == mprim) {
    //if (PCHAR == mprim) {
      if (v < 0 || v > 255) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
    }
      gendefw(v);
    } else if (PSCHAR == mprim) {
      //grw - add support for type qualifiers
      if (v < -128 || v > 127) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
      }
      gendefw(v);
    } else if (CHARPTR == mprim) {
      gendefpstr(v);
    } else {
      gendefw(v);
    }
    msize = objsize(mprim, mtype, msize);
    msize = ALIGNED(msize);
    nsize += msize;
    if (COMMA == Token)
      Token = scan();
    else
      break;
    if (eofcheck()) return 0;
  }
  /* debugging */
  //printf("LBRACE = %d RBRACE =%d COMMA = %d\n", LBRACE, RBRACE, COMMA);
  //printf("initstruct 7 Token = %d\n", Token);
  Token = scan();
  /* debugging */
  //printf("initstruct 8 Token = %d\n", Token);

  //if (!n) error("too few initializers", NULL);
  return nsize;
}

/*
 * Initialization for local (auto) arrays
 *
 * Local init list
 * linitlist :=
 *    { const_list }
 *  | STRLIT
 *
 * const_list :=
 *    constexpr
 *  | constexpr , const_list
 */

static int linitstruct(int prim, int *pinit, int nstart, int outer) {
  int  n = nstart;
  int  v = 0;
  int  y = 0;
  int  i = 0;
  char buf[30];
  // grw - moved to globals for recurssion */
  //int  vbuf[MAXLOCINIT];
  //int  pbuf[MAXLOCINIT];
  int  rsize;
  int mtype = 0;
  int mprim = 0;
  int msize = 0;
  int nsize = 0;
  int bprim;


  /* debugging */
  //printf("linitstruct 1 n = %d, outer = %d\n", n, outer);

  y = prim & ~STCMASK;

  rsize = objsize(prim, TSTRUCT, 1);

  lbrace();

  while (Token != RBRACE) {
    y = nextmember(y);
    if (!y) {
      error("Initialization list too long", NULL);
      break;
    }
    mtype = Types[y];
    mprim = Prims[y];
    msize = Sizes[y];

    //if ((mprim & STCMASK) || isArray(mtype)) {
    //  error("Complex structure initializations are not supported.", NULL);
    //  break;
    //}
    /*
     * type qualifiers do not affect type matching
     * so remove any type qualifier bits from primitive type before comparing
     */
    bprim = mprim & ~TQMASK;
    /* debugging */
    //printf("linitstruct 2 mprim = %d, mtype = %d, msize = %d\n", mprim, mtype, msize);

    if (mprim & STCMASK) {
      /* debugging */
      //printf("linitstruct 3 before call to linitstruct n =%d\n", n);
      n = linitstruct(mprim, &v, n, 0);
      //printf("linitstruct 4 after call to linitstruct n = %d\n", n);
    } else if (isArray(mtype)) {
      /* debugging */
      //error("Complex structure with array initializations are not supported.", NULL);
      //printf("initstruct 5 before call to linitlist mprim = %d, n = %d\n", mprim, n);
      n = linitlist(msize, mprim, &v, n, 0);
      //printf("initstruct 6 after call to linitlist n = %d\n", n);
    } else if (CHARPTR == bprim) {
      v = strexpr();
    } else {
      v = constexpr();
    }

     //grw - add support for type qualifiers
    if (isArray(mtype) || mprim & STCMASK) {
       /* debugging */
       //printf("linitstruct 5 (skip complex init) v = %d\n", v);
    } else if (PCHAR == bprim) {
       /* debugging */
       //printf("linitstruct 6 (char) n = %d, v = %d\n", n, v);

      if (v < 0 || v > 255) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
    }
      /* add to the member buffer */
      vbuf[n] = v;
      pbuf[n++] = mprim;
    } else if (PSCHAR == bprim) {
      /* debugging */
      //printf("linitstruct 6 (signed char)  n = %d, v = %d\n",n, v);

      if (v < -128 || v > 127) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
      }
      /* add to the member buffer */
      vbuf[n] = v;
      pbuf[n++] = mprim;
    } else {
      /* add to the member buffer */
      /* debugging */
      //printf("linitstruct 7 (default)  n = %d, prim = %d, v = %d\n", mprim, n, v);
      vbuf[n] = v;
      pbuf[n++] = mprim;
    }
    //n++;
    msize = objsize(mprim, mtype, msize);
    msize = ALIGNED(msize);
    nsize += msize;

    if (COMMA == Token)
      Token = scan();
    else
      break;
    if (eofcheck()) return 0;
  }
  /* mark init to not move stack */
  *pinit = 2;

  Token = scan();
  /* debugging */
  //printf("nsize = %d, rsize = %d\n", nsize, rsize);

  if (nsize < rsize) {
    v = ALIGNED(rsize - nsize)/2;


    for (i = 0;  i < v; i++) {
      //grw - pad with zero int for uninitialized member fields
      /* debugging */
      printf("padding (v) = %d\n", v);
      vbuf[n] = 0;
      pbuf[n++] = PINT;
    }
  } else if (nsize > rsize) {
    error("Initialization list is too large.", NULL);
  }

  /* push structure data backwards onto stack */
  if (outer) {
    writeldata(n);
  }
  return n;
}

/*
 * Add an local static object entry for a static structure
 */
static void addmemberlso(int y, int i, int value, int init) {
int mtype = Types[y];
int mprim = Prims[y];
int msize = Sizes[y];

msize = objsize(mprim, mtype, msize);
msize = ALIGNED(msize);

/* debugging */
printf("adding lso i = %d, y = %d, mprim = %d, mtype = %d, msize = %d, val = %d, init = %d\n",
  i, y, mprim, mtype, msize, value, init);

ls_objs[lso_idx].isize = 0;
ls_objs[lso_idx].ilist = NULL;
//grw - only print label on first member field of structure
//grw - char pointer is reversed from other types
if (mprim == CHARPTR)
  addlso(mprim, mtype, msize, i ? 0 : value, init);
else
  addlso(mprim, mtype, msize, i ? 0 : init, value);
}
/*
 * Initialization for static local structures
 *
 *  :=
 *    { const_list }
 *
 *
 * const_list :=
 *    constexpr | STRLIT
 *  | constexpr | STRLIT, const_list
 */

static int sinitstruct(int prim, int *pval, int *pinit) {
  int  n = 0;
  int  v = 0;
  int  i = 0;
  char errbuf[30];
  int  y = 0;
  int  rsize;
  int mtype = 0;
  int mprim = 0;
  int msize = 0;
  int nsize = 0;

  /* debugging */
  printf("sinitstruct prim = %d pval =%d, pinit = %d\n", prim, *pval, *pinit);

  y = prim & ~STCMASK;

  rsize = objsize(prim, TSTRUCT, 1);
  *pinit = label();
  lbrace();
  while (Token != RBRACE) {
    y = nextmember(y);
    if (!y) {
      error("Initialization list too long", NULL);
      break;
    }
    mtype = Types[y];
    mprim = Prims[y];
    msize = Sizes[y];

    /*
     * type qualifiers do not affect type matching
     * so remove any type qualifier bits from primitive type before comparing
     */
    mprim &= ~TQMASK;

    if (mprim & STCMASK) {
      /* debugging */
      printf("sinitstruct 1 before call to sinitstruct\n");
      //grw - call sinstruct with dummy values
      sinitstruct(mprim, &v, &i);
      printf("sinitstruct 2 after call to sinitstruct v = %d, i = %d\n", v, i);
    } else if (isArray(mtype)) {
      /* debugging */
      printf("sinitstruct 3 before call to sinitlist i = %d\n", i);
      if (chartype(mprim))
        msize = ALIGNED(msize);
      sinitlist(msize, mprim, &i);
      /* debugging */
      printf("sinitstruct 4 after call to sinitlist i = %d\n", i);
      //grw - label string inside structure
      i = label();
      addlso(mprim, mtype, msize, i, 0);

    } else if (CHARPTR == mprim) {
      v = strexpr();
    } else {
      v = constexpr();
    }

    /*
     * type qualifiers do not affect type matching
     * so remove any type qualifier bits from primitive type before comparing
     */
    if ((mprim & STCMASK) || isArray(mtype)) {
      /* debugging */
      printf("sinitstruct complex type *pinit = %d, v = %d, i = %d\n", *pinit, v, i);
      //grw - set values to skip complex member
      //ibuf[n] = 0;
      //ybuf[n] = 0;
    } else if (PCHAR == mprim) {
      if (v < 0 || v > 255) {
        sprintf(errbuf, "%d", v);
        error("initializer out of range: %s", errbuf);
      }
      /* add to the character array buffer */
      addmemberlso(y, n, *pinit, v);
      //ibuf[n] = v;
      //ybuf[n] = y;
    } else if (PSCHAR == mprim) {
      //grw - add support for type qualifiers
      if (v < -128 || v > 127) {
        sprintf(errbuf, "%d", v);
        error("initializer out of range: %s", errbuf);
      }
      /* add to the character array buffer */
      addmemberlso(y, n, *pinit, v);
      //ibuf[n] = v;
      //ybuf[n] = y;
    } else if (CHARPTR == mprim) {
      /* character pointer label is in init */
      addmemberlso(y, n, *pinit, v);
    } else {
      /* add to the integer array buffer */
      addmemberlso(y, n, *pinit, v);
    }
    n++;
    msize = objsize(mprim, mtype, msize);
    msize = ALIGNED(msize);
    nsize += msize;
    if (COMMA == Token)
      Token = scan();
    else
      break;
    if (eofcheck()) return 0;
  }
  Token = scan();

  /* debugging */
  printf("sinitstruct: nsize = %d, rsize = %d\n", nsize, rsize);
  if (nsize < rsize) {
    v = rsize - nsize;
    /* debugging */
    printf("sinitstruct: padding v = %d\n", v);
    addlso(PCHAR, TARRAY, v, 0, 0);
  } else if (nsize > rsize) {
    error("Initialization list is too large.", NULL);
  }
  *pval = 1;
  /* debugging */
  printf("sinitstruct: returning *pinit = %d, *pval = %d, n = %d\n", *pinit, *pval, n);
  return n;
}

/*
 * Initialization for arrays in local (auto) structures
 *
 * Local init list
 * linitlist :=
 *    { const_list }
 *  | STRLIT
 *
 * const_list :=
 *    constexpr
 *  | constexpr , const_list
 */

static int linitlist(int size, int mprim, int *pinit, int nstart, int outer) {
  int  n = nstart;
  int  v = 0;
  int  len = 0;
  int  i = 0;
  char buf[30];
//  int  ibuf[MAXLOCINIT];
  char sbuf[MAXLOCSTR];
  int  rsize;
  int  k = 0;
  int  bprim;

  //grw - need to stack align character arrays
  if(chartype(mprim)) {
    rsize = ALIGNED(size);
  } else {
    rsize = size;
  }

  if (STRLIT == Token) {
    // if (PCHAR != prim)
    if (!chartype(mprim))
      error("initializer type mismatch", NULL);
    //grw - update to allow concatenation of string literals
    v = 0;
    /* concatenate string literals */
    while (STRLIT == Token) {
      len = strlen(Text);
      /* don't process empty strings */
      if (len > 2) {
      /* copy characters in string, skipping quote marks at end */
      for(i = 1; i < len-1; i++) {
        /* debugging */
        //printf("Adding sbuf[%d] = '%c'\n", (v+i-1), Text[i]);
        sbuf[v+i-1] = Text[i];
      }
      v += (Value-2);
      }
      Token = scan();
    }
    if (v >= MAXLOCSTR) {
      v = MAXLOCSTR - 1;
      error("Local string initializer is too long", NULL);
    }
    /* set null at end of concatenated string */
    sbuf[v] = '\0';

    /* if dynamically sized, calculate stack size for string + 1 for null */
    if (0 == rsize) {
        //grw - created macro for alignment size
        rsize = ALIGNED(v+1);
    }
    if (v < rsize) {
      /* subtract one for null written with string */
      k = rsize - v - 1;
      /* debugging */
      //printf("k  = %d, rsize = %d, v = %d\n", k, rsize, v);
      /* pad unitialized elements with nulls */
      for(i=0; i < k; i++) {
        sbuf[v+i+1] = '\0';
      }
    }
    //grw - push characters onto buffer
    for (i = 0; i < rsize; i++) {
        pbuf[n] = mprim;
        vbuf[n++] = sbuf[i];
    }

    /* mark init to not move stack */
    *pinit = 2;

    //grw - write values to stack
    if (outer) {
      writeldata(n);
    }

    /* return elements added to pbuf */
    return n;
  }
  /*
   * type qualifiers do not affect type matching
   * so remove any type qualifier bits from primitive type before comparing
   */
  bprim = mprim & ~TQMASK;
  lbrace();
  //grw - use k as counter
  k = 0;
  while (Token != RBRACE) {
    if (mprim & STCMASK) {
      /* debugging */
      //printf("linitlist 1 before call to linitstruct n =%d\n", n);
      n = linitstruct(mprim, &v, n, 0);
      //printf("linitlist 2 after call to linitstruct n = %d\n", n);
    } else if (CHARPTR == bprim) {
      v = strexpr();
    } else {
      v = constexpr();
    }
    //grw - add support for type qualifiers
    if (mprim & STCMASK) {
      /* debugging */
      //printf("linitlist complex type v = %d\n", v);
    } else if (PCHAR == bprim) {
      if (v < 0 || v > 255) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
    }
      /* add to the array buffer */
      pbuf[n] = mprim;
      vbuf[n++] = v;
    } else if (PSCHAR == bprim) {
      //grw - add support for type qualifiers
      if (v < -128 || v > 127) {
        sprintf(buf, "%d", v);
        error("initializer out of range: %s", buf);
      }
      /* add to the char buffer */
      pbuf[n] = mprim;
      vbuf[n++] = v;
    } else {
      /* add to the array buffer */
      pbuf[n] = mprim;
      vbuf[n++] = v;
    }
    k++;
    if (COMMA == Token)
      Token = scan();
    else
      break;
    if (eofcheck()) return 0;
  }
  /* mark init to not move stack */
  *pinit = 2;
  Token = scan();
  if (k < rsize) {
    v = rsize - k;
    for (i = 0;  i < v; i++) {
      //grw - pad with bytes for char arrays
      if (chartype(mprim)){
        pbuf[n] = mprim;
        vbuf[n++] = '\0';
      } else {
        pbuf[n] = mprim;
        vbuf[n++] = 0;
      }
    }
  }
  /* if outer loop, push data onto stack */
  if (outer) {
    writeldata(n);
  }
  /*
   * If this is the outer loop, return number of elements,
   * for inner loop, return next index for data values
   */
  return outer ? k : n;
}

/*
 *  Write out the local (auto) data to the stack
 */
static void writeldata(int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (CHARPTR == pbuf[n-1-i])
      genldlab(vbuf[n-1-i]);
    else if (chartype(pbuf[n-1-i]))
      genbyte(vbuf[n-1-i]);
    else
      genlit(vbuf[n-1-i]);
  }
}
