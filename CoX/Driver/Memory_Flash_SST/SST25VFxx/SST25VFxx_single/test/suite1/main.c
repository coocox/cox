#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xsysctl.h"
#include "SST25VFxx.h"
#include <stdio.h>

void UartPrintf(void);
unsigned long ucIDcode;
#define BUFFER_LEN     21
unsigned char ucBuffer[BUFFER_LEN];

//*****************************************************************************
//
//! \brief main
//!
//! \return None.
//
//*****************************************************************************
int main1(void)
{
    int i=0;
    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(8000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    UartPrintf();
    printf("Hello World\r\n");

    for(i=0;i<BUFFER_LEN;i++)
    {
        ucBuffer[i] = i;
    }
    SST25VFxxInit(20000000);
    ucIDcode = 0xAB;
    ucIDcode = SST25VFxxIDGet(0x10);
    printf("ucIDcode = 0x%X\r\n",ucIDcode);
    ucIDcode = SST25VFxxJedecIDGet();
    printf("ucIDcode = 0x%X\r\n",ucIDcode);
    ucIDcode = SST25VFxxStatusRegRead();
    printf("ucIDcode = 0x%X\r\n",ucIDcode);
    SST25VFxxWaitNotBusy();
    printf("Not Busy\r\n");

    SST25VFxxWriteEnable();
    ucIDcode = SST25VFxxStatusRegRead();
    printf("ucIDcode = 0x%X\r\n",ucIDcode);

    SST25VFxxWriteDisable();
    ucIDcode = SST25VFxxStatusRegRead();
    printf("ucIDcode = 0x%X\r\n",ucIDcode);

    SST25VFxxChipErase();
    printf("SST25VFxxChipErase \r\n");

    SST25VFxxWrite(ucBuffer, 0, BUFFER_LEN);
    printf("SST25VFxxWrite(ucBuffer, 0, BUFFER_LEN) \r\n");

    for(i=0;i<BUFFER_LEN;i++)
    {
        ucBuffer[i] = 0;
    }
    printf("ucBuffer clear \r\n");
    for(i=0;i<BUFFER_LEN;i++)
    {
        printf("ucBuffer[%d] = 0x%X\r\n",i,ucBuffer[i]);
    }

    SST25VFxxDataRead(ucBuffer, 0, BUFFER_LEN);
    printf("SST25VFxxDataRead(ucBuffer, 0, BUFFER_LEN) \r\n");

    for(i=0;i<BUFFER_LEN;i++)
    {
        printf("ucBuffer[%d] = 0x%X\r\n",i,ucBuffer[i]);
    }
    printf("float=%10.9f\r\n",3.1415926);
    while(1)
    {

    }
}

