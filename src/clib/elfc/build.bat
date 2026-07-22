..\asm02 -r -r -L add16.asm
..\asm02 -r -r -L and16.asm
..\asm02 -r -r -L div16.asm
..\asm02 -r -r -L eq16.asm
..\asm02 -r -r -L false16.asm
..\asm02 -r -L gt16.asm
..\asm02 -r -L gte16.asm
..\asm02 -r -L lt16.asm
..\asm02 -r -L lte16.asm
..\asm02 -r -L mdsgn16.asm
..\asm02 -r -L mod16.asm
..\asm02 -r -L mul16.asm
..\asm02 -r -L ne16.asm
..\asm02 -r -L neg16.asm
..\asm02 -r -L or16.asm
..\asm02 -r -L sub16.asm
..\asm02 -r -L true16.asm
..\asm02 -r -L xor16.asm
..\asm02 -r -L epush16.asm
..\asm02 -r -L dpop16.asm
..\asm02 -r -L not16.asm
..\asm02 -r -L bool16.asm
..\asm02 -r -L inv16.asm
..\asm02 -r -L shl16.asm
..\asm02 -r -L shr16.asm
..\asm02 -r -L vpush16.asm
..\asm02 -r -L vpop16.asm
..\asm02 -r -L vpush8.asm
..\asm02 -r -L dpush16.asm
..\asm02 -r -L esmove.asm
..\asm02 -r -L linit16.asm
..\asm02 -r -L lstor16.asm
..\asm02 -r -L lstor8.asm
..\asm02 -r -L vstor16.asm
..\asm02 -r -L vstor8.asm
..\asm02 -r -L swap16.asm
..\asm02 -r -L dget16.asm
..\asm02 -r -L lpush16.asm
..\asm02 -r -L lpush8.asm
..\asm02 -r -L deref16.asm
..\asm02 -r -L deref8.asm
..\asm02 -r -L laddr16.asm
..\asm02 -r -L pstor16.asm
..\asm02 -r -L pstor8.asm
..\asm02 -r -L scltos2n.asm
..\asm02 -r -L sclsos2n.asm
..\asm02 -r -L unscl2n.asm
..\asm02 -r -L vinc16.asm
..\asm02 -r -L vdec16.asm
..\asm02 -r -L vinc8.asm
..\asm02 -r -L vdec8.asm
..\asm02 -r -L linc16.asm
..\asm02 -r -L ldec16.asm
..\asm02 -r -L linc8.asm
..\asm02 -r -L ldec8.asm
..\asm02 -r -L vpinc16.asm
..\asm02 -r -L vpdec16.asm
..\asm02 -r -L lpinc16.asm
..\asm02 -r -L lpdec16.asm
..\asm02 -r -L psave.asm
..\asm02 -r -L pinc16.asm
..\asm02 -r -L pinc8.asm
..\asm02 -r -L pdec16.asm
..\asm02 -r -L pdec8.asm
..\asm02 -r -L pincptr.asm
..\asm02 -r -L pdecptr.asm
..\asm02 -r -L stkchk.asm
..\asm02 -r -L ugt16.asm
..\asm02 -r -L uge16.asm
..\asm02 -r -L ult16.asm
..\asm02 -r -L ule16.asm
..\asm02 -r -L lget16.asm
..\asm02 -r -L lset16.asm
..\asm02 -r -L mcopy.asm
..\asm02 -r -L epush8.asm
..\asm02 -r -L derefm.asm
..\asm02 -r -L fp2args.asm
..\asm02 -r -L dpop32.asm
..\asm02 -r -L fp1arg.asm

type add16.prg and16.prg bool16.prg deref16.prg deref8.prg derefm.prg > elfc.lib
type dget16.prg div16.prg dpop16.prg dpop32.prg dpush16.prg epush16.prg >> elfc.lib
type epush8.prg eq16.prg esmove.prg false16.prg fp1arg.prg fp2args.prg >> elfc.lib
type gt16.prg gte16.prg inv16.prg laddr16.prg ldec16.prg ldec8.prg >> elfc.lib
type lget16.prg linc16.prg linc8.prg linit16.prg lpdec16.prg lpinc16.prg >> elfc.lib
type lpush16.prg lpush8.prg lset16.prg lstor16.prg lstor8.prg lt16.prg >> elfc.lib
type lte16.prg mcopy.prg mdsgn16.prg mod16.prg mul16.prg ne16.prg neg16.prg >> elfc.lib
type not16.prg or16.prg pdec16.prg pdec8.prg pdecptr.prg pinc16.prg >> elfc.lib
type pinc8.prg pincptr.prg psave.prg pstor16.prg pstor8.prg sclsos2n.prg >> elfc.lib
type scltos2n.prg shl16.prg shr16.prg stkchk.prg sub16.prg swap16.prg >> elfc.lib
type true16.prg uge16.prg ugt16.prg ule16.prg ult16.prg unscl2n.prg  >> elfc.lib
type vdec16.prg vdec8.prg vinc16.prg vinc8.prg vpdec16.prg vpinc16.prg >> elfc.lib
type vpop16.prg vpush16.prg vpush8.prg vstor16.prg vstor8.prg xor16.prg >> elfc.lib

copy elfc.lib ..\lib\elfc.lib
