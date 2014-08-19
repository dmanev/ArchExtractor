# Microsoft Developer Studio Project File - Name="target" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=target - Win32 CpuTrace
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "target.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "target.mak" CFG="target - Win32 CpuTrace"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "target - Win32 Target Debug" (based on "Win32 (x86) Application")
!MESSAGE "target - Win32 Target Release" (based on "Win32 (x86) Application")
!MESSAGE "target - Win32 CpuTrace" (based on "Win32 (x86) Application")
!MESSAGE "target - Win32 PerfCnt" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "target - Win32 Target Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "target___Win32_Target_Debug"
# PROP BASE Intermediate_Dir "target___Win32_Target_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\TARGET_D"
# PROP Intermediate_Dir "..\EXE\TARGET_D"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CIBLEEMUL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /map /debug /machine:I386 /out:"..\EXE\target_d" /CIBLE:r26 /MODEEMUL
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "target - Win32 Target Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "target___Win32_Target_Release"
# PROP BASE Intermediate_Dir "target___Win32_Target_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\TARGET_R"
# PROP Intermediate_Dir "..\EXE\TARGET_R"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CIBLEROM" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /machine:I386 /out:"..\EXE\target_r.hex" /pdbtype:sept /CIBLE:r26 /MODEROM
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "target - Win32 CpuTrace"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "target___Win32_CpuTrace"
# PROP BASE Intermediate_Dir "target___Win32_CpuTrace"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\TARGET_T"
# PROP Intermediate_Dir "..\EXE\TARGET_T"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CIBLEROM" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CIBLETRACECPU" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /incremental:no /machine:I386 /out:"..\EXE\target_r.hex" /pdbtype:sept /CIBLE:r26 /MODEROM
# SUBTRACT BASE LINK32 /pdb:none /debug
# ADD LINK32 /nologo /subsystem:windows /incremental:no /map /debug /machine:I386 /out:"..\EXE\target_t" /pdbtype:sept /CIBLE:r26 /MODECPUTRACE
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "target - Win32 PerfCnt"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "target___Win32_PerfCnt"
# PROP BASE Intermediate_Dir "target___Win32_PerfCnt"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\TARGET_P"
# PROP Intermediate_Dir "..\EXE\TARGET_P"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CIBLEEMUL" /FR /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CIBLEPERFCNT" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /incremental:no /machine:I386 /out:"..\EXE\target_d.lnk" /CIBLE:r26 /MODEEMUL
# SUBTRACT BASE LINK32 /pdb:none /debug
# ADD LINK32 /nologo /subsystem:windows /incremental:no /machine:I386 /out:"..\EXE\target_p.d26" /CIBLE:r26 /MODEPERFCNT
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "target - Win32 Target Debug"
# Name "target - Win32 Target Release"
# Name "target - Win32 CpuTrace"
# Name "target - Win32 PerfCnt"
# Begin Group "LIB"

# PROP Default_Filter ""
# Begin Group "LIB_API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\deftypes.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB.h
# End Source File
# End Group
# Begin Group "LIB_STK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\Lib_stk.h
# End Source File
# End Group
# Begin Group "LIB_IMMO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_IMMO.H
# End Source File
# End Group
# Begin Group "LIB_PCF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_PCF.h
# End Source File
# End Group
# Begin Group "LIB_LRN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_LRN.h
# End Source File
# End Group
# Begin Group "LIB_VLG2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_VLG2.H
# End Source File
# End Group
# Begin Group "LIB_RND"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_RND.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_RND.H
# End Source File
# End Group
# Begin Group "LIB_CFD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_CFD.H
# End Source File
# End Group
# Begin Group "LIB_BOO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB_BOO.H
# End Source File
# End Group
# End Group
# Begin Group "CC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\TOOLS\TARGET\Transfor\78K0_X90_BCM.tfm
# End Source File
# Begin Source File

SOURCE=.\asm.bat
# End Source File
# Begin Source File

SOURCE=.\cc.bat
# End Source File
# Begin Source File

SOURCE=.\link.bat
# End Source File
# Begin Source File

SOURCE=..\..\TOOLS\TARGET\Transfor\X90_image.bat
# End Source File
# Begin Source File

SOURCE=..\..\TOOLS\TARGET\Transfor\X90_image.mak
# End Source File
# Begin Source File

SOURCE=.\ZCode.txt
# End Source File
# End Group
# Begin Group "TOS"

# PROP Default_Filter ""
# Begin Group "TOS_ALA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_ala.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_ala.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\TOS_ALA.JIL
# End Source File
# End Group
# Begin Group "TOS_ORD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_ord.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_ord.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\TOS_ORD.JIL
# End Source File
# End Group
# Begin Group "TOS_SEQ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_seq.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_seq.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\TOS_SEQ.JIL
# End Source File
# End Group
# Begin Group "TOS_SIG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_sig.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_sig.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_sig.jil
# End Source File
# End Group
# Begin Group "TOS_TPO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_tpo.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_tpo.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\TOS_TPO.JIL
# End Source File
# End Group
# Begin Group "TOS_CONFIG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\TOSParam.h
# End Source File
# End Group
# Begin Group "TOS_JIL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\TOS.JIL
# End Source File
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos_jil.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\SOURCES\TOS\Tos.h
# End Source File
# End Group
# Begin Group "LDB"

# PROP Default_Filter ""
# Begin Group "LDB_TIM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\Ldb_tim.c
# End Source File
# Begin Source File

SOURCE=.\LDB\Ldb_tim.h
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_TIMP.C
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_TIMP.H
# End Source File
# End Group
# Begin Group "LDB_Reg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\intrinsics.h
# End Source File
# Begin Source File

SOURCE=.\LDB\io78f0536_64.h
# End Source File
# Begin Source File

SOURCE=.\LDB\Ldb_reg.h
# End Source File
# End Group
# Begin Group "LDB_SUP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\Ldb_sup.c
# End Source File
# Begin Source File

SOURCE=.\LDB\Ldb_sup.h
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_sup.s26

!IF  "$(CFG)" == "target - Win32 Target Debug"

# Begin Custom Build - Assemble $(InputPath)
OutDir=.\..\EXE\TARGET_D
InputPath=.\LDB\ldb_sup.s26

"..\EXE\TARGET_D\ldb_supa.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	asm.bat $(InputPath) ldb_supa $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "target - Win32 Target Release"

# Begin Custom Build - Assemble $(InputPath)
OutDir=.\..\EXE\TARGET_R
InputPath=.\LDB\ldb_sup.s26

"..\EXE\TARGET_R\ldb_supa.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	asm.bat $(InputPath) ldb_supa $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "target - Win32 CpuTrace"

# Begin Custom Build - Assemble $(InputPath)
OutDir=.\..\EXE\TARGET_T
InputPath=.\LDB\ldb_sup.s26

"..\EXE\TARGET_T\ldb_supa.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	asm.bat $(InputPath) ldb_supa $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "target - Win32 PerfCnt"

# Begin Custom Build - Assemble $(InputPath)
OutDir=.\..\EXE\TARGET_P
InputPath=.\LDB\ldb_sup.s26

"..\EXE\TARGET_P\ldb_supa.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	asm.bat $(InputPath) ldb_supa $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "LDB_API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LDB_API\ldb.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LDB_API\ldb_tos.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LDB_API\LDBParam.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LDB_API\LDBTypes.h
# End Source File
# End Group
# Begin Group "LDB_SWI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\ldb_swi.c
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_swi.h
# End Source File
# End Group
# Begin Group "LDB_EEP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\ldb_eep.c
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_eep.h
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_eepp.h
# End Source File
# End Group
# Begin Group "LDB_INT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_INT.C
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_int.h
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_INTP.C
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_intp.h
# End Source File
# End Group
# Begin Group "LDB_HAR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\ldb_har.c
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_har.h
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_harp.h
# End Source File
# End Group
# Begin Group "LDB_IOC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_IOC.C
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_IOC.H
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_IOCP.H
# End Source File
# End Group
# Begin Group "LDB_SPI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_SPI.C
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_SPI.H
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_SPIP.H
# End Source File
# End Group
# Begin Group "LDB_DIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_DIN.C
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_DIN.H
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_DINP.H
# End Source File
# End Group
# Begin Group "LDB_DOU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_DOU.C
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_DOU.H
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_DOUP.H
# End Source File
# End Group
# Begin Group "LDB_ANA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_ANA.C
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_ANA.H
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_ANAP.H
# End Source File
# End Group
# Begin Group "LDB_KWP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_KWP.C
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_KWP.H
# End Source File
# End Group
# Begin Group "LDB_BUZ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_BUZ.c

!IF  "$(CFG)" == "target - Win32 Target Debug"

!ELSEIF  "$(CFG)" == "target - Win32 Target Release"

!ELSEIF  "$(CFG)" == "target - Win32 CpuTrace"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "target - Win32 PerfCnt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_BUZ.h
# End Source File
# End Group
# Begin Group "LDB_SPD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_SPD.c
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_SPD.h
# End Source File
# End Group
# Begin Group "LDB_ALA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_ALA.c
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_ALA.h
# End Source File
# End Group
# Begin Group "LDB_RF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_RF.c
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_RF.h
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_RFp.h
# End Source File
# End Group
# Begin Group "LDB_TRP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\ldb_trp.c
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_trp.h
# End Source File
# Begin Source File

SOURCE=.\LDB\ldb_trpp.h
# End Source File
# End Group
# Begin Group "LDB_PWM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_PWM.c
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_PWM.h
# End Source File
# End Group
# Begin Group "LDB_SLD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB\LDB_SLD.c
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_SLD.h
# End Source File
# Begin Source File

SOURCE=.\LDB\LDB_SLDp.h
# End Source File
# End Group
# End Group
# Begin Group "DAT"

# PROP Default_Filter ""
# Begin Group "DAT_CPU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_CPU.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_CPU.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_CPU.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_CPUP.H
# End Source File
# End Group
# Begin Group "DAT_API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\dat.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DATParam.h
# End Source File
# End Group
# Begin Group "DAT_EEP"

# PROP Default_Filter ""
# Begin Group "EEP."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_EEP.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_EEP.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_eep.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_EEPp.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_EEPx.h
# End Source File
# End Group
# Begin Group "PEE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_EEP.XLS
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_EEPM.XLA
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PEE.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_pee.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_pee.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_pee.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_pee.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_peep.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PEEx.h
# End Source File
# End Group
# Begin Group "DBK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DBK.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Dbk.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_dbk.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Dbkp.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DBKx.h
# End Source File
# End Group
# Begin Group "SBK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_SBK.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Sbk.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Sbk.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Sbkp.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_SBKx.h
# End Source File
# End Group
# Begin Group "DEA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DEA.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_dea.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_dea.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_deap.h
# End Source File
# End Group
# End Group
# Begin Group "DAT_ANA"

# PROP Default_Filter ""
# Begin Group "ANA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_ANA.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_ana.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_ana.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_ANAp.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_ANAP.JIL
# End Source File
# End Group
# Begin Group "PAN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PAN.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_pan.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_pan.jil
# End Source File
# End Group
# End Group
# Begin Group "DAT_DIO"

# PROP Default_Filter ""
# Begin Group "DAT_DIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DIN.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Din.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Din.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Dinp.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DINP.JIL
# End Source File
# End Group
# Begin Group "DAT_PIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PIN.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Pin.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_Pin.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_Pinp.h
# End Source File
# End Group
# Begin Group "DAT_DOU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DOU.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_dou.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DOU.JIL
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DOUP.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_DOUP.JIL
# End Source File
# End Group
# Begin Group "DAT_POU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_POU.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_POU.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_POU.JIL
# End Source File
# End Group
# End Group
# Begin Group "DAT_CMN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_CMN.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_CMN.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_CMN.jil
# End Source File
# End Group
# Begin Group "DAT_KWP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_KWP.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_KWP.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_KWP.JIL
# End Source File
# End Group
# Begin Group "DAT_PWM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PWM.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PWM.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PWM.JIL
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_PWMP.H
# End Source File
# End Group
# Begin Group "DAT_BUZ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_BUZ.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_BUZ.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_BUZ.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_BUZp.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_BUZx.h
# End Source File
# End Group
# Begin Group "DAT_SPD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_SPD.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_SPD.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_SPD.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_SPD.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_SPD.jil
# End Source File
# End Group
# Begin Group "DAT_ALA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_ALA.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_ALA.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_ALA.jil
# End Source File
# End Group
# Begin Group "DAT_RBG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_RBG.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_RBG.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_RBG.jil
# End Source File
# End Group
# Begin Group "DAT_RF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_RF.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_RF.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_RF.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_RF.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_RF.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\Dat_RFp.h
# End Source File
# End Group
# Begin Group "DAT_APR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_apr.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_apr.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_apr.jil
# End Source File
# End Group
# Begin Group "DAT_TRP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_TRP.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_TRP.GFT
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_TRP.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_TRP.HGR
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_TRP.jil
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\dat_trpp.h
# End Source File
# End Group
# Begin Group "DAT_VLG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_VLG.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_VLG.GFT
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_VLG.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_VLG.HGR
# End Source File
# Begin Source File

SOURCE=..\SOURCES\DAT\DAT_VLG.jil
# End Source File
# End Group
# End Group
# Begin Group "LAP"

# PROP Default_Filter ""
# Begin Group "SUP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\lap_sup.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\lap_sup.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\lap_sup.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\lap_sup.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\lap_sup.jil

!IF  "$(CFG)" == "target - Win32 Target Debug"

# Begin Custom Build
InputPath=..\SOURCES\LAP\lap_sup.jil

BuildCmds= \
	cd ..\sources \
	ANALYSE.BAT $(InputPath) \
	

"..\EXE\GEN\JIL.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\EXE\GEN\JILi.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "target - Win32 Target Release"

# Begin Custom Build
InputPath=..\SOURCES\LAP\lap_sup.jil

BuildCmds= \
	cd ..\sources \
	ANALYSE.BAT $(InputPath) \
	

"..\EXE\GEN\JIL.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\EXE\GEN\JILi.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "target - Win32 CpuTrace"

# Begin Custom Build
InputPath=..\SOURCES\LAP\lap_sup.jil

BuildCmds= \
	cd ..\sources \
	ANALYSE.BAT $(InputPath) \
	

"..\EXE\GEN\JIL.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\EXE\GEN\JILi.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "target - Win32 PerfCnt"

# Begin Custom Build
InputPath=..\SOURCES\LAP\lap_sup.jil

BuildCmds= \
	cd ..\sources \
	SCC2\SCC2.EXE $(InputPath) -D:TOS_PERF_CNT_ENABLE -PerfCnt -OUT:..\EXE\GEN -G:SCC2 -Int -DUMP:..\EXE\DB.JIL \
	SCC2\SCC2.EXE $(InputPath) -D:TOS_PERF_CNT_ENABLE -OUT:..\EXE\GENSIMU -G:SCC2 -Simu \
	

"..\EXE\GEN\JIL.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\EXE\GEN\JILi.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_SUPp.H
# End Source File
# End Group
# Begin Group "DIAG"

# PROP Default_Filter ""
# Begin Group "KWP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_KWP.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_KWP.GFT
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_KWP.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_KWP.HGR
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_KWP.JIL
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_KWPP.H
# End Source File
# End Group
# Begin Group "AFS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_AFS.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_AFS.GFT
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_AFS.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_AFS.HGR
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_AFS.JIL
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_AFSP.H
# End Source File
# End Group
# Begin Group "DVP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DVP.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DVP.H
# End Source File
# End Group
# Begin Group "TFC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_TFC.C
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_TFC.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_TFC.H
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_TFC.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_TFC.JIL
# End Source File
# End Group
# End Group
# Begin Group "ILL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ILL.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ILL.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ILL.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ILL.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ILL.jil
# End Source File
# End Group
# Begin Group "BUZ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_BUZ.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_BUZ.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_BUZ.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_BUZ.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_BUZ.jil
# End Source File
# End Group
# Begin Group "FLI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FLI.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FLI.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FLI.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FLI.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FLI.jil
# End Source File
# End Group
# Begin Group "DFR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DFR.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DFR.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DFR.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DFR.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DFR.jil
# End Source File
# End Group
# Begin Group "ALA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ALA.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ALA.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ALA.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ALA.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_ALA.jil
# End Source File
# End Group
# Begin Group "FRW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FRW.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FRW.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FRW.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FRW.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_FRW.jil
# End Source File
# End Group
# Begin Group "DLK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DLK.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DLK.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DLK.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DLK.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_DLK.jil
# End Source File
# End Group
# Begin Group "CAR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_CAR.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_CAR.GFT
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_CAR.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_CAR.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_CAR.jil
# End Source File
# End Group
# Begin Group "LRN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_LRN.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_LRN.GFT
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_LRN.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_LRN.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_LRN.jil
# End Source File
# End Group
# Begin Group "VLD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_VLD.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_VLD.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_VLD.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_VLD.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_VLD.jil
# End Source File
# End Group
# Begin Group "RRW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_RRW.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_RRW.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_RRW.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_RRW.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_RRW.jil
# End Source File
# End Group
# Begin Group "EXL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_EXL.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_EXL.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_EXL.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_EXL.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_EXL.jil
# End Source File
# End Group
# Begin Group "PAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_PAL.c
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_PAL.gft
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_PAL.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_PAL.hgr
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LAP\LAP_PAL.jil
# End Source File
# End Group
# End Group
# Begin Group "Auto=..\SOURCES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB.JIL
# End Source File
# End Group
# Begin Group "Auto=."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EXE\target_d.map
# End Source File
# Begin Source File

SOURCE=..\EXE\target_r.map
# End Source File
# Begin Source File

SOURCE=..\EXE\target_t.map
# End Source File
# End Group
# Begin Group "Auto=..\EXE\GEN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EXE\GEN\DAT_ANAx.h
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\DAT_DINx.h
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\DAT_DOUx.h
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\DAT_PANx.H
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\DAT_PINx.H
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\DAT_POUx.H
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\JIL.H
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\JILI.H
# End Source File
# Begin Source File

SOURCE=..\EXE\GEN\TOS_PERFCNTP.H
# End Source File
# End Group
# End Target
# End Project
