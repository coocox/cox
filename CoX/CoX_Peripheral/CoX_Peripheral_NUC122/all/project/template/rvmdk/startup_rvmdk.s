;//*****************************************************************************
;//
;//! \file startup_rvmdk.s
;//! \brief NUC122 Devices Startup code for MDK.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss
;//!           - Setup the microcontroller system. 			
;//!           - Call the application's entry point.
;//!           .
;//! \version 1.0
;//! \date 11/30/2011
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


Stack_Size      EQU     0x00000400

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

                ; External Interrupts
                                                    ; maximum of 32 External Interrupts are possible
                DCD     BODIntHandler               ; Brownout low voltage detected interrupt                 
                DCD     WDTIntHandler               ; Watch Dog Timer interrupt                              
                DCD     EINT0IntHandler             ; External signal interrupt from PB.14 pin                
                DCD     EINT1IntHandler             ; External signal interrupt from PB.15 pin                
                DCD     GPABIntHandler              ; External signal interrupt from PA[15:0] / PB[13:0]     
                DCD     GPCDIntHandler              ; External interrupt from PC[15:0]/PD[15:0]  
                DCD     PWMAIntHandler              ; PWM0 or PWM2 interrupt PWM1 or PWM3 interrupt 
                DCD     DefaultIntHandler           ; Reserved                                 
                DCD     TIMER0IntHandler            ; Timer 0 interrupt                                      
                DCD     TIMER1IntHandler            ; Timer 1 interrupt                                      
                DCD     TIMER2IntHandler            ; Timer 2 interrupt                                      
                DCD     TIMER3IntHandler            ; Timer 3 interrupt                                      
                DCD     UART0IntHandler             ; UART0 interrupt                                        
                DCD     UART1IntHandler             ; UART1 interrupt                                        
                DCD     SPI0IntHandler              ; SPI0 interrupt                                         
                DCD     SPI1IntHandler              ; SPI1 interrupt 
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved 
                DCD     DefaultIntHandler           ; Reserved                                         
                DCD     I2C0IntHandler              ; I2C interrupt
                DCD     DefaultIntHandler           ; Reserved
                DCD     DefaultIntHandler           ; Reserved 
                DCD     DefaultIntHandler           ; Reserved                                        
                DCD     USBDIntHandler              ; USB FS Device interrupt                                
                DCD     PS2IntHandler               ; PS2 interrupt
                DCD     DefaultIntHandler           ; Reserved 
                DCD     DefaultIntHandler           ; Reserved 
                DCD     DefaultIntHandler           ; Reserved                                          
                DCD     PWRWUIntHandler             ; Clock controller interrupt for chip wake up from power-down
                DCD     DefaultIntHandler           ; Reserved                                          
                DCD     DefaultIntHandler           ; Reserved
                DCD     RTCIntHandler               ; Real time clock interrupt 
                

                
                
                
                AREA    |.text|, CODE, READONLY
                
                
                
; Reset Handler 
                
                ENTRY
                
ResetHandler   PROC
                EXPORT  ResetHandler             [WEAK]
                IMPORT  __main
                
                LDR     R0, =0x50000100
                ; Unlock Register                
                LDR     R1, =0x59
                STR     R1, [R0]
                LDR     R1, =0x16
                STR     R1, [R0]
                LDR     R1, =0x88
                STR     R1, [R0]

                ; Init POR
                LDR     R2, =0x50000024
                LDR     R1, =0x00005AA5
                STR     R1, [R2]

                ; Lock register
                MOVS    R1, #0
                STR     R1, [R0]                
                
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

                EXPORT  BODIntHandler            [WEAK]
                EXPORT  WDTIntHandler            [WEAK]
                EXPORT  EINT0IntHandler          [WEAK]
                EXPORT  EINT1IntHandler          [WEAK]
                EXPORT  GPABIntHandler           [WEAK]
                EXPORT  GPCDIntHandler           [WEAK]
                EXPORT  PWMAIntHandler           [WEAK]
                EXPORT  TIMER0IntHandler         [WEAK]
                EXPORT  TIMER1IntHandler         [WEAK]
                EXPORT  TIMER2IntHandler         [WEAK]
                EXPORT  TIMER3IntHandler         [WEAK]
                EXPORT  UART0IntHandler          [WEAK]
                EXPORT  UART1IntHandler          [WEAK]
                EXPORT  SPI0IntHandler           [WEAK]
                EXPORT  SPI1IntHandler           [WEAK]
                EXPORT  I2C0IntHandler           [WEAK]
                EXPORT  USBDIntHandler           [WEAK]
                EXPORT  PS2IntHandler            [WEAK]
                EXPORT  PWRWUIntHandler          [WEAK]
                EXPORT  RTCIntHandler            [WEAK]
                
BODIntHandler
WDTIntHandler
EINT0IntHandler
EINT1IntHandler
GPABIntHandler
GPCDIntHandler
PWMAIntHandler
TIMER0IntHandler
TIMER1IntHandler
TIMER2IntHandler
TIMER3IntHandler
UART0IntHandler
UART1IntHandler
SPI0IntHandler
SPI1IntHandler
I2C0IntHandler
USBDIntHandler
PS2IntHandler
I2SIntHandler
PWRWUIntHandler
RTCIntHandler
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