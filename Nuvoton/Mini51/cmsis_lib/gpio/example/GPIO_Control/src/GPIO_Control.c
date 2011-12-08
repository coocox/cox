//*****************************************************************************
//
//! \file GPIO_Control.c
//! \brief example of GPIO.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************
void P0P1Callback(uint32_t u32P0Status, uint32_t u32P1Status);
void P2P3P4Callback(uint32_t u32P2Status, uint32_t u32P3Status, uint32_t u32P4Status);
void P5Callback(uint32_t u32P5Status);
void EINT0Callback(void);
void EINT1Callback(void);
//*****************************************************************************
//
//! Include related header files  
//
//*****************************************************************************
#include "DrvGPIO.h"
#include "DrvSYS.h"

//*****************************************************************************
//
//! \brief GPIO test.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void GpioTest(void)
{
    int32_t i32Err;

    UNLOCKREG();
    //
    // Enable high external clock and use it as system clock (HCLK)
    //
	  DrvSYS_Open(XTL_CLK);
	  
    //
    // Waiting for 12M Xtal stable
    //
    while (DrvSYS_GetChipClockSourceStatus(XTL_CLK) != 1);

    //
    // Configure Bit0 in Port1 to Output pin and Bit4 in Port3 to Input 
    // pin then close it                  
    //

    DrvGPIO_Open(E_PORT1, E_PIN0, E_IO_OUTPUT);
    DrvGPIO_Open(E_PORT3, E_PIN4, E_IO_INPUT);

    i32Err = 0;

    DrvGPIO_ClrBit(E_PORT1, E_PIN0);
    if (DrvGPIO_GetBit(E_PORT3, E_PIN4) != 0)
    {
        i32Err = 1;
    }

    DrvGPIO_SetBit(E_PORT1, E_PIN0);
    if (DrvGPIO_GetBit(E_PORT3, E_PIN4) != 1)
    {
        i32Err = 1;
    }

    DrvGPIO_Close(E_PORT1, E_PIN0);
    DrvGPIO_Close(E_PORT3, E_PIN4);

    //
    // GPIO Interrupt Test:P15, P22, P32(INT0) and P52(INT1) are used to test 
    // interrupt and control LEDs(P30)
    //

    //
    //Configure P30 for LED control
    //
    DrvGPIO_Open(E_PORT3, E_PIN0, E_IO_OUTPUT);

    //
    //Configure P15 as general GPIO interrupt
    //
    DrvGPIO_Open(E_PORT1, E_PIN5, E_IO_INPUT);
    
    //
    //The Quasi-bidirection mode could be used as input with pull up enable 
    //
    DrvGPIO_Open(E_PORT2, E_PIN2, E_IO_QUASI);

    //
    // Configure general interrupt callback function for P0/P1 and P2/P3/P4
    //
    DrvGPIO_SetIntCallback(P0P1Callback, P2P3P4Callback, P5Callback);

    DrvGPIO_EnableInt(E_PORT1, E_PIN5, E_IO_RISING, E_MODE_EDGE);

    //
    // IO_FALLING means low level trigger if it is in level trigger mode.
    //
    DrvGPIO_EnableInt(E_PORT2, E_PIN2, E_IO_FALLING, E_MODE_LEVEL);

    DrvGPIO_SetDebounceTime(0, E_DBCLKSRC_HCLK);
    DrvGPIO_EnableDebounce(E_PORT1, E_PIN5);
    DrvGPIO_EnableDebounce(E_PORT2, E_PIN2);

    DrvGPIO_EnableDebounce(E_PORT3, E_PIN2);
    DrvGPIO_EnableDebounce(E_PORT5, E_PIN2);
    
    //
    // Configure external interrupt.
    //
    DrvGPIO_InitFunction(FUNC_EXTINT0);
    DrvGPIO_InitFunction(FUNC_EXTINT1);
    DrvGPIO_EnableEINT(E_EINT0_PIN, E_IO_FALLING, E_MODE_EDGE, EINT0Callback);
    DrvGPIO_EnableEINT(E_EINT1_PIN, E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callback);
}

void P0P1Callback(uint32_t u32P0Status, uint32_t u32P1Status)
{

	DrvGPIO_SetBit(E_PORT2, E_PIN0);
}

void P2P3P4Callback(uint32_t u32P2Status, uint32_t u32P3Status, uint32_t u32P4Status)
{
	DrvGPIO_SetBit(E_PORT2, E_PIN0);
}

void P5Callback(uint32_t u32P5Status)
{

	DrvGPIO_SetBit(E_PORT2, E_PIN0);
}

void EINT0Callback(void)
{
	DrvGPIO_SetBit(E_PORT2, E_PIN0);

}

void EINT1Callback(void)
{
	DrvGPIO_SetBit(E_PORT2, E_PIN0);

}


