@echo off
rem ------------------
rem ------------------
rem  link cible ASSP3
rem ------------------
rem ------------------

rem ---------------------------------------------------------------
rem  Arguments:
rem  -----------
rem   %1: Nom et chemin temporaire contenant la liste des fichiers objets (C:\COMPIL\TEST.C)
rem   %2: Nom du fichier resultat du link (DEBUG\LDB_PWM.EXE)
rem   %3: Chaine optionnelle (ParametreOptionnel)
rem ---------------------------------------------------------------

rem  Definition des chemins
rem ------------------------
set COMPIL_PATH="C:\Program Files\IAR Systems\Embedded Workbench 5.0\78k"
set LK_EXE=%COMPIL_PATH%\BIN\XLINK
set LB_EXE=%COMPIL_PATH%\BIN\XLIB
rem C Library: choose 'cl78ks1.r26' (78K0 non-banked) or 'cl78kb1.r26' (78K0 banked) both with MUL/DIV instructions
set SYS_LIB=%COMPIL_PATH%\lib\clib\cl78ks1.r26 ..\TARGET\LDB\LIB_PCF.R26 ..\TARGET\LDB\LIB_CFD.R26 ..\TARGET\LDB\LIB_VLG2.R26 ..\TARGET\LDB\LIB_LRN.R26

rem  Options du link
rem -----------------
rem 
rem -x cross reference list [	s segment map
rem 							m modul map
rem 							e symbol listing
rem                             n modules summary
rem                             h html format
rem 						]
rem -F output format			
rem 
rem -J checksum
rem 
rem -H Definition of Fillbyte for unused bytes
rem

rem Set here common link options:
set LK_OPTS= -xsmen -J2,sum -HBF -s __program_start

if %3==CPUTRACE goto ConfigCpuTrace
if %3==PERFCNT goto ConfigPerfCnt
if %3==EMUL goto ConfigEmul
if %3==ROM goto ConfigRom
echo cc.bat: Type de cible non defini (option /MODEEMUL ou /MODEROM)

goto Fin

rem Specific linker options depending on configuration
rem Refer to ZCODE.TXT for more comments

:ConfigEmul
set LK_OPTS=%LK_OPTS% -r -Fxcoff78K
set LK_OPTS=%LK_OPTS% -D_APPLICATION_CHECKSUM_START=7FFE -D_CODEBANK3_END=3BFFF
set MAPFILE= ..\Exe\target_d.map
goto FinConfig

:ConfigCpuTrace
set LK_OPTS=%LK_OPTS% -r -Fxcoff78K
set LK_OPTS=%LK_OPTS% -D_APPLICATION_CHECKSUM_START=7FFE -D_CODEBANK3_END=3BFFF
set MAPFILE= ..\Exe\target_t.map
goto FinConfig

:ConfigPerfCnt
set LK_OPTS=%LK_OPTS% -r -Fxcoff78K
set LK_OPTS=%LK_OPTS% -D_APPLICATION_CHECKSUM_START=7FFE -D_CODEBANK3_END=3BFFF
set MAPFILE= ..\Exe\target_p.map
goto FinConfig

:ConfigRom
set LK_OPTS=%LK_OPTS%  -FMOTOROLA-S28 -D_APPLICATION_CHECKSUM_START=67F4 -D_CODEBANK3_END=3ABFF
rem Option -M is for creation of real address banked segments
set LK_OPTS=%LK_OPTS% -M(CODE)_CODEBANK1_START-_CODEBANK1_END=_REAL_CODEBANK1_START
set LK_OPTS=%LK_OPTS% -M(CODE)_CODEBANK2_START-_CODEBANK2_END=_REAL_CODEBANK2_START
set LK_OPTS=%LK_OPTS% -M(CODE)_CODEBANK3_START-_CODEBANK3_END=_REAL_CODEBANK3_START
set MAPFILE= ..\exe\target_r.map

goto FinConfig
:FinConfig

rem  Link du fichier
rem -----------------
%LK_EXE% -f %1 -c78000 -f ZCode.txt -C %SYS_LIB% %LK_OPTS% -l %MAPFILE% -o %2

if %3==ROM  goto Ulp
goto Fin

:Ulp

if not exist ..\EXE\target_r.hex goto Fin

:GenerateUlp
echo .
echo *** Generating downloadable ULP file ***
echo .
  
..\..\TOOLS\TARGET\TRANSFOR\transfor @..\..\TOOLS\TARGET\TRANSFOR\78K0_X90_BCM.tfm

if not exist ..\..\..\..\BOOT_K0\BOOT\BUILD\EXE\target_r.hex goto Fin

:GenerateImage
echo .
echo *** Generating image (application with bootloader) HEX file ***
echo .

cd ..\..\TOOLS\TARGET\TRANSFOR
nmake -f X90_image.mak

:Fin
