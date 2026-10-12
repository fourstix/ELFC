/*
 *	NMH's Simple C Compiler, 2013,2014
 *	FreeBSD/x86-64 environment
 */

#define OS		  "Elf/OS"
#define ASCMD	  "%sasm02 %s-r -I %s -L -C %s"
//edos - output format is an argument, -e for Elf/OS or -b for ELF-DOS
#define LDCMD	  "%slink02 %s%s%s -S -L %slib -I %slib %s %s"
#define SYSLIBC	" -l elfc.lib -l stdlib.lib"
#define NOLIBC	" -l elfc.lib"
//edos - libraries for an ELF-DOS program (-E option)
#define EDOSLIBC	" -l edosc.lib -l edosstd.lib"
#define MINLIBC	" -l minio.lib"
#define IOLIBC	" -l stdio.lib"
