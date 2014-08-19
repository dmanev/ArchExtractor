// tcSADAdrFrame.h: interface for the tcSADAdrFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCSADADRFRAME_H__EDA10141_8298_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCSADADRFRAME_H__EDA10141_8298_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcSAD.h"

class tcSADAdrFrame : public tcSAD
{
public:
    tcSADAdrFrame();
    virtual ~tcSADAdrFrame();

    tSADStatus SADConnect(const char* Name) {return tcSAD::SADConnect(cSADAdrFrameType,Name);}

    tSADStatus SADAdrFrameTraceRx(U32 Adr, U32 Lng, U8* Buffer, U32 Time = (10*GetTickCount()));
    tSADStatus SADAdrFrameTraceTx(U32 Adr, U32 Lng, U8* Buffer, U32 Time = (10*GetTickCount()));
    tSADStatus SADAdrFrameTextRx(U32 Adr, const char* Text, U32 Time = (10*GetTickCount()));
    tSADStatus SADAdrFrameTextTx(U32 Adr, const char* Text, U32 Time = (10*GetTickCount()));
    tSADStatus SADAdrFrameText(const char* Text, BOOL Error = cFalse, U32 Time = (10*GetTickCount()));

protected:
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    static U8                     m_SADAdrFrameInstanceNumber;
    static BOOL                   m_SADAdrFrameDllLoadingSupplierOk;
    static SADADRFRAMETRACE           m_SADAdrFrameTrace;
#endif
    tSADAdrFrameType m_AdrFrame;
};

#endif // !defined(AFX_TCSADADRFRAME_H__EDA10141_8298_11D6_A188_0001030A1077__INCLUDED_)
