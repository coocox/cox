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
extern void GPIO_Example_LED_Blink(void);

int main(void)
{
    GPIO_Example_LED_Blink();
	
    while (1)
    {
    }
}
