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
void	gendiv(int swap);
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
void	genmod(int swap);
void	genmul(void);
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
void	genshl(int swap);
void	genshr(int swap);
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
