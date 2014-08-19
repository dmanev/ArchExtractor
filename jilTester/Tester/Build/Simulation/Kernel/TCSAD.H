// tcSAD.h: interface for the tcSAD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCSAD_H__25EF4162_8211_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCSAD_H__25EF4162_8211_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScanAllDll.h"

class tcSAD
{
public:
    tcSAD();
    virtual ~tcSAD();

    CString SADGetError() {return m_SADError;}

    tSADStatus SADConnect(tSADTraceType Type,const char* Name);
    tSADStatus SADDeconnect();

    tSADStatus SADSetCallBackCde(tSADCallBackCde CallBackCde, void* Param);

protected:
    CString     m_SADError;
    tSADHandle  m_SADHandle;

protected:
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    BOOL                      m_SADInitOk;
    static U8                 m_SADInstanceNumber;
    static HINSTANCE              m_SADhLib;
    static BOOL               m_SADDllLoadingSupplierOk;

    static SADCONNECTSUPPLIER     m_SADConnectSupplier;
    static SADDECONNECTSUPPLIER   m_SADDeconnectSupplier;
    static SADGETDLLVERSION       m_SADGetDllVersion;
    static SADSETCALLBACKCDE      m_SADSetCallBackCde;

#endif
};

#endif // !defined(AFX_TCSAD_H__25EF4162_8211_11D6_A188_0001030A1077__INCLUDED_)
