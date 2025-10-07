;--------------------------------------------------------------------
; Elf/OS and Mini/DOS Kernel API
;--------------------------------------------------------------------

O_OPEN:       equ    0306h             ; open a file
O_READ:       equ    0309h             ; read from file
O_WRITE:      equ    030ch             ; write to file
O_SEEK:       equ    030fh             ; seek to file position
O_CLOSE:      equ    0312h             ; close file
O_DELETE:     equ    0318h             ; delete a file
O_RENAME:     equ    031bh             ; rename a file
O_TYPE:       equ    0330h             ; console character output
O_MSG:        equ    0333h             ; console string output
O_READKEY:    equ    0336h             ; console character input
O_INPUT:      equ    0339h             ; console string input
O_INMSG:      equ    034bh             ; console inline messae output
O_GETDEV:     equ    034eh             ; get device information
O_GETTOD:     equ    0351h             ; get time of day
O_ALLOC:      equ    036ch             ; alloc memory block
O_DEALLOC:    equ    036fh             ; dealloc memory block

;--------------------------------------------------------------------
; Elf/OS and Mini/DOS Data Locations
;--------------------------------------------------------------------

K_KEYBUF:     equ    0080h             ; input key buffer
K_MONTH:      equ    0475h             ; date/time information

;-------------------------- end os_api.inc --------------------------
