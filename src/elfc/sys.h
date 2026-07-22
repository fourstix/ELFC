/*
 *	NMH's Simple C Compiler, 2013,2014
 *	FreeBSD/x86-64 environment
 */

#define OS		  "Elf/OS"
#define ASCMD	  "%sasm02 %s-r -I %s -L -C %s"
#define LDCMD	  "%slink02 %s%s-e -S -L %slib -I %slib %s %s"
#define SYSLIBC	" -l elfc.lib -l stdlib.lib -l stdio.lib"
#define ELFLIBC	" -l elfc.lib -l elfstd.lib -l elfio.lib"
#define NOLIBC	" -l elfc.lib"
