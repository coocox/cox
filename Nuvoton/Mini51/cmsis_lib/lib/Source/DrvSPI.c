//*****************************************************************************
//
//! \file DrvSPI.c
//! \brief Driver for the SPI Controller.
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//
//*****************************************************************************


//*****************************************************************************
//
//! Include related headers
//
//*****************************************************************************
#include "DrvSPI.h"
#include "DrvSYS.h"
#include "Assert.h"

//*****************************************************************************
//
//! Global file scope (static) variables
//
//*****************************************************************************
typedef struct
{
    uint8_t bInUse;
    PFN_DRVSPI_CALLBACK pfncallback;
    uint32_t u32userData;
//
// Function pointer of the 3-wire SPI start interrupt
//
    PFN_DRVSPI_CALLBACK pfn3WireStartCallBack;
    uint32_t u32ThreeWireStartUserData;
} S_DRVSPI_HANDLE;

static S_DRVSPI_HANDLE g_sSpiHandler;
//*****************************************************************************
//
//! Interrupt Handler
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief SPI0 interrupt handler. Clear the SPI interrupt flag and execute the
//!  callback function. 
//!
//! \param None 
//!
//! \return None.  
//
//*****************************************************************************
void SPI0_IRQHandler(void)
{    
    if( SPI->CNTRL_BITS.IF == 1 ) /* One transaction done interrupt */
    {
        SPI->CNTRL_BITS.IF = 1;   /* write '1' to clear SPI0 interrupt flag */
    
        if(g_sSpiHandler.pfncallback != NULL)
	      {
	        g_sSpiHandler.pfncallback(g_sSpiHandler.u32userData);
	      }
    }
    
    if( SPI->CNTRL2_BITS.SLV_START_INTSTS == 1 ) /* 3-wire SPI start interrupt */
    {
        SPI->CNTRL2_BITS.SLV_START_INTSTS = 1;   /* write '1' to clear SPI0 3-wire start interrupt flag */
    
        if(g_sSpiHandler.pfn3WireStartCallBack != NULL)
        {
            g_sSpiHandler.pfn3WireStartCallBack(g_sSpiHandler.u32ThreeWireStartUserData);
        }
    }
    
}


//*****************************************************************************
//
//! \brief Configure the operation mode, transfer type and bit length of a
//!  transaction of the specified SPI port. The timing waveform types: 
//!
//!
//! \param eMode Specify the operation mode (eDRVSPI_MASTER/eDRVSPI_SLAVE)
//!
//! \param eType Specify the transfer type (eDRVSPI_TYPE0 ~ eDRVSPI_TYPE7)
//!
//! \param i32BitLength Specify the bit length in a transaction (1~32) 
//!
//! \return E_SUCCESS Success.  
//!
//! DRVSPI_TYPE0:          
//!
//!     CS    --|          Active state           |---
//!                _   _   _   _   _   _   _   _  
//!     CLK   ____| |_| |_| |_| |_| |_| |_| |_| |_____
//!               
//!     Tx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |---
//!           
//!     Rx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |-----
//!
//!
//! DRVSPI_TYPE1:          
//!
//!     CS    --|          Active state           |---
//!                _   _   _   _   _   _   _   _  
//!     CLK   ____| |_| |_| |_| |_| |_| |_| |_| |_____
//!               
//!     Tx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |-----
//!           
//!     Rx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |-----
//!
//!
//! DRVSPI_TYPE2:          
//!
//!     CS    --|          Active state           |---
//!                _   _   _   _   _   _   _   _  
//!     CLK   ____| |_| |_| |_| |_| |_| |_| |_| |_____
//!               
//!     Tx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |---
//!           
//!     Rx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |---
//!
//!
//! DRVSPI_TYPE3:          
//!
//!     CS    --|          Active state           |---
//!                _   _   _   _   _   _   _   _  
//!     CLK   ____| |_| |_| |_| |_| |_| |_| |_| |_____
//!               
//!     Tx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |-----
//!           
//!     Rx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |---
//!
//!
//! DRVSPI_TYPE4:          
//!
//!     CS    --|          Active state           |---
//!            ___   _   _   _   _   _   _   _   ______ 
//!     CLK       |_| |_| |_| |_| |_| |_| |_| |_|  
//!               
//!     Tx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |------
//!           
//!     Rx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |----
//!
//!
//! DRVSPI_TYPE5:
//!
//!     CS    --|          Active state           |---
//!            ___   _   _   _   _   _   _   _   ______ 
//!     CLK       |_| |_| |_| |_| |_| |_| |_| |_|  
//!               
//!     Tx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |----
//!           
//!     Rx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |----
//!
//!
//! DRVSPI_TYPE6:
//!
//!     CS    --|          Active state           |---
//!            ___   _   _   _   _   _   _   _   ______ 
//!     CLK       |_| |_| |_| |_| |_| |_| |_| |_|  
//!               
//!     Tx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |------
//!           
//!     Rx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |------
//!
//!
//! DRVSPI_TYPE7:
//!
//!     CS    --|          Active state           |---
//!            ___   _   _   _   _   _   _   _   ______ 
//!     CLK       |_| |_| |_| |_| |_| |_| |_| |_|  
//!               
//!     Tx    ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |----
//!           
//!     Rx    --| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |----
//!
//!
//! Master / Slave Transfer Type Matching Table
//!
//!     DRVSPI_TYPE0 <==> DRVSPI_TYPE3
//!     DRVSPI_TYPE1 <==> DRVSPI_TYPE1
//!     DRVSPI_TYPE2 <==> DRVSPI_TYPE2
//!     DRVSPI_TYPE3 <==> DRVSPI_TYPE0
//!     DRVSPI_TYPE4 <==> DRVSPI_TYPE7
//!     DRVSPI_TYPE5 <==> DRVSPI_TYPE5
//!     DRVSPI_TYPE6 <==> DRVSPI_TYPE6
//!     DRVSPI_TYPE7 <==> DRVSPI_TYPE4
//
//*****************************************************************************
int32_t DrvSPI_Open(E_DRVSPI_MODE eMode, E_DRVSPI_TRANS_TYPE eType, int32_t i32BitLength)
{
    int32_t i32TimeOut;
    
    assert_param(SPI_CHECK_INUSE)
            
    /* Bit length 1 ~ 32 */
    assert_param(SPI_CHECK_BIT_LENGTH)
       
    CLK->APBCLK_BITS.SPI_EN           =1;
    GCR->IPRST_CTL2_BITS.SPI_RST      =1;
    GCR->IPRST_CTL2_BITS.SPI_RST      =0;
    
    /* Check busy*/
    i32TimeOut = 0x10000;
    while(SPI->CNTRL_BITS.GO_BUSY == 1)
    {
        if(i32TimeOut-- <= 0)
        return E_DRVSPI_ERR_BUSY;
    }
    
    g_sSpiHandler.bInUse = TRUE;
    g_sSpiHandler.pfncallback = NULL;
    g_sSpiHandler.u32userData = 0;
    g_sSpiHandler.pfn3WireStartCallBack = NULL;
    g_sSpiHandler.u32ThreeWireStartUserData = 0;
    
    /* "i32BitLength = 0" means 32 bits */
    if(i32BitLength == 32)
    {
        i32BitLength = 0;
    }
    SPI->CNTRL_BITS.TX_BIT_LEN = i32BitLength;
    
    SPI->CNTRL_BITS.SLAVE = eMode;
       
    /* Automatic slave select */
    SPI->SSR_BITS.AUTOSS = 1;
    
    /* Timing waveform types */
   	SPI->CNTRL = (SPI->CNTRL &~0x806) | eType;
       
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Close the specified SPI module and disable the SPI interrupt. 
//!
//! \param None. 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_Close(void)
{
    int32_t i32TimeOut;
    
    g_sSpiHandler.bInUse = FALSE;
    g_sSpiHandler.pfncallback = NULL;
    g_sSpiHandler.u32userData = 0;
    g_sSpiHandler.pfn3WireStartCallBack = NULL;
    g_sSpiHandler.u32ThreeWireStartUserData = 0;

    /* Check SPI state */
    i32TimeOut = 0x10000;
    while(SPI->CNTRL_BITS.GO_BUSY == 1)
    {
        if(i32TimeOut-- <= 0)
            break;
    }
   
   	NVIC_DisableIRQ(SPI_IRQn);
    GCR->IPRST_CTL2_BITS.SPI_RST=1;
    GCR->IPRST_CTL2_BITS.SPI_RST=0;
    CLK->APBCLK_BITS.SPI_EN=0;
}

//*****************************************************************************
//
//! \brief Dertermine to transfer data with LSB first or MSB first 
//!
//! \param None
//!
//! \param eEndian Specify LSB first or MSB first (eDRVSPI_LSB_FIRST /
//!  eDRVSPI_MSB_FIRST) 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_SetEndian(E_DRVSPI_ENDIAN eEndian)
{
   SPI->CNTRL_BITS.LSB = eEndian;   
}

//*****************************************************************************
//
//! \brief Set the bit length of SPI transfer. 
//!
//! \param i32BitLength Specify the bit length (1~32 bits) 
//!
//! \return E_SUCCESS Success.  
//
//*****************************************************************************
int32_t DrvSPI_SetBitLength(int32_t i32BitLength)
{
	  assert_param(SPI_CHECK_BIT_LENGTH)
       
    if(i32BitLength == 32)
        i32BitLength = 0;

    SPI->CNTRL_BITS.TX_BIT_LEN = i32BitLength;
    
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Enable/disable Byte Reorder function. The Byte Reorder function is
//!  supported only in 16-, 24- and 32-bit transaction mode. 
//!
//! \param eOption the options of Byte Reorder function and Byte Suspend
//!  function. 
//!  eDRVSPI_BYTE_REORDER_SUSPEND_DISABLE both Byte Reorder function
//!  and Byte Suspend function are disabled. 
//!  eDRVSPI_BYTE_REORDER_SUSPEND both Byte Reorder function and Byte Suspend 
//!  function are enabled.
//!  eDRVSPI_BYTE_REORDER : only enable the Byte Reorder function. 
//!  eDRVSPI_BYTE_SUSPEND : only enable the Byte Suspend function. The Byte 
//!  Suspend function is only available in 32-bit transaction. 
//!
//! \return E_SUCCESS Success.  
//
//*****************************************************************************
int32_t DrvSPI_SetByteReorder(E_DRVSPI_BYTE_REORDER eOption)
{    
     /* The Byte Suspend function is only available in 32-bit transaction. */
    if( (eOption==eDRVSPI_BYTE_REORDER_SUSPEND)||(eOption==eDRVSPI_BYTE_SUSPEND) )
    {	
    	assert_param(SPI_CHECK_BYTE_REORDER_MIX)
    }
 //
 // The Byte Reorder function is supported only in 16-, 24- and 32-bit transaction mode.
 //
    else if( eOption==eDRVSPI_BYTE_REORDER )    	
    {
    	assert_param(SPI_CHECK_BYTE_REORDER)
    }
    
    SPI->CNTRL_BITS.REORDER = eOption;

    return E_SUCCESS;
}
//*****************************************************************************
//
//! \brief Set the number of clock cycle of the suspend interval. Only for
//!  master mode. The suspend cycle setting is shared with burst mode, byte 
//!  suspend function and FIFO mode.
//!
//! \param i32Interval In burst transfer mode, this value specified the delay
//!  clocks between successive transactions. If the Byte Suspend function is
//!  enabled, it specified the delay clocks among each byte. It could be 2~17
//!  which indicate 2~17 SPI clock cycles.Please refer to TRM for the actual 
//!  suspend interval.
//!
//! \return E_SUCCESS Success.  
//
//*****************************************************************************
int32_t DrvSPI_SetSuspendCycle(int32_t i32Interval)
{
 //
 // In burst mode and byte suspend function, it could be 2~17.
 //    
	  assert_param(SPI_CHECK_BURST_SUS)
               
    SPI->CNTRL_BITS.SP_CYCLE = i32Interval-2;
    return E_SUCCESS;
    
}

//*****************************************************************************
//
//! \brief Set the trigger mode of slave select pin. Only for slave mode. 
//!
//! \param eSSTriggerMode Specify the trigger mode. (eDRVSPI_EDGE_TRIGGER or
//!  eDRVSPI_LEVEL_TRIGGER) 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_SetTriggerMode(E_DRVSPI_SSLTRIG eSSTriggerMode)
{
    SPI->SSR_BITS.SS_LTRIG = eSSTriggerMode;
}

//*****************************************************************************
//
//! \brief Set the active level of slave select. 
//!
//! \param eSSActType Select the active type of slave select pin.
//!  eDRVSPI_ACTIVE_LOW_FALLING Slave select pin is active low in level-trigger
//!  mode; or falling-edge trigger in edge-trigger mode.
//!  eDRVSPI_ACTIVE_HIGH_RISING Slave select pin is active high in level
//! -trigger mode; or rising-edge trigger in edge-trigger mode. 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_SetSlaveSelectActiveLevel(E_DRVSPI_SS_ACT_TYPE eSSActType)
{
    SPI->SSR_BITS.SS_LVL = eSSActType;
}

//*****************************************************************************
//
//! \brief Get the level-trigger transmission status. Only for slave mode. 
//!
//! \return TRUE: The transaction number and the transferred bit length met the
//!  requirements which defines in TX_NUM and TX_BIT_LEN among one transfer.
//!  FALSE: The transaction number or the transferred bit length of one
//!  transaction doesn't meet the requirements.  
//
//*****************************************************************************
uint8_t DrvSPI_GetLevelTriggerStatus(void)
{
    return (SPI->SSR_BITS.LTRIG_FLAG==1?TRUE:FALSE);
}

//*****************************************************************************
//
//! \brief Enable the automatic slave select function and set the specified
//!  slave select pin. Only for master mode. 
//!
//! \param None 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_EnableAutoSS(void)
{
    SPI->SSR_BITS.AUTOSS = 1;
    SPI->SSR_BITS.SSR = 1;
}

//*****************************************************************************
//
//! \brief Disable the Automatic Slave Select function and deselect slave select
//!  pins. Only for master mode. 
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_DisableAutoSS(void)
{
    SPI->SSR_BITS.AUTOSS = 0;
    SPI->SSR_BITS.SSR = 0;
}


//*****************************************************************************
//
//! \brief Set the slave select pins. Only for master mode. In automatic slave
//!  select operation, call this function to select the slave select pin. The
//!  state of slave select pin will be controlled by hardware. In manual slave
//!  select operation, the slave select pin will be set to active state. 
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_SetSS(void)
{
    SPI->SSR_BITS.SSR = 1;
}


//*****************************************************************************
//
//! \brief Set the slave select pin to inactive state. Only for master mode. In 
//! automatic slave select operation, call this function to deselect the slave 
//! select pin. The slave select pin will be set to inactive state.In manual slave
//! select operation, the slave select pin will be set to inactive state.
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_ClrSS(void)
{
    SPI->SSR_BITS.SSR = 0;
}

//*****************************************************************************
//
//! \brief Check the busy status of the specified SPI port. 
//!
//! \param None
//!
//! \return TRUE The SPI port is in busy. 
//!         FALSE The SPI port is not in busy. 
//!  
//
//*****************************************************************************
uint8_t DrvSPI_IsBusy(void)
{
    return ((SPI->CNTRL_BITS.GO_BUSY)?TRUE:FALSE);
}

//*****************************************************************************
//
//! \brief Configure the burst transfer settings. 
//!
//! \param i32BurstCnt Specify the transaction number in one transfer. It
//!  could be 1 or 2.
//!
//! \param i32Interval Specify the delay clocks between successive
//!  transactions. It could be 2~17. 
//!
//! \return E_SUCCESS Success.  
//
//*****************************************************************************
int32_t DrvSPI_BurstTransfer(int32_t i32BurstCnt, int32_t i32Interval)
{
	  assert_param(SPI_CHECK_BRUST_CNT)
    
    SPI->CNTRL_BITS.TX_NUM = i32BurstCnt-1;
    SPI->CNTRL_BITS.SP_CYCLE = i32Interval-2;
    
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Configure the SPI clock. Only for master mode. 
//!
//! \param u32Clock1 Specify the SPI clock rate in Hz. It's the target clock
//!  rate of SPI base clock and variable clock 1.
//!
//! \param u32Clock2 : Specify the SPI clock rate in Hz. It's the target clock
//!  rate of variable clock 2. 
//!
//! \return The actual clock rate of SPI engine clock is returned. SPI engine
//!  clock rate = APB clock rate / ((DIVIDER + 1) * 2) The actual clock rate may
//!  be different to the target SPI clock due to hardware limitation.
//
//*****************************************************************************
uint32_t DrvSPI_SetClockFreq(uint32_t u32Clock1, uint32_t u32Clock2)
{
    uint32_t u32Div;
    uint32_t u32Pclk;
    
    u32Pclk = DrvSYS_GetHCLKFreq();
//
// Initial value
//    
    u32Div = 0xFFFF;

    if(u32Clock2!=0)
    {
        u32Div = (((u32Pclk / u32Clock2) + 1) >> 1) - 1;
        if(u32Div > 65535)
            u32Div = 65535;
        SPI->DIVIDER_BITS.DIVIDER2 = u32Div;
    }
    else
        SPI->DIVIDER_BITS.DIVIDER2 = 0xFFFF;
    
    if(u32Clock1!=0)
    {
        u32Div = (((u32Pclk / u32Clock1) + 1) >> 1) - 1;
        if(u32Div > 0xFFFF)
            u32Div = 0xFFFF;
        SPI->DIVIDER_BITS.DIVIDER1 = u32Div;
    }
    else
        SPI->DIVIDER_BITS.DIVIDER1 = 0xFFFF;
    
    return ( u32Pclk / ((u32Div+1)*2) );
}

//*****************************************************************************
//
//! \brief Get the SPI engine clock rate in Hz. Only for master mode. 
//!
//! \param None
//!
//! \return The current SPI bus clock frequency in Hz.  
//
//*****************************************************************************
uint32_t DrvSPI_GetClock1Freq(void)
{
    uint32_t u32Div;
    uint32_t u32ApbClock;

    u32ApbClock = DrvSYS_GetHCLKFreq();
    u32Div = SPI->DIVIDER_BITS.DIVIDER1;
//
// SPI_CLK = APB_CLK / ((Divider + 1) * 2)
//
    return ((u32ApbClock >> 1) / (u32Div + 1));
}

//*****************************************************************************
//
//! \brief Get the clock rate of variable clock 2 in Hz. Only for master mode. 
//!
//! \param None
//!
//! \return The frequency of variable clock 2 in Hz.  
//
//*****************************************************************************
uint32_t DrvSPI_GetClock2Freq(void)
{
    uint32_t u32Div;
    uint32_t u32ApbClock;

    u32ApbClock = DrvSYS_GetHCLKFreq();
    u32Div = SPI->DIVIDER_BITS.DIVIDER2;
//
// SPI_CLK = APB_CLK / ((Divider + 1) * 2)
//
    return ((u32ApbClock >> 1) / (u32Div + 1));
}


//*****************************************************************************
//
//! \brief Set the variable clock function. Only for master mode. If the bit
//!  pattern of VARCLK is '0', the output frequency of SPICLK is according to
//!  the value of DIVIDER. If the bit pattern of VARCLK is '1', the output
//!  frequency of SPICLK is according to the value of DIVIDER2. 
//!
//! \param bEnable TRUE  -- Enable variable clock function FALSE -- Disable
//!  variable clock function
//!
//! \param u32Pattern Specify the variable clock pattern 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_SetVariableClockFunction(uint8_t bEnable, uint32_t u32Pattern)
{
    SPI->CNTRL_BITS.VARCLK_EN = bEnable;
    SPI->VARCLK = u32Pattern;
}

//*****************************************************************************
//
//! \brief Enable the SPI interrupt of the specified SPI port and install the
//!  callback function. 
//!
//! \param pfnCallback The callback function of SPI interrupt.
//!
//! \param u32UserData The parameter which will be passed to the callback
//!  function. 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_EnableInt(PFN_DRVSPI_CALLBACK pfnCallback, uint32_t u32UserData)
{    
    assert_param(SPI_CHECK_CALLBACK_PR)
    
    g_sSpiHandler.pfncallback = pfnCallback;
    g_sSpiHandler.u32userData = u32UserData;
      
    SPI->CNTRL_BITS.IE = 1;
    
    NVIC_SetPriority(SPI_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(SPI_IRQn);
}   

//*****************************************************************************
//
//! \brief Disable the SPI interrupt. 
//!
//! \param None 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_DisableInt(void)
{
    NVIC_DisableIRQ(SPI_IRQn);
    
    g_sSpiHandler.pfncallback = NULL;
    g_sSpiHandler.u32userData = 0;
    
    SPI->CNTRL_BITS.IE = 0;   
}

//*****************************************************************************
//
//! \brief Return the SPI interrupt flag 
//!
//! \param None
//!
//! \return 0 SPI interrupt doesn't occur
//!         1 SPI interrupt occurs  
//
//*****************************************************************************
uint32_t DrvSPI_GetIntFlag(void)
{
    return (SPI->CNTRL_BITS.IF);
}

//*****************************************************************************
//
//! \brief Clear the SPI interrupt flag 
//!
//! \param None 
//!
//! \return None  
//
//*****************************************************************************
void DrvSPI_ClrIntFlag(void)
{
    SPI->CNTRL_BITS.IF = 1;
}


//*****************************************************************************
//
//! \brief Read data from SPI Rx registers and trigger SPI for next transfer. 
//!
//! \param pu32Data Store the data got from the SPI bus. 
//!
//! \return TRUE The data stored in pu32Data is valid. 
//!         FALSE The data stored in pu32Data is invalid.  
//
//*****************************************************************************
uint8_t DrvSPI_SingleRead(uint32_t *pu32Data)
{
    if(SPI->CNTRL_BITS.GO_BUSY==1)
        return FALSE;

    *pu32Data = SPI->RX0;
    SPI->CNTRL_BITS.GO_BUSY = 1;
    return TRUE;
}
//*****************************************************************************
//
//! \brief Write data to SPI bus and trigger SPI to start transfer. 
//!
//! \param pu32Data Store the data which will be transmitted through the SPI
//!  bus. 
//!
//! \return TRUE The data stored in pu32Data has been transferred.
//!         FALSE The SPI is in busy. The data stored in pu32Data has not been transferred.  
//
//*****************************************************************************

uint8_t DrvSPI_SingleWrite(uint32_t *pu32Data)
{
    if(SPI->CNTRL_BITS.GO_BUSY==1)
        return FALSE;

    SPI->TX0 = *pu32Data;
    SPI->CNTRL_BITS.GO_BUSY = 1;
    return TRUE;
}

//*****************************************************************************
//
//! \brief Read two words of data from SPI Rx registers and then trigger SPI for
//!  next transfer. 
//!
//! \param pu32Buf Store the data got from the SPI bus. 
//!
//! \return TRUE The data stored in pu32Buf is valid.
//!         FALSE The data stored in pu32Buf is invalid.  
//
//*****************************************************************************
uint8_t DrvSPI_BurstRead(uint32_t *pu32Buf)
{
    if(SPI->CNTRL_BITS.GO_BUSY==1)
        return FALSE;

    pu32Buf[0] = SPI->RX0;
    pu32Buf[1] = SPI->RX1;
    SPI->CNTRL_BITS.GO_BUSY = 1;

    return TRUE;
}


//*****************************************************************************
//
//! \brief Write two words of data to SPI bus and then trigger SPI to start
//!  transfer. 
//!
//! \param pu32Buf Store the data which will be transmitted through the SPI
//!  bus. 
//!
//! \return TRUE The data stored in pu32Buf has been transferred.
//!         FALSE The SPI is in busy. The data stored in pu32Buf has not been transferred.  
//
//*****************************************************************************
uint8_t DrvSPI_BurstWrite(uint32_t *pu32Buf)
{
    if(SPI->CNTRL_BITS.GO_BUSY==1)
        return FALSE;

    SPI->TX0 = pu32Buf[0];
    SPI->TX1 = pu32Buf[1];
    SPI->CNTRL_BITS.GO_BUSY = 1;

    return TRUE;
}

//*****************************************************************************
//
//! \brief Read data from Rx registers. This function will not trigger a SPI
//!  data transfer. 
//!
//! \param pu32Buf Store the data got from Rx registers.
//!
//! \param u32DataCount The count of data read from Rx registers. 
//!
//! \return The count of data actually read from Rx registers.  
//
//*****************************************************************************
uint32_t DrvSPI_DumpRxRegister(uint32_t *pu32Buf, uint32_t u32DataCount)
{
    assert_param(SPI_CHECK_SET_DATAREG_NUM)
 
    pu32Buf[0] = SPI->RX0;
	
	  if(u32DataCount == 2)
		pu32Buf[1] = SPI->RX1;

    return u32DataCount;
}

//*****************************************************************************
//
//! \brief Write data to Tx registers. This function will not trigger a SPI data
//!  transfer. 
//!
//! \param pu32Buf Store the data which will be written to Tx registers.
//!
//! \param u32DataCount The count of data write to Tx registers. 
//!
//! \return The count of data actually written to Tx registers.  
//
//*****************************************************************************
uint32_t DrvSPI_SetTxRegister(uint32_t *pu32Buf, uint32_t u32DataCount)
{
    assert_param(SPI_CHECK_SET_DATAREG_NUM)
 
    SPI->TX0 = pu32Buf[0];
	
	if(u32DataCount == 2)
		SPI->TX1 = pu32Buf[1];

    return u32DataCount;
}

//*****************************************************************************
//
//! \brief Set the GO_BUSY bit to trigger a SPI data trasfer. 
//!
//! \param None 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_SetGo(void)
{
    SPI->CNTRL_BITS.GO_BUSY = 1;
}

//*****************************************************************************
//
//! \brief Clear the GO_BUSY bit. 
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_ClrGo(void)
{
    SPI->CNTRL_BITS.GO_BUSY = 0;
}
//*****************************************************************************
//
//! \brief Enable the DIV_ONE feature. The SPI clock rate will be equal to system
//!  clock rate.
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_EnableDivOne(void)
{
    SPI->CNTRL2_BITS.DIV_ONE = 1;
}

//*****************************************************************************
//
//! \brief Disable the DIV_ONE feature. The SPI clock rate is determined by the
//! setting of SPI clock divider.
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_DisableDivOne(void)
{
    SPI->CNTRL2_BITS.DIV_ONE = 0;
}

//*****************************************************************************
//
//! \brief Enable the SPI 3-wire function. In master mode, executing this function
//! is unmeaningful.
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_Enable3Wire(void)
{
    SPI->CNTRL2_BITS.NOSLVSEL = 1;
}

//*****************************************************************************
//
//! \brief Disable the SPI 3-wire function.
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_Disable3Wire(void)
{
    SPI->CNTRL2_BITS.NOSLVSEL = 0;
}

//*****************************************************************************
//
//! \brief Abort transfer when using 3-wire SPI.If using 3-wire SPI as slave, 
//! when slave start interrupt status is set but transfer done flag doesn't be
//! set over a reasonable time, use this function to abort this transfer.
//!
//! \param None.
//!
//! \retur None.  
//
//*****************************************************************************
void DrvSPI_3WireAbort(void)
{
    SPI->CNTRL2_BITS.SLV_ABORT = 1;
}

//*****************************************************************************
//
//! \brief Enable the 3-wire SPI start interrupt of SPI and install the callback
//! function.
//!
//! \param pfnCallback The callback function of 3-wire SPI start interrupt.
//!
//! \param u32UserData The parameter which will be passed to the callback function. 
//!
//! \retur None.  
//
//*****************************************************************************
void DrvSPI_Enable3WireStartInt(PFN_DRVSPI_CALLBACK pfnCallback, uint32_t u32UserData)
{    
    assert_param(SPI_CHECK_CALLBACK_PR)
    g_sSpiHandler.pfn3WireStartCallBack = pfnCallback;
    g_sSpiHandler.u32ThreeWireStartUserData = u32UserData;
        
    SPI->CNTRL2_BITS.SSTA_INTEN = 1;
    
    NVIC_SetPriority(SPI_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(SPI_IRQn);   
}   

//*****************************************************************************
//
//! \brief Disable the 3-wire SPI start interrupt.
//!
//! \param None
//!
//! \return None  
//
//*****************************************************************************
void DrvSPI_Disable3WireStartInt(void)
{
    g_sSpiHandler.pfn3WireStartCallBack = NULL;
    g_sSpiHandler.u32ThreeWireStartUserData = 0;
    
    SPI->CNTRL2_BITS.SSTA_INTEN = 0;
    NVIC_DisableIRQ(SPI_IRQn);   
}

//*****************************************************************************
//
//! \brief Get the 3-wire SPI start interrupt status.
//!
//! \param None
//!
//! \return 0: SPI start interrupt doesn't occur.
//!         1: SPI start interrupt occurs.  
//
//*****************************************************************************
uint32_t DrvSPI_Get3WireStartIntFlag(void)
{
    return (SPI->CNTRL2_BITS.SLV_START_INTSTS);
}

//*****************************************************************************
//
//! \brief Clear the 3-wire SPI start interrupt status. 
//!
//! \param None 
//!
//! \return None.  
//
//*****************************************************************************
void DrvSPI_Clr3WireStartIntFlag(void)
{
    SPI->CNTRL2_BITS.SLV_START_INTSTS = 1;
}

//*****************************************************************************
//
//! \brief Get the version number of Mini51 SPI driver. 
//!
//! \param None 
//!
//! \return Version number.  
//
//*****************************************************************************
uint32_t DrvSPI_GetVersion(void)
{
    return DRVSPI_VERSION_NUM;
}