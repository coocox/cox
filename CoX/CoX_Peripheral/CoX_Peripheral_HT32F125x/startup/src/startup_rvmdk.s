;//*****************************************************************************
;//
;//! \file startup_rvmdk.s
;//! \brief HT32F125x Devices Startup code for MDK.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss
;//!           - Setup the microcontroller system. 			
;//!           - Call the application's entry point.
;//!           .
;//! \version V2.1.1.0
;//! \date 2/21/2012
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


Stack_Size      EQU     512

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
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
                DCD     MemManageIntHandler         ; Memory Management Fault Handler
                DCD     BusFaultIntHandler          ; Bus Fault Handler
                DCD     UsageFaultIntHandler        ; Usage Fault Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVCIntHandler               ; SVCall Handler
                DCD     DebugMonIntHandler          ; Debug Monitor Handler
                DCD     0                           ; Reserved
                DCD     PendSVIntHandler            ; PendSV Handler
                DCD     SysTickIntHandler           ; SysTick Handler

                                                    ; External Interrupts

                DCD     CKRDYIntHandler             ; Clock ready interrupt(HSE,HSI,LSE,LSI or PLL)
                DCD     LVDIntHandler               ; Low voltage detection interrupt
                DCD     BODIntHandler               ; Brownout low voltage detected interrupt
                DCD     WDTIntHandler               ; Watch Dog Timer interrupt
                DCD     RTCIntHandler               ; RTC global interrupt
                DCD     FMCIntHandler               ; FMC global interrupt
                DCD     EVWUPIntHandler             ; EXTI Event wakeup interrupt
                DCD     LPWUPIntHandler             ; WAKEUP pin interrupt
                DCD     EINT0IntHandler             ; EXTI Line 0 interrupt
                DCD     EINT1IntHandler             ; EXTI Line 1 interrupt
                DCD     EINT2IntHandler             ; EXTI Line 2 interrupt
                DCD     EINT3IntHandler             ; EXTI Line 3 interrupt
                DCD     EINT4IntHandler             ; EXTI Line 4 interrupt
                DCD     EINT5IntHandler             ; EXTI Line 5 interrupt
                DCD     EINT6IntHandler             ; EXTI Line 6 interrupt
                DCD     EINT7IntHandler             ; EXTI Line 7 interrupt
                DCD     EINT8IntHandler             ; EXTI Line 8 interrupt
                DCD     EINT9IntHandler             ; EXTI Line 9 interrupt
                DCD     EINT10IntHandler            ; EXTI Line 10 interrupt
                DCD     EINT11IntHandler            ; EXTI Line 11 interrupt
                DCD     EINT12IntHandler            ; EXTI Line 12 interrupt
                DCD     EINT13IntHandler            ; EXTI Line 13 interrupt
                DCD     EINT14IntHandler            ; EXTI Line 14 interrupt
                DCD     EINT15IntHandler            ; EXTI Line 15 interrupt
                DCD     COMPIntHandler              ; Comparator global interrupt
                DCD     ADCIntHandler               ; ADC interrupt
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     GTTM0IntHandler             ; GPTM0 global interrupt
                DCD     GTTM1IntHandler             ; GPTM1 global interrupt
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved
                DCD     I2C0IntHandler              ; I2C global interrupt
                DCD     DefaultIntHandler           ; Reserved
                DCD     SPI0IntHandler              ; SPI0 global interrupt
                DCD     DefaultIntHandler           ; Reserved
                DCD     UART0IntHandler             ; UART0 global interrupt

                

                
                
                
                AREA    |.text|, CODE, READONLY
                
                
                
; Reset Handler 
                
                ENTRY
                
ResetHandler    PROC
                EXPORT  ResetHandler                [WEAK]
                IMPORT  __main               

                LDR     R0, =__main
                BX      R0
                ENDP
                
                
; Dummy Exception Handlers (infinite loops which can be modified)
                
NMIIntHandler   PROC
                EXPORT  NMIIntHandler               [WEAK]
                B       .
                ENDP
HardFaultIntHandler\
                PROC
                EXPORT  HardFaultIntHandler         [WEAK]
                B       .
                ENDP
MemManageIntHandler\
                PROC
                EXPORT  MemManageIntHandler         [WEAK]
                B       .
                ENDP
BusFaultIntHandler\
                PROC
                EXPORT  BusFaultIntHandler          [WEAK]
                B       .
                ENDP
UsageFaultIntHandler\
                PROC
                EXPORT  UsageFaultIntHandler        [WEAK]
                B       .
                ENDP
DebugMonIntHandler\
                PROC
                EXPORT  DebugMonIntHandler          [WEAK]
                B       .
                ENDP
SVCIntHandler   PROC
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

                EXPORT CKRDYIntHandler           [WEAK]
                EXPORT LVDIntHandler             [WEAK]
                EXPORT BODIntHandler             [WEAK]
                EXPORT WDTIntHandler             [WEAK]
                EXPORT RTCIntHandler             [WEAK]
                EXPORT FMCIntHandler             [WEAK]
                EXPORT EVWUPIntHandler           [WEAK]
                EXPORT LPWUPIntHandler           [WEAK]
                EXPORT EINT0IntHandler           [WEAK]
                EXPORT EINT1IntHandler           [WEAK]
                EXPORT EINT2IntHandler           [WEAK]
                EXPORT EINT3IntHandler           [WEAK]
                EXPORT EINT4IntHandler           [WEAK]
                EXPORT EINT5IntHandler           [WEAK]
                EXPORT EINT6IntHandler           [WEAK]
                EXPORT EINT7IntHandler           [WEAK]
                EXPORT EINT8IntHandler           [WEAK]
                EXPORT EINT9IntHandler           [WEAK]
                EXPORT EINT10IntHandler          [WEAK]
                EXPORT EINT11IntHandler          [WEAK]
                EXPORT EINT12IntHandler          [WEAK]
                EXPORT EINT13IntHandler          [WEAK]
                EXPORT EINT14IntHandler          [WEAK]
                EXPORT EINT15IntHandler          [WEAK]
                EXPORT COMPIntHandler            [WEAK]
                EXPORT ADCIntHandler             [WEAK]
                EXPORT GTTM0IntHandler           [WEAK]
                EXPORT GTTM1IntHandler           [WEAK]
                EXPORT I2C0IntHandler            [WEAK]
                EXPORT SPI0IntHandler            [WEAK]
                EXPORT UART0IntHandler           [WEAK]

CKRDYIntHandler
LVDIntHandler
BODIntHandler
WDTIntHandler
RTCIntHandler
FMCIntHandler
EVWUPIntHandler
LPWUPIntHandler
EINT0IntHandler		   
EINT1IntHandler
EINT2IntHandler
EINT3IntHandler
EINT4IntHandler
EINT5IntHandler
EINT6IntHandler
EINT7IntHandler
EINT8IntHandler
EINT9IntHandler
EINT10IntHandler
EINT11IntHandler
EINT12IntHandler
EINT13IntHandler
EINT14IntHandler
EINT15IntHandler
COMPIntHandler
ADCIntHandler
GTTM0IntHandler
GTTM1IntHandler
I2C0IntHandler
SPI0IntHandler
UART0IntHandler
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