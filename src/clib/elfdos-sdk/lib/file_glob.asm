;
; file_glob.asm - wildcard ("*"/"?") filename expansion library
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/file_glob.prg)
; and linked alongside a program that wants it, the same way this
; project's other lib/ modules already work. A calling program
; declares "extrn is_glob"/"extrn glob_init"/"extrn glob_next" and
; calls them like any other routine.
;
; Replaces the shell's own former glob-expansion-at-tokenize-time
; design (progs/shell.asm's now-deleted glob_expand/ge_* block),
; which rewrote argv[] before a command was ever handed to a program
; -- a design with a hard structural ceiling (ARGV_MAX_ARGS=16) that
; silently truncated a directory with more matches than that (a real
; bug found and fixed the same session this library was designed).
; The new design: the shell no longer expands wildcards at all -- a
; glob pattern passes through as ONE unexpanded argv token, and
; glob-AWARE programs (COPY/DEL/MOVE/ATTRIB/DIR/LS) detect and expand
; it themselves via this library, iterating matches one at a time
; instead of through the fixed-size argv table.
;
; Design (revised during plan review, 2026-07-27, at the user's own
; direct suggestion): NO dynamic memory of any kind. glob_init/
; glob_next operate entirely on a small, FIXED-SIZE context block
; (GLOB_CTX_LEN bytes, include/file_glob.inc) the caller declares as
; ordinary program data -- no himem reservation, no dependency on
; lib/heap_bump.asm.
;
; Resumable scan (2026-07-27, REPLACING the original re-scan-and-skip
; design the SAME DAY, after real hardware showed it noticeably slow
; for a directory with many matches -- e.g. "dir many*.txt" against a
; directory with dozens of matches, each glob_next call re-reading
; every already-seen entry from the start). The original design
; traded scan speed for total independence from the kernel's own
; directory-scan state, which lives in ONE global, kernel-resident
; position shared by every K_DIR_OPEN/K_DIR_READ caller -- there was
; no way for a userland library to "pause" that state across whatever
; the calling program does with a match in between glob_next calls
; (K_STAT, COPY, DEL, etc., all of which do their own K_DIR_OPEN/
; K_DIR_READ internally). Fixed at the ROOT by adding two small kernel
; primitives, K_DIR_SAVE_STATE/K_DIR_RESTORE_STATE (kernel/dir.asm),
; that snapshot/restore the kernel's own scan position (9 bytes) into
; caller-owned memory -- so glob_next now scans forward exactly once,
; snapshotting its position into the context block right before
; returning each match and restoring it at the start of the next call,
; with zero re-scanning regardless of how many matches have already
; been returned. See kernel/dir.asm's own dir_save_state/
; dir_restore_state headers for the full mechanism (in particular why
; dir_lfn/dir_lfn_chk/dir_lfn_ok/dir_last_off don't need to be part of
; the snapshot at all).
;
; Context block layout (GLOB_CTX_LEN=141 bytes, entirely private to
; this file -- callers only ever see the published SIZE,
; include/file_glob.inc, matching FCB_LEN/DIRENT_LEN's own "publish a
; size, not the struct" precedent):
;   offset 0-1:    parent_clust  (resolved directory cluster to scan)
;   offset 2:      has_state     (0 = no snapshot yet -- glob_next's
;                  first call for this pattern does a fresh
;                  K_DIR_OPEN; 1 = resume via K_DIR_RESTORE_STATE)
;   offset 3-11:   dir_state     (K_DIR_SAVE_STATE/K_DIR_RESTORE_STATE's
;                  own DIR_STATE_LEN=9-byte snapshot, opaque)
;   offset 12:     prefix_len    (0-63; how many bytes of name_copy,
;                  from its start, are the directory-prefix part of
;                  the original pattern, i.e. through the last '/')
;   offset 13-76:  name_copy     (the original name/pattern text,
;                  copied in by glob_init, bounds-checked/truncated at
;                  63 chars + NUL -- matches RUN_PATH_LEN's own
;                  already-established "reasonable single path/name"
;                  bound, include/kernel.inc)
;   offset 77-140: result_buf    (the most recent match's own full
;                  path -- "name_copy[0..prefix_len) + matched name",
;                  written fresh by each glob_next call, same 64-byte
;                  bound/truncation policy)
;   offset 141:    flags         (glob_init's D argument, 2026-09-28:
;                  GLOB_HIDDEN = also match hidden/system entries)
;
; Register-liveness discipline: K_DIR_OPEN/K_DIR_READ have no
; documented "Modifies" list in include/kernel_api.inc at all -- this
; project's own standing rule (CLAUDE.md gotchas #8/#10) is to trust
; NOTHING across a call with no proven/documented clobber footprint.
; K_DIR_SAVE_STATE/K_DIR_RESTORE_STATE are new calls this same file
; introduces the need for, so their real clobber footprint IS fully
; known (RF/RD for save; R7/R8/RD/RF for restore -- see kernel/dir.asm)
; -- glob_next still reloads the context base fresh from memory (gn_ctx)
; after every one of these calls rather than trusting a register to
; survive, matching this file's own established discipline throughout.
;

#include    include/opcodes.def
#include    include/bios.inc
#include    include/kernel_api.inc
#include    include/file_glob.inc

GLOB_CTX_PARENT:       equ     0
GLOB_CTX_HASSTATE:     equ     2
GLOB_CTX_DIRSTATE:     equ     3           ; DIR_STATE_LEN=9 bytes
GLOB_CTX_PREFIXLEN:    equ     12          ; 3 + DIR_STATE_LEN(9)
GLOB_CTX_NAME:         equ     13
GLOB_CTX_NAME_MAX:     equ     63          ; 63 chars + 1 NUL = 64 bytes
GLOB_CTX_RESULT:       equ     77          ; 13 + 64
GLOB_CTX_RESULT_MAX:   equ     63
GLOB_CTX_FLAGS:        equ     141         ; 77 + 64
GLOB_SKIP_ATTRS:       equ     ATTR_HIDDEN|$04 ; hidden or system

            extrn   glob_match
            extrn   gi_ctx
            extrn   gn_ctx
            extrn   gn_dirent
            extrn   gn_dot
            extrn   gn_dotdot

; ----------------------------------------------------------------
; is_glob: does the whole null-terminated string at RF contain '*' or
; '?' anywhere? Pure string scan, no kernel calls, no side effects.
; Deliberately whole-string (not just the final path component after
; the last '/', unlike the old shell-side ge_check_wildcard) --
; matches the simplest, most literal reading of "does this name
; represent a glob." A wildcard character earlier in a path than the
; final component now routes into glob_init (which will then likely
; fail to resolve that literal, doomed directory component and return
; DF=1) rather than being silently treated as an ordinary character
; the way the old shell-side check did -- a deliberate, small,
; documented behavior change, not an oversight.
; Args:    RF = pointer to a null-terminated string
; Returns: DF = 0 if a wildcard character is present, DF = 1 if not
; Modifies: RF (advances through the string), D
; ----------------------------------------------------------------
            proc    is_glob

ig_loop:
            ldn     rf
            lbz     ig_no
            xri     '*'
            lbz     ig_yes
            ldn     rf
            xri     '?'
            lbz     ig_yes
            inc     rf
            lbr     ig_loop

ig_yes:
            clc
            rtn

ig_no:
            stc
            rtn

            endp

; ----------------------------------------------------------------
; glob_init: prepare a context block to iterate every directory entry
; matching a wildcard pattern, via repeated glob_next calls. Does NOT
; scan the directory itself -- see this file's own header for why.
; Args:    RF = pattern (a name, possibly with a '/'-prefixed
;          directory part, whose final component contains '*'/'?' --
;          caller should have already confirmed this via is_glob,
;          though glob_init doesn't re-check it itself: a pattern
;          with no wildcard at all just means every glob_next call
;          will look for an exact-text match, harmlessly correct but
;          pointless)
;          RD = pointer to a caller-owned GLOB_CTX_LEN-byte context
;          block (need not be pre-zeroed)
;          D  = flags (2026-09-28): 0 skips hidden and system entries,
;          as MS-DOS wildcards did; GLOB_HIDDEN matches them too. Set
;          it with ldi AFTER loading RF/RD -- a mov clobbers D.
; Returns: DF = 0 on success, DF = 1 if the directory prefix doesn't
;          resolve (bad intermediate path component)
; Modifies: everything (R7-RD)
; ----------------------------------------------------------------
            proc    glob_init

            plo     r7                  ; R7.0 = flags (D, before any
                                        ; mov can clobber it)
            mov     r8, rd
            add16   r8, GLOB_CTX_FLAGS
            glo     r7
            str     r8                  ; context.flags = D on entry

            mov     r8, gi_ctx
            ghi     rd
            str     r8
            inc     r8
            glo     rd
            str     r8                  ; gi_ctx = context base

            ; --- copy the pattern into context.name_copy, bounds-
            ; checked/truncated at GLOB_CTX_NAME_MAX chars + NUL ---
            mov     r8, gi_ctx
            lda     r8
            phi     r9
            ldn     r8
            plo     r9
            add16   r9, GLOB_CTX_NAME   ; R9 = &context.name_copy
            ldi     0
            plo     rb                  ; RB.0 = copied-byte count
gi_copy_loop:
            glo     rb
            smi     GLOB_CTX_NAME_MAX
            lbdf    gi_copy_trunc       ; count >= max: force-truncate
            ldn     rf                  ; D = source byte
            lbz     gi_copy_nul         ; NUL: copy it, stop
            str     r9
            inc     r9
            inc     rf
            glo     rb
            adi     1
            plo     rb
            lbr     gi_copy_loop
gi_copy_nul:
            str     r9                  ; store the real terminator
            lbr     gi_copy_done
gi_copy_trunc:
            ldi     0
            str     r9                  ; force a terminator
gi_copy_done:

            ; --- find the last '/' within the COPY (name_copy),
            ; computing prefix_len -- mirrors the old shell-side
            ; ge_check_wildcard's own scan exactly ---
            mov     r8, gi_ctx
            lda     r8
            phi     r9
            ldn     r8
            plo     r9
            add16   r9, GLOB_CTX_NAME   ; R9 = &context.name_copy
                                        ; (start -- kept as the "zero
                                        ; prefix" baseline)
            mov     rb, r9              ; RB = scan cursor
            mov     rd, r9              ; RD = last-slash-plus-1
                                        ; position (defaults to the
                                        ; start: no '/' found yet)
gi_slash_scan:
            ldn     rb
            lbz     gi_slash_done
            xri     '/'
            lbnz    gi_slash_next
            inc     rb
            mov     rd, rb              ; RD = position right after
                                        ; this '/'
            lbr     gi_slash_scan
gi_slash_next:
            inc     rb
            lbr     gi_slash_scan
gi_slash_done:
            ; RD = pointer to the final component within name_copy;
            ; prefix_len = RD - R9 (both point within the same
            ; 64-byte field, so this always fits in one byte)
            mov     r8, rd
            sub16   r8, r9              ; R8 = prefix_len

            mov     r9, gi_ctx
            lda     r9
            phi     rb
            ldn     r9
            plo     rb                  ; RB = context base
            add16   rb, GLOB_CTX_PREFIXLEN
            glo     r8
            str     rb                  ; context.prefix_len = R8.0

            ; --- resolve the prefix directory: K_GETCURDIR if no
            ; prefix, else K_PATH_RESOLVE on the whole copied name
            ; (which never looks up the final component itself,
            ; matching every other caller's own use of it in this
            ; codebase) ---
            glo     r8
            lbnz    gi_resolve_path     ; prefix_len != 0

            call    K_GETCURDIR         ; RD = cur_dir cluster
            lbr     gi_have_clust

gi_resolve_path:
            mov     r9, gi_ctx
            lda     r9
            phi     rf
            ldn     r9
            plo     rf
            add16   rf, GLOB_CTX_NAME   ; RF = &context.name_copy
            call    K_PATH_RESOLVE      ; RD = parent cluster, DF=0/1
            lbdf    gi_fail

gi_have_clust:
            ; RD = resolved parent cluster
            mov     r9, gi_ctx
            lda     r9
            phi     rb
            ldn     r9
            plo     rb                  ; RB = context base
            add16   rb, GLOB_CTX_PARENT
            ghi     rd
            str     rb
            inc     rb
            glo     rd
            str     rb                  ; context.parent_clust = RD

            mov     r9, gi_ctx
            lda     r9
            phi     rb
            ldn     r9
            plo     rb
            add16   rb, GLOB_CTX_HASSTATE
            ldi     0
            str     rb                  ; context.has_state = 0 (no
                                        ; snapshot yet -- glob_next's
                                        ; first call does a fresh
                                        ; K_DIR_OPEN instead of
                                        ; resuming)

            clc
            rtn

gi_fail:
            stc
            rtn

            endp

; ----------------------------------------------------------------
; glob_get_dir: return the prefix directory cluster glob_init resolved
; for this context (2026-08-02) -- exposed for a caller (progs/dir.asm's
; own "Directory of <path>" header for a glob-matched listing) that
; needs to describe the directory a pattern matches within, without
; reaching into the context block's own otherwise-private layout
; directly (see this file's own header on GLOB_CTX_LEN: "never
; referenced by name outside it").
; Args:    RD = pointer to a context block already initialized by
;          glob_init
; Returns: RD = the resolved prefix directory cluster
; Modifies: RD, R8
; ----------------------------------------------------------------
            proc    glob_get_dir

            mov     r8, rd
            add16   r8, GLOB_CTX_PARENT
            lda     r8
            phi     rd
            ldn     r8
            plo     rd
            rtn

            endp

; ----------------------------------------------------------------
; glob_next: return the next directory entry (within the directory
; and pattern established by glob_init) matching the wildcard
; pattern, or DF=1 once exhausted.
;
; Resumable design (2026-07-27, see this file's own header for the
; full rationale): the FIRST call for a given context opens the
; directory fresh via K_DIR_OPEN (context.has_state == 0); every call
; that finds a match snapshots the kernel's own directory-scan
; position via K_DIR_SAVE_STATE before returning; the NEXT call
; resumes exactly there via K_DIR_RESTORE_STATE, so no directory entry
; is ever examined twice across a whole glob_next sequence. Safe even
; though the caller does other kernel directory operations on the
; previously-returned match in between calls (K_STAT, COPY, etc.),
; because K_DIR_RESTORE_STATE re-derives dir_buf's own content via a
; fresh disk read rather than trusting anything to have survived --
; see kernel/dir.asm's own dir_save_state/dir_restore_state headers.
;
; Args:    RD = pointer to a context block already initialized by
;          glob_init
; Returns: DF = 0 and RF = pointer to the match's full path (inside
;          the context block's own result_buf -- valid until the next
;          glob_next call on the SAME context, exactly like
;          K_PATH_RESOLVE's own "points into scratch" convention);
;          DF = 1 if no further entries match (this call found
;          nothing new before reaching the end of the directory, or
;          the resume itself failed -- treated the same as EOF,
;          matching this codebase's own standing convention of never
;          distinguishing a real I/O error from EOF at this level)
; Modifies: everything (R7-RD)
; ----------------------------------------------------------------
            proc    glob_next

            mov     r8, gn_ctx
            ghi     rd
            str     r8
            inc     r8
            glo     rd
            str     r8                  ; gn_ctx = context base

            ; --- reactivate the source drive's BPB/FAT-cache
            ; (real hardware bug, 2026-07-27): K_DIR_OPEN/
            ; K_DIR_RESTORE_STATE both operate against whichever
            ; drive's BPB happens to be ACTIVE right now -- neither
            ; one switches to any particular drive itself. A caller
            ; that touches a DIFFERENT drive while processing the
            ; previous match (e.g. COPY opening its source on this
            ; glob's own drive, then writing its destination on the
            ; CURRENT drive) leaves the wrong BPB active by the time
            ; this call runs: K_DIR_RESTORE_STATE's own raw sector
            ; re-read still succeeds (its saved LBA is absolute), but
            ; the FIRST time the resumed scan needs to cross a sector
            ; boundary, _dir_next_sector/fat_get consult the ACTIVE
            ; (wrong) drive's BPB/FAT fields and land on garbage that
            ; looks like end-of-directory -- exactly matching the
            ; observed symptom (a cross-drive "copy C:/cfg/*.txt ."
            ; silently stopping after only a few matches). Same class
            ; of bug XCOPY's own cross-drive fix (2026-07-25) already
            ; hit; same fix shape: call something that goes through
            ; path_resolve, purely for its _switch_drive side effect.
            ; K_PATH_RESOLVE (not K_STAT) is used here specifically
            ; because it never looks up the final path component --
            ; safe even though context.name_copy's own final component
            ; is a glob pattern, not a real filename, which K_STAT
            ; would fail to find.
            mov     r8, gn_ctx
            lda     r8
            phi     rf
            ldn     r8
            plo     rf                  ; RF = context base
            add16   rf, GLOB_CTX_NAME   ; RF = &context.name_copy (the
                                        ; ORIGINAL pattern text,
                                        ; including any drive prefix)
            call    K_PATH_RESOLVE      ; side effect only -- RD/RF/RC
                                        ; all discarded below
            lbdf    gn_exhausted        ; the directory prefix no
                                        ; longer resolves (e.g. a
                                        ; drive was removed mid-scan):
                                        ; treat as exhausted, matching
                                        ; every other failure mode here

            mov     r8, gn_ctx
            lda     r8
            phi     r9
            ldn     r8
            plo     r9                  ; R9 = context base
            mov     rf, r9
            add16   rf, GLOB_CTX_HASSTATE
            ldn     rf                  ; D = context.has_state
            lbnz    gn_resume

            ; --- first call for this pattern: fresh open ---
            mov     r8, gn_ctx
            lda     r8
            phi     rd
            ldn     r8
            plo     rd                  ; RD = context base
            add16   rd, GLOB_CTX_PARENT
            lda     rd
            phi     r9
            ldn     rd
            plo     r9                  ; R9 = context.parent_clust
            mov     rd, r9              ; RD = cluster to open
            call    K_DIR_OPEN
            lbr     gn_loop

gn_resume:
            ; --- resuming: restore the kernel's own scan position
            ; from our own last snapshot ---
            mov     r8, gn_ctx
            lda     r8
            phi     rf
            ldn     r8
            plo     rf                  ; RF = context base
            add16   rf, GLOB_CTX_DIRSTATE ; RF = &context.dir_state
            call    K_DIR_RESTORE_STATE ; DF = 0/1
            lbdf    gn_exhausted        ; resume failed: treat as EOF

gn_loop:
            mov     rf, gn_dirent
            call    K_DIR_READ
            lbdf    gn_exhausted        ; end of directory: no more
                                        ; matches

            ; --- skip "."/".." , else try to match it ---
            mov     rf, gn_dirent
            mov     rd, gn_dot
            call    f_strcmp
            lbz     gn_loop             ; skip "."

            mov     rf, gn_dirent
            mov     rd, gn_dotdot
            call    f_strcmp
            lbz     gn_loop             ; skip ".."

            ; hidden/system entry: skipped unless glob_init was given
            ; GLOB_HIDDEN (MS-DOS wildcards never matched them)
            mov     rf, gn_dirent
            add16   rf, DIRENT_ATTR
            ldn     rf                  ; D = attribute byte
            ani     GLOB_SKIP_ATTRS
            lbz     gn_visible
            mov     r8, gn_ctx
            lda     r8
            phi     rf
            ldn     r8
            plo     rf                  ; RF = context base
            add16   rf, GLOB_CTX_FLAGS
            ldn     rf                  ; D = flags
            ani     GLOB_HIDDEN
            lbz     gn_loop             ; hidden, not wanted: skip
gn_visible:

            mov     r8, gn_ctx
            lda     r8
            phi     r9
            ldn     r8
            plo     r9                  ; R9 = context base
            mov     rf, r9
            add16   rf, GLOB_CTX_PREFIXLEN
            ldn     rf                  ; D = prefix_len
            plo     rc
            ldi     0
            phi     rc                  ; RC = prefix_len (16-bit)
            mov     rf, r9
            add16   rf, GLOB_CTX_NAME
            add16   rf, rc              ; RF = &name_copy[prefix_len]
                                        ; = the pattern
            mov     rd, gn_dirent       ; RD = this entry's own name
            call    glob_match          ; DF=0 on match
            lbdf    gn_loop             ; no match: keep scanning

            ; --- match found: snapshot the CURRENT kernel scan
            ; position (K_DIR_READ has already advanced past this
            ; entry, so the snapshot correctly resumes AFTER it) ---
            mov     r8, gn_ctx
            lda     r8
            phi     rf
            ldn     r8
            plo     rf                  ; RF = context base
            add16   rf, GLOB_CTX_DIRSTATE ; RF = &context.dir_state
            call    K_DIR_SAVE_STATE

            mov     r8, gn_ctx
            lda     r8
            phi     rf
            ldn     r8
            plo     rf                  ; RF = context base
            add16   rf, GLOB_CTX_HASSTATE
            ldi     1
            str     rf                  ; context.has_state = 1

            mov     r8, gn_ctx
            lda     r8
            phi     rb
            ldn     r8
            plo     rb                  ; RB = context base

            ; --- build the result: name_copy[0..prefix_len) +
            ; matched name, into context.result_buf, bounds-checked/
            ; truncated at GLOB_CTX_RESULT_MAX chars + NUL ---
            mov     rf, rb
            add16   rf, GLOB_CTX_PREFIXLEN
            ldn     rf                  ; D = prefix_len
            plo     rc
            ldi     0
            phi     rc                  ; RC = prefix_len (16-bit,
                                        ; counts down to 0)

            mov     rf, rb
            add16   rf, GLOB_CTX_NAME   ; RF = &context.name_copy
                                        ; (prefix copy source)
            mov     r8, rb
            add16   r8, GLOB_CTX_RESULT ; R8 = &context.result_buf
                                        ; (write cursor)
            ldi     0
            plo     r9                  ; R9.0 = bytes written so far

gn_copy_prefix:
            glo     rc
            lbnz    gn_copy_prefix_have
            ghi     rc
            lbz     gn_copy_name
gn_copy_prefix_have:
            glo     r9
            smi     GLOB_CTX_RESULT_MAX
            lbdf    gn_result_trunc     ; already at the bound
            ldn     rf
            str     r8
            inc     rf
            inc     r8
            glo     r9
            adi     1
            plo     r9
            sub16   rc, 1
            lbr     gn_copy_prefix

gn_copy_name:
            mov     rf, gn_dirent       ; RF = matched entry's own name
gn_copy_name_loop:
            glo     r9
            smi     GLOB_CTX_RESULT_MAX
            lbdf    gn_result_trunc
            ldn     rf
            lbz     gn_copy_name_nul
            str     r8
            inc     rf
            inc     r8
            glo     r9
            adi     1
            plo     r9
            lbr     gn_copy_name_loop
gn_copy_name_nul:
            str     r8
            lbr     gn_result_done
gn_result_trunc:
            ldi     0
            str     r8
gn_result_done:

            mov     r8, gn_ctx
            lda     r8
            phi     rf
            ldn     r8
            plo     rf
            add16   rf, GLOB_CTX_RESULT ; RF = &context.result_buf
                                        ; (the return value)
            clc
            rtn

gn_exhausted:
            stc
            rtn

            endp

; ----------------------------------------------------------------
; glob_match: does the text at RD match the wildcard pattern at RF?
; '*' matches zero or more characters, '?' matches exactly one.
; Case-sensitive. Classic non-recursive backtracking matcher --
; relocated VERBATIM from progs/shell.asm's own already-hardware-
; confirmed version (independently verified against 35 hand-picked
; test cases in a Python simulation before it was first written --
; see this project's own scratch glob_match_sim.py -- not re-verified
; here since the logic is completely unchanged, only its home file).
; Args:    RF = pattern (null-terminated), RD = text (null-terminated)
; Returns: DF = 0 on match, DF = 1 on no match
; Modifies: RF, RD, RB (star_p -- 0 means unset; safe sentinel, no
;           real buffer in this system sits at address 0), R9
;           (star_t), R8 (scratch)
; ----------------------------------------------------------------
            proc    glob_match

            ldi     0
            phi     rb
            plo     rb                  ; RB = 0 (star_p unset)

gm_loop:
            ldn     rd                  ; D = *t
            lbnz    gm_have_char

gm_skip_stars:
            ldn     rf
            xri     '*'
            lbnz    gm_check_pat_end
            inc     rf
            lbr     gm_skip_stars
gm_check_pat_end:
            ldn     rf
            lbnz    gm_no               ; pattern has more: no match
            lbr     gm_yes              ; both exhausted: match

gm_have_char:
            plo     r8                  ; R8.0 = *t
            ldn     rf                  ; D = *p
            str     r2                  ; M(X) = *p (consumed by the
                                        ; very next instruction -- no
                                        ; register-register add16/
                                        ; sub16 runs between, gotcha
                                        ; #18-safe)
            glo     r8                  ; D = *t
            sm                          ; D = *t - *p (zero iff equal)
            lbz     gm_advance

            ldn     rf                  ; D = *p (reload)
            xri     '?'
            lbz     gm_advance

            ldn     rf
            xri     '*'
            lbz     gm_set_star

            lbr     gm_try_backtrack

gm_advance:
            inc     rf
            inc     rd
            lbr     gm_loop

gm_set_star:
            mov     rb, rf              ; star_p = p
            inc     rf                  ; p++ (consume the '*' itself)
            mov     r9, rd              ; star_t = t
            lbr     gm_loop

gm_try_backtrack:
            ghi     rb
            lbnz    gm_backtrack
            glo     rb
            lbz     gm_no               ; star_p == 0: never set

gm_backtrack:
            mov     rf, rb
            inc     rf                  ; p = star_p + 1
            inc     r9                  ; star_t++
            mov     rd, r9              ; t = star_t
            lbr     gm_loop

gm_yes:
            clc
            rtn

gm_no:
            stc
            rtn

            endp

; ----------------------------------------------------------------
; Data
; ----------------------------------------------------------------
            proc    _file_glob_data

gi_ctx:         dw      0
gn_ctx:         dw      0
gn_dirent:      ds      DIRENT_LEN
gn_dot:         db      ".",0
gn_dotdot:      db      "..",0

                public  gi_ctx
                public  gn_ctx
                public  gn_dirent
                public  gn_dot
                public  gn_dotdot

            endp
