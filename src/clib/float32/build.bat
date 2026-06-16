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
..\asm02 -L _sgnfp.asm


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


type _addfp.prg _atof.prg _atoi32.prg _divfp.prg _eqfp.prg _false32.prg > float32.lib
type _fpargs.prg _fpcomp2.prg _fpdata.prg _fpnorm.prg _fpret0.prg _fpreta.prg >> float32.lib
type _fpretb.prg _fpretinf.prg _ftoa.prg _gtfp.prg _gtefp.prg _itoa32.prg >> float32.lib
type _ltfp.prg _ltefp.prg _mulfp.prg _nefp.prg _sgnfp.prg _subfp.prg _tobcd32.prg >> float32.lib
type _true32.prg absf.prg atof.prg addf.prg divf.prg eqf.prg ftoa.prg mulf.prg >> float32.lib
type nef.prg subf.prg >> float32.lib

copy float32.lib ..\lib\float32.lib
