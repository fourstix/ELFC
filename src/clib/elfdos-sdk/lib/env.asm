;
; env.asm - environment variable library (getenv/setenv/unsetenv)
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/env.prg) and
; linked alongside a program that wants it, the same way
; lib/heap_bump.asm/lib/heap_malloc.asm already do. A calling program
; declares "extrn env_getenv" / "extrn env_setenv" / "extrn
; env_unsetenv" and calls them like any other routine.
;
; Direct port of Elf/OS's own C implementation (getenv.c/setenv.c/
; unsetenv.c in this project's own root, plus their two helpers
; _env_read_line.c/_env_split_line.c and the shared constants, all in
; ~/projects/Elf/ELFC/src/clib/stdlib/). On-disk store: a flat text
; file of "NAME=VALUE\n" lines at "<shell_drive>:/cfg/env.dat" --
; "/cfg" is already an established path in this project's own history
; (see progs/copy.asm's own header comment). setenv/unsetenv both work
; by streaming the existing file into "<shell_drive>:/cfg/env.tmp"
; (copying every line through unchanged except the one being
; changed/dropped), then swapping the temp file into place via
; K_FILE_DELETE+K_FILE_RENAME (this kernel's own rename refuses to
; overwrite an existing destination, so delete-then-rename is
; required, exactly matching why the C reference does the same thing
; with remove()+rename()) -- same small crash-safety caveat the C
; reference already accepts: a crash between the delete and the
; rename briefly leaves no env.dat.
;
; BUG FIX (2026-08-21), two real, hardware-reported issues: (1) the
; store's own path used to be a bare, driveless "/cfg/env.dat" --
; resolved by the kernel against whatever drive happened to be ACTIVE
; at the moment a call was made, not any fixed drive, so EXPORT/UNSET/
; PRINTENV were silently reading and writing a DIFFERENT store (or
; none at all) depending purely on which drive was active when they
; ran. Fixed by anchoring every path to shell_drive (K_GETSHELLDRIVE)
; via the new _env_build_paths, called at the top of every public
; entry point below -- one single, consistent environment for the
; whole session regardless of the active drive. (2) EXPORT/UNSET both
; failed completely silently (no message, just a nonzero exit code)
; the very first time either ran on a drive whose "/cfg" didn't exist
; yet -- a real first-boot trap, since nothing in this project
; auto-creates "/cfg". Fixed by having env_setenv/env_unsetenv both
; best-effort auto-create "/cfg" (via K_DIR_CREATE, ignoring its
; "already exists" case) immediately before they need it.
;
; Calling convention (register-passed, RF for the primary string
; pointer -- matching K_FILE_DELETE/DEL/REN's own use of RF for path
; args):
;   env_getenv:   Args RF=name. Returns RF=pointer to the value (an
;                 internal static buffer, valid until the next
;                 env_getenv/env_setenv/env_unsetenv call -- matching
;                 the real getenv's own contract), or RF=0 if not
;                 found or the env file doesn't exist yet.
;   env_setenv:   Args RF=name, RD=value, D=overwrite (0 = leave an
;                 existing value untouched, nonzero = replace).
;                 Returns DF=0/1 (error: name contains '=', can't
;                 create the temp file, or the final rename failed).
;   env_unsetenv: Args RF=name. Returns DF=0/1 -- DF=0 even if the
;                 variable was never set, matching the real
;                 unsetenv's idempotent success.
;
; None of the three high-level routines are safe to call re-entrantly
; or concurrently (they share one set of internal scratch/FCBs) -- not
; a concern on this single-threaded kernel, same assumption
; kernel/redir.asm's own _redir_reserve already documents.
;

#include    include/opcodes.def
#include    include/kernel_api.inc

            extrn   drive_letter_of

ENV_LINE_MAX:   equ     128         ; bounds NAME=VALUE\0. Was 64, the C
                                    ; reference's own constant, until
                                    ; 2026-09-09: PATH wants more room
                                    ; than 58 characters of value, and
                                    ; other variables may too.
                                    ;
                                    ; Costs 2 bytes of PROGRAM RAM per
                                    ; byte (it sizes env_line_buf and
                                    ; env_namebuf, nothing else), which
                                    ; is noise beside the two 512-byte
                                    ; iobufs this library already
                                    ; carries. The on-disk store is
                                    ; unaffected -- env.dat is
                                    ; newline-terminated text, not
                                    ; fixed-width records, so files
                                    ; written at either size stay
                                    ; readable.
                                    ;
                                    ; CEILING IS 255: env_read_line
                                    ; takes its maxlen in RC.0, one
                                    ; byte. Going past that means
                                    ; widening that argument.
                                    ;
                                    ; A program still built with 64
                                    ; silently TRUNCATES a longer line
                                    ; to 63 characters rather than
                                    ; reporting anything (see
                                    ; env_read_line's own header), so
                                    ; everything linking this library
                                    ; needs rebuilding together.

            extrn   env_line_buf
            extrn   env_namebuf
            extrn   env_in_fcb
            extrn   env_in_iobuf
            extrn   env_out_fcb
            extrn   env_out_iobuf
            extrn   env_name
            extrn   env_value
            extrn   env_overwrite
            extrn   env_found
            extrn   env_len
            extrn   env_eq_byte
            extrn   env_nl_byte
            extrn   env_file_path
            extrn   env_tmp_path
            extrn   env_cfg_path
            extrn   env_file_suffix
            extrn   env_tmp_suffix
            extrn   env_cfg_suffix
            extrn   env_dat_name
            extrn   env_split_line
            extrn   env_read_line
            extrn   _env_streq
            extrn   _env_write_line
            extrn   env_next
            extrn   _env_build_paths

; ----------------------------------------------------------------
; env_read_line: read one line (up to '\n' or EOF) from env_in_fcb (the
; library's own shared read FCB, always the same fixed address) into a
; buffer, stripping the trailing newline, null-terminating the result.
; Truncates (silently drops the remainder of) a line longer than
; maxlen-1, matching the C reference's own behavior.
; Args:    RF = buffer, RC = maxlen (RC.0 only -- this library only
;          ever calls it with ENV_LINE_MAX=64, so one byte's range is
;          more than enough)
; Returns: DF = 0 on a real line (RC = length stored, 0..maxlen-1,
;          buffer null-terminated), DF = 1 at true EOF with nothing
;          read at all this call (matches K_INPUTL's own DF-based EOF
;          contract from this same project, not the C reference's -1
;          return -- a final line with no trailing newline is still
;          returned once, DF=0, before the FOLLOWING call reports
;          true EOF).
; Modifies: R7, R8, R9, RB, RC, RD, RF (and D) -- K_FILE_READ's own
;          clobber footprint is broad and undocumented beyond
;          RD-in/RC-out/DF-out, so nothing here is trusted to survive
;          it in a register; every value needed across the call is
;          stashed to memory first.
; ----------------------------------------------------------------
            proc    env_read_line

            mov     rb, erl_wptr
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; erl_wptr = buffer pointer

            mov     rb, erl_maxlen
            glo     rc
            str     rb                  ; erl_maxlen = maxlen (low
                                        ; byte)

            mov     rb, erl_count
            ldi     0
            str     rb                  ; erl_count = 0

            mov     rb, erl_got
            ldi     0
            str     rb                  ; erl_got = 0

erl_loop:
            mov     rf, erl_scratch
            ldi     0
            phi     rc
            ldi     1
            plo     rc                  ; RC = 1
            mov     rd, env_in_fcb      ; RD = FCB pointer (fixed --
                                        ; always the same shared read
                                        ; FCB, no capture needed)
            call    K_FILE_READ
            lbdf    erl_check_got       ; I/O error -- treat the same
                                        ; as EOF (matches the C
                                        ; reference's "r <= 0" merge)

            glo     rc
            lbnz    erl_got_byte        ; RC != 0: got a real byte
                                        ; (a 1-byte request can only
                                        ; ever return 0 or 1)

erl_check_got:
            mov     rf, erl_got
            ldn     rf
            lbnz    erl_terminate       ; already had content this
                                        ; call: EOF is the natural end
                                        ; of this (unterminated) line
            stc                         ; nothing read at all: true
                                        ; EOF
            rtn

erl_got_byte:
            mov     rf, erl_got
            ldi     1
            str     rf                  ; erl_got = 1

            mov     rf, erl_scratch
            ldn     rf                  ; D = the byte just read
            smi     10                  ; '\n' ?
            lbz     erl_terminate

            ; not a newline -- room for it? (count < maxlen - 1)
            mov     rf, erl_maxlen
            ldn     rf
            smi     1                   ; D = maxlen - 1
            str     r2                  ; [R2] = maxlen - 1
            mov     rf, erl_count
            ldn     rf                  ; D = count
            sm                          ; D = count - (maxlen - 1),
                                        ; DF = 1 iff count >= maxlen-1
            lbdf    erl_loop            ; full: silently drop this
                                        ; byte, keep reading

            ; room available: *wptr++ = byte; count++
            mov     rf, erl_wptr
            lda     rf
            phi     r8
            ldn     rf
            plo     r8                  ; R8 = wptr
            mov     rf, erl_scratch
            ldn     rf                  ; D = the byte
            str     r8                  ; *wptr = byte
            inc     r8                  ; wptr++
            mov     rf, erl_wptr
            ghi     r8
            str     rf
            inc     rf
            glo     r8
            str     rf                  ; erl_wptr = wptr

            mov     rf, erl_count
            ldn     rf
            adi     1
            str     rf                  ; erl_count++

            lbr     erl_loop

erl_terminate:
            mov     rf, erl_wptr
            lda     rf
            phi     r8
            ldn     rf
            plo     r8                  ; R8 = wptr (== buf + count)
            ldi     0
            str     r8                  ; *wptr = 0 (null terminator)

            mov     rf, erl_count
            ldn     rf
            plo     rc
            ldi     0
            phi     rc                  ; RC = count (return value)
            clc
            rtn

; ----------------------------------------------------------------
; Proc-private scratch -- nothing outside env_read_line ever
; references these, so no extrn/public wiring is needed.
; ----------------------------------------------------------------
erl_wptr:       dw      0
erl_maxlen:     db      0
erl_count:      db      0
erl_got:        db      0
erl_scratch:    db      0

            endp

; ----------------------------------------------------------------
; env_split_line: given a "NAME=VALUE" line, locate the '='
; separator, replace it with '\0' in place, so the NAME portion
; becomes its own null-terminated string at the start of the buffer.
; Args:    RF = line (mutated in place)
; Returns: RD = pointer to the VALUE portion (the byte after the old
;          '='), or RD = 0 if no '=' was found (RF's own content is
;          left untouched in that case)
; Modifies: RF (and D)
; ----------------------------------------------------------------
            proc    env_split_line

esl_loop:
            ldn     rf                  ; D = *RF
            lbz     esl_notfound        ; '\0': reached end, no '='
            smi     '='
            lbz     esl_found
            inc     rf
            lbr     esl_loop

esl_found:
            ldi     0
            str     rf                  ; *RF = '\0' (replaces '=')
            inc     rf
            mov     rd, rf              ; RD = pointer just past the
                                        ; old '=' (the value portion)
            rtn

esl_notfound:
            ldi     0
            phi     rd
            plo     rd                  ; RD = 0
            rtn

            endp

; ----------------------------------------------------------------
; _env_streq: byte-by-byte string equality check (not full strcmp
; ordering -- only equality is ever needed by this library). Hand-
; rolled rather than the BIOS's f_strcmp, whose clobber contract
; beyond its own documented args isn't confirmed for use outside the
; kernel.
; Args:    RF = str1, RD = str2
; Returns: DF = 0 if equal, DF = 1 if not equal
; Modifies: RF, RD (and D)
; ----------------------------------------------------------------
            proc    _env_streq

es_loop:
            ldn     rf                  ; D = *str1 (no advance yet)
            str     r2                  ; stage it (no register-
                                        ; register add16/sub16 runs
                                        ; before the xor below --
                                        ; gotcha #18)
            ldn     rd                  ; D = *str2
            xor                         ; D = *str1 XOR *str2
            lbnz    es_notequal

            ldn     rf                  ; D = *str1 again (reload --
                                        ; xor clobbered D): check for
                                        ; the terminator
            lbz     es_equal            ; both were NUL: fully matched

            inc     rf
            inc     rd
            lbr     es_loop

es_equal:
            clc
            rtn

es_notequal:
            stc
            rtn

            endp

; ----------------------------------------------------------------
; _env_build_paths: build the drive-prefixed env-store paths
; (env_file_path/env_tmp_path/env_cfg_path) fresh, anchored to the
; SHELL's own boot drive (K_GETSHELLDRIVE) rather than whichever
; drive happens to be active right now.
;
; BUG FIX (2026-08-21): env_file_path/env_tmp_path used to be plain,
; driveless "/cfg/env.dat"/"/cfg/env.tmp" constants -- K_PATH_RESOLVE's
; own documented behavior for a path with no "X:" prefix is to resolve
; it against whatever drive is CURRENTLY ACTIVE, not any fixed drive.
; So EXPORT/UNSET/PRINTENV were silently reading and writing a
; DIFFERENT env.dat (or none at all, on a drive that's never had one
; created) depending purely on which drive happened to be active at
; the moment they ran -- e.g. "export FOO=bar" while active on E:
; would create/use E:/cfg/env.dat, invisible to "printenv FOO" once
; back on C:. Fixed by anchoring to shell_drive (via K_GETSHELLDRIVE,
; the same primitive progs/shell.asm's own bare-command-name fallback
; search already uses for exactly this "one stable, well-known drive
; regardless of what's active" reasoning) -- one single, consistent
; environment store for the whole session, matching how a real DOS
; AUTOEXEC.BAT-style environment is expected to behave.
;
; Args:    none
; Returns: nothing (env_file_path/env_tmp_path/env_cfg_path updated)
; Modifies: R8, R9, RB, RD, RF (and D) -- R8 joined the list when
;           drive_letter_of replaced the old 'adi C' (2026-09-09);
;           env_getenv/setenv/unsetenv already documented it clobbered.
; ----------------------------------------------------------------
            proc    _env_build_paths

            call    K_GETSHELLDRIVE     ; D = shell_drive
            call    drive_letter_of     ; D = slot in, letter out
            plo     r9                  ; stash it -- R9 is free here,
                                        ; and the call below clobbers D

            mov     rd, env_file_path
            glo     r9
            str     rd
            inc     rd
            mov     rf, env_file_suffix
            call    ebp_strcpy_app      ; appends suffix + NUL at RD

            mov     rd, env_tmp_path
            glo     r9
            str     rd
            inc     rd
            mov     rf, env_tmp_suffix
            call    ebp_strcpy_app

            mov     rd, env_cfg_path
            glo     r9
            str     rd
            inc     rd
            mov     rf, env_cfg_suffix
            call    ebp_strcpy_app
            rtn

; ----------------------------------------------------------------
; ebp_strcpy_app: copy the NUL-terminated string at RF to RD
; (including the terminator). Internal to _env_build_paths only --
; called via a plain `call` from within this same proc, matching
; env_setenv's own se_write_nv/se_strlen precedent (no extrn/public
; needed for a helper only its own enclosing proc ever reaches).
; Args:    RF = src, RD = dst (both advance)
; ----------------------------------------------------------------
ebp_strcpy_app:
            lda     rf
            str     rd
            lbz     ebp_done
            inc     rd
            lbr     ebp_strcpy_app
ebp_done:
            rtn

            endp

; ----------------------------------------------------------------
; env_parse_uint: parse a decimal string into an unsigned integer,
; stopping at the first non-digit character. Moved here from
; progs/date.asm's own hardware-confirmed parse_uint (2026-07-17,
; including its own hard-won *2-not-*4 bugfix -- see that file's own
; history for the full story) -- ROWS/COLUMNS parsing needs the
; identical logic in multiple consuming programs (ls/more/edlin), and
; this avoids tripling it; date.asm's own copy is untouched (it's a
; single-file program with no lib/ dependency today, no reason to
; change that).
; Args:    RF = string pointer
; Returns: RD = parsed value (0 if the string starts with a
;          non-digit), RF = pointer to the first non-digit character
;          (unchanged from the input if there were no digits at all)
; Modifies: R8, R9, RD, RF (and D)
; ----------------------------------------------------------------
            proc    env_parse_uint

            ldi     0
            phi     rd
            plo     rd                  ; RD = 0

epu_loop:
            ldn     rf
            smi     '0'
            lbnf    epu_done            ; *RF < '0': not a digit
            plo     r9                  ; R9.0 = candidate digit value
            smi     10                  ; D = candidate - 10, DF=1 if
                                        ; candidate >= 10 (no borrow)
            lbdf    epu_done            ; not a valid digit

            mov     r8, rd
            shl16   r8
            shl16   r8
            shl16   r8                  ; R8 = RD*8
            shl16   rd                  ; RD = RD*2
            add16   rd, r8              ; RD = RD*10
            add16   rd, r9              ; RD += digit
            inc     rf
            lbr     epu_loop

epu_done:
            rtn

            endp

; ----------------------------------------------------------------
; _env_write_line: write env_line_buf's current content (env_len
; bytes, as measured by the most recent env_read_line call) plus a
; trailing '\n' to env_out_fcb. Shared by env_setenv and env_unsetenv
; for their "copy this line through unchanged" case.
; Args:    none (reads env_line_buf/env_len/env_out_fcb directly)
; Returns: nothing
; Modifies: R7, R8, R9, RB, RC, RD, RF (and D)
; ----------------------------------------------------------------
            proc    _env_write_line

            mov     rf, env_line_buf
            mov     rb, env_len
            lda     rb
            phi     rc
            ldn     rb
            plo     rc                  ; RC = env_len
            mov     rd, env_out_fcb     ; RD = FCB pointer (fixed)
            call    K_FILE_WRITE

            mov     rf, env_nl_byte
            ldi     0
            phi     rc
            ldi     1
            plo     rc                  ; RC = 1
            mov     rd, env_out_fcb
            call    K_FILE_WRITE
            rtn

            endp

; ----------------------------------------------------------------
; env_first/env_next: iterate over every "NAME=VALUE" line in the
; on-disk store, in file order, for callers that need to list every
; variable (printenv/export's own no-args case) rather than look up
; one name. Deliberately does NOT split each line -- the raw
; "NAME=VALUE" text (still null-terminated, '=' intact) is exactly
; what a listing wants to print. Reuses this library's own internal
; env_in_fcb/env_in_iobuf/env_line_buf (the same fields
; env_getenv/env_setenv/env_unsetenv already use for their own "read
; the source file" step) -- safe under this file's own standing
; single-threaded/non-reentrant assumption, as long as nothing calls
; env_getenv/env_setenv/env_unsetenv while a first/next scan is mid-
; flight (i.e. between env_first and the DF=1/RF=0 EOF return).
;
; env_first:
; Args:    none
; Returns: RF = pointer to the first line's raw content (env_line_buf,
;          unsplit), or RF = 0 if the file doesn't exist or is empty
;          (nothing to iterate).
; Modifies: broad (opens the file, then behaves exactly like env_next
;          below).
; ----------------------------------------------------------------
            proc    env_first

            call    _env_build_paths    ; no incoming args to protect

            mov     rf, env_file_path
            mov     rd, env_in_fcb
            mov     ra, env_in_iobuf
            ldi     0                   ; mode 0 = read -- set LAST,
                                        ; mov clobbers D (gotcha #4)
            call    K_FILE_OPEN         ; DF=0/1 (D unspecified --
                                        ; env_in_fcb is a fixed
                                        ; address, nothing to capture)
            lbdf    ef_empty            ; can't open: nothing to
                                        ; iterate

            lbr     env_next            ; tail call -- env_next's own
                                        ; "read one line, handle EOF"
                                        ; logic is exactly what's
                                        ; needed for the first line
                                        ; too; env_next's own rtn
                                        ; correctly returns to
                                        ; whatever called env_first,
                                        ; since this is a bare branch,
                                        ; not a nested call

ef_empty:
            ldi     0
            phi     rf
            plo     rf
            rtn

            endp

; ----------------------------------------------------------------
; env_next: continue an iteration started by env_first (or a
; previous successful env_next).
; Args:    none
; Returns: RF = pointer to the next line's raw content (env_line_buf,
;          unsplit), or RF = 0 at EOF (the file is closed
;          automatically in that case -- no separate "close" call is
;          needed from the caller).
; Modifies: R7, R8, R9, RB, RC, RF (and D), via env_read_line/
;          K_FILE_CLOSE.
; ----------------------------------------------------------------
            proc    env_next

            mov     rf, env_line_buf
            ldi     high ENV_LINE_MAX
            phi     rc
            ldi     low ENV_LINE_MAX
            plo     rc
            call    env_read_line
            lbdf    en_eof

            mov     rf, env_line_buf
            rtn

en_eof:
            mov     rd, env_in_fcb
            call    K_FILE_CLOSE
            ldi     0
            phi     rf
            plo     rf
            rtn

            endp

; ----------------------------------------------------------------
; env_getenv: look up an environment variable's value in the on-disk
; store.
; Args:    RF = name (null-terminated)
; Returns: RF = pointer to the value (an internal static buffer,
;          valid until the next env_getenv/env_setenv/env_unsetenv
;          call), or RF = 0 if not found or the env file doesn't
;          exist yet.
; Modifies: R7, R8, R9, RA, RB, RC, RD, RF (and D) -- broad, via the
;          K_FILE_* calls this makes.
; ----------------------------------------------------------------
            proc    env_getenv

            mov     rb, env_name
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; env_name = name pointer

            call    _env_build_paths    ; RF now safely stashed above

            mov     rf, env_file_path
            mov     rd, env_in_fcb
            mov     ra, env_in_iobuf
            ldi     0                   ; mode 0 = read -- set LAST,
                                        ; mov clobbers D (gotcha #4)
            call    K_FILE_OPEN         ; DF=0/1 (D unspecified --
                                        ; env_in_fcb is a fixed
                                        ; address, nothing to capture)
            lbdf    ge_notfound         ; can't open: no file yet

ge_loop:
            mov     rf, env_line_buf
            ldi     high ENV_LINE_MAX
            phi     rc
            ldi     low ENV_LINE_MAX
            plo     rc
            call    env_read_line
            lbdf    ge_eof              ; EOF: not found

            mov     rf, env_line_buf
            call    env_split_line      ; RD = value ptr or 0
            ghi     rd
            lbnz    ge_have_value
            glo     rd
            lbz     ge_loop             ; RD == 0: no '=' in this
                                        ; line, skip it (malformed)

ge_have_value:
            mov     rb, env_value
            ghi     rd
            str     rb
            inc     rb
            glo     rd
            str     rb                  ; env_value = value ptr
                                        ; (stashed -- _env_streq below
                                        ; clobbers RD)

            mov     rf, env_line_buf    ; RF = str1 (the name portion,
                                        ; now null-terminated at the
                                        ; old '=' position)
            mov     rd, env_name
            lda     rd
            phi     r8
            ldn     rd
            plo     r8
            mov     rd, r8              ; RD = str2 (target name,
                                        ; reloaded fresh from memory)
            call    _env_streq
            lbdf    ge_loop             ; DF=1: no match, keep
                                        ; scanning

            ; match! close the file and return the stashed value ptr
            mov     rd, env_in_fcb
            call    K_FILE_CLOSE

            mov     rb, env_value
            lda     rb
            phi     rf
            ldn     rb
            plo     rf                  ; RF = value ptr (reloaded
                                        ; fresh -- K_FILE_CLOSE's own
                                        ; clobber footprint isn't
                                        ; trusted)
            rtn

ge_eof:
            mov     rd, env_in_fcb
            call    K_FILE_CLOSE
ge_notfound:
            ldi     0
            phi     rf
            plo     rf
            rtn

            endp

; ----------------------------------------------------------------
; env_setenv: set (or update) an environment variable in the on-disk
; store.
; Args:    RF = name, RD = value, D = overwrite (0 = leave an
;          existing value untouched, nonzero = replace)
; Returns: DF = 0 on success, DF = 1 on error (name contains '=',
;          can't create the temp file, or the final rename failed)
; Modifies: broad -- everything but the caller's own registers before
;          the call; nothing survives across this routine's many
;          K_FILE_* calls except via the env_* scratch fields.
; ----------------------------------------------------------------
            proc    env_setenv

            plo     r9                  ; stash overwrite flag (D)
                                        ; immediately -- R9 is free
                                        ; here
            mov     rb, env_overwrite
            glo     r9
            str     rb                  ; env_overwrite = D

            mov     rb, env_name
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; env_name = name

            mov     rb, env_value
            ghi     rd
            str     rb
            inc     rb
            glo     rd
            str     rb                  ; env_value = value

            call    _env_build_paths    ; name/value already stashed
                                        ; above -- safe to clobber
                                        ; RF/RD/R9 now

            ; reject a name containing '='
            mov     rf, env_name
            lda     rf
            phi     r8
            ldn     rf
            plo     r8
            mov     rf, r8              ; RF = name (reloaded fresh)
se_rej_loop:
            ldn     rf
            lbz     se_name_ok          ; reached NUL: no '=' found
            smi     '='
            lbz     se_reject
            inc     rf
            lbr     se_rej_loop

se_reject:
            stc
            rtn

se_name_ok:
            ; Open the temp file for write (mode 1 = create/overwrite,
            ; always truncates fresh -- confirmed via this project's
            ; own file_open history) -- retrying with a best-effort
            ; /cfg auto-create ONLY if this first attempt fails.
            ;
            ; RESTRUCTURED (2026-08-21) from an earlier version of this
            ; same fix that called K_DIR_CREATE unconditionally, every
            ; single call. That version was investigated as a possible
            ; cause of real, hardware-reported /cfg corruption after
            ; heavy EXPORT/UNSET activity -- ruled out by reading
            ; dir_create's own collision path directly (kernel/file.asm):
            ; on an already-existing target it branches straight to its
            ; error return with zero intervening instructions, so it's
            ; a provably clean, read-only scan of the parent directory,
            ; not a write. The real, load-bearing effect of this fix
            ; making EXPORT/UNSET actually complete their full create-
            ; temp/delete-old/rename sequence reliably for the first
            ; time -- and that sequence never reuses a deleted
            ; directory-entry slot -- is the far more likely mechanism;
            ; see test/dirgrowtest.asm, built the same day to test that
            ; directly. This restructuring doesn't change end-user
            ; behavior at all (still auto-creates /cfg exactly when
            ; needed) -- it just cuts the unconditional per-call
            ; directory scan down to only the rare case that actually
            ; needs it (a missing /cfg), instead of paying for it on
            ; every single call once /cfg already exists.
            mov     rf, env_tmp_path
            mov     rd, env_out_fcb
            mov     ra, env_out_iobuf
            ldi     1                   ; set LAST (mov clobbers D,
                                        ; gotcha #4)
            call    K_FILE_OPEN         ; DF=0/1 (D unspecified --
                                        ; env_out_fcb is a fixed
                                        ; address, nothing to capture)
            lbnf    se_opened           ; success on the first try --
                                        ; the common case, /cfg already
                                        ; exists

            ; first attempt failed -- best-effort auto-create /cfg
            ; (K_DIR_CREATE's own DF=1 "already exists" case is
            ; deliberately ignored -- expected, common, and harmless;
            ; any OTHER failure, e.g. a full root or an invalid drive,
            ; is left to surface naturally at the retry just below
            ; instead of being duplicated here) and retry once.
            mov     rf, env_cfg_path
            call    K_DIR_CREATE        ; DF ignored -- see above.
                                        ; K_DIR_CREATE has no
                                        ; documented clobber list, so
                                        ; per this project's own
                                        ; standing convention it's
                                        ; treated as broadly unsafe --
                                        ; but nothing here needs
                                        ; anything it might have
                                        ; touched, since env_tmp_path
                                        ; is reloaded fresh from
                                        ; memory right below anyway

            mov     rf, env_tmp_path
            mov     rd, env_out_fcb
            mov     ra, env_out_iobuf
            ldi     1                   ; set LAST (mov clobbers D,
                                        ; gotcha #4)
            call    K_FILE_OPEN         ; DF=0/1
            lbdf    se_reject           ; still can't create temp file
                                        ; -- give up

se_opened:
            mov     rb, env_found
            ldi     0
            str     rb                  ; env_found = 0

            ; open the source file for read -- failure here is NOT
            ; fatal, it just means there's no existing env file yet
            mov     rf, env_file_path
            mov     rd, env_in_fcb
            mov     ra, env_in_iobuf
            ldi     0
            call    K_FILE_OPEN         ; DF=0/1 (D unspecified --
                                        ; env_in_fcb is a fixed
                                        ; address, nothing to capture)
            lbdf    se_no_source        ; open failed: skip the copy
                                        ; loop entirely

se_copy_loop:
            mov     rf, env_line_buf
            ldi     high ENV_LINE_MAX
            phi     rc
            ldi     low ENV_LINE_MAX
            plo     rc
            call    env_read_line
            lbdf    se_close_in         ; EOF: done copying

            mov     rb, env_len
            ghi     rc
            str     rb
            inc     rb
            glo     rc
            str     rb                  ; env_len = length (needed by
                                        ; _env_write_line below)

            ; preserve the pristine line: copy env_line_buf into
            ; env_namebuf, then split THAT copy (env_split_line
            ; mutates in place), so env_line_buf survives intact for
            ; a possible unchanged-copy-through write
            mov     rf, env_line_buf
            mov     rd, env_namebuf
se_cpy_loop:
            lda     rf
            str     rd
            lbnz    se_cpy_next
            lbr     se_cpy_done
se_cpy_next:
            inc     rd
            lbr     se_cpy_loop
se_cpy_done:

            mov     rf, env_namebuf
            call    env_split_line      ; RD = value ptr or 0
            ghi     rd
            lbnz    se_check_name
            glo     rd
            lbz     se_copy_through     ; RD == 0: no '=', copy
                                        ; through unchanged

se_check_name:
            mov     rf, env_namebuf
            mov     rd, env_name
            lda     rd
            phi     r8
            ldn     rd
            plo     r8
            mov     rd, r8              ; RD = target name
            call    _env_streq
            lbdf    se_copy_through     ; DF=1: no match, copy through

            ; match found
            mov     rb, env_found
            ldi     1
            str     rb                  ; env_found = 1

            mov     rb, env_overwrite
            ldn     rb
            lbz     se_write_old        ; overwrite==0: keep the
                                        ; original line verbatim

            call    se_write_nv         ; overwrite: write
                                        ; name=value\n
            lbr     se_copy_loop

se_write_old:
            call    _env_write_line
            lbr     se_copy_loop

se_copy_through:
            call    _env_write_line
            lbr     se_copy_loop

se_close_in:
            mov     rd, env_in_fcb
            call    K_FILE_CLOSE

se_no_source:
            ; if not found, append name=value\n before closing the
            ; output file
            mov     rb, env_found
            ldn     rb
            lbnz    se_close_out

            call    se_write_nv

se_close_out:
            mov     rd, env_out_fcb
            call    K_FILE_CLOSE

            ; swap the temp file into place
            mov     rf, env_file_path
            call    K_FILE_DELETE       ; DF ignored -- may not exist

            mov     rf, env_tmp_path
            mov     rd, env_dat_name
            call    K_FILE_RENAME       ; DF = overall return value
            rtn

; ----------------------------------------------------------------
; se_write_nv: write env_name + '=' + env_value + '\n' to
; env_out_fcb. Internal to env_setenv only (called via a plain
; `call` from within this same proc -- no extrn/public needed, unlike
; genuinely cross-proc routines).
; ----------------------------------------------------------------
se_write_nv:
            mov     rf, env_name
            lda     rf
            phi     r8
            ldn     rf
            plo     r8
            mov     rf, r8              ; RF = name pointer
            call    se_strlen           ; RC = length, RF unchanged
                                        ; (se_strlen never touches RF)
            mov     rd, env_out_fcb     ; RD = FCB pointer (fixed)
            call    K_FILE_WRITE

            mov     rf, env_eq_byte
            ldi     0
            phi     rc
            ldi     1
            plo     rc
            mov     rd, env_out_fcb
            call    K_FILE_WRITE

            mov     rf, env_value
            lda     rf
            phi     r8
            ldn     rf
            plo     r8
            mov     rf, r8              ; RF = value pointer
            call    se_strlen
            mov     rd, env_out_fcb
            call    K_FILE_WRITE

            mov     rf, env_nl_byte
            ldi     0
            phi     rc
            ldi     1
            plo     rc
            mov     rd, env_out_fcb
            call    K_FILE_WRITE
            rtn

; ----------------------------------------------------------------
; se_strlen: Args RF = str (left UNCHANGED -- scans with its own
; private copy in R8, never touching the caller's RF). Returns
; RC = length. Makes no calls of its own, so this is provably safe
; by direct inspection, not merely documented.
; ----------------------------------------------------------------
se_strlen:
            mov     r8, rf              ; R8 = scan pointer (copy)
            ldi     0
            phi     rc
            plo     rc                  ; RC = 0
se_strlen_loop:
            ldn     r8
            lbz     se_strlen_done
            inc     r8
            inc     rc
            lbr     se_strlen_loop
se_strlen_done:
            rtn

            endp

; ----------------------------------------------------------------
; env_unsetenv: remove an environment variable from the on-disk
; store.
; Args:    RF = name
; Returns: DF = 0 on success (including when the variable was not
;          set to begin with, matching the real unsetenv), DF = 1 on
;          error (name contains '=', can't create the temp file, or
;          the final rename failed)
; Modifies: broad, via this routine's many K_FILE_* calls.
; ----------------------------------------------------------------
            proc    env_unsetenv

            mov     rb, env_name
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; env_name = name

            call    _env_build_paths    ; RF already stashed above

            mov     rf, env_name
            lda     rf
            phi     r8
            ldn     rf
            plo     r8
            mov     rf, r8
ue_rej_loop:
            ldn     rf
            lbz     ue_name_ok
            smi     '='
            lbz     ue_reject
            inc     rf
            lbr     ue_rej_loop

ue_reject:
            stc
            rtn

ue_name_ok:
            ; Open the temp file for write, retrying with a best-
            ; effort /cfg auto-create ONLY if the first attempt fails
            ; -- restructured the same way and for the same reason as
            ; env_setenv's own identical block above (see its own
            ; comment for the full reasoning, including why the
            ; earlier unconditional-K_DIR_CREATE version was
            ; investigated, and ruled out, as a possible cause of real
            ; /cfg corruption). Doubly important that /cfg still gets
            ; auto-created here when genuinely missing: without SOME
            ; success path, a totally fresh install would make UNSET
            ; report failure for a name that was never set to begin
            ; with, breaking this routine's own documented "DF=0 even
            ; if the variable was never set" idempotent-success
            ; contract.
            mov     rf, env_tmp_path
            mov     rd, env_out_fcb
            mov     ra, env_out_iobuf
            ldi     1
            call    K_FILE_OPEN         ; DF=0/1
            lbnf    ue_opened           ; success on the first try

            mov     rf, env_cfg_path
            call    K_DIR_CREATE        ; DF ignored -- see above

            mov     rf, env_tmp_path
            mov     rd, env_out_fcb
            mov     ra, env_out_iobuf
            ldi     1
            call    K_FILE_OPEN         ; DF=0/1 (D unspecified --
                                        ; env_out_fcb is a fixed
                                        ; address, nothing to capture)
            lbdf    ue_reject

ue_opened:
            mov     rf, env_file_path
            mov     rd, env_in_fcb
            mov     ra, env_in_iobuf
            ldi     0
            call    K_FILE_OPEN         ; DF=0/1 (D unspecified --
                                        ; env_in_fcb is a fixed
                                        ; address, nothing to capture)
            lbdf    ue_close_out        ; no source file: nothing to
                                        ; copy, just finish up

ue_copy_loop:
            mov     rf, env_line_buf
            ldi     high ENV_LINE_MAX
            phi     rc
            ldi     low ENV_LINE_MAX
            plo     rc
            call    env_read_line
            lbdf    ue_close_in

            mov     rb, env_len
            ghi     rc
            str     rb
            inc     rb
            glo     rc
            str     rb

            mov     rf, env_line_buf
            mov     rd, env_namebuf
ue_cpy_loop:
            lda     rf
            str     rd
            lbnz    ue_cpy_next
            lbr     ue_cpy_done
ue_cpy_next:
            inc     rd
            lbr     ue_cpy_loop
ue_cpy_done:

            mov     rf, env_namebuf
            call    env_split_line
            ghi     rd
            lbnz    ue_check_name
            glo     rd
            lbz     ue_copy_through

ue_check_name:
            mov     rf, env_namebuf
            mov     rd, env_name
            lda     rd
            phi     r8
            ldn     rd
            plo     r8
            mov     rd, r8
            call    _env_streq
            lbdf    ue_copy_through     ; no match: copy through

            ; match: drop the line (don't write it), just loop
            lbr     ue_copy_loop

ue_copy_through:
            call    _env_write_line
            lbr     ue_copy_loop

ue_close_in:
            mov     rd, env_in_fcb
            call    K_FILE_CLOSE

ue_close_out:
            mov     rd, env_out_fcb
            call    K_FILE_CLOSE

            mov     rf, env_file_path
            call    K_FILE_DELETE

            mov     rf, env_tmp_path
            mov     rd, env_dat_name
            call    K_FILE_RENAME
            rtn

            endp

; ----------------------------------------------------------------
; Shared data -- reused across env_getenv/env_setenv/env_unsetenv/
; _env_write_line, never active concurrently within one caller (see
; this file's own header comment).
; ----------------------------------------------------------------
            proc    _env_data

            ; 32-aligned so no FCB can straddle a page boundary --
            ; file_open rejects one that does, and the kernel's own FCB
            ; field access relies on the property (see kernel/file.asm).
            ; Must stay the FIRST thing in the proc: .link .align moves
            ; the proc's BASE, which only aligns the label while nothing
            ; has been emitted yet. Link/02 now refuses it anywhere else.
            .link   .align 32

            ; The two FCBs are deliberately FIRST and adjacent: with the
            ; proc 32-aligned they land at offsets 0 and 32, so both are
            ; 32-aligned and neither can straddle a page. Do not insert
            ; anything above or between them.
env_in_fcb:         ds      FCB_LEN
env_out_fcb:        ds      FCB_LEN
env_line_buf:       ds      ENV_LINE_MAX
env_namebuf:        ds      ENV_LINE_MAX
env_in_iobuf:       ds      FCB_IOBUF_LEN
env_out_iobuf:      ds      FCB_IOBUF_LEN
env_name:           dw      0
env_value:          dw      0
env_overwrite:      db      0
env_found:          db      0
env_len:            dw      0
env_eq_byte:        db      '='
env_nl_byte:        db      10
env_file_path:      ds      16          ; "X:/cfg/env.dat",0 -- built
                                        ; fresh by _env_build_paths,
                                        ; not a fixed constant (see its
                                        ; own header comment for why)
env_tmp_path:       ds      16          ; "X:/cfg/env.tmp",0
env_cfg_path:       ds      8           ; "X:/cfg",0
env_file_suffix:    db      ":/cfg/env.dat",0
env_tmp_suffix:     db      ":/cfg/env.tmp",0
env_cfg_suffix:     db      ":/cfg",0
env_dat_name:       db      "env.dat",0

                public  env_line_buf
                public  env_namebuf
                public  env_in_fcb
                public  env_in_iobuf
                public  env_out_fcb
                public  env_out_iobuf
                public  env_name
                public  env_value
                public  env_overwrite
                public  env_found
                public  env_len
                public  env_eq_byte
                public  env_nl_byte
                public  env_file_path
                public  env_tmp_path
                public  env_cfg_path
                public  env_file_suffix
                public  env_tmp_suffix
                public  env_cfg_suffix
                public  env_dat_name

            endp
