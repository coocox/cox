//*****************************************************************************
//
//! \file xcore.h
//! \brief Prototypes for the CPU instruction wrapper functions.
//! \brief Prototypes for the NVIC Interrupt Controller Driver.
//! \brief Prototypes for the SysTick driver.
//! \version 1.0
//! \date 5/13/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#ifndef __XCORE_H__
#define __XCORE_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup COX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CORE
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup XCORE
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup XCORE_Exported_Macros
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Macro to generate an interrupt priority mask based on the number of bits
//! of priority supported by the hardware.
//
//*****************************************************************************
#define XINT_PRIORITY_MASK       ((0xFF << (8 - NUM_PRIORITY_BITS)) & 0xFF)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup XCORE_Exported_APIs
//! @{
//
//*****************************************************************************

extern unsigned long XCPUcpsid(void);
extern unsigned long XCPUcpsie(void);
extern unsigned long XCPUprimask(void);
extern void XCPUwfi(void);
extern unsigned long XCPUbasepriGet(void);
extern void XCPUbasepriSet(unsigned long ulNewBasepri);
extern void XCPUpspSet(unsigned long ulNewPspStack);
extern unsigned long XCPUpspGet(void);
extern void XCPUmspSet(unsigned long ulNewMspStack);
extern unsigned long XCPUmspGet(void);

extern xtBoolean XIntMasterEnable(void);
extern xtBoolean XIntMasterDisable(void);
extern void XIntPriorityGroupingSet(unsigned long ulBits);
extern unsigned long XIntPriorityGroupingGet(void);
extern void XIntPrioritySet(unsigned long ulInterrupt,
                           unsigned char ucPriority);
extern long XIntPriorityGet(unsigned long ulInterrupt);
extern void XIntEnable(unsigned long ulInterrupt);
extern void XIntDisable(unsigned long ulInterrupt);
extern void XIntPendSet(unsigned long ulInterrupt);
extern void XIntPendClear(unsigned long ulInterrupt);
extern void XIntPriorityMaskSet(unsigned long ulPriorityMask);
extern unsigned long XIntPriorityMaskGet(void);

extern void XSysTickEnable(void);
extern void XSysTickDisable(void);
extern void XSysTickIntEnable(void);
extern void XSysTickIntDisable(void);
extern void XSysTickPeriodSet(unsigned long ulPeriod);
extern unsigned long XSysTickPeriodGet(void);
extern unsigned long XSysTickValueGet(void);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __XCORE_H__
