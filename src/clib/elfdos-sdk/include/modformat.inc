;
; modformat.inc - on-disk format constants for a relocatable dynamic
; module, shared between lib/modload.asm (the loader) and
; kernel/batch_mod.asm (the first real module). Restated on both sides
; rather than #included from one into the other, matching this
; project's own established convention for exactly this situation --
; see include/vollabel.inc/include/ymodem.inc for precedent.
;
; On-disk layout:
;   [6-byte header: magic(3) + version(1) + code_size(2, big-endian)]
;   [(code_size - MOD_HEADER_LEN) bytes: the module's own code+data,
;   picking up right where the header leaves off]
;   [2-byte fixup_count (big-endian)]
;   [fixup_count * 2-byte offsets (big-endian) -- see lib/modload.asm's
;   own header for the full "add the load base's high byte to exactly
;   one byte per entry" mechanism]
;
; code_size is Link/02's own "-m" convention (highest-lowest+1) -- the
; TOTAL linked content size, counted from address 0, which INCLUDES
; this 6-byte header itself (Link/02 has no way to know any particular
; caller's own header layout, so it always reports the whole span;
; every "-m" consumer's own loader is expected to subtract its own
; header length). Written directly into the output file by Link/02
; itself, not computable by the assembled source -- it's inherently
; self-referential (the module's own total size), and there's no
; "current address"/location-counter operator in this toolchain to
; express that in-source.
;
; A DISTINCT magic from Phase 1's 'BMD' (include/batchmod.inc) is used
; deliberately -- the on-disk FORMAT changed (Phase 1 has no code_size
; field, no trailing fixup table, and loads to a fixed address with no
; relocation at all), so a Phase-1-only loader must not misinterpret a
; Phase-2 file, and vice versa.
;

MOD_MAGIC0:     equ     'M'
MOD_MAGIC1:     equ     'D'
MOD_MAGIC2:     equ     '2'
MOD_VERSION:    equ     1

MOD_HEADER_LEN:     equ     6       ; magic(3) + version(1) + code_size(2)
MOD_SIZE_OFF:       equ     4       ; offset of the code_size field
                                    ; within the header

; MOD_RESERVE_PAD: extra bytes requested beyond code_size so the
; loader can always find a page-aligned (low byte $00) starting point
; within the reservation -- worst case wastes this many bytes, never
; more. See lib/modload.asm's own header for the full reasoning.
MOD_RESERVE_PAD:    equ     255

; mod_load's failure reasons, returned in D when DF=1 (2026-09-23).
; Numerically equal to include/kernel_api.inc's BATCH_ERR_NOMOD/BADMOD/
; NOMEM on purpose: kernel/batch.asm passes this D straight through as
; K_BATCH_START's own result. Change one set, change both.
MODLOAD_ERR_NOTFOUND: equ   2           ; the module file wouldn't open
MODLOAD_ERR_BAD:      equ   3           ; bad magic, truncated, I/O error
MODLOAD_ERR_NOMEM:    equ   4           ; not enough himem headroom
