;/*****************************************************************************
; * @file:    startup_LPC17nx.s
; * @purpose: CMSIS Cortex-M3 Core Device Startup File
; *           for the NXP LPC17xx Device Series
; * @note:    n can be 5/6/7/8
; *           You must define LPC MCU type in assembler of IAR,
; *           This value can be one of the following value
; *           - LPC_175x
; *           - LPC_176x
; *           - LPC_177x
; *           - LPC_178x
; * @version: V1.03
; * @date:    09. February 2010
; *----------------------------------------------------------------------------
; *
; * Copyright (C) 2010 ARM Limited. All rights reserved.
; *
; * ARM Limited (ARM) is supplying this software for use with Cortex-Mx
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

#define LPC_176x

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     ResetIntHandler

        DCD     NMIIntHandler
        DCD     HardFaultIntHandler
        DCD     MemManageIntHandler
        DCD     BusFaultIntHandler
        DCD     UsageFaultIntHandler
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVCIntHandler
        DCD     DebugMonIntHandler
        DCD     0
        DCD     PendSVIntHandler
        DCD     SysTickIntHandler

        ; External Interrupts
        DCD     WDTIntHandler            ; 16: Watchdog Timer
        DCD     TIMER0IntHandler         ; 17: Timer0
        DCD     TIMER1IntHandler         ; 18: Timer1
        DCD     TIMER2IntHandler         ; 19: Timer2
        DCD     TIMER3IntHandler         ; 20: Timer3
        DCD     UART0IntHandler          ; 21: UART0
        DCD     UART1IntHandler          ; 22: UART1
        DCD     UART2IntHandler          ; 23: UART2
        DCD     UART3IntHandler          ; 24: UART3
        DCD     PWM1IntHandler           ; 25: PWM1
        DCD     I2C0IntHandler           ; 26: I2C0
        DCD     I2C1IntHandler           ; 27: I2C1
        DCD     I2C2IntHandler           ; 28: I2C2
        DCD     SPIIntHandler            ; 29: SPI
        DCD     SSP0IntHandler           ; 30: SSP0
        DCD     SSP1IntHandler           ; 31: SSP1
        DCD     PLL0IntHandler           ; 32: PLL0 Lock (Main PLL)
        DCD     RTCIntHandler            ; 33: Real Time Clock
        DCD     EINT0IntHandler          ; 34: External Interrupt 0
        DCD     EINT1IntHandler          ; 35: External Interrupt 1
        DCD     EINT2IntHandler          ; 36: External Interrupt 2
        DCD     EINT3IntHandler          ; 37: External Interrupt 3
        DCD     ADCIntHandler            ; 38: A/D Converter
        DCD     BODIntHandler            ; 39: Brown-Out Detect
        DCD     USBIntHandler            ; 40: USB
        DCD     CANIntHandler            ; 41: CAN
        DCD     DMAIntHandler            ; 42: General Purpose DMA
        DCD     I2SIntHandler            ; 43: I2S
        DCD     ENETIntHandler           ; 44: Ethernet
#if defined(LPC_175x) || defined (LPC_176x)
                DCD     RITIntHandler            ; 45: Repetitive Interrupt Timer
#elif defined(LPC_177x) || defined (LPC_178x)
                DCD     MCIIntHandler            ; 45: SD/MMC card I/F
#else
#error Please select your LPC MCU first!             \
       This value can be one of the following value: \
       LPC_175x or LPC_176x or LPC_177x or LPC_178x
#endif
        DCD     MCPWMIntHandler          ; 46: Motor Control PWM
        DCD     QEIIntHandler            ; 47: Quadrature Encoder Interface
        DCD     PLL1IntHandler           ; 48: PLL1 Lock (USB PLL)
        DCD     USBActivityIntHandler    ; 49: USB Activity Interrupt
        DCD     CANActivityIntHandler    ; 50: CAN Activity Interrupt
        DCD     UART4IntHandler          ; 51: UART4
        DCD     SSP2IntHandler       ; 52: SSP2
        DCD     LCDIntHandler        ; 53: LCD
        DCD     GPIOIntHandler       ; 54: GPIO
        DCD     PWM0IntHandler       ; 55: PWM0
        DCD     EEPROMIntHandler     ; 56: EEPROM


__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU     __Vectors_End - __Vectors

                PUBLIC   CRP_Value
        RSEG     CRPKEY : CODE(2)
CRP_Value       
                DCD  0xFFFFFFFF
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK ResetIntHandler
        SECTION .text:CODE:REORDER(2)
ResetIntHandler
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMIIntHandler
        SECTION .text:CODE:REORDER(1)
NMIIntHandler
        B NMIIntHandler

        PUBWEAK HardFaultIntHandler
        SECTION .text:CODE:REORDER(1)
HardFaultIntHandler
        B HardFaultIntHandler

        PUBWEAK MemManageIntHandler
        SECTION .text:CODE:REORDER(1)
MemManageIntHandler
        B MemManageIntHandler

        PUBWEAK BusFaultIntHandler
        SECTION .text:CODE:REORDER(1)
BusFaultIntHandler
        B BusFaultIntHandler

        PUBWEAK UsageFaultIntHandler
        SECTION .text:CODE:REORDER(1)
UsageFaultIntHandler
        B UsageFaultIntHandler

        PUBWEAK SVCIntHandler
        SECTION .text:CODE:REORDER(1)
SVCIntHandler
        B SVCIntHandler

        PUBWEAK DebugMonIntHandler
        SECTION .text:CODE:REORDER(1)
DebugMonIntHandler
        B DebugMonIntHandler

        PUBWEAK PendSVIntHandler
        SECTION .text:CODE:REORDER(1)
PendSVIntHandler
        B PendSVIntHandler

        PUBWEAK SysTickIntHandler
        SECTION .text:CODE:REORDER(1)
SysTickIntHandler
        B SysTickIntHandler

        PUBWEAK WDTIntHandler
        SECTION .text:CODE:REORDER(1)
WDTIntHandler
        B WDTIntHandler

        PUBWEAK TIMER0IntHandler
        SECTION .text:CODE:REORDER(1)
TIMER0IntHandler
        B TIMER0IntHandler

        PUBWEAK TIMER1IntHandler
        SECTION .text:CODE:REORDER(1)
TIMER1IntHandler
        B TIMER1IntHandler

        PUBWEAK TIMER2IntHandler
        SECTION .text:CODE:REORDER(1)
TIMER2IntHandler
        B TIMER2IntHandler

        PUBWEAK TIMER3IntHandler
        SECTION .text:CODE:REORDER(1)
TIMER3IntHandler
        B TIMER3IntHandler

        PUBWEAK UART0IntHandler
        SECTION .text:CODE:REORDER(1)
UART0IntHandler
        B UART0IntHandler

        PUBWEAK UART1IntHandler
        SECTION .text:CODE:REORDER(1)
UART1IntHandler
        B UART1IntHandler

        PUBWEAK UART2IntHandler
        SECTION .text:CODE:REORDER(1)
UART2IntHandler
        B UART2IntHandler

        PUBWEAK UART3IntHandler
        SECTION .text:CODE:REORDER(1)
UART3IntHandler
        B UART3IntHandler

        PUBWEAK PWM1IntHandler
        SECTION .text:CODE:REORDER(1)
PWM1IntHandler
        B PWM1IntHandler

        PUBWEAK I2C0IntHandler
        SECTION .text:CODE:REORDER(1)
I2C0IntHandler
        B I2C0IntHandler

        PUBWEAK I2C1IntHandler
        SECTION .text:CODE:REORDER(1)
I2C1IntHandler
        B I2C1IntHandler

        PUBWEAK I2C2IntHandler
        SECTION .text:CODE:REORDER(1)
I2C2IntHandler
        B I2C2IntHandler

        PUBWEAK SPIIntHandler
        SECTION .text:CODE:REORDER(1)
SPIIntHandler
        B SPIIntHandler

        PUBWEAK SSP0IntHandler
        SECTION .text:CODE:REORDER(1)
SSP0IntHandler
        B SSP0IntHandler

        PUBWEAK SSP1IntHandler
        SECTION .text:CODE:REORDER(1)
SSP1IntHandler
        B SSP1IntHandler

        PUBWEAK PLL0IntHandler
        SECTION .text:CODE:REORDER(1)
PLL0IntHandler
        B PLL0IntHandler

        PUBWEAK RTCIntHandler
        SECTION .text:CODE:REORDER(1)
RTCIntHandler
        B RTCIntHandler

        PUBWEAK EINT0IntHandler
        SECTION .text:CODE:REORDER(1)
EINT0IntHandler
        B EINT0IntHandler

        PUBWEAK EINT1IntHandler
        SECTION .text:CODE:REORDER(1)
EINT1IntHandler
        B EINT1IntHandler

        PUBWEAK EINT2IntHandler
        SECTION .text:CODE:REORDER(1)
EINT2IntHandler
        B EINT2IntHandler

        PUBWEAK EINT3IntHandler
        SECTION .text:CODE:REORDER(1)
EINT3IntHandler
        B EINT3IntHandler

        PUBWEAK ADCIntHandler
        SECTION .text:CODE:REORDER(1)
ADCIntHandler
        B ADCIntHandler

        PUBWEAK BODIntHandler
        SECTION .text:CODE:REORDER(1)
BODIntHandler
        B BODIntHandler

        PUBWEAK USBIntHandler
        SECTION .text:CODE:REORDER(1)
USBIntHandler
        B USBIntHandler

        PUBWEAK CANIntHandler
        SECTION .text:CODE:REORDER(1)
CANIntHandler
        B CANIntHandler

        PUBWEAK DMAIntHandler
        SECTION .text:CODE:REORDER(1)
DMAIntHandler
        B DMAIntHandler

        PUBWEAK I2SIntHandler
        SECTION .text:CODE:REORDER(1)
I2SIntHandler
        B I2SIntHandler

        PUBWEAK ENETIntHandler
        SECTION .text:CODE:REORDER(1)
ENETIntHandler
        B ENETIntHandler
#if defined(LPC_175x) || defined (LPC_176x)
        PUBWEAK RITIntHandler
        SECTION .text:CODE:REORDER(1)
RITIntHandler
        B RITIntHandler
#elif defined(LPC_177x) || defined (LPC_178x)
        PUBWEAK MCIIntHandler
        SECTION .text:CODE:REORDER(1)
MCIIntHandler
        B MCIIntHandler
#else
#error Please select your LPC MCU first!             \
       This value can be one of the following value: \
       LPC_175x or LPC_176x or LPC_177x or LPC_178x
#endif


        PUBWEAK MCPWMIntHandler
        SECTION .text:CODE:REORDER(1)
MCPWMIntHandler
        B MCPWMIntHandler

        PUBWEAK QEIIntHandler
        SECTION .text:CODE:REORDER(1)
QEIIntHandler
        B QEIIntHandler

        PUBWEAK PLL1IntHandler
        SECTION .text:CODE:REORDER(1)
PLL1IntHandler
        B PLL1IntHandler

        PUBWEAK USBActivityIntHandler
        SECTION .text:CODE:REORDER(1)
USBActivityIntHandler
        B USBActivityIntHandler

        PUBWEAK CANActivityIntHandler
        SECTION .text:CODE:REORDER(1)
CANActivityIntHandler
        B CANActivityIntHandler

        PUBWEAK UART4IntHandler
        SECTION .text:CODE:REORDER(1)
UART4IntHandler
        B UART4IntHandler

        PUBWEAK SSP2IntHandler
        SECTION .text:CODE:REORDER(1)
SSP2IntHandler
        B SSP2IntHandler

        PUBWEAK LCDIntHandler
        SECTION .text:CODE:REORDER(1)
LCDIntHandler
        B LCDIntHandler

        PUBWEAK GPIOIntHandler
        SECTION .text:CODE:REORDER(1)
GPIOIntHandler
        B GPIOIntHandler

        PUBWEAK PWM0IntHandler
        SECTION .text:CODE:REORDER(1)
PWM0IntHandler
        B PWM0IntHandler

        PUBWEAK EEPROMIntHandler
        SECTION .text:CODE:REORDER(1)
EEPROMIntHandler
        B EEPROMIntHandler

        END

