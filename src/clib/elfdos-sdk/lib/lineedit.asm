;
; lineedit.asm - K_INPUTL-style line editor with arrow-key/Emacs-style
; Ctrl-shortcut cursor editing (Left/Right/Home/End/Backspace/Del/
; Ctrl-B/F/A/E/D), lines longer than the terminal is wide (wrapping
; onto following rows), and optional Up/Down hand-back for a caller
; that keeps its own history (the shell). NOT a standalone program -- no EDF header, no org
; PROG_BASE, no entry point of its own. Assembled separately
; (lib/lineedit.prg) and linked alongside a program that wants it,
; the same way every other lib/*.asm module already does. A calling
; program declares "extrn read_line_ex" and calls it like any other
; routine.
;
; Extracted from progs/shell.asm's own read_line_with_history
; (2026-07-27), at the user's own request (EDLIN bug-report item 7,
; 2026-07-30: "I'd like to see us create that library function that
; programs can use as an alternative to K_INPUTL to give them line
; editing (no history) and use it when entering text in edlin").
;
; Deliberately scoped to cursor editing only -- HISTORY RECALL (Up/
; Down) IS NOT INCLUDED, by design, not as a deferred TODO. Up/Down
; arrow bytes are recognized (so a stray CSI sequence doesn't get
; mis-parsed as literal text) but silently discarded, exactly like
; the still-deferred Ctrl-K/U/W/Y cut/paste shortcuts. A caller that
; wants history needs its own mechanism layered on top (the shell's
; own hist_* machinery stays in progs/shell.asm, not moved here --
; it's tightly coupled to the shell's own history.dat file and
; wouldn't generalize cleanly).
;
; The single hardest design question extracting this out of the
; shell was the choice of underlying byte-read primitive, because the
; two callers this library actually has (the shell and EDLIN) have
; GENUINELY DIFFERENT needs here, not just a style preference:
;
;   - progs/shell.asm's own prompt read is NEVER itself redirected
;     (shell input redirection only ever applies to a CHILD program's
;     own I/O) -- so it was safe for read_line_with_history to always
;     call f_uread (the raw UART BIOS entry point) directly,
;     bypassing K_READ's own kernel-jump-table/RAM-vector redirect
;     indirection entirely. This was a real, hardware-confirmed fix
;     (2026-07-23): that indirection was slow enough, between this
;     routine's own per-byte branching, to drop the '[' byte of a
;     fast-arriving "ESC [ A"/"ESC [ B" arrow-key sequence -- the
;     exact bug progs/mr.asm/progs/ms.asm already hit and fixed the
;     same way (see their own header comments).
;
;   - EDLIN, by contrast, genuinely needs its OWN stdin to support
;     redirection ("edlin file < script.txt", an already-shipped,
;     hardware-confirmed feature depending on K_INPUTL's DF=0/1 EOF
;     contract -- see kernel/redir.asm's own header and the
;     K_INPUTL-EOF bug hunt in CLAUDE.md). f_uread can never see
;     redirected input at all (redirection is a kernel-jump-table-
;     level concept -- kernel/redir.asm's file-I/O read routine is
;     reached only via K_READ's own self-modified dispatch slot), so a
;     version that always used f_uread would
;     silently break "< file" batch editing for any caller that
;     switched to it.
;
; Resolved (confirmed with the user 2026-07-30) as a caller-selectable
; mode, matching this project's own established -u/-b precedent in
; progs/mr.asm/progs/ms.asm/lib/ymodem.asm (see read_line_ex's le_rdvec setup for
; the mode dispatch itself): LE_MODE_FAST uses f_uread throughout
; (byte-drop-safe, but can never signal EOF); LE_MODE_REDIR uses
; K_READ throughout (redirect-aware, DF=1 at EOF, but subject to the
; same K_READ-latency byte-drop risk on a live arrow-key sequence that
; motivated LE_MODE_FAST in the first place -- a live user might
; occasionally need to press an arrow key twice). Neither mode is
; strictly better; the caller picks based on whether ITS OWN stdin can
; ever be redirected.
;
; State (le_buf/le_max_len/le_mode/le_len/le_cursor and the various
; per-routine scratch fields below) is this library's own private,
; fixed-address static data -- NOT part of the caller's buffer, and
; not caller-visible. Safe because a program is single-threaded and a
; "read a line" call always runs to completion before returning, so
; there's no re-entrancy concern (the same reasoning every other
; lib/*.asm module's own static data already relies on). Only the
; BUFFER itself is caller-supplied (never this library's own fixed
; LINE_BUF-equivalent) -- confirmed with the user as the whole point
; of a reusable library: using the shell's own LINE_BUF here would
; risk corrupting live shell state for any caller other than the
; shell itself.
;

; WRAPPING (2026-09-30). The editor tracks where the terminal's own
; cursor is (le_phys, a logical position 0..le_len+1 in the line) and
; moves it with one routine, le_goto, which knows the terminal width W
; (the kernel's TERM_COLS byte, 80 if unknown) and the column S at
; which input started (the caller's prompt length, passed in RC.1).
; Position p is on row (S+p) div W, column (S+p) mod W, counting rows
; from the one the prompt ended on.
;
;   - Moving FORWARD reprints the characters in between (the proven
;     "reprint to move right" technique the single-row editor always
;     used); the terminal's own auto-wrap carries it onto the next row.
;   - Moving BACKWARD on the same row uses backspaces (also unchanged);
;     to an earlier row it sends ESC[<n>A, then backspaces or ESC[<n>C
;     to reach the column.
;   - After printing, if the cursor sits exactly at a row boundary the
;     terminal may be in "pending wrap" (xterm/VT100 hold the cursor on
;     the last column until the next character; others have already
;     moved it). Printing the character that belongs in the next cell
;     and a backspace puts both kinds in the same place: column 0 of the
;     next row.
;
; On a line that never wraps, every byte sent is the same as before:
; backspaces left, reprinting right. The CSI sequences only appear once
; a line actually crosses a row boundary.
;
; RC.1 = LE_COL_UNKNOWN ($FF) turns wrapping off (width treated as 255,
; start column 0) for a caller that does not know its prompt length.
;
; HISTORY HAND-BACK. With LE_OPT_HIST set in D, Up/Down (and Ctrl-P/
; Ctrl-N) return to the caller with DF=0 and D = LE_KEY_UP/LE_KEY_DOWN
; instead of being discarded. The caller may rewrite the buffer (a
; NUL-terminated string) and then calls read_line_resume with D=1 (the
; buffer changed: redraw it, cursor at the end) or D=0 (nothing
; changed); editing continues exactly where it left off. Enter always
; returns D = LE_KEY_ENTER (0).
;

#include    include/opcodes.def
#include    include/bios.inc
#include    include/kernel_api.inc
#include    include/lineedit.inc

LE_MAX_CAP:     equ     250             ; positions (incl. le_len+1)
                                        ; must stay below 256
LE_DEF_WIDTH:   equ     80              ; TERM_COLS unknown/implausible

            extrn   le_buf
            extrn   le_max_len
            extrn   le_mode
            extrn   le_rdvec
            extrn   le_opts
            extrn   le_len
            extrn   le_cursor
            extrn   le_phys
            extrn   le_width
            extrn   le_start
            extrn   le_startcol
            extrn   le_row
            extrn   le_col
            extrn   le_r1
            extrn   le_c1
            extrn   le_tgt
            extrn   le_pend
            extrn   le_pstart
            extrn   le_cnt
            extrn   le_csi_c
            extrn   le_dig
            extrn   le_eic_i
            extrn   le_eda_i
            extrn   le_oldlen

;------------------------------------------------------------------
; read_line_ex: see this file's own header comment.
; Args:    RF = caller-owned buffer (must be at least max_len+1 bytes)
;          RC.0 = max_len (max characters, NOT including the NUL;
;          values above LE_MAX_CAP are treated as LE_MAX_CAP)
;          RC.1 = column the input starts at (the prompt's length), or
;          LE_COL_UNKNOWN to disable wrapping
;          D = mode (LE_MODE_*) ORed with options (LE_OPT_HIST)
; Returns: DF=0: D = LE_KEY_ENTER, buffer holds a NUL-terminated line
;          (possibly empty); or (LE_OPT_HIST only) D = LE_KEY_UP/
;          LE_KEY_DOWN, editing suspended -- see read_line_resume
;          DF=1: EOF (LE_MODE_REDIR only) -- input was exhausted
;          before any real content was read this call; buffer holds
;          an empty string.
; Modifies: everything
;------------------------------------------------------------------
            proc    read_line_ex

            plo     r9                  ; stash D -- the mov below
                                        ; clobbers it (gotcha #4)
            mov     rb, le_mode
            glo     r9
            ani     $7F
            str     rb                  ; le_mode = mode bits
            mov     rb, le_opts
            glo     r9
            ani     $80
            str     rb                  ; le_opts = option bits

            ; point le_rdvec (an LBR in this library's data) at the
            ; read routine for this mode, once, so that every read below
            ; is a plain "call le_rdvec" with nothing in between -- the
            ; bytes of an arrow-key sequence arrive back to back, and a
            ; mode dispatch before each read was slow enough to lose
            ; them (hardware-found 2026-09-30)
            glo     r9
            ani     $7F
            lbz     rle_v_fast          ; LE_MODE_FAST
            xri     LE_MODE_REDIR
            lbz     rle_v_redir
            ldi     high f_bread        ; LE_MODE_BITBANG
            phi     r8
            ldi     low f_bread
            lbr     rle_v_set
rle_v_fast:
            ldi     high f_uread
            phi     r8
            ldi     low f_uread
            lbr     rle_v_set
rle_v_redir:
            ldi     high K_READ
            phi     r8
            ldi     low K_READ
rle_v_set:
            plo     r8                  ; R8 = read routine
            mov     rb, le_rdvec
            inc     rb
            ghi     r8
            str     rb
            inc     rb
            glo     r8
            str     rb                  ; le_rdvec = LBR <routine>

            glo     rc
            smi     LE_MAX_CAP+1
            lbnf    rle_max_ok          ; RC.0 <= LE_MAX_CAP
            ldi     LE_MAX_CAP
            plo     rc
rle_max_ok:
            mov     rb, le_max_len
            glo     rc
            str     rb                  ; le_max_len = RC.0

            mov     rb, le_startcol
            ghi     rc
            str     rb                  ; le_startcol = RC.1

            mov     rb, le_buf
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; le_buf = RF

            ldi     0
            str     rf                  ; buffer[0] = 0 (empty line)
            mov     rf, le_len
            ldi     0
            str     rf
            mov     rf, le_cursor
            ldi     0
            str     rf
            mov     rf, le_phys
            ldi     0
            str     rf

            ; ---- geometry: width W and start column S ----
            mov     rf, le_startcol
            ldn     rf
            xri     LE_COL_UNKNOWN
            lbnz    rle_known
            mov     rf, le_width        ; unknown prompt: no wrapping
            ldi     255
            str     rf
            mov     rf, le_start
            ldi     0
            str     rf
            lbr     le_loop

rle_known:
            mov     rf, TERM_COLS
            ldn     rf
            smi     8
            lbdf    rle_w_ok            ; >= 8: believe it
            ldi     LE_DEF_WIDTH-8      ; 0 (unknown) or implausible
rle_w_ok:
            adi     8
            plo     r9
            mov     rf, le_width
            glo     r9
            str     rf                  ; le_width = W

            ; S = startcol mod W
            mov     rf, le_startcol
            ldn     rf
rle_mod:
            plo     r8                  ; R8.0 = remainder so far
            mov     rf, le_width
            ldn     rf
            str     r2                  ; M(X) = W
            glo     r8
            sm                          ; D = rem - W
            lbdf    rle_mod             ; rem >= W: keep subtracting
            mov     rf, le_start
            glo     r8
            str     rf                  ; le_start = S

            ; prompt ended exactly at a row boundary: normalize a
            ; possible pending wrap so the cursor really is at column
            ; 0 of the next row, where le_start = 0 says it is
            glo     r8
            lbnz    le_loop
            mov     rf, le_startcol
            ldn     rf
            lbz     le_loop             ; no prompt at all
            ldi     ' '
            call    K_TYPE
            ldi     8
            call    K_TYPE
            lbr     le_loop

;------------------------------------------------------------------
; read_line_resume: continue a read_line_ex call that returned
; LE_KEY_UP/LE_KEY_DOWN. The caller may have rewritten the buffer
; (still the one given to read_line_ex).
; Args:    D = 0: buffer unchanged; nonzero: buffer replaced -- redraw
;          it and put the cursor at its end
; Returns: as read_line_ex
;------------------------------------------------------------------
            public  read_line_resume
read_line_resume:
            lbz     le_loop             ; unchanged: keep editing

            ldi     0
            call    le_goto             ; to the start of the line

            mov     rf, le_len
            ldn     rf
            plo     r9
            mov     rf, le_oldlen
            glo     r9
            str     rf                  ; le_oldlen = old length

            ; le_len = strlen(buffer), capped at le_max_len
            ldi     0
            plo     r9                  ; R9.0 = length so far
rlr_len:
            glo     r9
            call    le_ptr              ; RF = &buffer[len] (R9 kept)
            ldn     rf
            lbz     rlr_len_done
            mov     rf, le_max_len
            ldn     rf
            str     r2
            glo     r9
            sm                          ; D = len - max
            lbdf    rlr_cap             ; len >= max: cut it here
            inc     r9
            lbr     rlr_len
rlr_cap:
            glo     r9
            call    le_ptr
            ldi     0
            str     rf                  ; buffer[max] = NUL
rlr_len_done:
            mov     rf, le_len
            glo     r9
            str     rf
            mov     rf, le_cursor
            glo     r9
            str     rf                  ; cursor at the end

            ; print to max(old, new): the new text, then spaces over
            ; whatever is left of the old one
            mov     rf, le_oldlen
            ldn     rf
            str     r2
            mov     rf, le_len
            ldn     rf
            sm                          ; D = new - old
            lbdf    rlr_newlonger
            mov     rf, le_oldlen
            ldn     rf
            lbr     rlr_print
rlr_newlonger:
            mov     rf, le_len
            ldn     rf
rlr_print:
            call    le_print_to
            mov     rf, le_cursor
            ldn     rf
            call    le_goto
            lbr     le_loop

;------------------------------------------------------------------
; Reading. Every byte comes from "call le_rdvec", an LBR set up by
; read_line_ex to K_READ, f_uread or f_bread for the mode -- the same
; path "call K_READ" takes (K_READ is itself an LBR to the routine), so
; a read costs nothing beyond the BIOS call. A byte of 0 is end of input
; (K_READ's EOF, LE_MODE_REDIR); in the other modes a NUL keystroke is
; treated the same way.
;
; Within an escape sequence each read follows the previous one after
; only a compare or two: the terminal sends "ESC [ A" back to back, and
; anything slower loses bytes (the old dispatch-per-read le_getchar
; did, on hardware, 2026-09-30).
;------------------------------------------------------------------

;------------------------------------------------------------------
; Main loop.
;------------------------------------------------------------------
le_loop:
            call    le_rdvec
            lbz     le_do_eof
            plo     rc                  ; RC.0 = char
            xri     27                  ; ESC checked FIRST, straight
            lbz     le_escape           ; off the byte: see above

            glo     rc
            xri     13                  ; CR
            lbz     le_finish
            glo     rc
            xri     10                  ; LF
            lbz     le_finish

            glo     rc
            xri     8                   ; backspace / Ctrl-H
            lbz     le_backspace

            glo     rc
            xri     1                   ; Ctrl-A: home
            lbz     le_home

            glo     rc
            xri     5                   ; Ctrl-E: end
            lbz     le_end

            glo     rc
            xri     2                   ; Ctrl-B: cursor left
            lbz     le_left

            glo     rc
            xri     6                   ; Ctrl-F: cursor right
            lbz     le_right

            glo     rc
            xri     4                   ; Ctrl-D: delete at cursor
            lbz     le_ctrld

            glo     rc
            xri     16                  ; Ctrl-P: same as Up
            lbz     le_up
            glo     rc
            xri     14                  ; Ctrl-N: same as Down
            lbz     le_down

            ; ---- any other control byte (including the still-
            ; deferred Ctrl-K/U/W/Y cut/paste keys): discard ----
            glo     rc
            smi     32
            lbnf    le_loop             ; < 32 ($20): discard

            ; ---- ordinary character: insert at cursor if there's room ----
            mov     rf, le_max_len
            ldn     rf
            str     r2                  ; M(X) = le_max_len (subtrahend)
            mov     rf, le_len
            ldn     rf                  ; D = le_len (minuend)
            sm                          ; DF=1 iff le_len >= le_max_len
            lbdf    le_loop             ; at cap: silently drop

            call    le_insert_char      ; RC.0 = character to insert
            lbr     le_loop

;------------------------------------------------------------------
; le_ptr: RF = &buffer[D].
; Modifies: R8, RD, RF (and D)
;------------------------------------------------------------------
le_ptr:
            plo     r8
            ldi     0
            phi     r8                  ; R8 = index (zero-extended)
            mov     rd, le_buf
            lda     rd
            phi     rf
            ldn     rd
            plo     rf
            add16   rf, r8
            rtn

;------------------------------------------------------------------
; le_charat: D = the character shown at position D -- buffer[D], or a
; space for a position at or past le_len (screen cells beyond the end
; of the text are blank).
; Modifies: R8, R9, RD, RF (and D)
;------------------------------------------------------------------
le_charat:
            plo     r9
            mov     rf, le_len
            ldn     rf
            str     r2                  ; M(X) = le_len
            glo     r9
            sm                          ; D = p - len, DF=1 iff p >= len
            lbdf    lca_space
            glo     r9
            call    le_ptr
            ldn     rf
            rtn
lca_space:
            ldi     ' '
            rtn

;------------------------------------------------------------------
; le_rowcol: row/column of position D, relative to the row input
; started on: le_row = (S+p) div W, le_col = (S+p) mod W.
; Modifies: R7, R8, R9, RF (and D). Makes no calls.
;------------------------------------------------------------------
le_rowcol:
            plo     r8
            ldi     0
            phi     r8                  ; R8 = p
            mov     rf, le_start
            ldn     rf
            str     r2
            glo     r8
            add                         ; D = p.lo + S
            plo     r8
            ghi     r8
            adci    0
            phi     r8                  ; R8 = S + p (16-bit)
            ldi     0
            plo     r9                  ; R9.0 = row

lrc_loop:
            mov     rf, le_width
            ldn     rf
            str     r2                  ; M(X) = W
            glo     r8
            sm                          ; D = lo - W
            plo     r7                  ; R7.0 = candidate low byte
            ghi     r8
            smbi    0                   ; D = hi - borrow
            lbnf    lrc_done            ; borrow: R8 < W
            phi     r8
            glo     r7
            plo     r8                  ; R8 -= W
            glo     r9
            adi     1
            plo     r9                  ; row++
            lbr     lrc_loop

lrc_done:
            mov     rf, le_row
            glo     r9
            str     rf
            mov     rf, le_col
            glo     r8
            str     rf
            rtn

;------------------------------------------------------------------
; le_print_to: print the cells from le_phys up to (not including) D
; -- text characters, then spaces for cells past the end -- leaving
; le_phys = D. If anything was printed and the cursor ended at a row
; boundary, resolve a possible pending wrap (see the header): print
; the cell under it again, then back up.
; Modifies: everything except RC (and D)
;------------------------------------------------------------------
le_print_to:
            plo     r9
            mov     rf, le_pend
            glo     r9
            str     rf                  ; le_pend = end
            mov     rf, le_pstart
            mov     rb, le_phys
            ldn     rb
            str     rf                  ; le_pstart = le_phys

lpt_loop:
            mov     rf, le_pend
            ldn     rf
            str     r2                  ; M(X) = end
            mov     rf, le_phys
            ldn     rf
            sm                          ; D = phys - end
            lbdf    lpt_done            ; phys >= end

            mov     rf, le_phys
            ldn     rf
            call    le_charat
            call    K_TYPE

            mov     rf, le_phys
            ldn     rf
            adi     1
            str     rf                  ; le_phys++
            lbr     lpt_loop

lpt_done:
            mov     rf, le_pstart
            ldn     rf
            str     r2
            mov     rf, le_phys
            ldn     rf
            sm
            lbz     lpt_ret             ; nothing printed

            mov     rf, le_phys
            ldn     rf
            call    le_rowcol
            mov     rf, le_col
            ldn     rf
            lbnz    lpt_ret             ; mid-row: no wrap question

            mov     rf, le_phys
            ldn     rf
            call    le_charat
            call    K_TYPE
            ldi     8
            call    K_TYPE
lpt_ret:
            rtn

;------------------------------------------------------------------
; le_goto: move the terminal cursor from le_phys to position D (at
; most le_len), leaving le_phys = D. Forward by reprinting, backward by
; backspaces on the same row or ESC[<n>A plus a column move otherwise.
; Modifies: everything except RC (and D)
;------------------------------------------------------------------
le_goto:
            plo     r9
            mov     rf, le_tgt
            glo     r9
            str     rf                  ; le_tgt = target

            mov     rf, le_phys
            ldn     rf
            str     r2                  ; M(X) = phys
            mov     rf, le_tgt
            ldn     rf
            sm                          ; D = tgt - phys, DF=1 iff >=
            lbnf    lg_back
            mov     rf, le_tgt
            ldn     rf
            lbr     le_print_to         ; forward: reprint up to it

lg_back:
            mov     rf, le_phys
            ldn     rf
            call    le_rowcol
            mov     rf, le_row
            ldn     rf
            plo     r9
            mov     rf, le_r1
            glo     r9
            str     rf                  ; le_r1 = row of phys
            mov     rf, le_col
            ldn     rf
            plo     r9
            mov     rf, le_c1
            glo     r9
            str     rf                  ; le_c1 = column of phys

            mov     rf, le_tgt
            ldn     rf
            call    le_rowcol           ; le_row/le_col = target's

            mov     rf, le_row
            ldn     rf
            str     r2
            mov     rf, le_r1
            ldn     rf
            sm                          ; D = r1 - r2 (never negative)
            lbz     lg_horiz
            plo     r9
            ldi     'A'
            plo     r7
            glo     r9
            call    le_csi              ; up r1-r2 rows

lg_horiz:
            mov     rf, le_c1
            ldn     rf
            str     r2
            mov     rf, le_col
            ldn     rf
            sm                          ; D = c2 - c1
            lbz     lg_done
            lbdf    lg_right            ; c2 > c1
            mov     rf, le_col
            ldn     rf
            str     r2
            mov     rf, le_c1
            ldn     rf
            sm                          ; D = c1 - c2
            call    le_bs_n
            lbr     lg_done

lg_right:
            plo     r9                  ; D = c2 - c1 (branches keep D)
            ldi     'C'
            plo     r7
            glo     r9
            call    le_csi

lg_done:
            mov     rf, le_tgt
            ldn     rf
            plo     r9
            mov     rf, le_phys
            glo     r9
            str     rf                  ; le_phys = target
            rtn

;------------------------------------------------------------------
; le_bs_n: print D backspaces (D may be 0).
; Modifies: RF (and D)
;------------------------------------------------------------------
le_bs_n:
            plo     r9
            mov     rf, le_cnt
            glo     r9
            str     rf
lbs_loop:
            mov     rf, le_cnt
            ldn     rf
            lbz     lbs_done
            smi     1
            str     rf
            ldi     8
            call    K_TYPE
            lbr     lbs_loop
lbs_done:
            rtn

;------------------------------------------------------------------
; le_csi: send ESC [ <n> <letter>, n in decimal (1..255).
; Args:    D = n, R7.0 = final letter
; Modifies: R8, R9, RF (and D)
;------------------------------------------------------------------
le_csi:
            plo     r9                  ; R9.0 = n
            mov     rf, le_csi_c
            glo     r7
            str     rf                  ; le_csi_c = letter

            ldi     0
            plo     r8                  ; R8.0 = hundreds
lcs_h:
            glo     r9
            smi     100
            lbnf    lcs_h_done
            plo     r9
            glo     r8
            adi     1
            plo     r8
            lbr     lcs_h
lcs_h_done:
            ldi     0
            phi     r8                  ; R8.1 = tens
lcs_t:
            glo     r9
            smi     10
            lbnf    lcs_t_done
            plo     r9
            ghi     r8
            adi     1
            phi     r8
            lbr     lcs_t
lcs_t_done:
            mov     rf, le_dig
            glo     r8
            str     rf                  ; le_dig[0] = hundreds
            inc     rf
            ghi     r8
            str     rf                  ; le_dig[1] = tens
            inc     rf
            glo     r9
            str     rf                  ; le_dig[2] = ones

            ldi     27
            call    K_TYPE
            ldi     '['
            call    K_TYPE

            mov     rf, le_dig
            ldn     rf
            lbz     lcs_no_h
            adi     '0'
            call    K_TYPE
            lbr     lcs_tens            ; tens always printed now
lcs_no_h:
            mov     rf, le_dig+1
            ldn     rf
            lbz     lcs_ones
lcs_tens:
            mov     rf, le_dig+1
            ldn     rf
            adi     '0'
            call    K_TYPE
lcs_ones:
            mov     rf, le_dig+2
            ldn     rf
            adi     '0'
            call    K_TYPE
            mov     rf, le_csi_c
            ldn     rf
            call    K_TYPE
            rtn

;------------------------------------------------------------------
; le_insert_char: insert RC.0 into the buffer at le_cursor, shifting
; the tail (including the NUL) right by one, redraw from the cursor to
; the end, and advance the cursor. Caller has already confirmed
; there's room (le_len < le_max_len).
;
; The shift loop is a POST-test loop (copy first, then check whether
; that was the last needed copy): a pre-test/decrement loop breaks at
; cursor==0 on an empty line, since its counter would need to reach -1
; but wraps to 255 instead.
; Args:    RC.0 = character to insert
; Modifies: everything except RC (and D)
;------------------------------------------------------------------
le_insert_char:
            mov     rb, le_eic_i
            mov     rf, le_len
            ldn     rf
            str     rb                  ; i = le_len

leic_shift_loop:
            mov     rf, le_eic_i
            ldn     rf
            call    le_ptr              ; RF = &buffer[i]
            ldn     rf
            plo     r9
            inc     rf
            glo     r9
            str     rf                  ; buffer[i+1] = buffer[i]

            mov     rf, le_cursor
            ldn     rf
            str     r2
            mov     rf, le_eic_i
            ldn     rf
            sm                          ; D = i - le_cursor
            lbz     leic_shift_done     ; i == le_cursor: done

            mov     rf, le_eic_i
            ldn     rf
            smi     1
            str     rf                  ; i--
            lbr     leic_shift_loop

leic_shift_done:
            mov     rf, le_cursor
            ldn     rf
            call    le_ptr
            glo     rc
            str     rf                  ; buffer[le_cursor] = char

            mov     rf, le_len
            ldn     rf
            adi     1
            str     rf                  ; le_len++

            ldn     rf                  ; D = le_len
            call    le_print_to         ; from the cursor to the end

            mov     rf, le_cursor
            ldn     rf
            adi     1
            str     rf                  ; le_cursor++
            lbr     le_goto             ; and put the cursor there

;------------------------------------------------------------------
; le_delete_at: delete the character at le_cursor, shifting the rest
; (including the NUL) left by one, then redraw from there to one past
; the new end (blanking the old last cell) and return the terminal
; cursor to le_cursor. The terminal cursor must already be at
; le_cursor (le_phys == le_cursor). Caller has already confirmed
; le_cursor < le_len.
; Modifies: everything except RC (and D)
;------------------------------------------------------------------
le_delete_at:
            mov     rb, le_eda_i
            mov     rf, le_cursor
            ldn     rf
            str     rb                  ; i = le_cursor

ledel_shift_loop:
            ; pre-test is safe here (unlike the insert loop) since i
            ; only ever increases -- no underflow risk
            mov     rf, le_len
            ldn     rf
            str     r2                  ; M(X) = le_len
            mov     rf, le_eda_i
            ldn     rf                  ; D = i
            sm                          ; DF=1 iff i >= le_len
            lbdf    ledel_shift_done

            mov     rf, le_eda_i
            ldn     rf
            call    le_ptr              ; RF = &buffer[i]
            inc     rf
            ldn     rf                  ; D = buffer[i+1]
            dec     rf
            str     rf                  ; buffer[i] = buffer[i+1]

            mov     rf, le_eda_i
            ldn     rf
            adi     1
            str     rf                  ; i++
            lbr     ledel_shift_loop

ledel_shift_done:
            mov     rf, le_len
            ldn     rf
            smi     1
            str     rf                  ; le_len--

            ldn     rf
            adi     1                   ; D = new le_len + 1
            call    le_print_to         ; text, then one blank
            mov     rf, le_cursor
            ldn     rf
            lbr     le_goto             ; back to the cursor

;------------------------------------------------------------------
; Key handlers. Plain jump targets -- each ends with "lbr le_loop".
;------------------------------------------------------------------
le_home:
            mov     rf, le_cursor
            ldi     0
            str     rf
            call    le_goto             ; D = 0 (str keeps D)
            lbr     le_loop

le_end:
            mov     rf, le_len
            ldn     rf
            plo     r9
            mov     rf, le_cursor
            glo     r9
            str     rf                  ; le_cursor = le_len
            call    le_goto             ; D = le_len (str keeps D)
            lbr     le_loop

le_left:
            mov     rf, le_cursor
            ldn     rf
            lbz     le_loop             ; already at 0: no-op
            smi     1
            str     rf                  ; le_cursor--
            call    le_goto             ; D = new cursor
            lbr     le_loop

le_right:
            mov     rf, le_cursor
            ldn     rf
            str     r2                  ; M(X) = le_cursor
            mov     rf, le_len
            ldn     rf
            sm                          ; D = le_len - le_cursor
            lbz     le_loop             ; already at end: no-op
            mov     rf, le_cursor
            ldn     rf
            adi     1
            str     rf                  ; le_cursor++
            call    le_goto
            lbr     le_loop

le_ctrld:
            mov     rf, le_cursor
            ldn     rf
            str     r2                  ; M(X) = le_cursor
            mov     rf, le_len
            ldn     rf
            sm                          ; D = le_len - le_cursor
            lbz     le_loop             ; at end: nothing to delete
            call    le_delete_at
            lbr     le_loop

le_backspace:
            mov     rf, le_cursor
            ldn     rf
            lbz     le_loop             ; at start: no-op
            smi     1
            str     rf                  ; le_cursor = hole
            call    le_goto             ; terminal cursor onto the hole
            call    le_delete_at
            lbr     le_loop

le_up:
            mov     rf, le_opts
            ldn     rf
            ani     LE_OPT_HIST
            lbz     le_loop             ; no history: discard
            ldi     LE_KEY_UP
            clc
            rtn

le_down:
            mov     rf, le_opts
            ldn     rf
            ani     LE_OPT_HIST
            lbz     le_loop
            ldi     LE_KEY_DOWN
            clc
            rtn

;------------------------------------------------------------------
; le_escape: the byte(s) after an ESC, read with nothing between the
; reads but a compare (see "Reading" above). Malformed or unknown
; sequences are discarded, never guessed at.
;------------------------------------------------------------------
le_escape:
            call    le_rdvec
            lbz     le_do_eof
            xri     '['
            lbnz    le_loop             ; not a CSI sequence: discard

            call    le_rdvec
            lbz     le_do_eof
            plo     rc                  ; RC.0 = final byte
            xri     '3'                 ; Del is "ESC [ 3 ~": one more
            lbz     les_del             ; byte coming, so check it first

            glo     rc
            xri     'A'                 ; Up
            lbz     le_up
            glo     rc
            xri     'B'                 ; Down
            lbz     le_down
            glo     rc
            xri     'C'                 ; Right arrow
            lbz     le_right
            glo     rc
            xri     'D'                 ; Left arrow
            lbz     le_left
            lbr     le_loop             ; unrecognized: discard

les_del:
            call    le_rdvec            ; the expected '~'
            lbz     le_do_eof
            xri     '~'
            lbnz    le_loop             ; malformed: discard
            lbr     le_ctrld            ; Del: same as Ctrl-D

le_finish:
            ; leave the terminal cursor after the whole line, so the
            ; caller's newline doesn't land inside a wrapped line
            mov     rf, le_len
            ldn     rf
            call    le_goto
            ldi     LE_KEY_ENTER
            clc                         ; DF=0: a normal line
            rtn

le_do_eof:
            ; LE_MODE_REDIR only. A partial line already accumulated
            ; this call is still returned as a normal DF=0 line,
            ; matching K_INPUTL's own "final line with no trailing
            ; newline is still returned once" rule -- only a call that
            ; read nothing at all before hitting EOF reports DF=1.
            mov     rf, le_len
            ldn     rf
            lbnz    le_finish
            stc                         ; nothing read at all: true EOF
            rtn

            endp

;------------------------------------------------------------------
; Shared data -- one dedicated data proc (see CLAUDE.md gotcha #20).
;------------------------------------------------------------------
            proc    _lineedit_data

le_buf:             dw      0           ; caller's buffer pointer
le_max_len:         db      0           ; max characters (no NUL)
le_mode:            db      0           ; LE_MODE_*
le_rdvec:           db      $C0,0,0     ; LBR <read routine>, set by
                                        ; read_line_ex -- see "Reading"
le_opts:            db      0           ; LE_OPT_* bits
le_len:             db      0           ; current line length
le_cursor:          db      0           ; cursor position, 0..le_len
le_phys:            db      0           ; where the TERMINAL's cursor
                                        ; is, as a line position
                                        ; (0..le_len+1)
le_width:           db      0           ; terminal width W
le_start:           db      0           ; start column S (mod W)
le_startcol:        db      0           ; RC.1 as passed
le_row:             db      0           ; le_rowcol results
le_col:             db      0
le_r1:              db      0           ; le_goto: phys row/column
le_c1:              db      0
le_tgt:             db      0           ; le_goto: target position
le_pend:            db      0           ; le_print_to: end position
le_pstart:          db      0           ; le_print_to: start position
le_cnt:             db      0           ; le_bs_n: count
le_csi_c:           db      0           ; le_csi: final letter
le_dig:             ds      3           ; le_csi: decimal digits
le_eic_i:           db      0           ; le_insert_char: shift index
le_eda_i:           db      0           ; le_delete_at: shift index
le_oldlen:          db      0           ; read_line_resume: old length

                public  le_buf
                public  le_max_len
                public  le_mode
                public  le_rdvec
                public  le_opts
                public  le_len
                public  le_cursor
                public  le_phys
                public  le_width
                public  le_start
                public  le_startcol
                public  le_row
                public  le_col
                public  le_r1
                public  le_c1
                public  le_tgt
                public  le_pend
                public  le_pstart
                public  le_cnt
                public  le_csi_c
                public  le_dig
                public  le_eic_i
                public  le_eda_i
                public  le_oldlen

            endp
