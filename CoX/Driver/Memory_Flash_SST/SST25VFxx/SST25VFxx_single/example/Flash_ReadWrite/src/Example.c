//*****************************************************************************
//
//! \file Example.c
//! \brief the SST25VFxx Example.
//! \version 1.0
//! \date 10/15/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>


#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "SST25VFxx.h"

void UartPrintf(void);

unsigned long ucIDcode;
#define BUFFER_LEN     21
unsigned char ucBuffer[BUFFER_LEN];


//*****************************************************************************
//
//! \brief SST25VFxxReadWrite
//!
//! \return None.
//
//*****************************************************************************
int SST25VFxxReadWrite(void)
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

//*****************************************************************************
//
//! \brief print some data to terminal.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void UartPrintf(void)
{
    unsigned long i;
    //
    //Set System Clock
    //
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    xSysCtlDelay(10000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART0RX, PC10);
    xSPinTypeUART(UART0TX, PC8);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    //
    // Set UART0 clock source.
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_HCLK);

    //
    // Configure 8 bit word length, 1 stop bit,
    // and none parity bit, receive FIFO 1 byte.
    //
    xUARTConfigSet(UART0_BASE, 115200, (xUART_CONFIG_WLEN_8 |
                                        xUART_CONFIG_STOP_1 |
                                        xUART_CONFIG_PAR_NONE));

    xUARTEnable(UART0_BASE, (UART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
}


#undef errno
extern int errno;
extern int  _end;

caddr_t _sbrk ( int incr )
{
  static unsigned char *heap = NULL;
  unsigned char *prev_heap;

  if (heap == NULL) {
    heap = (unsigned char *)&_end;
  }
  prev_heap = heap;

  heap += incr;

  return (caddr_t) prev_heap;
}

int link(char *old, char *new) {
return -1;
}

int _close(int file)
{
  return -1;
}

int _fstat(int file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int file)
{
  return 1;
}

int _lseek(int file, int ptr, int dir)
{
  return 0;
}

int _read(int file, char *ptr, int len)
{
  return 0;
}

int _write(int file, char *ptr, int len) {
	int txCount;

	(void) file;

	for (txCount = 0; txCount < len; txCount++)
	{
		xUARTCharPut(xUART0_BASE,*ptr++);
	}

	return len;
}

void abort(void)
{
  /* Abort called */
  while(1);
}
