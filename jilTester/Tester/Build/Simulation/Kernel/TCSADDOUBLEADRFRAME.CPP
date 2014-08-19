// tcSADDoubleAdrFrame.cpp: implementation of the tcSADDoubleAdrFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tcSADDoubleAdrFrame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  U8                  tcSADDoubleAdrFrame::m_SADDoubleAdrFrameInstanceNumber = 0;
  BOOL                tcSADDoubleAdrFrame::m_SADDoubleAdrFrameDllLoadingSupplierOk = cFalse;
  SADDOUBLEADRFRAMETRACE  tcSADDoubleAdrFrame::m_SADDoubleAdrFrameTrace;
#endif

tcSADDoubleAdrFrame::tcSADDoubleAdrFrame()
{
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  m_SADDoubleAdrFrameInstanceNumber++;
  if (m_SADInitOk == cTrue)   // Load ScanAllDll
  {
    ASSERT(m_SADhLib != NULL);
    m_SADInitOk = cFalse;
    if (m_SADDoubleAdrFrameDllLoadingSupplierOk == cFalse)
    {
	    if (((FARPROC&)m_SADDoubleAdrFrameTrace = GetProcAddress(m_SADhLib, _T("SADDoubleAdrFrameTrace"))) == NULL)
	    {
        m_SADError = "tcSADDoubleAdrFrame::tcSADDoubleAdrFrame> Fail to load \"SADDoubleAdrFrameTrace\" function";
		    return;
	    }
      m_SADDoubleAdrFrameDllLoadingSupplierOk = cTrue;
    }
    if (m_SADDoubleAdrFrameDllLoadingSupplierOk == cTrue)
    {
      m_SADInitOk = cTrue;
    }
  }
#endif
}

tcSADDoubleAdrFrame::~tcSADDoubleAdrFrame()
{
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  if (m_SADInstanceNumber == 1)
  {
    m_SADDoubleAdrFrameDllLoadingSupplierOk = cFalse;
  }
  m_SADDoubleAdrFrameInstanceNumber--;
#endif
}

tSADStatus tcSADDoubleAdrFrame::SADDoubleAdrFrameTraceRx(U32 Adr1, U32 Adr2, U32 Lng, U8* Buffer, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_DoubleAdrFrame.Info.Type  = 0;
    m_DoubleAdrFrame.Info.Time  = Time;
    m_DoubleAdrFrame.Info.Adr1  = Adr1;
    m_DoubleAdrFrame.Info.Adr2  = Adr2;
    m_DoubleAdrFrame.Info.Lng   = Lng;
    m_DoubleAdrFrame.Buffer     = Buffer;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#else
    Status = ::SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADDoubleAdrFrame::SADDoubleAdrFrameTraceTx(U32 Adr1, U32 Adr2, U32 Lng, U8* Buffer, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_DoubleAdrFrame.Info.Type  = cSADTypeTxFlag;
    m_DoubleAdrFrame.Info.Time  = Time;
    m_DoubleAdrFrame.Info.Adr1  = Adr1;
    m_DoubleAdrFrame.Info.Adr2  = Adr2;
    m_DoubleAdrFrame.Info.Lng   = Lng;
    m_DoubleAdrFrame.Buffer     = Buffer;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#else
    Status = ::SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADDoubleAdrFrame::SADDoubleAdrFrameTextRx(U32 Adr1, U32 Adr2, const char* Text, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_DoubleAdrFrame.Info.Type  = cSADTypeFrameTextFlag;
    m_DoubleAdrFrame.Info.Time  = Time;
    m_DoubleAdrFrame.Info.Adr1  = Adr1;
    m_DoubleAdrFrame.Info.Adr2  = Adr2;
    m_DoubleAdrFrame.Info.Lng   = strlen(Text)+1;
    m_DoubleAdrFrame.Buffer     = (U8*)Text;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#else
    Status = ::SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADDoubleAdrFrame::SADDoubleAdrFrameTextTx(U32 Adr1, U32 Adr2, const char* Text, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_DoubleAdrFrame.Info.Type  = cSADTypeFrameTextFlag|cSADTypeTxFlag;
    m_DoubleAdrFrame.Info.Time  = Time;
    m_DoubleAdrFrame.Info.Adr1  = Adr1;
    m_DoubleAdrFrame.Info.Adr2  = Adr2;
    m_DoubleAdrFrame.Info.Lng   = strlen(Text)+1;
    m_DoubleAdrFrame.Buffer     = (U8*)Text;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#else
    Status = ::SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADDoubleAdrFrame::SADDoubleAdrFrameText(const char* Text, BOOL Error, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_DoubleAdrFrame.Info.Type  = (Error?cSADTypeErrorFlag|cSADTypeTextFlag:cSADTypeTextFlag);
    m_DoubleAdrFrame.Info.Time  = Time;
    m_DoubleAdrFrame.Info.Lng   = strlen(Text)+1;
    m_DoubleAdrFrame.Buffer     = (U8*)Text;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#else
    Status = ::SADDoubleAdrFrameTrace(m_SADHandle,&m_DoubleAdrFrame);
#endif
  }
  return Status;
}
