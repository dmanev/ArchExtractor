# Microsoft Developer Studio Project File - Name="simu" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=simu - Win32 PC Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "simu.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "simu.mak" CFG="simu - Win32 PC Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "simu - Win32 PC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "simu - Win32 PC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "simu - Win32 PC PerfCnt" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "simu - Win32 PC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "simu___Win32_PC_Debug"
# PROP BASE Intermediate_Dir "simu___Win32_PC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\PC_D\Src"
# PROP Intermediate_Dir "..\EXE\PC_D\Src"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /W3 /Gm /GX /Zi /Od /I "..\EXE\GEN" /I ".\LIB" /I ".\LDB_API" /I ".\DAT" /I ".\LAP" /I ".\TOS" /D "_DEBUG" /D MEM_FAST= /D "WIN32" /D "_MBCS" /D "_LIB" /D "COMPILATION_NATIVE" /D "USE_LIBSTK" /D "DONT_KEEP_OLD_TYPE_COMPATIBILITY" /D MEM_TYPE= /D CALLT_TYPE= /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\EXE\PC_D\pc_d.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Building LDBPC
PostBuild_Cmds=if exist ..\EXE\PC_D.exe del ..\EXE\PC_D.exe	msdev ..\Simulation\Tools.dsp /MAKE "Tools - Win32 PC Debug" /BUILD
# End Special Build Tool

!ELSEIF  "$(CFG)" == "simu - Win32 PC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "simu___Win32_PC_Release"
# PROP BASE Intermediate_Dir "simu___Win32_PC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\EXE\PC_R\Src"
# PROP Intermediate_Dir "..\EXE\PC_R\Src"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Zp1 /W3 /GX /O2 /I "..\EXE\GEN" /I ".\LIB" /I ".\LDB_API" /I ".\DAT" /I ".\LAP" /I ".\TOS" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "COMPILATION_NATIVE" /D "USE_LIBSTK" /D "DONT_KEEP_OLD_TYPE_COMPATIBILITY" /D MEM_TYPE= /D MEM_FAST= /D CALLT_TYPE= /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\EXE\PC_R\pc_r.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Building LDBPC
PostBuild_Cmds=if exist ..\EXE\PC_R.exe del ..\EXE\PC_R.exe	msdev ..\Simulation\Tools.dsp /MAKE "Tools - Win32 PC Release" /BUILD
# End Special Build Tool

!ELSEIF  "$(CFG)" == "simu - Win32 PC PerfCnt"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "simu___Win32_PC_PerfCnt"
# PROP BASE Intermediate_Dir "simu___Win32_PC_PerfCnt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\PC_P\Src"
# PROP Intermediate_Dir "..\EXE\PC_P\Src"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /W3 /Gm /GX /Zi /Od /I "..\EXE\GEN" /I ".\LIB" /I ".\LDB_API" /I ".\DAT" /I ".\LAP" /I ".\TOS" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "COMPILATION_NATIVE" /D "USE_LIBSTK" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /Zp1 /W3 /Gm /GX /Zi /Od /I "..\EXE\GEN" /I ".\LIB" /I ".\LDB_API" /I ".\DAT" /I ".\LAP" /I ".\TOS" /D "_DEBUG" /D "USE_DFA" /D "WIN32" /D "_MBCS" /D "_LIB" /D "COMPILATION_NATIVE" /D "USE_LIBSTK" /D "DONT_KEEP_OLD_TYPE_COMPATIBILITY" /D MEM_TYPE= /D MEM_FAST= /D CALLT_TYPE= /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\EXE\PC_D\pc_d.lib"
# ADD LIB32 /nologo /out:"..\EXE\PC_P\pc_p.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Building LDBPC
PostBuild_Cmds=if exist ..\EXE\PC_P.exe del ..\EXE\PC_P.exe	msdev ..\Simulation\Tools.dsp /MAKE "Tools - Win32 PerfCnt" /BUILD
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "simu - Win32 PC Debug"
# Name "simu - Win32 PC Release"
# Name "simu - Win32 PC PerfCnt"
# Begin Group "LIB"

# PROP Default_Filter ""
# Begin Group "LIB_API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\deftypes.h
# End Source File
# Begin Source File

SOURCE=.\LIB\LIB.C
# End Source File
# Begin Source File

SOURCE=.\LIB\LIB.h
# End Source File
# End Group
# Begin Group "LIB_STK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\Lib_stk.h
# End Source File
# End Group
# Begin Group "LIB_IMMO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\LIB_IMMO.H
# End Source File
# End Group
# Begin Group "LIB_PCF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\LIB_PCF.h
# End Source File
# Begin Source File

SOURCE=..\Simulation\LIB\LIB_PCF.lib
# End Source File
# End Group
# Begin Group "LIB_LRN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\LIB_LRN.h
# End Source File
# Begin Source File

SOURCE=..\Simulation\LIB\LIB_LRN.lib
# End Source File
# End Group
# Begin Group "LIB_VLG2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\LIB_VLG2.H
# End Source File
# Begin Source File

SOURCE=..\Simulation\LIB\LIB_VLG2.obj
# End Source File
# End Group
# Begin Group "LIB_RND"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\LIB_RND.C
# End Source File
# Begin Source File

SOURCE=.\LIB\LIB_RND.H
# End Source File
# End Group
# Begin Group "LIB_CFD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\LIB_CFD.H
# End Source File
# Begin Source File

SOURCE=..\Simulation\LIB\LIB_CFD.obj
# End Source File
# End Group
# Begin Group "LIB_BOO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\LIB_BOO.H
# End Source File
# End Group
# End Group
# Begin Group "TOS"

# PROP Default_Filter ""
# Begin Group "TOS_ORD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TOS\Tos_ord.c
# End Source File
# Begin Source File

SOURCE=.\TOS\Tos_ord.h
# End Source File
# Begin Source File

SOURCE=.\TOS\TOS_ORD.JIL
# End Source File
# End Group
# Begin Group "TOS_SEQ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TOS\Tos_seq.c
# End Source File
# Begin Source File

SOURCE=.\TOS\Tos_seq.h
# End Source File
# Begin Source File

SOURCE=.\TOS\TOS_SEQ.JIL
# End Source File
# End Group
# Begin Group "TOS_SIG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TOS\Tos_sig.c
# End Source File
# Begin Source File

SOURCE=.\TOS\Tos_sig.h
# End Source File
# Begin Source File

SOURCE=.\TOS\Tos_sig.jil
# End Source File
# End Group
# Begin Group "TOS_TPO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TOS\Tos_tpo.c
# End Source File
# Begin Source File

SOURCE=.\TOS\Tos_tpo.h
# End Source File
# Begin Source File

SOURCE=.\TOS\TOS_TPO.JIL
# End Source File
# End Group
# Begin Group "TOS_CONFIG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TOS\TOSParam.h
# End Source File
# End Group
# Begin Group "TOS_JIL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TOS\TOS.JIL
# End Source File
# Begin Source File

SOURCE=.\TOS\Tos_jil.c
# End Source File
# End Group
# Begin Group "TOS_ALA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TOS\Tos_ala.c
# End Source File
# Begin Source File

SOURCE=.\TOS\Tos_ala.h
# End Source File
# Begin Source File

SOURCE=.\TOS\TOS_ALA.JIL
# End Source File
# End Group
# Begin Source File

SOURCE=.\TOS\Tos.h
# End Source File
# End Group
# Begin Group "LDB"

# PROP Default_Filter ""
# Begin Group "LDB_API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LDB_API\ldb.h
# End Source File
# Begin Source File

SOURCE=.\LDB_API\ldb_tos.h
# End Source File
# Begin Source File

SOURCE=.\LDB_API\LDBParam.h
# End Source File
# Begin Source File

SOURCE=.\LDB_API\LDBTypes.h
# End Source File
# End Group
# End Group
# Begin Group "DAT"

# PROP Default_Filter ""
# Begin Group "DAT_CPU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_CPU.c
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_CPU.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_CPU.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_CPUP.H
# End Source File
# End Group
# Begin Group "DAT_API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\dat.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DATParam.h
# End Source File
# End Group
# Begin Group "DAT_EEP"

# PROP Default_Filter ""
# Begin Group "EEP."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_EEP.c
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_EEP.h
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_eep.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_EEPp.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_EEPx.h
# End Source File
# End Group
# Begin Group "PEE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_EEP.XLS
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_EEPM.XLA
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_pee.c
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_pee.gft
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_pee.h
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_pee.hgr
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_pee.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_peep.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_PEEx.h
# End Source File
# End Group
# Begin Group "DBK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\Dat_Dbk.c
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Dbk.H
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_dbk.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Dbkp.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_DBKx.h
# End Source File
# End Group
# Begin Group "SBK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\Dat_Sbk.c
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Sbk.H
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Sbk.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Sbkp.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_SBKx.h
# End Source File
# End Group
# Begin Group "DEA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\Dat_dea.c
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_dea.h
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_dea.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_deap.h
# End Source File
# End Group
# End Group
# Begin Group "DAT_DIO"

# PROP Default_Filter ""
# Begin Group "DAT_DIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\Dat_Din.c
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Din.h
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Din.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Dinp.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_DINP.JIL
# End Source File
# End Group
# Begin Group "DAT_PIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_PIN.C
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Pin.h
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_Pin.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_Pinp.h
# End Source File
# End Group
# Begin Group "DAT_DOU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_DOU.C
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_dou.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_DOU.JIL
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_DOUP.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_DOUP.JIL
# End Source File
# End Group
# Begin Group "DAT_POU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_POU.C
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_POU.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_POU.JIL
# End Source File
# End Group
# End Group
# Begin Group "DAT_ANA"

# PROP Default_Filter ""
# Begin Group "ANA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_ANA.C
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_ana.h
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_ana.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_ANAp.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_ANAP.JIL
# End Source File
# End Group
# Begin Group "PAN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_PAN.C
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_pan.h
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_pan.jil
# End Source File
# End Group
# End Group
# Begin Group "DAT_PWM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_PWM.C
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_PWM.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_PWM.JIL
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_PWMP.H
# End Source File
# End Group
# Begin Group "DAT_KWP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_KWP.C
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_KWP.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_KWP.JIL
# End Source File
# End Group
# Begin Group "DAT_CMN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_CMN.C
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_CMN.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_CMN.jil
# End Source File
# End Group
# Begin Group "DAT_BUZ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_BUZ.c
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_BUZ.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_BUZ.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_BUZp.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_BUZx.h
# End Source File
# End Group
# Begin Group "DAT_SPD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_SPD.c
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_SPD.gft
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_SPD.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_SPD.hgr
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_SPD.jil
# End Source File
# End Group
# Begin Group "DAT_ALA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_ALA.c
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_ALA.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_ALA.jil
# End Source File
# End Group
# Begin Group "DAT_RBG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_RBG.c
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_RBG.h
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_RBG.jil
# End Source File
# End Group
# Begin Group "DAT_RF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\Dat_RF.c
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_RF.gft
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_RF.h
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_RF.hgr
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_RF.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\Dat_RFp.h
# End Source File
# End Group
# Begin Group "DAT_APR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\dat_apr.c
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_apr.h
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_apr.jil
# End Source File
# End Group
# Begin Group "DAT_TRP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_TRP.C
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_TRP.GFT
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_TRP.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_TRP.HGR
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_TRP.jil
# End Source File
# Begin Source File

SOURCE=.\DAT\dat_trpp.h
# End Source File
# End Group
# Begin Group "DAT_VLG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAT\DAT_VLG.C
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_VLG.GFT
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_VLG.H
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_VLG.HGR
# End Source File
# Begin Source File

SOURCE=.\DAT\DAT_VLG.jil
# End Source File
# End Group
# End Group
# Begin Group "LAP"

# PROP Default_Filter ""
# Begin Group "SUP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\lap_sup.c
# End Source File
# Begin Source File

SOURCE=.\LAP\lap_sup.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\lap_sup.h
# End Source File
# Begin Source File

SOURCE=.\LAP\lap_sup.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_SUP.JIL

!IF  "$(CFG)" == "simu - Win32 PC Debug"

# Begin Custom Build
InputPath=.\LAP\LAP_SUP.JIL

BuildCmds= \
	ANALYSE.BAT $(InputPath)

"..\EXE\GEN\JIL.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\EXE\GEN\JILi.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "simu - Win32 PC Release"

# Begin Custom Build
InputPath=.\LAP\LAP_SUP.JIL

BuildCmds= \
	ANALYSE.BAT $(InputPath)

"..\EXE\GEN\JIL.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\EXE\GEN\JILi.H" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "simu - Win32 PC PerfCnt"

# Begin Custom Build
InputPath=.\LAP\LAP_SUP.JIL

BuildCmds= \
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

SOURCE=.\LAP\LAP_SUPp.H
# End Source File
# End Group
# Begin Group "ILL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_ILL.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ILL.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ILL.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ILL.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ILL.jil
# End Source File
# End Group
# Begin Group "DIAG"

# PROP Default_Filter ""
# Begin Group "KWP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_KWP.C
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_KWP.GFT
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_KWP.H
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_KWP.HGR
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_KWP.JIL
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_KWPP.H
# End Source File
# End Group
# Begin Group "AFS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_AFS.C
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_AFS.GFT
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_AFS.H
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_AFS.HGR
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_AFS.JIL
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_AFSP.H
# End Source File
# End Group
# Begin Group "DVP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_DVP.C
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DVP.H
# End Source File
# End Group
# Begin Group "TFC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_TFC.C
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_TFC.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_TFC.H
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_TFC.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_TFC.JIL
# End Source File
# End Group
# End Group
# Begin Group "BUZ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_BUZ.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_BUZ.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_BUZ.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_BUZ.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_BUZ.jil
# End Source File
# End Group
# Begin Group "FLI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_FLI.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FLI.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FLI.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FLI.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FLI.jil
# End Source File
# End Group
# Begin Group "DFR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_DFR.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DFR.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DFR.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DFR.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DFR.jil
# End Source File
# End Group
# Begin Group "ALA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_ALA.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ALA.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ALA.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ALA.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_ALA.jil
# End Source File
# End Group
# Begin Group "FRW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_FRW.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FRW.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FRW.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FRW.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_FRW.jil
# End Source File
# End Group
# Begin Group "DLK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_DLK.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DLK.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DLK.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DLK.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_DLK.jil
# End Source File
# End Group
# Begin Group "CAR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_CAR.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_CAR.GFT
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_CAR.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_CAR.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_CAR.jil
# End Source File
# End Group
# Begin Group "LRN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_LRN.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_LRN.GFT
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_LRN.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_LRN.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_LRN.jil
# End Source File
# End Group
# Begin Group "VLD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_VLD.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_VLD.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_VLD.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_VLD.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_VLD.jil
# End Source File
# End Group
# Begin Group "RRW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_RRW.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_RRW.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_RRW.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_RRW.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_RRW.jil
# End Source File
# End Group
# Begin Group "EXL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_EXL.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_EXL.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_EXL.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_EXL.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_EXL.jil
# End Source File
# End Group
# Begin Group "PAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LAP\LAP_PAL.c
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_PAL.gft
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_PAL.h
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_PAL.hgr
# End Source File
# Begin Source File

SOURCE=.\LAP\LAP_PAL.jil
# End Source File
# End Group
# End Group
# Begin Group "Auto=."

# PROP Default_Filter ""
# End Group
# End Target
# End Project
