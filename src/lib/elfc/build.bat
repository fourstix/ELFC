[Your_Path]\Asm02\asm02 -L abs16.asm
[Your_Path]\Asm02\asm02 -L add16.asm
[Your_Path]\Asm02\asm02 -L and16.asm
[Your_Path]\Asm02\asm02 -L atoi16.asm
[Your_Path]\Asm02\asm02 -L div16.asm
[Your_Path]\Asm02\asm02 -L eq16.asm
[Your_Path]\Asm02\asm02 -L false16.asm
[Your_Path]\Asm02\asm02 -L gt16.asm
[Your_Path]\Asm02\asm02 -L gte16.asm
[Your_Path]\Asm02\asm02 -L itoa16.asm
[Your_Path]\Asm02\asm02 -L lfsrshift.asm
[Your_Path]\Asm02\asm02 -L lt16.asm
[Your_Path]\Asm02\asm02 -L lte16.asm
[Your_Path]\Asm02\asm02 -L mdnorm16.asm
[Your_Path]\Asm02\asm02 -L mod16.asm
[Your_Path]\Asm02\asm02 -L mul16.asm
[Your_Path]\Asm02\asm02 -L ne16.asm
[Your_Path]\Asm02\asm02 -L neg16.asm
[Your_Path]\Asm02\asm02 -L or16.asm
[Your_Path]\Asm02\asm02 -L rnd16.asm
[Your_Path]\Asm02\asm02 -L sgn16.asm
[Your_Path]\Asm02\asm02 -L sub16.asm
[Your_Path]\Asm02\asm02 -L tobcd16.asm
[Your_Path]\Asm02\asm02 -L true16.asm
[Your_Path]\Asm02\asm02 -L xor16.asm
[Your_Path]\Asm02\asm02 -L epush16.asm
[Your_Path]\Asm02\asm02 -L epush8.asm
[Your_Path]\Asm02\asm02 -L dpop16.asm
[Your_Path]\Asm02\asm02 -L dpop8.asm
[Your_Path]\Asm02\asm02 -L not16.asm
[Your_Path]\Asm02\asm02 -L bool16.asm
[Your_Path]\Asm02\asm02 -L inv16.asm
[Your_Path]\Asm02\asm02 -L shl16.asm
[Your_Path]\Asm02\asm02 -L shr16.asm
[Your_Path]\Asm02\asm02 -L vpush16.asm
[Your_Path]\Asm02\asm02 -L vpop16.asm
[Your_Path]\Asm02\asm02 -L vpush8.asm
[Your_Path]\Asm02\asm02 -L vpop8.asm
[Your_Path]\Asm02\asm02 -L dpush16.asm
[Your_Path]\Asm02\asm02 -L dpush8.asm
[Your_Path]\Asm02\asm02 -L esmove.asm
[Your_Path]\Asm02\asm02 -L linit16.asm
[Your_Path]\Asm02\asm02 -L lstor16.asm
[Your_Path]\Asm02\asm02 -L lstor8.asm
[Your_Path]\Asm02\asm02 -L vstor16.asm
[Your_Path]\Asm02\asm02 -L vstor8.asm
[Your_Path]\Asm02\asm02 -L swap16.asm
[Your_Path]\Asm02\asm02 -L lpush16.asm
[Your_Path]\Asm02\asm02 -L lpush8.asm
[Your_Path]\Asm02\asm02 -L deref16.asm
[Your_Path]\Asm02\asm02 -L deref8.asm
[Your_Path]\Asm02\asm02 -L laddr16.asm
[Your_Path]\Asm02\asm02 -L pstor16.asm
[Your_Path]\Asm02\asm02 -L pstor8.asm
[Your_Path]\Asm02\asm02 -L scltos16.asm
[Your_Path]\Asm02\asm02 -L sclsos16.asm
[Your_Path]\Asm02\asm02 -L unscl16.asm
[Your_Path]\Asm02\asm02 -L vinc16.asm
[Your_Path]\Asm02\asm02 -L vdec16.asm
[Your_Path]\Asm02\asm02 -L vinc8.asm
[Your_Path]\Asm02\asm02 -L vdec8.asm
[Your_Path]\Asm02\asm02 -L linc16.asm
[Your_Path]\Asm02\asm02 -L ldec16.asm
[Your_Path]\Asm02\asm02 -L linc8.asm
[Your_Path]\Asm02\asm02 -L ldec8.asm
[Your_Path]\Asm02\asm02 -L vpinc16.asm
[Your_Path]\Asm02\asm02 -L vpdec16.asm
[Your_Path]\Asm02\asm02 -L lpinc16.asm
[Your_Path]\Asm02\asm02 -L lpdec16.asm
[Your_Path]\Asm02\asm02 -L psave.asm
[Your_Path]\Asm02\asm02 -L pinc16.asm
[Your_Path]\Asm02\asm02 -L pinc8.asm
[Your_Path]\Asm02\asm02 -L pdec16.asm
[Your_Path]\Asm02\asm02 -L pdec8.asm
[Your_Path]\Asm02\asm02 -L pincptr.asm
[Your_Path]\Asm02\asm02 -L pdecptr.asm
[Your_Path]\Asm02\asm02 -L escheck.asm


type epush16.prg dpop16.prg vpush16.prg vpop16.prg dpush16.prg dpush8.prg > elfc.lib
type epush8.prg dpop8.prg vpush8.prg vpop8.prg lstor16.prg linit16.prg esmove.prg >> elfc.lib
type abs16.prg add16.prg and16.prg atoi16.prg div16.prg eq16.prg false16.prg >> elfc.lib
type gt16.prg gte16.prg itoa16.prg lfsrshift.prg lt16.prg lte16.prg mdnorm16.prg >> elfc.lib
type mod16.prg mul16.prg ne16.prg neg16.prg or16.prg rnd16.prg sgn16.prg sub16.prg >> elfc.lib
type tobcd16.prg true16.prg xor16.prg not16.prg bool16.prg inv16.prg >> elfc.lib
type shl16.prg shr16.prg vstor16.prg vstor8.prg lstor8.prg swap16.prg >> elfc.lib
type lpush16.prg lpush8.prg deref16.prg deref8.prg laddr16.prg pstor16.prg pstor8.prg >> elfc.lib
type scltos16.prg sclsos16.prg unscl16.prg vinc16.prg vdec16.prg vinc8.prg vdec8.prg >> elfc.lib
type linc16.prg ldec16.prg linc8.prg ldec8.prg lpinc16.prg lpdec16.prg >> elfc.lib
type vpinc16.prg vpdec16.prg psave.prg pinc16.prg pdec16.prg pinc8.prg pdec8.prg >> elfc.lib
type pincptr.prg pdecptr.prg escheck.prg >> elfc.lib

copy elfc.lib ..\elfc.lib 
