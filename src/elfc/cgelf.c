/*
 *	NMH's Simple C Compiler, 2011,2012,2022
 *	Elf/OS target description
 */

#include "defs.h"
#include "data.h"
#include "decl.h"
#include "cgen.h"

//grw
void cgdata(void)	{gen(";----- cgdata");}
void cgtext(void)	{gen(";----- cgtext"); }

void cgprelude()	{
	genraw("; -------------------------------------------------------------------\n");
	genraw("; This file generated by ElfC, based on SubC\n");
	genraw("; SubC Copyright 2012-2025 by Nils Holm\n");	
	genraw("; -------------------------------------------------------------------\n");
	genraw("#include include/ops_c.inc\n");
	genraw("#include include/bios.inc\n");
	genraw("#include include/kernel.inc\n");
	genraw("#include include/elfc.inc\n\n");
	
	genraw("          public es_min\n\n");	
	
	genraw("            org    2000h\n\n");
	
	genraw("ElfCpgm:  br     Elfstart\n");
	genraw("          ever\n");
	genraw("  					db 'ElfC',0\n");
	genraw("Elfstart: push   r6            ; save original return address on stack\n");
	genraw("          load   rf, ostack    ; save original SP\n");
	genraw("          ghi    r2\n");
	genraw("          str    rf\n");
	genraw("          inc    rf\n");
	genraw("          glo    r2\n");
	genraw("          str    rf\n");
	genraw("          load   r2, cstack   ; set SP to C Program Stack\n");
	genraw("          load   r7, estack   ; set ESP (Expression Stack Pointer)\n");
	genraw("          copy   r7, rb       ; set Stack Frame BP (Base Pointer)\n");
	genraw("          load   r1, $F000    ; DEBUG set R1 for breakpoint\n");
	
	genraw(";----- TODO: set up main arguments and options\n");
	genraw("          call  Cmain				  ; call the main procedure\n");
	genraw("          clc                 ; clear DF for return to Elf/OS\n\n");
	genraw(";----- set up registers for return to Elf/OS\n");
	genraw("Elfexit:  load   rf, ostack   ; get original SP\n");
  genraw("          lda    rf\n");
  genraw("          phi    r2\n");
  genraw("          ldn    rf\n");
  genraw("          plo    r2\n");
  genraw("          sex    2            ; make sure X = SP for return\n");
  genraw("          pop    r6           ; restore original return\n");  
	genraw("          glo    ra						; get byte value for return\n");
  genraw("          return              ; return to Elf/OS\n");
	genraw("\n;----- error handling for when expression stack exhausted\n");
	genraw("auto_err: call o_inmsg        ; print error msg\n");
	genraw("            db 'Out of Stack Space for Auto Variables',10,13,0\n");
	genraw("          load   ra, -1       ; set error value for return\n");
	genraw("          stc                 ; set DF for error return\n");
	genraw("          lbr Elfexit         ; exit to Elf/OS\n");
	
	genraw(";--------------------- End Prelude ----------------------------------\n");
}

void cgpostlude(void)	{
  genraw("; --------------------- Begin Postlude ------------------------------\n");
  genraw("ostack: dw 0          	; original SP\n");
	genraw(";------------------------ C Program Stack ---------------------------\n");
	genraw("cstk:   ds 127\n");
	genraw("cstack: db 0          	; progam stack\n");
	genraw(";----------------------- Expression Stack ---------------------------\n");
	genraw("estk:   ds 32           ; minimum stack for arithmetic operations\n");
	genraw("es_min: ds 223					; auto variables and arithmetic operations\n");
	genraw("estack: db 0            ; Top of expression stack\n");
	genraw(";----------- TODO: load arguments for main function onto ES ---------\n");
	//genraw("m__argc:  dw   2					; main arg count (always 2)\n");
	//genraw(";----- argc count of arguments including command name\n"); 
	//genraw("m_argc:   dw   1 					; argc value\n");
	//genraw(";----- argv[] array of char pointers\n");								
	//genraw("m_argvp:  dw m_cmd				; arg[0] is command\n");  
	//genraw("m_ops: 	  ds   30					; array of char pointers for option strings\n"); 
	genraw("m_cmd:    ds   20         ; command name that invoked program\n");
	genraw("          db   0          ; guard byte for end of string\n");
	genraw("; --------------------- End Postlude --------------------------------\n");
	genraw("             end  ElfCpgm\n\n");
}

void cgpublic(char *s)	{gen(";----- cgpublic"); }
void cglit(int v)	{ 	
	gen(";----- cglit");
	gen(" 				call epush16");
	ngen(" 				  %s %d", "dw", v); }
void cgclear(void)	{gen(";----- cgclear"); }
void cgldgb(char *s)	{gen(";----- cgldgb"); 
	gen(" 				call vpush8");
	sgen(" 				  %s %s", "dw", s); }
void cgldgw(char *s)	{gen(";----- cgldgw"); 
	gen(" 				call vpush16");
	sgen(" 				  %s %s", "dw", s); }
void cgldlb(int n)	{ gen(";----- cgldlb"); 
	gen("          call  lpush8        ; push value of local variable on ES");
	ngen("          %s  %d  ;--- offset", "dw", n); }
void cgldlw(int n)	{ gen(";----- cgldlw"); 
	gen("          call  lpush16       ; push value of local variable on ES"); 
	ngen("          %s  %d  ;--- offset", "dw", n); }
void cgldsb(int n)	{gen(";----- cgldsb"); 
	gen(" 				call vpush8");
	lgen(" 				  %s %c%d", "dw", n); }
void cgldsw(int n)	{gen(";----- cgldsw"); 	
	gen(" 				call vpush16");
	lgen(" 				  %s %c%d", "dw", n); }
void cgldla(int n)	{gen(";----- cgldla"); 
	gen("          call  laddr16       ; push address of local variable on ES"); 
	ngen("          %s  %d  ;--- offset", "dw", n); }
void cgldsa(int n)	{gen(";----- cgldsa"); 
	gen(" 				call epush16");
	lgen(" 				   %s %c%d", "dw", n); }
void cgldga(char *s)	{gen(";----- cgldga"); 
	gen(" 				call epush16");
	sgen(" 				  %s %s", "dw", s); }
void cgindb(void)	{gen(";----- cgindb");
	gen(" 				call deref8"); }
void cgindw(void)	{gen(";----- cgindw");
	gen(" 				call deref16"); }

void cgargc(void)	{gen(";----- cgargc"); gen("movl\t8(%ebp),%eax"); }

void cgldlab(int id)	{gen(";----- cgldlab"); 
	gen(" 				call epush16");
  lgen(" 				  %s  %c%d", "dw", id); }

void cgpush(void)	{gen(";----- cgpush"); }

void cgpushlit(int n)	{gen(";----- cgpushlit");
		gen(" 				call epush16");
		ngen(" 				  %s %d", "dw", n); }

void cgpop2(void)	{gen(";----- cgpop2"); }
void cgswap(void)	{gen(";----- cgswap");
		gen("          call  swap16				 ; swap TOS and SOS on Expression Stack\n"); }
void cgand(void)	{gen(";----- cgand"); 
		gen("          call  and16				 ; bitwise and TOS and SOS on Expression Stack\n"); }
void cgxor(void)	{gen(";----- cgxor"); 
		gen("          call  xor16				 ; bitwise xor TOS and SOS on Expression Stack\n"); }
void cgior(void)	{gen(";----- cgior"); 
    gen("          call  or16	  			 ; bitwise or TOS and SOS on Expression Stack\n"); }
void cgadd(void)	{gen(";----- cgadd"); 
		gen("          call  add16				 ; add TOS and SOS on Expression Stack\n"); }
void cgmul(void)	{gen(";----- cgmul"); 
		gen("          call  mul16				 ; multiply SOS by TOS on Expression Stack\n"); }
void cgsub(void)	{gen(";----- cgsub"); 
    gen("          call  sub16				 ; subtract TOS from SOS on Expression Stack\n"); }
void cgdiv(void)	{gen(";----- cgdiv"); 
		gen("          call  div16				 ; divide SOS by TOS on Expression Stack\n"); }
void cgmod(void)	{gen(";----- cgmod");
		gen("          call  mod16				 ; SOS modulo TOS on Expression Stack\n"); }
void cgshl(void)	{gen(";----- cgshl"); 
		gen("          call  shl16				 ; SOS shifted left by TOS on Expression Stack\n"); }
void cgshr(void)	{gen(";----- cgshr"); 
		gen("          call  shr16				 ; SOS shifted right by TOS on Expression Stack\n"); }
void cgcmp(char *inst)	{ gen(";----- cgcmp"); }
void cgeq()		{gen(";----- cgeq"); 
		gen("          call  eq16				   ; compare SOS == TOS on Expression Stack\n"); }
void cgne()		{gen(";----- cgne"); 
		gen("          call  ne16				   ; compare SOS != TOS on Expression Stack\n"); }
void cglt()		{gen(";----- cglt");
		gen("          call  lt16				   ; compare SOS < TOS on Expression Stack\n"); }
void cggt()		{gen(";----- cggt"); 
		gen("          call  gt16				   ; compare SOS > TOS on Expression Stack\n"); }
void cgle()		{gen(";----- cgle"); 
		gen("          call  lte16				 ; compare SOS <= TOS on Expression Stack\n"); }
void cgge()		{gen(";----- cgge"); 
		gen("          call  gte16				 ; compare SOS >= TOS on Expression Stack\n"); }
void cgneg(void)	{gen(";----- cgneg"); 
		gen("          call  neg16				 ; negate TOS on Expression Stack\n"); }
void cgnot(void)	{gen(";----- cgnot"); 
		gen("          call  inv16				 ; bitwise invert TOS on Expression Stack\n"); }
void cglognot(void)	{gen(";----- cglognot"); 
		gen("          call  not16				 ; logical not TOS on Expression Stack\n"); }

void cgscale(void)	{gen(";----- cgscale"); 
	gen(" 				call scltos16");}
void cgscale2(void)	{gen(";----- cgscale2");
	gen(" 				call sclsos16");}
void cgunscale(void)	{gen(";----- cgunscale");
	gen(" 				  call unscl16");}
void cgbool(void)	{gen(";----- cgbool");
	gen(" 				  call bool16");}

void cgldinc(void)	{gen(";----- cgldinc");
	gen(" 				 call  psave        ; save pointer to pointer from stack for postfix"); }

void cginc1pi(void)	{gen(";----- cginc1pi");  	
	gen(" 				 call  psave        ; get pointer to pointer from stack for prefix");
	gen(" 				 call  pincptr      ; increment pointer referenced by pointer"); }

void cgdec1pi(void)	{gen(";----- cgdec1pi"); 
	gen(" 				 call  psave        ; get pointer to pointer from stack for prefix");
	gen(" 				 call  pdecptr      ; decrement pointer referenced by pointer"); }

void cginc2pi(void)	{gen(";----- cginc2pi"); 
	gen(" 				 call  pincptr      ; increment pointer referenced by saved pointer"); }
	
void cgdec2pi(void)	{gen(";----- cgdec2pi"); 
	gen(" 				 call  pdecptr      ; decrement pointer referenced by saved pointer"); }

void cgincpl(int a)	{gen(";----- cgincpl"); 
	gen("          call  lpinc16      ; increment local pointer to 2-byte value"); 
	ngen("          %s  %d  ;--- offset", "dw", a); }

void cgdecpl(int a)	{gen(";----- cgdecpl"); 
	gen("          call  lpdec16      ; decrement local pointer to 2-byte value"); 
	ngen("          %s  %d  ;--- offset", "dw", a); }

void cgincps(int a)	{gen(";----- cgincps"); 
	gen(" 				 call vpinc16       ; increment static pointer to 2-byte value");
	lgen(" 				  %s %c%d", "dw", a); }
void cgdecps(int a)	{gen(";----- cgdecps"); 
	gen(" 				 call vpdec16       ; decrement static pointer to 2-byte value");
	lgen(" 				  %s %c%d", "dw", a); }
void cgincpg(char *s)	{gen(";----- cgincpg"); 
	gen(" 				 call vpinc16       ; increment global pointer to 2-byte value");
	sgen(" 				  %s %s", "dw", s); }
void cgdecpg(char *s)	{gen(";----- cgdecpg");
	gen(" 				 call vpdec16       ; decrement global pointer to 2-byte value");
	sgen(" 				  %s %s", "dw", s); }
	
void cginc1iw(void)	{gen(";----- cginc1iw");
	gen(" 				 call  psave        ; save pointer from stack");
	gen("          call  pinc16       ; increment variable referenced by saved pointer"); }

void cgdec1iw(void)	{gen(";----- cgdec1iw");
	gen(" 				 call  psave        ; save pointer from stack");
	gen("          call  pdec16       ; decrement variable referenced by saved pointer"); }

void cginc2iw(void)	{gen(";----- cginc2iw");  
	gen("          call  pinc16       ; increment variable referenced by saved pointer"); }
void cgdec2iw(void)	{gen(";----- cgdec2iw"); 
	gen("          call  pdec16       ; decrement variable referenced by saved pointer"); }

void cginclw(int a)	{gen(";----- cginclw"); 
	gen("          call  linc16       ; increment local variable"); 
	ngen("          %s  %d  ;--- offset", "dw", a); }

void cgdeclw(int a)	{gen(";----- cgdeclw"); 
	gen("          call  ldec16       ; decrement local variable"); 
	ngen("          %s  %d  ;--- offset", "dw", a); }

void cgincsw(int a)	{gen(";----- cgincsw"); 
	gen(" 				 call vinc16       ; increment static variable");
	lgen(" 				  %s %c%d", "dw", a); }
void cgdecsw(int a)	{gen(";----- cgdecsw"); 
	gen(" 				 call vdec16       ; increment static variable");
	lgen(" 				  %s %c%d", "dw", a); }

void cgincgw(char *s)	{gen(";----- cgincgw"); 
	gen(" 				 call vinc16       ; increment global variable");
	sgen(" 				  %s %s", "dw", s); }
void cgdecgw(char *s)	{gen(";----- cgdecgw"); 
	gen(" 				 call vdec16       ; decrement global variable");
	sgen(" 				  %s %s", "dw", s); }

void cginc1ib(void)	{gen(";----- cginc1ib");
	gen(" 				 call  psave        ; save pointer from stack");
	gen("          call  pinc8        ; increment variable referenced by saved pointer"); }
void cgdec1ib(void)	{gen(";----- cgdec1ib");
	gen(" 				 call  psave        ; save pointer from stack");
	gen("          call  pdec8        ; decrement variable referenced by saved pointer"); }
	
void cginc2ib(void)	{gen(";----- cginc2ib");
	gen("          call  pinc8        ; increment variable referenced by saved pointer"); }
void cgdec2ib(void)	{gen(";----- cgdec2ib"); 
	gen("          call  pdec8        ; decrement variable referenced by saved pointer"); }

void cginclb(int a)	{gen(";----- cginclb"); 
	gen("          call  linc8        ; increment local variable"); 
	ngen("          %s  %d  ;--- offset", "dw", a); }
void cgdeclb(int a)	{gen(";----- cgdeclb"); 
	gen("          call  linc8        ; decrement local variable"); 
	ngen("          %s  %d  ;--- offset", "dw", a); }
void cgincsb(int a)	{gen(";----- cgincsb"); 
	gen(" 				 call  vinc8        ; increment static variable");
	lgen(" 				  %s %c%d", "dw", a); }
void cgdecsb(int a)	{gen(";----- cgdecsb"); 
	gen(" 				 call  vdec8        ; decrement static variable");
	lgen(" 				  %s %c%d", "dw", a); }
void cgincgb(char *s)	{gen(";----- cgincgb"); 
	gen(" 				 call  vinc8        ; increment global variable");
	sgen(" 				  %s %s", "dw", s); }
void cgdecgb(char *s)	{gen(";----- cgdecgb"); 
	gen(" 				 call  vdec8        ; decrement global variable");
	sgen(" 				  %s %s", "dw", s); }

void cgbr(char *how, int n)
			{gen(";----- cgbr");
			 gen(" 				 call  dpop16        ; get result from expression stack");
			 gen(" 				 ghi   ra            ; get MSB from result");
			 gen(" 				 str   r2            ; save in M(X)");
			 gen(" 				 glo   ra            ; get LSB from result");
			 gen(" 				 or                  ; D = MSB | LSB");			  
			lgen(" 				  %s\t%c%d", how, n); }
void cgbrtrue(int n)	{gen(";----- cgbrtrue"); cgbr("lbnz", n); }
void cgbrfalse(int n)	{gen(";----- cgbrfalse"); cgbr("lbz", n); }
void cgjump(int n)	{gen(";----- cgjump"); lgen(" 				  %s\t%c%d", "lbr", n); }

void cgldswtch(int n)	{gen(";----- cgldswtch"); }
void cgcalswtch(void)	{gen(";----- cgcalswtch"); 
			gen("          call  dpop16   		 ; get switch value from expression stack"); }
void cgcase(int v, int l)
			{gen(";----- cgcase");
			ngen("%s  ra, $%04x  ;----- look for match with case value", "match", v); 
			lgen("%s  %c%d", "lbz", l); }

void cgpopptr(void)	{gen(";----- cgpopptr"); 
	gen("          call  swap16				 ; swap TOS and SOS on Expression Stack"); 
	gen("          call  dpop16   		 ; get pointer from expression stack"); }
void cgstorib(void)	{gen(";----- cgstorib"); 
	gen("          call  pstor16       ; store value from ES in pointer variable"); }
void cgstoriw(void)	{gen(";----- cgstoriw"); 
	gen("          call  pstor16       ; store value from ES in pointer variable"); }
void cgstorlb(int n)	{gen(";----- cgstorlb"); 
	gen("          call  lstor8       ; store value from ES in local variable"); 
	ngen("          %s  %d  ;--- offset", "dw", n); }
void cgstorlw(int n)	{gen(";----- cgstorlw"); 
	gen("          call  lstor16      ; store value from ES in local variable"); 
	ngen("          %s  %d  ;--- offset", "dw", n); }
void cgstorsb(int n)	{gen(";----- cgstorsb"); 
	gen(" 				 call vstor8        ; store value from ES in static variable");
	lgen(" 				  %s %c%d", "dw", n); }
void cgstorsw(int n)	{gen(";----- cgstorsw");
	gen(" 				 call vstor16       ; store value from ES in static variable");
	lgen(" 				  %s %c%d", "dw", n); }
void cgstorgb(char *s)	{gen(";----- cgstorgb"); 
	gen(" 				 call vstor8        ; store value from ES in global variable");
	sgen(" 				  %s %s", "dw", s); }
void cgstorgw(char *s)	{gen(";----- cgstorgw");
	gen(" 				 call vstor16       ; store value from ES in global variable");
	sgen(" 				  %s %s", "dw", s); }

void cginitlw(int v, int a)	{gen(";----- cginitlw"); 
	gen("          call linit16         ; put value in local variable on ES"); 
	ngen("          %s  %d  ;--- offset", "dw", a);
	ngen("          %s  %d  ;--- init value", "dw", v); }

void cgcall(char *s)	{gen(";----- cgcall"); sgen("%s  %s", "call", s); }

void cgcalr(int n)	{gen(";----- cgcalr");
	gen("          call  dpop16  ; get function pointer from expression stack into ra");
 	lgen("          %s %c%d       ; r8 points to call address location", "load r8, ", n);
	gen("          ghi  ra   		 ; get address MSB from function pointer");
	gen("          str  r8   		 ; put function address MSB in call address");
	gen("          inc  r8   		 ; move call address pointer to LSB");
	gen("          glo  ra   		 ; get function address LSB from function pointer");
	gen("          str  r8   		 ; put function address LSB in call address");	
	sgenraw("%s  %s", "          sep", "r4    ; call function address loaded from function pointer");
	genlab(n);
	ngen("%s\t 0, 0  ;----- function address from fp", "db", 0);
 }

void cgstack(int n)	{gen(";----- cgstack");
	gen("          call  esmove				 ; move pointer for Expression Stack"); 
	ngen("          %s  %d  ;--- offset", "dw", n); 
	gen("          lbdf  auto_err			 ; exit immediately when stack is exhausted by auto variables"); }

void cgentry(void)	{
	gen(";---- cgentry");
	gen("          sex   r2   				 ; make sure X = SP");
	gen("          push  rb				 		 ; save current BP (base pointer)");
	gen("          copy  r7, rb			 	 ; set BP to current ES location"); }

void cgexit(void)	{
	gen(";----- cgexit");
	gen("          sex   r2            ; make sure X = SP");
	gen("          call  escheck       ; check for expression stack creep");
	gen("          pop   rb				 		 ; restore BP (base pointer)\n");
	gen("          rtn	  			 	     ; return to caller"); }

void cgdefb(int v)	{
	ngen("%s\t$%02x    ;----- cgdefb", "db", v); }

void cgdefw(int v)	{
	ngen2("%s\t$%02x, $%02x  ;----- cgdefw LSB first, MSB second", "db",	v&0x00FF, (v&0xFF00)>>8); }
void cgdefp(int v)	{
	ngen2("%s\t$%02x, $%02x  ;----- cgdefp LSB first, MSB second", "db",	v&0x00FF, (v&0xFF00)>>8); }

void cgdefl(int v)	{gen(";----- cgdefl"); lgen("%s\t%c%d", "lbr", v); }
void cgdefc(int c)	{
	if (c != '\'')
		ngen("%s\t'%c'  ;----- cgdefc", "db", c); 
	else 
		ngen("%s\t$%02x    ;----- cgdefc (quote char)", "db", c);
	}
void cgbss(char *s, int z)	{
	ngenraw("%s:    ds %d    ;----- cgbss\n", s, z); }

//grw - added cgpushd and cgpopd statements
void cgpushd() {gen(";----- cgpushd");
	gen("          call  dpush16   		 ; put result on expression stack"); }
void cgpopd() {
	gen("          call  dpop16   		 ; get result from expression stack"); }

//grw - added cgdefs to generate string in ASM/02 format
void cgdefs(char *s, int len) {
	int i;
	int in_str = 0;
	int start = 1;
	char c;

	genraw("  db ");
	for (i=1; i<len-1; i++) {
		c = s[i];
		if (isprint(c) && c != '\'') {
			if(!in_str) {
				in_str = 1;
				if (start) 
					start = 0;
				else 
				  genraw(", ");
				genraw("\'");
			} /* if !in_str */
			cgenraw("%c", c);
		} else {
			if (in_str) {
				genraw("\'");
				in_str = 0;
			}
			if (start) 
				start = 0;
			else 
				genraw(", ");
			cgenraw("%d", c);
		} /* if-else */
	} /* for */
	if (in_str) {
		genraw("\'");
	}
	genraw("    ;----- cgdefs\n");
}	
	
