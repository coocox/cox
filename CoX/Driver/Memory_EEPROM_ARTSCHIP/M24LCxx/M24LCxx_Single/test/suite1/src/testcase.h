//*****************************************************************************
//
//! \file testcase.h
//! \brief Add new testcases.
//! \version 1.0
//! \date 12/21/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2012 CooCox.  All rights reserved.
//
//*****************************************************************************

#ifndef __TESTCASE_H__
#define __TESTCASE_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \brief   User define.
//
//*****************************************************************************
//
//! \brief Test component libray name
//
#define TEST_COMPONENTS_NAME    "M24LCxx"

//
//! \brief Test component version
//
#define TEST_COMPONENTS_VERSION "1.0"

//
//! \brief Evkit name
//
#define TEST_BOARD_NAME         "STM32 fire bull develop board"


//
// Test Suites Buffer
//
extern const tTestCase * const* g_psPatterns[];


//*****************************************************************************
//
// testcases(extern the testcases)
//
//*****************************************************************************
extern const tTestCase * const psPatternM24LCxxTest[];



//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // __TESTCASE_H__

