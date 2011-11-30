//*****************************************************************************
//
//! \file DrvUART.c
//! \brief This file provides all the UART firmware functions.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************  
#include <stdio.h>
#include "MINI51.h"

//*****************************************************************************
//
//! Includes of local headers
//
//*****************************************************************************
#include "DrvUART.h"
#include "DrvSYS.h"
#include "Assert.h"


//*****************************************************************************
//
//! Macro, type and constant definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! Global variables
//
//*****************************************************************************
static PFN_DRVUART_CALLBACK *g_pfnUART0callback = NULL;


//*****************************************************************************
//
//! \brief Interrupt Handler
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void UART0_IRQHandler(void)
{
    uint32_t u32uart0IntStatus;

    u32uart0IntStatus = UART0->ISR;

    if(g_pfnUART0callback != NULL)
    {
        g_pfnUART0callback(u32uart0IntStatus);
    }
}


//*****************************************************************************
//
//!  \brief The function is used to set Baud Rate register according user's settings
//!
//! \param clk Uart Source Clock
//! \param baudRate User seting BaudRate
//! \param UART_TypeDef *tUART Get the pointer of register definition
//!
//! ----BaudRate Configure-------
//! Mode    DIV_X_EN    DIV_X_ONE   Divider X   BRD (Baud rate equation)
//! -----------------------------------------------------------------------
//! 0       Disable 0   B          A  UART_CLK / [16 * (A+2)]
//! 1       Enable  0   B          A  UART_CLK / [(B+1) * (A+2)] , B must >= 8
//! 2       Enable  1   Don't care A  UART_CLK / (A+2), A must >=3
//!
//! \return None 
//
//*****************************************************************************
static void BaudRateCalculator(uint32_t clk, uint32_t baudRate, UART_TypeDef *tUART)
{
    int32_t tmp;
    int32_t div;

    if ((((clk / baudRate)%16) < 2)  &&  (clk>(baudRate*16*2)))  /* Source Clock mod 16 < 2 => Using Divider X =16 (MODE#0) */ 
    {                                 
        tUART->BAUD_BITS.DIV_X_EN = 0;
        tUART->BAUD_BITS.DIV_X_ONE   = 0;
        tmp = clk / baudRate/16  -2;
    }
    else                              /* Source Clock mod 16 >3 => Up 5% Error BaudRate */
    {
        tUART->BAUD_BITS.DIV_X_EN = 1;           /* Try to Set Divider X = 1 (MODE#2)*/
        tUART->BAUD_BITS.DIV_X_ONE   = 1;
        tmp = clk / baudRate  -2;

        if(tmp > 0xFFFF)              /* If Divider > Range  */
        {
            tUART->BAUD_BITS.DIV_X_EN = 1;       /* Try to Set Divider X up 10 (MODE#1) */
            tUART->BAUD_BITS.DIV_X_ONE   = 0;

            for(div = 8; div <16;div++)
            {
                if(((clk / baudRate)%(div+1))<3)
                {
                    tUART->BAUD_BITS.DIVIDER_X   = div;
                    tmp = clk / baudRate / (div+1) -2;
                    break;
                }
            }
        }
    }

    tUART->BAUD_BITS.BRD = tmp; 

}


//*****************************************************************************
//
//! \brief The function is used to get Uart clock 
//!
//! \param None 
//!
//! \return Current Uart Clock  (Hz) 
//
//*****************************************************************************

static uint32_t GetUartClock(void)
{
    uint32_t clk =0 , div;

    div = CLK->CLKDIV_BITS.UART_N;                    /* According PLL Clock and UART_Divider to get clock */                                                 
                                                    
                                                    /* Check UART Clock Source Setting */
    if(CLK->CLKSEL1_BITS.UART_S == 0)         
    {
        clk = DrvSYS_GetExtClockFreq()/ (div+1);;   /* Get External Clock From DrvSYS Setting */
    }
    else if(CLK->CLKSEL1_BITS.UART_S == 1)
    {
        clk = DrvSYS_GetHCLKFreq()/ (div+1);
    }
    else
        clk = __IRC22M/ (div+1);                    /* Clock 22Mhz  */

    return clk;
}

 
//*****************************************************************************
//
//! \brief The function is used to set RTS information 
//!
//! \param u32Port UART Channel:  UART_PORT0 / UART_PORT1 / UART_PORT2
//! \param uint8_t RTS Value 
//!   Set 0: Drive RTS pin to logic 1 (If the LEV_RTS set to low level triggered).  
//!          Drive RTS pin to logic 0 (If the LEV_RTS set to high level triggered)  
//!   Set 1: Drive RTS pin to logic 0 (If the LEV_RTS set to low level triggered)   
//!          Drive RTS pin to logic 1 (If the LEV_RTS set to high level triggered) 
//!   Note. Lev_RTS is RTS Trigger Level. 0 is low level and 1 is high level 
//! \param u16TriggerLevel RTS Trigger Level :DRVUART_FIFO_1BYTES to 
//!   DRVUART_FIFO_14BYTES
//!
//! \return None  
//
//*****************************************************************************
void DrvUART_SetRTS(E_UART_PORT u32Port,uint8_t u8Value,uint16_t u16TriggerLevel)
{
    
    UART_TypeDef * tUART;

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port);  

    tUART->MCR_BITS.RTS = u8Value;

    tUART->FCR_BITS.RTS_TRI_LEV = u16TriggerLevel;
}   
    
//*****************************************************************************
//
//! \brief The function is used to initialize UART. It consists of baud-rate,
//!  parity, data-bits, stop-bits, rx-trigger-level and timeout interval
//!  settings.  
//!
//! \param u32Port UART Channel:  UART_PORT0 
//! \param sParam the struct parameter to configure UART
//!           include of                                            
//!           u32BaudRate    - Baud rate                            
//!           u8cParity - DRVUART_PARITY_NONE / DRVUART_PARITY_EVEN / 
//!                       DRVUART_PARITY_ODD                
//!           8cDataBits - DRVUART_DATA_BITS_5 / DRVUART_DATA_BITS_6 
//!                        DRVUART_DATA_BITS_7 / DRVUART_DATA_BITS_8 
//!           u8cStopBits - DRVUART_STOPBITS_1 / STOPBITS_1_5 / STOPBITS_2 
//!           8cRxTriggerLevel   - DRVUART_FIFO_1BYTES to DRVUART_FIFO_62BYTES 
//!           u8TimeOut - Time out value     
//!
//! \return  E_SUCCESS  
//
//*****************************************************************************
int32_t DrvUART_Open(E_UART_PORT u32Port, STR_UART_T *sParam)
{

    UART_TypeDef * tUART;
   
    /*-----------------------------------------------------------------------------------------------------*/
    /* Check UART port                                                                                     */
    /*-----------------------------------------------------------------------------------------------------*/
	assert_param(CHECK_UART_PORT(u32Port));


    /*-----------------------------------------------------------------------------------------------------*/
    /* Check the supplied parity                                                                           */
    /*-----------------------------------------------------------------------------------------------------*/
	assert_param(CHECK_UART_PARITY(sParam->u8cParity));


    /*-----------------------------------------------------------------------------------------------------*/
    /* Check the supplied number of data bits                                                              */
    /*-----------------------------------------------------------------------------------------------------*/
	assert_param(CHECK_UART_DATABIT(sParam->u8cDataBits));

	
    /*-----------------------------------------------------------------------------------------------------*/
    /* Check the supplied number of stop bits                                                              */
    /*-----------------------------------------------------------------------------------------------------*/
	assert_param(CHECK_UART_STOPBIT(sParam->u8cStopBits));  


    /*-----------------------------------------------------------------------------------------------------*/
    /* Check the supplied nember of trigger level bytes                                                    */
    /*-----------------------------------------------------------------------------------------------------*/
	assert_param(CHECK_UART_RXTRIGGERLEVEL(sParam->u8cRxTriggerLevel));              


    /* Reset IP */
    GCR->IPRST_CTL2_BITS.UART_RST = 1;
    GCR->IPRST_CTL2_BITS.UART_RST = 0;
    
    /* Enable UART clock */
    CLK->APBCLK_BITS.UART_EN = 1;
	
    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port); 

    /* Tx FIFO Reset & Rx FIFO Reset & FIFO Mode Enable */
    tUART->FCR_BITS.TFR =1;
    tUART->FCR_BITS.RFR =1;

    /* Set Rx Trigger Level */
    tUART->FCR_BITS.RFITL = sParam->u8cRxTriggerLevel;  
    
    /* Set Parity & Data bits & Stop bits */
	tUART->LCR = (tUART->LCR & ~0x3f) | (sParam->u8cParity<<3) | (sParam->u8cStopBits<<2) | sParam->u8cDataBits;
        
    /* Set Time-Out */
    tUART->TOR_BITS.TOIC =sParam->u8TimeOut;

    /* Set BaudRate */
    BaudRateCalculator(GetUartClock(), sParam->u32BaudRate, tUART);

    return E_SUCCESS;
}


//*****************************************************************************
//
//! \brief The function is used to disable UART clock, disable ISR and clear
//!  callback function pointer after checking the TX empty. 
//!
//! \param u32Port UART Channel:  UART_PORT0 
//!
//! \return None 
//
//*****************************************************************************
void DrvUART_Close(E_UART_PORT u32Port)
{
	assert_param(CHECK_UART_PORT(u32Port));
	
    while(!UART0->FSR_BITS.TE_FLAG);
    CLK->APBCLK_BITS.UART_EN = 0;
    g_pfnUART0callback = NULL;
    NVIC_DisableIRQ(UART0_IRQn);      
    
}

//*****************************************************************************
//
//! \brief The function is used to enable specified UART interrupt, install the
//!  callback function and enable NVIC UART IRQ 
//!  
//! \note When enable DRVUART_THREINT interrupt source, the interrup will 
//!  happen continouly if TX_FIFO is empty. Remind you thant be careful to 
//!  use it. Please reference TRM to get more information.
//!
//! \param u32Port UART Channel:  UART_PORT0
//! \param u32InterruptFlag
//!  DRVUART_LININT/DRVUART_WAKEUPINT/DRVUART_BUFERRINT/DRVUART_RLSINT
//!  DRVUART_MOSINT/DRVUART_THREINT/DRVUART_RDAINT/DRVUART_TOUTINT
//! \param pfncallback A function pointer for callback function
//!
//! \return None 
//
//*****************************************************************************
void
DrvUART_EnableInt(
    E_UART_PORT   u32Port,
    uint32_t  u32InterruptFlag,
    PFN_DRVUART_CALLBACK pfncallback
)
{
    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));
    
    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port); 

	tUART->IER = (tUART->IER & ~0x7f) | u32InterruptFlag;
	tUART->IER_BITS.TIME_OUT_EN  =(u32InterruptFlag & DRVUART_TOUTINT)?1:0;      /* Time-out count enable */

	/* Install Callback function */
    g_pfnUART0callback = pfncallback; 
    NVIC_EnableIRQ(UART0_IRQn); 
    
}

//*****************************************************************************
//
//! \brief The function is used to get the "interrupt enable" status 
//!
//! \param u32Port UART Channel:  UART_PORT0
//! \param u32InterruptFlag
//!  DRVUART_LININT/DRVUART_WAKEUPINT/DRVUART_BUFERRINT/DRVUART_RLSINT
//!  DRVUART_MOSINT/DRVUART_THREINT/DRVUART_RDAINT/DRVUART_TOUTINT
//!
//! \return Specified Interrupt Flag Set or clear 
//
//*****************************************************************************                                                                  
uint32_t DrvUART_IsIntEnabled(E_UART_PORT   u32Port,uint32_t u32InterruptFlag)
{

	assert_param(CHECK_UART_PORT(u32Port));

    /* Read IER Register and check specified flag is enable */
    return ((UART0->IER &
     (u32InterruptFlag & (DRVUART_WAKEUPINT | DRVUART_BUFERRINT | 
            DRVUART_TOUTINT | DRVUART_MOSINT | DRVUART_RLSINT| DRVUART_THREINT | DRVUART_RDAINT))))?1:0;

}

//*****************************************************************************
//
//! \brief The function is used to disable UART specified interrupt, uninstall
//!  the call back function and disable NVIC UART IRQ 
//!
//! \param u32Port UART Channel:  UART_PORT0 / UART_PORT1 / UART_PORT2
//! \param u32InterruptFlag
//!  DRVUART_LININT/DRVUART_WAKEUPINT/DRVUART_BUFERRINT/DRVUART_RLSINT
//!  DRVUART_MOSINT/DRVUART_THREINT/DRVUART_RDAINT/DRVUART_TOUTINT
//!
//! \return None 
//
//*****************************************************************************
void DrvUART_DisableInt(E_UART_PORT u32Port,uint32_t u32InterruptFlag)
{

	assert_param(CHECK_UART_PORT(u32Port));

	/* Disable Counter Enable */
    if(u32InterruptFlag & DRVUART_TOUTINT)
		UART0->IER_BITS.RTO_IEN = 0;
    
    /* Disable Callback function and NVIC */
	UART0->IER &= ~u32InterruptFlag;
    g_pfnUART0callback = NULL;
    NVIC_DisableIRQ(UART0_IRQn);   

}

//*****************************************************************************
//
//! \brief The function is used to clear UART specified interrupt flag 
//!
//! \param u32Port UART Channel:  UART_PORT0 / UART_PORT1 / /UART_PORT2
//! \param u32InterruptFlag DRVUART_MOSINT/DRVUART_RLSINT/DRVUART_THREINT
//!  DRVUART_RDAINT/DRVUART_TOUTINT
//!
//! \return E_SUCCESS      Successful 
//
//*****************************************************************************
uint32_t DrvUART_ClearIntFlg(E_UART_PORT    u32Port,uint32_t u32InterruptFlag)
{
    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port); 

    if((u32InterruptFlag & DRVUART_RDAINT) == DRVUART_RDAINT)               /* clear Rx read Interrupt */      
        tUART->RBR;

    if((u32InterruptFlag & DRVUART_THREINT) == DRVUART_THREINT)             /* clear Tx empty Interrupt */     
    {
        tUART->THR = 0;                                                     /* Write Data to TX FIFO to clear INT Flag */
    }   

    if((u32InterruptFlag & DRVUART_RLSINT)  == DRVUART_RLSINT)              /* clear Receive Line Status Interrupt */      
    {
        tUART->FSR_BITS.BIF = 1;
        tUART->FSR_BITS.FEF = 1;
        tUART->FSR_BITS.PEF = 1;
    }

    if((u32InterruptFlag & DRVUART_MOSINT)  == DRVUART_MOSINT)              /* clear Modem Interrupt */    
        tUART->MSR_BITS.DCTSF = 1;

    if((u32InterruptFlag & DRVUART_TOUTINT) == DRVUART_TOUTINT)             /* clear Time-out Interrupt */     
        tUART->RBR;

    if((u32InterruptFlag & DRVUART_BUFERRINT)  == DRVUART_BUFERRINT)        /* clear Buffer ErrorInterrupt */      
    {
        tUART->FSR_BITS.TX_OVER_IF = 1;
        tUART->FSR_BITS.RX_OVER_IF = 1;
    }


    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief The function is used to get the interrupt status 
//!
//! \param u32Port UART Channel:  UART_PORT0 / UART_PORT1 / UART_PORT2
//! \param u32InterruptFlag DRVUART_MOSINT / DRVUART_RLSINT / DRVUART_THREINT
//!  DRVUART_RDAINT/DRVUART_TOUTINT
//!
//! \return 
//!           0: The specified interrupt is not happened.                                               
//!           1: The specified interrupt is happened.                                                   
//!           E_DRVUART_ARGUMENT: Error Parameter  
//
//*****************************************************************************
int32_t DrvUART_GetIntStatus(E_UART_PORT u32Port,uint32_t u32InterruptFlag)
{

    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port); 

    
    switch(u32InterruptFlag)
    {
        case DRVUART_MOSINT:                        /* MODEM Status Interrupt */
                return tUART->ISR_BITS.MODEM_INT;
        
        case DRVUART_RLSINT:                        /* Receive Line Status Interrupt */
                return tUART->ISR_BITS.RLS_INT;

        case DRVUART_THREINT:                       /* Transmit Holding Register Empty Interrupt */
                return tUART->ISR_BITS.THRE_INT;

        case DRVUART_RDAINT:                        /* Receive Data Available Interrupt */
                return tUART->ISR_BITS.RDA_INT;

        case DRVUART_TOUTINT:                       /* Time-out Interrupt */
                return tUART->ISR_BITS.TOUT_INT;

        case DRVUART_BUFERRINT:                     /* Buffer Error Interrupt */
                return tUART->ISR_BITS.BUF_ERR_INT;
		

        default:
            return E_DRVUART_ARGUMENT;
    }
    
}

//*****************************************************************************
//
//! \brief The function is used to get CTS pin value and detect CTS change state
//!  
//!
//! \param u32Port UART Channel:  UART_PORT0 / UART_PORT1
//! \param pu8CTSValue Buffer to store the CTS Value return current CTS pin
//!  state
//! \param pu8CTSChangeState Buffer to store the CTS Change State return CTS pin
//!  status is changed or not 1:Changed 0:Not yet
//!
//! \return None 
//
//*****************************************************************************
void DrvUART_GetCTSInfo(E_UART_PORT u32Port,uint8_t *pu8CTSValue,   uint8_t *pu8CTSChangeState)
{
    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port);  

    *pu8CTSValue        = tUART->MSR_BITS.CTS_ST;
    *pu8CTSChangeState  = tUART->MSR_BITS.DCTSF;
}   

//*****************************************************************************
//
//! \brief The function is used to read Rx data from RX FIFO and the data will
//!  be stored in pu8RxBuf 
//!
//! \param u32Port UART Channel:  UART_PORT0
//! \param pu8RxBuf Specify the buffer to receive the data of receive FIFO
//! \param u32ReadBytes Specify the bytes number of data.
//!
//! \return E_SUCCESS 
//!         E_DRVUART_ERR_TIMEOUT: FIFO polling timeout 
//
//***************************************************************************** 
int32_t DrvUART_Read(E_UART_PORT    u32Port,uint8_t *pu8RxBuf, uint32_t u32ReadBytes)
{
    uint32_t  u32Count, u32delayno;

    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port);  

    for (u32Count=0; u32Count < u32ReadBytes; u32Count++)
    {
         u32delayno = 0;
         while (tUART->FSR_BITS.RX_EMPTY ==1)                        /* Check RX empty => failed */     
         {
            u32delayno++;        
            if ( u32delayno >= 0x40000000 )        
                return E_DRVUART_ERR_TIMEOUT;               
         }
         pu8RxBuf[u32Count] = tUART->RBR;                      /* Get Data from UART RX  */
    }

    return E_SUCCESS;
    
}


//*****************************************************************************
//
//! \brief The function is to write data to TX buffer to transmit data by UART
//!
//! \note In IrDA Mode, the BAUD RATE configure MUST to use MODE # 0 
//!
//! \param u32Port UART Channel:  UART_PORT0
//! \param pu8RxBuf Specify the buffer to send the data to transmission FIFO.
//! \param u32ReadBytes Specify the byte number of data.
//!
//! \return E_SUCCESS  
//!         E_DRVUART_ERR_TIMEOUT: FIFO polling timeout
//
//*****************************************************************************
int32_t DrvUART_Write(E_UART_PORT   u32Port,uint8_t *pu8TxBuf,  uint32_t u32WriteBytes)
{
    uint32_t  u32Count, u32delayno;

    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port);  

    for (u32Count=0; u32Count<u32WriteBytes; u32Count++)
    {
       u32delayno = 0;
       while (tUART->FSR_BITS.TE_FLAG !=1)                               /* Wait Tx empty and Time-out manner */
       {
            u32delayno++;
            if ( u32delayno >= 0x40000000 )             
               return E_DRVUART_ERR_TIMEOUT;               
                   
       }
       tUART->THR = pu8TxBuf[u32Count];                        /* Send UART Data from buffer */
    }

    return E_SUCCESS;
    
  
}

//*****************************************************************************
//
//! \brief The function is to configure IRDA relative settings.It consists of 
//! TX or RX mode and Inverse TX or RX signals.
//!
//! \param u32Port UART Channel:  UART_PORT0 / UART_PORT1 / UART_PORT2
//! \param STR_IRCR_T It includes of  
//!                    u8cTXSelect: 1: Enable Irda transmit function.(TX mode)
//!                                 0: Disable Irda transmit function.(RX mode) 
//!                    u8cInvTX: Inverse TX signal                            
//!                    u8cInvRX: Inverse RX signal
//!
//! \return None  
//
//*****************************************************************************
void DrvUART_SetFnIRDA(E_UART_PORT u32Port,STR_IRCR_T *str_IRCR )
{
    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port);  

    tUART->FUN_SEL_BITS.FUN_SEL   = FUN_IRCR;                             /* Enable IrDA function and configure */
    tUART->IRCR_BITS.TX_SELECT   = (str_IRCR->u8cTXSelect) ?1:0;
    tUART->IRCR_BITS.INV_TX      = str_IRCR->u8cInvTX ;
    tUART->IRCR_BITS.INV_RX      = str_IRCR->u8cInvRX ;
}

//*****************************************************************************
//
//! \brief The function is to Set RS485 Control Register 
//!
//! \param u32Port UART Channel:  UART_PORT0
//! \param STR_RS485_T Ther stucture of RS485 
//!           It includes of                                               
//!              u8cModeSelect: MODE_RS485_AUD / MODE_RS485_AAD            
//!                             MODE_RS485_NMM                             
//!              u8cAddrEnable: Enable or Disable RS-485 Address Detection 
//!              u8cAddrValue:  Match Address Value                        
//!              u8cDelayTime:  Set transmit delay time value              
//!              u8cRxDisable:  Enable or Disable receiver function  
//!
//! \return None  
//
//*****************************************************************************
void DrvUART_SetFnRS485(E_UART_PORT u32Port,STR_RS485_T *str_RS485)
{
    
    UART_TypeDef * tUART;

	assert_param(CHECK_UART_PORT(u32Port));

    tUART = (UART_TypeDef *)((uint32_t)UART0 + u32Port);  

    tUART->FUN_SEL_BITS.FUN_SEL           = FUN_RS485;                    /* Enable RS485 function and configure */
	tUART->FCR_BITS.RX_DIS               =  str_RS485->u8cRxDisable;
    tUART->ALT_CSR_BITS.RS485_ADD_EN      =  str_RS485->u8cAddrEnable?1:0;
    tUART->ALT_CSR_BITS.ADDR_MATCH        =  str_RS485->u8cAddrValue;
    tUART->ALT_CSR_BITS.RS485_NMM         = (str_RS485->u8cModeSelect & MODE_RS485_NMM)?1:0; 
    tUART->ALT_CSR_BITS.RS485_AAD         = (str_RS485->u8cModeSelect & MODE_RS485_AAD)?1:0; 
    tUART->ALT_CSR_BITS.RS485_AUD         = (str_RS485->u8cModeSelect & MODE_RS485_AUD)?1:0; 
    tUART->TOR_BITS.DLY                  =  str_RS485->u8cDelayTime;    
    tUART->MCR_BITS.LEV_RTS = 0;
} 


//*****************************************************************************
//
//! \brief The function is used to get  DrvUART Version Number 
//!
//! \param None 
//!
//! \return Version Number  
//
//*****************************************************************************
int32_t DrvUART_GetVersion(void)
{
    return DRVUART_VERSION_NUM;
    
}


//*****************************************************************************
//
//! (C) COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************



