;//*****************************************************************************
;//
;//! \file startup_rvmdk.c
;//! \brief TI Stellaris(LM3S) Devices Startup code for MDK.
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
                DCD     MemFaultIntHandler          ; The MPU fault handler
                DCD     BusFaultIntHandler          ; The bus fault handler
                DCD     UsageFaultIntHandler        ; The usage fault handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVCIntHandler               ; SVCall Handler
                DCD     DebugMonitorIntHandler      ; Debug monitor handler
                DCD     0                           ; Reserved
                DCD     PendSVIntHandler            ; PendSV Handler
                DCD     SysTickIntHandler           ; SysTick Handler

                                                    ; External Interrupts
                DCD     GPIOAIntHandler             ; GPIO Port A
                DCD     GPIOBIntHandler             ; GPIO Port B
                DCD     GPIOCIntHandler             ; GPIO Port C
                DCD     GPIODIntHandler             ; GPIO Port D
                DCD     GPIOEIntHandler             ; GPIO Port E
                DCD     UART0IntHandler             ; UART0 Rx and Tx
                DCD     UART1IntHandler             ; UART1 Rx and Tx
                DCD     SSI0IntHandler              ; SSI0 Rx and Tx
                DCD     I2C0IntHandler              ; I2C0 Master and Slave
                DCD     PWMFaultIntHandler          ; PWM Fault
                DCD     PWM0IntHandler              ; PWM Generator 0
                DCD     PWM1IntHandler              ; PWM Generator 1
                DCD     PWM2IntHandler              ; PWM Generator 2
                DCD     QEI0IntHandler              ; Quadrature Encoder 0
                DCD     ADC0Seq0IntHandler          ; ADC Sequence 0
                DCD     ADC0Seq1IntHandler          ; ADC Sequence 1
                DCD     ADC0Seq2IntHandler          ; ADC Sequence 2
                DCD     ADC0Seq3IntHandler          ; ADC Sequence 3
                DCD     WDTIntHandler               ; Watchdog timer
                DCD     TIMER0AIntHandler           ; Timer 0 subtimer A
                DCD     TIMER0BIntHandler           ; Timer 0 subtimer B
                DCD     TIMER1AIntHandler           ; Timer 1 subtimer A
                DCD     TIMER1BIntHandler           ; Timer 1 subtimer B
                DCD     TIMER2AIntHandler           ; Timer 2 subtimer A
                DCD     TIMER2BIntHandler           ; Timer 2 subtimer B
                DCD     ACMP0IntHandler             ; Analog Comparator 0
                DCD     ACMP1IntHandler             ; Analog Comparator 1
                DCD     ACMP2IntHandler             ; Analog Comparator 2
                DCD     SysCtlIntHandler            ; System Control (PLL, OSC, BO)
                DCD     FMCIntHandler               ; FLASH Control
                DCD     GPIOFIntHandler             ; GPIO Port F
                DCD     GPIOGIntHandler             ; GPIO Port G
                DCD     GPIOHIntHandler             ; GPIO Port H
                DCD     UART2IntHandler             ; UART2 Rx and Tx
                DCD     SSI1IntHandler              ; SSI1 Rx and Tx
                DCD     TIMER3AIntHandler           ; Timer 3 subtimer A
                DCD     TIMER3BIntHandler           ; Timer 3 subtimer B
                DCD     I2C1IntHandler              ; I2C1 Master and Slave
                DCD     QEI1IntHandler              ; Quadrature Encoder 1
                DCD     CAN0IntHandler              ; CAN0
                DCD     CAN1IntHandler              ; CAN1
                DCD     CAN2IntHandler              ; CAN2
                DCD     EthernetIntHandler          ; Ethernet
                DCD     HibernateIntHandler         ; Hibernate
                DCD     USB0IntHandler              ; USB0
                DCD     PWM3IntHandler              ; PWM Generator 3
                DCD     uDMAIntHandler              ; uDMA Software Transfer
                DCD     uDMAErrorIntHandler         ; uDMA Error
                DCD     ADC1Seq0IntHandler          ; ADC1 Sequence 0
                DCD     ADC1Seq1IntHandler          ; ADC1 Sequence 1
                DCD     ADC1Seq2IntHandler          ; ADC1 Sequence 2
                DCD     ADC1Seq3IntHandler          ; ADC1 Sequence 3
                DCD     I2S0IntHandler              ; I2S0
                DCD     EBI0IntHandler              ; External Bus Interface 0
                DCD     GPIOJIntHandler             ; GPIO Port J                     
                
                
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
MemFaultIntHandler\
                PROC
                EXPORT  MemFaultIntHandler          [WEAK]
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
SVCIntHandler     PROC
                EXPORT  SVCIntHandler               [WEAK]
                B       .
                ENDP
DebugMonitorIntHandler\
                PROC
                EXPORT  DebugMonitorIntHandler      [WEAK]
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

                EXPORT  GPIOAIntHandler           [WEAK]             
                EXPORT  GPIOBIntHandler           [WEAK]             
                EXPORT  GPIOCIntHandler           [WEAK]             
                EXPORT  GPIODIntHandler           [WEAK]             
                EXPORT  GPIOEIntHandler           [WEAK]             
                EXPORT  UART0IntHandler           [WEAK]             
                EXPORT  UART1IntHandler           [WEAK]             
                EXPORT  SSI0IntHandler            [WEAK]              
                EXPORT  I2C0IntHandler            [WEAK]              
                EXPORT  PWMFaultIntHandler        [WEAK]          
                EXPORT  PWM0IntHandler            [WEAK]              
                EXPORT  PWM1IntHandler            [WEAK]              
                EXPORT  PWM2IntHandler            [WEAK]              
                EXPORT  QEI0IntHandler            [WEAK]              
                EXPORT  ADC0Seq0IntHandler        [WEAK]          
                EXPORT  ADC0Seq1IntHandler        [WEAK]          
                EXPORT  ADC0Seq2IntHandler        [WEAK]          
                EXPORT  ADC0Seq3IntHandler        [WEAK]          
                EXPORT  WDTIntHandler             [WEAK]               
                EXPORT  TIMER0AIntHandler         [WEAK]           
                EXPORT  TIMER0BIntHandler         [WEAK]           
                EXPORT  TIMER1AIntHandler         [WEAK]           
                EXPORT  TIMER1BIntHandler         [WEAK]           
                EXPORT  TIMER2AIntHandler         [WEAK]           
                EXPORT  TIMER2BIntHandler         [WEAK]           
                EXPORT  ACMP0IntHandler           [WEAK]             
                EXPORT  ACMP1IntHandler           [WEAK]             
                EXPORT  ACMP2IntHandler           [WEAK]             
                EXPORT  SysCtlIntHandler          [WEAK]            
                EXPORT  FMCIntHandler             [WEAK]               
                EXPORT  GPIOFIntHandler           [WEAK]             
                EXPORT  GPIOGIntHandler           [WEAK]             
                EXPORT  GPIOHIntHandler           [WEAK]             
                EXPORT  UART2IntHandler           [WEAK]             
                EXPORT  SSI1IntHandler            [WEAK]              
                EXPORT  TIMER3AIntHandler         [WEAK]           
                EXPORT  TIMER3BIntHandler         [WEAK]           
                EXPORT  I2C1IntHandler            [WEAK]              
                EXPORT  QEI1IntHandler            [WEAK]              
                EXPORT  CAN0IntHandler            [WEAK]              
                EXPORT  CAN1IntHandler            [WEAK]              
                EXPORT  CAN2IntHandler            [WEAK]              
                EXPORT  EthernetIntHandler        [WEAK]          
                EXPORT  HibernateIntHandler       [WEAK]         
                EXPORT  USB0IntHandler            [WEAK]              
                EXPORT  PWM3IntHandler            [WEAK]              
                EXPORT  uDMAIntHandler            [WEAK]              
                EXPORT  uDMAErrorIntHandler       [WEAK]         
                EXPORT  ADC1Seq0IntHandler        [WEAK]          
                EXPORT  ADC1Seq1IntHandler        [WEAK]          
                EXPORT  ADC1Seq2IntHandler        [WEAK]          
                EXPORT  ADC1Seq3IntHandler        [WEAK]          
                EXPORT  I2S0IntHandler            [WEAK]              
                EXPORT  EBI0IntHandler            [WEAK]              
                EXPORT  GPIOJIntHandler           [WEAK]
GPIOAIntHandler             
GPIOBIntHandler             
GPIOCIntHandler             
GPIODIntHandler             
GPIOEIntHandler             
UART0IntHandler             
UART1IntHandler             
SSI0IntHandler              
I2C0IntHandler              
PWMFaultIntHandler          
PWM0IntHandler              
PWM1IntHandler              
PWM2IntHandler              
QEI0IntHandler              
ADC0Seq0IntHandler          
ADC0Seq1IntHandler          
ADC0Seq2IntHandler          
ADC0Seq3IntHandler          
WDTIntHandler               
TIMER0AIntHandler           
TIMER0BIntHandler           
TIMER1AIntHandler           
TIMER1BIntHandler           
TIMER2AIntHandler           
TIMER2BIntHandler           
ACMP0IntHandler             
ACMP1IntHandler             
ACMP2IntHandler             
SysCtlIntHandler            
FMCIntHandler               
GPIOFIntHandler             
GPIOGIntHandler             
GPIOHIntHandler             
UART2IntHandler             
SSI1IntHandler              
TIMER3AIntHandler           
TIMER3BIntHandler           
I2C1IntHandler              
QEI1IntHandler              
CAN0IntHandler              
CAN1IntHandler              
CAN2IntHandler              
EthernetIntHandler          
HibernateIntHandler         
USB0IntHandler              
PWM3IntHandler              
uDMAIntHandler              
uDMAErrorIntHandler         
ADC1Seq0IntHandler          
ADC1Seq1IntHandler          
ADC1Seq2IntHandler          
ADC1Seq3IntHandler          
I2S0IntHandler              
EBI0IntHandler              
GPIOJIntHandler                  
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
