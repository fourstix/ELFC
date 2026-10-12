;
; fmt32.asm - format a 32-bit unsigned value as a comma-grouped decimal
; string
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/fmt32.prg) and
; linked alongside a program that wants it, the same way the kernel's
; own multi-file modules link together, and the same convention this
; project's other lib/ modules already use. A calling program declares
; "extrn fmt_size32" and calls it like any other routine.
;
; Factored out of progs/dir.asm (2026-07-26, at the user's own
; suggestion) so progs/stat.asm -- and any future program -- can share
; the exact same, already-verified conversion instead of duplicating
; it. dir.asm was the first, and remains the most thoroughly verified,
; caller: see its own git history / CLAUDE.md for the full
; verification record (a plain-Python numeric model against Python's
; own f"{v:,}" formatting, a from-scratch mechanical mock-1802
; simulator executing the literal instruction sequence, and a manual
; re-trace that caught a real bug neither simulation did -- R9's own
; high byte being read as part of a 16-bit ADD16 array index without
; ever having been explicitly zeroed). That fix (the "ldi 0 / phi r9"
; right before the digit-reassembly loop) is preserved here unchanged.
;
; No kernel/BIOS primitive is called anywhere in this file, so none of
; this project's "does a register survive a call" gotchas apply to a
; caller using it -- ordinary register-clobber rules only.
;

#include    include/opcodes.def

; ----------------------------------------------------------------
; fmt_size32: format a 32-bit unsigned value as a right-justifiable,
; comma-grouped decimal string (e.g. 4294967295 -> "4,294,967,295",
; the largest 32-bit value, exactly 13 characters -- 10 digits + 3
; commas). Does NOT right-justify or print anything itself -- purely a
; buffer-filling conversion; the caller decides how (or whether) to
; pad/print the result, matching how f_uintout itself already works.
;
; Two passes: (1) repeatedly divide by 10 (no native divide on the
; 1802 -- see _div32_by10 below), extracting decimal digits least-
; significant first into raw_digits; (2) walk raw_digits backward
; (most significant first) into the caller's buffer, inserting a comma
; after digit i (i = position counted from the right, 0 = least
; significant) whenever i > 0 and i is a multiple of 3 -- looked up via
; mod3_table rather than computed, since i only ever ranges 0-9. This
; rule is independent of the total digit count K, including when the
; leftmost group has fewer than 3 digits.
;
; Args:    RD:R8 = 32-bit value (RD = high word, R8 = low word)
;          RF = destination buffer (caller-owned, must be at least 14
;          bytes: max "4,294,967,295" = 13 chars + null)
; Returns: the buffer filled and null-terminated
; Modifies: everything (R7-RD)
; ----------------------------------------------------------------
            extrn   _div32_by10
            extrn   raw_digits
            extrn   mod3_table

            proc    fmt_size32

            ; REAL BUG, caught before ever reaching hardware: this
            ; used to stash the caller's destination buffer in R7 --
            ; but _div32_by10 (called repeatedly, inside the loop
            ; right below) documents R7 as one of its OWN clobbered
            ; registers (its 32-iteration loop counter, ending at 0
            ; every time it returns), so by the time this buffer
            ; pointer was needed again below, it no longer held the
            ; caller's real address. Caught by re-checking every
            ; register this routine holds a value in against
            ; _div32_by10's own documented Modifies list -- exactly
            ; the discipline this project's gotcha #10 already
            ; established, self-inflicted here while refactoring code
            ; that (in its original, single-caller form in
            ; progs/dir.asm) never needed to stash a caller-supplied
            ; buffer pointer across this call at all. RB is untouched
            ; by both this routine's own logic and _div32_by10.
            mov     rb, rf              ; RB = caller's destination
                                        ; buffer (stashed -- RF is
                                        ; needed as scratch below)
            mov     rf, raw_digits
            ldi     0
            plo     rc                  ; RC.0 = digit count (K)

fsz_extract_loop:
            ghi     rd
            lbnz    fsz_extract_have_value
            glo     rd
            lbnz    fsz_extract_have_value
            ghi     r8
            lbnz    fsz_extract_have_value
            glo     r8
            lbnz    fsz_extract_have_value
            ; value is 0 here
            glo     rc
            lbnz    fsz_extract_done   ; already have digits and the
                                        ; value is now 0: stop (avoids
                                        ; leading zeros)
            ; value started at 0 (K==0 still): fall through to emit
            ; the single '0' digit

fsz_extract_have_value:
            call    _div32_by10        ; RD:R8 = quotient, R9.0 = remainder
            glo     r9
            adi     '0'
            str     rf
            inc     rf                  ; raw_digits[K] = ASCII digit
            glo     rc
            adi     1
            plo     rc                  ; K += 1
            lbr     fsz_extract_loop

fsz_extract_done:
            ; RC.0 = K (1-10); raw_digits[0..K-1] holds the digits,
            ; least-significant first

            mov     rf, rb              ; RF = caller's destination
                                        ; buffer (write cursor)
            glo     rc
            smi     1
            plo     r9                  ; R9.0 = i, starts at K-1 (the
                                        ; most significant digit's
                                        ; right-indexed position)
            ldi     0
            phi     r9                  ; R9.1 = 0 -- REAL BUG, found
                                        ; via a manual re-trace after
                                        ; two independent simulations
                                        ; both missed it (see this
                                        ; file's own header comment):
                                        ; R9's high byte is never
                                        ; written anywhere else in this
                                        ; routine, so without this it
                                        ; holds whatever garbage was
                                        ; left over from elsewhere in
                                        ; the calling program, and the
                                        ; "add16 r8, r9" calls below
                                        ; use R9 as a FULL 16-bit
                                        ; value -- a nonzero garbage
                                        ; high byte computes a wild,
                                        ; out-of-bounds array index
                                        ; instead of the small 0-9
                                        ; index intended.

fsz_build_loop:
            mov     r8, raw_digits
            add16   r8, r9              ; safe: r9 is always 0-9 here
            ldn     r8
            str     rf
            inc     rf                  ; append raw_digits[i]

            glo     r9
            lbz     fsz_build_done      ; i==0: just printed the least
                                        ; significant digit -- stop,
                                        ; no trailing comma

            mov     r8, mod3_table
            add16   r8, r9
            ldn     r8
            lbnz    fsz_build_next      ; mod3_table[i] != 0: no comma
            ldi     ','
            str     rf
            inc     rf

fsz_build_next:
            glo     r9
            smi     1
            plo     r9
            lbr     fsz_build_loop

fsz_build_done:
            ldi     0
            str     rf                  ; null-terminate
            rtn

            endp

; ----------------------------------------------------------------
; fmt_uint32: format a 32-bit unsigned value as plain decimal digits,
; with no commas and no leading zeros (0 -> "0", 4294967295 ->
; "4294967295"). The same digit extraction as fmt_size32 above; only
; the reassembly differs. Added 2026-09-11 for LESS -N's line numbers.
;
; Args:    RD:R8 = 32-bit value (RD = high word, R8 = low word)
;          RF = destination buffer, at least 11 bytes
; Returns: the buffer filled and null-terminated
; Modifies: R7, R8, R9, RB, RC, RD, RF
; ----------------------------------------------------------------
            proc    fmt_uint32

            mov     rb, rf              ; RB = destination -- not touched
                                        ; by _div32_by10 (R7/R9/RD:R8)
            mov     rf, raw_digits
            ldi     0
            plo     rc                  ; RC.0 = digit count

fu_extract:
            ghi     rd
            lbnz    fu_have_value
            glo     rd
            lbnz    fu_have_value
            ghi     r8
            lbnz    fu_have_value
            glo     r8
            lbnz    fu_have_value
            glo     rc
            lbnz    fu_extract_done     ; value used up: stop
                                        ; (a value of 0 falls through
                                        ; once, for its single '0')
fu_have_value:
            call    _div32_by10         ; RD:R8 = quotient, R9.0 = digit
            glo     r9
            adi     '0'
            str     rf
            inc     rf                  ; raw_digits[count] = digit
            glo     rc
            adi     1
            plo     rc
            lbr     fu_extract

fu_extract_done:
            ; RF = raw_digits + count; the digits are least significant
            ; first, so copy them out backward
            mov     r8, rb              ; R8 = write cursor
fu_copy:
            dec     rf
            ldn     rf
            str     r8
            inc     r8
            glo     rc
            smi     1
            plo     rc
            lbnz    fu_copy
            ldi     0
            str     r8                  ; null-terminate
            rtn

            endp

; ----------------------------------------------------------------
; _div32_by10: divide a 32-bit value by 10 in place. No native divide
; on the 1802 -- standard "restoring division" via 32 bit-shifts: each
; iteration shifts the dividend left by 1 (low byte first, carry
; chained up through the high byte via SHL then SHLC/SHLC/SHLC), the
; bit that falls off the very top (bit 31) feeds into a small
; remainder accumulator; whenever that accumulator reaches 10 or more,
; 10 is subtracted back out and the dividend's own just-vacated LSB
; (bit 0, freshly shifted in as 0) is set to 1 -- that bit becomes the
; quotient bit for this position. After 32 iterations the dividend
; register holds the quotient in place, and the final accumulator
; value is the remainder (0-9).
;
; Args:    RD:R8 = dividend (RD = high word, R8 = low word)
; Returns: RD:R8 = quotient (in place), R9.0 = remainder (0-9)
; Modifies: R7, R9 (and RD:R8, which are also the return value)
; ----------------------------------------------------------------
            proc    _div32_by10

            ldi     32
            plo     r7                  ; R7.0 = iteration count
            ldi     0
            plo     r9                  ; R9.0 = remainder accumulator

d32_loop:
            glo     r7
            lbz     d32_done

            glo     r8
            shl
            plo     r8
            ghi     r8
            shlc
            phi     r8
            glo     rd
            shlc
            plo     rd
            ghi     rd
            shlc
            phi     rd                  ; DF = bit that fell off bit31

            glo     r9                  ; remainder = (remainder<<1)|DF
            shlc                        ; -- DF here is still the one
            plo     r9                  ; from the shlc above, nothing
                                        ; in between touched it

            glo     r9
            smi     10
            lbnf    d32_no_sub          ; remainder < 10: no
                                        ; subtraction needed

            plo     r9                  ; remainder -= 10 (D already
                                        ; holds this from the smi above)
            glo     r8
            ori     1
            plo     r8                  ; set the quotient bit for
                                        ; this position

d32_no_sub:
            dec     r7
            lbr     d32_loop
d32_done:
            rtn

            endp

; ----------------------------------------------------------------
; Data
; ----------------------------------------------------------------
            proc    _fmt32_data

raw_digits: ds      10                  ; up to 10 extracted decimal
                                        ; digits, least-significant
                                        ; first
mod3_table: db      0,1,2,0,1,2,0,1,2,0 ; mod3_table[i] = i mod 3, for
                                        ; i=0-9 -- a lookup rather than
                                        ; a computed modulo, since i
                                        ; only ever ranges that far

                public  raw_digits
                public  mod3_table

            endp
