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

static void PrintN(unsigned long n);
static void Print(char* pcMsg);
static void PrintLine(char* pcMsg);
static void ClearTokens(void);
static void PrintTokens(void);
static void ExecuteTest(const tTestCase *psTest);
static void PrintNewLine(void);
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
// current point of the token buffer
//
static char *g_pcTok;

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
    *g_pcTok++ = cToken;
    TestEnableIRQ();
}

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

