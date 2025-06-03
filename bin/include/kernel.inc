O_CLDBOOT:    equ    0300h             ; jump to cold boot routine
O_WRMBOOT:    equ    0303h             ; jump to warm boot routine
O_OPEN:       equ    0306h             ; open a file
O_READ:       equ    0309h             ; read from file
O_WRITE:      equ    030ch             ; write to file
O_SEEK:       equ    030fh             ; seek to file position
O_CLOSE:      equ    0312h             ; close file
O_OPENDIR:    equ    0315h             ; open dir as a file
O_DELETE:     equ    0318h             ; delete a file
O_RENAME:     equ    031bh             ; rename a file
O_EXEC:       equ    031eh             ; execute an external program
O_MKDIR:      equ    0321h             ; make directory
O_CHDIR:      equ    0324h             ; change directory
O_RMDIR:      equ    0327h             ; remove directory
O_RDLUMP:     equ    032Ah             ; read LAT entry
O_RDLUMP32:   equ    040fh             ; read 32-bit LAT entry
O_WRLUMP:     equ    032Dh             ; write LAT entry
O_WRLUMP32:   equ    0421h             ; write LAT entry
O_TYPE:       equ    0330h             ; passthrough for console output
O_MSG:        equ    0333h             ; passthrough for console output
O_READKEY:    equ    0336h             ; passthrough for console input
O_INPUT:      equ    0339h             ; passthrough for console input
O_PRTSTAT:    equ    033ch             ; printer status
O_PRINT:      equ    033fh             ; output to printer
O_EXECBIN:    equ    0342h             ; execute from default directory
O_SETDEF:     equ    0345h             ; set/get default directory
O_KINIT:      equ    0348h             ; reserved - do not use!!!
O_INMSG:      equ    034bh             ; passthrough for console output
O_GETDEV:     equ    034eh             ; passthrough to f_getdef
O_GETTOD:     equ    0351h             ; passthrough to f_gettod
O_SETTOD:     equ    0354h             ; passthrough to f_settod
O_INPUTL:     equ    0357h             ; passthrough to f_inputl
O_BOOT:       equ    035ah             ; passthrough to f_boot
O_SETBD:      equ    0360h             ; passthrough to f_setbd
O_INITCALL:   equ    0363h             ; passthrough to f_initcall
O_BRKTEST:    equ    0366h             ; passthrough to f_brktest
O_DEVCTRL:    equ    0369h             ; Hook for device control drivers
O_ALLOC:      equ    036ch             ; passthrough to alloc
O_DEALLOC:    equ    036fh             ; passthrough to dealloc
O_TERMCTRL:   equ    0372h             ; Hook for terminal control drivers
O_NBREAD:     equ    0375h             ; passthrough to f_nbread
O_MEMBTRL:    equ    0378h             ; Hook for memory control drivers
O_LMPTOSEC:   equ    0409h             ; convert lump to sector
O_SECTOLMP:   equ    040ch             ; convert sector to lump
O_DIRENT:     equ    037Bh             ; get dirent for a file
O_RELSEC:     equ    0418h             ; find relative sector
O_TRUNC:      equ    046ah             ; Truncate file
O_VIDEO:      equ    0456h             ; video driver hook
D_IDERESET:   equ    0444h             ; passthrough to f_idereset
D_IDEREAD:    equ    0447h             ; passthrough to f_ideread
D_IDEWRITE:   equ    044Ah             ; passthrough to f_idewrite
D_REAPHEAP:   equ    044Dh             ; calls heap reaper to clean non-permanent heap blocks
D_SAVESYS:    equ    0459h             ; save system sector
D_DELCHAIN:   equ    0453h             ; delete an AU chain
D_ALLOCAU:    equ    045eh             ; allocate an AU
D_FREEDIRENT: equ    046dh             ; allocate a DIRENT
I_SERVE:      equ    03f6h             ; address of interrupt chain head
V_IVEC:       equ    03fdh             ; interrupt head
V_DVEC:       equ    036ah             ; device head
K_SYS_DTA:    equ    0100h             ; system sector DTA
K_VER:        equ    0400h             ; kernel version number
K_BUILD:      equ    0403h             ; kernel build number
K_BMONTH:     equ    0405h             ; kernel build month
K_BDAY:       equ    0406h             ; kernel build day
K_BYEAR:      equ    0407h             ; kernel build month
K_LASTSEC:    equ    042bh             ; sector currently in sys DTA
K_CWD_LUMP:   equ    0436h             ; lump for current directory
K_EXEC_AU:    equ    043Eh             ; executable starting AU
K_HIMEM:      equ    0442h             ; high memory pointer
K_LOWMEM:     equ    0465h             ; lowest memory heap can use
K_RETVAL:     equ    0467h             ; D on program exit
K_HEAP:       equ    0468h             ; heap pointer
K_CLKFREQ:    equ    0470h             ; system clock frequency
K_MONTH:      equ    0475h             ; date/time
K_DAY:        equ    0476h
K_YEAR:       equ    0477h
K_HOUR:       equ    0478h
K_MINUTE:     equ    0479h
K_SECOND:     equ    047ah
K_SECDEN:     equ    047bh
K_SECNUM:     equ    047dh


