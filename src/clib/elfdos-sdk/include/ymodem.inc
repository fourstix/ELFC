;
; ymodem.inc - YMODEM-CRC protocol constants shared by progs/yr.asm and
; progs/ys.asm. Restated (not #included from lib/ymodem.asm) matching
; this project's own established convention for small shared constant
; sets -- see include/vollabel.inc/include/file_glob.inc for precedent.
;

; restated from lib/ymodem.asm's own equ's -- an equ is a pure
; assemble-time constant, not a real linked symbol, so it can't be
; extrn'd across files the way ym_io_mode (real memory) can; matches
; this project's own established restated-constant convention (e.g.
; BPBBLK_* between kernel.inc/kernel_api.inc). Renumbered 2026-09-01
; when a third mode (CONSOLE, via K_READ/K_TYPE) became the default --
; see lib/ymodem.asm's own header comment for the full device-
; selection design; keep this file in sync with lib/ymodem.asm if it
; ever changes again.
YM_IO_CONSOLE:  equ     0       ; call K_READ/K_TYPE (default)
YM_IO_UART:     equ     1       ; call f_uread/f_utype directly
YM_IO_BITBANG:  equ     2       ; call f_bread/f_btype directly

YM_SOH:     equ     $01     ; 128-byte block follows
YM_STX:     equ     $02     ; 1024-byte block follows ("-k" mode)
YM_EOT:     equ     $04     ; end of this file's data
YM_ACK:     equ     $06     ; positive acknowledge
YM_NAK:     equ     $15     ; negative acknowledge / retransmit please
YM_CAN:     equ     $18     ; cancel (sent by either end to abort)
YM_C:       equ     $43     ; 'C' -- CRC-mode probe, sent by the receiver

YM_BLKLEN_128:  equ     128
YM_BLKLEN_1024: equ     1024

; Retry/timeout policy -- see lib/ymodem.asm's own header comment for
; why these can only be real, polled timeouts in UART (-u) mode; bit-
; bang (-b) mode has no non-blocking "byte waiting" primitive at all,
; so ym_getbyte_timeout just blocks there regardless of these budgets.
; YM_POLL_BUDGET is an iteration count, not a calibrated wall-clock
; time.
;
; YM_HANDSHAKE_TRIES raised 15->255 (2026-09-06), the real fix for a
; hardware-found bug: with a real human driving a terminal program's
; own upload menu (e.g. minicom's Ctrl-A/S -> ymodem -> select file),
; there's a genuine 5-15+ second gap between starting YR and the
; sender actually beginning to transmit -- confirmed by the user's own
; timing report. The OLD 15-try handshake window (no longer padded out
; by per-iteration diagnostic printing, once that was all stripped
; out this same session) apparently completes in well under that real-
; world delay, so YR gave up, printed "Transfer completed with
; errors." and returned to the shell -- and since the console and the
; transfer share the same physical wire by default, both that message
; and the shell's own next prompt leaked onto the wire right as
; minicom's sender was finally starting, confusing it (matches the
; user's own report exactly: minicom's "Got 54 for sector ACK" is
; 0x54='T', the first byte of "Transfer..."; "Got 3a for sector ACK"
; is 0x3A=':', the second byte of the shell's own "C:/> " prompt).
; 255 is the maximum representable in the single-byte "ldi
; YM_HANDSHAKE_TRIES" load every use site does -- raising it further
; would need code changes (a 16-bit counter), not just this constant.
; This is a real ~17x increase in the total handshake window with
; ZERO change to how often a 'C' probe is actually sent (YM_POLL_BUDGET
; is unchanged), so a sender that's already listening sees probes at
; exactly the same cadence as before -- only genuinely patient waiting
; for a slow-to-start human is extended. Strictly safe for YS's own
; already-hardware-confirmed behavior too: a real early success still
; exits this loop immediately regardless of how high the ceiling is.
YM_POLL_BUDGET:     equ     20000       ; per-attempt poll budget
YM_HANDSHAKE_TRIES: equ     255         ; times to (re)send 'C' before
                                        ; giving up on a file/batch --
                                        ; max representable via a
                                        ; single-byte ldi (see above)
YM_BLOCK_TRIES:     equ     10          ; times to NAK-and-retry one
                                        ; bad data block before giving up
