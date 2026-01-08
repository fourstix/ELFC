/*
 *	NMH's Simple C Compiler, 2011--2014
 *	Main program
 */

#include "defs.h"
#define extern_
 #include "data.h"
#undef extern_
#include "decl.h"
#include "modpath.h"

static void cmderror(char *s, char *a) {
  //grw
  //fprintf(stderr, "scc: ");
	fprintf(stderr, "elfc: ");
	fprintf(stderr, s, a);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}

void cleanup(void) {
	if (!O_testonly && NULL != Basefile) {
    //grw - use extensions for Asm/02 and Link/02
		//remove(newfilename(Basefile, 's'));
		//remove(newfilename(Basefile, 'o'));
    remove(newfilename(Basefile, "asm"));
		remove(newfilename(Basefile, "prg"));

	}
}
//grw - rewrote newfilename function for multiple character suffix
char *newfilename(char *file, char* sfx) {
	int   len = (int)(strlen(file) + strlen(file) + 1);
	char *ofile = malloc(len);
	char *p;
	if (ofile == NULL) return NULL;

	strcpy(ofile, file);
	/* truncate the string one past the last period */
	p = strrchr(ofile, '.');
	if (p != NULL) {
		p++;
		*p = 0;
  } /* if */

	strcat(ofile, sfx);
	return ofile;
}


static int filetype(char *file) {
	int	k;

	k = (int)strlen(file);
	if ('.' == file[k-2]) return file[k-1];
	return 0;
}

static int exists(char *file) {
	FILE	*f;

	if ((f = fopen(file, "r")) == NULL) return 0;
	fclose(f);
	return 1;
}

//grw - elimiate __dos conditional code
static void compile(char *file, char *def) {
	char	*ofile;
	FILE	*in, *out;

	in = stdin;
	out = stdout;
	ofile = NULL;
	if (file) {
    //grw change logic to support extension
		//ofile = newfilename(file, 's');
    ofile = newfilename(file, "asm");
		if ((in = fopen(file, "r")) == NULL)
			cmderror("no such file: %s", file);
		if (!O_testonly) {
      //grw - overwrite should be okay?
			//if ((out = fopen(ofile, "r")) != NULL)
			//	cmderror("will not overwrite file: %s",
			//		ofile);
			if ((out = fopen(ofile, "w")) == NULL)
				cmderror("cannot create file: %s", ofile);
		}
	}
	if (O_testonly) out = NULL;
	if (O_verbose) {
		if (O_testonly)
			printf("elfc -t %s\n", file);
		else
      printf("compiling %s\n", file);

    //grw - removed old extra verbose messages
  	//	if (O_verbose > 1)
		//		printf("elfc -S -o %s %s\n", ofile, file);
		//	else
		//printf("compiling %s\n", file);
	}
	program(file, in, out, def);
	if (file) {
		fclose(in);
		if (out) fclose(out);
	}
}

static void collect(char *file, int temp) {
	if (O_componly || O_asmonly) return;
	if (Nf >= MAXFILES)
		cmderror("too many input files", NULL);
	Temp[Nf] = temp;
	Files[Nf++] = file;
}

static void assemble(char *file, char *path) {
	char	*ofile;
	char	cmd[TEXTLEN+1];
  char  *vb;

  //grw - add support for quiet flag
  vb = (O_verbose > 0) ? "" : "-q";

  //grw - Asm/02 specifies object name
	//file = newfilename(file, 's');
	//if (O_componly && O_outfile)
	//	ofile = O_outfile;
	//else
	//	collect(ofile = newfilename(file, 'o'), 1);
  //if (O_componly && O_outfile)
  //	ofile = O_outfile;
  ofile = newfilename(file, "asm");

	if (strlen(ofile) + strlen(ASCMD) + strlen(vb) >= TEXTLEN)
		cmderror("assembler command too long", NULL);

  //grw - snprintf is safer
	snprintf(cmd, sizeof(cmd), ASCMD, path, vb, path, ofile);

  //grw - show assembly command
  if (O_verbose > 0) printf("%s\n", cmd);

	if (system(cmd)) {
		cmderror("assembler invocation failed", NULL);
  } else {
    collect(newfilename(file, "prg"), 1);
  }
  //grw - don't delete files
	//if (delete) {
	//	if (O_verbose > 2) printf("rm %s\n", file);
	//	remove(file);
	//}
}

//arh - removed unused function concat
//grw need to pass filename to Link/02
static void link(char *fname, char *path) {
  //grw - larger command size for linker
	char	cmd[CMDLEN+1];
  //grw - modules to be linked
	char	mods[TEXTLEN+1];
	char	*ofile;
  //grw - add binary file name
  char	*binfile;
  int   i;
  char  *vb;

  //grw - add support for quiet flag
  vb = (O_verbose > 0) ? "" : "-q";

  //grw - initialize of file to output file name
  ofile = newfilename(fname, "prg");
  binfile = newfilename(fname, "elfos");

  //grw - set up initial mods list
  strcpy(mods, ofile);

  //grw - rewrote logic for Link/02 add remaining modules to list
  for (i=1; i < Nf; i++) {
    if (Temp[i]) {
      strcat(mods, " ");
      strcat(mods, Files[i]);
    }
  }

  //grw - check length of command
  if (strlen(O_outfile) + 6 + strlen(mods) + strlen(LDCMD) + strlen(SYSLIBC) +
      strlen(binfile) + strlen(path) + strlen(vb) >= CMDLEN)
	 	cmderror("linker command too long", NULL);

  //grw - snprintf is safer
  snprintf(cmd, sizeof(cmd), LDCMD, path, vb, path, path, mods);

  /* add outfile name option to linker command */
  if (strlen(O_outfile)) {
    strcat(cmd, " -o ");
    strcat(cmd, O_outfile);
  } else {
    strcat(cmd, " -o ");
    strcat(cmd, binfile);
  }

  //grw - added no c libs option
  if (O_clibs)
    strcat(cmd, SYSLIBC);
  else
     strcat(cmd, ELFLIBC);

  //grw - simplified logic to not remove files
	//if (O_verbose > 2) printf("rm ");
	//for (i=0; i<Nf; i++) {
	//	if (Temp[i]) {
	//		if (O_verbose > 2) printf(" %s", Files[i]);
	//		remove(Files[i]);
	//	}
	//}
	//if (O_verbose > 2) printf("\n");
  if (O_verbose > 0) printf("%s\n", cmd);
  if (system(cmd))
    cmderror("linker invocation failed", NULL);
}

static void usage(void) {
  //grw
	//printf("Usage: scc [-h] [-ctvNSV] [-d opt] [-o file] [-D macro[=text]]"
	//	" file [...]\n");
  printf("Usage: elfc [-h] [-ctvLNSV] [-d opt] [-o file] [-D macro[=text]] file [...]\n");
}

static void longusage(void) {
	printf("\n");
	usage();
	printf(	"\n"
		"-c       compile and assemble only, do not link\n"
		"-d opt   activate debug option OPT, ? = list\n"
		"-o file  write linker output to FILE\n"
		"-t       test only, generate no code\n"
		"-v       verbose output\n"
		"-D m=v   define macro M with optional value V\n"
  	"-L       compile and assemble a library object file\n"
		//grw - added no c libs option
    "-N       do not link stdlib and stdio by default\n"
    //grw - added play macro option
    "-P       print expanded macro text\n"
		"-S       compile to assembly language\n"
		"-V       print version and exit\n"
		"\n" );
}

static void version(void) {
	printf("ElfC version %s for %s %s\n", VERSION, OS, CPU);
}

static char *nextarg(int argc, char *argv[], int *pi, int *pj) {
	char	*s;

	if (argv[*pi][*pj+1] || *pi >= argc-1) {
		usage();
		exit(EXIT_FAILURE);
	}
	s = argv[++*pi];
	*pj = (int)(strlen(s)-1);
	return s;
}

static int dbgopt(int argc, char *argv[], int *pi, int *pj) {
	char	*s;

	s = nextarg(argc, argv, pi, pj);
	if (!strcmp(s, "lsym")) return D_LSYM;
	if (!strcmp(s, "gsym")) return D_GSYM;
	if (!strcmp(s, "stat")) return D_STAT;
	printf(	"\n"
    //grw
		//"scc: valid -d options are: \n\n"
    "elfc: valid -d options are: \n\n"
		"lsym - dump local symbol tables\n"
		"gsym - dump global symbol table\n"
		"stat - print usage statistics\n"
		"\n");
	exit(EXIT_FAILURE);
}

static char exe_path[MAXPATH];

int main(int argc, char *argv[]) {
	int	i, j;
	char	*def;
  //grw need to pase first file name to Asm/02 and Link/02
  char  *fname = NULL;

	def = NULL;
	O_debug = 0;
	O_verbose = 0;
	O_componly = 0;
	O_asmonly = 0;
	O_testonly = 0;
    //grw - added no c libs option
	O_clibs = 1;
	O_outfile = "";
  //grw - added library option
  O_library = 0;
  //grw - added play macro option
  O_playmac = 0;


	//arh - Get absolute path of executable to locate files and tools
	get_module_path(exe_path, MAXPATH);
	Fpath = exe_path;

	for (i=1; i<argc; i++) {
		if (*argv[i] != '-') break;
		if (!strcmp(argv[i], "-")) {
			compile(NULL, def);
			exit(Errors? EXIT_FAILURE: EXIT_SUCCESS);
		}
		for (j=1; argv[i][j]; j++) {
			switch (argv[i][j]) {
			case 'c':
				O_componly = 1;
				break;
			case 'd':
				O_debug |= dbgopt(argc, argv, &i, &j);
				O_testonly = 1;
				break;
			case 'h':
				longusage();
				exit(EXIT_SUCCESS);
			case 'o':
				//grw need to add -o O_outfile to linker command
				O_outfile = nextarg(argc, argv, &i, &j);
				break;
			case 't':
				O_testonly = 1;
				break;
			case 'v':
				O_verbose++;
				break;
			case 'D':
				if (def) cmderror("too many -D's", NULL);
				def = nextarg(argc, argv, &i, &j);
				break;
      case 'L':
				O_library = 1;
				break;
				//grw - added no c lib option
      case 'N':
				//grw - don't link stdlib and stdio
				O_clibs = 0;
				break;
      case 'P':
        //grw - don't link stdlib and stdio
        O_playmac = 1;
        break;
			case 'S':
				O_componly = O_asmonly = 1;
				break;
			case 'V':
				version();
				exit(EXIT_SUCCESS);
			default:
				usage();
				exit(EXIT_FAILURE);
			}
		}
	}
	if (i >= argc) {
		usage();
		exit(EXIT_FAILURE);
	}
	Nf = 0;
	while (i < argc) {
		if (filetype(argv[i]) == 'c') {
			compile(argv[i], def);
			//grw - set name for linker
      if (fname == NULL) {
			  fname = argv[i];
      } else {
      //grw - pass rest of modules to linker

      }
			if (Errors && !O_testonly)
				cmderror("compilation stopped", NULL);
			if (!O_asmonly && !O_testonly)
				assemble(argv[i], Fpath);
			i++;
		}
    //grw - support 'asm' for extension (used by Asm/02)
		else if (filetype(argv[i]) == 's' || strstr(argv[i], ".asm")) {
			//grw - set name for linker
      if (fname == NULL) {
        fname = argv[i];
      } else {
        //grw - add name to module list for linker
        collect(newfilename(argv[i], "prg"), 1);
      }

			if (!O_testonly) assemble(argv[i++], Fpath);
		}
		else {
			if (!exists(argv[i])) cmderror("no such file: %s",
							argv[i]);
			collect(argv[i++], 0);
		}
	}
	//grw - pass name to linker
	//if (!O_componly && !O_testonly) link();
	if (!O_componly && !O_testonly && !O_library) link(fname, Fpath);
	return EXIT_SUCCESS;
}
