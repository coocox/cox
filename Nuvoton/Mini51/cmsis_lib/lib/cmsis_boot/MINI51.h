//*****************************************************************************
//! \file     MINI51.h
//! \author   NuMicro MCU Software Team
//! \version  V1.01
//! \date     11. August 2011
//! \brief    CMSIS ARM Cortex-M0 Core Peripheral Access Layer Header File.
//!           This file contains all the peripheral register's definitions, 
//!           bits definitions and memory mapping for NuMicro Nano series.
//!
//! \note
//!  Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
//!
//!  par
//!  THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
//!  OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
//!  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
//!  ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
//!  CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//!
//******************************************************************************


#ifndef __MINI51_H__
#define __MINI51_H__

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
//
// Interrupt Number Definition 
//
//******************************************************************************

typedef enum IRQn
{
//******************************************************************************
//
// Cortex-M0 Processor Exceptions Numbers 
//
//******************************************************************************
  //
  // 2 Non Maskable Interrupt
  //
  NonMaskableInt_IRQn	= -14,	
  //
  // 3 Cortex-M0 Hard Fault Interrupt
  //
  HardFault_IRQn		= -13,	
  //
  // 11 Cortex-M0 SV Call Interrupt
  //
  SVCall_IRQn			= -5,	
  //
  // 14 Cortex-M0 Pend SV Interrupt
  //
  PendSV_IRQn			= -2,	
  //
  // 15 Cortex-M0 System Tick Interrupt
  //
  SysTick_IRQn			= -1,	

//******************************************************************************
//
// NANO1xx specific Interrupt Numbers 
//
//******************************************************************************
  //
  // Brownout low voltage detected interrupt
  //	
  BOD_IRQn              = 0,	
  //
  // Watch Dog Timer interrupt
  //
  WDT_IRQn              = 1,	
  //
  // External signal interrupt from P3.2 pin
  //
  EINT0_IRQn            = 2,	
  //
  // External signal interrupt from P3.3 pin
  //
  EINT1_IRQn            = 3,	
  //
  // External signal interrupt from P0/P1
  //
  GPIO01_IRQn           = 4,	
  //
  // External interrupt from P2/P3/P4
  //
  GPIO234_IRQn          = 5,	
  //
  // PWM interrupt
  //
  PWM_IRQn              = 6,	
  //
  // Fault break interrupt
  //
  FB_IRQn               = 7,	
  //
  // Timer 0 interrupt
  //
  TMR0_IRQn             = 8,	
  //
  // Timer 1 interrupt
  //
  TMR1_IRQn             = 9,	
  //
  // UART0 interrupt
  //
  UART0_IRQn            = 12,	
  //
  // SPI0 interrupt
  //
  SPI_IRQn              = 14,	
  //
  // External interrupt from P5 
  //
  GPIO5_IRQn            = 16,	
  //
  // HFIRC trim interrupt source identify
  //
  HIRC_IRQn             = 17,  	
  //
  // I2C interrupt
  //
  I2C_IRQn              = 18,	
  //
  // ACMP interrupt
  //
  ACMP_IRQn				= 25,	
  //
  // Power Down Wake up interrupt
  //
  PDWU_IRQn             = 28,	
  //
  // ADC interrupt
  //
  ADC_IRQn              = 29	
  
} IRQn_Type;


//******************************************************************************
//
// Processor and Core Peripheral Section 
//
//******************************************************************************

//******************************************************************************
//
// Configuration of the Cortex-M0 Processor and Core Peripherals 
//
//******************************************************************************

//
// MPU present or not
//
#define __MPU_PRESENT             0         
//
// Number of Bits used for Priority Levels
//
#define __NVIC_PRIO_BITS          2         
//
// Set to 1 if different SysTick Config is used
//
#define __Vendor_SysTickConfig    0         

//
// Cortex-M0 processor and core peripherals
//
#include "core_cm0.h"                       
#include "system_MINI51.h"                 
#include "SysInfra.h"    
#include <stdint.h>

#if defined ( __CC_ARM  )
#pragma anon_unions
#endif

//*****************************************************************************
//
// Device Specific Peripheral registers structures 
//
//*****************************************************************************

//
//! \brief General Purpose I/O pins (GPIO)
//
typedef struct
{
  union {
  __IO uint32_t  PMD;
                 struct {
                 __IO uint32_t PMD0:2;
                 __IO uint32_t PMD1:2;
                 __IO uint32_t PMD2:2;
                 __IO uint32_t PMD3:2;
                 __IO uint32_t PMD4:2;
                 __IO uint32_t PMD5:2;
                 __IO uint32_t PMD6:2;
                 __IO uint32_t PMD7:2;
                 __I  uint32_t RESERVE:16;
                 } PMD_BITS;
  };
  __IO uint32_t  OFFD;
  __IO uint32_t  DOUT;
  __IO uint32_t  DMASK;
  __I  uint32_t  PIN;
  __IO uint32_t  DBEN;
  __IO uint32_t  IMD;
  union {
  __IO uint32_t  IER;
                 struct {
                 __IO uint32_t  FIER:8;
                 __I  uint32_t RESERVE0:8;
                 __IO uint32_t  RIER:8;
                 __I  uint32_t RESERVE1:8;
                 } IER_BITS;
  };
  __IO uint32_t  ISR;
} GPIO_TypeDef;

//
//! \brief GPIO De-bounce Cycle Control
//
typedef struct
{
  union {
  __IO uint32_t  CON;
                 struct {
                 __IO uint32_t  DBCLKSEL:4;
                 __IO uint32_t  DBCLKSRC:1;
                 __IO uint32_t  DBCLKEN:1;
                 __I  uint32_t  RESERVE:26;    
                 } CON_BITS;
  };
} GPIODBNCE_TypeDef;

//
//! \brief General Purpose I/O bit mode (GPIO bit mode)
//
typedef struct
{
  __IO uint32_t  GP_BIT0;
  __IO uint32_t  GP_BIT1;
  __IO uint32_t  GP_BIT2;
  __IO uint32_t  GP_BIT3;
  __IO uint32_t  GP_BIT4;
  __IO uint32_t  GP_BIT5;
  __IO uint32_t  GP_BIT6;
  __IO uint32_t  GP_BIT7;
} GPIOBIT_TypeDef;

//*****************************************************************************
//
// UART Interface Controller 
//
//*****************************************************************************

//
//! \brief UART
//
typedef struct
{
  union {
  __I   uint32_t  RBR;
  __O   uint32_t  THR;
  };
  union {
  __IO uint32_t  IER;
                 struct {
                 __IO uint32_t  RDA_IEN:1;
                 __IO uint32_t  THRE_IEN:1;
                 __IO uint32_t  RLS_IEN:1;
                 __IO uint32_t  MODEM_IEN:1;
                 __IO uint32_t  RTO_IEN:1;	  
                 __IO uint32_t  BUF_ERR_IEN:1;
                 __IO uint32_t  WAKE_EN:1;
                 __I  uint32_t  RESERVED0:4;
		         __IO uint32_t  TIME_OUT_EN:1;
		         __IO uint32_t  AUTO_RTS_EN:1;	  
                 __IO uint32_t  AUTO_CTS_EN:1;
		         __I  uint32_t  RESERVED2:18;		 
		   } IER_BITS;
  };
  union {
  __IO uint32_t  FCR;
                 struct {
                 __I  uint32_t  RESERVED0:1;	
                 __IO uint32_t  RFR:1;
                 __IO uint32_t  TFR:1;
		         __I  uint32_t  RESERVED1:1;
                 __IO uint32_t  RFITL:4;
                 __IO uint32_t  RX_DIS:1;	  
                 __I  uint32_t  RESERVED2:7;
		         __IO uint32_t  RTS_TRI_LEV:4;
		         __I  uint32_t  RESERVED3:12;   
                 } FCR_BITS;
  };
  union {
  __IO uint32_t  LCR;
                 struct {
                 __IO uint32_t  WLS:2;
                 __IO uint32_t  NSB:1;
                 __IO uint32_t  PBE:1;
                 __IO uint32_t  EPE:1;
                 __IO uint32_t  SPE:1;	  
                 __IO uint32_t  BCB:1;
                 __I  uint32_t  RESERVED0:25;    
                 } LCR_BITS;
  };
   union {
  __IO uint32_t  MCR;
                 struct {
		         __I  uint32_t  RESERVED0:1; 
                 __IO uint32_t  RTS:1;
                 __I  uint32_t  RESERVED1:2;          
		         __IO uint32_t  LBME:1;	
                 __I  uint32_t  RESERVED2:4;
                 __IO uint32_t  LEV_RTS:1;
                 __I  uint32_t  RESERVED3:3; 
                 __IO uint32_t  RTS_ST:1;
                 __I  uint32_t  RESERVED4:18;
                 } MCR_BITS;
  };
    union {
  __IO uint32_t  MSR;
                 struct {
                 __IO uint32_t  DCTSF:1;
                 __I  uint32_t  RESERVED0:3; 
                 __IO uint32_t  CTS_ST:1;
                 __I  uint32_t  RESERVED1:3;               
                 __IO uint32_t  LEV_CTS:1;
                 __I  uint32_t  RESERVED2:23; 
                 } MSR_BITS;
  };
  union {
  __IO uint32_t  FSR;
                 struct {
                 __IO uint32_t  RX_OVER_IF:1;
                 __I  uint32_t  RESERVED0:2;
                 __IO uint32_t  RS485_ADD_DETF:1;
                 __IO uint32_t  PEF:1;
                 __IO uint32_t  FEF:1;
                 __IO uint32_t  BIF:1;
                 __I  uint32_t  RESERVED1:1;
                 __IO uint32_t  RX_POINTER:6;
                 __IO uint32_t  RX_EMPTY:1;
                 __IO uint32_t  RX_FULL:1;
                 __IO uint32_t  TX_POINTER:6; 
                 __IO uint32_t  TX_EMPTY:1;
                 __IO uint32_t  TX_FULL:1;
                 __IO uint32_t  TX_OVER_IF:1;		
                 __I  uint32_t  RESERVED2:3;
                 __IO uint32_t  TE_FLAG:1;
                 __I  uint32_t  RESERVED3:3;
                 } FSR_BITS;
  };
   union {
  __IO uint32_t  ISR;
                 struct {
                 __IO uint32_t  RDA_IF:1;
                 __IO uint32_t  THRE_IF:1;
                 __IO uint32_t  RLS_IF:1;
                 __IO uint32_t  MODEM_IF:1;
                 __IO uint32_t  TOUT_IF:1;
                 __IO uint32_t  BUF_ERR_IF:1;
                 __I  uint32_t  RESERVED0:2;		 	
                 __IO uint32_t  RDA_INT:1;
                 __IO uint32_t  THRE_INT:1;
                 __IO uint32_t  RLS_INT:1;
                 __IO uint32_t  MODEM_INT:1;
                 __IO uint32_t  TOUT_INT:1;
                 __IO uint32_t  BUF_ERR_INT:1;
                 __I  uint32_t  RESERVED1:18;
                 } ISR_BITS;
  };
   union {
  __IO uint32_t  TOR;
  		  struct {
                 __IO uint32_t  TOIC:7;
                 __I  uint32_t  RESERVED0:1;
                 __IO uint32_t  DLY:8;
                 __I  uint32_t  RESERVED1:16;
                 } TOR_BITS;
  };
    union {
  __IO uint32_t  BAUD;
                 struct {
                 __IO uint32_t  BRD:16;
                 __I  uint32_t  RESERVED0:8;
                 __IO uint32_t  DIVIDER_X:4;
                 __IO uint32_t  DIV_X_ONE:1; 
                 __IO uint32_t  DIV_X_EN:1; 
                 __I  uint32_t  RESERVED1:2;
                 } BAUD_BITS;
  };
   union {
  __IO uint32_t  IRCR;
                 struct {
                 __I  uint32_t  RESERVED0:1;				 	
                 __IO uint32_t  TX_SELECT:1;
                 __I  uint32_t  RESERVED1:3;				 
                 __IO uint32_t  INV_TX:1;            
                 __IO uint32_t  INV_RX:1;            
                 __I  uint32_t  RESERVE2:25;
                 } IRCR_BITS;
  };
   union {
  __IO uint32_t  ALT_CSR;
  		struct {
                 __I  uint32_t  RESERVED0:8;         
                 __IO uint32_t  RS485_NMM:1;
                 __IO uint32_t  RS485_AAD:1;
                 __IO uint32_t  RS485_AUD:1;
                 __I  uint32_t  RESERVED1:4;		
                 __IO uint32_t  RS485_ADD_EN:1;
                 __I  uint32_t  RESERVED2:8;
                 __IO uint32_t  ADDR_MATCH:8;
                 } ALT_CSR_BITS;
  };
    union {
  __IO uint32_t  FUN_SEL;
               struct {
                 __IO uint32_t  FUN_SEL:2;
	             __I  uint32_t  RESERVE0:30;
                 } FUN_SEL_BITS;   
  }; 
} UART_TypeDef;

//*****************************************************************************
//
// Timer Controller 
//
//*****************************************************************************

//
//! \brief General Timer
//
typedef struct
{
  union {
  __IO uint32_t  CSR;
                 struct {
                 __IO uint32_t  PRESCALE:8;
				      uint32_t  RESERVED0:8;
				 __IO uint32_t  TDR_EN:1;
				      uint32_t  RESERVED1:6;
				 __IO uint32_t  WAKE_EN:1;
				 __IO uint32_t  CTB:1;
				 __IO uint32_t  CACT:1;
                 __IO uint32_t  CRST:1;
				 __IO uint32_t  MODE:2;
                 __IO uint32_t  IE:1;
                 __IO uint32_t  CEN:1;
				      uint32_t  RESERVED2:1;
                } CSR_BITS;
  };
  __IO uint32_t  CMPR;
  union {
  __IO uint32_t  ISR;
                 struct {
                 __IO uint32_t  TIF:1;
                 __IO uint32_t  TWF:1;
                      uint32_t  RESERVED0:30;
                 } ISR_BITS;
  };
  __I  uint32_t  DR;
  __I  uint32_t  CAP;
  union {
  __IO uint32_t  EXCON;
                 struct {
                 __IO uint32_t  TX_PHASE:1;
                 __IO uint32_t  TEX_EDGE:2;
                 __IO uint32_t  TEXEN:1;
                 __IO uint32_t  RSTCAP:1;
                 __IO uint32_t  TEX_INT:1;
                 __IO uint32_t  TEX_DBNCE:1;
                 __IO uint32_t  COUNTER_DBNCE:1;
                 __IO uint32_t  CAP_MODE:1;
                      uint32_t  RESERVED0:23;
                 } EXCON_BITS;
  };  
  union {
  __IO uint32_t  EXISR;
                 struct {
                 __IO uint32_t  TEXIF:1;
                      uint32_t  RESERVED0:31;
                 } EXISR_BITS;
  };  
} TIMER_TypeDef;

//*****************************************************************************
//
// WDT Controller 
//
//*****************************************************************************

//
//! \brief WatchDog Timer
//
typedef struct
{
  union {
  __IO uint32_t  WTCR;
                 struct {
                 __IO uint32_t  WTR:1;
	             __IO uint32_t  WTRE:1;
	             __IO uint32_t  WTRF:1;
	             __IO uint32_t  WTIF:1;
				 __IO uint32_t  WTWKE:1;
				 __IO uint32_t  WTWKF:1;
				 __IO uint32_t  WTIE:1;
				 __IO uint32_t  WTE:1;
	             __IO uint32_t  WTIS:3;
                 __I  uint32_t  RESERVED0:21;
                 } WTCR_BITS;
  };
} WDT_TypeDef;

//*****************************************************************************
//
// SPI Interface Controller 
//
//*****************************************************************************

//
//! \brief Serial Peripheral Interface (SPI)
//
typedef struct
{
  union {
  __IO uint32_t  CNTRL;
                 struct {
                 __IO uint32_t  GO_BUSY:1;
                 __IO uint32_t  RX_NEG:1;
                 __IO uint32_t  TX_NEG:1;
                 __IO uint32_t  TX_BIT_LEN:5;
                 __IO uint32_t  TX_NUM:2;
                 __IO uint32_t  LSB:1;
                 __IO uint32_t  CLKP:1;
                 __IO uint32_t  SP_CYCLE:4;
                 __IO uint32_t  IF:1;
                 __IO uint32_t  IE:1;
                 __IO uint32_t  SLAVE:1;
                 __IO uint32_t  REORDER:2;
                 __IO uint32_t  FIFO:1;
                 	  uint32_t  RESERVED0:1;
                 __IO uint32_t  VARCLK_EN:1;
                 __IO uint32_t  RX_EMPTY:1;
			     __IO uint32_t  RX_FULL:1;
			     __IO uint32_t  TX_EMPTY:1;
			     __IO uint32_t  TX_FULL:1;			    
                      uint32_t  RESERVED1:4;
                 } CNTRL_BITS;
  };
  union {
  __IO uint32_t  DIVIDER;
                 struct {
                 __IO uint32_t  DIVIDER1:16;
                 __IO uint32_t  DIVIDER2:16;
                 } DIVIDER_BITS;
  }; 
  union {
  __IO uint32_t  SSR;
                 struct {
                 __IO uint32_t  SSR:1;
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  SS_LVL:1;
                 __IO uint32_t  AUTOSS:1;
                 __IO uint32_t  SS_LTRIG:1;
                 __IO uint32_t  LTRIG_FLAG:1;
                 	  uint32_t  RESERVED1:26;
                 } SSR_BITS;
  };
       uint32_t  RESERVED0;
  __I  uint32_t  RX0;
  __I  uint32_t  RX1;
       uint32_t  RESERVED1;
       uint32_t  RESERVED2;
  __O  uint32_t  TX0;
  __O  uint32_t  TX1;
       uint32_t  RESERVED3;
       uint32_t  RESERVED4;
       uint32_t  RESERVED5;
  __IO uint32_t  VARCLK;
       uint32_t  RESERVED6;
  union {
  __IO uint32_t  CNTRL2;
                 struct {
                 __IO uint32_t  DIV_ONE:1;
			     __I  uint32_t  RESERVE1:7;
			     __IO uint32_t  NOSLVSEL:1;
			     __IO uint32_t  SLV_ABORT:1;
			     __IO uint32_t  SSTA_INTEN:1;
			     __IO uint32_t  SLV_START_INTSTS:1;
			     __I  uint32_t  RESERVE0:20;                 
                 } CNTRL2_BITS;
  };
  union {
  __IO uint32_t  FIFO_STS_CLR;
                 struct {
                 __IO uint32_t  RX_CLR:1;
				 __IO uint32_t  TX_CLR:1;
    			 __I  uint32_t  RESERVE0:30;               
                 } FIFO_STS_CLR_BITS;
  };
  
} SPI_TypeDef;

//*****************************************************************************
//
// I2C Controller 
//
//*****************************************************************************

//
//! \brief I2C
//
typedef struct
{
  union {
  __IO uint32_t  CON;
                 struct {
                      uint32_t  RESERVED0:2;
                 __IO uint32_t  AA:1;
                 __IO uint32_t  SI:1;
                 __IO uint32_t  STOP:1;
                 __IO uint32_t  START:1;
                 __IO uint32_t  ENSI:1;
                 __IO uint32_t  EI:1;
                      uint32_t  RESERVED1:24;
                 } CON_BITS;
  };
  union {
  __IO uint32_t  SADDR0;
                 struct {
                 __IO uint32_t  GC:1;
                 __IO uint32_t  SADDR:7;
                      uint32_t  RESERVED0:24;
                 } SADDR0_BITS;
  };
  __IO uint32_t  DATA;
  __IO uint32_t  STATUS;
  __IO uint32_t  DIV;
  union {
  __IO uint32_t  TOUT;
                 struct {
                 __IO uint32_t  TIF:1;
                 __IO uint32_t  DIV4:1;
                 __IO uint32_t  ENTI:1;
                      uint32_t  RESERVED0:29;
                 } TOUT_BITS;
  };
  union {
  __IO uint32_t  SADDR1;
                 struct {
                 __IO uint32_t  GC:1;
                 __IO uint32_t  SADDR:7;
                      uint32_t  RESERVED0:24;
                 } SADDR1_BITS;
  };
  union {
  __IO uint32_t  SADDR2;
                 struct {
                 __IO uint32_t  GC:1;
                 __IO uint32_t  SADDR:7;
                      uint32_t  RESERVED0:24;
                 } SADDR2_BITS;
  };
  union {
  __IO uint32_t  SADDR3;
                 struct {
                 __IO uint32_t  GC:1;
                 __IO uint32_t  SADDR:7;
                      uint32_t  RESERVED0:24;
                 } SADDR3_BITS;
  };
  union {
  __IO uint32_t  SAMASK0;
  				struct {
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  SAMASK:7;
                      uint32_t  RESERVED1:24;
                 } SAMASK0_BITS;
  };               
  union {
  __IO uint32_t  SAMASK1;
  				struct {
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  SAMASK:7;
                      uint32_t  RESERVED1:24;
                 } SAMASK1_BITS;
  };
  union {
  __IO uint32_t  SAMASK2;
  				struct {
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  SAMASK:7;
                      uint32_t  RESERVED1:24;
                 } SAMASK2_BITS;
  };
  union {
  __IO uint32_t  SAMASK3;
  				struct {
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  SAMASK:7;
                      uint32_t  RESERVED1:24;
                 } SAMASK3_BITS;
  };
} I2C_TypeDef;

//*****************************************************************************
//
// ADC Controller 
//
//*****************************************************************************

//
//! \brief Analog-to-Digital Converters (ADC)
//
typedef struct
{
  union {
  __IO uint32_t  DR;
                 struct {
                 __IO uint32_t  RESULT:10;
					  uint32_t  RESERVED0:6;
                 __IO uint32_t  OVERRUN:1;
                 __IO uint32_t  VALID:1;
                      uint32_t  RESERVED1:14;
                 } DR_BITS;
  };
	   uint32_t RESERVED0[7];
  union {
  __IO uint32_t  CR;
                 struct {
                 __IO uint32_t  ADEN:1;
                 __IO uint32_t  ADIE:1;
                 __IO uint32_t  RESERVED0:4;
                 __IO uint32_t  TRGCOND:1;
                 __IO uint32_t  RESERVED1:1;				 
                 __IO uint32_t  TRGEN:1;
                 __IO uint32_t  RESERVED2:2;
                 __IO uint32_t  ADST:1;
                      uint32_t  RESERVED3:20;
                 } CR_BITS;
  };
  union {
  __IO uint32_t  CHER;
                 struct {
                 __IO uint32_t  CHEN0:1;
                 __IO uint32_t  CHEN1:1;
                 __IO uint32_t  CHEN2:1;
                 __IO uint32_t  CHEN3:1;
                 __IO uint32_t  CHEN4:1;
                 __IO uint32_t  CHEN5:1;
                 __IO uint32_t  CHEN6:1;
                 __IO uint32_t  CHEN7:1;
                 __IO uint32_t  PRESEL:1;
                      uint32_t  RESERVED0:23;
                 } CHER_BITS;
  };
  union {
  __IO uint32_t  CMPR0;
                 struct {
                 __IO uint32_t  CMPEN:1;
                 __IO uint32_t  CMPIE:1;
                 __IO uint32_t  CMPCOND:1;
                 __IO uint32_t  CMPCH:3;
                      uint32_t  RESERVED0:2;
                 __IO uint32_t  CMPMATCNT:4;
                      uint32_t  RESERVED1:4;
                 __IO uint32_t  CMPD:10;
                      uint32_t  RESERVED2:6;
                } CMPR0_BITS;
  };
  union {
  __IO uint32_t  CMPR1;
                 struct {
                 __IO uint32_t  CMPEN:1;
                 __IO uint32_t  CMPIE:1;
                 __IO uint32_t  CMPCOND:1;
                 __IO uint32_t  CMPCH:3;
                      uint32_t  RESERVED0:2;
                 __IO uint32_t  CMPMATCNT:4;
                      uint32_t  RESERVED1:4;
                 __IO uint32_t  CMPD:10;
                      uint32_t  RESERVED2:6;
                } CMPR1_BITS;
  };
  union {
  __IO uint32_t  SR;
                 struct {
                 __IO uint32_t  ADF:1;
                 __IO uint32_t  CMPF0:1;
                 __IO uint32_t  CMPF1:1;
                 __IO uint32_t  BUSY:1;
                 __IO uint32_t  CHANNEL:3;                      
				 	  uint32_t  RESERVED0:1;
                 __IO uint32_t  VALID:1;
				 	  uint32_t  RESERVED1:7;				 
                 __IO uint32_t  OVERRUN:1;			 
                      uint32_t  RESERVED2:15;
                 } SR_BITS;
  };
} ADC_TypeDef;

//*****************************************************************************
//
// Analog Comparator Controller 
//
//*****************************************************************************

//
//! \brief Analog Comparator (ACMP)
//
typedef struct
{
  union {
  __IO uint32_t  CR0;
                 struct {
                 __IO uint32_t  CMPEN:1;
                 __IO uint32_t  CMPIE:1;
                 __IO uint32_t  HYSEN:1;
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  CMPCN:1;
                      uint32_t  RESERVED1:27;
                 } CR0_BITS;
  };
  union {
  __IO uint32_t  CR1;
                 struct {
                 __IO uint32_t  CMPEN:1;
                 __IO uint32_t  CMPIE:1;
                 __IO uint32_t  HYSEN:1;
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  CMPCN:1;
                      uint32_t  RESERVED1:27;
                 } CR1_BITS;
  };
  union {
  __IO uint32_t  SR;
                 struct {
                 __IO uint32_t  CMPF0:1;
                 __IO uint32_t  CMPF1:1;
                 __IO uint32_t  CO0:1;
                 __IO uint32_t  CO1:1;
				 	  uint32_t  RESERVED0:28;
                 } SR_BITS;
  };
  union {
  __IO uint32_t  RVCR;
                 struct {
                 __IO uint32_t  CRVS:4;
                 __IO uint32_t  RESERVED0:3;
                 __IO uint32_t  OUT_SEL:1;
				 	  uint32_t  RESERVED1:24;
                 } RVCR_BITS;
  };  
} ACMP_TypeDef;

//*****************************************************************************
//
// Clock Controller 
//
//*****************************************************************************

//
//! \brief Clock Control Registers (CLK)
//
typedef struct
{
  union {
  __IO uint32_t  PWRCON;
                 struct {
                 __IO uint32_t  XTLCLK_EN:2;
                 __IO uint32_t  OSC22M_EN:1;
                 __IO uint32_t  OSC10K_EN:1;
                 __IO uint32_t  WK_DLY:1;
                 __IO uint32_t  PD_WK_IE:1;
                 __IO uint32_t  PD_WK_STS:1;
                 __IO uint32_t  PD_EN:1;
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  PD_32K_EN:1;
                      uint32_t  RESERVED1:22;
                 } PWRCON_BITS;
  };
  union {
  __IO uint32_t  AHBCLK;
                 struct {
                      uint32_t  RESERVED0:2;
                 __IO uint32_t  ISP_EN:1;
                      uint32_t  RESERVED1:29;
                 } AHBCLK_BITS;
  };
  union {
  __IO uint32_t  APBCLK;
                 struct {
                 __IO uint32_t  WDT_EN:1;
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  TMR0_EN:1;
                 __IO uint32_t  TMR1_EN:1;
                      uint32_t  RESERVED1:2;
                 __IO uint32_t  FDIV_EN:1;
                      uint32_t  RESERVED2:1;
                 __IO uint32_t  I2C_EN:1;
                      uint32_t  RESERVED3:3;
                 __IO uint32_t  SPI_EN:1;
                      uint32_t  RESERVED4:3;
                 __IO uint32_t  UART_EN:1;
	                  uint32_t  RESERVED5:3;
                 __IO uint32_t  PWM01_EN:1;
                 __IO uint32_t  PWM23_EN:1;
	             __IO uint32_t  PWM45_EN:1;
	                  uint32_t  RESERVED6:5;
                 __IO uint32_t  ADC_EN:1;
	                  uint32_t  RESERVED7:1;
                 __IO uint32_t  ACMP_EN:1;
	                  uint32_t  RESERVED8:1;
                 } APBCLK_BITS;
  };
  union {
  __IO uint32_t  CLKSTATUS;
                 struct {
                 __IO uint32_t  XTL_STB:1;
                      uint32_t  RESERVED0:2;
                 __IO uint32_t  OSC10K_STB:1;
                 __IO uint32_t  OSC22M_STB:1;
                      uint32_t  RESERVED1:2;
                 __IO uint32_t  CLK_SW_FAIL:1;
                      uint32_t  RESERVED2:24;
                 } CLKSTATUS_BITS;
  };
  union {
  __IO uint32_t  CLKSEL0;
                 struct {
                 __IO uint32_t  HCLK_S:3;
                 __IO uint32_t  STCLK_S:3;
                      uint32_t  RESERVED0:26;
                 } CLKSEL0_BITS;
  };
  union {
  __IO uint32_t  CLKSEL1;
                 struct {
                 __IO uint32_t  WDT_S:2;
                 __IO uint32_t  ADC_S:2;
                      uint32_t  RESERVED0:4;
                 __IO uint32_t  TMR0_S:3;
                      uint32_t  RESERVED1:1;
                 __IO uint32_t  TMR1_S:3;
                      uint32_t  RESERVED2:9;
                 __IO uint32_t  UART_S:2;
                      uint32_t  RESERVED4:2;
                 __IO uint32_t  PWM01_S:2;
                 __IO uint32_t  PWM23_S:2;
                 } CLKSEL1_BITS;
  };
  union {
  __IO uint32_t  CLKDIV;
                  struct {
                 __IO uint32_t  HCLK_N:4;
                      uint32_t  RESERVED0:4;
                 __IO uint32_t  UART_N:4;
                      uint32_t  RESERVED1:4;
                 __IO uint32_t  ADC_N:8;
                      uint32_t  RESERVED2:8;
                 } CLKDIV_BITS;
  };
  union {
  __IO uint32_t  CLKSEL2;
                 struct {
                      uint32_t  RESERVED0:2;      
                 __IO uint32_t  FRQDIV_S:2;
                 __IO uint32_t  PWM45_S:2;
                      uint32_t  RESERVED1:26;
                 } CLKSEL2_BITS;
  };
          uint32_t  RESERVED0;
  union {
  __IO uint32_t  FRQDIV;
                 struct {    
                 __IO uint32_t  FSEL:4;
	             __IO uint32_t  FDIV_EN:1;
                 __I  uint32_t  RESERVE:27;
                 } FRQDIV_BITS;
  };
} CLK_TypeDef;

//*****************************************************************************
//
// Global Controller 
//
//*****************************************************************************

//
//! \brief System Management Control Registers (GCR)
//
typedef struct
{
  __I  uint32_t  PDID;
  union {
  __IO uint32_t  RST_SRC;
                 struct {
                 __IO uint32_t  POR:1;
	             __IO uint32_t  RESET:1;
	             __IO uint32_t  WDT:1;
	                  uint32_t  RESERVED0:1;
	             __IO uint32_t  BOD:1;
	             __IO uint32_t  MCU:1;
                 __IO uint32_t  PMU:1;
	             __IO uint32_t  CPU:1;    
	                  uint32_t  RESERVED1:24;
                 } RST_SRC_BITS;
  };
  union {
  __IO uint32_t  IPRST_CTL1;
                 struct {
                 __IO uint32_t  CHIP_RST:1;
                 __IO uint32_t  CPU_RST:1;
                      uint32_t  RESERVED0:30;
                 } IPRST_CTL1_BITS;
  };
  union {
  __IO uint32_t  IPRST_CTL2;
                 struct {
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  GPIO_RST:1;
                 __IO uint32_t  TMR0_RST:1;
                 __IO uint32_t  TMR1_RST:1;
                      uint32_t  RESERVED1:4;
                 __IO uint32_t  I2C_RST:1;
                      uint32_t  RESERVED2:3;
                 __IO uint32_t  SPI_RST:1;
                      uint32_t  RESERVED3:3;
                 __IO uint32_t  UART_RST:1;
                      uint32_t  RESERVED4:3;
                 __IO uint32_t  PWM_RST:1;
                      uint32_t  RESERVED5:1;
                 __IO uint32_t  ACMP_RST:1;
                      uint32_t  RESERVED6:5;
                 __IO uint32_t  ADC_RST:1;
                      uint32_t  RESERVED7:3;
                 } IPRST_CTL2_BITS;
  };
       uint32_t  RESERVED0[2];
  union {
  __IO uint32_t  BODCTL;
                 struct {
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  VL:2;
                 __IO uint32_t  RSTEN:1;
                 __IO uint32_t  INTF:1;
                      uint32_t  RESERVED1:1;
                 __IO uint32_t  OUT:1;
                      uint32_t  RESERVED2:9;
                 __IO uint32_t  TRIM27:4;
                 __IO uint32_t  TRIM38:4;
	                  uint32_t  RESERVED3:8;
                 } BODCTL_BITS;
  };
       uint32_t  RESERVED1[2];
  __IO uint32_t  PORCTL;
       uint32_t  RESERVED2[2];
  union {
  __IO uint32_t  P0_MFP;
                 struct {
                 __IO uint32_t  MFP:8;
                 __IO uint32_t  ALT:8;
                 __IO uint32_t  TYPE:8;
	                  uint32_t  RESERVED0:8;
                 } P0_MFP_BITS;
  };
  union {
  __IO uint32_t  P1_MFP;
                 struct {
                 __IO uint32_t  MFP:8;
                 __IO uint32_t  ALT:8;
                 __IO uint32_t  TYPE:8;
	                  uint32_t  RESERVED0:8;
                 } P1_MFP_BITS;
  };
  union {
  __IO uint32_t  P2_MFP;
                 struct {
                 __IO uint32_t  MFP:8;
                 __IO uint32_t  ALT:8;
                 __IO uint32_t  TYPE:8;
	                  uint32_t  RESERVED0:8;
                 } P2_MFP_BITS;
  };
  union {
  __IO uint32_t  P3_MFP;
                 struct {
                 __IO uint32_t  MFP:8;
                 __IO uint32_t  ALT:8;
                 __IO uint32_t  TYPE:8;
	                  uint32_t  RESERVED0:8;
                 } P3_MFP_BITS;
  };
  union {
  __IO uint32_t  P4_MFP;
                 struct {
                 __IO uint32_t  MFP:8;
                 __IO uint32_t  ALT:8;
                 __IO uint32_t  TYPE:8;
	                  uint32_t  RESERVED0:8;
                 } P4_MFP_BITS;
  };
  union {
  __IO uint32_t  P5_MFP;
                 struct {
                 __IO uint32_t  MFP:8;
                 __IO uint32_t  ALT:8;
                 __IO uint32_t  TYPE:8;
	                  uint32_t  RESERVED0:8;
                 } P5_MFP_BITS;
  };
       uint32_t  RESERVED3[14];
  union {
  __IO uint32_t  IRCTRIMCTL;
                 struct {
                 __IO uint32_t  TRIM_SEL:2;
	                  uint32_t  RESERVED0:2;
                 __IO uint32_t  TRIM_LOOP:2;
                 __IO uint32_t  TRIM_RETRY_CNT:2;
	                  uint32_t  RESERVED1:24;
                 } IRCTRIMCTL_BITS;
  };
  union {
  __IO uint32_t  IRCTRIMIER;
                 struct {
	                  uint32_t  RESERVED0:1;
                 __IO uint32_t  TRIM_FAIL_IE:1;
                 __IO uint32_t  ERR_32K_IE:1;
	                  uint32_t  RESERVED1:29;
                 } IRCTRIMIER_BITS;
  };
  union {
  __IO uint32_t  IRCTRIMISR;
                 struct {
                 __IO uint32_t  FREQ_LOCK:1;
                 __IO uint32_t  TRIM_FAIL_IS:1;
                 __IO uint32_t  ERR_32K_IS:1;
	                  uint32_t  RESERVED0:29;
                 } IRCTRIMISR_BITS;
  };
       uint32_t  RESERVED4[29];
  __IO uint32_t  RegLockAddr;
       uint32_t  RESERVED5[3];
  __IO uint32_t  RCADJ;	   
} GCR_TypeDef;

//*****************************************************************************
//
// FLASH Memory Controller 
//
//*****************************************************************************

//
//! \brief Flash Memory Controller (FMC)
//
typedef struct
{
  union {
  __IO uint32_t  ISPCON;
                 struct {
                 __IO uint32_t  ISPEN:1;
                 __IO uint32_t  BS:1;
	                  uint32_t  RESERVED0:2;
                 __IO uint32_t  CFGUEN:1;
	             __IO uint32_t  LDUEN:1;
                 __IO uint32_t  ISPFF:1;
	                  uint32_t  RESERVED1:1;
                 __IO uint32_t  PT:3;
	                  uint32_t  RESERVED2:1;
	             __IO uint32_t  ET:3;
                      uint32_t  RESERVED3:17;
                 } ISPCON_BITS;
  };
  __IO uint32_t  ISPADR;
  __IO uint32_t  ISPDAT;
  union {
  __IO uint32_t  ISPCMD;
                 struct {
                 __IO uint32_t  FCTRL:4;
                 __IO uint32_t  FCEN:1;
                 __IO uint32_t  FOEN:1;
                      uint32_t  RESERVED0:26;
                 } ISPCMD_BITS;
  };
  union {
  __IO uint32_t  ISPTRG;
                 struct {
                 __IO uint32_t  ISPGO:1;
                      uint32_t  RESERVED0:31;
                 } ISPTRG_BITS;
  };
  __I  uint32_t  DFBADR;
  union {
  __IO uint32_t  FATCON;
                 struct {
                 __IO uint32_t  FPSEN:1;
                 __IO uint32_t  FATS:3;
                 __IO uint32_t  LSPEED:1;
                      uint32_t  RESERVED0:27;
                 } FATCON_BITS;
  };
} FMC_TypeDef;

//*****************************************************************************
//
// PWM Controller 
//
//*****************************************************************************

//
//! \brief PWM Generator and Capture Timer
//
typedef struct
{
  union {
  __IO uint32_t  PPR;
                 struct {
                 __IO uint32_t  CP01:8;
                 __IO uint32_t  CP23:8;
                 __IO uint32_t  CP45:8;
                      uint32_t  RESERVED0:8;
                 } PPR_BITS;
  };
  union {
  __IO uint32_t  CSR;
                 struct {
                 __IO uint32_t  CSR0:3;
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  CSR1:3;
                      uint32_t  RESERVED1:1;
                 __IO uint32_t  CSR2:3;
                      uint32_t  RESERVED2:1;
                 __IO uint32_t  CSR3:3;
                      uint32_t  RESERVED3:1;
                 __IO uint32_t  CSR4:3;
                      uint32_t  RESERVED4:1;
                 __IO uint32_t  CSR5:3;
                      uint32_t  RESERVED5:9;
                 } CSR_BITS;
  };
  union {
  __IO uint32_t  PCR;
                 struct {
                 __IO uint32_t  CH0EN:1;
                      uint32_t  DB_MODE:1;
                 __IO uint32_t  CH0INV:1;
                 __IO uint32_t  CH0MOD:1;
                 __IO uint32_t  CH1EN:1;
                      uint32_t  RESERVED0:1;
                 __IO uint32_t  CH1INV:1;
                 __IO uint32_t  CH1MOD:1;
                 __IO uint32_t  CH2EN:1;
                      uint32_t  RESERVED1:1;
                 __IO uint32_t  CH2INV:1;
                 __IO uint32_t  CH2MOD:1;
                 __IO uint32_t  CH3EN:1;
                      uint32_t  RESERVED2:1;
                 __IO uint32_t  CH3INV:1;
                 __IO uint32_t  CH3MOD:1;
                 __IO uint32_t  CH4EN:1;
                      uint32_t  RESERVED3:1;
                 __IO uint32_t  CH4INV:1;
                 __IO uint32_t  CH4MOD:1;
                 __IO uint32_t  CH5EN:1;
                      uint32_t  RESERVED4:1;
                 __IO uint32_t  CH5INV:1;
                 __IO uint32_t  CH5MOD:1;
                 __IO uint32_t  DZEN01:1;
                 __IO uint32_t  DZEN23:1;
                 __IO uint32_t  DZEN45:1;
                 __IO uint32_t  CLRPWM:1;
                 __IO uint32_t  PWMMOD:2;
                 __IO uint32_t  GRP:1;
                 __IO uint32_t  PWMTYPE:1;
                 } PCR_BITS;
  };
  union {
  __IO uint32_t  CNR0;
                 struct {
                 __IO uint32_t  CNR:16;
	                  uint32_t  RESERVED0:16;
                 } CNR0_BITS;
  };
  union {
  __IO uint32_t  CNR1;
                 struct {
                 __IO uint32_t  CNR:16;
	                  uint32_t  RESERVED0:16;
                 } CNR1_BITS;
  };
  union {
  __IO uint32_t  CNR2;
                 struct {
                 __IO uint32_t  CNR:16;
	                  uint32_t  RESERVED0:16;
                 } CNR2_BITS;
  };
  union {
  __IO uint32_t  CNR3;
                 struct {
                 __IO uint32_t  CNR:16;
	                  uint32_t  RESERVED0:16;
                 } CNR3_BITS;
  };
  union {
  __IO uint32_t  CNR4;
                 struct {
                 __IO uint32_t  CNR:16;
	                  uint32_t  RESERVED0:16;
                 } CNR4_BITS;
  };
  union {
  __IO uint32_t  CNR5;
                 struct {
                 __IO uint32_t  CNR:16;
	                  uint32_t  RESERVED0:16;
                 } CNR5_BITS;
  };
  union {
  __IO uint32_t  CMR0;
                 struct {
                 __IO uint32_t  CMR:16;
	                  uint32_t  RESERVED0:16;
                 } CMR0_BITS;
  };
  union {
  __IO uint32_t  CMR1;
                 struct {
                 __IO uint32_t  CMR:16;
	                  uint32_t  RESERVED0:16;
                 } CMR1_BITS;
  };
  union {
  __IO uint32_t  CMR2;
                 struct {
                 __IO uint32_t  CMR:16;
	                  uint32_t  RESERVED0:16;
                 } CMR2_BITS;
  };
  union {
  __IO uint32_t  CMR3;
                 struct {
                 __IO uint32_t  CMR:16;
	                  uint32_t  RESERVED0:16;
                 } CMR3_BITS;
  };
  union {
  __IO uint32_t  CMR4;
                 struct {
                 __IO uint32_t  CMR:16;
	                  uint32_t  RESERVED0:16;
                 } CMR4_BITS;
  };
  union {
  __IO uint32_t  CMR5;
                 struct {
                 __IO uint32_t  CMR:16;
	                  uint32_t  RESERVED0:16;
                 } CMR5_BITS;
  };
	   uint32_t  RESERVED0[6];  

  union {
  __IO uint32_t  PIER;
                 struct {
                 __IO uint32_t  PIE0:1;
                 __IO uint32_t  PIE1:1;
                 __IO uint32_t  PIE2:1;
                 __IO uint32_t  PIE3:1;
                 __IO uint32_t  PIE4:1;
                 __IO uint32_t  PIE5:1;
	                  uint32_t  RESERVED0:2;
                 __IO uint32_t  DIE0:1;
                 __IO uint32_t  DIE1:1;
                 __IO uint32_t  DIE2:1;
                 __IO uint32_t  DIE3:1;
                 __IO uint32_t  DIE4:1;
                 __IO uint32_t  DIE5:1;
	                  uint32_t  RESERVED1:2;
                 __IO uint32_t  BRKIE:1;
                 __IO uint32_t  INT_TYPE:1;
	                  uint32_t  RESERVED2:14;
                 } PIER_BITS;
  };
  union {
  __IO uint32_t  PIIR;
                 struct {
                 __IO uint32_t  PIF0:1;
                 __IO uint32_t  PIF1:1;
                 __IO uint32_t  PIF2:1;
                 __IO uint32_t  PIF3:1;
                 __IO uint32_t  PIF4:1;
                 __IO uint32_t  PIF5:1;
	                  uint32_t  RESERVED0:2;
                 __IO uint32_t  DIF0:1;
                 __IO uint32_t  DIF1:1;
                 __IO uint32_t  DIF2:1;
                 __IO uint32_t  DIF3:1;
                 __IO uint32_t  DIF4:1;
                 __IO uint32_t  DIF5:1;
	                  uint32_t  RESERVED1:2;
                 __IO uint32_t  BKF0:1;
                 __IO uint32_t  BKF1:1;
	                  uint32_t  RESERVED2:14;
                 } PIIR_BITS;
  };
  union {
  __IO uint32_t  POE;
                 struct {
                 __IO uint32_t  PWM0:1;
                 __IO uint32_t  PWM1:1;
                 __IO uint32_t  PWM2:1;
                 __IO uint32_t  PWM3:1;
                 __IO uint32_t  PWM4:1;
                 __IO uint32_t  PWM5:1;
	                  uint32_t  RESERVED0:26;
                 } POE_BITS;
  };
  union {
  __IO uint32_t  PFBCON;
                 struct {
                 __IO uint32_t  BKEN0:1;
                 __IO uint32_t  BKEN1:1;
                 __IO uint32_t  CPO0BKEN:1;
	                  uint32_t  RESERVED0:4;
				 __IO uint32_t  BKF:1;
	                  uint32_t  RESERVED1:16;				 
                 __IO uint32_t  BKO0:1;
                 __IO uint32_t  BKO1:1;
                 __IO uint32_t  BKO2:1;
                 __IO uint32_t  BKO3:1;
                 __IO uint32_t  BKO4:1;
                 __IO uint32_t  BKO5:1;
	                  uint32_t  RESERVED2:2;
                 } PFBCON_BITS;
  };
  union {
  __IO uint32_t  PDZIR;
                 struct {
                 __IO uint32_t  DZI01:8;
                 __IO uint32_t  DZI23:8;
                 __IO uint32_t  DZI45:8;
	                  uint32_t  RESERVED0:8;
                 } PDZIR_BITS;
  };
} PWM_TypeDef;


/*
 * @}
 */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

//*****************************************************************************
//
// Peripheral memory map 
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PPeripheral_memory_map
//! @{
//
//*****************************************************************************

//
// Peripheral and SRAM base address
//
#define SRAM_BASE             ((uint32_t)0x20000000)
#define APB1PERIPH_BASE       ((uint32_t)0x40000000)
#define APB2PERIPH_BASE       ((uint32_t)0x40100000)
#define AHBPERIPH_BASE        ((uint32_t)0x50000000)

//
// Peripheral memory map
//
#define WDT_BASE	          (APB1PERIPH_BASE + 0x04000)
#define TIMER0_BASE	          (APB1PERIPH_BASE + 0x10000)
#define TIMER1_BASE	          (APB1PERIPH_BASE + 0x10020)
#define I2C_BASE	          (APB1PERIPH_BASE + 0x20000)
#define SPI0_BASE	          (APB1PERIPH_BASE + 0x30000)
#define PWM_BASE	          (APB1PERIPH_BASE + 0x40000)
#define UART0_BASE	          (APB1PERIPH_BASE + 0x50000)
#define ACMP_BASE	          (APB1PERIPH_BASE + 0xD0000)
#define ADC_BASE	          (APB1PERIPH_BASE + 0xE0000)

#define GCR_BASE	          (AHBPERIPH_BASE + 0x00000)
#define CLK_BASE	          (AHBPERIPH_BASE + 0x00200)
#define INTID_BASE	          (AHBPERIPH_BASE + 0x00300)
#define GPIO0_BASE	          (AHBPERIPH_BASE + 0x04000)
#define GPIO1_BASE	          (AHBPERIPH_BASE + 0x04040)
#define GPIO2_BASE	          (AHBPERIPH_BASE + 0x04080)
#define GPIO3_BASE	          (AHBPERIPH_BASE + 0x040C0)
#define GPIO4_BASE	          (AHBPERIPH_BASE + 0x04100)
#define GPIO5_BASE	          (AHBPERIPH_BASE + 0x04140)
#define GPIODBNCE_BASE        (AHBPERIPH_BASE + 0x04180)
#define GPIOBIT0_BASE	      (AHBPERIPH_BASE + 0x04200)
#define GPIOBIT1_BASE	      (AHBPERIPH_BASE + 0x04220)
#define GPIOBIT2_BASE	      (AHBPERIPH_BASE + 0x04240)
#define GPIOBIT3_BASE	      (AHBPERIPH_BASE + 0x04260)
#define GPIOBIT4_BASE	      (AHBPERIPH_BASE + 0x04280)
#define FMC_BASE	          (AHBPERIPH_BASE + 0x0C000)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Peripheral declaration 
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Peripheral_declaration
//! @{
//
//***************************************************************************** 
#define WDT                   ((WDT_TypeDef *) WDT_BASE)
#define TIMER0                ((TIMER_TypeDef *) TIMER0_BASE)
#define TIMER1   	          ((TIMER_TypeDef *) TIMER1_BASE)
#define I2C                   ((I2C_TypeDef *) I2C_BASE)
#define SPI                  ((SPI_TypeDef *) SPI0_BASE)
#define PWM                   ((PWM_TypeDef *) PWM_BASE)
#define UART0                 ((UART_TypeDef *) UART0_BASE)
#define ADC                   ((ADC_TypeDef *) ADC_BASE)
#define ACMP                   ((ACMP_TypeDef *) ACMP_BASE)

#define GCR                   ((GCR_TypeDef *) GCR_BASE)
#define CLK                   ((CLK_TypeDef *) CLK_BASE)
#define INTID                 ((INTID_TypeDef *) INTID_BASE)
#define GPIO0                 ((GPIO_TypeDef *) GPIO0_BASE)
#define GPIO1                 ((GPIO_TypeDef *) GPIO1_BASE)
#define GPIO2                 ((GPIO_TypeDef *) GPIO2_BASE)
#define GPIO3                 ((GPIO_TypeDef *) GPIO3_BASE)
#define GPIO4                 ((GPIO_TypeDef *) GPIO4_BASE)
#define GPIO5                 ((GPIO_TypeDef *) GPIO5_BASE)
#define GPIODBNCE             ((GPIODBNCE_TypeDef *) GPIODBNCE_BASE)
#define GPIOBIT0              ((GPIOBIT_TypeDef *) GPIOBIT0_BASE)
#define GPIOBIT1              ((GPIOBIT_TypeDef *) GPIOBIT1_BASE)
#define GPIOBIT2              ((GPIOBIT_TypeDef *) GPIOBIT2_BASE)
#define GPIOBIT3              ((GPIOBIT_TypeDef *) GPIOBIT3_BASE)
#define GPIOBIT4              ((GPIOBIT_TypeDef *) GPIOBIT4_BASE)
#define FMC                   ((FMC_TypeDef *) FMC_BASE)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#define UNLOCKREG(x)        GCR->RegLockAddr  = 0x59; GCR->RegLockAddr = 0x16; GCR->RegLockAddr = 0x88;
#define LOCKREG(x)            GCR->RegLockAddr = 0x00;     
 
//*****************************************************************************
//
//! @I/O routines and constant definitions
//! @{
//
//*****************************************************************************
typedef volatile unsigned char  vu8;
typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
#define M8(adr)  (*((vu8  *) (adr)))
#define M16(adr) (*((vu16 *) (adr)))
#define M32(adr) (*((vu32 *) (adr)))

#define outpw(port,value)	*((volatile unsigned int *)(port))=value
#define inpw(port)			(*((volatile unsigned int *)(port)))
#define outpb(port,value)	*((volatile unsigned char *)(port))=value
#define inpb(port)			(*((volatile unsigned char *)(port)))
#define outps(port,value)	*((volatile unsigned short *)(port))=value
#define inps(port)			(*((volatile unsigned short *)(port)))

#define outp32(port,value)	*((volatile unsigned int *)(port))=value
#define inp32(port)			(*((volatile unsigned int *)(port)))
#define outp8(port,value)	*((volatile unsigned char *)(port))=value
#define inp8(port)			(*((volatile unsigned char *)(port)))
#define outp16(port,value)	*((volatile unsigned short *)(port))=value
#define inp16(port)			(*((volatile unsigned short *)(port)))


#ifndef E_SUCCESS
#define E_SUCCESS 	(0)
#endif
#ifndef NULL
#define NULL        (0)
#endif

#define TRUE	   	(1)
#define FALSE   	(0)

#define ENABLE     (1)
#define DISABLE    (0)

/* Define one bit mask */
#define BIT0	(0x00000001)
#define BIT1	(0x00000002)
#define BIT2	(0x00000004)
#define BIT3	(0x00000008)
#define BIT4	(0x00000010)
#define BIT5	(0x00000020)
#define BIT6	(0x00000040)
#define BIT7	(0x00000080)
#define BIT8	(0x00000100)
#define BIT9	(0x00000200)
#define BIT10	(0x00000400)
#define BIT11	(0x00000800)
#define BIT12	(0x00001000)
#define BIT13	(0x00002000)
#define BIT14	(0x00004000)
#define BIT15	(0x00008000)
#define BIT16	(0x00010000)
#define BIT17	(0x00020000)
#define BIT18	(0x00040000)
#define BIT19	(0x00080000)
#define BIT20	(0x00100000)
#define BIT21	(0x00200000)
#define BIT22	(0x00400000)
#define BIT23	(0x00800000)
#define BIT24	(0x01000000)
#define BIT25	(0x02000000)
#define BIT26	(0x04000000)
#define BIT27	(0x08000000)
#define BIT28	(0x10000000)
#define BIT29	(0x20000000)
#define BIT30	(0x40000000)
#define BIT31	(0x80000000)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif  // __MINI51_H__
