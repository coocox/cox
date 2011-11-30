//*****************************************************************************
//
//! \file system_MINI51.h
//! \brief CMSIS ARM Cortex-M0 Device Peripheral Access Layer Header File
//! \version V1.00
//! \date 07. April 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//***************************************************************************** 

#ifndef __SYSTEM_MINI51_H
#define __SYSTEM_MINI51_H

#ifdef __cplusplus
 extern "C" {
#endif 

//*****************************************************************************
//
//! Macro Definition
//
//*****************************************************************************

//#define DEBUG_ENABLE_SEMIHOST   /* To enable semihosted. !!!The SEMIHOSTED of startup_MINI51.s must be {TRUE} */

//
//! Using UART0
//
#define DEBUG_PORT   0          /* 0:UART0 */

//
//! Define SYSCLK
//
#define __XTAL12M      (12000000UL)
#define __XTAL32K      (32768UL)
#define __IRC22M    	(22118400UL)
#define __IRC10K    	(10000UL)
#define __XTAL		__XTAL12M
#define __HSI       	(__IRC22M)      /* Factory Default is internal 22MHz */

extern uint32_t SystemCoreClock;                   /*!< System Clock Frequency (Core Clock) */
extern uint32_t CyclesPerUs;                       /* Cycles per micro second */

//*****************************************************************************
//
//! \brief Setup the microcontroller system Initialise GPIO directions 
//!  and values
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
extern void SystemInit(void);


//*****************************************************************************
//
//! \brief Updates the SystemCoreClock with current core Clock retrieved  
//!  from cpu registers.
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif

