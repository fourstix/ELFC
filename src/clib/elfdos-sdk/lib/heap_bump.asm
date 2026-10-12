;
; heap_bump.asm - minimal bump (arena) allocator library
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/heap_bump.prg)
; and linked alongside a program that wants it, the same way the
; kernel's own multi-file modules link together. A calling program
; declares "extrn bump_init" / "extrn bump_alloc" / etc. and calls
; them like any other routine.
;
; Design: a single pointer (bump_next) that only ever moves forward
; within [base, top]. bump_alloc just returns the current bump_next
; and advances it by the requested size -- no header, no bookkeeping,
; no way to free an individual block. Two ways to reclaim space:
;   - bump_mark/bump_release: snapshot the current pointer, later
;     reset back to it, freeing everything allocated since (a classic
;     stack-discipline / scoped-allocation pattern -- e.g. "mark, do
;     a bunch of temporary work, release" with no per-object cost).
;   - bump_init again, to reclaim the WHOLE arena at once.
; This trades away general-purpose free() entirely in exchange for
; being about as small and fast as an allocator can possibly be --
; the right tool for a program with simple, scoped, or never-freed
; allocation needs. See lib/heap_malloc.asm for a general-purpose
; alternative when arbitrary alloc/free order is actually needed.
;
; Register convention (matching heap_malloc.asm's own, so a caller
; can switch between the two with minimal code changes):
;   bump_init:    Args RD=base, RF=top (both INCLUSIVE -- top is the
;                 LAST usable byte, matching LOADER_ARGS' own
;                 mem_base/mem_top convention exactly, so a caller can
;                 pass those values straight through with no
;                 adjustment). Returns: nothing.
;   bump_alloc:   Args RC=requested size (0 is legal: always succeeds,
;                 returns the current pointer unchanged, never
;                 advances). Returns: RF=pointer to the block, or
;                 RF=0 if there isn't enough room left.
;   bump_mark:    Args: none. Returns: RF=the current allocation
;                 pointer (an opaque value -- just remember it).
;   bump_release: Args RF=a value previously returned by bump_mark
;                 (or by bump_init's own base, to reclaim everything).
;                 Returns: nothing. No validation that RF is actually
;                 a value this allocator produced -- trusted, like a
;                 raw pointer anywhere else in this codebase.
;
; None of these routines call any kernel/BIOS primitive, so none of
; the "does this survive a call" gotchas apply to a caller using
; them -- ordinary register-clobber rules only.
;

#include    include/opcodes.def

            extrn   bump_next
            extrn   bump_top

; ----------------------------------------------------------------
; bump_init: establish the arena's bounds and reset the allocation
; pointer to its start.
; Args:    RD = base (first usable byte), RF = top (last usable byte,
;          inclusive)
; Returns: nothing
; Modifies: RB (and D)
; ----------------------------------------------------------------
            proc    bump_init

            mov     rb, bump_next
            ghi     rd
            str     rb
            inc     rb
            glo     rd
            str     rb                  ; bump_next = base

            mov     rb, bump_top
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb                  ; bump_top = top
            rtn

            endp

; ----------------------------------------------------------------
; bump_alloc: carve 'size' bytes off the front of the remaining
; arena.
; Args:    RC = requested size (0 always succeeds trivially)
; Returns: RF = pointer to the block (bump_next's old value), or
;          RF = 0 if the request doesn't fit in what's left
; Modifies: R7, R8, R9, RB, RD (and D)
; ----------------------------------------------------------------
            proc    bump_alloc

            ghi     rc
            lbnz    ba_have_size
            glo     rc
            lbnz    ba_have_size

            ; size == 0: always succeeds, pointer unchanged, no
            ; bounds check needed (nothing is actually being carved
            ; off)
            mov     rf, bump_next
            lda     rf
            phi     r9
            ldn     rf
            plo     r9
            mov     rf, r9
            rtn

ba_have_size:
            mov     rf, bump_top
            lda     rf
            phi     r8
            ldn     rf
            plo     r8                  ; R8 = bump_top

            mov     rf, bump_next
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = bump_next (the block
                                        ; we'll return on success)

            ; remaining = bump_top - bump_next (both inclusive
            ; bounds, so this is one less than the true byte count --
            ; accounted for by comparing against size-1 below rather
            ; than size)
            mov     rb, r8
            sub16   rb, r9              ; RB = remaining

            mov     rd, rc
            sub16   rd, 1               ; RD = size - 1 (safe: size
                                        ; >= 1 on this path)

            ; remaining >= size-1 ?
            glo     rd
            str     r2
            glo     rb
            sm
            ghi     rd
            str     r2
            ghi     rb
            smb
            lbnf    ba_fail             ; DF=0: remaining < size-1,
                                        ; doesn't fit

            mov     rf, r9              ; RF = block start (return
                                        ; value)
            add16   r9, rc              ; R9 = bump_next + size (the
                                        ; new bump_next)
            mov     rb, bump_next
            ghi     r9
            str     rb
            inc     rb
            glo     r9
            str     rb                  ; bump_next updated
            rtn                         ; RF still holds the block
                                        ; pointer

ba_fail:
            ldi     0
            phi     rf
            plo     rf
            rtn

            endp

; ----------------------------------------------------------------
; bump_mark: snapshot the current allocation pointer.
; Args:    none
; Returns: RF = the current bump_next value (an opaque mark)
; Modifies: RD (and D)
; ----------------------------------------------------------------
            proc    bump_mark

            mov     rf, bump_next
            lda     rf
            phi     rd
            ldn     rf
            plo     rd
            mov     rf, rd
            rtn

            endp

; ----------------------------------------------------------------
; bump_release: reset the allocation pointer back to a previously
; taken mark (or to bump_init's own base), freeing everything
; allocated since.
; Args:    RF = a mark from bump_mark, or the base passed to
;          bump_init
; Returns: nothing
; Modifies: RB (and D)
; ----------------------------------------------------------------
            proc    bump_release

            mov     rb, bump_next
            ghi     rf
            str     rb
            inc     rb
            glo     rf
            str     rb
            rtn

            endp

; ----------------------------------------------------------------
; Data
; ----------------------------------------------------------------
            proc    _heap_bump_data

bump_next:      dw      0
bump_top:       dw      0

                public  bump_next
                public  bump_top

            endp
