#include "test.h"

#define _PORTC_PCR3             (0x4004B00C)
#define _PORTC_PCR4             (0x4004B010)

#define UART_DIV                16UL
#define UART_BAUD               115200UL


//*****************************************************************************
//
//! \brief Init uart to print.
//!
//! \param None
//!
//! \details uart config as (115200, 8 data bit, 1 stop bit , no partiy)
//!
//! \return None.
//
//*****************************************************************************
unsigned long tmp = 0;

void 
TestIOInit(void)
{
    unsigned long ulBaud     = 0;
    unsigned long ulTmpReg   = 0;
    unsigned long ulBusClock = 0;

    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    //
    // Get Bus Clock
    //
    ulBusClock = SysCtlBusClkGet();

    //
    // Enable GPIO/UART Clock
    //
    
    xHWREG(SIM_SCGC5) |= SIM_SCGC5_PORTC_EN;    
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART1_EN;
    

    

    //
    // Remap UART pin to GPIO Port
    //
    
    // UART1_RX --> PC3
    ulTmpReg = xHWREG(_PORTC_PCR3);
    ulTmpReg &= ~(PORT_PCR_PIN_MUX_M);
    ulTmpReg |= PORT_PCR_PIN_ALT3;
    xHWREG(_PORTC_PCR3) = ulTmpReg;

    
    

    // UART1_TX --> PC4
    ulTmpReg = xHWREG(_PORTC_PCR4);
    ulTmpReg &= ~(PORT_PCR_PIN_MUX_M);
    ulTmpReg |= PORT_PCR_PIN_ALT3;
    xHWREG(_PORTC_PCR4) = ulTmpReg;

   
    
    //
    // Disable UART Receive/Transmit
    //
    xHWREGB(UART1_BASE + UART_012_C2) &= (unsigned char)(~UART_012_C2_TE_MASK);
    xHWREGB(UART1_BASE + UART_012_C2) &= (unsigned char)(~UART_012_C2_RE_MASK);

    //
    // Configure UART1 to 8-N-1
    // Set register to default value
    xHWREGB(UART1_BASE + UART_012_C1) = (unsigned char)(0x00);

    //
    // Configure UART Baud 115200
    //
    ulBaud = ulBusClock/(UART_DIV*UART_BAUD);

    xHWREGB(UART1_BASE + UART_012_BDH) &= (unsigned char)(~UART_012_BDH_SBR_MASK);
    xHWREGB(UART1_BASE + UART_012_BDH) |= 
                        (unsigned char)((ulBaud >> 8) & UART_012_BDH_SBR_MASK);

    xHWREGB(UART1_BASE + UART_012_BDL) = (unsigned char)(ulBaud);
 
    tmp = xHWREGB(UART1_BASE + UART_012_BDH);
    tmp = xHWREGB(UART1_BASE + UART_012_BDL);
    
    //
    // Enable UART Receive/Transmit
    //
    xHWREGB(UART1_BASE + UART_012_C2) |= (unsigned char)(UART_012_C2_TE_MASK);
    xHWREGB(UART1_BASE + UART_012_C2) |= (unsigned char)(UART_012_C2_RE_MASK);

}

//*****************************************************************************
//
//! \brief print a char.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
TestIOPut(char ch)
{
    volatile unsigned char ulStatus = 0;

    //
    // Wait until transmit register availavle
    //
    do
    {
        ulStatus = xHWREGB(UART1_BASE + UART_012_S1) &
                   ((unsigned char) UART_012_S1_TDRE_MASK);
    }while(0 == ulStatus);

    //
    // Send the char
    //
    xHWREGB(UART1_BASE + UART_012_D) = ch;

}

//*****************************************************************************
//
//! \brief Enable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestEnableIRQ(void)
{
    xCPUcpsie();
}

//*****************************************************************************
//
//! \brief Disable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestDisableIRQ(void)
{
    xCPUcpsid();
}

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.(COX)
//
//*****************************************************************************
#ifdef xDEBUG
void
__xerror__(char *pcFilename, unsigned long ulLine)
{
    while(1);
}
#endif

