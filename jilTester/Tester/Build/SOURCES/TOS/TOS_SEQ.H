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
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SEQ.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SEQ.H-arc  $
// 
//    Rev 1.1   Sep 17 2009 10:27:10   adzhelp
// Cm003277: Functions defined as CALLT_TYPE
// 
//    Rev 1.0   04 Feb 2009 17:03:06   adzhelp
// Initial revision.
*/
//******************************************************************************

#ifndef I_TOS_SEQ_H
#define I_TOS_SEQ_H

//--------------------------------------------------------------------------
//  Define for compatibility with previous version
//--------------------------------------------------------------------------
#define TOSSeqInitialiser()                 TOSSeqInitialize()
#define TOSSeqActiverGraphe(numGraphe)      TOSSeqActivateGraph(numGraphe)
#define TOSSeqDesactiverGraphe(numGraphe)   TOSSeqDeactivateGraph(numGraphe)
#define TOSSeqGelerGraphe(numGraphe)        TOSSeqFreezeGraph(numGraphe)
#define TOSSeqDegelerGraphe(numGraphe)      TOSSeqUnfreezeGraph(numGraphe)
#define TOSSeqEtatGraphe(numGraphe)         TOSSeqGraphState(numGraphe)

#define TOSSeqEvalVrai                      TOSSeqTrueEval
#define TOSSeqNop                           TOSSeqNoAction

#define mTOSSeqAdrRegle(RuleNumber)         mTOSSeqRuleNumber(RuleNumber)
#define cTOSSeqPtNul                        cTOSSeqInvalidRule
#define tTOSSeqTypeGraphe                   tTOSSeqGraphType
#define tTOSSeqTypeRegle                    tTOSSeqRuleType
#define tTOSSeqTypeApplicatif               tTOSSeqGraphListType

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tosparam.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

//----- Define the invalid rule number -----
#define cTOSSeqInvalidRule    cTOSSeqMaxRuleNumber

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------
//--- Define all differents state of graph ---
typedef enum
{
    cTOSSeqInactiveGraph,
    cTOSSeqActiveGraph,
    cTOSSeqFrozenGraph
} tTOSSeqGraphStateType;

//----- Define the graph Id type -----
#if   (cTOSSeqMaxGraphNumber <= 255UL)
typedef U8 tTOSSeqGraphId;
#elif (cTOSSeqMaxGraphNumber <= 65535UL)
typedef U16 tTOSSeqGraphId;
#else
  #error "The maximum graph number is bad defined"
#endif
#define cTOSSeqGraphNumber ((tTOSSeqGraphId)cTOSSeqMaxGraphNumber)

//----- Define the rule number type -----
#if   (cTOSSeqMaxRuleNumber == 255)
typedef U8 tTOSSeqRuleId;
#elif (cTOSSeqMaxRuleNumber == 65535)
typedef U16 tTOSSeqRuleId;
#else
  #error "The maximum rules number is bad defined"
#endif

//----- Define the rule type -----
typedef struct
{
    BOOL (* pTransition)(void);        // Adress of transition function
    void     (* pAction)(void);        // Adress of action function
    tTOSSeqRuleId SisterRuleNumber;    // Number of sister rule
    tTOSSeqRuleId DaughterRuleNumber;  // Number of daughter rule
} tTOSSeqRuleType;

//----- Define the graph type -----
#ifdef _QAC_
#define mUndefinedSize()    256
// there no sense in the value 256 (random value to avoid a QAC warning)
#else
#define mUndefinedSize()
#endif

#ifndef COMPILATION_NATIVE
typedef tTOSSeqRuleType tTOSSeqGraphType[mUndefinedSize()];
#else
typedef struct
{
    char* GraphName;
    tTOSSeqRuleType Rules[];
} tTOSSeqGraphType;
#endif

//----- Define the graphs list type -----
typedef const tTOSSeqGraphType* tTOSSeqGraphListType[cTOSSeqGraphNumber];

//----- Define the graph context type -----
typedef struct
{
    tTOSSeqGraphStateType  GraphState;
    tTOSSeqRuleId          RuleNumber;
} tTOSSeqGraphContextType ;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
extern const tTOSSeqGraphListType   TOSSeqGraphList;
extern       tTOSSeqGraphId         TOSSeqGraphNumber;  // Read only

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
//----- Macro for identified the rule -----
#define mTOSSeqRuleNumber(RuleNumber)   (RuleNumber)

//----- Macro for identified graph instance -----
#define mTOSSeqGetGraphInstance(GraphId)              \
        ((tTOSSeqGraphInstance)(TOSSeqGraphNumber - (GraphId)))

//----- Macro for get graph Id with instance to graph name -----
#define mTOSSeqGetGraphInstanceId(GraphId,Instance)   \
        ((tTOSSeqGraphId)((GraphId) + ((tTOSSeqGraphId)(Instance))))

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
//==============================================================================
// DESCRIPTION:         Initializes the Tos_seq component
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  - Sets all graphs state to cTOSSeqInactiveGraph;
//                      - Resets all current rule's ID.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSeqInitialize(void);

//==============================================================================
// DESCRIPTION:         Gives the current graph state
//
// PARAMETERS:          GraphNumber - Graph Id in bounds (0 - cTOSSeqGraphNumber).
//
// RETURN VALUE:        tTOSSeqGraphStateType
//
// DESIGN INFORMATION:  Returns the graph state.
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE tTOSSeqGraphStateType TOSSeqGraphState(const tTOSSeqGraphId GraphNumber);

//==============================================================================
// DESCRIPTION:         Activates graph
//
// PARAMETERS:          GraphNumber - Graph Id in bounds (0 - cTOSSeqGraphNumber).
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  - Sets the graph state to cTOSSeqActiveGraph;
//                      - Resets the current rule ID of the graph.
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE void TOSSeqActivateGraph(const tTOSSeqGraphId GraphNumber);

//==============================================================================
// DESCRIPTION:         Deactivates graph
//
// PARAMETERS:          GraphNumber - Graph Id in bounds (0 - cTOSSeqGraphNumber).
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets the graph state to cTOSSeqInactiveGraph.
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE void TOSSeqDeactivateGraph(const tTOSSeqGraphId GraphNumber);

//==============================================================================
// DESCRIPTION:         Freezes graph
//
// PARAMETERS:          GraphNumber - Graph Id in bounds (0 - cTOSSeqGraphNumber).
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets the graph state to cTOSSeqFrozenGraph.
//                      Refer to Detailed Design Document
//==============================================================================
void     TOSSeqFreezeGraph(const tTOSSeqGraphId GraphNumber);

//==============================================================================
// DESCRIPTION:         Unfreezes graph
//
// PARAMETERS:          GraphNumber - Graph Id in bounds (0 - cTOSSeqGraphNumber).
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets the graph state to cTOSSeqActiveGraph.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSeqUnfreezeGraph(const tTOSSeqGraphId GraphNumber);

//==============================================================================
// DESCRIPTION:         Executes the scheduling from StartGraph to EndGraph
//
// PARAMETERS:          StartGraph - Graph ID in bounds 0-(Number of Graphs-1)
//                      EndGraph   - Graph ID in bounds 0-(Number of Graphs-1)
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Goes through the graphs from StartGraph to EndGraph.
//                      If the current graph is activated, calls ScanGraph() and
//                      calls the scheduler.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSeqMotor(const tTOSSeqGraphId StartGraph,const tTOSSeqGraphId EndGraph);

//==============================================================================
// DESCRIPTION:         Represents an always true evaluation
//
// PARAMETERS:          None
//
// RETURN VALUE:        Always cTrue
//
// DESIGN INFORMATION:  Returns always TRUE.
//                      Refer to Detailed Design Document
//==============================================================================
BOOL TOSSeqTrueEval(void);

//==============================================================================
// DESCRIPTION:         Represents an empty action
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Does nothing - an empty function.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSeqNoAction(void);

#endif // I_TOS_SEQ_H
