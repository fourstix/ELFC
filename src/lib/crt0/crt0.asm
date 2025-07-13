;---------------------------------------------------------
;	NMH's Simple C Compiler, 2012--2014
;	C runtime module for Elf/OS
;---------------------------------------------------------

#include ../include/ops_c.inc
#include ../include/bios.inc
#include ../include/kernel.inc

#define  KEYBUF  $0080

          public es_min
          public auto_err
          public Elfexit
          ;----- debugging expose arg variables
          public m_argv
          public m_argc
          public estack
          
          extrn  Cmain
          extrn  C_init

            org    2000h

ElfCpgm:  br     Elfstart
          ever
  					db 'ElfC',0
Elfstart: push   r6            ; save original return address on stack
          load   rf, ostack    ; save original SP
          ghi    r2
          str    rf
          inc    rf
          glo    r2
          str    rf
          load   r2, cstack   ; set SP to C Program Stack
          load   r7, estack   ; set ESP (Expression Stack Pointer)
          copy   r7, rb       ; set Stack Frame BP (Base Pointer)
          load   r1, $F000    ; DEBUG set R1 for breakpoint
;------ Need to call the _init function in stdlib ---------
          call   C_init
;------ load arguments for main function onto ES ---------
          call   argvload     ; initialize arg pointer array *argv[]
;-----  before calling main, push argc and **argv onto stack
          load   rd, m_argc
          load   rf, m_argv
          sex    r7           ; set X = ES to push arguments to main
          ghi    rf           ; push address of argv[] as second argument
          stxd                ; push MSB of argv[] onto expression stack
          glo    rf           ; push LSB of argv[] onto expression stack
          stxd  
          ldi    0            ; argc is an int, so pad bye with 0
          stxd                ; push MSB or int argc
          ldn    rd           ; push arg count as LSB of first argument
          stxd 
          sex   r2            ; set X = SP for call to main
          call  Cmain				  ; call the main procedure
          clc                 ; clear DF for return to Elf/OS

;----- set up registers for return to Elf/OS
Elfexit:  load   rf, ostack   ; get original SP
          lda    rf
          phi    r2
          ldn    rf
          plo    r2
          sex    2            ; make sure X = SP for return
          pop    r6           ; restore original return
          glo    ra						; get byte value for return
          return              ; return to Elf/OS

;----- error handling for when expression stack exhausted
auto_err: call o_inmsg        ; print error msg
            db 'Out of Stack Space for Auto Variables',10,13,0
          load   ra, -1       ; set error value for return
          stc                 ; set DF for error return
          lbr Elfexit         ; exit to Elf/OS
          
argvload: load  rd, m_argc    ; load argc pointer
          load  rf, m_argv    ; load argv pointer 
          load  rc, $00       ; set counter 
          load  r8, KEYBUF    ; set pointer to key buffer
sk_sp:    lda   r8            ; get byte from cmd string
          lbz   argvdone      ; end of arg string
          smi   ' '           ; check for space
          lbz   sk_sp         ; skip over leading spaces
          
          dec   r8            ; move back to first char in argument
          glo  r8             ; put argument address in arg slot
          str   rf            ; C variables are stored LSB first, then MSB
          inc   rf
          ghi   r8            ; C variables are LSB first, then MSB
          str   rf 
          inc   rf
          inc   rc            ; increment arg counter
sk_ns:    lda   r8            ; skip over non-spaces
          lbz   argvdone      ; if we hit zero, we're done
          smi   ' '
          lbnz  sk_ns
          dec   r8            ; back up to first space
          ldi   0
          str   r8            ; put zero after arg
          inc   r8            ; move back to next char
          glo   rc            
          smi   8             ; up to 8 args
          lbnz  sk_sp         ; if not at max, keep going
                     
argvdone: glo   rc            ; get argument count
          str   rd            ; save arg count in variable      
          return 
          
; --------------------- Variables and Stack--------------------------
ostack: dw 0          	; original SP
;------------------------ C Program Stack ---------------------------
cstk:   ds 127
cstack: db 0          	; progam stack
;----------------------- Expression Stack ---------------------------
estk:   ds 32           ; minimum stack for arithmetic operations
es_min: ds 223					; auto variables and arithmetic operations
estack: db 0            ; Top of expression stack
;----------------------- Arguments for Main ---------------------------
m_argc:   db   0        ; arguement count
          ;----- argv[] room for pointers up to 8 arguments
m_argv:   db   0, 0, 0, 0, 0, 0, 0, 0
          db   0, 0, 0, 0, 0, 0, 0, 0
; --------------------- End Variables and Stack ---------------------
             end  ElfCpgm
