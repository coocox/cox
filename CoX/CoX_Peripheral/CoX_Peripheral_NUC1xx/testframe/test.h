//*****************************************************************************
//
//! \file test.h
//! \brief Tests support header.
//! \version 1.0
//! \date 5/19/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#ifndef __TEST_H__
#define __TEST_H__

#include <stdint.h>
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"

//*****************************************************************************
//
//! \addtogroup test
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif
//*****************************************************************************
//
//! \brief   User define.
//
//*****************************************************************************
//
// determine if uart have port, if not port, assert while use while(1) instead of print.
//
#define TEST_IO_PORT

//
//! \brief Token Number 
//
#define TEST_TOKENS_MAX_NUM     10

//
//! \brief Error Buffer Size(File Name & Line Number & Error Info)
//
#define TEST_ERROR_BUF_SIZE     512

//*****************************************************************************
//
//! \brief   Structure representing a test case.
//
//*****************************************************************************
typedef struct 
{
    //
    //! \brief Test case name get function. 
    //
    char* (*GetTest)(void);

    //
    //! \brief Test case preparation function.
    //
    void (*Setup)(void);

    //
    //! \brief Test case clean up function. 
    //
    void (*TearDown)(void);

    //
    //! \brief Test case execution function.
    //
    void (*Execute)(void);
}
tTestCase;


extern xtBoolean TestMain(void);
extern void TestEmitToken(char token);

extern xtBoolean _TestAssert(char* pcFile, unsigned long ulLine, 
                             xtBoolean bCondition, 
                             char * pcMsg);

extern xtBoolean _TestAssertSequenceBreak(char *pcExpected, 
                                          unsigned long ulDelay);

//*****************************************************************************
//
// Functions should be ported.
//
//*****************************************************************************
extern void TestIOInit(void);
extern void TestIOPut(char ch);
extern void TestEnableIRQ(void);
extern void TestDisableIRQ(void);

//*****************************************************************************
//
//! \brief Test assertion.
//!
//! \param pcFile is the current file name. usually is \b __FILE__
//! \param pcLine is the current line number. usually is \b __LINE__
//! \param bCondition is the checking expr. \b xtrue, \bxfalse
//! \param pcMsg failure message
//!
//! \details The TestAssert macro, which does the actual assertion checking. 
//!
//! \return None.
//
//*****************************************************************************
#ifdef TEST_IO_PORT
#define TestAssert(bCondition, pcMsg)                                         \
        do                                                                    \
        {                                                                     \
            if (_TestAssert(__FILE__, __LINE__, bCondition, pcMsg))           \
            {                                                                 \
                return;                                                       \
            }                                                                 \
        }while(0)

#else
#define TestAssert(bCondition, pcMsg)                                         \
        do                                                                    \
        {                                                                     \
            if (_TestAssert(__FILE__, __LINE__, bCondition, pcMsg))           \
            {                                                                 \
                while(1);                                                     \
            }                                                                 \
        }while(0)

#endif

//*****************************************************************************
//
//! \brief Test sequence assertion.
//!
//! \param pcFile is the current file name. usually is \b __FILE__
//! \param pcLine is the current line number. usually is \b __LINE__
//! \param pcExpected is the expect token seq.
//! \param bCondition is the checking expr. \b xtrue, \bxfalse
//! \param pcMsg failure message
//! \param ulDelay wait delay time
//!
//! \details Test sequence assertion.
//!
//! \return None.
//
//*****************************************************************************
#ifdef TEST_IO_PORT
#define TestAssertQBreak(pcExpected, pcMsg, ulDelay)                          \
        do                                                                    \
        {                                                                     \
            if (_TestAssertSequenceBreak( pcExpected, ulDelay))               \
            {                                                                 \
                _TestAssert(__FILE__, __LINE__, 0, pcMsg);                    \
                return;                                                       \
            }                                                                 \
        }while(0)
#else
#define TestAssertQBreak(pcExpected, pcMsg, ulDelay)                          \
        do                                                                    \
        {                                                                     \
            if (_TestAssertSequenceBreak(pcExpected, ulDelay))                \
            {                                                                 \ 
                _TestAssert(__FILE__, __LINE__, 0, pcMsg);                    \
                while(1);                                                     \
            }                                                                 \
        }while(0)
#endif       

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif /* __TEST_H__ */
