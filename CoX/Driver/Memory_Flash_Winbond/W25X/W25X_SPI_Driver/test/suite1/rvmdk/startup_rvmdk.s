;//*****************************************************************************
;//
;//! \file startup_rvmdk.c
;//! \brief NUC1xx Devices Startup code for MDK.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss
;//!           - Setup the microcontroller system. 			
;//!           - Call the application's entry point.
;//!           .
;//! \version 1.0
;//! \date 8/13/2011
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

CLK_BA_base      EQU 0x50000200
PWRCON			 EQU 0x00
AHBCLK			 EQU 0x04
APBCLK			 EQU 0x08
CLKSEL0			 EQU 0x10
CLKSEL1			 EQU 0x14
CLKDIV			 EQU 0x18
PLLCON			 EQU 0x20
TEST_S			 EQU 0x30

CLK_BA_APBCLK    EQU 0x50000208

;// Define clock enable registers  

ADC_COMP_CLK     EQU 0x50000208
ADC_enable		 EQU 0x10000000
COMP_enable      EQU 0x40000000

PDMA_CLK         EQU 0x50000204 
PDMA_enable      EQU 0x00000003

;;  bit 0  CPU_EN
;;	bit 1  PDMA_EN




;// Define COMP registers base
COMP_base        EQU  0x400D0000
CMP1CR           EQU  0x00
CMP2CR           EQU  0x04
CMPSR            EQU  0x08

;// Define ADC registers base
ADC_base         EQU  0x400E0000
ADDR0            EQU  0x00
ADDR1            EQU  0x04
ADDR2            EQU  0x08
ADDR3            EQU  0x0c
ADDR4            EQU  0x10
ADDR5            EQU  0x14
ADDR6            EQU  0x18
ADDR7            EQU  0x1c
ADCR             EQU  0x20
ADCHER           EQU  0x24
ADCMPR0          EQU  0x28
ADCMPR1          EQU  0x2c
ADSR             EQU  0x30
ADCALR           EQU  0x34
ADCFCR           EQU  0x38
ADCALD           EQU  0x3c

;// Pattern Table
pattern_55555555 EQU  0x55555555
pattern_aaaaaaaa EQU  0xaaaaaaaa
pattern_00005555 EQU  0x00005555
pattern_0000aaaa EQU  0x0000aaaa
pattern_05550515 EQU  0x05550515
pattern_0aaa0a2a EQU  0x0aaa0a2a

;// Define PDMA regsiter base
PDMA_BA_ch0_base        EQU  0x50008000
PDMA_BA_ch1_base        EQU  0x50008100
PDMA_BA_ch2_base        EQU  0x50008200
PDMA_BA_ch3_base        EQU  0x50008300
PDMA_BA_ch4_base        EQU  0x50008400
PDMA_BA_ch5_base        EQU  0x50008500
PDMA_BA_ch6_base        EQU  0x50008600
PDMA_BA_ch7_base        EQU  0x50008700

PDMA_BA_GCR             EQU 0x50008F00
PDMA_BA_GCR_base        EQU 0x50008F00

PDMA_GCRCSR		 EQU  0X00
PDMA_PDSSR2		 EQU  0X04
PDMA_PDSSR1		 EQU  0X08  ;; PDMA channel select   0x77000000
PDMA_GCRISR		 EQU  0X0C

PDMA_GLOBAL_enable      EQU 0x0000FF00


PDMA_CSR         EQU  0X00
PDMA_SAR         EQU  0X04
PDMA_DAR         EQU  0X08
PDMA_BCR         EQU  0X0C
PDMA_CSAR        EQU  0X14
PDMA_CDAR        EQU  0X18
PDMA_CBSR        EQU  0X1C
PDMA_IER         EQU  0X20
PDMA_ISR         EQU  0X24
PDMA_CTCSR       EQU  0X28
PDMA_SASOCR		 EQU  0X2C
PDMA_DASOCR      EQU  0X30
PDMA_SBUF0       EQU  0X80
PDMA_SBUF1       EQU  0X84
PDMA_SBUF2       EQU  0X88
PDMA_SBUF3       EQU  0X8C


;// Define VIC control register
VIC_base         EQU  0xFFFF0000
VIC_SCR15        EQU  0x003c
VIC_SVR15        EQU  0x00bc
VIC_SCR16        EQU  0x0040
VIC_SVR16        EQU  0x00c0
VIC_SCR30        EQU  0x0078
VIC_SVR30        EQU  0x00f8
VIC_MECR         EQU  0x0318
VIC_MDCR         EQU  0x031c
VIC_EOSCR        EQU  0x0130

;//==================================
INT_BA_base      EQU  0x50000300


;// Parameter table
ADC_PDMA_CFG     EQU  0x00002980  
ADC_PDMA_DST     EQU  0xC0000000
ADC_PDMA_SRC     EQU  0xE0024200
ADC_PDMA_TCBL    EQU  0x00030008

;//==================================


GPIO_base        EQU  0x50004000
GPIOB_PMD		 EQU  0x0040
GPIOB_OFFD		 EQU  0x0044
GPIOB_DOUT		 EQU  0x0048
GPIOB_DMASK		 EQU  0x004C
GPIOB_PIN		 EQU  0x0050
GPIOB_DBEN		 EQU  0x0054
GPIOB_IMD		 EQU  0x0058
GPIOB_IEN		 EQU  0x005C
GPIOB_ISRC		 EQU  0x0060

;//==================================


GCR_base         EQU  0x50000000
GPB_MFP          EQU  0x0034





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;







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

                ; External Interrupts
                                                    ; maximum of 32 External Interrupts are possible
                DCD     BODIntHandler               ; Brownout low voltage detected interrupt                 
                DCD     WDTIntHandler               ; Watch Dog Timer interrupt                              
                DCD     EINT0IntHandler             ; External signal interrupt from PB.14 pin                
                DCD     EINT1IntHandler             ; External signal interrupt from PB.15 pin                
                DCD     GPABIntHandler              ; External signal interrupt from PA[15:0] / PB[13:0]     
                DCD     GPCDEIntHandler             ; External interrupt from PC[15:0]/PD[15:0]/PE[15:0]     
                DCD     PWMAIntHandler              ; PWM0 or PWM2 interrupt                                 
                DCD     PWMBIntHandler              ; PWM1 or PWM3 interrupt                                 
                DCD     TIMER0IntHandler            ; Timer 0 interrupt                                      
                DCD     TIMER1IntHandler            ; Timer 1 interrupt                                      
                DCD     TIMER2IntHandler            ; Timer 2 interrupt                                      
                DCD     TIMER3IntHandler            ; Timer 3 interrupt                                      
                DCD     UART02IntHandler            ; UART0 interrupt                                        
                DCD     UART1IntHandler             ; UART1 interrupt                                        
                DCD     SPI0IntHandler              ; SPI0 interrupt                                         
                DCD     SPI1IntHandler              ; SPI1 interrupt                                         
                DCD     SPI2IntHandler              ; SPI2 interrupt                                         
                DCD     SPI3IntHandler              ; SPI3 interrupt                                         
                DCD     I2C0IntHandler              ; I2C0 interrupt                                         
                DCD     I2C1IntHandler              ; I2C1 interrupt                                         
                DCD     CAN0IntHandler              ; CAN0 interrupt                                         
                DCD     DefaultIntHandler           ; Reserved                                         
                DCD     DefaultIntHandler           ; Reserved
                DCD     USBDIntHandler              ; USB FS Device interrupt                                
                DCD     PS2IntHandler               ; PS2 interrupt                                          
                DCD     ACMPIntHandler              ; Analog Comparator-0 or Comaprator-1 interrupt          
                DCD     PDMAIntHandler              ; PDMA interrupt  
                DCD     I2SIntHandler               ; I2S interrupt
                DCD     PWRWUIntHandler             ; Clock controller interrupt for chip wake up from power-
                DCD     ADCIntHandler               ; ADC interrupt                                          
                DCD     DefaultIntHandler           ; Reserved
                DCD     RTCIntHandler               ; Real time clock interrupt 
                

                
                
                
                AREA    |.text|, CODE, READONLY
                
                
                
; Reset Handler 
                
                ENTRY
                
ResetHandler   PROC
                EXPORT  ResetHandler             [WEAK]
                IMPORT  __main
                
                ; Check PB.15 to hold CPU               
                LDR     R0, =0x50004000
                LDR     R2, =0x8000
1
                LDR     R1, [R0, #0x50]
                ANDS    R1, R1, R2
                BEQ     %B1


                LDR     R0, =0x50000100
                
                ; Unlock Register                
                LDR     R1, =0x59
                STR     R1, [R0]
                LDR     R1, =0x16
                STR     R1, [R0]
                LDR     R1, =0x88
                STR     R1, [R0]

                ; Init clock
                LDR     R1, [R0, #0x10]
                CMP     R1, #0x3F
                BNE     %F0

                LDR     R1, =0x20
                STR     R1, [R0, #0x10]
0
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
                EXPORT  GPCDEIntHandler          [WEAK]
                EXPORT  PWMAIntHandler           [WEAK]
                EXPORT  PWMBIntHandler           [WEAK]
                EXPORT  TIMER0IntHandler         [WEAK]
                EXPORT  TIMER1IntHandler         [WEAK]
                EXPORT  TIMER2IntHandler         [WEAK]
                EXPORT  TIMER3IntHandler         [WEAK]
                EXPORT  UART02IntHandler         [WEAK]
                EXPORT  UART1IntHandler          [WEAK]
                EXPORT  SPI0IntHandler           [WEAK]
                EXPORT  SPI1IntHandler           [WEAK]
                EXPORT  SPI2IntHandler           [WEAK]
                EXPORT  SPI3IntHandler           [WEAK]
                EXPORT  I2C0IntHandler           [WEAK]
                EXPORT  I2C1IntHandler           [WEAK]
                EXPORT  CAN0IntHandler           [WEAK]
                EXPORT  USBDIntHandler           [WEAK]
                EXPORT  PS2IntHandler            [WEAK]
                EXPORT  ACMPIntHandler           [WEAK]
                EXPORT  PDMAIntHandler           [WEAK]
				EXPORT  I2SIntHandler            [WEAK]
                EXPORT  PWRWUIntHandler          [WEAK]
                EXPORT  ADCIntHandler            [WEAK]
                EXPORT  RTCIntHandler            [WEAK]
                
BODIntHandler
WDTIntHandler
EINT0IntHandler
EINT1IntHandler
GPABIntHandler
GPCDEIntHandler
PWMAIntHandler
PWMBIntHandler
TIMER0IntHandler
TIMER1IntHandler
TIMER2IntHandler
TIMER3IntHandler
UART02IntHandler
UART1IntHandler
SPI0IntHandler
SPI1IntHandler
SPI2IntHandler
SPI3IntHandler
I2C0IntHandler
I2C1IntHandler
CAN0IntHandler
USBDIntHandler
PS2IntHandler
ACMPIntHandler
PDMAIntHandler
I2SIntHandler
PWRWUIntHandler
ADCIntHandler
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
