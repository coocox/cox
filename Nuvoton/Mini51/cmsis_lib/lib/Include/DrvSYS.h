//*****************************************************************************
//
//! \file DrvSYS.h
//! \brief Contains all functions support for SYS 
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c) Nuvoton Technology Corp. All rights reserved.
//
//*****************************************************************************
#ifndef DRVSYS_H
#define DRVSYS_H

#include "MINI51.h"


//*****************************************************************************
//
//! Macro, type and constant definitions 
//
//*****************************************************************************
#define DRVSYS_MAJOR_NUM 1
#define DRVSYS_MINOR_NUM 01
#define DRVSYS_BUILD_NUM 001

#define DRVSYS_VERSION_NUM				_SYSINFRA_VERSION(DRVSYS_MAJOR_NUM,DRVSYS_MINOR_NUM,DRVSYS_BUILD_NUM)  


#define E_DRVSYS_ERR_UNLOCK_FAIL		_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 1)
#define E_DRVSYS_ERR_LOCK_FAIL			_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 2)
#define E_DRVSYS_ERR_ARGUMENT			_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 3)
#define E_DRVSYS_ERR_IPSRC				_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 4)
#define E_DRVSYS_ERR_IPDIV				_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 5)
#define E_DRVSYS_ERR_OUT_OF_RANGE		_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 6)
#define E_DRVSYS_ERR_CLKSWITCH_FAIL		_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 7)
#define E_DRVSYS_ERR_CLKSSRC_UNSTABLE	_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 8)
#define E_DRVSYS_ERR_32K_CLK_FAIL		_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVSYS, 11)


//
//!  Define System Chip Clock Source                                                                        
//!            Byte3 : HCLK Selection                                                                       
//!            Byte2 : Clock Statu Bit                                                                      
//!            Byte1 : Clock Enable Mask Bit
//!            Byte0 : Clock Enable Bit                                                                     
/
#define XTL_CLK			0x00010301
#define XTL32K_CLK		0x00010302
#define OSC22M_CLK		0x07100404
#define OSC10K_CLK		0x03080808


//
//!  Define IP Clock Source
//!           Byte3 : Reserved
//!           Byte2 : Clcok Select Register Number
//!           Byte1 : Number of shift bits
//!           Byte0 : Clock Selection Mask Bits
//

#define WDT_CLK_SET		0x00010003
#define ADC_CLK_SET		0x00010203
#define TMR0_CLK_SET	0x00010807
#define TMR1_CLK_SET	0x00010C07
#define UART_CLK_SET	0x00011803
#define PWM01_CLK_SET	0x00011C03
#define PWM23_CLK_SET	0x00011E03
#define FRQDIV_CLK_SET	0x00020203
#define PWM45_CLK_SET	0x00020403

//*****************************************************************************
//
//! SYS IP Clcok Divider
//! Byte3 : Reserved
//! Byte2 : Reserved
//! Byte1 : Number of shift bits
//! Byte0 : Clock Divider Mask Bits  
//
//*****************************************************************************
#define HCLK_CLK_DIV	0x0000000F
#define UART_CLK_DIV	0x0000080F
#define ADC_CLK_DIV		0x000010FF


//*****************************************************************************
//
//! Define parameter checking 
//
//*****************************************************************************
#define CHECK_CLK_ALL(ClkSet)				((ClkSet == XTL_CLK)    || \
											 (ClkSet == XTL32K_CLK) || \
											 (ClkSet == OSC22M_CLK) || \
											 (ClkSet == OSC10K_CLK))
#define CHECK_HCLK_SOURCE(HclkSel)			((HclkSel == 7) || (HclkSel == 3) || (HclkSel == 0))
#define CHECK_SYSTICK_SOURCE(TickClkSel)	(!((TickClkSel > 7) || (TickClkSel == 1)))
#define CHECK_FREQ_DIVIDER(Divider)			(!(Divider > 15))
#define CHECK_IP_CLKSRC(IpClkSrc)           ((IpClkSrc == WDT_CLK_SET)     || \
	                                         (IpClkSrc == ADC_CLK_SET)     || \
	                                         (IpClkSrc == TMR0_CLK_SET)    || \
	                                         (IpClkSrc == TMR1_CLK_SET)    || \
	                                         (IpClkSrc == UART_CLK_SET)    || \
	                                         (IpClkSrc == PWM01_CLK_SET)   || \
	                                         (IpClkSrc == PWM23_CLK_SET)   || \
	                                         (IpClkSrc == FRQDIV_CLK_SET)  || \
	                                         (IpClkSrc == PWM45_CLK_SET))

#define CHECK_IP_CLKDIV(IpClkDiv)           ((IpClkDiv == HCLK_CLK_DIV)    || \
	                                         (IpClkDiv == UART_CLK_DIV)    || \
	                                         (IpClkDiv == ADC_CLK_DIV))
	                                                                       

//*****************************************************************************
//
//! IP reset 
//
//*****************************************************************************
typedef enum 
{
    E_SYS_GPIO_RST  = 1,
    E_SYS_TMR0_RST  = 2,
    E_SYS_TMR1_RST  = 3,
    E_SYS_I2C_RST   = 8,
    E_SYS_SPI_RST  = 12,
    E_SYS_UART_RST = 16,
    E_SYS_PWM_RST = 20,
    E_SYS_ACMP_RST  = 22,
    E_SYS_ADC_RST   = 28,
}E_SYS_IP_RST;

//*****************************************************************************
//
//! SYS IP Clcok Selector 
//
//*****************************************************************************

typedef enum 
{
    E_SYS_WDT_CLK   = 0,
    E_SYS_TMR0_CLK  = 2,
    E_SYS_TMR1_CLK  = 3,
    E_SYS_FDIV_CLK  = 6,
    E_SYS_I2C_CLK   = 8,
    E_SYS_SPI_CLK  = 12,
    E_SYS_UART_CLK = 16,
    E_SYS_PWM01_CLK = 20,
    E_SYS_PWM23_CLK = 21,
    E_SYS_PWM45_CLK = 22,
    E_SYS_ADC_CLK   = 28,
    E_SYS_ACMP_CLK  = 30,
    E_SYS_ISP_CLK   = 34,
}E_SYS_IP_CLK;


//*****************************************************************************
//
//! Define callback functions 
//
//*****************************************************************************
typedef void (*BOD_CALLBACK)(void);
typedef void (*PWRWU_CALLBACK)(void);
typedef void (*DRVSYS_IRC_CALLBACK)(uint32_t u32IrcStatus);

//*****************************************************************************
//
//!  Define IRC data structure 
//
//*****************************************************************************
typedef enum 
{
	E_SYS_RETRY_64,
	E_SYS_RETRY_128,
	E_SYS_RETRY_256,
	E_SYS_RETRY_512
} E_SYS_IRC_RETRY;

typedef enum 
{
	E_SYS_LOOP_4,
	E_SYS_LOOP_8,
	E_SYS_LOOP_16,
	E_SYS_LOOP_32
} E_SYS_IRC_LOOP;

typedef struct DRVIRC_STRUCT
{
    E_SYS_IRC_RETRY     u8cRetryCnt;
    E_SYS_IRC_LOOP      u8cLoop;
}STR_IRC_T;


//*****************************************************************************
//
//!  Define GCR functions prototype 
//
//*****************************************************************************
void     DrvSYS_ClearClockSwitchStatus(void);
uint32_t DrvSYS_ClearResetSource(uint32_t u32Src);

void     DrvSYS_Delay(uint32_t us);
void     DrvSYS_DisablePOR(void);

void     DrvSYS_EnablePOR(void);
void     DrvSYS_EnterPowerDown(int32_t i32Active32K);

uint32_t DrvSYS_GetBODState(void);
int32_t  DrvSYS_GetChipClockSourceStatus(uint32_t u32ClkSrc);
uint32_t DrvSYS_GetClockSwitchStatus(void);
uint32_t DrvSYS_GetExtClockFreq(void);
uint32_t DrvSYS_GetHCLKFreq(void);
uint32_t DrvSYS_GetResetSource(void);
uint32_t DrvSYS_GetVersion(void);

int32_t  DrvSYS_IsProtectedRegLocked(void);

int32_t  DrvSYS_LockProtectedReg(void);

int32_t  DrvSYS_Open(uint32_t u32HclkSrc);

uint32_t DrvSYS_ReadProductID(void);
void     DrvSYS_ResetChip(void);
void     DrvSYS_ResetCPU(void);
void     DrvSYS_ResetIP(E_SYS_IP_RST eIpRst);

void     DrvSYS_SelectBODVolt(uint8_t u8Volt);
int32_t  DrvSYS_SelectHCLKSource(uint8_t u8ClkSrcSel);
int32_t  DrvSYS_SelectIPClockSource(uint32_t u32IpClkSrc, uint8_t u8ClkSrcSel);
int32_t  DrvSYS_SelectSysTickSource(uint8_t u8ClkSrcSel);
void     DrvSYS_SetBODFunction(int32_t i32Enable, int32_t i32Mode, BOD_CALLBACK bodcallbackFn);
int32_t  DrvSYS_SetClockDivider(uint32_t u32IpDiv , int32_t i32value);
int32_t  DrvSYS_SetFreqDividerOutput(int32_t i32Flag, uint8_t u8Divider);
void     DrvSYS_SetIPClock(E_SYS_IP_CLK eIpClk, int32_t i32Enable);
int32_t DrvSYS_SetOscCtrl(uint32_t u32ClkSrc, int32_t i32Enable);
void     DrvSYS_SetPowerDownWakeUpInt(int32_t i32Enable, PWRWU_CALLBACK pdwucallbackFn, int32_t i32enWUDelay);

int32_t  DrvSYS_UnlockProtectedReg(void);

int32_t  DrvSYS_EnableAutoTrim(STR_IRC_T *sParam, DRVSYS_IRC_CALLBACK pfncallback);
void     DrvSYS_DisableAutoTrim(void);

#endif

