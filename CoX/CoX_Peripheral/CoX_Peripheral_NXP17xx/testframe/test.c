//*****************************************************************************
//
//! \file test.c
//! \brief Tests support code.
//! \version 1.0
//! \date 5/19/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "test.h"
#include "testcase.h"



#ifdef ENHANCE_MODE

//
// the following const value only used in TestAssert function
//
#define FSM_BEGIN       0
#define FSM_END         1
#define FSM_CHAR        2
#define FSM_DISPATCH    3
#define NEW_LINE                                                               \
"------------------------------------------------------------------------------"

typedef void (* VirtualIoPort)(char);


//
// private function
//

static uint32 NumToStr (uint32 Num,
                        uint32 Base,
                        uint8  *Buffer,
                        uint32 BufferSize);

static uint32 PrintDec (VirtualIoPort pIOPutChar,
                        void * pParam);

static uint32 PrintHex (VirtualIoPort pIOPutChar,
                        void * pParam);

static uint32 PrintStr (VirtualIoPort pIOPutChar,
                        void * pParam);

static uint32 Print    (VirtualIoPort pIoPutchar,
                        const char * pcMsg,
                        va_list VarPara);
static void   BufWrite (char ch);

//
// Public function
//
uint32 FILE_Print  (const char * pcMsg, ...);
uint32 UART_Print  (const char * pcMsg, ...);
void   _TestAssert (const char * pcMsg, ...);

#else

static void PrintN(unsigned long n);
static void Print(char* pcMsg);
static void PrintLine(char* pcMsg);
static void PrintNewLine(void);
static void PrintTokens(void);
#endif

static void ClearTokens(void);
static void ExecuteTest(const tTestCase *psTest);
static xtBoolean _TestFail(void);


static xtBoolean g_bLocalFail, g_bGlobalFail;

//
// tokens buffer
//
static char g_pcTokensBuffer[TEST_TOKENS_MAX_NUM];

//
// error string buffer
//
static char g_pcErrorInfoBuffer[TEST_ERROR_BUF_SIZE];

//
// Error Info Buffer Index
//
static unsigned long ErrorBufIndex;

//
// current point of the token buffer
//
static char *g_pcTok;

#ifndef ENHANCE_MODE
//*****************************************************************************
//
//! \brief Prints a decimal unsigned number.
//!
//! \param n is the number to be printed
//!
//! \details Prints a decimal unsigned number.
//!
//! \return None.
//
//*****************************************************************************
static
void PrintN(unsigned long n)
{
    char buf[16], *p;

    if (n == 0)
    {
        TestIOPut('0');
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > buf)
            TestIOPut(*--p);
    }
}

//*****************************************************************************
//
//! \brief Prints a line without final end-of-line.
//!
//! \param pcMsg is the message to print
//!
//! \details Prints a line without final end-of-line.
//!
//! \return None.
//
//*****************************************************************************
static void
Print(char *pcMsg)
{
    while (*pcMsg != '\0')
    {
        TestIOPut(*pcMsg++);
    }
}

//*****************************************************************************
//
//! \brief Prints a line.
//!
//! \param pcMsg is the message to print
//!
//! \details Prints a line.
//!
//! \return None.
//
//*****************************************************************************
static void
PrintLine(char *pcMsg)
{
    Print(pcMsg);
    TestIOPut('\r');
    TestIOPut('\n');
}

//*****************************************************************************
//
//! \brief Prints a line of "---".
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
static void
PrintNewLine(void)
{
    unsigned int i;
    for (i = 0; i < 76; i++)
    {
        TestIOPut('-');
    }
    TestIOPut('\r');
    TestIOPut('\n');
}
#endif

//*****************************************************************************
//
//! \brief clear the token buffer
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
static void
ClearTokens(void)
{
    g_pcTok = g_pcTokensBuffer;
}

#ifndef ENHANCE_MODE
//*****************************************************************************
//
//! \brief Print the tokens.
//!
//! \param None
//!
//!
//! \return None.
//
//*****************************************************************************
static void
PrintTokens(void)
{
    char *pcToken = g_pcTokensBuffer;

    while (pcToken < g_pcTok)
    {
        TestIOPut(*pcToken++);
    }
}
#endif

//*****************************************************************************
//
//! \brief Emits a token into the tokens buffer.
//!
//! \param token is a char to be emit into the buffer
//!
//! \return None.
//
//*****************************************************************************
void TestEmitToken(char cToken)
{
    TestDisableIRQ();
    if(g_pcTok < (g_pcTokensBuffer + TEST_TOKENS_MAX_NUM) )
    {
        *g_pcTok++ = cToken;
    }
    TestEnableIRQ();
}

#ifndef ENHANCE_MODE
//*****************************************************************************
//
//! \brief Clear Error info buffer.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static void
TestErrorInfoClear(void)
{
    int i = 0;

    while(i < TEST_ERROR_BUF_SIZE)
    {
        g_pcErrorInfoBuffer[i++] = '\0';
    }

}

//*****************************************************************************
//
//! \brief store the error message.
//!
//! \param pcMessage is the point of the error message.
//!
//! \return None.
//
//*****************************************************************************
static void
TestErrorInfoStore(char *pcMessage)
{
    int i = 0;

    while((i < TEST_ERROR_BUF_SIZE-1) && g_pcErrorInfoBuffer[i] != '\0')
    {
        i++;
    }

    while ((*pcMessage != '\0') && (i < TEST_ERROR_BUF_SIZE-1))
    {
        g_pcErrorInfoBuffer[i++] = *pcMessage++;
    }

    g_pcErrorInfoBuffer[i] = '\0';
}

//*****************************************************************************
//
//! \brief store the error message.
//!
//! \param n is a number.
//!
//! \return None.
//
//*****************************************************************************
static void
TestErrorInfoStoreNumber(unsigned long n)
{
    char buf[16], *p;

    int i = 0;

    while((i < TEST_ERROR_BUF_SIZE-1) && g_pcErrorInfoBuffer[i] != '\0')
    {
        i++;
    }


    if (n == 0 && (i < TEST_ERROR_BUF_SIZE-1))
    {
        g_pcErrorInfoBuffer[i++] = '0';
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }


        while (p > buf)
        {
            g_pcErrorInfoBuffer[i++] = *--p;
        }
    }

    g_pcErrorInfoBuffer[i] = '\0';

}
#endif

//*****************************************************************************
//
//! \brief set the global value of error flag.
//!
//! \return None.
//
//*****************************************************************************
static xtBoolean
_TestFail(void)
{
    g_bLocalFail = xtrue;
    g_bGlobalFail = xtrue;
    return xtrue;
}

#ifndef ENHANCE_MODE
//*****************************************************************************
//
//! \brief Test assertion.
//!
//! \param pcFile is the current file name. usually is \b __FILE__
//! \param ulLine is the current line number. usually is \b __LINE__
//! \param bCondition is the checking expr. \b xtrue, \bxfalse
//! \param pcMsg failure message
//!
//! \details The TestAssert macro, which does the actual assertion checking.
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
_TestAssert(char* pcFile, unsigned long ulLine,
              xtBoolean bCondition,
              char * pcMsg)
{
    if (bCondition == xfalse)
    {
        TestErrorInfoClear();
        TestErrorInfoStore("\r\nFile:\t");
        TestErrorInfoStore(pcFile);
        TestErrorInfoStore("\r\nLine:\t");
        TestErrorInfoStoreNumber(ulLine);
        TestErrorInfoStore("\r\nError:\t");
        TestErrorInfoStore(pcMsg);
        return _TestFail();
    }

    return xfalse;
}
#endif

//*****************************************************************************
//
//! \brief Test sequence assertion.
//!
//! \param pcExpected is the expect token seq.
//! \param ulDelay wait delay time

//!
//! \details Test sequence assertion.
//! \note If ulDelay is -1,then this will not break until sequence token is
//! finished! if ulDelay is not -1,then it will be wait delay time.ulDelay
//! is 0,show that there will be no delay!
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
_TestAssertSequenceBreak(char *pcExpected, unsigned long ulDelay)
{
    char *cp = g_pcTokensBuffer;
    unsigned long ulTemp = ulDelay;
    do
    {
        while (cp < g_pcTok)
        {
            if (*cp++ != *pcExpected++)
            {
                return _TestFail();
            }
        }
        SysCtlDelay(1);
        if (*pcExpected == '\0')
        {
            ClearTokens();
            return xfalse;
        }
        if (ulDelay == 0xFFFFFFFF)
        {
            ulTemp = 1;
        }
        else if(ulDelay != 0)
        {
            ulTemp--;
        }
    } while(ulTemp);
    return _TestFail();
}

//*****************************************************************************
//
//! \brief Execute the test.
//!
//! \param psTest is the point of the test case.
//!
//! \details Test suite execution.
//!
//! \return None.
//
//*****************************************************************************
static void
ExecuteTest(const tTestCase *psTest)
{
    //
    // Initialization
    //
    ClearTokens();
    g_bLocalFail = xfalse;

    if (psTest->Setup != 0)
    {
        psTest->Setup();
    }

    psTest->Execute();

    if (psTest->TearDown != 0)
    {
        psTest->TearDown();
    }
}


#ifndef ENHANCE_MODE
//*****************************************************************************
//
//! \brief Test execution thread function.
//!
//! \param None
//!
//! \details Test execution thread function.
//!
//! \return The test result xtrue or xfalse.
//
//*****************************************************************************
xtBoolean
TestMain(void)
{
    int i, j;

    TestIOInit();

    PrintLine("");
    PrintLine("*** CooCox CoIDE components test suites");
    PrintLine("***");
#ifdef TEST_COMPONENTS_NAME
    Print("*** Components: ");
    PrintLine(TEST_COMPONENTS_NAME);
#endif
#ifdef TEST_COMPONENTS_VERSION
    Print("*** Version:       ");
    PrintLine(TEST_COMPONENTS_VERSION);
#endif
#ifdef TEST_BOARD_NAME
    Print("*** Test Board:   ");
    PrintLine(TEST_BOARD_NAME);
#endif
    PrintLine("");

    g_bGlobalFail = xfalse;
    i = 0;
    while (g_psPatterns[i])
    {
        j = 0;
        while (g_psPatterns[i][j])
        {
            PrintNewLine();
            Print("--- Test Case ");
            PrintN(i + 1);
            Print(".");
            PrintN(j + 1);
            Print(" (");
            Print(g_psPatterns[i][j]->GetTest());
            PrintLine(")");

            ExecuteTest(g_psPatterns[i][j]);
            if (g_bLocalFail == xtrue)
            {
                Print("--- Result: FAILURE ");
                PrintLine("");
                //
                //printf error information
                //
                Print(g_pcErrorInfoBuffer);
                PrintLine("");
                if (g_pcTokensBuffer < g_pcTok)
                {
                    Print(" The tokens in buffer is: ");
                    PrintTokens();
                    PrintLine("");
                }
            }
            else
            {
                PrintLine("--- Result: SUCCESS ");
            }
            j++;
        }
        i++;
    }

    PrintNewLine();
    PrintLine("");
    Print("Final result: ");

    if (g_bGlobalFail == xtrue)
    PrintLine("FAILURE");
    else
    PrintLine("SUCCESS");

    return g_bGlobalFail;
}
#endif

//
// Enhance Mode
//
#ifdef ENHANCE_MODE
static uint32 NumToStr(uint32 Num,
                       uint32  Base,
                       uint8  *Buffer,
                       uint32 BufferSize)
{
    uint32        tmpNum = Num;
    uint32        index  = 0;
    uint32        Strlen = 0;
    const uint8 * NumStr = (uint8 *)"0123456789ABCDEF";

    if((Buffer == NULL) || (BufferSize == 0))
    {
        Strlen = 0;
        return (Strlen);
    }

    if(tmpNum == 0)
    {
        *Buffer = '0';
        *(Buffer+1) = '\0';

        Strlen = 1;
        return (Strlen);
    }

    while(tmpNum)
    {
        tmpNum /= Base;
        index++;
    }

    Strlen = index;
    if(Strlen > (BufferSize-1))
    {
        Strlen = 0;
        return (Strlen);
    }

    *(Buffer + index) = '\0';
    tmpNum = Num;

    while(tmpNum)
    {
        --index;
        *(Buffer + index) = (uint8)*(tmpNum%Base + NumStr);
        tmpNum /= Base;
    }

    return (Strlen);
}


static uint32 PrintDec(VirtualIoPort pIOPutChar, void * pParam)
{
#define BUF_SIZE 16
    uint32 i             = 0;
    uint32 NumOfChar     = 0;
    uint32 DecValue      = 0;
    uint8  Buf[BUF_SIZE] = {0};

    //
    // check the argument
    //
    if(NULL == pParam)
    {
        return NumOfChar;
    }

    DecValue = (uint32)pParam;

    //
    // Clear the memory
    //
    for(i = 0; i < BUF_SIZE; i++)
    {
        Buf[i] = '\0';
    }

    //
    // Convert num to dec format
    //
    NumToStr(DecValue, 10, &Buf[0], BUF_SIZE);

    //
    // Output String to IO port,and count the num of chars
    //
    for(i = 0; (i < BUF_SIZE) && ('\0' != Buf[i]); i++)
    {
        (*pIOPutChar)(Buf[i]);
        NumOfChar++;
    }

    return NumOfChar;
#undef BUF_SIZE
}

static uint32 PrintStr(VirtualIoPort pIOPutChar, void * pParam)
{
    uint32 NumOfChar = 0;
    uint8  *pStr     = 0;

    //
    // Check the argument
    //
    if(NULL == pParam)
    {
        return NumOfChar;
    }

    pStr = (uint8 *) pParam;

    //
    // Output the string and count the number of char
    //
    while(*pStr)
    {
        NumOfChar++;
        (*pIOPutChar)(*pStr++);
    }

    return NumOfChar;
}


static uint32 PrintHex(VirtualIoPort pIOPutChar, void * pParam)
{
#define BUF_SIZE 16
    uint32 i             = 0;
    uint32 NumOfChar     = 0;
    uint32 HexValue      = 0;
    uint8  Buf[BUF_SIZE] = {'0','X'};

    //
    // check the argument
    //
    if(NULL == pParam)
    {
        return NumOfChar;
    }

    HexValue = (uint32)pParam;

    //
    // Clear the memory, expect the first two value('0','X')
    //
    for(i = 2; i < BUF_SIZE; i++)
    {
        Buf[i] = '\0';
    }

    //
    // Convert num to hex format
    //
    NumToStr(HexValue, 16, &Buf[2], (BUF_SIZE-2));

    //
    // Output String to IO port,and count the num of chars
    //
    for(i = 0; (i < BUF_SIZE) && ('\0' != Buf[i]); i++)
    {
        (*pIOPutChar)(Buf[i]);
        NumOfChar++;
    }

    return NumOfChar;
#undef BUF_SIZE
}

uint32 Print(VirtualIoPort pIoPutchar, const char * pcMsg, va_list VarPara)
{
    uint8   Token     = 0;
    uint32  NumOfChar = 0;
    const char * pStr = pcMsg;

    uint32 FSM_Status = FSM_BEGIN;

    //
    //vaild pointer, return 0
    //
    if(NULL == pStr)
    {
        return 0;
    }

    //
    // use FSM(Fimit state Machine) to deal string
    //
    while(1)
    {
        switch(FSM_Status)
        {
            case FSM_BEGIN:
                {
                    Token = *pStr;

                    if('\0' == Token)
                    {
                        FSM_Status = FSM_END;
                    }
                    else if('%' == Token)
                    {
                        pStr += 1;
                        FSM_Status = FSM_DISPATCH;
                    }
                    else
                    {
                        FSM_Status = FSM_CHAR;
                    }

                    break;
                }
            case FSM_CHAR:
                {
                   (*pIoPutchar)(*pStr++);
                    NumOfChar++;
                    FSM_Status = FSM_BEGIN;
                    break;
                }
            case FSM_DISPATCH:
                {
                    Token = *pStr++;
                    FSM_Status = FSM_BEGIN;
                    switch(Token)
                    {
                        case 'x':
                        case 'X':
                            {
                                uint32 InputPara = 0;
                                InputPara = va_arg(VarPara, uint32);
                                NumOfChar += PrintHex(pIoPutchar, (void *)InputPara);
                                break;
                            }
                       case 'd':
                            {
                                uint32 InputPara = 0;
                                InputPara = va_arg(VarPara, uint32);
                                NumOfChar += PrintDec(pIoPutchar, (void *)InputPara);
                                break;
                            }
                       case 's':
                            {
                                uint8  *InputPara = 0;
                                InputPara = va_arg(VarPara, uint8 *);
                                NumOfChar += PrintStr(pIoPutchar, (void *)InputPara);
                                break;
                            }

                       //
                       // If you want to add new function, add your code here
                       // for example: you can add %p feature in ErrorPrint
                       // for you can print the address of varilable
                       //
                       // case 'p':
                       // {
                       //     //your code is here
                       //
                       //     uint8  *InputPara = 0;
                       //     InputPara = va_arg(pVar, uint8 *);
                       //     NumOfChar += PrintPointer(pIoPutchar, (void *)InputPara);
                       //     break;
                       // }
                       //

                       default:
                            {
                                (*pIoPutchar)(Token);
                                NumOfChar++;
                                break;
                            }
                    }
                    break;
                }
            case FSM_END:
                {
                    va_end(pVar);
                    return NumOfChar;
                }
        }

    }
}

static void BufWrite(char ch)
{
    if(ErrorBufIndex < TEST_ERROR_BUF_SIZE)
    {
        g_pcErrorInfoBuffer[ErrorBufIndex++] = ch;
    }
}

uint32 FILE_Print(const char * pcMsg, ...)
{
    uint32 count = 0;
    va_list InputVar;
    va_start(InputVar, pcMsg);
    count = Print(BufWrite, pcMsg, InputVar);
    va_end(InputVar);
    return count;
}

uint32 UART_Print(const char * pcMsg, ...)
{
    uint32 count = 0;
    va_list InputVar;
    va_start(InputVar, pcMsg);
    count = Print(TestIOPut, pcMsg, InputVar);
    va_end(InputVar);
    return count;
}

void _TestAssert(const char * pcMsg, ...)
{
    va_list InputVar;

    ErrorBufIndex = 0;
    memset(g_pcErrorInfoBuffer, '\0', TEST_ERROR_BUF_SIZE);
    va_start(InputVar, pcMsg);
    Print(BufWrite, pcMsg, InputVar);
    va_end(InputVar);
    _TestFail();
}

//*****************************************************************************
//
//! \brief Test execution thread function.
//!
//! \param None
//!
//! \details Test execution thread function.
//!
//! \return The test result xtrue or xfalse.
//
//*****************************************************************************
xtBoolean TestMain(void)
{
    uint32 i = 0;
    uint32 j = 0;

    TestIOInit();

    UART_Print("\r\n*** CooCox CoIDE components test suites\r\n");
#ifdef TEST_COMPONENTS_NAME
    UART_Print("*** Components: %s\r\n", TEST_COMPONENTS_NAME);
#endif
#ifdef TEST_COMPONENTS_VERSION
    UART_Print("*** Version   : %s\r\n", TEST_COMPONENTS_VERSION);
#endif
#ifdef TEST_BOARD_NAME
    UART_Print("*** Test Board: %s\r\n", TEST_BOARD_NAME);
#endif
    g_bGlobalFail = xfalse;

    i = 0;
    while (g_psPatterns[i])
    {
        j = 0;
        while (g_psPatterns[i][j])
        {
            UART_Print("%s\r\n--- Test Case %d.%d", NEW_LINE, i+1, j+1);
            UART_Print("(%s)\r\n", g_psPatterns[i][j]->GetTest());

            ExecuteTest(g_psPatterns[i][j]);
            if (g_bLocalFail == xtrue)
            {

                UART_Print("--- Result: FAILURE \r\n%s\r\n", g_pcErrorInfoBuffer);

                if (g_pcTokensBuffer < g_pcTok)
                {
                    UART_Print(" The tokens in buffer is: %s\r\n", g_pcTokensBuffer);
                }
            }
            else
            {
                UART_Print("--- Result: SUCCESS \r\n");
            }
            j++;
        }
        i++;
    }

    if (g_bGlobalFail == xtrue)
    {
        UART_Print("%s\r\nFinal result: FAILURE\r\n", NEW_LINE);
    }
    else
    {
        UART_Print("%s\r\nFinal result: SUCCESS\r\n", NEW_LINE);
    }

    return g_bGlobalFail;
}

#endif




