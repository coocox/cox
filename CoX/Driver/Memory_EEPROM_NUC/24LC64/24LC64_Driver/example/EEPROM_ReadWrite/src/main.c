//*****************************************************************************
//
//! \file main.c
//! \brief Test main.
//! \version 1.0
//! \date 9/1/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xi2c.h"
#include "xhw_i2c.h"
#include "xgpio.h"
#include "24LC64.h"
#include "hw_24LC64.h"

extern void _24LC64_Write_Read(void);

int main(void)
{
	_24LC64_Write_Read();
    while(1);
};
