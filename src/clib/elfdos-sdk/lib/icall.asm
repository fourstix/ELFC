;
; icall.asm - SCRT-parallel indirect call, for invoking a routine whose
; address is only known at runtime (a dynamically loaded module's
; public entry point, computed as module_base + a compile-time-
; constant jump-table offset).
;
; NOT a standalone program -- no EDF header, no org PROG_BASE, no
; entry point of its own. Assembled separately (lib/icall.prg) and
; linked alongside a program (or kernel file) that wants it, the same
; way every other lib/*.asm module already does. A calling program
; declares "extrn icall" and does "call icall" (never "lbr icall" --
; see below for why that matters) with RB already set to the resolved
; target address.
;
; Deliberately a SEPARATE routine, never a modification to scall.asm
; (this project's own shared, system-wide SCRT call/return mechanism
; -- every call and return in the whole OS goes through it, making it
; about the highest-blast-radius file that exists here). This file
; only gets linked into whatever specifically calls it; a bug here can
; only ever break a dynamic-module caller, never ordinary calls
; anywhere else.
;
; *** REAL BUG FOUND AND FIXED (2026-08-01), found via a hardware boot
; hang: the FIRST version of this routine tried to load the runtime
; target directly into R3 via "ghi rb/phi r3/glo rb/plo r3" while
; STILL EXECUTING UNDER P=R3 (icall's own entry state -- see the entry
; mechanics below). This is fundamentally broken on the 1802: PHI/PLO
; write only ONE byte of a register per instruction, and the CPU
; re-fetches the NEXT instruction using R(P)'s CURRENT value at the
; very start of every instruction cycle. So the instant "phi r3"
; executes (writing R3's HIGH byte to the target's high byte, while
; R3's LOW byte still reflects icall's OWN code position, unrelated to
; the target), the very next fetch -- for "glo rb" -- happens at
; (target.hi : icall's-own-current-low-byte), almost never valid code.
; Confirmed against the real scall.asm (this project's own root-level
; file, kept there for exactly this kind of reference): its own
; "call"/"callbr" NEVER modifies R3 while P=R3 -- it always assembles
; a fresh R3 value while executing under P=R4 (reached via the calling
; code's own "SEP R4"), only doing the final "SEP R3" once R3 is
; completely and correctly set. This isn't a style choice -- it's the
; only safe way to redirect execution to a computed address on this
; CPU: SEP is a single, atomic instruction (switches P to an
; already-fully-set register, no partial-state window), while
; PHI/PLO/GHI/GLO are NOT atomic with respect to the fetch cycle when
; the register being modified is R(P) itself.
;
; Symptom on real hardware: kernel_init calls batch_start
; unconditionally for /autoexec.bat on every single boot (see
; kernel/kernel.asm), which -- once the module loads successfully via
; mod_load -- reached this routine to jump into the module's own
; batch_start entry point. The corrupted jump sent execution into
; undefined memory, manifesting as "prints the complete boot banner,
; then hangs" on EVERY boot, not just ones where /autoexec.bat happens
; to exist -- batch_start always loads the module before ever trying
; to open the script, so mod_load/icall ran regardless.
;
; THE FIX: temporarily switch P to R7 (an ordinary, otherwise-unused
; scratch register -- confirmed unused across all 3 current call sites
; in kernel/batch.asm right before their own "call icall") via a
; compile-time-constant "SEP R7", landing at a local label within this
; same routine. Since R7 is NOT R3, it's now completely safe to modify
; R3 with ordinary PHI/PLO -- R3 isn't the active P register at that
; moment -- and a final "SEP R3" switches P back to R3, now correctly
; holding the runtime target, fully assembled BEFORE that switch
; happens (mirroring scall.asm's own proven technique, just using R7
; as the "temporarily different P" instead of R4 -- R4 must stay
; pointed at the shared call trampoline for every OTHER call in the
; system and can't be repurposed even briefly). R6 is never touched
; anywhere in this sequence, so the callee's own eventual "rtn" still
; resumes directly at icall's REAL caller -- true tail-call
; transparency, exactly matching the original design intent.
;
; How the ENTRY mechanics work (traced against the real scall.asm,
; kept in this project's own root for reference): "call X" compiles to
; "SEP R4" followed by X's address as two inline bytes. The 1802 auto-
; increments whichever register is P as instructions are fetched, so
; by the time SEP R4 has been executed, R3 (no longer P, but unchanged
; in value otherwise) has already advanced past the SEP R4 opcode to
; point at those two inline bytes -- scall.asm's own "call"/"callbr"
; reads them via R6 (copied from R3), producing R3 = the real call
; target and, critically, leaving R6 pointing at whatever comes right
; after the two inline bytes -- the correct return-continuation
; address, which "rtn" (SEP R5, not shown in this project's own
; scall.asm excerpt) uses to resume the caller once the callee
; returns.
;
; icall is invoked via an ORDINARY "call icall" -- meaning by the time
; icall's own body starts running, that entire mechanism has ALREADY
; run once, for icall's own invocation: R6 already correctly holds
; "resume right after this call icall instruction". icall's own job is
; just to redirect P to the runtime target WITHOUT ever disturbing R6,
; so the callee's own eventual "rtn" lands there directly. This is why
; the CALLER must reach icall via "call", never "lbr" -- only "call"
; refreshes R6 to the right value in the first place.
;

#include    include/opcodes.def

;------------------------------------------------------------------
; icall: transfer control to a runtime-computed address exactly as if
; reached by an ordinary "call label" -- the target routine runs
; normally and its own "rtn" returns directly to icall's OWN caller
; (see this file's own header for the full mechanism, including the
; hardware-confirmed bug this design fixes).
; Args:    RB = target address (module_base + a compile-time-constant
;          jump-table offset, computed by the caller)
; Returns: whatever the target routine itself returns -- icall is
;          fully transparent to both its caller and the callee
; Modifies: R3 (as any call/dispatch mechanism must), R7 (used as a
;          brief, purely-local temporary P register -- never expected
;          to carry anything meaningful across this call). D is
;          preserved across the jump (stashed in R9, reloaded
;          immediately before the final SEP) so the target sees D
;          exactly as icall's own caller left it. RB itself is
;          consumed by icall's own mechanism -- a target routine's own
;          calling convention must not expect RB to carry anything
;          meaningful across this call, the same way ordinary SCRT
;          calls already reserve R3/R4/R6 for their own mechanism and
;          no ordinary routine's calling convention relies on those
;          either.
;------------------------------------------------------------------
            proc    icall

            plo     r9                  ; stash D -- the mov below
                                        ; clobbers D via its own LDI
                                        ; sequence, and the target
                                        ; callee needs to see D exactly
                                        ; as icall's own caller left it
                                        ; (gotcha #4)

            mov     r7, icall_safe      ; R7 = a compile-time-constant
                                        ; local address -- safe to set
                                        ; while P=R3, since R7 is not
                                        ; the active P register
            sep     r7                  ; P = R7, TEMPORARILY -- now
                                        ; executing under a register
                                        ; other than R3, so R3 can be
                                        ; safely modified below with no
                                        ; fetch-corruption risk (see
                                        ; this file's own header for
                                        ; why this step is mandatory)

icall_safe:
            ghi     rb
            phi     r3
            glo     rb
            plo     r3                  ; R3 = target address, fully
                                        ; and safely assembled while
                                        ; P=R7, not P=R3

            glo     r9                  ; D restored, for the callee to
                                        ; see exactly what icall's own
                                        ; caller left it as
            sep     r3                  ; P = R3 = target. R6 was never
                                        ; touched anywhere above, so
                                        ; the target's own eventual
                                        ; "rtn" resumes directly at
                                        ; icall's REAL caller with zero
                                        ; extra bookkeeping

            endp
