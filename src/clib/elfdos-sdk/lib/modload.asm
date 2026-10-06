;
; modload.asm - loader for relocatable dynamic modules (see
; include/modformat.inc for the on-disk format). NOT a standalone
; program -- no EDF header, no org PROG_BASE, no entry point of its
; own. Assembled separately (lib/modload.prg) and linked alongside a
; program (or kernel file) that wants it. A calling program declares
; "extrn mod_load" / "extrn mod_release" and calls them like any other
; routine.
;
; Companion to Link/02's own "-m" module output mode (see this
; project's design plan) and lib/icall.asm (for invoking a loaded
; module's public entry points, whose addresses are only known once
; the module has actually been loaded).
;
; The core mechanism: a module always loads at a page-aligned address
; (low byte $00). Link/02's own "-m" mode already established (see its
; own header comment) that with this guarantee, adding the load base
; to ANY embedded address only ever changes that address's HIGH byte
; -- the low byte is unconditionally unchanged. So every fixup table
; entry is just a 2-byte offset, and applying it is a single 8-bit add
; with no carry propagation: memory[base+offset] += base.hi. This
; loader does exactly that, nothing more -- there is no per-module
; init code to run, no PC introspection, nothing module-side needs to
; know its own address (see the project's own design plan for why that
; approach was chosen over full position-independent/RB-relative
; addressing).
;
; The caller supplies its own FCB+iobuf (RD/RA, see mod_load's own
; Args below) rather than this file owning a fixed pair -- deliberate,
; matching K_FILE_OPEN's own established convention exactly. A real
; first consumer (kernel/batch.asm, retrofitting the loadable batch
; module) found this the hard way: an early version of this file
; declared its own 544-byte FCB+iobuf, which -- once linked into
; kernel.bin -- pushed the kernel's own Highest address past
; PROG_BASE. The old, Phase 1 batch-module loader had deliberately
; reused kernel/loader.asm's already-idle prog_fcb/prog_iobuf instead
; of paying for a second pair; a caller-supplied convention here lets
; the kernel keep doing exactly that (zero additional kernel-resident
; bytes for the FCB/iobuf), while an ordinary program calling this
; from outside the kernel supplies its own.
;

#include    include/opcodes.def
#include    include/bios.inc
#include    include/kernel_api.inc
#include    include/modformat.inc

            extrn   ml_fcb_ptr
            extrn   _ml_close_fcb
            extrn   _ml_fcb_rd
            extrn   ml_header
            extrn   ml_code_size
            extrn   ml_body_size
            extrn   ml_base
            extrn   ml_fixup_count
            extrn   ml_fixup_entry
            extrn   ml_scratch

;------------------------------------------------------------------
; mod_load: open, load, and fix up a relocatable module.
; Args:    RF = pointer to a null-terminated path string
;          RD = pointer to a caller-owned FCB_LEN-byte FCB (need not
;          be pre-zeroed -- matches K_FILE_OPEN's own convention)
;          RA = pointer to a caller-owned FCB_IOBUF_LEN-byte I/O buffer
; Returns: DF = 0 on success: RD = the module's actual (page-aligned)
;          load address, RC = the himem reservation size that must be
;          passed back to mod_release later (NOT the same as the
;          module's own code_size -- includes the alignment padding).
;          DF = 1 on any failure, with D = a MODLOAD_ERR_* code
;          (include/modformat.inc): NOTFOUND if the file wouldn't open,
;          NOMEM if there wasn't enough RAM headroom, BAD for anything
;          else (bad magic, truncated file, I/O error). Nothing is left
;          reserved or open in any failure case.
; Modifies: everything
;------------------------------------------------------------------
            proc    mod_load

            ; stash the caller's FCB pointer immediately -- every
            ; later K_FILE_* call in this routine needs to reload RD
            ; fresh (nothing survives the intervening calls). The
            ; iobuf pointer (RA) is used exactly once, right below,
            ; with no reload ever needed later, so it's simply left
            ; untouched in RA rather than also being stashed.
            mov     r8, ml_fcb_ptr
            ghi     rd
            str     r8
            inc     r8
            glo     rd
            str     r8

            ldi     0                   ; mode 0 = read
            call    K_FILE_OPEN         ; RD/RA still hold the
                                        ; caller's own fcb/iobuf,
                                        ; exactly as it set them
            lbdf    ml_open_fail

            ; read the 6-byte header
            call    _ml_fcb_rd          ; RD = caller's FCB
                                        ; RD = caller's FCB (reloaded)
            mov     rf, ml_header
            ldi     0
            phi     rc
            ldi     MOD_HEADER_LEN
            plo     rc
            call    K_FILE_READ
            lbdf    ml_fail_close_only
            glo     rc
            xri     MOD_HEADER_LEN
            lbnz    ml_fail_close_only  ; short/truncated read

            ; validate magic
            mov     rf, ml_header
            lda     rf
            xri     MOD_MAGIC0
            lbnz    ml_fail_close_only
            lda     rf
            xri     MOD_MAGIC1
            lbnz    ml_fail_close_only
            lda     rf
            xri     MOD_MAGIC2
            lbnz    ml_fail_close_only
            inc     rf                  ; skip the version byte --
                                        ; not strictly checked (a
                                        ; future version bump that
                                        ; stays format-compatible
                                        ; shouldn't need this loader
                                        ; to also change)

            ; rf now points at header[4] -- code_size, big-endian.
            ; code_size is Link/02's own "-m" convention:
            ; highest-lowest+1, the TOTAL linked content size,
            ; INCLUDING the 6-byte header itself (Link/02 has no way
            ; to know this project's own header layout, so it always
            ; reports the whole span) -- meaning the bytes still to be
            ; read from the file at this point (the header's own 6
            ; bytes are already consumed) are code_size-MOD_HEADER_LEN,
            ; and they belong at aligned_base+MOD_HEADER_LEN, not
            ; aligned_base+0, so the module's own jump table (defined
            ; at fixed offsets from address 0, i.e. from the header's
            ; own start) lands exactly where its offsets expect.
            lda     rf
            phi     r8
            ldn     rf
            plo     r8                  ; R8 = code_size
            mov     rf, ml_code_size
            ghi     r8
            str     rf
            inc     rf
            glo     r8
            str     rf

            ; reject a code_size that couldn't even fit the header
            ; that was just read -- a corrupt/truncated file, not a
            ; real module
            ghi     r8
            lbnz    ml_size_ok          ; high byte nonzero: >= 256,
                                        ; certainly >= MOD_HEADER_LEN
            glo     r8
            smi     MOD_HEADER_LEN
            lbnf    ml_fail_close_only  ; code_size < MOD_HEADER_LEN
ml_size_ok:
            ; ml_body_size = code_size - MOD_HEADER_LEN -- the real
            ; byte count still to be read from the file, and reused
            ; below for the short-read check. Six repeated DECs
            ; (MOD_HEADER_LEN=6) rather than SUB16's own NW-immediate
            ; form -- smaller (6 bytes vs. 8) for a constant this
            ; small, and DEC never touches D/DF at all (matching this
            ; project's own established INC/DEC-over-ADD16/SUB16
            ; preference for small constant register-pair adjustments;
            ; the very next instruction clobbers D via MOV regardless,
            ; so nothing here relies on D/DF surviving either way).
            dec     r8
            dec     r8
            dec     r8
            dec     r8
            dec     r8
            dec     r8
            mov     rf, ml_body_size
            ghi     r8
            str     rf
            inc     rf
            glo     r8
            str     rf

            ; reserve code_size + MOD_RESERVE_PAD bytes of himem --
            ; the FULL logical span from address 0, even though the
            ; first MOD_HEADER_LEN bytes of it are never actually
            ; written (nothing ever reads the module's own in-RAM
            ; copy of its header, only the jump table at
            ; MOD_HEADER_LEN onward)
            call    ml_reserve_size     ; RC = code_size + PAD
            call    K_HIMEM_RESERVE
            lbdf    ml_fail_nomem       ; not enough headroom -- reserve
                                        ; guarantees nothing changed

            ; RD = raw_base (mem_top+1) -- align up to the next page
            ; boundary within [raw_base, raw_base+PAD]. Adding PAD then
            ; masking the low byte to 0 always lands in that range --
            ; see this file's own design notes / the project plan for
            ; the proof.
            ghi     rd
            phi     r8
            glo     rd
            adi     MOD_RESERVE_PAD
            plo     r8
            ghi     rd
            adci    0
            phi     r8                  ; R8 = raw_base + PAD (full)
            ldi     0
            plo     r8                  ; R8 = aligned base (low byte
                                        ; forced to 0)

            mov     rf, ml_base
            ghi     r8
            str     rf
            inc     rf
            glo     r8
            str     rf

            ; read ml_body_size bytes (code_size, minus the header
            ; already consumed above) starting at aligned_base +
            ; MOD_HEADER_LEN -- NOT aligned_base itself, since the
            ; header's own logical span (address 0..5) is intentionally
            ; left unwritten; the module's own jump table (fixed
            ; offsets starting at MOD_HEADER_LEN) needs to land exactly
            ; where its own offsets expect
            call    _ml_fcb_rd          ; RD = caller's FCB
                                        ; RD = caller's FCB
            mov     rb, ml_base
            lda     rb
            phi     rf
            ldn     rb
            plo     rf                  ; RF = aligned base

            ; RF += MOD_HEADER_LEN (16-bit add via M(X) staging, not
            ; the risky register-register ADD16 -- gotcha #18)
            mov     ra, ml_scratch
            sex     ra
            ldi     MOD_HEADER_LEN
            str     ra
            glo     rf
            add
            plo     rf
            ldi     0
            str     ra
            ghi     rf
            adc
            phi     rf                  ; RF = aligned_base + MOD_HEADER_LEN
            sex     r2

            mov     rb, ml_body_size
            lda     rb
            phi     rc
            ldn     rb
            plo     rc                  ; RC = ml_body_size
            call    K_FILE_READ
            lbdf    ml_fail_release_close

            ; confirm the full code body was actually read (a short
            ; read means a truncated/corrupt file -- proceeding would
            ; run whatever garbage is sitting in that RAM)
            mov     rb, ml_body_size
            ldn     rb
            str     r2
            ghi     rc
            xor
            lbnz    ml_fail_release_close
            inc     rb
            ldn     rb
            str     r2
            glo     rc
            xor
            lbnz    ml_fail_release_close

            ; read the 2-byte fixup_count
            call    _ml_fcb_rd          ; RD = caller's FCB
                                        ; RD = caller's FCB
            mov     rf, ml_fixup_count
            ldi     0
            phi     rc
            ldi     2
            plo     rc
            call    K_FILE_READ
            lbdf    ml_fail_release_close
            glo     rc
            xri     2
            lbnz    ml_fail_release_close

ml_fixup_loop:
            ; fixup_count == 0 ?
            mov     rb, ml_fixup_count+1
            ldn     rb                  ; low byte
            lbnz    ml_fixup_have_more
            dec     rb
            ldn     rb                  ; high byte
            lbz     ml_fixup_done

ml_fixup_have_more:
            call    _ml_fcb_rd          ; RD = caller's FCB
                                        ; RD = caller's FCB
            mov     rf, ml_fixup_entry
            ldi     0
            phi     rc
            ldi     2
            plo     rc
            call    K_FILE_READ
            lbdf    ml_fail_release_close
            glo     rc
            lbz     ml_fail_release_close  ; nothing read at all: the
                                        ; file ran out of data where a
                                        ; real entry was still expected

            ; R8 = ml_base (full)
            mov     rb, ml_base
            lda     rb
            phi     r8
            ldn     rb
            plo     r8

            ; R9 = ml_fixup_entry (full, the offset)
            mov     rb, ml_fixup_entry
            lda     rb
            phi     r9
            ldn     rb
            plo     r9

            ; R8 += R9 (target address = base + offset) -- staged via
            ; M(X), never register-register ADD16 (gotcha #18)
            mov     ra, ml_scratch
            sex     ra
            glo     r9
            str     ra
            glo     r8
            add
            plo     r8
            ghi     r9
            str     ra
            ghi     r8
            adc
            phi     r8
            sex     r2                  ; R8 = target address

            ; memory[R8] += ml_base.hi (single 8-bit add, no carry --
            ; the whole point of the page-alignment guarantee)
            mov     rb, ml_base
            ldn     rb                  ; D = base.hi
            str     r2
            ldn     r8                  ; D = current byte at target
            add                         ; D = current + base.hi
            str     r8                  ; write back

            ; fixup_count -= 1 (DEC, not SUB16 -- see the earlier
            ; MOD_HEADER_LEN comment for why)
            mov     rb, ml_fixup_count
            lda     rb
            phi     r9
            ldn     rb
            plo     r9
            dec     r9
            mov     rb, ml_fixup_count
            ghi     r9
            str     rb
            inc     rb
            glo     r9
            str     rb

            lbr     ml_fixup_loop

ml_fixup_done:
            call    _ml_close_fcb

            mov     rf, ml_base
            lda     rf
            phi     rd
            ldn     rf
            plo     rd                  ; RD = module base

            call    ml_reserve_size     ; RC = reservation size, for
                                        ; the caller to pass back to
                                        ; mod_release later
            clc
            rtn

ml_fail_release_close:
            call    ml_reserve_size     ; RC = the same size originally
                                        ; requested from K_HIMEM_RESERVE
            call    K_HIMEM_RELEASE
            ; falls through into ml_fail_close_only's own close+fail
            ; tail -- byte-for-byte identical, no branch needed

ml_fail_close_only:
            ldi     MODLOAD_ERR_BAD
            lskp                        ; skip the 2-byte ldi below
ml_fail_nomem:
            ldi     MODLOAD_ERR_NOMEM
            call    _ml_close_fcb       ; preserves D (the code)
            stc                         ; SMI 0: DF=1, D unchanged
            rtn

ml_open_fail:
            ldi     MODLOAD_ERR_NOTFOUND
            stc
            rtn

; ----------------------------------------------------------------
; ml_reserve_size: RC = ml_code_size + MOD_RESERVE_PAD -- factored out
; since it's needed at three points (the initial reservation, and both
; the success and failure paths' matching release/report), and each
; needs it freshly recomputed from memory rather than trusted in a
; register across the intervening K_FILE_*/K_HIMEM_* calls.
; Args:    none (reads ml_code_size)
; Returns: RC = ml_code_size + MOD_RESERVE_PAD
; Modifies: RC (and D)
; ----------------------------------------------------------------
ml_reserve_size:
            mov     rb, ml_code_size
            lda     rb
            phi     rc                  ; RC.hi = code_size.hi
                                        ; (tentative -- may need +1
                                        ; below for a carry out of lo)
            ldn     rb
            adi     MOD_RESERVE_PAD
            plo     rc                  ; RC.lo = (code_size.lo+PAD)
                                        ; & 0xff, DF = carry out
            ghi     rc
            adci    0
            phi     rc                  ; RC.hi += carry
            rtn

            endp

;------------------------------------------------------------------
; _ml_close_fcb: close the caller's own FCB (ml_fcb_ptr). Factored
; out of mod_load after finding this exact "dereference ml_fcb_ptr
; into RD, call K_FILE_CLOSE" sequence duplicated at all 3 of its
; exit paths (success, and both failure tails).
; Args:    none
; Returns: D unchanged (2026-09-23: the failure tails load their
;          MODLOAD_ERR_* code before calling this); DF is K_FILE_CLOSE's
; Modifies: RB, RD (plus whatever K_FILE_CLOSE itself modifies)
;------------------------------------------------------------------
            proc    _ml_close_fcb

            stxd                        ; save D on the stack (X = R2)
            call    _ml_fcb_rd          ; RD = caller's FCB
                                        ; RD = caller's FCB
            call    K_FILE_CLOSE
            irx
            ldx                         ; restore D
            rtn

            endp

;------------------------------------------------------------------
; mod_release: reverse a successful mod_load's reservation.
; Args:    RC = the reservation size mod_load returned (NOT the
;          module's own code_size)
; Returns: nothing
; Modifies: R8, RA, RB, RF (whatever K_HIMEM_RELEASE itself modifies)
;------------------------------------------------------------------
            proc    _ml_fcb_rd

;------------------------------------------------------------------
; _ml_fcb_rd: RD = the caller's FCB pointer (ml_fcb_ptr). Leaves
; RB = ml_fcb_ptr+1 and D = RD.lo, DF untouched -- the same state the
; inline 5-instruction reload it replaced left at each of its 5 sites.
;------------------------------------------------------------------
            mov     rb, ml_fcb_ptr
            lda     rb
            phi     rd
            ldn     rb
            plo     rd
            rtn

            endp

;------------------------------------------------------------------
            proc    mod_release

            lbr     K_HIMEM_RELEASE ; tail call

            endp
