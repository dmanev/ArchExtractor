// tcCanECar.h: interface for the tcCanECar class.
//
//////////////////////////////////////////////////////////////////////
/******************************************************************************
--------------------------------------------------------------------------------
Cette classe gère la connexion ECar

Pour obtenir un pointeur sur la connexion ECar:

  tcCanUUDT* pCan= new tcCanECar();

               ----------- 
              | tcCanUUDT | = 0 Classe abstraite
               ----------- 
                   / \
                    |
            --------------------...
           |            |
       -----------   ---------
      |tcCanVector| | tcCanNI |
       -----------   ---------

-------------------------------------------------------------------------------

Nom et initiales des developpeurs :

         Mickaël GRANDSIRE - MG

-------------------------------------------------------------------------------

Historique du fichier tcCanECar.c
(initiales, date, modification)

       Cree par : MG le 01/02/2002

******************************************************************************/

#if !defined(AFX_TCCANECAR_H__878455C1_16EF_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCCANECAR_H__878455C1_16EF_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcCanUUDT.h"

typedef void (*tpfCallBackCanReq)  (U32 Id,tTrameCan2 *,void*);

class tcCanECar : public tcCanUUDT
{
public:
    tcCanECar(tcTimerCan* pTimerCan,tpfCallBackCanReq FCallBackCanReq,void* pParam);
    virtual ~tcCanECar();

public:
    // Création et fermeture de sessions
    virtual BOOL CreerObjet(tObjetCanUU2* pObjetCan);
    virtual BOOL DetruireObjet(tObjetCanUU2* pObjetCan);

    // Réception d'une trame par Appel externe (DLL ou Appli)
    void    RepTrame(U32 Id,tTrameCan2* pTrameCan);

protected:
    // Emission d'une trame sur CallBack
    virtual BOOL ReqTrameUU(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan);

private:
    tpfCallBackCanReq     m_FCallBackCanReq;
    void*                 m_ParamCallBackCanReq;

};

#endif // !defined(AFX_TCCANECAR_H__878455C1_16EF_11D6_A188_0001030A1077__INCLUDED_)
