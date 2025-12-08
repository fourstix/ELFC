/*
 *	NMH's Simple C Compiler, 2011--2014
 *	Global variables
 */

#ifndef extern_
 #define extern_ extern
#endif

extern_ FILE	*Infile;
extern_ FILE	*Outfile;
extern_ int	Token;
extern_ char	Text[TEXTLEN+1];
extern_ int	Value;
extern_ int	Line;
extern_ int	Errors;
extern_ int	Syntoken;
extern_ int	Putback;
extern_ int	Rejected;
extern_ int	Rejval;
extern_ char	Rejtext[TEXTLEN+1];
extern_ char	*File;
extern_ char	*Basefile;
extern_ char	*Fpath;
extern_ char	*Macp[MAXNMAC];
extern_ int	Macc[MAXNMAC];
extern_ int	Mp;
/* Macro Parameter counts */
//extern_ int Margc[MAXNMAC];
/* Macro arg entries */
struct marg_entry {
  int  id;
  char *text;
};
/* Marco args count */
extern_ int	Margp;
/* Macro args table */
extern_ struct marg_entry Margs[MAXNMAC];
/* Macro arg text to replace */
extern_ char *Mhide[MAXMARGS];
/* Macro parameters */
extern_ char *Mshow[MAXMARGS];

extern_ int	Expandmac;
extern_ int	Ifdefstk[MAXIFDEF], Isp;
extern_ int	Inclev;
extern_ int	Textseg;
extern_ int	Nodes[NODEPOOLSZ];
extern_ int	Ndtop;
extern_ int	Ndmax;

/* symbol tabel structure */
extern_ char	*Names[NSYMBOLS];
extern_ int	Prims[NSYMBOLS];
extern_ char	Types[NSYMBOLS];
extern_ char	Stcls[NSYMBOLS];
extern_ int	Sizes[NSYMBOLS];
extern_ int	Vals[NSYMBOLS];
extern_ char	*Mtext[NSYMBOLS];
extern_ int	Globs;
extern_ int	Locs;

extern_ int	Thisfn;

/* name list */
extern_ char	Nlist[POOLSIZE];
extern_ int	Nbot;
extern_ int	Ntop;

/* label stacks */
extern_ int	Breakstk[MAXBREAK], Bsp;
extern_ int	Contstk[MAXBREAK], Csp;
extern_ int	Retlab;

/* local init structure */
extern_ int	LIaddr[MAXLOCINIT];
extern_ int	LIval[MAXLOCINIT];
extern_ int	Nli;

/* synthesizer operand queue */
//grw - refactor Q_type to Q_jmp, Q_val to Q_dest
//extern_ int	Q_type;
//extern_ int	Q_val;
//grw - removed Q_name
//extern_ char	Q_name[NAMELEN+1];
//grw - added logic to eliminate push followed by immediate pop
extern_ int	Q_jmp;
extern_ int	Q_dest;
extern_ int	Q_cmp;
extern_ int	Q_bool;
extern_ int	Q_push;

/* file collector */
extern_ char	*Files[MAXFILES];
extern_ char	Temp[MAXFILES];
extern_ int	Nf;

/* options */
extern_ int	O_verbose;
extern_ int	O_componly;
extern_ int	O_asmonly;
extern_ int	O_testonly;
//grw - added no c libs option
extern_ int	O_clibs;
extern_ char	*O_outfile;
extern_ int	O_debug;
//grw - added library object action
extern_ int	O_library;

//grw - create string table
//grw - convert string table to array of structures
struct str_entry {
  int  label;
  char *text;
  int  len;
};
/*
extern_ int	str_lab[MAXSTRTBL];
extern_ char *str_text[MAXSTRTBL];
extern_ int	str_len[MAXSTRTBL];
*/
extern_ struct str_entry str_tbl[MAXSTRTBL];
extern_ int str_idx;

//grw - added support for local labels and goto

/* entry for local lables*/
struct  llbl_entry {
  int  scope;
  char *text;
  int  defined;
};
/* table for local lables */
extern_ struct llbl_entry lcl_lbls[MAXUSRLBL];
/* index for local labels */
extern_ int llbl_idx;
