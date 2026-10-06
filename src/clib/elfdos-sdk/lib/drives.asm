;
; drives.asm - drive letter <-> slot conversion
;
; Since 2026-09-09 a drive's letter is no longer its slot index plus
; 'C'. Any of the DRIVE_COUNT slots may carry any letter A-Z, so the
; two directions need a real lookup, and every program that prints a
; drive letter or parses one has to go through here.
;
; The table itself is drive_letter[DRIVE_COUNT] in kernel memory, one
; byte per slot, 0 meaning the slot is free. It is reached through
; DRIVE_DATA_PTR + DRIVE_LETTER_OFF, the same published-offset
; mechanism progs/mount.asm already uses for drive_present and
; drive_bpb_table -- see include/kernel_api.inc.
;
; No kernel call is involved: the kernel's own copy of this logic lives
; in path_resolve (kernel/path.asm), which is the only kernel code that
; converts a letter, and a jump-table slot for a single caller was not
; worth the three bytes. The two implementations are small and
; independent; if the table's shape ever changes, both need editing.
;
; Neither routine calls anything, so their clobber lists are exactly
; what they touch.
;

#include    include/opcodes.def
#include    include/bios.inc
#include    include/kernel_api.inc

;------------------------------------------------------------------
; drive_letter_of: which letter a slot answers to.
;
; Args:    D = slot (0..DRIVE_COUNT-1)
; Returns: DF = 0 and D = the slot's letter, or 0 if the slot is free;
;          DF = 1 and D = 0 if the slot number is out of range.
; Modifies: D, R8, R9, RF
;------------------------------------------------------------------
            proc    drive_letter_of

            plo     r9                  ; R9.0 = slot (plo leaves D alone)
            smi     DRIVE_COUNT
            lbdf    dlo_bad             ; slot >= DRIVE_COUNT

            mov     rf, DRIVE_DATA_PTR
            lda     rf
            phi     r8
            ldn     rf
            plo     r8                  ; R8 = drive_present's address
            mov     rf, r8
            add16   rf, DRIVE_LETTER_OFF ; RF = &drive_letter[0]

            glo     r9
            plo     r8
            ldi     0
            phi     r8                  ; R8 = slot, zero-extended
            add16   rf, r8              ; RF = &drive_letter[slot]

            ldn     rf
            clc
            rtn

dlo_bad:
            ldi     0
            stc
            rtn

            endp

;------------------------------------------------------------------
; drive_index_of: which slot, if any, answers to a letter.
;
; Args:    D = letter. The caller folds case first (ani $DF is safe for
;          the whole A-Z range: the only bytes aliasing into $41-$5A
;          under that mask are $41-$5A and $61-$7A themselves).
; Returns: DF = 0 and D = slot if some mounted drive carries that
;          letter; DF = 1 otherwise (D undefined).
; Modifies: D, R8, R9, RF
;------------------------------------------------------------------
            proc    drive_index_of

            plo     r9                  ; R9.0 = letter
            lbz     dio_no              ; 0 is the free-slot marker and
                                        ; must never be matched against
                                        ; the table, or every free slot
                                        ; would "match"

            mov     rf, DRIVE_DATA_PTR
            lda     rf
            phi     r8
            ldn     rf
            plo     r8
            mov     rf, r8
            add16   rf, DRIVE_LETTER_OFF ; RF = &drive_letter[0]

            ldi     0
            phi     r9                  ; R9.1 = slot under test

dio_loop:
            lda     rf                  ; D = drive_letter[slot], RF++
            str     r2
            glo     r9
            sm                          ; D = letter - drive_letter[slot]
            lbz     dio_found

            ghi     r9
            adi     1
            phi     r9
            smi     DRIVE_COUNT
            lbnf    dio_loop            ; DF=0: still < DRIVE_COUNT

dio_no:
            stc
            rtn

dio_found:
            ghi     r9
            clc
            rtn

            endp
