/*
 *	NMH's Simple C Compiler, 2013,2014
 *	FreeBSD/x86-64 environment
 */

#define OS		  "Elf/OS"
#define ASCMD	  "%sasm02 -I %s -L -C %s"
#define LDCMD	  "%slink02 -e -S -L %slib -I %slib crt0.prg %s"
#define SYSLIBC	" -l elfc.lib -l stdlib.lib -l stdio.lib"
#define ELFLIBC	" -l elfc.lib"
