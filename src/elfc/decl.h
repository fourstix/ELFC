/*
 *	NMH's Simple C Compiler, 2011,2012
 *	Function declarations
 */

int	addglob(char *name, int prim, int ttype, int scls, int size, int val,
		char *mval, int init);
int	addloc(char *name, int prim, int type, int scls, int size, int val,
		int init);
void	cerror(char *s, int c);
int	chrpos(char *s, int c);
void	clear(void);
void	clrlocs(void);
void	colon(void);
void	compound(int lbr);
int	constexpr(void);
void	copyname(char *name, char *s);
int	declarator(int pmtr, int scls, char *name, int *pprim, int *psize,
		int *pval, int *pinit);
void	dumpsyms(char *title, char *sub, int from, int to);
int	eofcheck(void);
void	error(char *s, char *a);
int	expr(int *lv);
void	fatal(char *s);
int	findglob(char *s);
int	findloc(char *s);
int	findmac(char *s);
int	frozen(int depth);
void	gen(char *s);
int	genadd(int p1, int p2, int swapped);
void	genaddr(int y);
void	genand(void);
void	genargc(void);
void	genasop(int op, int p1, int p2, int swapped);
int	genbinop(int op, int p1, int p2);
void	genbool(void);
void	genbrfalse(int dest);
void	genbrtrue(int dest);
void	genbss(char *name, int len);
void	gencall(int y);
void	gencalr(void);
void	gencmp(char *inst);
void	gendata(void);
void	gendefb(int v);
void	gendefl(int id);
void	gendefp(int v);
void	gendefs(char *s, int len);
void	gendefw(int v);
void	gendiv(int swapped);
void	genentry(void);
void	genexit(void);
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
void	genmod(int swapped);
void	genmul(void);
void	genname(char *name);
void	genfname(char *name);
void	genneg(void);
void	gennot(void);
void	genpostlude(void);
void	genprelude(void);
void	genpublic(char *name);
void	genfpublic(char *name);
void	genpush(void);
void	genpushlit(int n);
void	genraw(char *s);
void	genscale(void);
void	genscale2(void);
void	genshl(int swapped);
void	genshr(int swapped);
void	genstack(int n);
void	genstore(int op, int *lv, int *lv2);
int	gensub(int p1, int p2, int swapped);
void	genswitch(int *vals, int *labs, int nc, int dflt);
void	gentext(void);
void	genxor(void);
char	*globname(char *s);
char	*gsym(char *s);
void	ident(void);
int	inttype(int p);
int	label(void);
char	*labname(int id);
void	lbrace(void);
void	lgen(char *s, char *inst, int n);
void	lgen2(char *s, int v1, int v2);
void	load(void);
void	lparen(void);
void	match(int t, char *what);
//grw
/* char	*newfilename(char *name, int sfx); */
char	*newfilename(char *name, char* sfx);
int	next(void);
//grw - added ngenraw 
void ngenraw(char *s, char *inst, int n);
void	ngen(char *s, char *inst, int n);
void	ngen(char *s, char *inst, int n);
void	ngen2(char *s, char *inst, int n, int a);
int	objsize(int prim, int type, int size);
void	playmac(char *s);
int	pointerto(int prim);
void	preproc(void);
int	primtype(int t);
void	putback(int t);
void	rbrack(void);
void	reject(void);
int	rexpr(void);
void	rparen(void);
void	rvalue(int *lv);
int	scan(void);
int	scanraw(void);
void	semi(void);
void	sgen(char *s, char *inst, char *s2);
int	skip(void);
int	synch(int syn);
void	top(void);
int	typematch(int p1, int p2);

//grw - functions to get and save return value to expression stack
void genpushd(void);
void genpopd(void);
//grw - added raw character output function
void cgenraw(char *s, char ch);
//grw - added raw string output function
void sgenraw(char *s, char *inst, char *s2);

//grw - added function for assembly statement outputs
void genasm(char *strlit);
