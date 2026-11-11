..\asm02 -r -r -L _addfp.asm
..\asm02 -r -L _divfp.asm
..\asm02 -r -L _fpargs.asm
..\asm02 -r -L _fpcomp2.asm
..\asm02 -r -L _fpnorm.asm
..\asm02 -r -L _fpret0.asm
..\asm02 -r -L _fpreta.asm
..\asm02 -r -L _fpretb.asm
..\asm02 -r -L _fpretinf.asm
..\asm02 -r -L _ftos.asm
..\asm02 -r -L _mulfp.asm
..\asm02 -r -L _subfp.asm
..\asm02 -r -L _atof.asm
..\asm02 -r -L _atoi32.asm
..\asm02 -r -L _ftoi32.asm
..\asm02 -r -L _trigdata.asm
..\asm02 -r -L _addtows.asm
..\asm02 -r -L _getargs.asm
..\asm02 -r -L _fpcopy.asm
..\asm02 -r -L _fpsqrt.asm
..\asm02 -r -L _fpsin.asm
..\asm02 -r -L _fpcos.asm
..\asm02 -r -L _fptan.asm
..\asm02 -r -L _fpasin.asm
..\asm02 -r -L _fpacos.asm
..\asm02 -r -L _fpatan.asm
..\asm02 -r -L _ftrunc.asm
..\asm02 -r -L _fpln.asm
..\asm02 -r -L _fpexp.asm
..\asm02 -r -L _fppow.asm
..\asm02 -r -L _i32tof.asm

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
..\elfc -L ftosci.c
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
..\elfc -L makef.c


type _addfp.prg _addtows.prg _atof.prg _atoi32.prg _divfp.prg _fpacos.prg > float32.lib
type _fpargs.prg _fpasin.prg _fpatan.prg _fpcomp2.prg _fpcopy.prg _fpcos.prg >> float32.lib
type _fpexp.prg _fpln.prg _fpnorm.prg _fppow.prg _fpret0.prg _fpreta.prg >> float32.lib
type _fpretb.prg _fpretinf.prg _fpsin.prg _fpsqrt.prg _fptan.prg _ftoi32.prg >> float32.lib
type _ftos.prg _ftrunc.prg _getargs.prg _i32tof.prg _mulfp.prg _subfp.prg >> float32.lib
type _trigdata.prg _fp_const.prg absf.prg acosf.prg addf.prg areducef.prg >> float32.lib
type asinf.prg atan2f.prg atanf.prg atof.prg ceilf.prg cosf.prg >> float32.lib
type coshf.prg deg2radf.prg divf.prg eqf.prg expf.prg floorf.prg >> float32.lib
type fmodf.prg fracf.prg frexpf.prg fstrf.prg ftoa.prg ftoi.prg >> float32.lib
type ftoi32.prg ftosci.prg gtef.prg gtf.prg hypotf.prg i32tof.prg >> float32.lib
type invf.prg itof.prg ldexpf.prg log10f.prg log2f.prg logf.prg >> float32.lib
type ltef.prg ltf.prg makef.prg modf.prg mulf.prg nef.prg >> float32.lib
type negf.prg powf.prg rad2degf.prg roundf.prg samef.prg sgnf.prg >> float32.lib
type sinf.prg sinhf.prg sqrtf.prg subf.prg tanf.prg tanhf.prg >> float32.lib
type truncf.prg zflushf.prg >> float32.lib

copy float32.lib ..\lib\float32.lib
