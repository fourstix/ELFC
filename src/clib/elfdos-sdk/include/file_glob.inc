;
; file_glob.inc - shared constant for lib/file_glob.asm's callers
;
; "Publish a size, not the struct" -- same precedent as FCB_LEN/
; DIRENT_LEN (kernel_api.inc): a calling program declares its own
; `ds GLOB_CTX_LEN` context block and passes a pointer to it into
; glob_init/glob_next; the block's own internal layout is entirely
; private to lib/file_glob.asm, never referenced by name outside it.
;

GLOB_CTX_LEN:   equ     142         ; +1 flags byte, 2026-09-28         ; widened 2026-07-27 (+8 bytes)
                                    ; when glob_next switched from
                                    ; re-scan-and-skip to a resumable
                                    ; K_DIR_SAVE_STATE/RESTORE_STATE-
                                    ; based design -- see
                                    ; lib/file_glob.asm's own header

GLOB_HIDDEN:    equ     1           ; glob_init flag (D): also match
                                    ; hidden and system entries -- by
                                    ; default they are skipped, as
                                    ; MS-DOS wildcards did (2026-09-28)
