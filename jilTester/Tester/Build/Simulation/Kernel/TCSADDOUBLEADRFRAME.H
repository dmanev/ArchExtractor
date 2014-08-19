// tcSADDoubleAdrFrame.h: interface for the tcSADDoubleAdrFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCSADDOUBLEADRFRAME_H__EDA10141_8298_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCSADDOUBLEADRFRAME_H__EDA10141_8298_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcSAD.h"

class tcSADDoubleAdrFrame : public tcSAD
{
public:
    tcSADDoubleAdrFrame();
    virtual ~tcSADDoubleAdrFrame();

    tSADStatus SADConnect(const char* Name) {return tcSAD::SADConnect(cSADDoubleAdrFrameType,Name);}

    tSADStatus SADDoubleAdrFrameTraceRx(U32 Adr1, U32 Adr2, U32 Lng, U8* Buffer, U32 Time = (10*GetTickCount()));
    tSADStatus SADDoubleAdrFrameTraceTx(U32 Adr1, U32 Adr2, U32 Lng, U8* Buffer, U32 Time = (10*GetTickCount()));
    tSADStatus SADDoubleAdrFrameTextRx(U32 Adr1, U32 Adr2, const char* Text, U32 Time = (10*GetTickCount()));
    tSADStatus SADDoubleAdrFrameTextTx(U32 Adr1, U32 Adr2, const char* Text, U32 Time = (10*GetTickCount()));
    tSADStatus SADDoubleAdrFrameText(const char* Text, BOOL Error = cFalse, U32 Time = (10*GetTickCount()));

protected:
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    static U8                       m_SADDoubleAdrFrameInstanceNumber;
    static BOOL                     m_SADDoubleAdrFrameDllLoadingSupplierOk;
    static SADDOUBLEADRFRAMETRACE       m_SADDoubleAdrFrameTrace;
#endif
    tSADDoubleAdrFrameType m_DoubleAdrFrame;
};

#endif // !defined(AFX_TCSADDOUBLEADRFRAME_H__EDA10141_8298_11D6_A188_0001030A1077__INCLUDED_)
