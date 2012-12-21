;//*****************************************************************************
;//
;//! \file startup_rvmdk.c
;//! \brief Cortex-M0/M3 Devices Startup code for MDK.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss 			
;//!           - Call the application's entry point.
;//!           .
;//! \version V2.1.1.0
;//! \date 11/14/2011
;//! \author CooCox
;//! \copy
;//!
;//! Copyright (c)  2011, CooCox 
;//! All rights reserved.
;//! 
;//! Redistribution and use in source and binary forms, with or without 
;//! modification, are permitted provided that the following conditions 
;//! are met: 
;//! 
;//!     * Redistributions of source code must retain the above copyright 
;//! notice, this list of conditions and the following disclaimer. 
;//!     * Redistributions in binary form must reproduce the above copyright
;//! notice, this list of conditions and the following disclaimer in the
;//! documentation and/or other materials provided with the distribution. 
;//!     * Neither the name of the <ORGANIZATION> nor the names of its 
;//! contributors may be used to endorse or promote products derived 
;//! from this software without specific prior written permission. 
;//! 
;//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
;//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
;//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
;//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
;//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
;//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
;//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
;//! THE POSSIBILITY OF SUCH DAMAGE.
;//
;//*****************************************************************************

Stack_Size      EQU     0x00001000

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

__Vectors       DCD     __initial_sp                ; Top of Stack
                DCD     ResetHandler                ; Reset Handler
                DCD     NMIIntHandler               ; NMI Handler
                DCD     HardFaultIntHandler         ; Hard Fault Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVCIntHandler               ; SVCall Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     PendSVIntHandler            ; PendSV Handler
                DCD     SysTickIntHandler           ; SysTick Handler

                DCD     DMA0IntHandler              ; DMA channel 0 transfer complete and error handler
                DCD     DMA1IntHandler              ; DMA channel 1 transfer complete and error handler
                DCD     DMA2IntHandler              ; DMA channel 2 transfer complete and error handler
                DCD     DMA3IntHandler              ; DMA channel 3 transfer complete and error handler
                DCD     0                           ; Reserved
                DCD     FTFAIntHandler              ; Command complete and read collision
                DCD     LVDIntHandler               ; Low-voltage detect, low-voltage warning
                DCD     LLWUIntHandler              ; Low Leakage Wakeup
                DCD     I2C0IntHandler              ; I2C0 handler
                DCD     I2C1IntHandler              ; I2C1 handler
                DCD     SPI0IntHandler              ; SPI0 handler
                DCD     SPI1IntHandler              ; SPI1 handler
                DCD     UART0SEIntHandler           ; UART0SE handler
                DCD     UART1SEIntHandler           ; UART1SE handler
                DCD     UART2SEIntHandler           ; UART2SE handler
                DCD     ADCIntHandler               ; ADC handler
                DCD     ACMPIntHandler              ; ACMP handler
                DCD     FTM0IntHandler              ; FTM0 handler
                DCD     FTM1IntHandler              ; FTM1 handler
                DCD     FTM2IntHandler              ; FTM2 handler
                DCD     RTCAIntHandler              ; RTCA handler
                DCD     RTCSIntHandler              ; RTCS handler
                DCD     PITIntHandler               ; PIT handler
                DCD     0                           ; Reserved
                DCD     USBOTGIntHandler            ; USBOTG handler
                DCD     DACIntHandler               ; DAC handler
                DCD     TSIIntHandler               ; TSI handler
                DCD     MCGIntHandler               ; MCG handler
                DCD     LPTMRIntHandler             ; PIT handler
                DCD     0                           ; Reserved 
                DCD     PORTAIntHandler             ; PORTA handler
                DCD     PORTDIntHandler             ; PORTD handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0xffffffff                  ; CONFIG_1
                DCD     0xffffffff                  ; CONFIG_2
                DCD     0xffffffff                  ; CONFIG_3
                DCD     0xfffffffe                  ; CONFIG_4
                     
                AREA    |.text|, CODE, READONLY
                
                
                
; Reset Handler 
                
                ENTRY
                
ResetHandler   PROC
                EXPORT  ResetHandler             [WEAK]
                IMPORT  __main              

                LDR     R0, =__main
                BX      R0
                ENDP
                
                
; Dummy Exception Handlers (infinite loops which can be modified)                
                
NMIIntHandler     PROC
                EXPORT  NMIIntHandler               [WEAK]
                B       .
                ENDP
HardFaultIntHandler\
                PROC
                EXPORT  HardFaultIntHandler         [WEAK]
                B       .
                ENDP
SVCIntHandler     PROC
                EXPORT  SVCIntHandler               [WEAK]
                B       .
                ENDP
PendSVIntHandler  PROC
                EXPORT  PendSVIntHandler            [WEAK]
                B       .
                ENDP
SysTickIntHandler PROC
                EXPORT  SysTickIntHandler           [WEAK]
                B       .
                ENDP

DefaultIntHandler PROC
                EXPORT  DMA0IntHandler           [WEAK]
                EXPORT  DMA1IntHandler           [WEAK]
                EXPORT  DMA2IntHandler           [WEAK]
                EXPORT  DMA3IntHandler           [WEAK]
                EXPORT  FTFAIntHandler           [WEAK]
                EXPORT  LVDIntHandler            [WEAK]
                EXPORT  LLWUIntHandler           [WEAK]
                EXPORT  I2C0IntHandler           [WEAK]
                EXPORT  I2C1IntHandler           [WEAK]
                EXPORT  SPI0IntHandler           [WEAK]
                EXPORT  SPI1IntHandler           [WEAK]
                EXPORT  UART0SEIntHandler        [WEAK]
                EXPORT  UART1SEIntHandler        [WEAK]
                EXPORT  UART2SEIntHandler        [WEAK]
                EXPORT  ADCIntHandler            [WEAK]
                EXPORT  ACMPIntHandler           [WEAK]
                EXPORT  FTM0IntHandler           [WEAK]
                EXPORT  FTM1IntHandler           [WEAK]
                EXPORT  FTM2IntHandler           [WEAK]
                EXPORT  RTCAIntHandler           [WEAK]
                EXPORT  RTCSIntHandler           [WEAK]
                EXPORT  PITIntHandler            [WEAK] 
                EXPORT  USBOTGIntHandler         [WEAK]
                EXPORT  DACIntHandler            [WEAK]
                EXPORT  TSIIntHandler            [WEAK]
                EXPORT  MCGIntHandler            [WEAK]
                EXPORT  LPTMRIntHandler          [WEAK]
                EXPORT  PORTAIntHandler          [WEAK]
                EXPORT  PORTDIntHandler          [WEAK]

DMA0IntHandler
DMA1IntHandler
DMA2IntHandler
DMA3IntHandler
FTFAIntHandler
LVDIntHandler
LLWUIntHandler
I2C0IntHandler
I2C1IntHandler
SPI0IntHandler
SPI1IntHandler
UART0SEIntHandler
UART1SEIntHandler
UART2SEIntHandler
ADCIntHandler
ACMPIntHandler
FTM0IntHandler
FTM1IntHandler
FTM2IntHandler
RTCAIntHandler
RTCSIntHandler
PITIntHandler
USBOTGIntHandler
DACIntHandler
TSIIntHandler
MCGIntHandler
LPTMRIntHandler
PORTAIntHandler
PORTDIntHandler
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
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
