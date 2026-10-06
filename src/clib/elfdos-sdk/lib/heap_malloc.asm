;
; heap_malloc.asm - general-purpose malloc/free allocator library
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/heap_malloc.prg)
; and linked alongside a program that wants it, the same way the
; kernel's own multi-file modules link together. A calling program
; declares "extrn heap_init" / "extrn heap_alloc" / "extrn heap_free"
; and calls them like any other routine.
;
; Design: a classic address-ordered singly-linked free list with
; first-fit search, splitting a too-large block on alloc, and
; coalescing adjacent free blocks (both directions) on free -- the
; same shape used by countless small-system C library mallocs. Chosen
; over a bump allocator (see lib/heap_bump.asm) specifically because
; it supports freeing blocks in ANY order, which a bump allocator
; structurally can't -- the right tool once a program's allocation
; pattern isn't simply "allocate a bunch, then release it all at
; once."
;
; Block layout: every block, free or allocated, begins with a 2-byte
; SIZE field giving the size of its OWN usable area (not counting
; this 2-byte header). A FREE block additionally has a 2-byte NEXT
; field immediately after SIZE, pointing to the next free block in
; address order (0 = end of list) -- this costs nothing extra, since
; a free block's own "usable area" isn't holding live data anyway, so
; the list linkage just lives in the first 2 bytes of it. An
; ALLOCATED block's bytes past SIZE are entirely the caller's own
; data; heap_alloc returns a pointer to that data (block address + 2),
; and heap_free takes that same pointer back (block address = pointer
; - 2) -- callers never see or touch a raw block address directly.
;
; HEAP_MIN_SPLIT (4 = a free block's own SIZE+NEXT fields): when
; satisfying an allocation from a larger free block, if what's left
; over after satisfying the request is smaller than this, the WHOLE
; block is handed to the caller instead of splitting off an unusably
; tiny sliver that could never itself be allocated later. This is
; the only source of internal fragmentation this allocator has.
;
; Algorithm verified independently before writing this file: the
; exact same free-list/split/coalesce logic was re-implemented in
; Python and run against basic round-trips, FIFO/reverse/20 rounds of
; randomized-order alloc-then-free-everything (confirming full
; coalescing back to one block every time), exhaustion+recovery,
; exact-fit (no split), and remainder-below-HEAP_MIN_SPLIT (no split)
; cases -- see project scratch history. That validates the algorithm
; itself; the 1802 register-level implementation below was then
; hand-traced against it.
;
; Register convention (matching heap_bump.asm's own):
;   heap_init:  Args RD=base, RF=top (both INCLUSIVE -- top is the
;               LAST usable byte, matching LOADER_ARGS' own
;               mem_base/mem_top convention exactly). Returns:
;               nothing.
;   heap_alloc: Args RC=requested size (usable bytes; 0 is legal --
;               always succeeds, returns SOME valid pointer with zero
;               usable bytes, handled as a degenerate 0-remainder
;               split-avoidance case, not specially coded).
;               Returns: RF=pointer to the block's data, or RF=0 if
;               nothing in the free list is big enough.
;   heap_free:  Args RF=a pointer previously returned by heap_alloc.
;               Returns: nothing. No validation that RF is genuinely
;               a live allocation from this heap -- trusted, like any
;               raw pointer elsewhere in this codebase; freeing a
;               bad/foreign/already-freed pointer is undefined,
;               exactly like a C malloc/free's own contract.
;
; None of these routines call any kernel/BIOS primitive, so none of
; the "does this survive a call" gotchas apply to a caller using
; them -- ordinary register-clobber rules only.
;

#include    include/opcodes.def

HEAP_MIN_SPLIT: equ     4

            extrn   heap_free_head

; ----------------------------------------------------------------
; heap_init: establish the heap's bounds as one single free block
; spanning the whole arena.
; Args:    RD = base (first usable byte), RF = top (last usable byte,
;          inclusive)
; Returns: nothing
; Modifies: R8, RB (and D)
; ----------------------------------------------------------------
            proc    heap_init

            ; total = top - base + 1; usable = total - 2 (this one
            ; block's own header)
            mov     r8, rf
            sub16   r8, rd
            add16   r8, 1               ; R8 = total size
            sub16   r8, 2               ; R8 = usable size

            mov     rf, rd              ; RF = base (the block's own
                                        ; address)
            ghi     r8
            str     rf
            inc     rf
            glo     r8
            str     rf                  ; SIZE = usable
            inc     rf
            ldi     0
            str     rf
            inc     rf
            str     rf                  ; NEXT = 0 (only block, end
                                        ; of list)

            mov     rb, heap_free_head
            ghi     rd
            str     rb
            inc     rb
            glo     rd
            str     rb                  ; heap_free_head = base
            rtn

            endp

; ----------------------------------------------------------------
; heap_alloc: first-fit search the free list; split the found block
; if enough remains to be independently useful, otherwise hand over
; the whole thing.
; Args:    RC = requested size
; Returns: RF = pointer to the block's data, or RF = 0 on failure
; Modifies: R7, R8, R9, RA, RB, RD (and D)
; ----------------------------------------------------------------
            proc    heap_alloc

            ldi     0
            phi     r7
            plo     r7                  ; R7 = 'previous' block
                                        ; address seen so far (0 =
                                        ; none -- the eventual match,
                                        ; if any, is the list head)

            mov     rf, heap_free_head
            lda     rf
            phi     r8
            ldn     rf
            plo     r8                  ; R8 = 'current' candidate

ha_loop:
            ghi     r8
            lbnz    ha_check
            glo     r8
            lbnz    ha_check
            lbr     ha_fail             ; R8 == 0: end of list,
                                        ; nothing fit

ha_check:
            mov     rf, r8
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = candidate's own SIZE

            ; SIZE >= requested ?
            glo     rc
            str     r2
            glo     r9
            sm
            ghi     rc
            str     r2
            ghi     r9
            smb
            lbdf    ha_found            ; DF=1: big enough

            ; advance: previous = current, current = current's own
            ; NEXT (read BEFORE R8 itself is overwritten)
            mov     r7, r8
            mov     rf, r8
            add16   rf, 2
            lda     rf
            phi     r8
            ldn     rf
            plo     r8
            lbr     ha_loop

ha_found:
            ; R8 = matching block, R9 = its own SIZE, R7 = the
            ; PREVIOUS block (0 if R8 is the list head), RC =
            ; requested size
            mov     rb, r9
            sub16   rb, rc              ; RB = remainder if split

            ghi     rb
            lbnz    ha_split            ; RB.hi != 0: definitely a
                                        ; large remainder, split
            glo     rb
            smi     HEAP_MIN_SPLIT
            lbnf    ha_no_split         ; remainder < HEAP_MIN_SPLIT:
                                        ; too small to be useful,
                                        ; don't split

ha_split:
            ; new free block goes right after the allocated part
            mov     rd, r8
            add16   rd, 2
            add16   rd, rc              ; RD = new free block's own
                                        ; address

            mov     r9, rb
            sub16   r9, 2               ; R9 = new free block's own
                                        ; SIZE (remainder minus its
                                        ; own new header)

            mov     rf, rd
            ghi     r9
            str     rf
            inc     rf
            glo     r9
            str     rf                  ; new block's SIZE written

            ; new block's NEXT = old block's own NEXT (old block's
            ; header hasn't been touched yet, still holds the
            ; original NEXT)
            mov     rf, r8
            add16   rf, 2
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = old block's own NEXT
            mov     rf, rd
            add16   rf, 2
            ghi     r9
            str     rf
            inc     rf
            glo     r9
            str     rf                  ; new block's NEXT = old
                                        ; block's NEXT

            ; shrink the allocated block's own SIZE field down to
            ; exactly what was requested
            mov     rf, r8
            ghi     rc
            str     rf
            inc     rf
            glo     rc
            str     rf

            ; relink: whatever pointed at the OLD block (R8) now
            ; points at the NEW block (RD) instead
            ghi     r7
            lbnz    ha_split_prev_nz
            glo     r7
            lbnz    ha_split_prev_nz
            mov     rf, heap_free_head
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf
            lbr     ha_done

ha_split_prev_nz:
            mov     rf, r7
            add16   rf, 2
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf
            lbr     ha_done

ha_no_split:
            ; hand over the WHOLE block -- its own SIZE field stays
            ; exactly as it was (R9), no shrink. Unlink it entirely:
            ; whatever pointed at it now points at ITS OWN next
            ; instead.
            mov     rf, r8
            add16   rf, 2
            lda     rf
            phi     rd
            ldn     rf
            plo     rd                  ; RD = this block's own NEXT

            ghi     r7
            lbnz    ha_nosplit_prev_nz
            glo     r7
            lbnz    ha_nosplit_prev_nz
            mov     rf, heap_free_head
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf
            lbr     ha_done

ha_nosplit_prev_nz:
            mov     rf, r7
            add16   rf, 2
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf

ha_done:
            mov     rf, r8
            add16   rf, 2               ; RF = the allocated block's
                                        ; data pointer
            rtn

ha_fail:
            ldi     0
            phi     rf
            plo     rf
            rtn

            endp

; ----------------------------------------------------------------
; heap_free: return a block to the free list, in address order, then
; coalesce it with an immediately-adjacent free neighbor on either
; side if one exists.
; Args:    RF = pointer to the block's data, as returned by heap_alloc
; Returns: nothing
; Modifies: R7, R8, R9, RA, RB, RD (and D)
; ----------------------------------------------------------------
            proc    heap_free

            mov     r8, rf
            sub16   r8, 2               ; R8 = block address

            mov     rf, r8
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = this block's own SIZE
                                        ; (already correct, set at
                                        ; allocation time)

            ; --- find where it belongs in the address-ordered free
            ; list: RB = the block that should precede it (0 = none,
            ; belongs at the head), RD = the block that should follow
            ; it (0 = none, belongs at the tail) ---
            ldi     0
            phi     rb
            plo     rb                  ; RB = 'previous' candidate

            mov     rf, heap_free_head
            lda     rf
            phi     rd
            ldn     rf
            plo     rd                  ; RD = 'current' candidate

hf_scan:
            ghi     rd
            lbnz    hf_scan_have
            glo     rd
            lbnz    hf_scan_have
            lbr     hf_insert           ; RD == 0: insert at the tail

hf_scan_have:
            ; current >= freed block's own address ? (insert before
            ; current if so)
            glo     r8
            str     r2
            glo     rd
            sm
            ghi     r8
            str     r2
            ghi     rd
            smb
            lbdf    hf_insert           ; DF=1: current >= freed
                                        ; block, insert here

            mov     rb, rd
            mov     rf, rd
            add16   rf, 2
            lda     rf
            phi     rd
            ldn     rf
            plo     rd
            lbr     hf_scan

hf_insert:
            ; freed block's own NEXT = current candidate (RD,
            ; possibly 0)
            mov     rf, r8
            add16   rf, 2
            ghi     rd
            str     rf
            inc     rf
            glo     rd
            str     rf

            ; link whatever pointed at RD (heap_free_head, or RB's
            ; own NEXT) to point at the freed block (R8) instead
            ghi     rb
            lbnz    hf_link_prev_nz
            glo     rb
            lbnz    hf_link_prev_nz
            mov     rf, heap_free_head
            ghi     r8
            str     rf
            inc     rf
            glo     r8
            str     rf
            lbr     hf_coalesce_fwd

hf_link_prev_nz:
            mov     rf, rb
            add16   rf, 2
            ghi     r8
            str     rf
            inc     rf
            glo     r8
            str     rf

hf_coalesce_fwd:
            ; does the freed block's own end address equal RD's own
            ; start address?
            ghi     rd
            lbnz    hf_coalesce_fwd_check
            glo     rd
            lbnz    hf_coalesce_fwd_check
            lbr     hf_coalesce_back    ; RD == 0: nothing follows,
                                        ; skip forward coalescing

hf_coalesce_fwd_check:
            mov     rf, r8
            add16   rf, 2
            add16   rf, r9              ; RF = freed block's own end
                                        ; address

            glo     rd
            str     r2
            glo     rf
            xor
            lbnz    hf_coalesce_back    ; low bytes differ: not
                                        ; adjacent
            ghi     rd
            str     r2
            ghi     rf
            xor
            lbnz    hf_coalesce_back

            ; adjacent -- merge RD into the freed block (R8): its
            ; SIZE grows by RD's own header + SIZE, and its NEXT
            ; becomes RD's own NEXT (RD disappears from the list
            ; entirely)
            mov     rf, rd
            lda     rf
            phi     ra
            ldn     rf
            plo     ra                  ; RA = RD's own SIZE
            add16   ra, 2
            add16   r9, ra              ; R9 = freed block's new,
                                        ; merged SIZE

            mov     rf, rd
            add16   rf, 2
            lda     rf
            phi     ra
            ldn     rf
            plo     ra                  ; RA = RD's own NEXT
            mov     rf, r8
            add16   rf, 2
            ghi     ra
            str     rf
            inc     rf
            glo     ra
            str     rf                  ; freed block's NEXT = RD's
                                        ; own NEXT

            mov     rf, r8
            ghi     r9
            str     rf
            inc     rf
            glo     r9
            str     rf                  ; freed block's SIZE updated

hf_coalesce_back:
            ghi     rb
            lbnz    hf_coalesce_back_check
            glo     rb
            lbnz    hf_coalesce_back_check
            rtn                         ; RB == 0: nothing precedes,
                                        ; done

hf_coalesce_back_check:
            mov     rf, rb
            lda     rf
            phi     ra
            ldn     rf
            plo     ra                  ; RA = RB's own SIZE
            mov     rf, rb
            add16   rf, 2
            add16   rf, ra              ; RF = RB's own end address

            glo     r8
            str     r2
            glo     rf
            xor
            lbnz    hf_done             ; low bytes differ: not
                                        ; adjacent
            ghi     r8
            str     r2
            ghi     rf
            xor
            lbnz    hf_done

            ; adjacent -- merge the freed block (R8, possibly already
            ; forward-merged) into RB: RB's SIZE grows, RB's NEXT
            ; becomes the freed block's own (possibly already
            ; updated) NEXT
            mov     rf, r8
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = freed block's own
                                        ; (possibly already merged)
                                        ; SIZE, reloaded fresh

            add16   r9, 2
            add16   ra, r9              ; RA = RB's new, merged SIZE

            mov     rf, r8
            add16   rf, 2
            lda     rf
            phi     r9
            ldn     rf
            plo     r9                  ; R9 = freed block's own NEXT
            mov     rf, rb
            add16   rf, 2
            ghi     r9
            str     rf
            inc     rf
            glo     r9
            str     rf                  ; RB's NEXT = freed block's
                                        ; own NEXT

            mov     rf, rb
            ghi     ra
            str     rf
            inc     rf
            glo     ra
            str     rf                  ; RB's SIZE updated

hf_done:
            rtn

            endp

; ----------------------------------------------------------------
; Data
; ----------------------------------------------------------------
            proc    _heap_malloc_data

heap_free_head: dw      0

                public  heap_free_head

            endp
