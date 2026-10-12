;----------------------------------------------------------------------
; bios.inc - Elf/OS-compatible BIOS entry points used by ELF-DOS
;
; Copyright (C) 2026 Tony Hefner. Released under the Zero-Clause BSD
; license (see LICENSE): use it for anything, no conditions.
;
; Written for ELF-DOS. It lists only the entry points ELF-DOS itself
; calls, at the addresses the Elf/OS BIOS interface fixes for them:
; the standard vectors in page $FF00 and the extended vectors in page
; $F800, three bytes apart. Any BIOS that provides that interface
; works; nothing here depends on a particular one.
;
; Every entry is reached with CALL (SCRT) and returns with RTN. Call
; them -- never branch into them -- and rely only on the arguments and
; results noted here. A register not mentioned should be assumed
; destroyed unless you have checked the BIOS you are running on.
;
; Programs normally use the K_* calls in kernel_api.inc instead; the
; kernel routes console I/O through redirection and picks the right
; console port.
;----------------------------------------------------------------------

; --- Standard vectors ($FF00) ---

; Boot and system
f_boot:     equ     $FF00       ; boot from the BIOS's default disk
f_freemem:  equ     $FF57       ; RF = highest usable RAM address
f_getdev:   equ     $FF81       ; RF = bit map of devices present
f_setbd:    equ     $FF2D       ; detect/set the console baud rate

; Console
f_type:     equ     $FF03       ; print the character in D
f_tty:      equ     $FF4E       ; print the character in D
f_read:     equ     $FF06       ; wait for a key; D = character
f_msg:      equ     $FF09       ; print the NUL-ended string at RF
f_inmsg:    equ     $FF66       ; print the NUL-ended string that
                                ;  follows the CALL in the code
f_inputl:   equ     $FF69       ; read a line into the buffer at RF,
                                ;  at most RC characters

; Disk (R8.1 = unit, R8.0:R7 = sector number, RF = 512-byte buffer;
; DF = 1 on return means the operation failed)
f_idereset: equ     $FF36       ; reset the disk interface
f_ideread:  equ     $FF3C       ; read one sector
f_idewrite: equ     $FF39       ; write one sector

; Strings
f_strcmp:   equ     $FF12       ; compare strings at RF and RD;
                                ;  D = 0 if they are equal
f_strcpy:   equ     $FF18       ; copy the string at RF to RD
f_ltrim:    equ     $FF15       ; advance RF past leading spaces

; Numbers
f_mul16:    equ     $FF30       ; 16-bit multiply
f_div16:    equ     $FF33       ; 16-bit divide
f_atoi:     equ     $FF5D       ; decimal text at RF -> RD
f_uintout:  equ     $FF60       ; RD -> unsigned decimal text at RF
                                ;  (RF advanced, no NUL written)
f_hexout2:  equ     $FF48       ; RD.0 -> 2 hex digits at RF
f_hexout4:  equ     $FF4B       ; RD -> 4 hex digits at RF

; --- Extended vectors ($F800) ---

; Bit-banged serial port (the CPU's Q and EF lines)
f_bread:    equ     $F800       ; wait for a character; D = character
f_btype:    equ     $F803       ; send the character in D
f_btest:    equ     $F806       ; DF = 1 if a character is arriving

; Hardware UART
f_utype:    equ     $F809       ; send the character in D
f_uread:    equ     $F80C       ; wait for a character; D = character
f_utest:    equ     $F80F       ; DF = 1 if a character is waiting
f_usetbd:   equ     $F812       ; set the UART's baud rate and format

; Real-time clock (RF = 6 bytes: month, day, year-1972, hour, minute,
; second. Check f_getdev for a clock before relying on the result.)
f_gettod:   equ     $F815       ; read the date and time
f_settod:   equ     $F818       ; set the date and time
f_dttoas:   equ     $F827       ; date -> text
f_astodt:   equ     $F830       ; text -> date

; Disk information
f_idesize:  equ     $F821       ; size of an attached disk
