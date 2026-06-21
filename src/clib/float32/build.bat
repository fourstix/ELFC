..\asm02 -L _addfp.asm
..\asm02 -L _divfp.asm
..\asm02 -L _fpargs.asm
..\asm02 -L _fpcomp2.asm
..\asm02 -L _fpdata.asm
..\asm02 -L _fpnorm.asm
..\asm02 -L _fpret0.asm
..\asm02 -L _fpreta.asm
..\asm02 -L _fpretb.asm
..\asm02 -L _fpretinf.asm
..\asm02 -L _ftoa.asm
..\asm02 -L _itoa32.asm
..\asm02 -L _mulfp.asm
..\asm02 -L _subfp.asm
..\asm02 -L _tobcd32.asm
..\asm02 -L _true32.asm
..\asm02 -L _false32.asm
..\asm02 -L _eqfp.asm
..\asm02 -L _nefp.asm
..\asm02 -L _gtfp.asm
..\asm02 -L _gtefp.asm
..\asm02 -L _ltfp.asm
..\asm02 -L _ltefp.asm
..\asm02 -L _atof.asm
..\asm02 -L _atoi32.asm
..\asm02 -L _ftoi32.asm
..\asm02 -L _trigdata.asm
..\asm02 -L _addtows.asm
..\asm02 -L _getargs.asm
..\asm02 -L _fpcopy.asm
..\asm02 -L _fpsqrt.asm
..\asm02 -L _fpsin.asm
..\asm02 -L _fpcos.asm
..\asm02 -L _fptan.asm
..\asm02 -L _fpasin.asm
..\asm02 -L _fpacos.asm
..\asm02 -L _fpatan.asm
..\asm02 -L _ftrunc.asm

..\elfc -L addf.c
..\elfc -L divf.c
..\elfc -L mulf.c
..\elfc -L subf.c
..\elfc -L eqf.c
..\elfc -L nef.c
..\elfc -L gtf.c
..\elfc -L gtef.c
..\elfc -L ltf.c
..\elfc -L ltef.c
..\elfc -L ftoa.c
..\elfc -L atof.c
..\elfc -L absf.c
..\elfc -L sgnf.c
..\elfc -L ftoi32.c
..\elfc -L sinf.c
..\elfc -L cosf.c
..\elfc -L tanf.c
..\elfc -L asinf.c
..\elfc -L acosf.c
..\elfc -L atanf.c
..\elfc -L sqrtf.c
..\elfc -L _reduce.c
..\elfc -L truncf.c
..\elfc -L fracf.c
..\elfc -L modf.c
..\elfc -L negf.c
..\elfc -L ceilf.c
..\elfc -L floorf.c
..\elfc -L roundf.c
..\elfc -L frexpf.c

type _addfp.prg _addtows.prg _atof.prg _atoi32.prg _divfp.prg _eqfp.prg > float32.lib
type _false32.prg _fpacos.prg _fpargs.prg _fpasin.prg _fpatan.prg >> float32.lib
type _fpcomp2.prg _fpcopy.prg _fpcos.prg _fpdata.prg _fpnorm.prg >> float32.lib
type _fpret0.prg _fpreta.prg _fpretb.prg _fpretinf.prg _fpsin.prg _fpsqrt.prg >> float32.lib
type _fptan.prg _ftoa.prg _ftoi32.prg _ftrunc.prg _getargs.prg _gtfp.prg _gtefp.prg >> float32.lib
type _ltfp.prg _ltefp.prg _mulfp.prg _nefp.prg _reduce.prg _subfp.prg _tobcd32.prg _itoa32.prg >> float32.lib
type _trigdata.prg _true32.prg absf.prg acosf.prg addf.prg asinf.prg atanf.prg >> float32.lib
type atof.prg cosf.prg ceilf.prg divf.prg eqf.prg floorf.prg fracf.prg frexpf.prg>> float32.lib
type ftoa.prg ftoi32.prg gtf.prg gtef.prg ltf.prg ltef.prg modf.prg mulf.prg >> float32.lib
type nef.prg negf.prg roundf.prg sgnf.prg sinf.prg sqrtf.prg subf.prg >> float32.lib
type tanf.prg truncf.prg >> float32.lib

copy float32.lib ..\lib\float32.lib
