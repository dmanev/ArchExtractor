@echo off
rem -------------------------
rem -------------------------
rem  Compilation cible ASSP3
rem -------------------------
rem -------------------------

rem ---------------------------------------------------------------
rem  Arguments:
rem  -----------
rem   %1: Nom et chemin du fichier source (D:\COMPIL\TEST.S26) /input path/
rem   %2: Nom du fichier source sans extension (TEST)          /file name/
rem   %3: Repertoire de compilation (.\DEBUG)                  /output dir/
rem ---------------------------------------------------------------

rem  Definition des chemins
rem ------------------------
set COMPIL_PATH="C:\Program Files\IAR Systems\Embedded Workbench 5.0\78k"
set AS_EXE=%COMPIL_PATH%\bin\a78k.exe
set CC_EXE=%COMPIL_PATH%\bin\icc78k.exe
set INC_PATH=%2
set OUT_FILE=%3\%2.R26
set OUT_LST=%3\%2.LST

rem  Options de compilation
rem ------------------------
set AS_OPTS= -v1 -r -D__BANKED_MODEL__ 
rem Obsolete options (from STK V03.12): -re /generate debug information including sorce file/

rem  Compilation du fichier
rem ------------------------
echo Compilation %2
%AS_EXE% %AS_OPTS% -l %OUT_LST% -o %OUT_FILE% %1
echo Empty>%3\%2.OBJ
