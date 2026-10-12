@echo off
rem Remove the files generated for one program:  clean name
del %1.asm 2>nul
del %1.build 2>nul
del %1.lst 2>nul
del %1.elfos 2>nul
del %1.prg 2>nul
del %1.sym 2>nul
del %1.lkb 2>nul
rem an ELF-DOS program has the name of its source file without an extension
if not "%~1"=="" if exist "%~1" if not exist "%~1\*" del "%~1"
