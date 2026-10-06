;
; move.asm - general-purpose "move" primitive: rename a file or
; directory in place when possible, falling back to nothing more than
; telling the caller a data copy is required.
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/move.prg) and
; linked alongside a program that wants it, the same way
; lib/env.asm/lib/heap_bump.asm/lib/heap_malloc.asm already do. A
; calling program declares "extrn move_rename" and calls it like any
; other routine.
;
; Design (2026-07-23, revised same day after a real hardware bug hunt
; found the first version's approach was needlessly complicated): the
; ONLY thing that decides whether a fast, data-free rename is even
; possible is K_FILE_RENAME's own existing contract -- its new-name
; argument must be a bare name (no '/' anywhere) applying within the
; OLD path's own parent directory. So rather than independently
; resolving both paths via K_PATH_RESOLVE and comparing parent
; clusters (the first version's approach), this routine just checks
; the DESTINATION STRING ITSELF: does it contain a '/' or look like
; an "X:" drive prefix? If either, a fast rename can never apply
; (K_FILE_RENAME would reject it outright, and even if it didn't, the
; caller's own intent was clearly a different location) -- report
; "needs copy" WITHOUT ever calling into the kernel. Otherwise, call
; K_FILE_RENAME directly with the caller's OWN strings, completely
; unmodified -- no K_PATH_RESOLVE call happens anywhere in this
; routine, so there's no kernel-scratch-pointer lifetime to worry
; about at all, and no kernel changes were needed to make this safe
; (REN's own already-hardware-proven code path, untouched).
;
; The one real tradeoff, accepted deliberately: "MOVE /cfg/foo.txt
; /cfg/bar.txt" (full paths on both sides, but genuinely the same
; directory) takes the copy+delete fallback instead of the instant
; rename, since this routine has no way to know the two paths resolve
; to the same place without doing the very resolution being avoided.
; In practice, real usage types a bare name for a same-directory
; rename and a path/directory for an actual move, so this covers the
; overwhelming common case for free.
;
; Calling convention (register-passed, RF/RD for path args -- matching
; K_FILE_RENAME/REN's own convention):
;   move_rename: Args RF=pointer to null-terminated SOURCE path (any
;                valid path, resolved however the caller likes), RD=
;                pointer to null-terminated DESTINATION (checked as
;                described above -- if it's a bare name, passed
;                straight through to K_FILE_RENAME unmodified).
;                Returns:
;                  DF=0: renamed in place (no data was copied) --
;                        nothing left for the caller to do.
;                  DF=1, D=0: destination isn't a bare name (contains
;                        '/' or looks like a drive prefix) -- no
;                        rename was attempted. Caller should fall
;                        back to its own copy-then-delete.
;                  DF=1, D=1: destination WAS a bare name, but
;                        K_FILE_RENAME itself failed (name already
;                        exists, source not found, "."/".." names, or
;                        an invalid intermediate path component in the
;                        source) -- a real failure; no fallback should
;                        be attempted.
; Modifies: R7, R8 (and D)
;

#include    include/opcodes.def
#include    include/kernel_api.inc

; ----------------------------------------------------------------
; move_rename: see the file header above for the full contract.
; ----------------------------------------------------------------
            proc    move_rename

            ; --- does the destination contain a '/' anywhere? ---
            mov     r8, rd              ; R8 = scan pointer (RD itself
                                        ; is left untouched, so it's
                                        ; still ready to pass straight
                                        ; to K_FILE_RENAME below)
mrn_scan:
            ldn     r8
            lbz     mrn_no_sep          ; reached the null: no '/'
                                        ; found
            xri     '/'
            lbz     mrn_needs_copy
            inc     r8
            lbr     mrn_scan

mrn_no_sep:
            ; --- does it look like an "X:" drive prefix? (guard the
            ; empty-string case first, so the second-character peek
            ; below never reads past a 0-length string) ---
            mov     r8, rd
            ldn     r8
            lbz     mrn_try             ; empty destination -- let
                                        ; K_FILE_RENAME's own
                                        ; validation reject it
            inc     r8
            ldn     r8
            xri     ':'
            lbz     mrn_needs_copy

mrn_try:
            ; RF/RD are exactly as the caller passed them -- neither
            ; was ever touched, so this is a direct, unmodified
            ; K_FILE_RENAME call using the caller's own stable strings
            call    K_FILE_RENAME       ; DF=0/1
            lbdf    mrn_real_fail

            clc
            rtn

mrn_needs_copy:
            stc
            ldi     0
            rtn

mrn_real_fail:
            stc
            ldi     1
            rtn

            endp
