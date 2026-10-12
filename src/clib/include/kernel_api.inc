;
; kernel_api.inc - ELF-DOS kernel API jump table addresses
;
; #include this file in any program built to run under ELF-DOS
; (loaded via prog_load to PROG_BASE) to call kernel and BIOS
; functionality without depending on the kernel's internal layout,
; which shifts across kernel builds/versions.
;
; The table itself lives at a fixed address ($0106, the same address
; the boot chain has always jumped to) in kernel/kernel.asm. Each
; slot is a 3-byte 'lbr' to the real routine. Once this project
; releases, these addresses become a stable contract (new entries only
; ever APPENDED, never reordered or removed, so a program built
; against an older kernel keeps working after a rebuild) -- but until
; then, EVERY program in this repo is rebuilt from source on every
; `make progs`, so nothing external depends on today's addresses.
; 2026-07-13's pre-release cleanup pass (removing K_BPB_INIT/
; K_PROG_LOAD/K_PROG_EXEC, adding K_SHELL_INIT/K_GETSHELLDRIVE, and
; renumbering the whole table sequentially rather than leaving gaps)
; deliberately used this last mutable window; don't repeat that kind
; of full renumber after release.
;
; A SECOND renumbering pass happened 2026-08-26 (removing K_INPUTL/
; K_SETBD/K_GLOB_RESERVE, three genuinely dead slots found by a full-
; repo audit -- see each one's own removal note further down for why).
; Still within the same "not actually released" window this header's
; own rule describes: KERNEL_VER was bumped to 1.0.0 back on
; 2026-08-01, but never actually tagged or released to anyone, and
; every external program in existence is the user's own, rebuilt from
; source on every `make progs` regardless -- confirmed directly with
; the user before doing this, not assumed. The SAME "don't repeat a
; full renumber after release" rule still applies going forward from
; here; this note exists so a future reader knows the table has moved
; twice, not that the rule above was violated.
;
; Calling convention for every slot: identical to the real routine it
; forwards to (see kernel/file.asm, kernel/dir.asm, kernel/loader.asm,
; and include/bios.inc for each routine's args/returns/clobbers).
; Call like any other subroutine, e.g.:
;   ldi     0
;   call    K_FILE_OPEN
;
; K_INIT (slot 0, $0106) is the kernel's own boot entry, pinned here
; by the boot chain itself -- it is not meant to be called by
; programs (calling it would re-run kernel boot init while a program
; is already running).
;
; Command line: at program entry, RA holds a pointer to the argument
; table (argv) and RC holds the argument count (argc). argv is an
; array of RC 16-bit big-endian pointers, argv[0..argc-1], each
; pointing to a null-terminated string. argv[0] is the program's own
; invocation name (matching real C's main(argc, argv) convention, so
; the eventual ELFC C startup code needs no special-casing); argc is
; therefore always >= 1 on a successful hand-off. Arguments are
; tokenized by the shell with quoting ("..." keeps embedded spaces in
; one token) and backslash-escaping (\X produces a literal X, inside or
; outside quotes -- covers \" for a literal quote, \\ for a literal
; backslash, and \<space> for a literal space in an unquoted token).
;
; Both RA and RC are passed in registers rather than fixed addresses
; since they're only needed once, at entry -- unlike mem_base/mem_top
; below, which a program may need to consult at any point during its
; run (e.g. from within a heap allocator), and so use a fixed address
; instead. Like any register, neither is guaranteed to survive a
; kernel/BIOS call -- stash to memory (or another register) immediately
; if either is needed after the first such call (see
; progs/template.asm's own header comment for the canonical example).
;
; This file is deliberately independent of kernel.inc (which is for
; the kernel's own internal structures -- FCB/BPB/directory-entry
; layout, etc.) so that program code never has a reason to reach into
; kernel internals that could change across kernel updates. PROG_BASE
; and LOADER_ARGS are restated below rather than shared by #include;
; keep them in sync with kernel.inc if they ever change.
;

PROG_BASE:      equ     $0D00       ; user programs load here (see kernel.inc;
                                    ; moved $4400->$4200->$4100->$4000
                                    ; (2026-08-25, 2026-08-26 x2) as
                                    ; successive kernel size-reduction
                                    ; passes freed real margin back; see
                                    ; kernel.inc's own PROG_BASE comment
                                    ; for the full history)
LOADER_ARGS:    equ     PROG_BASE-4 ; word 0 = mem_base, word 1 = mem_top

; LINE_BUF/RUN_ARGC/RUN_ARGV_TABLE/RUN_PATH: the shell-as-a-program
; handoff protocol (see kernel.inc's own copy of this comment for the
; full reasoning). Only progs/shell.asm has a real reason to touch
; these -- ordinary programs should not, and never reference them by
; name; they only ever see the RA/RC register values built from them
; at entry (see the "Command line" section above) -- but they're
; restated here rather than given a separate include file, matching
; this file's existing precedent for PROG_BASE/LOADER_ARGS.
LINE_BUF:       equ     $0080       ; shell command input buffer (128 bytes)
RUN_ARGC:       equ     PROG_BASE-6     ; word: argument count
RUN_ARGV_TABLE: equ     PROG_BASE-38    ; ARGV_MAX_ARGS 2-byte pointers,
                                        ; argv[0..argc-1]
ARGV_MAX_ARGS:  equ     16              ; RUN_ARGV_TABLE's own capacity
RUN_PATH:       equ     PROG_BASE-102   ; 64-byte buffer: resolved path
                                        ; to load next
RUN_PATH_LEN:   equ     64              ; RUN_PATH's own size, for
                                        ; bounds-checking writes to it

; RUN_REDIR_OUT/RUN_REDIR_OUT_APPEND/RUN_REDIR_IN: I/O redirection relay
; -- same mechanism as RUN_PATH above (kernel/shell-internal only, see
; kernel.inc's own copy of this comment for the full reasoning). Each is
; a pointer into LINE_BUF (not a copied buffer), 0 = no redirect of that
; kind.
RUN_REDIR_OUT:      equ     PROG_BASE-105
RUN_REDIR_OUT_APPEND: equ   PROG_BASE-106
RUN_REDIR_IN:       equ     PROG_BASE-108

; RUN_BATCH_ECHO_OFF: persistent "suppress batch line echo" mode (real
; MS-DOS "ECHO OFF" semantics) -- unlike RUN_REDIR_OUT/IN above, NOT
; reset every command cycle, only when a new batch starts (see
; kernel.inc's own copy of this comment for the full reasoning).
; progs/echo.asm writes it directly for ECHO ON/OFF; a bare ECHO reads
; it to report the current state.
RUN_BATCH_ECHO_OFF: equ     PROG_BASE-109   ; byte: 0 = echo batch lines
                                            ; normally, nonzero = suppress

; RUN_ERRORLEVEL: the last command's exit code (see kernel.inc's own
; copy of this comment for the full reasoning) -- kernel/shell-internal
; only, same as RUN_PATH/RUN_ARGC above. Ordinary programs should use
; K_GET_ERRORLEVEL below instead of referencing this fixed address
; directly.
RUN_ERRORLEVEL:     equ     PROG_BASE-110   ; byte: last command's exit
                                            ; code (0-255)

; IO_TYPE_TARGET/IO_READ_TARGET: the real console I/O routine's address,
; auto-detected once at boot (see kernel.inc's own copy of this comment
; for the full mBIOS-vs-classic-BIOS detection reasoning, and for the
; Phase 2 self-modifying-K_TYPE/K_READ-vector redesign that changed who
; reads these -- now only kernel/redir.asm's _redir_teardown, once per
; redirected command, not every console call). Kernel/boot-internal
; only, same as RUN_PATH/RUN_ERRORLEVEL above -- restated here only
; because boot/krnboot.asm (which writes these) is a separate link unit
; from kernel.bin and needs a fixed address to reach them either way; no
; ordinary program has any reason to reference these directly.
IO_READ_TARGET:     equ     PROG_BASE-112   ; word: real f_uread/f_bread
IO_TYPE_TARGET:     equ     PROG_BASE-114   ; word: real f_utype/f_btype

; BOOT_UNIT: the block device unit the system booted from (0-7), which
; is where C:-F: live. Written by boot/krnboot.asm at boot. Programs
; that act on the boot device (SYS, KSAVE) use it as their default unit.
BOOT_UNIT:          equ     PROG_BASE-115   ; byte: boot block device unit

; K_GET_ERRORLEVEL: read the last command's exit code. A real jump-table
; call rather than a direct RUN_ERRORLEVEL read, unlike the shell's own
; internal access -- an ordinary program shouldn't bake a kernel/shell-
; internal relay address into its own compiled binary (the same mistake
; the argv/argc ABI redesign already moved away from).
; Args:    none
; Returns: D = the last command's exit code (0-255), DF = 0 always
K_GET_ERRORLEVEL: equ   $0173       ; -> kernel_get_errorlevel

K_INIT:         equ     $0106       ; reserved -- kernel boot entry, do not call

; FCB_LEN/FCB_IOBUF_LEN: sizes only, not the field layout (which stays
; kernel-internal, see kernel.inc's own FCB_* offsets) -- same
; "publish a size, not the struct" precedent as DIRENT_LEN below.
; CALLER-ALLOCATED FCBs (2026-07-15), FCB POINTER IS THE HANDLE
; (2026-07-21): a program declares its own `ds FCB_LEN` (the FCB
; itself) and `ds FCB_IOBUF_LEN` (that FCB's own private 512-byte
; sector buffer) per file it wants open at once, and passes both
; pointers to K_FILE_OPEN. K_FILE_CLOSE/K_FILE_READ/K_FILE_WRITE/
; K_FILE_SEEK all take that same FCB pointer directly (in RD) on every
; call -- there is no separate small-integer "handle" anymore, and no
; kernel-imposed limit on how many files can be open at once (only
; available RAM, since each FCB lives in the caller's own memory).
; K_FILE_OPEN itself no longer returns anything meaningful in D on
; success -- the caller already has the FCB pointer they passed in.
;
; *** AN FCB MUST NOT STRADDLE A 256-BYTE PAGE BOUNDARY. ***
; The kernel reaches an FCB's fields by adding a field offset to the
; LOW BYTE of the FCB pointer alone, so an FCB split across a page
; would have its upper fields read from the wrong page. K_FILE_OPEN
; REJECTS a straddling FCB -- it returns DF=1 before touching any of
; its own state, so the open fails cleanly at the first call instead
; of corrupting memory for the life of the file. There is no distinct
; error message: it looks like any other failed open, it happens at
; RUN time, and only on the builds where the address happens to land
; badly. Declare every FCB 32-aligned and it can never happen:
;
;   ; flat file (no proc): align the label directly
;   .align  32
;   my_fcb:     ds      FCB_LEN
;   my_iobuf:   ds      FCB_IOBUF_LEN
;
;   ; inside a proc: align the PROC BASE, and keep the FCB(s) first.
;   ; ".link .align" moves the proc's base address, which only aligns
;   ; a label while nothing has been emitted yet -- Link/02 refuses it
;   ; anywhere else in a proc. Several FCBs may share one aligned proc
;   ; as long as they are adjacent and FIRST (offsets 0, 32, 64 ...).
;               proc    _my_data
;               .link   .align 32
;   my_fcb:     ds      FCB_LEN
;   my_fcb2:    ds      FCB_LEN
;   ; ... everything else after
;
; An FCB carved out of a heap or himem reservation at run time must be
; aligned by the CALLER (round the returned pointer up to a multiple
; of 32); nothing checks it for you until K_FILE_OPEN refuses it.
FCB_LEN:        equ     32
FCB_IOBUF_LEN:  equ     512

; ---- ELF-DOS kernel calls (see kernel/file.asm, kernel/dir.asm, kernel/loader.asm) ----
; K_FILE_OPEN:  Args: RF = path, D = mode (0=read, 1=read/write),
;               RD = pointer to caller's FCB_LEN-byte FCB (need not be
;               pre-zeroed -- file_open initializes every field),
;               RA = pointer to caller's FCB_IOBUF_LEN-byte I/O buffer.
;               Returns: DF = 0/1 (D is unspecified on return -- the
;               caller already has the FCB pointer they passed in).
; K_FILE_CLOSE: Args: RD = FCB pointer (the same one passed to
;               K_FILE_OPEN). Returns: DF = 0/1.
; K_FILE_SEEK (2026-07-20, register ABI changed 2026-07-21, full
;               32-bit range enabled 2026-07-26): Args: RD = FCB
;               pointer, RC.0 = whence (0 = SEEK_SET, absolute from
;               start; 1 = SEEK_CUR, relative to current position;
;               2 = SEEK_END, relative to end of file), RA:R9 = 32-bit
;               signed offset (RA = high word, R9 = low word -- R9,
;               not RD, since RD now carries the FCB pointer). The
;               full signed 32-bit range is accepted; file positions
;               and sizes are likewise supported up to the full 32
;               bits FCB_FSIZE/FCB_FPOS hold.
;               Returns: DF = 0 on success (RA:RD = the resulting
;               absolute 32-bit position; RA = high word, RD = low
;               word. Widened 2026-09-08 -- RD alone used to be the
;               whole answer, which left the size of any file over 64K
;               unobtainable from a SEEK_END. Additive and safe: RA is
;               an argument in, and was already documented as
;               destroyed, so no existing caller could rely on it),
;               DF = 1 on error (bad whence, offset would
;               place the position outside [0, filesize], or an I/O
;               error occurred walking the cluster chain); on any
;               error the file position is left unchanged.
; K_FILE_READ/K_FILE_WRITE: Args: RD = FCB pointer, RF = data buffer,
;               RC = byte count. Returns: RC = bytes actually
;               transferred (read only), DF = 0/1.
K_FILE_OPEN:    equ     $0109
K_FILE_CLOSE:   equ     $010C
K_FILE_READ:    equ     $010F
K_FILE_WRITE:   equ     $0112
K_FILE_SEEK:    equ     $0115
K_DIR_OPEN:     equ     $0118
K_DIR_READ:     equ     $011B

; K_DIR_SAVE_STATE/K_DIR_RESTORE_STATE: snapshot/restore the directory
; iterator's own scan position (2026-07-27), so a caller can pause a
; K_DIR_OPEN/K_DIR_READ scan across other, unrelated kernel directory
; operations (K_STAT, K_FILE_OPEN, etc.) and later resume it exactly
; where it left off -- K_DIR_OPEN/K_DIR_READ share ONE kernel-resident
; scan position, so without this, a caller wanting to interleave a
; multi-call scan with other directory activity would have no choice
; but to re-scan from the start each time (see lib/file_glob.asm's
; glob_next, the motivating use case: iterating wildcard matches one
; at a time while the caller processes each match in between calls).
;
; K_DIR_SAVE_STATE:
;   Args:    RF = pointer to a caller-owned DIR_STATE_LEN-byte buffer
;   Returns: nothing (buffer filled)
; K_DIR_RESTORE_STATE:
;   Args:    RF = pointer to a DIR_STATE_LEN-byte buffer previously
;            filled by K_DIR_SAVE_STATE
;   Returns: DF = 0 on success (the next K_DIR_READ call resumes
;            exactly where the snapshot was taken); DF = 1 if the
;            disk re-read needed to restore the current sector failed
;            -- treat as a hard I/O error, same as any other failed
;            K_DIR_READ
K_DIR_SAVE_STATE:    equ     $017F
K_DIR_RESTORE_STATE: equ     $0182

; DIR_STATE_LEN: size of the K_DIR_SAVE_STATE/K_DIR_RESTORE_STATE
; snapshot buffer, restated from kernel.inc for any program that needs
; to declare one (a plain `ds DIR_STATE_LEN`, opaque -- same "publish
; a size, not the struct" precedent as FCB_LEN/DIRENT_LEN above).
DIR_STATE_LEN:  equ     9

; K_PROG_LOAD/K_PROG_EXEC: REMOVED 2026-07-13 (pre-release jump-table
; cleanup). Neither could ever be safely called by a program while it
; was running -- loading a second program to PROG_BASE overwrites the
; caller's own currently-executing code, the exact constraint that
; already forced the shell hand-off protocol (RUN_PATH/RUN_ARGC/
; RUN_ARGV_TABLE) in the first place. Confirmed via repo-wide grep that the only
; callers were kernel.asm's own run_loop, via direct same-link-unit
; calls, never through this table. Collapsed internally into a single
; kernel-private routine (prog_run, kernel/loader.asm) with no
; jump-table exposure at all, since nothing external could ever call
; it. Safe to remove outright (not just leave a stub) because nothing
; in this repo depends on today's addresses yet -- see K_BPB_INIT's
; own removal note below for the same reasoning. (See the "BIOS
; passthroughs" section further down for K_TYPE through K_READ, which
; now start at $011E, immediately after K_DIR_READ, instead of $0124.)

; K_GETCURDIR/K_SETCURDIR/K_SETDRIVE/K_GETSHELLDRIVE: multi-drive
; current-directory state (2026-07-13). Classic MS-DOS semantics,
; adopted deliberately: CD-style directory changes and drive switches
; are two separate operations. K_SETCURDIR sets a given drive's OWN
; remembered directory and never changes which drive is active --
; "CD D:\games" while C: is active updates D's directory without
; switching to it. The ONLY way the active drive itself changes is
; K_SETDRIVE, which the shell calls directly from a bare "C:"/"D:"/
; "E:"/"F:" command line (see progs/shell.asm) -- never from CD.
;
; K_GETCURDIR: no args.
;   Returns: RD = the ACTIVE drive's current directory cluster
;            (0 = that drive's root), D = cur_drive (0-3, 0=C..3=F)
; K_SETCURDIR: Args: D = drive index (0-3), RD = new directory
;   cluster for THAT drive. Returns: nothing. Does not touch which
;   drive is active, even if D != the active drive.
; K_SETDRIVE: Args: D = drive index (0-3) to make active.
;   Returns: DF = 0 on success, DF = 1 if that drive has no mounted
;   partition (drive_present[D]=0) -- nothing changes in that case.
; K_GETSHELLDRIVE: no args. Returns: D = shell_drive (0-3), the drive
;   the shell binary itself was found on at boot (see K_SHELL_INIT
;   below) -- almost always 0 (C:) in practice. Used by progs/shell.asm
;   to build a fallback "<shell_drive>:/bin/<name>" candidate when a
;   bare command name isn't found on the active drive, so ordinary
;   commands work from any drive without needing /bin duplicated
;   everywhere.
K_GETCURDIR:    equ     $0136
K_SETCURDIR:    equ     $0139
K_SETDRIVE:     equ     $013C
K_GETSHELLDRIVE: equ    $013F

; K_PATH_RESOLVE: resolve a '/'-separated path, optionally prefixed
; with a drive letter, to (parent directory cluster, final path
; component, resolved drive). An optional 2-character "X:" prefix
; (C:-F:, case-insensitive) names the target drive; absent, the
; target drive is cur_drive. After any prefix, a leading '/' resolves
; from that drive's FAT16 root; otherwise resolution starts from that
; drive's OWN remembered current directory (drive_cur_dir[target] --
; NOT necessarily the active drive's directory, per the K_SETCURDIR
; semantics above). Internally switches the active BPB/FAT-cache to
; the target drive (see _switch_drive, kernel-internal) before doing
; any lookup that depends on it -- a no-op if that drive is already
; active. Every component except the last is looked up as a directory
; ('.' and '..' work automatically -- real FAT entries, no special-
; casing needed); the last component is NOT looked up here -- the
; caller decides what to do with it (e.g. search for a file vs. a
; directory).
;
; Args:    RF = pointer to null-terminated path string (not modified)
; Returns: RD = resolved parent directory cluster
;          RF = pointer to the final path component, null-terminated.
;               Points into kernel scratch memory -- same convention
;               as the command-tail pointer in RA at program entry,
;               valid until the next K_PATH_RESOLVE call reuses it.
;               Empty string if the path was empty, "/", or ended in
;               a separator (the resolved RD cluster IS the target
;               in that case -- e.g. CD should skip straight to
;               K_SETCURDIR rather than searching for an empty name).
;          RC.0 = resolved drive index (0-3, 0=C..3=F)
;          DF = 0 on success, DF = 1 if an intermediate component
;               was not found, was found but is not a directory, or
;               an explicit "X:" prefix named a drive with no mounted
;               partition
K_PATH_RESOLVE: equ     $0142

; K_FILE_DELETE: delete a file (not a directory -- rejected).
; Crash-safe ordering: the directory entry is marked deleted on disk
; BEFORE the cluster chain is freed, so an interruption partway
; through leaves at worst a recoverable cluster leak (via fsck), not
; a live entry pointing at clusters the FAT has already freed.
;
; Args:    RF = pointer to null-terminated path string
; Returns: DF = 0 on success, DF = 1 on error (not found, is a
;          directory, or an intermediate path component is invalid)
K_FILE_DELETE:  equ     $0145

; K_DIR_CREATE: create a new, empty subdirectory (MD). Single-level
; only -- the parent must already exist (no implicit intermediate
; directory creation, matching classic DOS MD).
;
; Args:    RF = pointer to null-terminated path string
; Returns: DF = 0 on success, DF = 1 on error (already exists, an
;          intermediate path component is invalid, or disk full)
K_DIR_CREATE:   equ     $0148

; K_DIR_REMOVE: remove an EMPTY subdirectory (RD). Refuses non-empty
; directories (no recursive delete), "."/".."  and the root itself.
;
; Args:    RF = pointer to null-terminated path string
; Returns: DF = 0 on success, DF = 1 on error (not found, not a
;          directory, not empty, is "."/".."/root, or an intermediate
;          path component is invalid)
K_DIR_REMOVE:   equ     $014B

; K_FILE_RENAME: rename a file or directory within the SAME parent
; directory (no cross-directory move). Works on either files or
; directories.
;
; Args:    RF = pointer to null-terminated OLD path string
;          RD = pointer to null-terminated NEW name (bare name, no
;          path separator -- always applies within the OLD path's
;          own parent directory)
; Returns: DF = 0 on success, DF = 1 on error (old not found, new
;          name already exists or is invalid, old or new name is
;          "."/"..", or an intermediate component of the old path is
;          invalid)
K_FILE_RENAME:  equ     $014E

; ---- Kernel version (read directly, no call needed) ----
; $0100's 6-byte header layout is a stable, never-shifting contract
; (same reasoning as PROG_BASE/LOADER_ARGS above), so the version
; bytes are just read directly rather than through a jump-table call.
KERNEL_HDR_VER: equ     $0103       ; major version byte; minor follows at +1

; ---- K_DIR_READ result buffer format (DIRENT_LEN bytes, caller-provided) ----
; Restated from kernel.inc (not #included, per the note above) since any
; program calling K_DIR_READ needs to know how to parse what it returns.
DIRENT_NAME:    equ     0           ; null-terminated filename (up to 127 chars)
DIRENT_ATTR:    equ     128         ; FAT attribute byte
DIRENT_CLUST:   equ     129         ; first cluster, 2 bytes, big-endian
DIRENT_SIZE:    equ     131         ; file size, 4 bytes, big-endian
DIRENT_WRTTIME: equ     135         ; last-write time, 2 bytes, big-endian,
                                    ; packed FAT format: bits 15-11=hour,
                                    ; 10-5=minute, 4-0=seconds/2
DIRENT_WRTDATE: equ     137         ; last-write date, 2 bytes, big-endian,
                                    ; packed FAT format: bits 15-9=year-1980,
                                    ; 8-5=month, 4-0=day
DIRENT_LEN:     equ     139         ; total result buffer size
ATTR_DIR:       equ     $10         ; DIRENT_ATTR bit set for subdirectories
ATTR_HIDDEN:    equ     $02         ; DIRENT_ATTR bit set for hidden
                                    ; entries (2026-07-22) -- restated
                                    ; from kernel.inc, same "decoupled,
                                    ; not #included" reasoning as
                                    ; ATTR_DIR above
ATTR_RDONLY:    equ     $01         ; DIRENT_ATTR bit set for read-only
                                    ; files (2026-09-28): K_FILE_OPEN
                                    ; refuses mode 1/2 and K_FILE_DELETE
                                    ; refuses the file; reading and
                                    ; renaming are allowed, as in MS-DOS

; ---- BIOS passthroughs (see include/bios.inc for each one's convention) ----
; Calling through here rather than directly into BIOS means a program
; has no dependency on the raw BIOS vector table, and gives ELF-DOS a
; hook point for future I/O redirection.
;
; K_INPUTL/K_SETBD REMOVED (dead-code cleanup, post-v1.0.0 -- see the
; jump-table renumbering note below for why this was safe to do despite
; the version bump): K_INPUTL's own kernel-resident implementation had
; zero real callers anywhere in this repo, fully superseded by
; lib/lineedit.asm's read_line_ex (built 2026-07-30 explicitly as its
; replacement -- progs/edlin.asm already uses that instead). K_SETBD
; (a bare "lbr f_setbd" passthrough) never had a real caller at all --
; f_setbd is a bare-metal auto-baud-detection routine for pre-OS boot
; code, irrelevant once ELF-DOS is already running; setting the
; hardware UART's baud rate uses f_usetbd directly (progs/baud.asm),
; a genuinely different routine.
K_TYPE:         equ     $011E       ; -> the real console output
                                    ; routine, self-modified at boot
                                    ; (NOT f_type), and rewritten
                                    ; again while output is redirected
K_MSG:          equ     $0121       ; -> _redir_msg (NOT f_msg): loops
                                    ; over the string calling K_TYPE,
                                    ; so it inherits redirection
K_INMSG:        equ     $0124       ; -> _redir_inmsg (NOT f_inmsg);
                                    ; same per-byte K_TYPE loop
K_GETDEV:       equ     $0127       ; -> f_getdev
K_GETTOD:       equ     $012A       ; -> f_gettod
K_SETTOD:       equ     $012D       ; -> f_settod
K_BOOT:         equ     $0130       ; -> f_boot
K_TTY:          equ     $0133       ; -> f_tty
K_READ:         equ     $0151       ; -> f_read: blocking read of a single
                                    ; character from the console, returned
                                    ; in D. Standard Elf/OS BIOS contract,
                                    ; confirmed on hardware 2026-07-10 via
                                    ; COPY's overwrite-confirmation prompt.

; K_FAT_INIT/K_FILE_INIT/K_SHELL_INIT: reserved -- boot-only one-time
; init, called exactly once each by boot/krnboot.asm's relocated init
; code (see that file's own header comment), not meant to be called by
; ordinary programs (re-running them mid-session would reset live BPB/
; FAT-cache/FCB state out from under whatever's currently using it).
; Exist as jump-table slots at all only because krnboot.asm is linked
; completely separately from kernel.bin, so this fixed-address table is
; the only way it can reach these kernel-resident routines -- same
; reasoning as every other slot in this file, just with a boot-code
; caller instead of a program.
;
; K_BPB_INIT REMOVED 2026-07-13 (pre-release cleanup): its own
; jump-table slot had already been a no-op stub since the multi-sector
; krnboot expansion (bpb_init's real body moved into krnboot.asm
; itself, which reaches the BPB fields directly via BPB_DATA_PTR
; instead) -- grep confirmed zero remaining callers, so the dead stub
; is now removed outright rather than kept as a stub forever.
;
; K_SHELL_INIT (new): locates the shell binary's own directory entry
; once at boot (always "C:/bin/shell" -- see kernel.inc's own
; shell_drive/shell_elba/shell_eoff comment) via _find_dirent, and
; records its (drive, sector LBA, byte offset within that sector) into
; those three kernel-resident fields, rather than a path string --
; run_loop's own reload of the shell every command cycle then reads
; that ONE known sector directly instead of re-walking a directory
; scan every time (see kernel/loader.asm's prog_run_shell). Args:
; none. Returns: DF = 0 on success (shell_drive/shell_elba/shell_eoff
; populated), DF = 1 if "C:/bin/shell" doesn't exist or isn't a file
; -- boot/krnboot.asm treats DF = 1 as a fatal boot error.
K_FAT_INIT:     equ     $0154       ; -> fat_init
K_FILE_INIT:    equ     $0157       ; -> file_init
K_SHELL_INIT:   equ     $015A       ; -> kernel_shell_init

; K_SECWRITE/K_SECREAD: raw 512-byte sector read/write by LBA, bypassing
; the FAT16 filesystem entirely -- direct passthroughs to the same BIOS
; routines this project's own fat.asm uses for FAT/directory sector I/O.
; Args: R7/R8 = 24-bit LBA (R8.0 = bits 23-16, R7.1 = bits 15-8, R7.0 =
; bits 7-0), R8.1 = the block device UNIT number 0-7 (0 = the boot
; device; a BIOS supporting only one device ignores it), RF = pointer to
; a 512-byte buffer (source for K_SECWRITE, destination for K_SECREAD).
;
; R8.1 used to be documented as "0, the drive/head byte" and every
; caller set it to 0. It became a real unit number in 2026-09-09's
; multi-drive work -- a BIOS with more than one device reads it there
; (MiniROM masks it to 5 bits and rejects >= 8), and the LBA is only 24
; bits, so the byte was free.
;
; A program working on a DRIVE's own sectors (anything located through
; BPB_DATA_PTR) must load that drive's BPBBLK_DEV into R8.1, not 0: the
; drive may have been MOUNTed from another unit. LABEL, CHKDSK and
; CORRUPT all hardcoded 0 until 2026-09-11, so LABEL on a floppy mounted
; from unit 1 wrote into the boot device's MBR. 0 is only right for the
; boot device itself (e.g. SYS installing boot sectors).
;
; Returns:
; DF = 0/1 (success/error); R7/R8 are clobbered by the call. DANGEROUS
; if misused -- a wrong LBA can silently corrupt the running filesystem
; or the boot sectors themselves. Added specifically for progs/sys.asm
; (target-side kernel/MBR installer); not intended for casual use.
K_SECWRITE:     equ     $015D       ; -> f_idewrite
K_SECREAD:      equ     $0160       ; -> f_ideread

; K_STAT: resolve a (possibly multi-component) path to its own
; directory entry, filling the caller's buffer with the same format
; K_DIR_READ itself returns (DIRENT_NAME/ATTR/CLUST/SIZE/WRTTIME/
; WRTDATE below). Works on either a file or a directory -- unlike
; K_FILE_DELETE (files only) or K_DIR_REMOVE (directories only), the
; caller decides what to do with DIRENT_ATTR's ATTR_DIR bit.
;
; Args:    RF = pointer to null-terminated path string
;          RD = pointer to a caller-provided DIRENT_LEN-byte buffer
; Returns: DF = 0 on success (buffer filled), DF = 1 on error (not
;          found, an intermediate path component is invalid, or the
;          path names the root/a directory via a trailing separator --
;          see K_PATH_RESOLVE's own comment on that case; there's no
;          real directory entry describing the root itself)
K_STAT:         equ     $0163       ; -> file_stat

; BPBBLK_*/BPB_DATA_PTR: restated from kernel.inc (not #included, per
; the note above) for krnboot's own relocated bpb_init body, which
; reaches these 11 kernel-resident fields (part1_lba through
; fat_csec, 23 bytes, always contiguous -- see kernel.inc's own
; header comment on this block for the full reasoning) via a fixed
; pointer instead of a normal relocatable symbol, since krnboot.asm is
; linked completely separately from kernel.bin. BPB_DATA_PTR's own
; VALUE (the block's real address) is populated at kernel *link* time,
; not by krnboot -- krnboot only ever reads it. This is a DATA slot,
; not a call target (2 bytes, not a 3-byte lbr), sitting at the jump
; table's own tail by design -- the next real K_* call slot starts
; 2 bytes later than it otherwise would.
BPBBLK_PART1_LBA:  equ  0          ; 3 bytes
BPBBLK_FAT_LBA:    equ  3          ; 3 bytes
BPBBLK_ROOT_LBA:   equ  6          ; 3 bytes
BPBBLK_DATA_LBA:   equ  9          ; 3 bytes
BPBBLK_SPC:        equ  12         ; 1 byte
BPBBLK_SPC_SHIFT:  equ  13         ; 1 byte
BPBBLK_ROOT_ENTS:  equ  14         ; 2 bytes
BPBBLK_NUM_FATS:   equ  16         ; 1 byte
BPBBLK_SPF:        equ  17         ; 2 bytes
BPBBLK_MAX_CLUST:   equ  19          ; 2 bytes -- highest valid cluster:
                    ; exactly the volume's cluster count + 1, so
                    ; clusters 2..max_clust exist (2026-09-11; was
                    ; an over-estimate derived from the FAT size).
                    ; It also IS the FAT type, as the spec defines
                    ; it: max_clust < $0FF6 (fewer than 4085
                    ; clusters) means FAT12, otherwise FAT16. The
                    ; kernel derives its own FAT12 flag from this
                    ; in _switch_drive, and a program decoding a
                    ; raw FAT itself (CHKDSK) must do the same.
BPBBLK_DEV:         equ  21          ; 1 byte -- block device UNIT number
                    ; (0-7) this partition lives on, passed to
                    ; the BIOS in R8.1 on every f_ideread /
                    ; f_idewrite. See _set_lba_dev (fat.asm).
BPBBLK_LEN:         equ  22          ; total block size

BPB_DATA_PTR:      equ  $0166      ; 2-byte pointer to the block's
                                    ; start (part1_lba's real address)

; DRIVE_DATA_PTR: same mechanism as BPB_DATA_PTR above, for the
; multi-partition boot-time scan (2026-07-13). Points at
; drive_present[0..DRIVE_COUNT-1] (1 byte each, presence flags)
; immediately followed by drive_bpb_table[0..DRIVE_COUNT-1]
; (BPBBLK_LEN bytes each, contiguous, same "point at the block's
; start" convention) -- krnboot's own relocated partition-scan loop
; writes both regions through this one pointer, one drive at a time.
; Its reach extends 6 more bytes past drive_bpb_table (still
; contiguous) to shell_drive/shell_elba/shell_eoff -- boot-discovered
; facts in the same spirit as drive_present, populated once by
; K_SHELL_INIT (see below) rather than the partition-scan loop itself,
; but reusing this same pointer rather than adding a second one.
;
; The reach was extended again (2026-09-09, multi-drive MOUNT/UMOUNT)
; over drive_cur_dir and cur_drive, which are contiguous right after
; shell_eoff. These are session state rather than boot-time facts --
; kernel_init initializes them, not the partition scan -- but MOUNT has
; to reset a freshly-mounted drive's current directory to its root, and
; UMOUNT has to move cur_drive off a drive it is about to remove, so
; both need reaching from userland. See DRIVE_CUR_DIR_OFF/CUR_DRIVE_OFF
; below.
;
; active_bpb_drive sits one byte past cur_drive and is deliberately NOT
; published. Userland must go through K_DRIVE_INVALIDATE instead:
; poking active_bpb_drive directly would skip the FAT-cache flush that
; call exists to perform, silently losing a dirty FAT sector.
DRIVE_COUNT:       equ  6          ; simultaneously mounted drives

; MBR_PART_COUNT: primary partitions in an MBR. Distinct from
; DRIVE_COUNT since 2026-09-09 -- see include/kernel.inc for why
; krnboot's scan in particular must use this one.
MBR_PART_COUNT:    equ  4

; Drive letters -- see include/kernel.inc for the full note.
DRIVE_LETTER_MIN:  equ  'A'
DRIVE_LETTER_MAX:  equ  'Z'
BOOT_DRIVE_FIRST:  equ  'C'
DRIVE_DATA_PTR:    equ  $0168      ; 2-byte pointer to drive_present's
                                    ; real address
DRIVE_PRESENT_LEN: equ  DRIVE_COUNT            ; 4 bytes
DRIVE_BPB_TABLE_OFF: equ DRIVE_COUNT           ; drive_bpb_table starts
                                                ; this many bytes after
                                                ; DRIVE_DATA_PTR's target
SHELL_DATA_OFF: equ     DRIVE_COUNT + DRIVE_COUNT*BPBBLK_LEN
                                                ; shell_drive (then
                                                ; shell_elba, then
                                                ; shell_eoff) starts
                                                ; this many bytes after
                                                ; DRIVE_DATA_PTR's target

; DRIVE_CUR_DIR_OFF/CUR_DRIVE_OFF: two more DRIVE_DATA_PTR-relative
; offsets, for MOUNT/UMOUNT (see the note above). drive_cur_dir is
; DRIVE_COUNT 2-byte big-endian cluster numbers, one per drive, 0
; meaning that drive's root; cur_drive is a single byte naming the
; drive an unprefixed path resolves against.
;
; Prefer K_SETDRIVE over writing cur_drive directly -- it validates
; drive_present first. Writing it raw is only appropriate when the
; validation would be wrong for the caller's purpose, and no current
; caller needs that.
DRIVE_CUR_DIR_OFF: equ  SHELL_DATA_OFF + 6      ; DRIVE_COUNT*2 bytes
CUR_DRIVE_OFF:     equ  DRIVE_CUR_DIR_OFF + DRIVE_COUNT*2   ; 1 byte
; DRIVE_LETTER_OFF: which letter each slot answers to, one byte per
; slot, 0 = free. Since 2026-09-09 a slot's letter is no longer 'C' +
; its index -- any slot may carry any letter A-Z -- so this table is the
; only way to convert either direction. lib/drives.asm wraps it; prefer
; that to reading it directly. A lettered slot is not necessarily
; usable: MOUNT gives an UNFORMATTED partition a letter but leaves its
; drive_present byte 0 (only BPBBLK_PART1_LBA/BPBBLK_DEV are filled in),
; and FORMAT sets drive_present once it has written a filesystem.
; Check drive_present before reading any other field of the entry.
DRIVE_LETTER_OFF:  equ  CUR_DRIVE_OFF + 2      ; +1 for cur_drive,
                                                ; +1 for active_bpb_drive
                                                ; (which is deliberately
                                                ; NOT published -- see
                                                ; K_DRIVE_INVALIDATE)

; K_BATCH_START/K_BATCH_READLINE: minimal flat (non-nested) batch
; script execution (2026-07-14). The shell (progs/shell.asm) is
; reloaded fresh from disk every command cycle, so it has no memory of
; its own that survives from one line to the next -- these two calls
; let the KERNEL hold that state instead (a dedicated FCB+I/O buffer,
; the same reason cur_dir/cur_drive live in the kernel too), giving
; the shell a trivial contract: call K_BATCH_READLINE once at the top
; of every cycle; DF=0 means a batch line is ready in LINE_BUF (use it
; instead of prompting the console), DF=1 means read from the console
; as normal (no batch active, or one just ended).
;
; K_BATCH_START: begin executing a batch script.
; Args:    RF = pointer to a null-terminated path, already resolved
;          (and confirmed to exist) by the caller -- see
;          progs/shell.asm's own K_STAT-based existence check.
; Returns: DF = 0 on success. DF = 1 on failure, with D = one of the
;          BATCH_ERR_* codes below saying why.
;
; K_BATCH_READLINE: fetch the next line of the active batch script.
; Args:    none
; Returns: DF = 0 with LINE_BUF holding the next line (null-terminated,
;          CR/LF stripped) if a line was available; DF = 1 if no batch
;          is active, or the batch just reached EOF (auto-closed, so
;          the very next call also returns DF=1 until a new
;          K_BATCH_START).
K_BATCH_START:      equ     $016A       ; -> batch_start
; K_BATCH_START's failure reasons, returned in D when DF=1 (2026-09-23).
; Before this every failure looked the same, and the shell reported all
; of them as "Nested batch not supported." -- including a missing
; batch.mod, which is what a hardware user actually hit. Codes 2-4 are
; mod_load's own MODLOAD_ERR_* values (include/modformat.inc), passed
; through unchanged, so the two sets must stay numerically equal.
BATCH_ERR_ACTIVE:   equ     1           ; a batch is already running
BATCH_ERR_NOMOD:    equ     2           ; C:/bin/batch.mod not found
BATCH_ERR_BADMOD:   equ     3           ; batch.mod unreadable/invalid
BATCH_ERR_NOMEM:    equ     4           ; no room in RAM for batch.mod
BATCH_ERR_OPEN:     equ     5           ; the .bat file wouldn't open
K_BATCH_READLINE:   equ     $016D       ; -> batch_readline

; K_BATCH_GOTO: reposition the active batch script to just after a
; labeled line ("2026-07-25, IF/GOTO batch scripting). Always rewinds
; to the start of the file and scans forward -- simpler than tracking
; direction, and batch scripts are small enough that a full rescan is
; cheap. GOTO to an undefined label ends the batch, matching real
; MS-DOS -- this falls out for free, since the failed scan already
; reaches real EOF, which K_BATCH_READLINE's own EOF path already
; closes as an existing side effect (see its own doc above).
; Args:    RF = pointer to a null-terminated label name, no leading
;          ':' (e.g. "end" for a line reading ":end") -- a copy is
;          taken immediately, so the caller's own buffer (typically
;          argv[1], living in LINE_BUF) is safe to reuse/overwrite
;          right after this call returns
; Returns: DF = 0 on success (the label was found; the next
;          K_BATCH_READLINE call returns the line right after it),
;          DF = 1 if no batch is active or the label wasn't found (in
;          the latter case the batch is already closed, same as
;          K_BATCH_READLINE's own EOF behavior)
K_BATCH_GOTO:       equ     $0176       ; -> batch_goto

; K_GLOB_RESERVE REMOVED (dead-code cleanup, 2026-08-26 -- see the
; jump-table renumbering note near the top of this file). Reserved
; himem for the shell's own tokenizer-level glob-expansion buffer,
; which was itself completely removed 2026-07-27 in favor of
; lib/file_glob.asm's per-program glob approach -- nothing called this
; slot anymore, and kernel/glob.asm (its whole implementation) was
; deleted along with it.

; K_FILE_SETATTR: change an existing directory entry's attribute byte.
; Works on either a file or a directory. Deliberately a general
; set/clear-mask primitive, not narrowed to hidden specifically -- a
; future ATTRIB extension to R/S bits needs no kernel change, only more
; userland argument parsing (same "general primitive, minimal current
; caller" precedent as K_STAT above).
; Args:    RF = pointer to null-terminated path string
;          RC (low byte, glo rc)  = bits to SET
;          RC (high byte, ghi rc) = bits to CLEAR
;          new_attr = (old_attr & ~clear) | set
; Returns: DF = 0 on success, DF = 1 on error (not found, bad path,
;          target is "." or "..", or an I/O error writing the sector)
K_FILE_SETATTR:     equ     $0170       ; -> file_setattr

; K_FILE_TOUCH: update an existing directory entry's last-write date/
; time to the current time. Touches nothing else -- content, size,
; cluster chain, and attribute byte are all left exactly as they were.
; Works on either a file or a directory, same "caller decides" spirit
; as K_FILE_SETATTR just above.
; Args:    RF = pointer to null-terminated path string
; Returns: DF = 0 on success, DF = 1 on error (not found, bad path,
;          target is "." or "..", or an I/O error writing the sector)
K_FILE_TOUCH:       equ     $0185       ; -> file_touch

; K_HIMEM_RESERVE/K_HIMEM_RELEASE (2026-07-31): general-purpose himem
; reservation, exposed to ordinary programs for the first time. Thin
; passthroughs to the kernel's own already-proven _himem_reserve/
; _himem_release (kernel/redir.asm, used internally for years by I/O
; redirection and batch-args substitution) -- PURE MECHANISM, no flag,
; no idempotency, caller-supplied size, caller tracks its own
; reservation state. First real consumer: lib/modload.asm's mod_load,
; which needs a page-aligned region whose size varies per module.
; K_HIMEM_RESERVE:
;   Args:    RC = bytes to reserve
;   Returns: DF = 0 on success, RD = this reservation's base address
;            (mem_top + 1). DF = 1 if there isn't enough headroom
;            (nothing changed).
K_HIMEM_RESERVE:    equ     $0188       ; -> kernel_himem_reserve
; K_HIMEM_RELEASE:
;   Args:    RC = bytes to release (must match a caller's own prior
;            successful K_HIMEM_RESERVE call)
;   Returns: nothing
K_HIMEM_RELEASE:    equ     $018B       ; -> kernel_himem_release

; K_DRIVE_INVALIDATE: drop cached kernel state for one drive, so its
; drive_bpb_table entry can be replaced (MOUNT) or its drive_present
; flag cleared (UMOUNT), added 2026-09-09 for multi-drive support.
;
; Does exactly two things, both of which userland cannot: flushes and
; then discards the FAT cache if the named drive is the currently
; active one, and forces the next _switch_drive to reload from
; drive_bpb_table rather than taking its already-active no-op path.
;
; Also the call for a program that writes sectors directly with
; K_SECWRITE: call it BEFORE the raw writes (so no pending FAT change
; can land on top of them later) and AFTER (so the kernel holds no
; stale copy of a FAT sector that was just changed underneath it). The
; kernel keeps no directory or file-data cache between calls, so the
; FAT sector is the only thing that needs this.
;
; *** ORDERING CONTRACT ***  Call this BEFORE you overwrite
; drive_bpb_table[i] or clear drive_present[i], never after. The flush
; derives its LBAs from the active BPB fields, so running it against a
; table entry that has already been replaced writes a cached FAT sector
; to an address computed from the NEW partition's geometry -- silent
; cross-partition corruption rather than a reported error.
;
;   Args:    D = drive index (0..DRIVE_COUNT-1)
;   Returns: DF = 0 always
K_DRIVE_INVALIDATE: equ     $018E       ; -> kernel_drive_invalidate

; TERM_ROWS/TERM_COLS: the console terminal's size in rows/columns, one
; byte each, kept by the kernel in volatile RAM (2026-09-30, kernel
; v1.2). DATA bytes at fixed addresses, read and written directly -- no
; call. 0 means unknown: that is the value at every boot. TERMSIZE sets
; both, along with ROWS/COLUMNS. Values above 255 are stored as 255.
; To lay out output, call term_size (lib/term.asm) rather than reading
; these: it falls back to ROWS/COLUMNS and then 24x80 when they are 0.
;
; Why here and not only in the environment: reading COLUMNS means
; opening and scanning /cfg/env.dat, which is fine once per program run
; but far too slow for the line editor (lib/lineedit.asm), which needs
; the width at the start of every input line to wrap long lines.
TERM_ROWS:          equ     $0191       ; byte: terminal rows, 0=unknown
TERM_COLS:          equ     $0192       ; byte: terminal columns, 0=unknown

; GLOB_BUF_LEN REMOVED along with K_GLOB_RESERVE above (dead code,
; 2026-08-26) -- its only use was sizing that reservation.

; K_BATCH_ARGS_RESERVE/K_BATCH_ARGS_GETARG: %0-%9 batch-argument
; substitution (2026-07-25) -- see kernel/batch.asm's own module
; comments and progs/shell.asm's $/% expansion pass for the full
; design. Reserves dynamic himem via the same _himem_reserve/
; _himem_release mechanism (kernel/redir.asm) K_GLOB_RESERVE used to,
; hands back a base address, lets the CALLER (progs/shell.asm, which
; already has the data) populate it directly -- rather than passing
; argv data as call arguments for the kernel to pack.
;
; K_BATCH_ARGS_RESERVE: called once by progs/shell.asm's own is_batch:
; path, right after K_BATCH_START succeeds. NOT idempotent -- starting
; a new batch while one is already active is already rejected (nested
; batch) before this could ever be called twice without a release in
; between, so no idempotency check is needed.
; Args:    none
; Returns: DF = 0 on success, RD = this reservation's base address
;          (BATCH_ARGS_RESERVE_LEN bytes usable from RD onward -- see
;          the BATCH_ARGS_*_OFF constants below for its internal
;          layout). DF = 1 if there isn't enough RAM headroom -- the
;          caller should let the batch proceed anyway, just without
;          %N support for that run (graceful degradation, not an
;          aborted batch).
K_BATCH_ARGS_RESERVE: equ   $0179       ; -> kernel_batch_args_reserve
;
; K_BATCH_ARGS_GETARG: look up one positional argument by index.
; Bounds-checks against the reservation's own stored count before ever
; touching the pointer table, so it can never return a pointer into an
; unpopulated slot.
; Args:    D = index (0-9)
; Returns: DF = 0 in every case where a batch-args reservation is
;          currently active: RF = pointer to a null-terminated string
;          -- either the real argument (index < the count actually
;          passed) or a fixed, always-valid empty string (index >= the
;          count, but the reservation IS active -- matches real DOS,
;          where %N beyond what was passed expands to nothing, not
;          literal text). DF = 1 only when NO reservation is active at
;          all (no batch running, or its reservation failed) -- the
;          caller should leave %<digit> as literal text in that case.
K_BATCH_ARGS_GETARG: equ    $017C       ; -> kernel_batch_args_getarg

; BATCH_ARGS_*: layout of K_BATCH_ARGS_RESERVE's own reservation,
; restated from kernel.inc for progs/shell.asm's own use -- it
; populates the block directly (see is_batch:'s own code), addressing
; into it via these same offsets. This copy is for kernel/batch.asm
; itself, which #includes kernel.inc, not this file.
BATCH_ARGS_TEXT_OFF: equ    0
BATCH_ARGS_ARGV_OFF: equ    128
BATCH_ARGS_ARGC_OFF: equ    148
BATCH_ARGS_RESERVE_LEN: equ 149

; Raw FAT16 VBR/BPB and MBR partition-table field offsets, restated
; from kernel.inc for the same reason as BPBBLK_*/BPB_DATA_PTR above --
; krnboot's own relocated bpb_init body needs these to parse the raw
; MBR/VBR sector bytes it reads directly (kernel.inc's own copy, used
; by every other BPB/FAT-adjacent kernel file, is unaffected).
BPB_SPC:        equ     $0D         ; sectors per cluster (byte)
BPB_RSVD:       equ     $0E         ; reserved sector count (word)
BPB_NFAT:       equ     $10         ; number of FATs (byte)
BPB_ROOTENT:    equ     $11         ; root directory entry count (word)
BPB_SPF:        equ     $16         ; sectors per FAT (word)
PT_OFFSET:      equ     $01BE       ; partition table entry 0 (drive C)
                                    ; offset within the MBR
PT_ENTRY_LEN:   equ     16          ; bytes between successive MBR
                                    ; partition-table entries -- entry i
                                    ; (drive C+i) starts at
                                    ; PT_OFFSET + i*PT_ENTRY_LEN
PT_LBA_OFF:     equ     8           ; LBA start within entry (4 bytes, LE)

; next free jump-table slot address: $0193 (after the TERM_ROWS/TERM_COLS data bytes)
;
; This comment has been stale in BOTH directions before ($0179 until
; 2026-07-27, then $0197 until 2026-09-09) while kernel.asm was right
; each time. kernel/kernel.asm's own trailing comment, immediately
; after the jump table itself, is the actual source of truth -- check
; there, not here, and update this one when you append a slot.
