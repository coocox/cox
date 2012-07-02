;//*****************************************************************************
;//
;//! \file startup_rvmdk.c
;//! \brief STM32F1xx Devices Startup code for MDK.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss
;//!           - Setup the microcontroller system. 			
;//!           - Call the application's entry point.
;//!           .
;//! \version V2.1.1.1
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

Stack_Size      EQU     0x00000400

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
                DCD     MemManageIntHandler         ; The hard fault handler
                DCD     BusFaultIntHandler          ; The bus fault handler
                DCD     UsageFaultIntHandler        ; The usage fault handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVCIntHandler               ; SVCall Handler
                DCD     DebugMonIntHandler          ; Debug monitor handler
                DCD     0                           ; Reserved
                DCD     PendSVIntHandler            ; PendSV Handler
                DCD     SysTickIntHandler           ; SysTick Handler

                ; External Interrupts
                DCD     WWDGIntHandler              ; 0 Window Watchdog interrupt                 
                DCD     PVDIntHandler               ; 1 PVD through EXTI Line detection  
                DCD     TAMPERIntHandler            ; 2 Tamper interrupt 
                DCD     RTCIntHandler               ; 3 RTC global interrupt
                DCD     FLASHIntHandler             ; 4 Flash global interrupt
                DCD     RCCIntHandler               ; 5 RCC global interrupt
                DCD     EXTI0IntHandler             ; 6 EXTI Line0 interrupt
                DCD     EXTI1IntHandler             ; 7 EXTI Line1 interrupt 
                DCD     EXTI2IntHandler             ; 8 EXTI Line2 interrupt
                DCD     EXTI3IntHandler             ; 9 EXTI Line3 interrupt
                DCD     EXTI4IntHandler             ; 10 EXTI Line4 interrupt
                DCD     DMA1Channel1IntHandler      ; 11 DMA1 Channel1 global interrupt
                DCD     DMA1Channel2IntHandler      ; 12 DMA1 Channel2 global interrupt
                DCD     DMA1Channel3IntHandler      ; 13 DMA1 Channel3 global interrupt
                DCD     DMA1Channel4IntHandler      ; 14 DMA1 Channel4 global interrupt
                DCD     DMA1Channel5IntHandler      ; 15 DMA1 Channel5 global interrupt
                DCD     DMA1Channel6IntHandler      ; 16 DMA1 Channel6 global interrupt
                DCD     DMA1Channel7IntHandler      ; 17 DMA1 Channel7 global interrupt
                DCD     ADC12IntHandler             ; 18 ADC1 and ADC2 global interrupt
                DCD     CAN1TXIntHandler            ; 19 CAN1 TX interrupts
                DCD     CAN1RX0IntHandler           ; 20 CAN1 RX0 interrupts
                DCD     CAN1RX1IntHandler           ; 21 CAN1 RX1 interrupt
                DCD     CAN1SCEIntHandler           ; 22 CAN1 SCE interrupt 
                DCD     EXTI95IntHandler            ; 23 EXTI Line[9:5] interrupts 
                DCD     TIM1BRKTIM9IntHandler       ; 24 TIM1 Break and IIM9 global interrupt
                DCD     TIM1UPTIM10IntHandler       ; 25 TIM1 Update and TIM10 global interrupt
                DCD     TIM1TRGCOMTIM11IntHandler   ; 26 TIM1 Trigger and Commutation and TIM11 global interrupt
                DCD     TIM1CCIntHandler            ; 27 TIM1 Capture Compare interrupt
                DCD     TIM2IntHandler              ; 28 TIM2 global interrupt
                DCD     TIM3IntHandler              ; 29 TIM3 global interrupt
                DCD     TIM4IntHandler              ; 30 TIM4 global interrupt
                DCD     I2C1EVIntHandler            ; 31 I2C1 event interrupt
                DCD     I2C1ERIntHandler            ; 32 I2C1 error interrupt
                DCD     I2C2EVIntHandler            ; 33 I2C2 event interrupt
                DCD     I2C2ERIntHandler            ; 34 I2C2 error interrupt
                DCD     SPI1IntHandler              ; 35 SPI1 global interrupt
                DCD     SPI2IntHandler              ; 36 SPI2 global interrupt
                DCD     USART1IntHandler            ; 37 USART1 global interrupt
                DCD     USART2IntHandler            ; 38 USART2 global interrupt
                DCD     USART3IntHandler            ; 39 USART3 global interrupt
                DCD     EXTI1510IntHandler          ; 40 EXTI Line[15:10] interrupts
                DCD     RTCAlarmIntHandler          ; 41 RTC alarm through EXTI line
                DCD     OTGFSWKUPIntHandler         ; 42 USB On-The-Go FS Wakeup
                DCD     TIM8BRKTIM12IntHandler      ; 43 TIM8 Break and TIM12 global interrupt
                DCD     TIM8UPTIM13IntHandler       ; 44 TIM8 Update interrupt and TIM13 global interrupt
                DCD     TIM8TRGCOMTIM14IntHandler   ; 45 TIM8 Trigger and Commutation and TIM14 global interrupt
                DCD     TIM8CCIntHandler            ; 46 TIM8 Capture Compare interrupt
                DCD     ADC3IntHandler              ; 47 ADC3 global interrupt
                DCD     FSMCIntHandler              ; 48 FSMC global interrupt
                DCD     SDIOIntHandler              ; 49 SDIO global interrupt
                DCD     TIM5IntHandler              ; 50 TIM5 global interrupt
                DCD     SPI3IntHandler              ; 51 SPI3 global interrupt
                DCD     UART4IntHandler             ; 52 UART4 global interrupt
                DCD     UART5IntHandler             ; 53 UART5 global interrupt
                DCD     TIM6IntHandler              ; 54 TIM6 global interrupt
                DCD     TIM7IntHandler              ; 55 TIM7 global interrupt
                DCD     DMA2Channel1IntHandler      ; 56 DMA2 Channel1 global interrupt
                DCD     DMA2Channel2IntHandler      ; 57 DMA2 Channel2 global interrupt
                DCD     DMA2Channel3IntHandler      ; 58 DMA2 Channel3 global interrupt
                DCD     DMA2Channel4IntHandler      ; 59 DMA2 Channel4 global interrupt
                DCD     DMA2Channel5IntHandler      ; 60 DMA2 Channel5 global interrupt
                DCD     ETHIntHandler               ; 61 Ethernet global interrupt
                DCD     ETHWKUPIntHandler           ; 62 Ethernet Wakeup through EXTI line
                DCD     CAN2TXIntHandler            ; 63 CAN2 TX interrupts
                DCD     CAN2RX0IntHandler           ; 64 CAN2 RX0 interrupts
                DCD     CAN2RX1IntHandler           ; 65 CAN2 RX1 interrupt
                DCD     CAN2SCEIntHandler           ; 66 CAN2 SCE interrupt
                DCD     OTGFSIntHandler             ; 67 USB On The Go FS global interrupt
                DCD     0xF108F85F                  ; Boot in RAM mode                     
        

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
                
NMIIntHandler PROC
                EXPORT NMIIntHandler [WEAK]
                B .
                ENDP
HardFaultIntHandler\
                PROC
                EXPORT HardFaultIntHandler [WEAK]
                B .
                ENDP
MemManageIntHandler\
                PROC
                EXPORT MemManageIntHandler [WEAK]
                B .
                ENDP
BusFaultIntHandler\
                PROC
                EXPORT BusFaultIntHandler [WEAK]
                B .
                ENDP
UsageFaultIntHandler\
                PROC
                EXPORT UsageFaultIntHandler [WEAK]
                B .
                ENDP
DebugMonIntHandler\
                PROC
                EXPORT DebugMonIntHandler [WEAK]
                B .
                ENDP
SVCIntHandler PROC
                EXPORT SVCIntHandler [WEAK]
                B .
                ENDP
PendSVIntHandler PROC
                EXPORT PendSVIntHandler [WEAK]
                B .
                ENDP
SysTickIntHandler PROC
                EXPORT SysTickIntHandler [WEAK]
                B .
                ENDP

DefaultIntHandler PROC

                EXPORT WWDGIntHandler            [WEAK]
                EXPORT PVDIntHandler             [WEAK] 
                EXPORT TAMPERIntHandler          [WEAK]      
                EXPORT RTCIntHandler             [WEAK]
                EXPORT FLASHIntHandler           [WEAK]
                EXPORT RCCIntHandler             [WEAK]
                EXPORT EXTI0IntHandler           [WEAK]
                EXPORT EXTI1IntHandler           [WEAK]
                EXPORT EXTI2IntHandler           [WEAK]
                EXPORT EXTI3IntHandler           [WEAK]
                EXPORT EXTI4IntHandler           [WEAK]
                EXPORT DMA1Channel1IntHandler    [WEAK]
                EXPORT DMA1Channel2IntHandler    [WEAK]
                EXPORT DMA1Channel3IntHandler    [WEAK]
                EXPORT DMA1Channel4IntHandler    [WEAK]
                EXPORT DMA1Channel5IntHandler    [WEAK]
                EXPORT DMA1Channel6IntHandler    [WEAK]
                EXPORT DMA1Channel7IntHandler    [WEAK]
                EXPORT ADC12IntHandler           [WEAK] 
                EXPORT CAN1TXIntHandler          [WEAK] 
                EXPORT CAN1RX0IntHandler         [WEAK]
                EXPORT CAN1RX1IntHandler         [WEAK]
                EXPORT CAN1SCEIntHandler         [WEAK]
                EXPORT EXTI95IntHandler          [WEAK]
                EXPORT TIM1BRKTIM9IntHandler     [WEAK]
                EXPORT TIM1UPTIM10IntHandler     [WEAK]
                EXPORT TIM1TRGCOMTIM11IntHandler [WEAK]
                EXPORT TIM1CCIntHandler          [WEAK]
                EXPORT TIM2IntHandler            [WEAK]
                EXPORT TIM3IntHandler            [WEAK]
                EXPORT TIM4IntHandler            [WEAK]
                EXPORT I2C1EVIntHandler          [WEAK]
                EXPORT I2C1ERIntHandler          [WEAK]
                EXPORT I2C2EVIntHandler          [WEAK]
                EXPORT I2C2ERIntHandler          [WEAK]
                EXPORT SPI1IntHandler            [WEAK]
                EXPORT SPI2IntHandler            [WEAK]
                EXPORT USART1IntHandler          [WEAK]
                EXPORT USART2IntHandler          [WEAK]
                EXPORT USART3IntHandler          [WEAK]
                EXPORT EXTI1510IntHandler        [WEAK]
                EXPORT RTCAlarmIntHandler        [WEAK]
                EXPORT OTGFSWKUPIntHandler       [WEAK]
                EXPORT TIM8BRKTIM12IntHandler    [WEAK]
                EXPORT TIM8UPTIM13IntHandler     [WEAK]
                EXPORT TIM8TRGCOMTIM14IntHandler [WEAK]
                EXPORT TIM8CCIntHandler          [WEAK]
                EXPORT ADC3IntHandler            [WEAK]
                EXPORT FSMCIntHandler            [WEAK]
                EXPORT SDIOIntHandler            [WEAK]
                EXPORT TIM5IntHandler            [WEAK]
                EXPORT SPI3IntHandler            [WEAK]
                EXPORT UART4IntHandler           [WEAK]
                EXPORT UART5IntHandler           [WEAK]
                EXPORT TIM6IntHandler            [WEAK]
                EXPORT TIM7IntHandler            [WEAK]
                EXPORT DMA2Channel1IntHandler    [WEAK]
                EXPORT DMA2Channel2IntHandler    [WEAK]
                EXPORT DMA2Channel3IntHandler    [WEAK]
                EXPORT DMA2Channel4IntHandler    [WEAK]
                EXPORT DMA2Channel5IntHandler    [WEAK]
                EXPORT ETHIntHandler             [WEAK]
                EXPORT ETHWKUPIntHandler         [WEAK]
                EXPORT CAN2TXIntHandler          [WEAK]
                EXPORT CAN2RX0IntHandler         [WEAK]
                EXPORT CAN2RX1IntHandler         [WEAK]
                EXPORT CAN2SCEIntHandler         [WEAK]
                EXPORT OTGFSIntHandler           [WEAK]

WWDGIntHandler
PVDIntHandler 
TAMPERIntHandler
RTCIntHandler
FLASHIntHandler
RCCIntHandler
EXTI0IntHandler
EXTI1IntHandler
EXTI2IntHandler
EXTI3IntHandler
EXTI4IntHandler
DMA1Channel1IntHandler
DMA1Channel2IntHandler
DMA1Channel3IntHandler
DMA1Channel4IntHandler
DMA1Channel5IntHandler
DMA1Channel6IntHandler
DMA1Channel7IntHandler
ADC12IntHandler 
CAN1TXIntHandler 
CAN1RX0IntHandler
CAN1RX1IntHandler
CAN1SCEIntHandler
EXTI95IntHandler
TIM1BRKTIM9IntHandler
TIM1UPTIM10IntHandler
TIM1TRGCOMTIM11IntHandler
TIM1CCIntHandler
TIM2IntHandler
TIM3IntHandler
TIM4IntHandler
I2C1EVIntHandler
I2C1ERIntHandler
I2C2EVIntHandler
I2C2ERIntHandler
SPI1IntHandler
SPI2IntHandler
USART1IntHandler
USART2IntHandler
USART3IntHandler
EXTI1510IntHandler
RTCAlarmIntHandler
OTGFSWKUPIntHandler
TIM8BRKTIM12IntHandler
TIM8UPTIM13IntHandler
TIM8TRGCOMTIM14IntHandler
TIM8CCIntHandler
ADC3IntHandler
FSMCIntHandler
SDIOIntHandler
TIM5IntHandler
SPI3IntHandler
UART4IntHandler
UART5IntHandler
TIM6IntHandler
TIM7IntHandler
DMA2Channel1IntHandler
DMA2Channel2IntHandler
DMA2Channel3IntHandler
DMA2Channel4IntHandler
DMA2Channel5IntHandler
ETHIntHandler
ETHWKUPIntHandler
CAN2TXIntHandler
CAN2RX0IntHandler
CAN2RX1IntHandler
CAN2SCEIntHandler
OTGFSIntHandler
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
