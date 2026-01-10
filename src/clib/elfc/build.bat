..\asm02 -L add16.asm
..\asm02 -L and16.asm
..\asm02 -L div16.asm
..\asm02 -L eq16.asm
..\asm02 -L false16.asm
..\asm02 -L gt16.asm
..\asm02 -L gte16.asm
..\asm02 -L lt16.asm
..\asm02 -L lte16.asm
..\asm02 -L mdsgn16.asm
..\asm02 -L mod16.asm
..\asm02 -L mul16.asm
..\asm02 -L ne16.asm
..\asm02 -L neg16.asm
..\asm02 -L or16.asm
..\asm02 -L sub16.asm
..\asm02 -L true16.asm
..\asm02 -L xor16.asm
..\asm02 -L epush16.asm
..\asm02 -L dpop16.asm
..\asm02 -L not16.asm
..\asm02 -L bool16.asm
..\asm02 -L inv16.asm
..\asm02 -L shl16.asm
..\asm02 -L shr16.asm
..\asm02 -L vpush16.asm
..\asm02 -L vpop16.asm
..\asm02 -L vpush8.asm
..\asm02 -L dpush16.asm
..\asm02 -L esmove.asm
..\asm02 -L linit16.asm
..\asm02 -L lstor16.asm
..\asm02 -L lstor8.asm
..\asm02 -L vstor16.asm
..\asm02 -L vstor8.asm
..\asm02 -L swap16.asm
..\asm02 -L dget16.asm
..\asm02 -L lpush16.asm
..\asm02 -L lpush8.asm
..\asm02 -L deref16.asm
..\asm02 -L deref8.asm
..\asm02 -L laddr16.asm
..\asm02 -L pstor16.asm
..\asm02 -L pstor8.asm
..\asm02 -L scltos2n.asm
..\asm02 -L sclsos2n.asm
..\asm02 -L unscl2n.asm
..\asm02 -L vinc16.asm
..\asm02 -L vdec16.asm
..\asm02 -L vinc8.asm
..\asm02 -L vdec8.asm
..\asm02 -L linc16.asm
..\asm02 -L ldec16.asm
..\asm02 -L linc8.asm
..\asm02 -L ldec8.asm
..\asm02 -L vpinc16.asm
..\asm02 -L vpdec16.asm
..\asm02 -L lpinc16.asm
..\asm02 -L lpdec16.asm
..\asm02 -L psave.asm
..\asm02 -L pinc16.asm
..\asm02 -L pinc8.asm
..\asm02 -L pdec16.asm
..\asm02 -L pdec8.asm
..\asm02 -L pincptr.asm
..\asm02 -L pdecptr.asm
..\asm02 -L stkchk.asm
..\asm02 -L ugt16.asm
..\asm02 -L uge16.asm
..\asm02 -L ult16.asm
..\asm02 -L ule16.asm
..\asm02 -L lget16.asm
..\asm02 -L lset16.asm
..\asm02 -L mcopy.asm

type add16.prg and16.prg bool16.prg deref16.prg deref8.prg dget16.prg div16.prg > elfc.lib
type dpop16.prg dpush16.prg epush16.prg eq16.prg esmove.prg false16.prg gt16.prg >> elfc.lib
type gte16.prg inv16.prg laddr16.prg ldec16.prg ldec8.prg lget16.prg linc16.prg >> elfc.lib
type linc8.prg linit16.prg lpdec16.prg lpinc16.prg lpush16.prg lpush8.prg >> elfc.lib
type lset16.prg lstor16.prg lstor8.prg lt16.prg lte16.prg mcopy.prg mdsgn16.prg >> elfc.lib
type mod16.prg mul16.prg ne16.prg neg16.prg not16.prg or16.prg pdec16.prg >> elfc.lib
type pdec8.prg pdecptr.prg pinc16.prg pinc8.prg pincptr.prg psave.prg pstor16.prg >> elfc.lib
type pstor8.prg sclsos2n.prg scltos2n.prg shl16.prg shr16.prg stkchk.prg sub16.prg >> elfc.lib
type swap16.prg true16.prg uge16.prg ugt16.prg ule16.prg ult16.prg unscl2n.prg >> elfc.lib
type vdec16.prg vdec8.prg vinc16.prg vinc8.prg vpdec16.prg vpinc16.prg >> elfc.lib
type vpop16.prg vpush16.prg vpush8.prg vstor16.prg vstor8.prg xor16.prg >> elfc.lib

copy elfc.lib ..\lib\elfc.lib
