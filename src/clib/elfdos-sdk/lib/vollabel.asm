;
; vollabel.asm - FAT16 volume label read/create-or-update/remove
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/vollabel.prg) and
; linked alongside a program that wants it, the same way this
; project's other lib/ modules already work. A calling program
; declares "extrn vol_label_get"/"extrn vol_label_set"/"extrn
; vol_label_delete" and calls them like any other routine.
;
; Extracted from progs/label.asm (2026-07-30) once a second caller
; showed up (progs/dir.asm, printing a "Volume in drive C is MYDISK"
; header the way MS-DOS's own DIR always has) -- matches this
; project's own established precedent for lib/heap_bump.asm, lib/
; env.asm, lib/file_glob.asm: pull shared logic out once more than one
; program needs it, rather than duplicating it.
;
; A volume label is a single, special directory entry (ATTR_VOLID)
; that only ever lives in the ROOT directory -- K_DIR_READ silently
; skips it (see its own doc comment), so there's no kernel primitive
; that can find one via an ordinary scan. Rather than dedicating
; permanent kernel-resident code to a feature this rarely used (an
; earlier kernel-side draft of this cost enough bytes to push the
; kernel's own boot-sector headroom negative -- see project history),
; this library does the whole thing itself: K_SECREAD/K_SECWRITE (raw
; 512-byte sector I/O by LBA, already exposed for progs/sys.asm) plus
; BPB_DATA_PTR (the ACTIVE drive's own root-directory LBA/entry-count,
; already exposed too -- neither primitive needed to be added for
; this). The root directory in FAT16 is a fixed, contiguous range of
; sectors with no cluster chain to follow, which is what makes a
; from-scratch scan like this reasonable to do entirely in userland --
; a subdirectory would need real cluster-chain-following machinery
; this library deliberately doesn't reimplement.
;
; Deliberately operates on whichever drive is CURRENTLY ACTIVE --
; exactly like BPB_DATA_PTR/K_SECREAD/K_SECWRITE themselves already
; do -- with no drive argument or drive-switching logic of its own.
; Which drive should be active is a caller concern: progs/label.asm
; has an explicit "drive:" argument to honor and does its own
; activation before calling in here (K_GETCURDIR for the current
; drive, or a K_STAT("X:/")-for-its-side-effect trick for an explicit
; one -- see that file's own header for why, and why not K_SETDRIVE);
; progs/dir.asm needs no activation of its own at all, since its own
; very first instruction (K_GETCURDIR) already leaves the right
; drive's BPB active as a side effect before it ever calls in here.
;
; Settable label text is restricted to 1-11 characters, letters/
; digits/'_'/'-' -- the full length of a real DOS volume label,
; just without its "any character at all" allowance. This routine
; builds the raw 11-byte on-disk field itself (see vol_label_set's own
; body below), with no _gen_short_name-style 8-char-base/3-char-
; extension splitting to worry about -- unlike an ordinary 8.3
; filename, a volume label has no dot/extension concept at all, so
; there was never a real reason to stay narrower than 11 once this
; library stopped reusing that kernel routine (an earlier, since-
; abandoned draft of this feature DID reuse it, which is why an even
; earlier version of this file capped the length at 8 -- caught and
; fixed 2026-07-30 after the user asked directly "isn't the limit 11
; characters?"). A lowercase letter is upper-cased automatically,
; matching real MS-DOS's own LABEL behavior (also fixed the same day
; -- an earlier draft of this library rejected lowercase outright
; instead); any OTHER character outside that set is rejected via
; VOL_ERR_INVALID rather than silently mangled into something else.
;

#include    include/opcodes.def
#include    include/kernel_api.inc
#include    include/vollabel.inc

; Raw FAT16 directory-entry field offsets/attribute bits -- not
; exposed via kernel_api.inc (those are kernel-internal, used by code
; operating on the kernel's own dir_buf), but this is genuinely just
; the FAT specification's own fixed 32-byte entry format, reasonable
; for code doing raw sector manipulation to know directly. Values
; match kernel.inc's own DE_ATTR/ATTR_LFN/ATTR_VOLID exactly.
DE_ATTR:        equ     11
ATTR_LFN:       equ     $0F
ATTR_VOLID:     equ     $08

VOL_FOUND_NONE:      equ 0   ; no label, no insertion point either
                              ; (root directory completely full)
VOL_FOUND_EXISTING:  equ 1   ; an existing label entry was found
VOL_FOUND_INSERTPT:  equ 2   ; no label, but a '$00' terminator was
                              ; found -- safe to insert a new entry there

            extrn   vol_found
            extrn   vol_found_off
            extrn   vol_cur_lba
            extrn   vol_unit
            extrn   vol_sector_buf
            extrn   _vol_scan
            extrn   _vol_classify_char
            extrn   _vol_sync_bootsector

;------------------------------------------------------------------
; vol_label_get: read the volume label, if any, on the active drive.
; Args:    RD = destination buffer, at least 12 bytes
; Returns: DF = 0 -- buffer holds the label, trailing spaces trimmed,
;          null-terminated (1-11 real characters).
;          DF = 1 -- no volume label exists; buffer untouched.
; Modifies: everything
;------------------------------------------------------------------
            proc    vol_label_get

            mov     rb, vlg_dest
            ghi     rd
            str     rb
            inc     rb
            glo     rd
            str     rb                  ; vlg_dest = caller's dest buffer

            call    _vol_scan

            mov     rf, vol_found
            ldn     rf
            xri     VOL_FOUND_EXISTING
            lbnz    vlg_notfound

            mov     rf, vol_found_off
            lda     rf
            phi     rb
            ldn     rf
            plo     rb

            mov     rf, vol_sector_buf
            add16   rf, rb              ; RF -> the entry's own 11-byte
                                        ; name field
            mov     r8, rf              ; R8 = field base (kept)

            ; trim trailing spaces: scan backward from index 10
            add16   rf, 10
            ldi     10
            plo     r9
vlg_trim:
            ldn     rf
            xri     ' '
            lbnz    vlg_trim_found
            glo     r9
            lbz     vlg_trim_empty
            dec     rf
            glo     r9
            smi     1
            plo     r9
            lbr     vlg_trim

vlg_trim_found:
            glo     r9
            adi     1
            plo     rc                  ; RC.0 = trimmed length
            lbr     vlg_copy

vlg_trim_empty:
            ldi     0
            plo     rc

vlg_copy:
            mov     rf, r8
            mov     rb, vlg_dest
            lda     rb
            phi     rd
            ldn     rb
            plo     rd                  ; RD = caller's dest buffer
vlg_copy_loop:
            glo     rc
            lbz     vlg_copy_done
            lda     rf
            str     rd
            inc     rd
            glo     rc
            smi     1
            plo     rc
            lbr     vlg_copy_loop
vlg_copy_done:
            ldi     0
            str     rd                  ; null-terminate

            clc                         ; DF = 0, success
            rtn

vlg_notfound:
            stc                         ; DF = 1, no label
            rtn

vlg_dest:   dw      0

            endp

;------------------------------------------------------------------
; vol_label_set: create or update the volume label on the active
; drive.
; Args:    RD = pointer to a null-terminated label string, 1-11
;          characters, restricted to letters/digits/'_'/'-' (lowercase
;          letters are upper-cased automatically -- see this file's
;          own header for why)
; Returns: DF = 0 on success.
;          DF = 1 on failure, D = VOL_ERR_INVALID/VOL_ERR_FULL/
;          VOL_ERR_IO (include/vollabel.inc).
; Modifies: everything
;------------------------------------------------------------------
            proc    vol_label_set

            mov     rb, vls_text
            ghi     rd
            str     rb
            inc     rb
            glo     rd
            str     rb                  ; vls_text = caller's label text

            ; --- validate first, before any I/O: length 1-11, every
            ; character already safe or safely upper-casable. 11, not
            ; 8 -- there is no dot/extension concept for a volume
            ; label at all (unlike an ordinary 8.3 filename), and this
            ; routine builds the raw 11-byte field itself below with
            ; no _gen_short_name-style splitting to worry about, so
            ; the real DOS-native limit applies with no need to stay
            ; narrower (an earlier draft capped this at 8 as a holdover
            ; from a since-abandoned design that DID reuse
            ; _gen_short_name's own 8-char-base splitting -- caught by
            ; the user directly asking "isn't the limit 11 characters?"
            ; after the final, splitting-free design had already made
            ; that caution moot) ---
            mov     rf, rd
            ldi     0
            plo     r9                  ; R9.0 = length so far
vls_validate:
            ldn     rf
            lbz     vls_length_check
            call    _vol_classify_char  ; DF = 0 if allowed (A-Z/a-z/
                                        ; 0-9/_/-) -- D's own returned
                                        ; (possibly uppercased) value
                                        ; is unused here, only DF matters
            lbdf    vls_bad
            inc     rf
            glo     r9
            adi     1
            plo     r9
            smi     12
            lbdf    vls_bad             ; length just exceeded 11
            lbr     vls_validate

vls_length_check:
            glo     r9
            lbz     vls_bad             ; length 0: reject

            ; build the padded 11-byte name into vls_new_name --
            ; re-running each character through _vol_classify_char
            ; (not just copying it raw) so a lowercase letter lands
            ; uppercased, matching real MS-DOS's own LABEL behavior
            ; (2026-07-30) rather than this project's earlier, stricter
            ; "reject anything not already uppercase" draft. Every
            ; character here is already known to return DF=0 -- the
            ; validate pass above already confirmed it -- so DF isn't
            ; re-checked, only D (the transformed character) is used.
            mov     rf, rd              ; RF = source text again (start)
            mov     r8, vls_new_name
            ldi     11
            plo     rc
vls_build:
            glo     rc
            lbz     vls_built
            ldn     rf
            lbz     vls_pad
            ldn     rf                  ; D = char (peek -- _vol_
                                        ; classify_char needs D as its
                                        ; own input, not a pointer)
            call    _vol_classify_char  ; D = transformed (uppercased
                                        ; if needed) character
            str     r8
            inc     r8
            inc     rf
            glo     rc
            smi     1
            plo     rc
            lbr     vls_build
vls_pad:
            ldi     ' '
            str     r8
            inc     r8
            glo     rc
            smi     1
            plo     rc
            lbz     vls_built
            lbr     vls_pad
vls_built:

            call    _vol_scan

            mov     rf, vol_found
            ldn     rf
            xri     VOL_FOUND_EXISTING
            lbz     vls_update

            mov     rf, vol_found
            ldn     rf
            xri     VOL_FOUND_INSERTPT
            lbz     vls_insert

            ldi     VOL_ERR_FULL
            stc
            rtn

vls_update:
            mov     rf, vol_found_off
            lda     rf
            phi     rb
            ldn     rf
            plo     rb
            mov     rf, vol_sector_buf
            add16   rf, rb              ; RF -> existing entry's own
                                        ; name field

            mov     rd, vls_new_name
            ldi     11
            plo     rc
vls_update_copy:
            glo     rc
            lbz     vls_write_back
            lda     rd
            str     rf
            inc     rf
            glo     rc
            smi     1
            plo     rc
            lbr     vls_update_copy

vls_insert:
            mov     rf, vol_found_off
            lda     rf
            phi     rb
            ldn     rf
            plo     rb
            mov     rf, vol_sector_buf
            add16   rf, rb              ; RF -> insertion point -- 32
                                        ; bytes here are already zero
                                        ; (past the old terminator,
                                        ; never written before)
            mov     r8, rf              ; R8 = entry base (kept)

            mov     rd, vls_new_name
            ldi     11
            plo     rc
vls_insert_name:
            glo     rc
            lbz     vls_insert_attr
            lda     rd
            str     rf
            inc     rf
            glo     rc
            smi     1
            plo     rc
            lbr     vls_insert_name

vls_insert_attr:
            mov     rf, r8
            add16   rf, DE_ATTR
            ldi     ATTR_VOLID
            str     rf
                                        ; rest of the 32-byte entry
                                        ; left zero, already valid for
                                        ; a volume-label entry

vls_write_back:
            mov     rf, vol_cur_lba
            lda     rf
            plo     r8
            lda     rf
            phi     r7
            ldn     rf
            plo     r7
            mov     rf, vol_unit
            ldn     rf
            phi     r8                  ; R8.1 = this drive's block-device unit

            mov     rf, vol_sector_buf
            call    K_SECWRITE
            lbnf    vls_ok

            ldi     VOL_ERR_IO
            stc
            rtn

vls_ok:
            ; keep the boot sector's own separate BS_VolLab copy in
            ; sync (2026-07-30) -- FAT16 stores the volume label in
            ; TWO places, and fsck.vfat (confirmed by the user, real
            ; hardware) treats a mismatch as corruption and "fixes" it
            ; by overwriting the boot-sector copy with whatever the
            ; root directory says -- this routine's own write above
            ; only ever touched the root-directory copy until now
            mov     rf, vls_new_name
            call    _vol_sync_bootsector
            lbdf    vls_bootsec_err

            clc
            rtn

vls_bootsec_err:
            ldi     VOL_ERR_IO
            stc
            rtn

vls_bad:
            ldi     VOL_ERR_INVALID
            stc
            rtn

vls_text:       dw      0
vls_new_name:   ds      11

            endp

;------------------------------------------------------------------
; vol_label_delete: remove the volume label on the active drive.
; Args:    none
; Returns: DF = 0 on success.
;          DF = 1, D = VOL_ERR_NONE (no label to remove) or VOL_ERR_IO.
; Modifies: everything
;------------------------------------------------------------------
            proc    vol_label_delete

            call    _vol_scan

            mov     rf, vol_found
            ldn     rf
            xri     VOL_FOUND_EXISTING
            lbz     vld_delete

            ldi     VOL_ERR_NONE
            stc
            rtn

vld_delete:
            mov     rf, vol_found_off
            lda     rf
            phi     rb
            ldn     rf
            plo     rb
            mov     rf, vol_sector_buf
            add16   rf, rb              ; RF -> the entry's own first byte
            ldi     $E5
            str     rf

            mov     rf, vol_cur_lba
            lda     rf
            plo     r8
            lda     rf
            phi     r7
            ldn     rf
            plo     r7
            mov     rf, vol_unit
            ldn     rf
            phi     r8                  ; R8.1 = this drive's block-device unit

            mov     rf, vol_sector_buf
            call    K_SECWRITE
            lbnf    vld_ok

            ldi     VOL_ERR_IO
            stc
            rtn

vld_ok:
            ; blank the boot sector's own separate BS_VolLab copy too
            ; -- see vol_label_set's own vls_ok for why
            mov     rf, vld_blank_name
            call    _vol_sync_bootsector
            lbdf    vld_bootsec_err

            clc
            rtn

vld_bootsec_err:
            ldi     VOL_ERR_IO
            stc
            rtn

vld_blank_name: db   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '

            endp

;------------------------------------------------------------------
; _vol_scan: locate the volume label entry (or a safe insertion
; point, or neither) on the active drive's root directory. Shared by
; all three public entry points above.
;
; Reads the root directory's own LBA/entry-count via BPB_DATA_PTR
; (the active drive's own, already-boot-populated BPB data), then
; reads one 512-byte root sector at a time (K_SECREAD), examining
; every 32-byte entry for either ATTR_VOLID or the '$00' end-of-
; directory terminator. Stops immediately on either -- vol_sector_buf
; is left holding exactly the sector the match (or insertion point)
; lives in, ready for vol_label_set/vol_label_delete to patch in
; place and write straight back to vol_cur_lba (also left describing
; that same sector).
;
; Args:    none
; Returns: nothing in registers -- vol_found/vol_found_off/
;          vol_cur_lba/vol_sector_buf all populated (see this proc's
;          own header comment above for what each result state means)
; Modifies: everything
;------------------------------------------------------------------
            proc    _vol_scan

            mov     rf, BPB_DATA_PTR
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = BPB block's real address

            ; vol_unit: the drive's block-device unit, for every raw
            ; sector read/write below. BUG FIX (2026-09-11): this library
            ; used to hardcode R8.1 = 0 (the boot device), so LABEL on a
            ; drive MOUNTed from another unit wrote the boot device --
            ; the boot-sector sync at that drive's part1_lba, which for
            ; a floppy (part1_lba 0) is the boot card's MBR.
            mov     rf, r9
            add16   rf, BPBBLK_DEV
            mov     rb, vol_unit
            ldn     rf
            str     rb

            mov     rf, r9
            add16   rf, BPBBLK_ROOT_LBA ; RF -> 3-byte root LBA
            mov     rb, vol_cur_lba
            lda     rf
            str     rb
            inc     rb
            lda     rf
            str     rb
            inc     rb
            ldn     rf
            str     rb                  ; vol_cur_lba = root LBA (3
                                        ; bytes, big-endian, same
                                        ; storage convention as
                                        ; dir_cur_lba)

            mov     rf, r9
            add16   rf, BPBBLK_ROOT_ENTS ; RF -> 2-byte root_ents
                                        ; (big-endian)
            lda     rf
            phi     rc
            ldn     rf
            plo     rc                  ; RC = root_ents

            ; root_sectors = root_ents / 16 -- always exact for a
            ; spec-compliant FAT16 volume (root_ents*32 is always a
            ; multiple of the 512-byte sector size)
            shr16   rc
            shr16   rc
            shr16   rc
            shr16   rc                  ; RC = root_sectors

            mov     rf, vs_sectors_left
            ghi     rc
            str     rf
            inc     rf
            glo     rc
            str     rf

            mov     rf, vol_found
            ldi     VOL_FOUND_NONE
            str     rf

vs_scan_loop:
            mov     rf, vs_sectors_left
            lda     rf
            phi     rc
            ldn     rf
            plo     rc
            glo     rc
            lbnz    vs_have_sector
            ghi     rc
            lbz     vs_scan_done        ; 0 sectors left: vol_found is
                                        ; already VOL_FOUND_NONE

vs_have_sector:
            mov     rf, vol_cur_lba
            lda     rf
            plo     r8
            lda     rf
            phi     r7
            ldn     rf
            plo     r7
            mov     rf, vol_unit
            ldn     rf
            phi     r8                  ; R8.1 = this drive's block-device unit

            mov     rf, vol_sector_buf
            call    K_SECREAD           ; DF = 0/1 (an I/O error here
                                        ; is treated the same as
                                        ; VOL_FOUND_NONE -- the caller
                                        ; sees "no label" rather than a
                                        ; distinguishable I/O failure;
                                        ; GET has no way to report an
                                        ; error anyway, and SET/DELETE
                                        ; would fail their own
                                        ; write-back moments later on
                                        ; the same drive if this really
                                        ; is a genuine I/O problem)
            lbdf    vs_scan_done

            mov     ra, vol_sector_buf  ; RA = entry cursor
            ldi     16
            plo     r9                  ; R9.0 = entries remaining in
                                        ; this sector

vs_entry_loop:
            glo     r9
            lbz     vs_sector_done      ; no more entries this sector

            ldn     ra                  ; D = entry's first byte
            lbz     vs_hit_terminator   ; $00 = end of directory

            xri     $E5
            lbz     vs_entry_skip       ; deleted

            mov     rf, ra
            add16   rf, DE_ATTR
            ldn     rf                  ; D = attribute byte
            xri     ATTR_LFN
            lbz     vs_entry_skip       ; LFN entry: never the label

            mov     rf, ra
            add16   rf, DE_ATTR
            ldn     rf                  ; D = attribute byte (reloaded
                                        ; -- the xri just above clobbered
                                        ; it)
            ani     ATTR_VOLID
            lbz     vs_entry_skip       ; not the volume label

            ; FOUND -- record this entry's own byte offset within
            ; vol_sector_buf
            mov     rf, vol_sector_buf
            glo     rf
            str     r2
            glo     ra
            sm                          ; D = ra.lo - vol_sector_buf.lo
            plo     rb
            ghi     rf
            str     r2
            ghi     ra
            smb                         ; D = ra.hi - vol_sector_buf.hi
                                        ; - borrow
            phi     rb                  ; RB = byte offset

            mov     rf, vol_found_off
            ghi     rb
            str     rf
            inc     rf
            glo     rb
            str     rf

            mov     rf, vol_found
            ldi     VOL_FOUND_EXISTING
            str     rf
            lbr     vs_scan_done

vs_entry_skip:
            add16   ra, 32
            glo     r9
            smi     1
            plo     r9
            lbr     vs_entry_loop

vs_hit_terminator:
            mov     rf, vol_sector_buf
            glo     rf
            str     r2
            glo     ra
            sm
            plo     rb
            ghi     rf
            str     r2
            ghi     ra
            smb
            phi     rb

            mov     rf, vol_found_off
            ghi     rb
            str     rf
            inc     rf
            glo     rb
            str     rf

            mov     rf, vol_found
            ldi     VOL_FOUND_INSERTPT
            str     rf
            lbr     vs_scan_done

vs_sector_done:
            ; vol_cur_lba += 1 (24-bit, big-endian: byte0=bits23-16,
            ; byte1:byte2=bits15-0)
            mov     rf, vol_cur_lba
            lda     rf
            plo     r8                  ; R8.0 = byte0 (stash)
            lda     rf
            phi     rd
            ldn     rf
            plo     rd                  ; RD = byte1:byte2 (16-bit)
            add16   rd, 1

            ghi     rd
            lbnz    vs_no_carry
            glo     rd
            lbnz    vs_no_carry
            glo     r8
            adi     1
            plo     r8                  ; byte0 += 1 (carry out of the
                                        ; low 16 bits)
vs_no_carry:
            mov     rf, vol_cur_lba
            glo     r8
            str     rf
            inc     rf
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf

            mov     rf, vs_sectors_left
            lda     rf
            phi     rc
            ldn     rf
            plo     rc
            sub16   rc, 1
            mov     rf, vs_sectors_left
            ghi     rc
            str     rf
            inc     rf
            glo     rc
            str     rf

            lbr     vs_scan_loop

vs_scan_done:
            rtn

vs_sectors_left: dw   0

            endp

;------------------------------------------------------------------
; _vol_sync_bootsector: patch BS_VolLab (the FAT16 boot sector's OWN
; separate 11-byte volume-label copy, at fixed offset $2B) on the
; active drive to match what vol_label_set/vol_label_delete just
; wrote to the root-directory copy.
;
; FAT16 stores the volume label in two places: the root-directory
; ATTR_VOLID entry this library's own _vol_scan/vol_label_get/
; vol_label_set/vol_label_delete already read and write, AND a
; second, independent 11-byte field baked directly into the boot
; sector itself. Real DOS/Windows keep both copies in sync; this
; project's own testing (2026-07-30) found fsck.vfat treats a
; mismatch as real corruption and silently "fixes" it by overwriting
; the boot-sector copy with the root-directory one on its own next
; run -- this routine exists so that never has to happen.
;
; part1_lba (BPBBLK_PART1_LBA in the active drive's own BPB_DATA_PTR
; block) is the partition's own starting LBA, i.e. the boot sector's
; own location -- already used for exactly this purpose by boot/
; krnboot.asm at boot time, restated here since userland has no
; kernel primitive that hands back a raw sector by drive-relative
; role, only BPB_DATA_PTR's own already-parsed fields.
;
; Args:    RF = pointer to 11 bytes to write as BS_VolLab (already
;          uppercased/padded -- vol_label_set passes vls_new_name,
;          vol_label_delete passes 11 spaces)
; Returns: DF = 0/1 (I/O error reading or writing the boot sector)
; Modifies: everything
;------------------------------------------------------------------
            proc    _vol_sync_bootsector

            mov     rb, vsb_src
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; vsb_src = caller's 11-byte
                                        ; name pointer

            mov     rf, BPB_DATA_PTR
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = BPB block's real address

            ; vol_unit, captured again here so this routine never depends
            ; on _vol_scan having run first (see _vol_scan's note)
            mov     rf, r9
            add16   rf, BPBBLK_DEV
            mov     rb, vol_unit
            ldn     rf
            str     rb

            mov     rf, r9
            add16   rf, BPBBLK_PART1_LBA ; RF -> 3-byte boot sector LBA
            mov     rb, vsb_lba
            lda     rf
            str     rb
            inc     rb
            lda     rf
            str     rb
            inc     rb
            ldn     rf
            str     rb                  ; vsb_lba = boot sector LBA

            mov     rf, vsb_lba
            lda     rf
            plo     r8
            lda     rf
            phi     r7
            ldn     rf
            plo     r7
            mov     rf, vol_unit
            ldn     rf
            phi     r8                  ; R8.1 = this drive's block-device unit

            mov     rf, vsb_sector_buf
            call    K_SECREAD           ; read the WHOLE sector --
                                        ; only 11 of its 512 bytes
                                        ; change, but a write has to
                                        ; supply the rest unchanged
            lbdf    vsb_err

            mov     rf, vsb_sector_buf
            add16   rf, $2B             ; BS_VolLab's own fixed offset
            mov     rd, vsb_src
            lda     rd
            phi     ra
            ldn     rd
            plo     ra                  ; RA = source (caller's 11
                                        ; bytes)
            ldi     11
            plo     rc
vsb_copy:
            glo     rc
            lbz     vsb_write
            lda     ra
            str     rf
            inc     rf
            glo     rc
            smi     1
            plo     rc
            lbr     vsb_copy

vsb_write:
            mov     rf, vsb_lba
            lda     rf
            plo     r8
            lda     rf
            phi     r7
            ldn     rf
            plo     r7
            mov     rf, vol_unit
            ldn     rf
            phi     r8                  ; R8.1 = this drive's block-device unit

            mov     rf, vsb_sector_buf
            call    K_SECWRITE
            lbdf    vsb_err

            clc
            rtn

vsb_err:
            stc
            rtn

vsb_src:        dw      0
vsb_lba:        ds      3               ; 3-byte LBA (kernel.inc's own
                                        ; LBA_SIZE -- not restated in
                                        ; kernel_api.inc, so declared
                                        ; as a plain literal here,
                                        ; matching this file's own
                                        ; existing DE_ATTR/ATTR_LFN/
                                        ; ATTR_VOLID precedent)
vsb_sector_buf: ds      512

            endp

;------------------------------------------------------------------
; _vol_classify_char: is D an allowed volume-label character, after
; upper-casing if it's a lowercase letter (matching real MS-DOS's own
; LABEL behavior, added 2026-07-30 -- the original version of this
; routine rejected lowercase outright instead of transforming it)?
;
; Branch structure (lbnf on the low-end check, lbdf on the high-end
; check of each range) and the "reload D via ldn r2 immediately before
; every safe return" discipline both mirror kernel/file.asm's own
; proven _classify_char exactly -- that reload is NOT optional: it's
; what makes D hold the real (possibly transformed) character at
; return, rather than a stale smi subtraction remainder or an xri
; comparison result left over from whichever check last ran. The
; first version of this routine dropped that reload (harmless at the
; time, since no caller read D back then) -- restored here now that
; vol_label_set's own build pass depends on D being correct.
;
; Args:    D = character
; Returns: DF = 0 -- character is allowed; D = the character to
;          actually use (uppercased if the input was a-z, otherwise
;          unchanged).
;          DF = 1 -- character is not a letter, digit, '_', or '-',
;          even after case-folding; D unspecified.
; Modifies: nothing but D/DF (uses [R2] as scratch, same established
; str-r2-as-scratch convention used throughout this codebase)
;------------------------------------------------------------------
            proc    _vol_classify_char

            str     r2                  ; [R2] = original char

            ; lowercase a-z? -- transform to uppercase, accept
            smi     'a'
            lbnf    vcc_check_upper     ; D < 'a'
            ldn     r2
            smi     'z'+1
            lbdf    vcc_check_upper     ; D > 'z'
            ldn     r2
            smi     $20                 ; D = uppercased character
            clc                         ; DF = 0, accepted
            rtn

vcc_check_upper:
            ldn     r2
            smi     'A'
            lbnf    vcc_check_digit
            ldn     r2
            smi     'Z'+1
            lbdf    vcc_check_digit
            ldn     r2
            clc                         ; DF = 0, already uppercase
            rtn

vcc_check_digit:
            ldn     r2
            smi     '0'
            lbnf    vcc_check_special
            ldn     r2
            smi     '9'+1
            lbdf    vcc_check_special
            ldn     r2
            clc                         ; DF = 0, digit
            rtn

vcc_check_special:
            ldn     r2
            xri     '_'
            lbz     vcc_ok
            ldn     r2
            xri     '-'
            lbz     vcc_ok
            stc                         ; DF = 1, genuinely illegal --
                                        ; rejected outright, not
                                        ; substituted (unlike the
                                        ; kernel's own _classify_char,
                                        ; which always needs SOME
                                        ; character to fall back to
                                        ; for short-name generation;
                                        ; this routine's own caller
                                        ; would rather reject the whole
                                        ; label than silently mangle it)
            rtn

vcc_ok:
            ldn     r2
            clc                         ; DF = 0, '_' or '-'
            rtn

            endp

;------------------------------------------------------------------
; _vol_data: state shared across _vol_scan and all three public entry
; points above -- see gotcha #6 (same-file cross-proc references
; still need extrn+public, exactly as if they were in a different
; file).
;------------------------------------------------------------------
            proc    _vol_data

vol_found:      db      0
vol_found_off:  dw      0
vol_cur_lba:    ds      3
vol_unit:       db      0
vol_sector_buf: ds      512

                public  vol_found
                public  vol_found_off
                public  vol_cur_lba
                public  vol_unit
                public  vol_sector_buf

            endp
