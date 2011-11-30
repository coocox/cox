//*****************************************************************************
//
//! \file SPILoopBack.c
//! \brief example of SPI.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//***************************************************************************** 

//*****************************************************************************
//
//! Include related header files  
//
//*****************************************************************************
#include "DrvSYS.h"
#include "DrvSPI.h"
#include "DrvGPIO.h"

//*****************************************************************************
//
//! \brief SPI LoopBack Example.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void SPILoopBack(void)
{
    uint32_t u32TxData, u32RxData;
     
    //
    // Enable high external clock and use it as system clock (HCLK)
    //
	  DrvSYS_Open(XTL_CLK);

    //
    // Waiting for 12M Xtal stable
    //
    while (DrvSYS_GetChipClockSourceStatus(XTL_CLK) != 1);
     
    //
    // Configure SPI0 related multi-function pins
    //
    DrvGPIO_InitFunction(FUNC_SPI);
    
    //
    // Configure SPI0 as a master, 32-bit transaction
    //
    DrvSPI_Open(eDRVSPI_MASTER, eDRVSPI_TYPE7, 32);
    
    //
    // Enable the automatic slave select function of SS0.
    //
    DrvSPI_EnableAutoSS();
    
    //
    // Set the active level of slave select.
    //
    DrvSPI_SetSlaveSelectActiveLevel(eDRVSPI_ACTIVE_LOW_FALLING);
    
    //
    // SPI clock rate 2MHz
    //
    DrvSPI_SetClockFreq(200000, 0);

    DrvSPI_SetByteReorder(eDRVSPI_BYTE_REORDER);

    //
    // Please connect P0.5 to P0.6 and test! 
    //

    //
    // Clear Tx register of SPI1 to avoid send non-zero data to Master. Just for safe.
    //
    u32TxData = 0x55;

    while(DrvSPI_IsBusy() == TRUE);

    DrvSPI_SetTxRegister(&u32TxData, 1);
    
    //
    // set the GO_BUSY bit of SPI0
    //
    DrvSPI_SetGo();
    
    //
    // Wait until transfer is done
    //
    while(DrvSPI_IsBusy() == TRUE);
    DrvSPI_DumpRxRegister(&u32RxData, 1);

    DrvSPI_Close();
}