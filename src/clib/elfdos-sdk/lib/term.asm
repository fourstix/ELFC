;
; term.asm - the console terminal's size, for programs that lay out
; their output to fit the screen (LS, LESS, HEXDUMP, EDLIN).
;
; NOT a standalone program -- linked alongside one, like every other
; lib/*.asm module. Needs lib/env.asm (and therefore lib/drives.asm).
;
; term_size answers each dimension from the first of these that knows it:
;   1. the kernel's copy (TERM_ROWS/TERM_COLS in kernel_api.inc), set by
;      TERMSIZE -- free to read;
;   2. the ROWS/COLUMNS environment variables -- one file lookup each,
;      and only when the kernel's copy is 0;
;   3. 24 rows by 80 columns.
; The two dimensions are decided independently. A variable that is set
; but is not a number, or is 0, counts as not set.
;
; The line editor (lib/lineedit.asm) does NOT use this: it runs at every
; prompt and must not open a file there, so it reads TERM_COLS alone and
; assumes 80 when that is 0.
;

#include    include/opcodes.def
#include    include/kernel_api.inc

TERM_DEF_ROWS:  equ     24
TERM_DEF_COLS:  equ     80

            extrn   env_getenv
            extrn   env_parse_uint
            extrn   tsz_rows
            extrn   tsz_cols
            extrn   tsz_def
            extrn   tsz_rows_name
            extrn   tsz_cols_name

;------------------------------------------------------------------
; term_size: the terminal's size -- see the header.
; Args:    none
; Returns: RC.1 = rows, RC.0 = columns, each 1..255 (values over 255
;          are reported as 255)
; Modifies: everything (env_getenv's own footprint)
;------------------------------------------------------------------
            proc    term_size

            mov     rf, TERM_ROWS
            ldn     rf
            plo     r9
            mov     rf, tsz_rows
            glo     r9
            str     rf                  ; kernel's rows, maybe 0
            lbnz    tsz_do_cols

            mov     rf, tsz_rows_name
            ldi     TERM_DEF_ROWS
            call    tsz_env
            plo     r9
            mov     rf, tsz_rows
            glo     r9
            str     rf

tsz_do_cols:
            mov     rf, TERM_COLS
            ldn     rf
            plo     r9
            mov     rf, tsz_cols
            glo     r9
            str     rf                  ; kernel's columns, maybe 0
            lbnz    tsz_done

            mov     rf, tsz_cols_name
            ldi     TERM_DEF_COLS
            call    tsz_env
            plo     r9
            mov     rf, tsz_cols
            glo     r9
            str     rf

tsz_done:
            mov     rf, tsz_rows
            ldn     rf
            phi     rc
            mov     rf, tsz_cols
            ldn     rf
            plo     rc
            rtn

;------------------------------------------------------------------
; tsz_env: one environment variable as a byte.
; Args:    RF = variable name, D = default
; Returns: D = its value (1..255, over 255 -> 255), or the default if
;          it is not set, not a number, or 0
;------------------------------------------------------------------
tsz_env:
            plo     r9                  ; mov below clobbers D
            mov     rb, tsz_def
            glo     r9
            str     rb

            call    env_getenv          ; RF = value, or 0 if not set
            ghi     rf
            lbnz    tse_have
            glo     rf
            lbz     tse_default
tse_have:
            call    env_parse_uint      ; RD = value (0 if no digits)
            ghi     rd
            lbnz    tse_big
            glo     rd
            lbz     tse_default
            rtn
tse_big:
            ldi     255
            rtn
tse_default:
            mov     rf, tsz_def
            ldn     rf
            rtn

            endp

            proc    _term_data

tsz_rows:       db      0
tsz_cols:       db      0
tsz_def:        db      0
tsz_rows_name:  db      "ROWS",0
tsz_cols_name:  db      "COLUMNS",0

                public  tsz_rows
                public  tsz_cols
                public  tsz_def
                public  tsz_rows_name
                public  tsz_cols_name

            endp
