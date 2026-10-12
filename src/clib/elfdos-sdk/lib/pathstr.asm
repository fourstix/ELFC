;
; pathstr.asm - cluster -> full path string, shared by PWD and DIR
;
; Extracted 2026-07-30 from progs/pwd.asm (unchanged algorithm, just
; wrapped as a callable library entry point) once progs/dir.asm also
; wanted the same "what's the full path to this cluster" logic, for
; its own "Directory of <path>" header (matching real MS-DOS's own
; DIR output) -- the same extract-once-two-callers-exist pattern this
; project already used for lib/vollabel.asm/lib/fmt32.asm.
;
; FAT stores no "my own name" or "path from root" anywhere -- a
; directory only knows its own cluster and its parent's cluster (via
; its '..' entry). To print a path, this walks UP from the given
; cluster to the root, and at each level finds "my own name" by
; searching the PARENT directory for the entry whose first cluster
; matches the cluster just come from (the only place that name is
; actually recorded -- the mirror image of K_PATH_RESOLVE, which goes
; name -> cluster; this goes cluster -> name).
;
; Path components are discovered leaf-to-root but need to print
; root-to-leaf, so the path is assembled backwards: cursor starts at
; the end of path_buf (on the null terminator) and each level's
; "/name" is prepended by moving cursor left, one level per loop.
;
; Deliberately assumes the CALLER's own cluster belongs to the
; CURRENTLY ACTIVE drive (the drive letter comes from K_GETCURDIR's
; own D return, matching PWD's own original scope) -- not a general
; cross-drive path-namer. Fine for PWD (always describes cur_dir on
; the active drive) and for DIR's own bare-listing case (same); a
; single-argument DIR naming a path on a DIFFERENT drive won't get
; this header at all, a known, accepted limitation for now.
;

#include    include/opcodes.def
#include    include/bios.inc
#include    include/kernel_api.inc

            extrn   drive_letter_of

PATH_BUF_LEN:   equ     128
PS_MAX_DEPTH:   equ     16

;------------------------------------------------------------------
; path_print_from_cluster: print "X:/some/path" (no trailing
; newline, no leading text) for the given directory cluster.
; Args:    RD = directory cluster (0 = root)
;          D  = drive-letter override: $FF means "derive it from
;          K_GETCURDIR/cur_drive" (the original, still-default
;          behavior -- what every caller used before this argument
;          existed); 0-3 means "use this drive index directly, matching
;          cur_drive's own C=0..F=3 convention" (2026-08-02, added
;          after real hardware use of progs/dir.asm's own path-
;          argument case: an explicit "X:/foo" argument switches the
;          ACTIVE BPB/FAT cache to X via K_PATH_RESOLVE, but never
;          touches cur_drive itself -- deriving the header's drive
;          letter from cur_drive would print the WRONG letter whenever
;          the two differ. The override only changes which letter gets
;          printed; the actual directory walk below still always
;          operates against whichever drive is CURRENTLY ACTIVE
;          (unaffected by this argument), so the override must be the
;          real, already-resolved target drive -- never a guess).
; Returns: DF = 0 on success (path printed); DF = 1 on error (nothing
;          printed -- directory structure error, or a cycle/too-deep
;          path)
; Modifies: everything
;------------------------------------------------------------------
            proc    path_print_from_cluster

            plo     r9                  ; stash D (the drive-letter
                                        ; override argument) FIRST --
                                        ; every mov below clobbers D
                                        ; (gotcha #4)

            ; save the caller's cluster argument next -- K_GETCURDIR
            ; further below also returns a cluster in RD (its own
            ; cur_dir, not necessarily the same one the caller passed
            ; us), which would silently overwrite it. A real bug
            ; caught during review, before this ever reached DIR: for
            ; PWD's own use (always describing cur_dir itself) the two
            ; values happen to be identical, which would have hidden
            ; this completely -- it only breaks for a cluster genuinely
            ; different from cur_dir, exactly DIR's own use case.
            mov     rf, clust
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf                  ; clust = caller's cluster

            glo     r9
            xri     $FF
            lbnz    ppfc_drive_ready    ; not $FF: R9.0 already holds
                                        ; the caller's explicit drive
                                        ; index -- use it directly,
                                        ; skip K_GETCURDIR entirely

            call    K_GETCURDIR         ; D = cur_drive (0-3) -- the
                                        ; RD it also returns is
                                        ; discarded; clust (above) is
                                        ; already safely in memory
            plo     r9                  ; R9.0 = cur_drive (stashed
                                        ; immediately -- the mov below
                                        ; clobbers D, gotcha #4)

ppfc_drive_ready:
            mov     rf, drive
            glo     r9
            str     rf                  ; drive = whichever we ended
                                        ; up with (override or cur_drive)

            mov     rf, clust
            lda     rf
            phi     rd
            ldn     rf
            plo     rd                  ; RD = clust (reloaded fresh,
                                        ; since K_GETCURDIR overwrote
                                        ; the register copy)

            ; already at root?
            ghi     rd
            lbnz    ps_walk
            glo     rd
            lbnz    ps_walk

            call    print_drive_letter
            call    K_INMSG
            db      ":/",0
            clc
            rtn

ps_walk:
            mov     rf, path_buf
            add16   rf, PATH_BUF_LEN - 1
            ldi     0
            str     rf
            mov     rb, cursor
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; cursor = pointer to the null

            mov     rf, depth_left
            ldi     PS_MAX_DEPTH
            str     rf

ps_loop:
            mov     rf, depth_left
            ldn     rf
            lbz     ps_err
            smi     1
            str     rf                  ; depth_left -= 1

            ; --- open clust, find its '..' entry -> parent cluster ---
            mov     rf, clust
            lda     rf
            phi     rd
            ldn     rf
            plo     rd                  ; RD = clust
            call    K_DIR_OPEN

ps_find_dotdot:
            mov     rf, ps_dir_result
            call    K_DIR_READ
            lbdf    ps_err              ; ran out of entries: shouldn't
                                        ; happen for a real subdirectory

            mov     rf, ps_dir_result   ; RF = entry name
            mov     rd, dotdot          ; RD = ".."
            call    f_strcmp
            lbnz    ps_find_dotdot

            ; parent = this entry's DIRENT_CLUST
            mov     rf, ps_dir_result
            add16   rf, DIRENT_CLUST
            lda     rf                  ; D = cluster high byte
            phi     rd
            ldn     rf                  ; D = cluster low byte
            plo     rd
            mov     rf, parent
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf                  ; parent = RD

            ; --- open parent, find the entry whose cluster == clust ---
            call    K_DIR_OPEN          ; RD is still = parent

ps_find_self:
            mov     rf, ps_dir_result
            call    K_DIR_READ
            lbdf    ps_err              ; ran out: shouldn't happen --
                                        ; clust must appear once in
                                        ; its own parent's listing

            mov     rf, ps_dir_result
            add16   rf, DIRENT_CLUST
            lda     rf                  ; D = entry cluster high byte,
                                        ; RF -> entry cluster low byte
            str     r2
            mov     rb, clust
            ldn     rb                  ; D = clust high byte
            sm                          ; D = clust.hi - entry.hi
            lbnz    ps_find_self        ; mismatch: keep looking

            ldn     rf                  ; D = entry cluster low byte
            str     r2
            inc     rb                  ; RB -> clust low byte
            ldn     rb                  ; D = clust low byte
            sm                          ; D = clust.lo - entry.lo
            lbnz    ps_find_self        ; mismatch: keep looking

            ; match: ps_dir_result's name is this level's path
            ; component

            ; --- prepend "/" + name to path_buf ---
            mov     ra, ps_dir_result   ; RA = name start
            mov     rf, ra
ps_namelen:
            ldn     rf
            lbz     ps_namelen_done
            inc     rf
            lbr     ps_namelen
ps_namelen_done:
            ; RF = pointer to the name's null terminator
            mov     rc, rf
            sub16   rc, ra              ; RC = namelen

            mov     rf, cursor
            lda     rf
            phi     rd
            ldn     rf
            plo     rd                  ; RD = cursor
            sub16   rd, rc              ; RD = cursor - namelen (name dest)

            mov     rb, rd              ; RB = copy destination
ps_copy_name:
            glo     rc
            lbz     ps_copy_done
            lda     ra                  ; D = source char, RA++
            str     rb
            inc     rb
            dec     rc
            lbr     ps_copy_name
ps_copy_done:
            dec     rd                  ; make room for the separator
            ldi     '/'
            str     rd

            mov     rf, cursor
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf                  ; cursor = RD (new position)

            ; --- move up one level: clust = parent ---
            mov     rf, parent
            lda     rf
            phi     rd
            ldn     rf
            plo     rd
            mov     rf, clust
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf                  ; clust = parent

            ; if we just reached root, we're done -- otherwise walk
            ; up another level (RD is still = parent from just above)
            ghi     rd
            lbnz    ps_loop
            glo     rd
            lbnz    ps_loop

            call    print_drive_letter
            call    K_INMSG
            db      ":",0

            mov     rf, cursor
            lda     rf
            phi     rd
            ldn     rf
            plo     rd
            mov     rf, rd              ; RF = cursor (start of the path)
            call    K_MSG
            clc
            rtn

ps_err:
            stc
            rtn

;------------------------------------------------------------------
; print_drive_letter: print drive's letter (a single character) via a
; bare, one-shot K_TTY call -- same proven-safe pattern progs/pwd.asm's
; own original copy of this routine already used (gotcha #14 -- a
; single call, unlike a large buffer loop, is safe here).
; Args:    none (reads drive)
; Returns: nothing
; Modifies: D, R8, R9, RF -- drive_letter_of's clobber list. Both call
;           sites follow with K_INMSG and reload from memory, so none of
;           it is live across them.
;------------------------------------------------------------------
print_drive_letter:
            mov     rf, drive
            ldn     rf
            call    drive_letter_of     ; D = slot in, letter out
            call    K_TTY
            rtn

clust:      dw      0
parent:     dw      0
cursor:     dw      0
depth_left: db      0
drive:      db      0                   ; K_GETCURDIR's D return
                                        ; (cur_drive), stashed at entry
dotdot:     db      "..",0
ps_dir_result: ds   DIRENT_LEN          ; 135-byte result buffer for K_DIR_READ
path_buf:   ds      PATH_BUF_LEN

            endp
