..\asm02 -r -L -C crt0.asm
..\asm02 -r -L -C elfrt0.asm
copy crt0.prg ..\lib\crt0.prg
copy elfrt0.prg ..\lib\elfrt0.prg
