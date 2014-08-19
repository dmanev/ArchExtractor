// tcSADAdrFrame.cpp: implementation of the tcSADAdrFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tcSADAdrFrame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  U8                  tcSADAdrFrame::m_SADAdrFrameInstanceNumber = 0;
  BOOL                tcSADAdrFrame::m_SADAdrFrameDllLoadingSupplierOk = cFalse;
  SADFRAMETRACE           tcSADAdrFrame::m_SADAdrFrameTrace;
#endif

tcSADAdrFrame::tcSADAdrFrame()
{
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  m_SADAdrFrameInstanceNumber++;
  if (m_SADInitOk == cTrue)   // Continuous to load ScanAllDll
  {
    ASSERT(m_SADhLib != NULL);
    m_SADInitOk = cFalse;
    if (m_SADAdrFrameDllLoadingSupplierOk == cFalse)
    {
	    if (((FARPROC&)m_SADAdrFrameTrace = GetProcAddress(m_SADhLib, _T("SADAdrFrameTrace"))) == NULL)
	    {
        m_SADError = "tcSADAdrFrame::tcSADAdrFrame> Fail to load \"SADAdrFrameTrace\" function";
		    return;
	    }
      m_SADAdrFrameDllLoadingSupplierOk = cTrue;
    }
    if (m_SADAdrFrameDllLoadingSupplierOk == cTrue)
    {
      m_SADInitOk = cTrue;
    }
  }
#endif
}

tcSADAdrFrame::~tcSADAdrFrame()
{
#ifdef DYNAMIC_SCANALLDLL_DRIVER
  if (m_SADAdrFrameInstanceNumber == 1)
  {
    m_SADAdrFrameDllLoadingSupplierOk = cFalse;
  }
  m_SADAdrFrameInstanceNumber--;
#endif
}

tSADStatus tcSADAdrFrame::SADAdrFrameTraceRx(U32 Adr, U32 Lng, U8* Buffer, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_AdrFrame.Info.Type    = 0;
    m_AdrFrame.Info.Time    = Time;
    m_AdrFrame.Info.Adr     = Adr;
    m_AdrFrame.Info.Lng     = Lng;
    m_AdrFrame.Buffer       = Buffer;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#else
    Status = ::SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADAdrFrame::SADAdrFrameTraceTx(U32 Adr, U32 Lng, U8* Buffer, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_AdrFrame.Info.Type    = cSADTypeTxFlag;
    m_AdrFrame.Info.Time    = Time;
    m_AdrFrame.Info.Adr     = Adr;
    m_AdrFrame.Info.Lng     = Lng;
    m_AdrFrame.Buffer       = Buffer;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#else
    Status = ::SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADAdrFrame::SADAdrFrameTextRx(U32 Adr, const char* Text, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_AdrFrame.Info.Type    = cSADTypeFrameTextFlag;
    m_AdrFrame.Info.Time    = Time;
    m_AdrFrame.Info.Adr     = Adr;
    m_AdrFrame.Info.Lng     = strlen(Text)+1;
    m_AdrFrame.Buffer       = (U8*)Text;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#else
    Status = ::SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADAdrFrame::SADAdrFrameTextTx(U32 Adr, const char* Text, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_AdrFrame.Info.Type    = cSADTypeFrameTextFlag|cSADTypeTxFlag;
    m_AdrFrame.Info.Time    = Time;
    m_AdrFrame.Info.Adr     = Adr;
    m_AdrFrame.Info.Lng     = strlen(Text)+1;
    m_AdrFrame.Buffer       = (U8*)Text;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#else
    Status = ::SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#endif
  }
  return Status;
}

tSADStatus tcSADAdrFrame::SADAdrFrameText(const char* Text, BOOL Error, U32 Time)
{
  tSADStatus Status = cSADNotConnected;
  if (m_SADHandle != cSADInvalidHandle)
  {
    m_AdrFrame.Info.Type    = (Error?cSADTypeErrorFlag|cSADTypeTextFlag:cSADTypeTextFlag);
    m_AdrFrame.Info.Time    = Time;
    m_AdrFrame.Info.Lng     = strlen(Text)+1;
    m_AdrFrame.Buffer       = (U8*)Text;
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    Status = m_SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#else
    Status = ::SADAdrFrameTrace(m_SADHandle,&m_AdrFrame);
#endif
  }
  return Status;
}
