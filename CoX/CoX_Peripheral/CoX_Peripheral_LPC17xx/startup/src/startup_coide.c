//*****************************************************************************
//
//! \file startup_coide.c
//! \brief LPC17nx MCU Startup code for CooCox CoIDE.
//!        (n can be 5,6,7,8)
//!        This module performs:
//!           - Set the initial SP
//!           - Set the vector table entries with the exceptions ISR address
//!           - Initialize data and bss
//!           - Setup the microcontroller system.
//!           - Call the application's entry point.
//!           .
//! \version V2.1.1.0
//! \todo Need to update time information.
//! \date
//! \author CooCox
//! \note You MUST define LPC MCU type before use this startup code.
//!       The MCU type can be one of the following value:
//!       - LPC_175x
//!       - LPC_176x
//!       - LPC_177x
//!       - LPC_178x
//!
//! \copy
//!
//! Copyright (c)  2013, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
//!     * Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     * Neither the name of the <ORGANIZATION> nor the names of its
//! contributors may be used to endorse or promote products derived
//! from this software without specific prior written permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
// Stack Configuration
//
//*****************************************************************************
//
// Stack size (in Words)
//
#define STACK_SIZE       0x00000200
__attribute__ ((section(".co_stack")))
unsigned long pulStack[STACK_SIZE];

#define WEAK __attribute__ ((weak))

//*****************************************************************************
//
// Declaration of the default fault handlers
//
//*****************************************************************************
void WEAK ResetHandler           (void);
void WEAK NMIIntHandler          (void);
void WEAK HardFaultIntHandler    (void);
void WEAK MemManageIntHandler    (void);
void WEAK BusFaultIntHandler     (void);
void WEAK UsageFaultIntHandler   (void);
void WEAK SVCIntHandler          (void);
void WEAK DebugMonIntHandler     (void);
void WEAK PendSVIntHandler       (void);
void WEAK SysTickIntHandler      (void);

// External Interrupts
void WEAK WDTIntHandler         (void);     // 16: Watchdog Timer
void WEAK TIMER0IntHandler      (void);     // 17: Timer0
void WEAK TIMER1IntHandler      (void);     // 18: Timer1
void WEAK TIMER2IntHandler      (void);     // 19: Timer2
void WEAK TIMER3IntHandler      (void);     // 20: Timer3
void WEAK UART0IntHandler       (void);     // 21: UART0
void WEAK UART1IntHandler       (void);     // 22: UART1
void WEAK UART2IntHandler       (void);     // 23: UART2
void WEAK UART3IntHandler       (void);     // 24: UART3
void WEAK PWM1IntHandler        (void);     // 25: PWM1
void WEAK I2C0IntHandler        (void);     // 26: I2C0
void WEAK I2C1IntHandler        (void);     // 27: I2C1
void WEAK I2C2IntHandler        (void);     // 28: I2C2
void WEAK SPIIntHandler         (void);     // 29: SPI
void WEAK SSP0IntHandler        (void);     // 30: SSP0
void WEAK SSP1IntHandler        (void);     // 31: SSP1
void WEAK PLL0IntHandler        (void);     // 32: PLL0 Lock (Main PLL)
void WEAK RTCIntHandler         (void);     // 33: Real Time Clock
void WEAK EINT0IntHandler       (void);     // 34: External Interrupt 0
void WEAK EINT1IntHandler       (void);     // 35: External Interrupt 1
void WEAK EINT2IntHandler       (void);     // 36: External Interrupt 2
void WEAK EINT3IntHandler       (void);     // 37: External Interrupt 3
void WEAK ADCIntHandler         (void);     // 38: A/D Converter
void WEAK BODIntHandler         (void);     // 39: Brown-Out Detect
void WEAK USBIntHandler         (void);     // 40: USB
void WEAK CANIntHandler         (void);     // 41: CAN
void WEAK DMAIntHandler         (void);     // 42: General Purpose DMA
void WEAK I2SIntHandler         (void);     // 43: I2S
void WEAK ENETIntHandler        (void);     // 44: Ethernet
#if defined(LPC_175x) || defined (LPC_176x)
void WEAK RITIntHandler         (void);     // 45: Repetitive Interrupt Timer
#elif defined(LPC_177x) || defined (LPC_178x)
void WEAK MCIIntHandler         (void);     // 45: SD/MMC Card
#else
#error Please select your LPC MCU first!             \
       This value can be one of the following value: \
       LPC_175x or LPC_176x or LPC_177x or LPC_178x
#endif
void WEAK MCPWMIntHandler       (void);     // 46: Motor Control PWM
void WEAK QEIIntHandler         (void);     // 47: Quadrature Encoder Interface
void WEAK PLL1IntHandler        (void);     // 48: PLL1 Lock (USB PLL)
void WEAK USBActivityIntHandler (void);     // 49: USB Activity
void WEAK CANActivityIntHandler (void);     // 50: CAN Activity
void WEAK UART4IntHandler       (void);     // 51: UART4
void WEAK SSP2IntHandler        (void);     // 52: SSP2
void WEAK LCDIntHandler         (void);     // 53: LCD
void WEAK GPIOIntHandler        (void);     // 54: GPIO
void WEAK PWM0IntHandler        (void);     // 55: PWM0
void WEAK EEPROMIntHandler      (void);     // 56: EEPROM
//*****************************************************************************
//
// Symbols defined in linker script
//
//*****************************************************************************
//
// Start address for the initialization values of the .data section.
//
extern unsigned long _sidata;

//
// Start address for the .data section
//
extern unsigned long _sdata;

//
// End address for the .data section
//
extern unsigned long _edata;

//
// Start address for the .bss section
//
extern unsigned long _sbss;

//
// End address for the .bss section
//
extern unsigned long _ebss;

//
// End address for ram
//
extern void _eram;

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************
extern int main(void);
__attribute__ ((used))
void ResetHandler(void);
static void DefaultIntHandler(void);

//
// The minimal vector table for a Cortex M3.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x00000000.
//
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void *)&pulStack[STACK_SIZE],          // The initial stack pointer
    ResetHandler                 ,          // The reset handler
    NMIIntHandler                ,          // The NMI handler
    HardFaultIntHandler          ,          // The hard fault handler
    MemManageIntHandler          ,          // The MPU fault handler
    BusFaultIntHandler           ,          // The bus fault handler
    UsageFaultIntHandler         ,          // The usage fault handler
    0                            ,          // Reserved
    0                            ,          // Reserved
    0                            ,          // Reserved
    0                            ,          // Reserved
    SVCIntHandler                ,          // SVCall handler
    DebugMonIntHandler           ,          // Debug monitor handler
    0                            ,          // Reserved
    PendSVIntHandler             ,          // The PendSV handler
    SysTickIntHandler            ,          // The SysTick handler

    // External Interrupts
    WDTIntHandler               ,          // 16: Watchdog Timer
    TIMER0IntHandler            ,          // 17: Timer0
    TIMER1IntHandler            ,          // 18: Timer1
    TIMER2IntHandler            ,          // 19: Timer2
    TIMER3IntHandler            ,          // 20: Timer3
    UART0IntHandler             ,          // 21: UART0
    UART1IntHandler             ,          // 22: UART1
    UART2IntHandler             ,          // 23: UART2
    UART3IntHandler             ,          // 24: UART3
    PWM1IntHandler              ,          // 25: PWM1
    I2C0IntHandler              ,          // 26: I2C0
    I2C1IntHandler              ,          // 27: I2C1
    I2C2IntHandler              ,          // 28: I2C2
    SPIIntHandler               ,          // 29: SPI
    SSP0IntHandler              ,          // 30: SSP0
    SSP1IntHandler              ,          // 31: SSP1
    PLL0IntHandler              ,          // 32: PLL0 Lock (Main PLL)
    RTCIntHandler               ,          // 33: Real Time Clock
    EINT0IntHandler             ,          // 34: External Interrupt 0
    EINT1IntHandler             ,          // 35: External Interrupt 1
    EINT2IntHandler             ,          // 36: External Interrupt 2
    EINT3IntHandler             ,          // 37: External Interrupt 3
    ADCIntHandler               ,          // 38: A/D Converter
    BODIntHandler               ,          // 39: Brown-Out Detect
    USBIntHandler               ,          // 40: USB
    CANIntHandler               ,          // 41: CAN
    DMAIntHandler               ,          // 42: General Purpose DMA
    I2SIntHandler               ,          // 43: I2S
    ENETIntHandler              ,          // 44: Ethernet
#if defined(LPC_175x) || defined (LPC_176x)
    RITIntHandler               ,          // 45: Repetitive Interrupt Timer
#elif defined(LPC_177x) || defined (LPC_178x)
    MCIIntHandler               ,          // 45: SD/MMC Card
#else
#error Please select your LPC MCU first!             \
       This value can be one of the following value: \
       LPC_175x or LPC_176x or LPC_177x or LPC_178x
#endif
    MCPWMIntHandler             ,          // 46: Motor Control PWM
    QEIIntHandler               ,          // 47: Quadrature Encoder Interface
    PLL1IntHandler              ,          // 48: PLL1 Lock (USB PLL)
    USBActivityIntHandler       ,          // 49: USB Activity
    CANActivityIntHandler       ,          // 50: CAN Activity
    UART4IntHandler             ,          // 51: UART4
    SSP2IntHandler              ,          // 52: SSP2
    LCDIntHandler               ,          // 53: LCD
    GPIOIntHandler              ,          // 54: GPIO
    PWM0IntHandler              ,          // 55: PWM0
    EEPROMIntHandler            ,          // 56: EEPROM
};

//*****************************************************************************
//
//! \brief This is the code that gets called when the processor first
//! starts execution following a reset event.
//!
//! \param None.
//!
//! Only the absolutely necessary set is performed, after which the
//! application supplied main() routine is called.
//!
//! \return None.
//
//*****************************************************************************
void Default_ResetHandler(void)
{
    //
    // Initialize data and bss
    //
    unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM
    //
    pulSrc = &_sidata;

    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    //
    // Zero fill the bss segment.
    //
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    //
    // Call the application's entry point.
    //
    main();
}

//*****************************************************************************
//
// Provide weak aliases for each Exception handler to the DefaultIntHandler.
// As they are weak aliases, any function with the same name will override
// this definition.
//
//*****************************************************************************

#pragma weak ResetHandler            = Default_ResetHandler
#pragma weak NMIIntHandler           = DefaultIntHandler
#pragma weak HardFaultIntHandler     = DefaultIntHandler
#pragma weak MemManageIntHandler     = DefaultIntHandler
#pragma weak BusFaultIntHandler      = DefaultIntHandler
#pragma weak UsageFaultIntHandler    = DefaultIntHandler
#pragma weak SVCIntHandler           = DefaultIntHandler
#pragma weak DebugMonIntHandler      = DefaultIntHandler
#pragma weak PendSVIntHandler        = DefaultIntHandler
#pragma weak SysTickIntHandler       = DefaultIntHandler

// External Interrupts
#pragma weak WDTIntHandler          = DefaultIntHandler    // 16: Watchdog Timer
#pragma weak TIMER0IntHandler       = DefaultIntHandler    // 17: Timer0
#pragma weak TIMER1IntHandler       = DefaultIntHandler    // 18: Timer1
#pragma weak TIMER2IntHandler       = DefaultIntHandler    // 19: Timer2
#pragma weak TIMER3IntHandler       = DefaultIntHandler    // 20: Timer3
#pragma weak UART0IntHandler        = DefaultIntHandler    // 21: UART0
#pragma weak UART1IntHandler        = DefaultIntHandler    // 22: UART1
#pragma weak UART2IntHandler        = DefaultIntHandler    // 23: UART2
#pragma weak UART3IntHandler        = DefaultIntHandler    // 24: UART3
#pragma weak PWM1IntHandler         = DefaultIntHandler    // 25: PWM1
#pragma weak I2C0IntHandler         = DefaultIntHandler    // 26: I2C0
#pragma weak I2C1IntHandler         = DefaultIntHandler    // 27: I2C1
#pragma weak I2C2IntHandler         = DefaultIntHandler    // 28: I2C2
#pragma weak SPIIntHandler          = DefaultIntHandler    // 29: SPI
#pragma weak SSP0IntHandler         = DefaultIntHandler    // 30: SSP0
#pragma weak SSP1IntHandler         = DefaultIntHandler    // 31: SSP1
#pragma weak PLL0IntHandler         = DefaultIntHandler    // 32: PLL0 Lock (Main PLL)
#pragma weak RTCIntHandler          = DefaultIntHandler    // 33: Real Time Clock
#pragma weak EINT0IntHandler        = DefaultIntHandler    // 34: External Interrupt 0
#pragma weak EINT1IntHandler        = DefaultIntHandler    // 35: External Interrupt 1
#pragma weak EINT2IntHandler        = DefaultIntHandler    // 36: External Interrupt 2
#pragma weak EINT3IntHandler        = DefaultIntHandler    // 37: External Interrupt 3
#pragma weak ADCIntHandler          = DefaultIntHandler    // 38: A/D Converter
#pragma weak BODIntHandler          = DefaultIntHandler    // 39: Brown-Out Detect
#pragma weak USBIntHandler          = DefaultIntHandler    // 40: USB
#pragma weak CANIntHandler          = DefaultIntHandler    // 41: CAN
#pragma weak DMAIntHandler          = DefaultIntHandler    // 42: General Purpose DMA
#pragma weak I2SIntHandler          = DefaultIntHandler    // 43: I2S
#pragma weak ENETIntHandler         = DefaultIntHandler    // 44: Ethernet

#if defined(LPC_175x) || defined (LPC_176x)
#pragma weak RITIntHandler          = DefaultIntHandler    // 45: Repetitive Interrupt Timer
#elif defined(LPC_177x) || defined (LPC_178x)
#pragma weak MCIIntHandler          = DefaultIntHandler    // 45: SD/MMC Card
#else
#error Please select your LPC MCU first!             \
       This value can be one of the following value: \
       LPC_175x or LPC_176x or LPC_177x or LPC_178x
#endif

#pragma weak MCPWMIntHandler        = DefaultIntHandler    // 46: Motor Control PWM
#pragma weak QEIIntHandler          = DefaultIntHandler    // 47: Quadrature Encoder Interface
#pragma weak PLL1IntHandler         = DefaultIntHandler    // 48: PLL1 Lock (USB PLL)
#pragma weak USBActivityIntHandler  = DefaultIntHandler    // 49: USB Activity
#pragma weak CANActivityIntHandler  = DefaultIntHandler    // 50: CAN Activity
#pragma weak UART4IntHandler        = DefaultIntHandler    // 51: UART4
#pragma weak SSP2IntHandler         = DefaultIntHandler    // 52: SSP2
#pragma weak LCDIntHandler          = DefaultIntHandler    // 53: LCD
#pragma weak GPIOIntHandler         = DefaultIntHandler    // 54: GPIO
#pragma weak PWM0IntHandler         = DefaultIntHandler    // 55: PWM0
#pragma weak EEPROMIntHandler       = DefaultIntHandler    // 56: EEPROM
//*****************************************************************************
//
//! \brief This is the code that gets called when the processor receives an
//! unexpected interrupt.
//!
//! \param None.
//!
//! This simply enters an infinite loop, preserving the system state for
//! examination by a debugger.
//!
//! \return None.
//*****************************************************************************
static void DefaultIntHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while (1)
    {
    }
}

