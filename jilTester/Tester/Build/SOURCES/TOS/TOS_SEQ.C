//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      STK
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    TOS_SEQ
//               The graph engine management
// -----------------------------------------------------------------------------
// $Date:   Sep 17 2009 10:27:10  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SEQ.C-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SEQ.C-arc  $
// 
//    Rev 1.1   Sep 17 2009 10:27:10   adzhelp
// Cm003277: Functions defined as CALLT_TYPE
// 
//    Rev 1.0   04 Feb 2009 17:03:06   adzhelp
// Initial revision.
*/
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define TOS_SEQ "TOS_SEQ"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos_seq.h"
#include "tos_ord.h"
#include "lib.h"
#ifdef COMPILATION_NATIVE
  #include <windows.h>
  #include <winbase.h>
#endif

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#ifdef COMPILATION_NATIVE
    #define mDbgInit() DbgInit()

    #define mDbgSeqMotor()\
        if( pfDbgSeqMotor!=NULL) pfDbgSeqMotor()

    #define mDbgActivateGraph(ID)                   \
        if(pfDbgActivateGraph!=NULL)                \
        {                                           \
            if( pfDbgActivateGraph(ID) )            \
            {                                       \
                DbgDebugBreak();                    \
            }                                       \
        }

    #define mDbgDeactivateGraph(ID)                 \
        if(pfDbgDeactivateGraph!=NULL)              \
        {                                           \
            if( pfDbgDeactivateGraph(ID) )          \
            {                                       \
                DbgDebugBreak();                    \
            }                                       \
        }

    #define mDbgFreezeGraph(ID)                     \
        if(pfDbgFreezeGraph!=NULL)                  \
        {                                           \
            if( pfDbgFreezeGraph(ID) )              \
            {                                       \
                DbgDebugBreak();                    \
            }                                       \
        }

    #define mDbgUnfreezeGraph(ID)                   \
        if(pfDbgUnfreezeGraph!=NULL)                \
        {                                           \
            if( pfDbgUnfreezeGraph(ID) )            \
            {                                       \
                DbgDebugBreak();                    \
            }                                       \
        }

    #define mDbgChangeGrapheRule(ID,Rule)           \
        if(pfDbgChangeGrapheRule!=NULL)             \
        {                                           \
            if( pfDbgChangeGrapheRule(ID,Rule) )    \
            {                                       \
                DbgDebugBreak();                    \
            }                                       \
        }
#elif defined (_QAC_)
extern void NOP(void);
    #define mDbgInit()                          NOP()
    #define mDbgSeqMotor()                      NOP()
    #define mDbgActivateGraph(ID)               NOP()
    #define mDbgDeactivateGraph(ID)             NOP()
    #define mDbgFreezeGraph(ID)                 NOP()
    #define mDbgUnfreezeGraph(ID)               NOP()
    #define mDbgChangeGrapheRule(ID,Rule)       NOP()
#else
    #define mDbgInit()
    #define mDbgSeqMotor()
    #define mDbgActivateGraph(ID)
    #define mDbgDeactivateGraph(ID)
    #define mDbgFreezeGraph(ID)
    #define mDbgUnfreezeGraph(ID)
    #define mDbgChangeGrapheRule(ID,Rule)
#endif

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
#ifdef COMPILATION_NATIVE
BOOL  (*pfDbgInit)(U32 u32NbGr,const tTOSSeqGraphListType*);
void  (*pfDbgSeqMotor)(void);
BOOL  (*pfDbgActivateGraph)(U32 u32ID);
BOOL  (*pfDbgDeactivateGraph)(U32 u32ID);
BOOL  (*pfDbgFreezeGraph)(U32 u32ID);
BOOL  (*pfDbgUnfreezeGraph)(U32 u32ID);
BOOL  (*pfDbgChangeGrapheRule)(U32 u32ID,U32 u32Rule);
HINSTANCE hDbgGraphDll = NULL;
#endif

static tTOSSeqGraphContextType TOSSeqGraphContext[cTOSSeqGraphNumber];

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
tTOSSeqGraphId TOSSeqGraphNumber;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
#ifdef COMPILATION_NATIVE
//==============================================================================
// DESCRIPTION:         Initializes the debug mode in COMPILATION_NATIVE
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Initializes the debug variables.
//                      Refer to Detailed Design Document
//==============================================================================
static void DbgInit(void);

//==============================================================================
// DESCRIPTION:         Avoids masking of the last function by the debugbreak 
//                      execution.
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calls debugbreak function.
//                      Refer to Detailed Design Document
//==============================================================================
static void DbgDebugBreak(void);
#endif

//==============================================================================
// DESCRIPTION:         Tests all sister's transitions of the graph and executes
//                      corresponding actions.
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Tests all sister's transitions of the current graph one
//                      after the other. When one returns TRUE executes the
//                      corresponding action and stops testing the other sister's
//                      rules. If there is no daughter's rule, deactivates the graph.
//                      Refer to Detailed Design Document
//==============================================================================
static void ScanGraph(void);

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

#ifdef COMPILATION_NATIVE
static void DbgInit(void)
{
    if( hDbgGraphDll == NULL )
    {
        hDbgGraphDll = LoadLibrary("DBGSEQ.DLL");
    }

    if ( hDbgGraphDll != NULL )
    {
        pfDbgInit = (void*)GetProcAddress(hDbgGraphDll, "DbgInit");

        if( pfDbgInit != NULL )
        {
            if( pfDbgInit(cTOSSeqGraphNumber, &TOSSeqGraphList) )
            {
                pfDbgSeqMotor         = (void*)GetProcAddress(hDbgGraphDll, "DbgSeqMoteur");
                pfDbgActivateGraph    = (void*)GetProcAddress(hDbgGraphDll, "DbgActiverGraphe");
                pfDbgDeactivateGraph  = (void*)GetProcAddress(hDbgGraphDll, "DbgDesactiverGraphe");
                pfDbgFreezeGraph       = (void*)GetProcAddress(hDbgGraphDll, "DbgGelerGraphe");
                pfDbgUnfreezeGraph     = (void*)GetProcAddress(hDbgGraphDll, "DbgDegelerGraphe");
                pfDbgChangeGrapheRule = (void*)GetProcAddress(hDbgGraphDll, "DbgChangerRegleGraphe");
            }
            else
            {
                pfDbgInit = NULL;
            }
        }
    }
    else
    {
        pfDbgInit               = NULL;
        pfDbgSeqMotor           = NULL;
        pfDbgActivateGraph      = NULL;
        pfDbgDeactivateGraph    = NULL;
        pfDbgFreezeGraph        = NULL;
        pfDbgUnfreezeGraph      = NULL;
        pfDbgChangeGrapheRule   = NULL;
    }
}

static void DbgDebugBreak(void)
{
    DebugBreak();
}
#endif

static void ScanGraph(void)
{
    const tTOSSeqRuleType* pRule;
#ifdef COMPILATION_NATIVE         // For debug mode, save the rule number
    tTOSSeqRuleId RuleNumber;
#endif

    mLIBassert(TOSSeqGraphNumber < cTOSSeqGraphNumber);

#ifdef COMPILATION_NATIVE
    RuleNumber = TOSSeqGraphContext[TOSSeqGraphNumber].RuleNumber;
    pRule = TOSSeqGraphList[TOSSeqGraphNumber]->Rules
            + TOSSeqGraphContext[TOSSeqGraphNumber].RuleNumber;
#else
    pRule = *TOSSeqGraphList[TOSSeqGraphNumber]
            + TOSSeqGraphContext[TOSSeqGraphNumber].RuleNumber;
#endif
    do
    {
        if ((*pRule->pTransition)() != cFalse)
        {
#ifdef COMPILATION_NATIVE
            mDbgChangeGrapheRule(TOSSeqGraphNumber,RuleNumber);
            // When GraphDesigner break the application, you are in the DLL
            // For exit to the DLL, place a breakpoint in front of (*ptRegle->ptAction)();
            // and continue the application by 'F5' key press.
            // Now you can debug your application just before execute the action.
#endif
            (*pRule->pAction)();

            if (pRule->DaughterRuleNumber != cTOSSeqInvalidRule)
            {
                TOSSeqGraphContext[TOSSeqGraphNumber].RuleNumber = pRule->DaughterRuleNumber;
            }
            else    // End of graph
            {
                mDbgDeactivateGraph(TOSSeqGraphNumber);
                TOSSeqGraphContext[TOSSeqGraphNumber].GraphState  = cTOSSeqInactiveGraph;
                TOSSeqGraphContext[TOSSeqGraphNumber].RuleNumber  = 0 ;
            }
            pRule = NULL;     // Condition for exit loop
        }
        else if ( pRule->SisterRuleNumber != cTOSSeqInvalidRule )
        {
#ifdef COMPILATION_NATIVE                   // For debug mode, save the rule number
            RuleNumber = pRule->SisterRuleNumber;
            pRule = TOSSeqGraphList[TOSSeqGraphNumber]->Rules
                    + pRule->SisterRuleNumber;
#else
            pRule = *TOSSeqGraphList[TOSSeqGraphNumber]
                    + pRule->SisterRuleNumber;
#endif
        }
        else
        {
            pRule = NULL;
        }
    }
    while(pRule != NULL);
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSeqInitialize(void)
{
    tTOSSeqGraphId GraphNumber;

    mLIBassert(cTOSSeqGraphNumber > 0);

    mDbgInit();

    for (GraphNumber = 0;GraphNumber < cTOSSeqGraphNumber; GraphNumber++)
    {
        TOSSeqGraphContext[GraphNumber].GraphState = cTOSSeqInactiveGraph;
        TOSSeqGraphContext[GraphNumber].RuleNumber = 0 ;
    }
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE void TOSSeqActivateGraph(const tTOSSeqGraphId GraphNumber)
{
    mLIBassert(GraphNumber < cTOSSeqGraphNumber);
    mLIBassert(TOSSeqGraphContext[GraphNumber].GraphState == cTOSSeqInactiveGraph);

    mDbgActivateGraph(GraphNumber);
    TOSSeqGraphContext[GraphNumber].GraphState = cTOSSeqActiveGraph;
    TOSSeqGraphContext[GraphNumber].RuleNumber = 0;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE void TOSSeqDeactivateGraph(const tTOSSeqGraphId GraphNumber)
{
    mLIBassert(GraphNumber < cTOSSeqGraphNumber);
    // If graph is already deactivated, it is not a fault
    //  mLIBassert(TOSSeqGraphContext[GraphNumber].GraphState != cTOSSeqInactiveGraph);

    mDbgDeactivateGraph(GraphNumber);
    TOSSeqGraphContext[GraphNumber].GraphState = cTOSSeqInactiveGraph;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSeqFreezeGraph(const tTOSSeqGraphId GraphNumber)
{
    mLIBassert(GraphNumber < cTOSSeqGraphNumber);
    mLIBassert(TOSSeqGraphContext[GraphNumber].GraphState == cTOSSeqActiveGraph);

    mDbgFreezeGraph(GraphNumber);
    TOSSeqGraphContext[GraphNumber].GraphState = cTOSSeqFrozenGraph;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSeqUnfreezeGraph(const tTOSSeqGraphId GraphNumber)
{
    mLIBassert(GraphNumber < cTOSSeqGraphNumber);
    mLIBassert(TOSSeqGraphContext[GraphNumber].GraphState == cTOSSeqFrozenGraph);

    mDbgUnfreezeGraph(GraphNumber);
    TOSSeqGraphContext[GraphNumber].GraphState = cTOSSeqActiveGraph;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE tTOSSeqGraphStateType TOSSeqGraphState(const tTOSSeqGraphId GraphNumber)
{
    mLIBassert(GraphNumber < cTOSSeqGraphNumber);

    return (TOSSeqGraphContext[GraphNumber].GraphState);
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
BOOL TOSSeqTrueEval(void)
{
    // This function must always return true
    return (cTrue);
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSeqNoAction(void)
{
    // This function must be always empty
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSeqMotor(const tTOSSeqGraphId StartGraph,const tTOSSeqGraphId EndGraph)
{
    tTOSSeqGraphId OldGraphNumber;

    mLIBassert(EndGraph < cTOSSeqGraphNumber);

    mDbgSeqMotor();

    OldGraphNumber = TOSSeqGraphNumber;     // Save OldGraphNumber

    // if no graph is activated -> simulation of a minimum time
    mLDBSimulateProcessingTime(cTOSSeqDureeTourGrapheSimulationNs/
                               (cLDBTick*(cTOSSeqGraphNumber+1)));

    // It is possible because it is not possible to have 2 graph tasks with same priority
    for (TOSSeqGraphNumber = StartGraph; TOSSeqGraphNumber<= EndGraph; TOSSeqGraphNumber++)
    {
        mLIBassert(TOSSeqGraphList[TOSSeqGraphNumber] != NULL);

        if (TOSSeqGraphContext[TOSSeqGraphNumber].GraphState == cTOSSeqActiveGraph)
        {
            ScanGraph();

            // TosSeq Call this Macro for simulate the LDB component
            // This macro is empty in the LDB embedded
            mLDBSimulateProcessingTime(cTOSSeqDureeTourGrapheSimulationNs/
                                       (cLDBTick*(cTOSSeqGraphNumber+1)));

            // Call the scheduler for give the hand again
            TOSSchedule();
        }
    }

    TOSSeqGraphNumber = OldGraphNumber;     // Restore OldGraphNumber
}

