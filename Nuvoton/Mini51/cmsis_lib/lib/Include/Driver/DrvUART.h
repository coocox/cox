//*****************************************************************************
//
//! \file DrvUART.h
//! \brief This file provides all the UART firmware functions.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************
#ifndef __DRVUART_H__
#define __DRVUART_H__

#include "MINI51.h"

#ifdef  __cplusplus
extern "C"
{
#endif

//
//! Define Version number 
//
#define DRVUART_MAJOR_NUM   1
#define DRVUART_MINOR_NUM   00
#define DRVUART_BUILD_NUM   001

//
//! Version define with SysInfra 
//
#define DRVUART_VERSION_NUM     _SYSINFRA_VERSION(DRVUART_MAJOR_NUM, DRVUART_MINOR_NUM, DRVUART_BUILD_NUM)

//
//! Define Error Code
//                               
#define E_DRVUART_ERR_TIMEOUT               _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 1)
#define E_DRVUART_ERR_PORT_INVALID          _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 2)
#define E_DRVUART_ERR_PARITY_INVALID        _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 3)
#define E_DRVUART_ERR_DATA_BITS_INVALID     _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 4)
#define E_DRVUART_ERR_STOP_BITS_INVALID     _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 5)
#define E_DRVUART_ERR_TRIGGERLEVEL_INVALID  _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 6)
#define E_DRVUART_ARGUMENT                  _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 7)



//
//! Define UART Macro 
//
#define _DRVUART_SENDBYTE(u32Port,byData)							outp32(UART0_BASE + u32Port, (byData))
#define _DRVUART_RECEIVEBYTE(u32Port)								inp32(UART0_BASE + u32Port)
#define _DRVUART_SET_DIVIDER(u32Port,u16Divider)				outp32(UART0->BAUD + u32Port,(0x3<<28)|(u16Divider))    /* Using Mode3 */
#define _DRVUART_RECEIVEAVAILABLE(u32Port)						(inp32(UART0->FSR + u32Port) & 0x3F00)>>8
#define _DRVUART_WAIT_TX_EMPTY(u32Port)							(inp32(UART0->FSR + u32Port) & (1<<28))>>28


typedef void (PFN_DRVUART_CALLBACK)(uint32_t userData);

//
//! Define IRDA Operation direction 
//
#define MODE_TX  1
#define MODE_RX  2

//
//! Port Number 
//
typedef enum 
{
    UART_PORT0 = 0x000,
} E_UART_PORT;


//
//! define UART line status control 
//
typedef enum 
{
     DRVUART_WAKEUPINT  =    BIT6,      /* Wake up interrupt */
     DRVUART_BUFERRINT  =    BIT5,      /* Buffer Error Interrupt */
     DRVUART_TOUTINT    =    BIT4,      /* RX Time out Interrupt */
     DRVUART_MOSINT     =    BIT3,      /* MODEM Status Interrupt */
     DRVUART_RLSINT     =    BIT2,      /* Receive Line Status Interrupt*/
     DRVUART_THREINT    =    BIT1,      /* Transmit Holding Register Empty Interrupt */
     DRVUART_RDAINT     =    BIT0       /* Receive Data Available Interrupt */
} E_INT_SOURCE;


//
//! DATA BIT 
//
typedef enum 
{
     DRVUART_DATABITS_5   =    0x0,
     DRVUART_DATABITS_6   =    0x1,
     DRVUART_DATABITS_7   =    0x2,
     DRVUART_DATABITS_8   =    0x3

} E_DATABITS_SETTINS;

//
//! PARITY Setting 
//
typedef enum 
{
     DRVUART_PARITY_NONE   =    0x0,
     DRVUART_PARITY_ODD    =    0x1,
     DRVUART_PARITY_EVEN   =    0x3,
     DRVUART_PARITY_MARK   =    0x5,
     DRVUART_PARITY_SPACE  =    0x7
} E_PARITY_SETTINS;

//
//! STOP BIT 
//
typedef enum 
{
     DRVUART_STOPBITS_1     =   0x0,
     DRVUART_STOPBITS_1_5   =   0x1,
     DRVUART_STOPBITS_2     =   0x1
} E_STOPBITS_SETTINS;


//
//! FIFO Select 
//
typedef enum 
{
    DRVUART_FIFO_1BYTES     = 0x0, 
    DRVUART_FIFO_4BYTES     = 0x1,
    DRVUART_FIFO_8BYTES     = 0x2,
    DRVUART_FIFO_14BYTES    = 0x3
} E_FIFO_SETTINGS;




//
//! Function Selection 
//
typedef enum 
{
    FUN_UART    = 0, 
    FUN_IRCR    = 2,
    FUN_RS485   = 3
} E_UART_FUNC;

//
//! Define RS485 operation mode 
//
typedef enum 
{
    MODE_RS485_NMM = 1, 
    MODE_RS485_AAD = 2,
    MODE_RS485_AUD = 4
} E_MODE_RS485;
                                    


//
//! Define UART data structure 
//
typedef struct DRVUART_STRUCT
{
    uint32_t            u32BaudRate;
    E_DATABITS_SETTINS  u8cDataBits;
    E_STOPBITS_SETTINS  u8cStopBits;
    E_PARITY_SETTINS    u8cParity;
    E_FIFO_SETTINGS     u8cRxTriggerLevel;
    uint8_t             u8TimeOut ;
}STR_UART_T;

//
//! Define IRDA data structure 
//
typedef struct IRCR_STRUCT
{
    uint8_t         u8cTXSelect;
    uint8_t         u8cInvTX;
    uint8_t         u8cInvRX;
}STR_IRCR_T;

//
//! Define RS485 Setting structure 
//
typedef struct RS485_STRUCT
{
    uint8_t         u8cModeSelect;
    uint8_t         u8cAddrEnable;
    uint8_t         u8cAddrValue;
    uint8_t         u8cDelayTime;
    uint8_t         u8cRxDisable;
}STR_RS485_T;

//
//! Define UART Macro assert_param check
//
#define CHECK_UART_PORT(port)			((port == UART_PORT0))
#define CHECK_UART_PARITY(parity)		((parity==DRVUART_PARITY_NONE) || (parity==DRVUART_PARITY_EVEN) || (parity==DRVUART_PARITY_ODD) || (parity==DRVUART_PARITY_MARK) || (parity==DRVUART_PARITY_SPACE))
#define CHECK_UART_DATABIT(databit)	((databit==DRVUART_DATABITS_5) || (databit==DRVUART_DATABITS_6) || (databit==DRVUART_DATABITS_7) || (databit==DRVUART_DATABITS_8))
#define CHECK_UART_STOPBIT(stopbit)	((stopbit==DRVUART_STOPBITS_1) || (stopbit==DRVUART_STOPBITS_2) || (stopbit==DRVUART_STOPBITS_1_5))
#define CHECK_UART_RXTRIGGERLEVEL(trigger)	((trigger==DRVUART_FIFO_1BYTES) || (trigger==DRVUART_FIFO_4BYTES) || (trigger==DRVUART_FIFO_8BYTES) || (trigger==DRVUART_FIFO_14BYTES))


//
//! Define UART functions prototype 
//
void DrvUART_Close(E_UART_PORT u32Port);
void DrvUART_DisableInt(E_UART_PORT u32Port,uint32_t u32InterruptFlag);
void DrvUART_GetCTS(E_UART_PORT u32Port,uint8_t *pu8CTSValue,uint8_t *pu8CTSChangeState);
void DrvUART_SetClcok(uint8_t u8ClcokSrc, uint8_t u8ClcokDiv);
void DrvUART_SetRTS(E_UART_PORT u32Port,uint8_t u8Value,uint16_t u16TriggerLevel);
void DrvUART_SetFnIRDA(E_UART_PORT u32Port,STR_IRCR_T *str_IRCR );
void DrvUART_SetFnRS485(E_UART_PORT u32Port,STR_RS485_T *str_RS485);
void DrvUART_EnableInt(E_UART_PORT u32Port,uint32_t u32InterruptFlag,PFN_DRVUART_CALLBACK pfncallback);

int32_t DrvUART_GetIntStatus(E_UART_PORT u32Port,uint32_t u32InterruptFlag);
int32_t DrvUART_Read(E_UART_PORT u32Port,uint8_t *pu8RxBuf,uint32_t u32ReadBytes);
int32_t DrvUART_Open(E_UART_PORT u32Port, STR_UART_T *sParam);
int32_t DrvUART_Write(E_UART_PORT u32Port,uint8_t *pu8TxBuf,uint32_t u32WriteBytes);
int32_t DrvUART_GetVersion(void);
int32_t DrvUART_kbhit(void);
uint32_t DrvUART_IsIntEnabled(E_UART_PORT u32Port,uint32_t u32InterruptFlag);
uint32_t DrvUART_ClearIntFlag(E_UART_PORT u32Port,uint32_t u32InterruptFlag);



#ifdef  __cplusplus
}
#endif

#endif

//*****************************************************************************
//
//! (C) COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************






