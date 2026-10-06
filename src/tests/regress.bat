@echo off
rem Build all of the test programs, like the Makefile does.
rem The options can be given in any order:
rem   regress                 build for Elf/OS
rem   regress elfdos          build for ELF-DOS
rem   regress stgrom          the BRKPT macro breaks into the STG ROM
rem   regress maxmon          the BRKPT macro breaks into the MAXMON ROM
rem   regress elfdos maxmon   build for ELF-DOS with MAXMON breakpoints
rem Without stgrom or maxmon the BRKPT macro does nothing.
setlocal
set TARGET=
set BRKPT=
set BAD=
for %%a in (%*) do (
  if /i "%%a"=="elfos" (set TARGET=) else if /i "%%a"=="elfdos" (set TARGET=-E) else if /i "%%a"=="none" (set BRKPT=) else if /i "%%a"=="stgrom" (set BRKPT=-D _STGROM_) else if /i "%%a"=="maxmon" (set BRKPT=-D _MAXMON_) else (set BAD=%%a)
)
if defined BAD (
  echo Unknown option '%BAD%', use elfos or elfdos, and none, stgrom or maxmon
  exit /b 1
)
for %%f in (*.c) do (
  echo Building: %%f
  call clean %%~nf
  elfc -O %TARGET% %BRKPT% %%f
)
endlocal
