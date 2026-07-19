..\asm02 -L _addfp.asm
..\asm02 -L _divfp.asm
..\asm02 -L _fpargs.asm
..\asm02 -L _fpcomp2.asm
..\asm02 -L _fpnorm.asm
..\asm02 -L _fpret0.asm
..\asm02 -L _fpreta.asm
..\asm02 -L _fpretb.asm
..\asm02 -L _fpretinf.asm
..\asm02 -L _ftos.asm
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
..\asm02 -L _fpln.asm
..\asm02 -L _fpexp.asm
..\asm02 -L _fppow.asm
..\asm02 -L _i32tof.asm

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
..\elfc -L ftos.c
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
..\elfc -L areducef.c
..\elfc -L truncf.c
..\elfc -L fracf.c
..\elfc -L modf.c
..\elfc -L negf.c
..\elfc -L ceilf.c
..\elfc -L floorf.c
..\elfc -L roundf.c
..\elfc -L frexpf.c
..\elfc -L fmodf.c
..\elfc -L atan2f.c
..\elfc -L logf.c
..\elfc -L expf.c
..\elfc -L powf.c
..\elfc -L log10f.c
..\elfc -L log2f.c
..\elfc -L zflushf.c
..\elfc -L invf.c
..\elfc -L deg2radf.c
..\elfc -L rad2degf.c
..\elfc -L hypotf.c
..\elfc -L ldexpf.c
..\elfc -L _fp_const.c
..\elfc -L sinhf.c
..\elfc -L coshf.c
..\elfc -L tanhf.c
..\elfc -L i32tof.c
..\elfc -L itof.c
..\elfc -L ftoi.c
..\elfc -L samef.c
..\elfc -L fstrf.c


type _addfp.prg _addtows.prg _atof.prg _atoi32.prg _divfp.prg _eqfp.prg > float32.lib
type _false32.prg _fp_const.prg _fpacos.prg _fpargs.prg _fpasin.prg _fpatan.prg >> float32.lib
type _fpcomp2.prg _fpcopy.prg _fpcos.prg _fpexp.prg _fpln.prg  >> float32.lib
type _fpnorm.prg _fppow.prg _fpret0.prg _fpreta.prg _fpretb.prg _fpretinf.prg >> float32.lib
type _fpsin.prg _fpsqrt.prg _fptan.prg _ftos.prg _ftoi32.prg _ftrunc.prg >> float32.lib
type _getargs.prg _gtfp.prg _gtefp.prg _i32tof.prg _itoa32.prg _ltfp.prg _ltefp.prg >> float32.lib
type _mulfp.prg _nefp.prg _subfp.prg _tobcd32.prg _trigdata.prg _true32.prg absf.prg >> float32.lib
type acosf.prg addf.prg areducef.prg asinf.prg atanf.prg atan2f.prg atof.prg >> float32.lib
type cosf.prg coshf.prg ceilf.prg deg2radf.prg divf.prg eqf.prg expf.prg floorf.prg >> float32.lib
type fmodf.prg fracf.prg frexpf.prg fstrf.prg ftoa.prg ftoi32.prg ftoi.prg ftos.prg >> float32.lib
type gtf.prg gtef.prg hypotf.prg itof.prg i32tof.prg invf.prg ldexpf.prg logf.prg >> float32.lib
type log2f.prg log10f.prg ltf.prg ltef.prg modf.prg mulf.prg nef.prg negf.prg >> float32.lib
type powf.prg rad2degf.prg roundf.prg samef.prg sgnf.prg sinf.prg sinhf.prg >> float32.lib
type sqrtf.prg subf.prg tanf.prg tanhf.prg truncf.prg zflushf.prg >> float32.lib

copy float32.lib ..\lib\float32.lib
