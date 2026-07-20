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
..\asm02 -L _mulfp.asm
..\asm02 -L _subfp.asm
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


type _addfp.prg _addtows.prg _atof.prg _atoi32.prg _divfp.prg _fp_const.prg > float32.lib
type _fpacos.prg _fpargs.prg _fpasin.prg _fpatan.prg _fpcomp2.prg _fpcopy.prg >> float32.lib
type _fpcos.prg _fpexp.prg _fpln.prg _fpnorm.prg _fppow.prg _fpret0.prg >> float32.lib
type _fpreta.prg _fpretb.prg _fpretinf.prg _fpsin.prg _fpsqrt.prg >> float32.lib
type _getargs.prg _i32tof.prg _fptan.prg _ftos.prg _ftoi32.prg _ftrunc.prg >> float32.lib
type _mulfp.prg _subfp.prg _trigdata.prg absf.prg acosf.prg addf.prg >> float32.lib
type areducef.prg asinf.prg atanf.prg atan2f.prg atof.prg ceilf.prg cosf.prg >> float32.lib
type coshf.prg deg2radf.prg divf.prg eqf.prg expf.prg floorf.prg fmodf.prg >> float32.lib
type fracf.prg frexpf.prg fstrf.prg ftoa.prg ftoi32.prg ftoi.prg ftosci.prg >> float32.lib
type gtf.prg gtef.prg hypotf.prg itof.prg i32tof.prg invf.prg ldexpf.prg >> float32.lib
type logf.prg log2f.prg log10f.prg ltf.prg ltef.prg makef.prg modf.prg mulf.prg >> float32.lib
type nef.prg negf.prg powf.prg rad2degf.prg roundf.prg samef.prg sgnf.prg >> float32.lib
type sinf.prg sinhf.prg sqrtf.prg subf.prg tanf.prg tanhf.prg truncf.prg >> float32.lib
type zflushf.prg >> float32.lib

copy float32.lib ..\lib\float32.lib
