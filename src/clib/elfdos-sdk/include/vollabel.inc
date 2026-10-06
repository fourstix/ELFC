;
; vollabel.inc - shared constants for lib/vollabel.asm's callers
;
; vol_label_set/vol_label_delete return a reason code in D whenever
; DF=1, so a calling program can print a specific message instead of
; a generic failure -- matches this project's own "library owns the
; mechanism, caller owns the message" convention (see
; kernel_api.inc's own K_* error contracts).
;

VOL_ERR_INVALID: equ    0   ; vol_label_set only -- text was empty,
                            ; over 8 characters, or contained a
                            ; character outside A-Z/0-9/'_'/'-'
VOL_ERR_FULL:     equ    1  ; vol_label_set only -- no existing label
                            ; and the root directory has no room for
                            ; a new entry
VOL_ERR_IO:       equ    2  ; either call -- an I/O error reading or
                            ; writing the root directory
VOL_ERR_NONE:     equ    3  ; vol_label_delete only -- there was no
                            ; label to remove
