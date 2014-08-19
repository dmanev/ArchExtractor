@echo off
rem -------------------------
rem -------------------------
rem  Compilation cible ASSP3
rem -------------------------
rem -------------------------

rem ---------------------------------------------------------------
rem  Arguments:
rem  -----------
rem   %1: Nom et chemin du fichier source (C:\COMPIL\TEST.C)
rem   %2: Chemin du fichier source (C:\COMPIL)
rem   %3: Nom du fichier source sans extension (TEST)
rem   %4: Extension du fichier source (C)
rem   %5: Repertoire de compilation (.\DEBUG)
rem   %6: Nom ajoute a la constante CIBLE (EMULEE pour CIBLEEMULEE)
rem ---------------------------------------------------------------

rem  Definition des chemins
rem ------------------------
set COMPIL_PATH="C:\Program Files\IAR Systems\Embedded Workbench 5.0\78k"
set AS_EXE=%COMPIL_PATH%\bin\a78k.exe
set CC_EXE=%COMPIL_PATH%\bin\icc78k.exe
set OUT_FILE=%5\%3.R26
set OUT_LST=%5\%3.LST

rem  Options de compilation
rem ------------------------
rem Common CC options:
set CC_OPTS= --code_model standard --core 78k0 -e -DMEM_TYPE=__banked -DMEM_FAST=__saddr -DCALLT_TYPE=__callt -DX90_PROJECT --generate_callt_runtime_library_calls
rem Obsolete options (from STK V3.12): -mS /standard code model/, -v1 /processor 78K/0/, -P /code in ROM/, -q /insert mnemonic in listing/ -C /nested comments/ -K /C++ comments/ -g /global strict type checking/
set INCLUDES=-I%COMPIL_PATH%\inc -I%COMPIL_PATH%\inc\clib -I. -I..\EXE\GEN\ -I..\SOURCES\DAT -I..\SOURCES\LAP -I..\SOURCES\LDB_API -I..\SOURCES\LIB -I..\SOURCES\TOS -I.\LDB


if %6==PERFCNT goto OptionsPerfCnt
if %6==TRACECPU goto OptionsTraceCpu
if %6==EMUL goto OptionsEmul
if %6==ROM goto OptionsRom

:OptionsEmul
set CC_OPTS=%CC_OPTS% -r -Ohs
set DEFINES=-DEMUL -DDEBUG -DUSE_LIBSTK -DDONT_KEEP_OLD_TYPE_COMPATIBILITY
goto FinOptions

:OptionsPerfCnt
set CC_OPTS=%CC_OPTS% -r -Ohs
set DEFINES=-DEMUL -DDEBUG -DUSE_LIBSTK -DDONT_KEEP_OLD_TYPE_COMPATIBILITY -DTOS_PERF_CNT_ENABLE
goto FinOptions

:OptionsTraceCpu
set CC_OPTS=%CC_OPTS% -r -Ohs
set DEFINES=-DEMUL -DDEBUG -DUSE_LIBSTK -DTRACE_CPU_ACTIVE -DDONT_KEEP_OLD_TYPE_COMPATIBILITY
goto FinOptions

:OptionsRom
set CC_OPTS=%CC_OPTS% -Ohs
set DEFINES=-DROM -DUSE_LIBSTK -DDONT_KEEP_OLD_TYPE_COMPATIBILITY 
goto FinOptions

:FinOptions

rem  Compilation du fichier
rem ------------------------
echo Compiling %3.%4
%CC_EXE% %CC_OPTS% %INCLUDES% %DEFINES% -l %OUT_LST% -o %OUT_FILE% %1