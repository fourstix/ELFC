;
; lineedit.inc - mode constants for lib/lineedit.asm's read_line_ex,
; shared between the library and any consuming program (progs/edlin.asm
; being the first). An equ is a pure assemble-time constant, not a real
; linked symbol, so it's safe to #include from multiple files that get
; linked together (unlike a db/dw variable, which would collide) --
; matches how include/kernel_api.inc's own constants are shared.
;

LE_MODE_FAST:   equ     0       ; read_line_ex: f_uread directly, byte-
                                ; drop-safe for live typed escape
                                ; sequences, but can never see
                                ; redirected input -- always DF=0.
LE_MODE_REDIR:  equ     1       ; read_line_ex: K_READ (redirect-aware
                                ; via kernel/redir.asm's self-modified
                                ; jump-table slot -- see its own module
                                ; header), may return DF=1 at EOF, but
                                ; still subject to K_READ's own latency-
                                ; driven byte-drop risk on a fast live
                                ; arrow-key sequence.
LE_MODE_BITBANG: equ    2       ; read_line_ex: f_bread directly
                                ; (2026-08-05) -- the onboard bit-
                                ; banged serial port, same byte-drop-
                                ; safe direct-BIOS-call reasoning as
                                ; LE_MODE_FAST's own f_uread, just the
                                ; other UART. Always DF=0, same as
                                ; LE_MODE_FAST -- a live bit-banged
                                ; keyboard has no EOF concept either.
                                ; Matches progs/mr.asm's/lib/ymodem.
                                ; asm's own already-proven "-b" mode
                                ; convention exactly.

; Options, ORed into read_line_ex's D argument (2026-09-30).
LE_OPT_HIST:    equ     $80     ; Up/Down (and Ctrl-P/Ctrl-N) return
                                ; to the caller as LE_KEY_UP/LE_KEY_DOWN
                                ; instead of being discarded -- see
                                ; read_line_resume.

; read_line_ex/read_line_resume return codes in D when DF=0.
LE_KEY_ENTER:   equ     0       ; a finished line
LE_KEY_UP:      equ     1       ; Up pressed (LE_OPT_HIST only)
LE_KEY_DOWN:    equ     2       ; Down pressed (LE_OPT_HIST only)

; RC.1 value meaning "I don't know my prompt's length": wrapping is
; turned off and the editor behaves as it did before wrapping existed
; (lines longer than the terminal is wide redraw wrongly).
LE_COL_UNKNOWN: equ     $FF
