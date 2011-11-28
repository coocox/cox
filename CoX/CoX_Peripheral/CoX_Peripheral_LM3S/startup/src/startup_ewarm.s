;//*****************************************************************************
;//
;//! \file startup_coide.c
;//! \brief TI Stellaris(LM3S) Devices Startup code for EWARM.
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

        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
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

                                     

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        PUBWEAK ResetHandler
        PUBWEAK NMIIntHandler       
        PUBWEAK HardFaultIntHandler 
        PUBWEAK MemFaultIntHandler
        PUBWEAK BusFaultIntHandler
        PUBWEAK UsageFaultIntHandler
        PUBWEAK SVCIntHandler
        PUBWEAK DebugMonitorIntHandler
        PUBWEAK PendSVIntHandler    
        PUBWEAK SysTickIntHandler  
        PUBWEAK GPIOAIntHandler             
        PUBWEAK GPIOBIntHandler             
        PUBWEAK GPIOCIntHandler             
        PUBWEAK GPIODIntHandler             
        PUBWEAK GPIOEIntHandler             
        PUBWEAK UART0IntHandler             
        PUBWEAK UART1IntHandler             
        PUBWEAK SSI0IntHandler              
        PUBWEAK I2C0IntHandler              
        PUBWEAK PWMFaultIntHandler          
        PUBWEAK PWM0IntHandler              
        PUBWEAK PWM1IntHandler              
        PUBWEAK PWM2IntHandler              
        PUBWEAK QEI0IntHandler              
        PUBWEAK ADC0Seq0IntHandler          
        PUBWEAK ADC0Seq1IntHandler          
        PUBWEAK ADC0Seq2IntHandler          
        PUBWEAK ADC0Seq3IntHandler          
        PUBWEAK WDTIntHandler               
        PUBWEAK TIMER0AIntHandler           
        PUBWEAK TIMER0BIntHandler           
        PUBWEAK TIMER1AIntHandler           
        PUBWEAK TIMER1BIntHandler           
        PUBWEAK TIMER2AIntHandler           
        PUBWEAK TIMER2BIntHandler           
        PUBWEAK ACMP0IntHandler             
        PUBWEAK ACMP1IntHandler             
        PUBWEAK ACMP2IntHandler             
        PUBWEAK SysCtlIntHandler            
        PUBWEAK FMCIntHandler               
        PUBWEAK GPIOFIntHandler             
        PUBWEAK GPIOGIntHandler             
        PUBWEAK GPIOHIntHandler             
        PUBWEAK UART2IntHandler             
        PUBWEAK SSI1IntHandler              
        PUBWEAK TIMER3AIntHandler           
        PUBWEAK TIMER3BIntHandler           
        PUBWEAK I2C1IntHandler              
        PUBWEAK QEI1IntHandler              
        PUBWEAK CAN0IntHandler              
        PUBWEAK CAN1IntHandler              
        PUBWEAK CAN2IntHandler              
        PUBWEAK EthernetIntHandler          
        PUBWEAK HibernateIntHandler         
        PUBWEAK USB0IntHandler              
        PUBWEAK PWM3IntHandler              
        PUBWEAK uDMAIntHandler              
        PUBWEAK uDMAErrorIntHandler         
        PUBWEAK ADC1Seq0IntHandler          
        PUBWEAK ADC1Seq1IntHandler          
        PUBWEAK ADC1Seq2IntHandler          
        PUBWEAK ADC1Seq3IntHandler          
        PUBWEAK I2S0IntHandler              
        PUBWEAK EBI0IntHandler              
        PUBWEAK GPIOJIntHandler             

        THUMB
        SECTION .text:CODE:REORDER(2)
ResetHandler

;****************************************** 
               LDR     R0, =__iar_program_start
               BX      R0
              SECTION .text:CODE:REORDER(2)
NMIIntHandler       
HardFaultIntHandler
MemFaultIntHandler
BusFaultIntHandler
UsageFaultIntHandler
SVCIntHandler
DebugMonitorIntHandler
PendSVIntHandler    
SysTickIntHandler 
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
DefaultIntHandler          
        B DefaultIntHandler 
        

        END
