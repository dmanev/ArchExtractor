# Microsoft Developer Studio Project File - Name="Tools" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Tools - Win32 PerfCnt
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tools.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tools.mak" CFG="Tools - Win32 PerfCnt"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tools - Win32 PC Debug" (based on "Win32 (x86) Application")
!MESSAGE "Tools - Win32 PC Release" (based on "Win32 (x86) Application")
!MESSAGE "Tools - Win32 PerfCnt" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tools - Win32 PC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ldbpc___Win32_PC_Debug"
# PROP BASE Intermediate_Dir "ldbpc___Win32_PC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\PC_D"
# PROP Intermediate_Dir "..\EXE\PC_D"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /Zi /Od /I "PARAMDAT" /I "..\SOURCES" /I "..\SOURCES\LIB" /I "..\SOURCES\LDB_API" /I "..\EXE\GEN" /I "..\EXE\GENSIMU" /I "KERNEL" /I "PARAMLDB" /D "_DEBUG" /D MEM_TYPE= /D CALLT_TYPE= /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "COMPILATION_NATIVE" /D "DYNAMIC_SCANALLDLL_DRIVER" /D "USE_LIBSTK" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\EXE\PC_D\PC_D.LIB /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"..\EXE\pc_d.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Tools - Win32 PC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ldbpc___Win32_PC_Release"
# PROP BASE Intermediate_Dir "ldbpc___Win32_PC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\EXE\PC_R"
# PROP Intermediate_Dir "..\EXE\PC_R"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "KERNEL" /I "PARAMLDB" /I "PARAMDAT" /I "..\SOURCES\LIB" /I "..\SOURCES\LDB_API" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "COMPILATION_NATIVE" /D "DYNAMIC_SCANALLDLL_DRIVER" /D "USE_LIBSTK" /D MEM_TYPE= /D CALLT_TYPE= /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\EXE\PC_R\PC_R.LIB /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"..\EXE\pc_r.exe" /OPT:NOREF
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Tools - Win32 PerfCnt"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Tools___Win32_PerfCnt"
# PROP BASE Intermediate_Dir "Tools___Win32_PerfCnt"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\EXE\PC_P"
# PROP Intermediate_Dir "..\EXE\PC_P"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MDd /W3 /Gm /GX /Zi /Od /I "PARAMDAT" /I "..\SOURCES" /I "..\EXE\GEN" /I "..\EXE\GENSIMU" /I "KERNEL" /I "PARAMLDB" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "COMPILATION_NATIVE" /D "DYNAMIC_SCANALLDLL_DRIVER" /D "USE_LIBSTK" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /Zi /Od /I "PARAMDAT" /I "..\SOURCES\DAT" /I "..\SOURCES\LAP" /I "..\SOURCES\LDB_API" /I "..\SOURCES\LIB" /I "..\SOURCES\TOS" /I "..\EXE\GEN" /I "..\EXE\GENSIMU" /I "KERNEL" /I "PARAMLDB" /D "_DEBUG" /D "TOS_PERF_CNT_ENABLE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "COMPILATION_NATIVE" /D "DYNAMIC_SCANALLDLL_DRIVER" /D "USE_LIBSTK" /D MEM_TYPE= /D CALLT_TYPE= /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\EXE\PC_D\PC_D.LIB /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"..\EXE\pc_d.exe" /pdbtype:sept
# ADD LINK32 ..\EXE\PC_P\PC_P.LIB /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"..\EXE\pc_p.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Tools - Win32 PC Debug"
# Name "Tools - Win32 PC Release"
# Name "Tools - Win32 PerfCnt"
# Begin Group "Kernel"

# PROP Default_Filter ""
# Begin Group "Auto=Kernel"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\KERNEL\ApiDonne.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\ApiDonne.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\ApiRes.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\ApiTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Appli.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Appli.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Appli.ico
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Appli.rc
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Appli.rc2
# End Source File
# Begin Source File

SOURCE=.\KERNEL\AppliDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\AppliDlg.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Array.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\CanDll.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\DLLCOM.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\ImgCompare.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\ImgCompare.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Ldbpc.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Ldbpc.rtf
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcCan.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcCan.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcCom.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcCtl.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCDon.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCDon.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCErc.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcErr.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcErr.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCEvt.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCEvt.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcFlu.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcFlu.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCPar.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcRdo.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcRdo.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcRes.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcRes.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCTem.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCTem.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCTim.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LDBPCTim.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcTra.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\LdbpcTra.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\Liste.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\MainLev.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\MainLev.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\OpenGl.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\param.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\resource.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\ScanAllDll.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanalCan.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanalCan.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanASDT.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanASDT.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanECar.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanECar.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanNonASDT.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanNonASDT.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanNonSession.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanNonSession.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanNonUSDT.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanNonUSDT.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanSession.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanSession.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanUSDT.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanUSDT.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanUUDT.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcCanUUDT.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcSAD.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcSAD.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcSADAdrFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcSADAdrFrame.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcSADDoubleAdrFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcSADDoubleAdrFrame.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTimerCan.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTimerCan.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTrameMsgCan.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTrameMsgCan.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTrameMsgCanAck.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTrameMsgCanAck.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTrameMsgCanSession.cpp
# End Source File
# Begin Source File

SOURCE=.\KERNEL\tcTrameMsgCanSession.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\XCarCAN.h
# End Source File
# Begin Source File

SOURCE=.\KERNEL\DLLCOM.lib
# End Source File
# Begin Source File

SOURCE=.\KERNEL\DLLOpenGL.lib
# End Source File
# Begin Source File

SOURCE=.\KERNEL\CanDll.lib
# End Source File
# Begin Source File

SOURCE=.\KERNEL\XCarCAN.lib
# End Source File
# End Group
# Begin Group "ParamLDB"

# PROP Default_Filter ""
# Begin Group "Auto=ParamLDB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ParamLDB\ParamAla.cpp
# End Source File
# Begin Source File

SOURCE=PARAMLDB\PARAMINT.CPP
# End Source File
# Begin Source File

SOURCE=PARAMLDB\PARAMKWP.CPP
# End Source File
# Begin Source File

SOURCE=PARAMLDB\PARAMLCD.CPP
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\ParamMod.cpp
# End Source File
# Begin Source File

SOURCE=PARAMLDB\PARAMOGL.CPP
# End Source File
# Begin Source File

SOURCE=PARAMLDB\PARAMPWM.CPP
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\ParamRf.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\ParamSpd.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\ParamTrp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ParamLDB\config.h
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\IhmParam.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\LdbpcPar.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\PARAMBUZ.CPP
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\ParamEep.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamLDB\ParamRst.cpp
# End Source File
# End Group
# Begin Group "ParamDAT"

# PROP Default_Filter ""
# Begin Group "Auto=ParamDAT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=PARAMDAT\DATPCPAR.H
# End Source File
# End Group
# End Group
# Begin Group "API_LDB"

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
# Begin Group "API_LIB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\LIB\deftypes.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LIB\LIB.h
# End Source File
# Begin Source File

SOURCE=..\SOURCES\LIB\Lib_stk.h
# End Source File
# End Group
# Begin Group "API_TOS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCES\TOS\Tosparam.h
# End Source File
# End Group
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Group "Auto=..\EXE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EXE\DB.JIL
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
# Begin Group "Auto=..\EXE\GENSIMU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EXE\GENSIMU\ParamAna.CPP
# End Source File
# Begin Source File

SOURCE=..\EXE\GENSIMU\ParamDin.CPP
# End Source File
# Begin Source File

SOURCE=..\EXE\GENSIMU\ParamDou.CPP
# End Source File
# End Group
# End Group
# End Target
# End Project
