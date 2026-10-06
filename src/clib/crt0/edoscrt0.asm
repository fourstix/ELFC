;---------------------------------------------------------
;    NMH's Simple C Compiler, 2012--2014
;    C runtime module for ELF-DOS
;---------------------------------------------------------
;
; An ELF-DOS program is loaded at PROG_BASE and starts with a six byte
; header, so this module is laid out as:
;
;   PROG_BASE         header, 'E','D','F' and the program version
;   PROG_BASE + 6     start up, exit and error code, in the rest of the page
;   PROG_BASE + $100  subroutine table, which must fill one page
;   PROG_BASE + $200  stacks and arguments for main
;
; The rest of the program follows this module, and the memory after
; the program up to the top of memory is the heap, so no memory is
; left unused.
;
; A GOSUB holds only the low byte of an address in the subroutine
; table, so compiled code does not depend on the page the table is on.
; Only RSUB does, which is why the routines in the table are built for
; ELF-DOS as edosc.lib (see RSUB in ../include/ops_c.inc). If PROG_BASE
; ever moves, RSUB must be changed to match and edosc.lib rebuilt.
;---------------------------------------------------------

#include ../include/ops_c.inc
#include ../elfdos-sdk/include/kernel_api.inc

          public es_min
          public auto_err
          public stk_err
          public Elfexit

          ;----- elfc subroutines
          extrn   epush16
          extrn   epush8
          extrn   dpop16
          extrn   add16
          extrn   and16
          extrn   div16
          extrn   eq16
          extrn   false16
          extrn   gt16
          extrn   gte16
          extrn   lt16
          extrn   lte16
          extrn   mdsgn16
          extrn   mod16
          extrn   mul16
          extrn   ne16
          extrn   neg16
          extrn   or16
          extrn   sub16
          extrn   true16
          extrn   xor16
          extrn   not16
          extrn   bool16
          extrn   inv16
          extrn   shl16
          extrn   shr16
          extrn   vpush16
          extrn   vpop16
          extrn   vpush8
          extrn   dpush16
          extrn   esmove
          extrn   linit16
          extrn   lstor16
          extrn   lstor8
          extrn   vstor16
          extrn   vstor8
          extrn   swap16
          extrn   dget16
          extrn   lpush16
          extrn   lpush8
          extrn   deref16
          extrn   deref8
          extrn   laddr16
          extrn   pstor16
          extrn   pstor8
          extrn   scltos2n
          extrn   sclsos2n
          extrn   unscl2n
          extrn   vinc16
          extrn   vdec16
          extrn   vinc8
          extrn   vdec8
          extrn   linc16
          extrn   ldec16
          extrn   linc8
          extrn   ldec8
          extrn   lpinc16
          extrn   lpdec16
          extrn   vpinc16
          extrn   vpdec16
          extrn   psave
          extrn   pinc16
          extrn   pdec16
          extrn   pinc8
          extrn   pdec8
          extrn   pincptr
          extrn   pdecptr
          extrn   stkchk
          extrn   ugt16
          extrn   uge16
          extrn   ult16
          extrn   ule16
          extrn   lget16
          extrn   lset16
          extrn   mcopy
          extrn   derefm
          extrn   fp2args
          extrn   dpop32
          extrn   fp1arg

          ;----- C routines
          extrn  Cmain
          extrn  C_init

            org    PROG_BASE

          db     'E','D','F'  ; ELF-DOS executable signature
          db     1,0,0        ; program version number and reserved byte

;------ ELF-DOS starts the program here with RA = argv and RC = argc.
;------ These are only good until the first kernel call, and argv is a
;------ table of pointers with the high byte first, so copy the pointers
;------ into the table for main with the low byte first.
Elfstart: push   r6           ; save original return address on stack
          glo    rc           ; get the argument count
          smi    ARGV_MAX_ARGS+1
          lbnf   argcok       ; the kernel passes no more than this
          ldi    ARGV_MAX_ARGS
          plo    rc
argcok:   load   rf, m_argc   ; save the argument count for main
          glo    rc
          str    rf
          load   rf, m_argv   ; argv table pointer
          glo    rc           ; ELF-DOS always passes the program name
          lbz    argdone      ; but make sure there is something to copy
argloop:  lda    ra           ; get MSB of pointer to argument
          plo    re           ; set aside
          lda    ra           ; get LSB of pointer to argument
          str    rf           ; store LSB first
          inc    rf
          glo    re           ; then store MSB
          str    rf
          inc    rf
          dec    rc           ; count down arguments
          glo    rc
          lbnz   argloop      ; keep going until all are copied

argdone:  load   rf, ostack   ; save original SP
          ghi    r2
          str    rf
          inc    rf
          glo    r2
          str    rf
          load   r2, cstack   ; set SP to C Program Stack
          load   r7, estack   ; set ESP (Expression Stack Pointer)
          copy   r7, rb       ; set Stack Frame BP (Base Pointer)
          load   r9, dispatch ; set up subroutine vector

;------ Need to call the _init function in stdlib ---------
          call   C_init
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
          sex    r2           ; set X = SP for call to main
          call   Cmain        ; call the main procedure

;----- set up registers for return to ELF-DOS, which takes the byte
;----- in D as the exit code of the program
Elfexit:  load   rf, ostack   ; get original SP
          lda    rf
          phi    r2
          ldn    rf
          plo    r2
          sex    2            ; make sure X = SP for return
          pop    r6           ; restore original return
          glo    ra           ; get byte value for return
          rtn                 ; return to ELF-DOS

;----- error handling for when expression stack exhausted
auto_err: call K_INMSG        ; print error msg
            db 'Out of Stack Space for Auto Variables',10,13,0
          load   ra, -1       ; set error value for return
          lbr    Elfexit      ; exit to ELF-DOS

;----- error handling for when expression stack exhausted
stk_err:  call K_INMSG        ; print error msg
            db 'Stack Creep Error',10,13,0
          load   ra, -1       ; set error value for return
          lbr    Elfexit      ; exit to ELF-DOS

;----- the code above has to end before the subroutine table
          org    PROG_BASE+$100 ; align subroutine table to page boundary
.norelax
s_return: sep    r3           ; return from subroutine
dispatch: lda    r3           ; jump in page to inline byte address
          plo    r9
          ;----- subroutine vectors
s_esmove:   lbr esmove
s_stkchk:   lbr stkchk
s_dpop16:   lbr dpop16
s_dpush16:  lbr dpush16
s_dget16:   lbr dget16
s_epush16:  lbr epush16
s_vpop16:   lbr vpop16
s_vpush8:   lbr vpush8
s_vpush16:  lbr vpush16
s_vstor8:   lbr vstor8
s_vstor16:  lbr vstor16
s_vinc8:    lbr vinc8
s_vinc16:   lbr vinc16
s_vdec8:    lbr vdec8
s_vdec16:   lbr vdec16
s_vpinc16:  lbr vpinc16
s_vpdec16:  lbr vpdec16
s_linit16:  lbr linit16
s_lstor8:   lbr lstor8
s_lstor16:  lbr lstor16
s_lpush8:   lbr lpush8
s_lpush16:  lbr lpush16
s_lget16:   lbr lget16
s_lset16:   lbr lset16
s_linc8:    lbr linc8
s_linc16:   lbr linc16
s_ldec8:    lbr ldec8
s_ldec16:   lbr ldec16
s_lpinc16:  lbr lpinc16
s_lpdec16:  lbr lpdec16
s_psave:    lbr psave
s_pstor8:   lbr pstor8
s_pstor16:  lbr pstor16
s_pinc8:    lbr pinc8
s_pinc16:   lbr pinc16
s_pdec8:    lbr pdec8
s_pdec16:   lbr pdec16
s_pincptr:  lbr pincptr
s_pdecptr:  lbr pdecptr
s_laddr16:  lbr laddr16
s_deref8:   lbr deref8
s_deref16:  lbr deref16
s_swap16:   lbr swap16
s_add16:    lbr add16
s_sub16:    lbr sub16
s_neg16:    lbr neg16
s_mdsgn16:  lbr mdsgn16
s_mul16:    lbr mul16
s_div16:    lbr div16
s_mod16:    lbr mod16
s_bool16:   lbr bool16
s_true16:   lbr true16
s_false16:  lbr false16
s_and16:    lbr and16
s_or16:     lbr or16
s_xor16:    lbr xor16
s_not16:    lbr not16
s_inv16:    lbr inv16
s_shl16:    lbr shl16
s_shr16:    lbr shr16
s_eq16:     lbr eq16
s_gt16:     lbr gt16
s_gte16:    lbr gte16
s_lt16:     lbr lt16
s_lte16:    lbr lte16
s_ne16:     lbr ne16
s_ugt16:    lbr ugt16
s_uge16:    lbr uge16
s_ult16:    lbr ult16
s_ule16:    lbr ule16
s_scltos2n: lbr scltos2n
s_sclsos2n: lbr sclsos2n
s_unscl2n:  lbr unscl2n
s_mcopy:    lbr mcopy
s_epush8:   lbr epush8
s_derefm:   lbr derefm
s_fp2args:  lbr fp2args
s_dpop32:   lbr dpop32
s_fp1arg:   lbr fp1arg

.relax

; --------------------- Variables and Stack--------------------------
ostack:   dw     0            ; original SP
;------------------------ C Program Stack ---------------------------
cstk:     ds     127
cstack:   db     0            ; progam stack
;----------------------- Expression Stack ---------------------------
estk:     ds     32           ; minimum stack for arithmetic operations
es_min:   ds     223          ; auto variables and arithmetic operations
estack:   db     0            ; Top of expression stack
;----------------------- Arguments for Main ---------------------------
m_argc:   db   0              ; argument count
m_argv:   ds   ARGV_MAX_ARGS*2 ; pointers to arguments, argv[]
