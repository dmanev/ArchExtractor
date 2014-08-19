//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      SW0032
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    This component manages the sharing of the access to the EEPROM
//               from several processes.
// -----------------------------------------------------------------------------
// QACJ - (0288): Specific comment characters needed for PVCS compatibility
// $Date:   04 Feb 2009 17:02:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/DAT_EEP.C-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
// QACJ - (2017): Comment style needed for our toolkit
/* $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/DAT_EEP.C-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:02:50   adzhelp
// Initial revision.
*/
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define DAT_EEP  "DAT_EEP"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "LIB.h"
#include "TOS.h"
#include "LDB.h"
#ifdef _QAC_
#include "DAT.h"
#endif
#include "DAT_EEP.h"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------

#define cInvalidProcessHandle ((tDATEepProcessHandle) 0xFFU)

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
#define mConvAdress16ToAdr8( Adr16 ) (tAddress)((Adr16) << 1U)


#if ((cDATEepPageSize > 2) && ((cDATEepPageSize % 2) == 0))

#define mIsDataIdentical(pSourceData, pReadData, lng) \
                (mLIBmemcmp((pReadData), (pSourceData), lng) == 0)

#define mGetTransferSize(address) GetMaxBurstTransferSize(address)
#define DAT_EEP_BURST_MODE_ACTIVE

#elif (cDATEepPageSize == 2)

#define mIsDataIdentical(pSourceData, pReadData, lng) \
                ((pReadData)[0] == (pSourceData)[0]) 

#define mGetTransferSize(address)    ((LDBPARAM_TYPE_LNGMSG)2)

#else

#error "cDATEepPageSize: incorrect value. 2 is min value.\
    For the max value check the EEPROM specification!.\
    The value must be devisable by 2"

#endif


#ifdef TOSSuspendAllInterupts
  #define  mSuspendIT()\
  TOSSuspendAllInterupts() // Ancienne version de TOS_ORD (TOS.h Rev 1.12)
#else
  #define  mSuspendIT()\
  TOSSuspendOSInterrupts() // Nouvelle version de TOS_ORD (TOS.h Rev 1.13)
#endif

#ifdef TOSResumeAllInterupts
  #define  mResumeIT()\
  TOSResumeAllInterupts() // Ancienne version de TOS_ORD (TOS.h Rev 1.12)
#else
  #define  mResumeIT()\
  TOSResumeOSInterrupts() // Nouvelle version de TOS_ORD (TOS.h Rev 1.13)
#endif

#ifdef TOSDisableOSInterrupts
  #define mDisableIT()\
  TOSDisableOSInterrupts() // Nouvelle version de TOS_ORD (TOS.h Rev 1.13)
#else
  #define mDisableIT()\
  TOSDisableAllInterupts() // Ancienne version de TOS_ORD (TOS.h Rev 1.12)
#endif

#ifdef TOSEnableOSInterrupts
  #define mEnableIT()\
  TOSEnableOSInterrupts() // Nouvelle version de TOS_ORD (TOS.h Rev 1.13)
#else
  #define mEnableIT()\
  TOSEnableAllInterupts() // Ancienne version de TOS_ORD (TOS.h Rev 1.12)
#endif
//------------------------------------------------------------------------------
// Local types
//
// typedef Expression   tTypeName;
//------------------------------------------------------------------------------

// States of main machine
typedef enum
{
    cStateReady,
    cStateReading,
    cStateComparing,
    cStateUnLocking,
    cStateChecking,
    cStateWriting,
    cStateLocking,
    cStateUnprotecting
} tState;


// Paramaters of Command machine
typedef enum
{
    cCmdRead,
    cCmdWrite,
    cCmdLock,
    cCmdUnlock,
    cCmdUnprotect
} tCommandType;

typedef struct
{
    tMsg         Msg;
    U16          Adress;
    tCommandType Type;
} tCommand;

// States of command machine
typedef enum
{
    cCommandStateFree,
    cCommandStateFrozen,
    cCommandStateProcessing,
    cCommandStateFinished
} tCommandState;

#if cDATEepExtendedNumberOfProcess <= 8U
typedef U8 tActiveProcessList;
#else
    #if cDATEepExtendedNumberOfProcess <= 16U
typedef U16 tActiveProcessList;
    #else
        #if cDATEepExtendedNumberOfProcess <= 32U
typedef U32 tActiveProcessList;
        #else
            #error "Too many processes"
        #endif
    #endif
#endif

// -----------------------------------------------------------------------------
// Local data
//
// static  tType   u8VariableName;  
// static  tType*  pu8VariableName; 
//------------------------------------------------------------------------------

// Process schedule
static tDATEepProcessHandle ActiveProcessHandle;
static tActiveProcessList   ActiveProcessList;

// Main state machine
static tState        State;
static U8            WriteRetryCounter;
static U16			 ReadBuffer[cDATEepPageSize / 2];
static U16*          UserBuffer;
static tDATEepOffset OffsetFromUserBuffer;
static tDATEepOffset LastOffset;

// Command state machine
static volatile tCommandState  CommandState;
static tCommand             Command;
static tTOSTimer            CommandTempo;
static tTOSAlarm            Alarm;



//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

static const tDATEepBloc BlocList[cDATEepExtendedNumberOfProcess ] =
    { mDATEepProcessInformationTable() };

//QACJ 3218: Coding rule mismatch with static scopes.
static const tpfCallBack CallBackList[cDATEepExtendedNumberOfCallBack] = 
	{ mDATEepExtendedCallBackList() };
//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------

U16 DATEepBuffer[cDATEepBufferSize];

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION : Calls the callback function of the active process
//
// PARAMETERS (Type,Name,Min,Max) : 
//    BOOL StatusOk: cTrue if the last operation is a success, cFalse otherwise.
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
static void CallUser(BOOL StatusOk)
{
    U8 CallBackIndex;

    mLIBassert( ActiveProcessHandle < cDATEepExtendedNumberOfProcess );
    CallBackIndex = BlocList[ActiveProcessHandle].CallBackNumber;

    mLIBassert( CallBackIndex < cDATEepExtendedNumberOfCallBack );
    CallBackList[CallBackIndex]( ActiveProcessHandle, StatusOk );
}


//==============================================================================
// DESCRIPTION : Translate the contents of the Command variable into LDB call
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
static void SendCommand( void )
{
    mLIBassert( CommandState == cCommandStateProcessing );

    TOSStartTimer( &CommandTempo );

    switch( Command.Type )
    {
    case( cCmdRead ) :
        // This is a read command
        LDBReceiveWithAddr( cLDBChannelEep, mConvAdress16ToAdr8(Command.Adress), &Command.Msg );
        break;

    case( cCmdWrite ) :
        // This is a write command
        LDBSendWithAddr( cLDBChannelEep, mConvAdress16ToAdr8(Command.Adress), &Command.Msg );
        break;

    case( cCmdLock ) :
        // This is a lock command
        LDBControl(cLDBChannelEep, cLDBEepLock );
        break;

    case( cCmdUnlock ) :
        // This is an unlock command
        LDBControl(cLDBChannelEep, cLDBEepUnLock );
        break;

#ifdef cLIBStkUnprotect_Used
    case( cCmdUnprotect ) :
        // This is an unprotect command
        LDBControl(cLDBChannelEep, cLDBEepUnprotect );
        break;
#endif // cLIBStkUnprotect_Used

    default:
        
        mLIBassert(cFalse);
        break;
    }
}

//==============================================================================
// DESCRIPTION : Send the LDB command that is prepared in the Command variable
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
static void StartCommand( void )
{
    BOOL IsAccessible;

    mLIBassert( CommandState == cCommandStateFree );

    if( Command.Type == cCmdRead )
    {
        // The Command state machine enter in the processing state
        CommandState = cCommandStateProcessing;
        SendCommand();
    }
    else
    {
        // For all commands exclude Read we must
        // check if the EEPROM is accesible
        IsAccessible = DATPeeIsEepromAccessible();

        if( IsAccessible == cTrue )
        {
            // The Command state machine enter in the processing state
            CommandState = cCommandStateProcessing;
            SendCommand();
        }
        else
        {
            // The Command state machine enter in the frozen state
            CommandState = cCommandStateFrozen;
        }
    }
}
#ifdef DAT_EEP_BURST_MODE_ACTIVE
//==============================================================================
// DESCRIPTION : Calculate number of bytes that could be written (read) with 
// single LDB call.
//
// PARAMETERS (Type,Name,Min,Max) :   Start address (in words)
//
// RETURN VALUE :   Number of bytes that could be fit in EEPROM page starting
// from u16Addr.
//
// DESIGN INFORMATION : 
//==============================================================================
static LDBPARAM_TYPE_LNGMSG GetMaxBurstTransferSize(U16 u16Addr)
{
    LDBPARAM_TYPE_LNGMSG result;

    U16 u16Address = (U16)(u16Addr * 2);
    U16 u16Size = (U16)((LastOffset - OffsetFromUserBuffer) * 2);

    // Physical EEPROM could read pages aligned on cDATEepPageSize boundaries
    // If the size exceed cDATEepPageSize data from the begining of the page
    // would be read instead data byte from address cDATEepPageSize+1.
    U16 u16DataOffset = (U16)(u16Address % cDATEepPageSize);
    
    if ((u16DataOffset + u16Size) > cDATEepPageSize)
    {
        result = (LDBPARAM_TYPE_LNGMSG)(cDATEepPageSize - u16DataOffset);
    }
    else
    {
        result = ((LDBPARAM_TYPE_LNGMSG)u16Size);
    }

    return result;
}
#endif
//==============================================================================
// DESCRIPTION : Update the component when a LDB command is complete.
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
static void EndOfCommand( void )
{
    tDATEepOffset  ReadDataLng;

    switch( State )
    {
        // ------------------------------------------------------
        //                 Reading State
        // ------------------------------------------------------
    case( cStateReading   ) :

        ReadDataLng = (tDATEepOffset)(Command.Msg.Lng / 2);

        OffsetFromUserBuffer = OffsetFromUserBuffer + ReadDataLng;
        
        if( OffsetFromUserBuffer < LastOffset )
        {
            // Read the next block

            //QACJ 0506: The Buffer is always checked against NULL on assigment
            Command.Msg.pBuffer = &(Command.Msg.pBuffer[Command.Msg.Lng]);
            Command.Adress = Command.Adress + ReadDataLng;
            Command.Msg.Lng = mGetTransferSize(Command.Adress);

            StartCommand();
        }
        else
        {
            // There is no more data to process
            State = cStateReady;
            CallUser( cTrue );
        }
        break;

        // ------------------------------------------------------
        //                 Comparing State
        // ------------------------------------------------------
    case( cStateComparing ) :

        //QACJ 3416: No side effect because the function change nothing
        //QACJ 0506: The UserBuffer is always checked against NULL on assigment
        if( mIsDataIdentical((&UserBuffer[OffsetFromUserBuffer]), 
						        ReadBuffer, Command.Msg.Lng) )
        {
            ReadDataLng = (tDATEepOffset)(Command.Msg.Lng / 2);

            OffsetFromUserBuffer = OffsetFromUserBuffer + ReadDataLng;

            if( OffsetFromUserBuffer < LastOffset )
            {
                // Read the next block

                Command.Adress = Command.Adress + ReadDataLng;
                Command.Msg.Lng = mGetTransferSize(Command.Adress);
                Command.Msg.pBuffer = (U8*)ReadBuffer;

                StartCommand();
            }
            else
            {
                // There is no more data to process
                State = cStateReady;
                CallUser( cTrue );
            }
        }
        else
        {
            State = cStateReady;
            CallUser( cFalse );
        }
        break;

        // ------------------------------------------------------
        //                 Checking State
        // ------------------------------------------------------
    case( cStateChecking  ) :

        //QACJ 3416: No side effect because the function change nothing
        if( mIsDataIdentical((&UserBuffer[OffsetFromUserBuffer]), 
						        ReadBuffer, Command.Msg.Lng) )
        {
            WriteRetryCounter = 0;

            ReadDataLng = (tDATEepOffset)(Command.Msg.Lng / 2);

            OffsetFromUserBuffer = OffsetFromUserBuffer + ReadDataLng;

            if( OffsetFromUserBuffer < LastOffset )
            {
                // Read the next block

                Command.Adress = Command.Adress + ReadDataLng;
                Command.Msg.Lng = mGetTransferSize(Command.Adress);
                Command.Msg.pBuffer = (U8*)ReadBuffer;

                Command.Type = cCmdRead;

                StartCommand();
            }
            else
            {
                // There is no more data to process
                // Write cycle is terminate
                State = cStateLocking;
                Command.Type = cCmdLock;
                StartCommand();
            }
        }
        else
        {
            if( WriteRetryCounter < cDATEepMaxWriteRetryNumber )
            {
                // The maximum number of retry is not reached
                // A write cycle is done for this data

                State = cStateWriting;
                WriteRetryCounter++;

                Command.Msg.pBuffer  = (U8*)&UserBuffer[OffsetFromUserBuffer];
                Command.Type = cCmdWrite;

                StartCommand();
            }
            else
            {
                // The max number of retry is reached
                // Write cycle is terminate
                State = cStateLocking;

                Command.Type = cCmdLock;
                StartCommand();
            }
        }
        break;

        // ------------------------------------------------------
        //                 Writing State
        // ------------------------------------------------------
    case( cStateWriting   ) :
        // The data write is terminated
        // A read cycle is done to verify
        Command.Msg.pBuffer = (U8*)ReadBuffer;
        
        Command.Type = cCmdRead;

        State = cStateChecking;
        StartCommand();
        break;

        // ------------------------------------------------------
        //                 Unlocking
        // ------------------------------------------------------
    case( cStateUnLocking ) :
        State = cStateChecking;
        Command.Type = cCmdRead;
        StartCommand();
        break;

        // ------------------------------------------------------
        //                 Locking
        // ------------------------------------------------------
    case( cStateLocking ) :
        State = cStateReady;
        if( WriteRetryCounter < cDATEepMaxWriteRetryNumber )
        {
            CallUser( cTrue );
        }
        else
        {
            CallUser( cFalse );
        }
        break;

        // ------------------------------------------------------
        //                 Removing the EEPROM protection if needed
        // ------------------------------------------------------
#ifdef cLIBStkUnprotect_Used
        case( cStateUnprotecting ) :
        {
          State = cStateReady;
          CallUser( cTrue );
        }
        break;
#endif // cLIBStkUnprotect_Used

        // ------------------------------------------------------
        //                 Error State
        // ------------------------------------------------------
    default :
        mLIBassert(cFalse);
        break;
    }
}


//==============================================================================
// DESCRIPTION : Periodical trigger of the state machine
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
static void CommandStateMachine(void)
{
    BOOL bResult;
    BOOL IsAccessible;

    switch( CommandState )
    {
    case(cCommandStateFrozen):

        IsAccessible = DATPeeIsEepromAccessible();

        if( IsAccessible == (BOOL) cTrue )
        {
            // The state machine can leave the frozen state
            CommandState = cCommandStateProcessing;
            SendCommand();
        }
        break;

    case(cCommandStateProcessing):

#ifdef cLDBEepCheckWriteCompletion
        if( Command.Type == cCmdWrite )
        {
            LDBControl(cLDBChannelEep, cLDBEepCheckWriteCompletion);
        }
#endif

#ifdef cLIBStkUnprotect_Used
        if( Command.Type == cCmdUnprotect )
        {
            LDBControl(cLDBChannelEep, cLDBEepUnprotect);
        }
#endif // cLIBStkUnprotect_Used

        bResult = TOSIsTimerElapsed( &CommandTempo, 
	        mTOSConvMsInTimerTick(cDATEepTimeoutLdbMs));

        if( bResult != cFalse )
        {
            // The time-out is reach
            // the command is finised
            CommandState = cCommandStateFree;
            EndOfCommand();
        }
        break;

    case(cCommandStateFinished):
        // the command is finised
        CommandState = cCommandStateFree;
        EndOfCommand();
        break;

    case(cCommandStateFree):
        break;

    default:
        mLIBassert(cFalse);
        break;
    }
}

//==============================================================================
// DESCRIPTION : Process scheduling engine. Passes from one active process to another.
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
static void ScheduleProcess(void)
{
    // No process are working
    if( ActiveProcessList != (tActiveProcessList) 0 )
    {
        // One process or more are waiting
        // we must select the next active process
        tActiveProcessList ActiveProcessMask;

        // Request ActiveSleep Mode
        TOSSendControl( cTOSControlActiveSleepRequest );
        
        ActiveProcessHandle = 0;
        ActiveProcessMask   = 1;
        while((ActiveProcessMask & ActiveProcessList) == (tActiveProcessList) 0)
        {
            ActiveProcessHandle ++;
            ActiveProcessMask <<= 1;
        }

        mLIBassert( ActiveProcessHandle<cDATEepExtendedNumberOfProcess );

        // The process request is clear
        // Modif YM le 09/01/2003: EPT URD 42 DEV 315
        // TOSSuspendAllInterupts();

        mDisableIT();

        ActiveProcessList &= ~( ActiveProcessMask );

        mEnableIT();

        CallUser( cTrue );

        // In this state the alaram is start
        TOSSetRelAlarm(
                       &Alarm,
                       0,
                       (tTOSTickAlarm) mTOSConvUsInAlarmTick(cDATEepPeriodAlarmUs)
                      );
    }
}



//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : Request of activation of a process
//
// PARAMETERS (Type,Name,Min,Max) : 
//    tDATEepProcessHandle ProcessHandle: Indentifier of the process to activate
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Result in a call of the process callback when teh EEPROM is
//    available
//==============================================================================
void DATEepProcessRequest(tDATEepProcessHandle ProcessHandle)
{
    mLIBassert( ProcessHandle<cDATEepExtendedNumberOfProcess );

    // Modif YM le 09/01/2003: EPT URD 42 DEV 315
    // TOSSuspendAllInterupts();

    mSuspendIT();

    ActiveProcessList |= ( ((tActiveProcessList)1UL) << ProcessHandle );

    mResumeIT();

    if( ActiveProcessHandle == cInvalidProcessHandle )
    {
        TOSActivateTask( cTOSTaskIdDATEepTask );
    }
}

//==============================================================================
// DESCRIPTION : Check if a process activation is pending or active.
//
// PARAMETERS (Type,Name,Min,Max) : 
//    tDATEepProcessHandle ProcessHandle: Identifier og the process to check
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
BOOL DATEepIsActivate(tDATEepProcessHandle ProcessHandle)
{
    BOOL IsActivate;

    if( ActiveProcessHandle == ProcessHandle )
    {
        // This process is currently working
        IsActivate = cTrue;
    }
    
    else if ( (ActiveProcessList & ( ((tActiveProcessList)1U) << ProcessHandle ))
              != (tActiveProcessList)0U)
    {
        // This process is not actually working,
        // This process is present in the waiting list.
        IsActivate = cTrue;
    }
    else
    {
        // This process is not actually working,
        // This process is not present in the waiting list.
        IsActivate = cFalse;
    }

    return IsActivate;
}


//==============================================================================
// DESCRIPTION : Free the currently active process so as to let the others run.
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION :
//==============================================================================
void DATEepTerminateProcess(void)
{
    mLIBassert( State == cStateReady );

    ActiveProcessHandle = cInvalidProcessHandle;
    TOSCancelAlarm( &Alarm );

    if( ActiveProcessList != (tActiveProcessList)0U )
    {
        TOSActivateTask( cTOSTaskIdDATEepTask );
    }
}
//==============================================================================
// DESCRIPTION : Read a buffer from the EEPROM in a zone belonging to the active process
//
// PARAMETERS (Type,Name,Min,Max) : 
//    U16* pBuff:        Buffer for output.
//
//    tDATEepOffset Ad:  Address to read, relative to the EEPROM zone of the process.
//						 (in 16 bit word)
//    tDATEepOffset Sz:  Size to read in bytes (in 16 bit word)
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Use this only from an active process.
//    Make sure the buffer is big enough for the size
//==============================================================================
void DATEepRead( U16* pBuff, tDATEepOffset Ad, tDATEepOffset Sz )
{
    mLIBassert( State == cStateReady );

    if( (ActiveProcessHandle != cInvalidProcessHandle) && (pBuff != NULL) )
    {
        mLIBassert( ActiveProcessHandle < cDATEepExtendedNumberOfProcess );

        State = cStateReading;

        LastOffset = Sz;
        OffsetFromUserBuffer = 0;

        Command.Adress  = Ad + BlocList[ActiveProcessHandle].Offset;
        Command.Msg.Lng = mGetTransferSize(Command.Adress);
        Command.Msg.pBuffer = (U8*)pBuff;
        Command.Type = cCmdRead;

        StartCommand();
    }
    else
    {
        mLIBassert(cFalse);
    }
}
//==============================================================================
// DESCRIPTION : Write a buffer into the EEPROM in a zone belonging to the 
// active process
//
// PARAMETERS (Type,Name,Min,Max) : 
//    U16* pBuff:       Buffer containing the source data.
//    tDATEepOffset Ad: Adress where the data must be written (in 16 bit word).
//    tDATEepOffset Sz: Size of the data (in 16 bit word).
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Use this only from an active process
//==============================================================================
void DATEepWrite  (U16* pBuff, tDATEepOffset Ad, tDATEepOffset Sz)
{
    mLIBassert( State == cStateReady );

    if( (ActiveProcessHandle != cInvalidProcessHandle) && (pBuff != NULL) )
    {
        mLIBassert( ActiveProcessHandle < cDATEepExtendedNumberOfProcess );

        if( (Sz+Ad) <= BlocList[ActiveProcessHandle].Size )
        {
            State = cStateUnLocking;

            LastOffset = Sz;
            OffsetFromUserBuffer = 0;

            Command.Adress  = Ad + BlocList[ActiveProcessHandle].Offset;
            Command.Msg.Lng = mGetTransferSize(Command.Adress);
            Command.Msg.pBuffer = (U8*)ReadBuffer;
            Command.Type = cCmdUnlock;

            UserBuffer = pBuff;

            WriteRetryCounter = 0;

            StartCommand();
        }
        else
        {
            mLIBassert(cFalse);
        }
    }
    else
    {
        mLIBassert(cFalse);
    }
}

//==============================================================================
// DESCRIPTION : Compare the contents of the EEPROM in a zone belonging to a process
//    with a RAM area
//
// PARAMETERS (Type,Name,Min,Max) : 
//    U16* pBuff:               Buffer containing the reference data.
//    tDATEepOffset Ad:  Adress where to begin the comparison, relative to the beginning
//       of the zone belonging to the process.
//    tDATEepOffset Sz: Size to compare in bytes.
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Use this only from an active process
//==============================================================================
void DATEepCompare(U16* pBuff, tDATEepOffset Ad, tDATEepOffset Sz)
{
    mLIBassert( State == cStateReady );

    if( (ActiveProcessHandle != cInvalidProcessHandle) && (pBuff != NULL) )
    {
        mLIBassert( ActiveProcessHandle < cDATEepExtendedNumberOfProcess );

        State = cStateComparing;

        LastOffset = Sz;
        OffsetFromUserBuffer = 0;

        Command.Adress  = Ad + BlocList[ActiveProcessHandle].Offset;
        Command.Msg.Lng = mGetTransferSize(Command.Adress);
        Command.Msg.pBuffer = (U8*)ReadBuffer;
        Command.Type = cCmdRead;

        UserBuffer = pBuff;

        StartCommand();
    }
    else
    {
        mLIBassert(cFalse);
    }
}

//==============================================================================
// DESCRIPTION : Read the EEPROM without process mapping
//
// PARAMETERS (Type,Name,Min,Max) :
//    U16* pBuff:               Buffer where to write the data to.
//    tDATEepOffset Ad:  Adress where to read from the EEPROM, relative to the beginning
//       of the zone belonging to the process.
//    tDATEepOffset Sz: Size to write in bytes.
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Use this only from the supervisor process when active
//==============================================================================
void DATEepAbsoluteRead (U16* pBuff, U16 Ad, tDATEepOffset Sz)
{
    mLIBassert( State == cStateReady );

    if( (ActiveProcessHandle == cDATEepProcessSupervisor) && (pBuff != NULL) )
    {
        State = cStateReading;

        LastOffset = Sz;
        OffsetFromUserBuffer = 0;

        Command.Adress  = Ad;
        Command.Msg.Lng = mGetTransferSize(Command.Adress);
        Command.Msg.pBuffer = (U8*)pBuff;
        Command.Type = cCmdRead;

        StartCommand();
    }
    else
    {
        mLIBassert(cFalse);
    }
}

//==============================================================================
// DESCRIPTION : Write into the EEPROM without process mapping
//
// PARAMETERS (Type,Name,Min,Max) : 
//    U16* pBuff:               Buffer containing the source data.
//    U16 Ad:                       Adress where to write to. 0 is the beginning of the EEPROM
//    tDATEepOffset Sz   Size to write
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Use this only from the supervisor process when active
//==============================================================================
void DATEepAbsoluteWrite(U16* pBuff, U16 Ad, tDATEepOffset Sz)
{
    mLIBassert( State == cStateReady );

    if( (ActiveProcessHandle == cDATEepProcessSupervisor) && (pBuff != NULL) )
    {
        State = cStateUnLocking;

        LastOffset = Sz;
        OffsetFromUserBuffer  = 0;

        Command.Adress  = Ad;
        Command.Msg.Lng = mGetTransferSize(Command.Adress);
        Command.Msg.pBuffer = (U8*)ReadBuffer;
        Command.Type = cCmdUnlock;

        UserBuffer = pBuff;

        WriteRetryCounter = 0;

        StartCommand();
    }
    else
    {
        mLIBassert(cFalse);
    }
}

//==============================================================================
// DESCRIPTION : Command for unprotecting the EEPROM.
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : This updates the Command contect and provokes the LDB
//    command
//==============================================================================
#ifdef cLIBStkUnprotect_Used
void DATEepUnprotect (void)
{
    mLIBassert( State == cStateReady );

    State = cStateUnprotecting;

    Command.Type          = cCmdUnprotect;
    // The other fields of Command are not reset because unuseful

    StartCommand();
}
#endif // cLIBStkUnprotect_Used


//==============================================================================
// DESCRIPTION : Callback used by LDB_EEP for indicating the completion of a LDBControl
//    operation
//
// PARAMETERS (Type,Name,Min,Max) : 
//    tCtrl Ctrl:          The type of control that is complete.
//    tStatus Status  Status of the operation (value of cLDBCorrect for success).
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void DATEepCallBackEndCtrl (tCtrl Ctrl, tStatus Status)
{
    BOOL IsCommandToFinish;

    //QACJ 3199: API change refused yet - we keep non static parameters
    Status = Status;
    Ctrl = Ctrl;

    IsCommandToFinish = cTrue;

#ifdef cLDBEepCheckWriteCompletion
    if( Ctrl == cLDBEepCheckWriteCompletion )
    {
        // The write operation is not complete before LDB calls the Tx Callback
        mLIBassert(Status==cLDBCorrect);
        IsCommandToFinish = cFalse;
    }
#endif // cLDBEepCheckWriteCompletion

#ifdef cLIBStkUnprotect_Used
    if( Status == cLDBEepControlInProgress )
    {
        // The command is not over while the callback says
        //    cLDBEepControlInProgress. linited to the unprotect service
        mLIBassert(Ctrl == cLDBEepUnprotect);
        IsCommandToFinish = cFalse;
    }
#endif // cLIBStkUnprotect_Used
    
    if (IsCommandToFinish != cFalse)
    {
        mLIBassert(Status==cLDBCorrect);
        CommandState = cCommandStateFinished;
        TOSActivateTask( cTOSTaskIdDATEepTask );
    }
}

//==============================================================================
// DESCRIPTION : DATEepCallBackTxWithAddr
//
// PARAMETERS (Type,Name,Min,Max) : 
//    tAddress Unused:  Address targetted by the write request that is complete
//    tStatus Status:      Status of the write operation. cLDBCorrect for success.
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void DATEepCallBackTxWithAddr (tAddress Unused, tStatus Status)
{
    mLIBassert(Status==cLDBCorrect);
    //QACJ 3199: API change refused yet - we keep non static parameters
    Status = Status;
    //QACJ 3199: API change refused yet - we keep non static parameters
    Unused = Unused;

    CommandState = cCommandStateFinished;
    TOSActivateTask( cTOSTaskIdDATEepTask );
}

//==============================================================================
// DESCRIPTION : Callback used by LDB_EEP for indicating the completion of a read
//    operation.
//
// PARAMETERS (Type,Name,Min,Max) : 
//    tAddress Unused:  Address targetted by the read request that is complete
//    tStatus Status:      Status of the read operation. cLDBCorrect for success.
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void DATEepCallBackRxWithAddr (tAddress Unused, tStatus Status)
{
    mLIBassert(Status==cLDBCorrect);
    //QACJ 3199: API change refused yet - we keep non static parameters
    Status = Status;
    //QACJ 3199: API change refused yet - we keep non static parameters
    Unused = Unused;

    CommandState = cCommandStateFinished;
    TOSActivateTask( cTOSTaskIdDATEepTask );
}

//==============================================================================
// DESCRIPTION : DAT_EEP task
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void DATEepTask(void)
{
    if( ActiveProcessHandle != cInvalidProcessHandle )
    {
        CommandStateMachine();
    }
    else
    {
        ScheduleProcess();
    }
}

//==============================================================================
// DESCRIPTION : Initialize DAT_EEP
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void DATEepInit(void)
{
    ActiveProcessList = 0;
    State = cStateReady;
    ActiveProcessHandle = cInvalidProcessHandle;
    CommandState = cCommandStateFree;
    Alarm.TaskID = cTOSTaskIdDATEepTask;
}

//==============================================================================
// DESCRIPTION : Sends the MaintainActiveSleep signal unless DAT_EEP is inactive
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void DATEepIsMaintainActiveSleepState( void )
{
    BOOL IsProcessing = (BOOL) DATEepIsProcessing();

    if( IsProcessing != cFalse )
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveSleepState);
    }
}


//==============================================================================
// DESCRIPTION : Checks if any process is pending or active
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================

BOOL DATEepIsProcessing(void)
{
    BOOL IsProcessingReturn;

    if (ActiveProcessHandle != cInvalidProcessHandle)
    {
        // A process is active
        IsProcessingReturn = cTrue;
    }
    else if (!(ActiveProcessList == (tActiveProcessList)0))
    {
        // A process has requested activity but is not schedulled yed
        IsProcessingReturn = cTrue;
    }
    else
    {
        // This block erradicates a QAC warning
        IsProcessingReturn = cFalse;
    }

    return IsProcessingReturn;
}


