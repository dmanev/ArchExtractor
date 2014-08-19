// tcSAD.cpp: implementation of the tcSAD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tcSAD.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  U8                tcSAD::m_SADInstanceNumber = 0;
  HINSTANCE             tcSAD::m_SADhLib           = NULL;
  BOOL              tcSAD::m_SADDllLoadingSupplierOk = cFalse;

  SADGETDLLVERSION      tcSAD::m_SADGetDllVersion;
  SADCONNECTSUPPLIER    tcSAD::m_SADConnectSupplier;
  SADDECONNECTSUPPLIER  tcSAD::m_SADDeconnectSupplier;
  SADSETCALLBACKCDE     tcSAD::m_SADSetCallBackCde;
#endif

tcSAD::tcSAD()
{
  m_SADHandle     = cSADInvalidHandle;

#ifdef DYNAMIC_SCANALLDLL_DRIVER
  m_SADInstanceNumber ++;

  m_SADInitOk = cFalse;
  if (m_SADDllLoadingSupplierOk == cFalse)   // Load ScanAllDll
  {
    CString str("ScanAllDll.dll");
	  m_SADhLib = LoadLibrary(str);
	  if (m_SADhLib == NULL)
	  {
      m_SADError.Format("tcSAD::tcSAD> Fail to load \"%s\"",str);
		  return;
	  }
	  if (((FARPROC&)m_SADGetDllVersion = GetProcAddress(m_SADhLib,  _T("SADGetDllVersion"))) == NULL)
	  {
      m_SADError = "tcSAD::tcSAD> Fail to load \"SADGetDllVersion\" function";
		  return;
	  }
	  if (((FARPROC&)m_SADConnectSupplier = GetProcAddress(m_SADhLib,  _T("SADConnectSupplier"))) == NULL)
	  {
      m_SADError = "tcSAD::tcSAD> Fail to load \"SADConnectSupplier\" function";
      DWORD Err=GetLastError();
		  return;
	  }
	  if (((FARPROC&)m_SADDeconnectSupplier = GetProcAddress(m_SADhLib,  _T("SADDeconnectSupplier"))) == NULL)
	  {
      m_SADError = "tcSAD::tcSAD> Fail to load \"SADDeconnectSupplier\" function";
		  return;
	  }
	  if (((FARPROC&)m_SADSetCallBackCde = GetProcAddress(m_SADhLib, _T("SADSetCallBackCde"))) == NULL)
	  {
      m_SADError = "tcSAD::tcSAD> Fail to load \"SADSetCallBackCde\" function";
		  return;
	  }
    m_SADDllLoadingSupplierOk = cTrue;
  }
  if (m_SADDllLoadingSupplierOk == cTrue)
  {
    m_SADInitOk = cTrue;
  }
#endif
}

tcSAD::~tcSAD()
{
  SADDeconnect();

#ifdef DYNAMIC_SCANALLDLL_DRIVER
  if (m_SADInstanceNumber == 1)   // Discharge ScanAllDll
  {
    m_SADDllLoadingSupplierOk = cFalse;
    if (m_SADhLib != NULL)
    {
 		  FreeLibrary(m_SADhLib);
      m_SADhLib = NULL;
    }
  }
  m_SADInstanceNumber--;
#endif
}

tSADStatus tcSAD::SADConnect(tSADTraceType Type,const char* Name)
{
  tSADStatus Status = cSADDeactivated;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  if (m_SADInitOk != cFalse)
  {
    m_SADHandle = m_SADConnectSupplier(Type,Name);
#else
    m_SADHandle = ::SADConnectSupplier(Type,Name);
#endif
    if ( m_SADHandle != cSADInvalidHandle)
    {
      Status = cSADOk;
    }
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  }
#endif
  return Status;
}

tSADStatus tcSAD::SADDeconnect()
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADDeconnectSupplier(m_SADHandle);
#else
    Status = ::SADDeconnectSupplier(m_SADHandle);
#endif
    m_SADHandle = cSADInvalidHandle;
  }
  return Status;
}

tSADStatus tcSAD::SADSetCallBackCde(tSADCallBackCde CallBackCde, void* Param)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status =  m_SADSetCallBackCde(m_SADHandle,CallBackCde,Param);
#else
    Status = ::SADSetCallBackCde(m_SADHandle,CallBackCde,Param);
#endif
  }
  return Status;
}
