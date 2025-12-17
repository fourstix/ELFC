/*
 *	NMH's Simple C Compiler, 2011--2014
 *	Function declarations
 */

int	addglob(char *name, int prim, int type, int scls, int size, int val,
		char *mval, int init);
int	addloc(char *name, int prim, int type, int scls, int size, int val,
		int init);
int	binoptype(int op, int p1, int p2);
int	chrpos(char *s, int c);
void	clear(int q);
void	cleanup(void);
void	clrlocs(void);
void	colon(void);
void	commit(void);
void	commit_bool(void);
void	commit_cmp(void);
void	compound(int lbr);
int	comptype(int p);
int	constexpr(void);
void	copyname(char *name, char *s);
int	deref(int p);
void	dumpsyms(char *title, char *sub, int from, int to);
void	dumptree(node *a);
void	emittree(node *a);
int	eofcheck(void);
void	error(char *s, char *a);
void	expr(int *lv, int cvoid);
void	fatal(char *s);
int	findglob(char *s);
int	findloc(char *s);
int	findmem(int y, char *s);
int	findstruct(char *s);
int	findsym(char *s);
int	findmac(char *s);
node	*fold_reduce(node *n);
int	frozen(int depth);
char	*galloc(int k, int align);
void	gen(char *s);
int	genadd(int p1, int p2, int swap);
void	genaddr(int y);
//grw - removed genalign and genaligntext
//void	genalign(int k);
//void	genaligntext(void);
void	genand(void);
void	genasop(int op, int *lv, int p2);
void	genbool(void);
void	genbrfalse(int dest);
void	genbrtrue(int dest);
//grw - added short-circuit code generators
void	genscfalse(int dest);
void	gensctrue(int dest);
void	genbss(char *name, int len, int statc);
void	gencall(int y);
void	gencalr(void);
void	gencmp(char *inst);
//grw - removed gendata
//void	gendata(void);
void	gendefb(int v);
void	gendefp(int v);
void	gendefs(char *s, int len);
void	gendefw(int v);
//grw - added support for signed and unsigned
void	gendiv(int sgn);
void	genentry(void);
//grw - added support for user labels and goto
void	genexit(int scope);
void	geninc(int *lv, int inc, int pre);
void	genind(int p);
void	genior(void);
void	genjump(int dest);
void	genlab(int id);
void	genldlab(int id);
void	genlit(int v);
void	genln(char *s);
void	genlocinit(void);
void	genlognot(void);
//grw - added support for signed and unsigned
void	genmod(int sgn);
void	genmul(int sgn);
void	genname(char *name);
void	genneg(void);
void	gennot(void);
void	genpostlude(void);
void	genprelude(void);
void	genpublic(char *name);
void	genpush(void);
void	genpushlit(int n);
void	genraw(char *s);
void	genrval(int *lv);
void	genscale(void);
void	genscale2(void);
void	genscaleby(int v);
//grw - removed swap argument
//void	genshl(int swap);
//void	genshr(int swap);
void	genshl(void);
void	genshr(void);
void	genstack(int n);
void	genstore(int *lv);
int	gensub(int p1, int p2, int swap);
void	genswitch(int *vals, int *labs, int nc, int dflt);
//grw - removed gentext
//void	gentext(void);
void	genxor(void);
char	*globname(char *s);
char	*gsym(char *s);
void	ident(void);
void	init(void);
void	initopt(void);
//grw - check for compatible int types (true for int and char types)
int	inttype(int p);
int	label(void);
char	*labname(int id);
void	lbrace(void);
void	lgen(char *s, char *inst, int n);
void	lgen2(char *s, int v1, int v2);
void	load(void);
void	lparen(void);
node	*mkbinop(int op, node *left, node *right);
node	*mkbinop1(int op, int n, node *left, node *right);
node	*mkbinop2(int op, int n1, int n2, node *left, node *right);
node	*mkleaf(int op, int n);
node	*mkunop(int op, node *left);
node	*mkunop1(int op, int n, node *left);
node	*mkunop2(int op, int n1, int n2, node *left);
void	match(int t, char *what);
//grw
//char	*newfilename(char *name, int sfx);
char	*newfilename(char *name, char* sfx);
int	next(void);
//grw - added ngenraw
void ngenraw(char *s, char *inst, int n);
void	ngen(char *s, char *inst, int n);
void	ngen2(char *s, char *inst, int n, int a);
void	notvoid(int p);
int	objsize(int prim, int type, int size);
node	*optimize(node *n);
void	opt_init(void);
void	playmac(char *s);
int	pointerto(int prim);
void	preproc(void);
int	primtype(int t, char *s);
void	program(char *name, FILE *in, FILE *out, char *def);
void	putback(int t);
void	queue_cmp(int op);
//arh - Add declaration of function from gen.c
void queue_jmp(int val);
void	rbrace(void);
void	rbrack(void);
void	reject(void);
void	rexpr(void);
void	rparen(void);
int	scan(void);
int	scanraw(void);
void	scnerror(char *s, int c);
void	semi(void);
void	sgen(char *s, char *inst, char *s2);
void	sgen2(char *s, char *inst, int v, char *s2);
int	skip(void);
void	spill(void);
int	synch(int syn);
void	top(void);
int	typematch(int p1, int p2);
int	usertype(char *s);

//grw - functions to get and save return value to expression stack
void genpushd(void);
void genpopd(void);
//grw - added raw character output function
void cgenraw(char *s, char ch);
//grw - added raw string output function
void sgenraw(char *s, char *inst, char *s2);
//grw - added function for assembly statement outputs
void genasm(char *strlit);

//grw - function to add string to string table
void addstr(int label, char *text, int len);
//grw - concatenate a string to previous string entry
void concatstr(char *text, int len);
//grw - function to write out strings
void genstrtbl(void);
//grw - function for character type
int	chartype(int p);
//grw - function for signed or unsigned type
int	signtype(int p);
//grw - function for signed or unsigned operand
int unsgnop(int p1, int p2);
//grw - level of multiple pointer indirection
int ptrlevel(int ptype);
//grw - return the base type of pointer or primitive type
int basetype(int ptype);
//grw - determine if a type is a pointer to void
int isvoidptr(int ptype);
//grw - determine if a type is a pointer to function
int isfunptr(int ptype);
//grw - set the type with a new level of pointer indirection
int setptrlevel(int ptype, int lvl);
//grw - functions to support user labels and goto
//grw - generate an instruction with a user label
void llgen(char *s, char *inst, int n);
//grw - generate a user lable
void genllab(int id);
//grw - get the local label name
/* char *llabname(int id); */
//grw - find a local label in the list
int findLocalLabel(int scope, char *text);
//grw - add a new user label to the list
int addLocalLabel(int fn, char *text, int defined);
//grw - added support for user labels and goto
void gengoto(int dest);
//grw - added support for user labels and goto
void chklocals(int scope);
//grw - added warning to compiler
void	warn(char *s, char *a);
//grw - added logic to assign struct/union
void	gencopy(int *lv);
//grw - added support for const keyword
int allowasgmnt(int *lv);
//grw - check for int types alone (true for int , false for char types)
int	pinttype(int p);
//grw - check to see if two pointers are compatible
int compatible(int p1, int p2);
//grw - load macro arguments into Mhide array
int findargs(int id);
//grw - scan macro parameters int Mshow array
int scanparams(char *name);
//grw - replace macro arguments with macro parameters
void prepmac(char *mb, char *m, int nargs);
//grw - function to trim a macro parameter for pasting
int trim(char *pb, int max);
//grw - function to foramt a macro parameter as a string literal
int stringify(char *pb, int max);
//grw - test to see if a string is all whitespace or empty
int blank(char *p);
