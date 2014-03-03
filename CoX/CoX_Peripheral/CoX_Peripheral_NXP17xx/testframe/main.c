//*****************************************************************************
//
//! \file main.c
//! \brief Test main.
//! \version 1.0
//! \date 5/17/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "test.h"


int main(void)
{
    //
    // Do the main test
    //
    TestMain();

    while(1)
    {
      //xHWREG(SIM_SRVCOP) = 0x55;
      //xHWREG(SIM_SRVCOP) = 0xAA;
    }
}
