;/*****************************************************************************
; * @file:    startup_rvmdk.s
; * @purpose: CMSIS Cortex-M3 Core Device Startup File
; *           for the NXP LPC17xx Device Series
; * @version: V1.03
; * @date:    09. February 2010
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2010 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M3
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; *****************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     ResetHandler             ; Reset Handler
                DCD     NMIHandler               ; NMI Handler
                DCD     HardFaultHandler         ; Hard Fault Handler
                DCD     MemManageHandler         ; MPU Fault Handler
                DCD     BusFaultHandler          ; Bus Fault Handler
                DCD     UsageFaultHandler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVCHandler               ; SVCall Handler
                DCD     DebugMonHandler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSVHandler            ; PendSV Handler
                DCD     SysTickHandler           ; SysTick Handler

                ; External Interrupts
                DCD     WDTIRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0IRQHandler         ; 17: Timer0
                DCD     TIMER1IRQHandler         ; 18: Timer1
                DCD     TIMER2IRQHandler         ; 19: Timer2
                DCD     TIMER3IRQHandler         ; 20: Timer3
                DCD     UART0IRQHandler          ; 21: UART0
                DCD     UART1IRQHandler          ; 22: UART1
                DCD     UART2IRQHandler          ; 23: UART2
                DCD     UART3IRQHandler          ; 24: UART3
                DCD     PWM1IRQHandler           ; 25: PWM1
                DCD     I2C0IRQHandler           ; 26: I2C0
                DCD     I2C1IRQHandler           ; 27: I2C1
                DCD     I2C2IRQHandler           ; 28: I2C2
                DCD     SPIIRQHandler            ; 29: SPI
                DCD     SSP0IRQHandler           ; 30: SSP0
                DCD     SSP1IRQHandler           ; 31: SSP1
                DCD     PLL0IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTCIRQHandler            ; 33: Real Time Clock
                DCD     EINT0IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3IRQHandler          ; 37: External Interrupt 3
                DCD     ADCIRQHandler            ; 38: A/D Converter
                DCD     BODIRQHandler            ; 39: Brown-Out Detect
                DCD     USBIRQHandler            ; 40: USB
                DCD     CANIRQHandler            ; 41: CAN
                DCD     DMAIRQHandler            ; 42: General Purpose DMA
                DCD     I2SIRQHandler            ; 43: I2S
                DCD     ENETIRQHandler           ; 44: Ethernet
                DCD     RITIRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWMIRQHandler          ; 46: Motor Control PWM
                DCD     QEIIRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD		USBActivityIRQHandler	  ; 49: USB Activity interrupt to wakeup
                DCD		CANActivityIRQHandler	  ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


                AREA    |.text|, CODE, READONLY


; Reset Handler

ResetHandler   PROC
                EXPORT  ResetHandler             [WEAK]
                IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMIHandler     PROC
                EXPORT  NMIHandler               [WEAK]
                B       .
                ENDP
HardFaultHandler\
                PROC
                EXPORT  HardFaultHandler         [WEAK]
                B       .
                ENDP
MemManageHandler\
                PROC
                EXPORT  MemManageHandler         [WEAK]
                B       .
                ENDP
BusFaultHandler\
                PROC
                EXPORT  BusFaultHandler          [WEAK]
                B       .
                ENDP
UsageFaultHandler\
                PROC
                EXPORT  UsageFaultHandler        [WEAK]
                B       .
                ENDP
SVCHandler     PROC
                EXPORT  SVCHandler               [WEAK]
                B       .
                ENDP
DebugMonHandler\
                PROC
                EXPORT  DebugMonHandler          [WEAK]
                B       .
                ENDP
PendSVHandler  PROC
                EXPORT  PendSVHandler            [WEAK]
                B       .
                ENDP
SysTickHandler PROC
                EXPORT  SysTickHandler           [WEAK]
                B       .
                ENDP

DefaultHandler PROC

                EXPORT  WDTIRQHandler            [WEAK]
                EXPORT  TIMER0IRQHandler         [WEAK]
                EXPORT  TIMER1IRQHandler         [WEAK]
                EXPORT  TIMER2IRQHandler         [WEAK]
                EXPORT  TIMER3IRQHandler         [WEAK]
                EXPORT  UART0IRQHandler          [WEAK]
                EXPORT  UART1IRQHandler          [WEAK]
                EXPORT  UART2IRQHandler          [WEAK]
                EXPORT  UART3IRQHandler          [WEAK]
                EXPORT  PWM1IRQHandler           [WEAK]
                EXPORT  I2C0IRQHandler           [WEAK]
                EXPORT  I2C1IRQHandler           [WEAK]
                EXPORT  I2C2IRQHandler           [WEAK]
                EXPORT  SPIIRQHandler            [WEAK]
                EXPORT  SSP0IRQHandler           [WEAK]
                EXPORT  SSP1IRQHandler           [WEAK]
                EXPORT  PLL0IRQHandler           [WEAK]
                EXPORT  RTCIRQHandler            [WEAK]
                EXPORT  EINT0IRQHandler          [WEAK]
                EXPORT  EINT1IRQHandler          [WEAK]
                EXPORT  EINT2IRQHandler          [WEAK]
                EXPORT  EINT3IRQHandler          [WEAK]
                EXPORT  ADCIRQHandler            [WEAK]
                EXPORT  BODIRQHandler            [WEAK]
                EXPORT  USBIRQHandler            [WEAK]
                EXPORT  CANIRQHandler            [WEAK]
                EXPORT  DMAIRQHandler            [WEAK]
                EXPORT  I2SIRQHandler            [WEAK]
                EXPORT  ENETIRQHandler           [WEAK]
                EXPORT  RITIRQHandler            [WEAK]
                EXPORT  MCPWMIRQHandler          [WEAK]
                EXPORT  QEIIRQHandler            [WEAK]
                EXPORT  PLL1IRQHandler           [WEAK]
                EXPORT  USBActivityIRQHandler	  [WEAK]
                EXPORT  CANActivityIRQHandler	  [WEAK]

WDTIRQHandler
TIMER0IRQHandler
TIMER1IRQHandler
TIMER2IRQHandler
TIMER3IRQHandler
UART0IRQHandler
UART1IRQHandler
UART2IRQHandler
UART3IRQHandler
PWM1IRQHandler
I2C0IRQHandler
I2C1IRQHandler
I2C2IRQHandler
SPIIRQHandler
SSP0IRQHandler
SSP1IRQHandler
PLL0IRQHandler
RTCIRQHandler
EINT0IRQHandler
EINT1IRQHandler
EINT2IRQHandler
EINT3IRQHandler
ADCIRQHandler
BODIRQHandler
USBIRQHandler
CANIRQHandler
DMAIRQHandler
I2SIRQHandler
ENETIRQHandler
RITIRQHandler
MCPWMIRQHandler
QEIIRQHandler
PLL1IRQHandler
USBActivityIRQHandler
CANActivityIRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
