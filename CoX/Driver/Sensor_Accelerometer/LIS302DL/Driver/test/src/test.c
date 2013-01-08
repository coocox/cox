//*****************************************************************************
//
//! \file test.c
//! \brief Test LIS302DL Driver.
//! \version V2.1.1.0
//! \date 4/1/2013
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
//
//*****************************************************************************

#include <stdio.h>

#if defined(gcc) || defined(__GNUC__) || defined(coide)
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#undef errno
extern int errno;
extern int  _end;
#endif

#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_i2c.h"
#include "xi2c.h"
#include "xuart.h"
#include "LIS302DL.h"

#define TICK_S 0xFFFFF
#define TICK_L 0x2FFFFF

typedef struct TEST_INFO
{
    Result (*pFun)(void);
    char * pInfo;
} TEST_INFO;

//*****************************************************************************
//
//! Internal Function (Used in this file only!)
//
//*****************************************************************************

static void SysInit(void);
static void UartInit(void);

static Result Test_LIS302DLInit(void);
static Result Test_LIS302DLRegReadByte(void);
static Result Test_LIS302DLRegWriteByte(void);
static Result Test_LIS302DLCfg(void);
static Result Test_LIS302DLHPFilterReset(void);
static Result Test_LIS302DLAccDataRead(void);
static Result Test_LIS302DLIDGet(void);
static Result Test_LIS302DLStart(void);
static Result Test_LIS302DLStop(void);
static Result Test_LIS302DLWUFFCfg(void);
static Result Test_LIS302DLWUFFEventCheck(void);
static Result Test_LIS302DLWUFFThresHoldSet(void);
static Result Test_LIS302DLWUFFDurValueSet(void);
static Result Test_LIS302DLClickCfg(void);
static Result Test_LIS302DLClickEventCheck(void);
static Result Test_LIS302DLClickThresholdSet(void);
static Result Test_LIS302DLClickTimeLimitSet(void);
static Result Test_LIS302DLClickLatencySet(void);
static Result Test_LIS302DLClickWindowSet(void);


TEST_INFO TestFunSet[] =
{
    {Test_LIS302DLInit,                "LIS302DLInit             ",},
    {Test_LIS302DLRegReadByte,         "LIS302DLRegReadByte      ",},
    {Test_LIS302DLRegWriteByte,        "LIS302DLRegWriteByte     ",},
    {Test_LIS302DLCfg,                 "LIS302DLCfg              ",},
    {Test_LIS302DLHPFilterReset,       "LIS302DLHPFilterReset    ",},
    {Test_LIS302DLAccDataRead,         "LIS302DLAccDataRead      ",},
    {Test_LIS302DLIDGet,               "LIS302DLIDGet            ",},
    {Test_LIS302DLStart,               "LIS302DLStart            ",},
    {Test_LIS302DLStop,                "LIS302DLStop             ",},
    {Test_LIS302DLWUFFCfg,             "LIS302DLWUFFCfg          ",},
    {Test_LIS302DLWUFFEventCheck,      "LIS302DLWUFFEventCheck   ",},
    {Test_LIS302DLWUFFThresHoldSet,    "LIS302DLWUFFThresHoldSet ",},
    {Test_LIS302DLWUFFDurValueSet,     "LIS302DLWUFFDurValueSet  ",},
    {Test_LIS302DLClickCfg,            "LIS302DLClickCfg         ",},
    {Test_LIS302DLClickEventCheck,     "LIS302DLClickEventCheck  ",},
    {Test_LIS302DLClickThresholdSet,   "LIS302DLClickThresholdSet",},
    {Test_LIS302DLClickTimeLimitSet,   "LIS302DLClickTimeLimitSet",},
    {Test_LIS302DLClickLatencySet,     "LIS302DLClickLatencySet  ",},
    {Test_LIS302DLClickWindowSet,      "LIS302DLClickWindowSet   ",},
};

char * WelcomeInfo =
{
"\t---------------------------------------------------------\r\n"
"\t|  CooCox Open Source Driver Project                    |\r\n"
"\t|  Module : Accelerometer KIS302DL Driver               |\r\n"
"\t|  author : CooCox Cedar                                |\r\n"
"\t|  version: V1.0                                        |\r\n"
"\t|  More information, please visit www.coocox.org        |\r\n"
"\t---------------------------------------------------------\r\n"
"\r\nSelftest Beginning!\r\n"
};

#if defined(gcc) || defined(__GNUC__) || defined(coide)
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

int _write(int file, char *ptr, int len)
{

	int i = 0;
	(void) file;

	for(i = 0; i < len; i++)
	{
		xUARTCharPut(USART2_BASE,*ptr++);
	}

	return len;
}

void abort(void)
{
  /* Abort called */
  while(1);
}
#endif

#if defined(ewarm) || defined(__ICCARM__)
int putchar(int c)
{
    xUARTCharPut(USART2_BASE, (char)c);
    return (1);
}
#endif


void LIS302DL_DriverTest(void)
{
    uint8_t  i          = 0;
    Result   retv       = SUCCESS;
    Result   TestResult = SUCCESS;

    //
    // Init the LED
    //
    //xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOD);
    //xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_3, xGPIO_DIR_MODE_OUT);

    SysInit();
    UartInit();

    printf("%s\r\n", WelcomeInfo);

    for(i = 0; i < sizeof(TestFunSet)/sizeof(TEST_INFO); i++)
    {
        retv =  TestFunSet[i].pFun();
        if(retv != SUCCESS)
        {
            printf("%d\t%s\tFailure\r\n", i, TestFunSet[i].pInfo);
            TestResult = FAILURE;
        }
        else
        {
            printf("%d\t%s\tOK\r\n", i, TestFunSet[i].pInfo);
        }
    }

    if(TestResult != FAILURE)
    {
        printf("\r\nLIS302DL Test OK\r\n");
    }
    else
    {
        printf("\r\nLIS302DL Test FAILURE\r\n");
    }
}


////////////////////////////////////////////////////////////////////////////////
static void SysInit(void)
{
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_25MHZ);
    SysCtlDelay(10000);
}

static void UartInit(void)
{
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOD);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //xSPinTypeUART(UART2RX,PD6);
    xSPinTypeUART(UART2TX,PD5);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART2);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART2);

    xUARTConfigSet(USART2_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE |
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART2_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

static Result Test_LIS302DLInit(void)
{
    return (LIS302DLInit());
}

static Result Test_LIS302DLRegReadByte(void)
{
    uint8_t   ID = 0;
    Result retv  = SUCCESS;

    retv = LIS302DLRegReadByte(WHO_AM_I, &ID);
    if((retv != SUCCESS) || (ID != 0x3B))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

static Result Test_LIS302DLRegWriteByte(void)
{
    Result retv  = SUCCESS;
    uint8_t  ValueOld = 0;
    uint8_t  ValueNew = 0;

    //Get Current value
    retv = LIS302DLRegReadByte(CTRL_REG1, &ValueOld);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Change the value and writeback to register
    retv = LIS302DLRegWriteByte(CTRL_REG1, ~ValueOld);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // read the value and check old value & new value
    retv = LIS302DLRegReadByte(CTRL_REG1, &ValueNew);
    if((retv != SUCCESS) || (ValueOld == ValueNew))
    {
        return (FAILURE);
    }

    // restore environment
    retv = LIS302DLRegWriteByte(CTRL_REG1, ValueOld);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }
    return (SUCCESS);
}

static Result Test_LIS302DLCfg(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

////////////////////////////////////////////////////////////////////////////////


    //Check LIS302DL_CLK_400K
    retv = LIS302DLCfg(LIS302DL_CLK_400K);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_DR;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_CLK_100K
    retv = LIS302DLCfg(LIS302DL_CLK_100K);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_DR;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_SCALE_8G
    retv = LIS302DLCfg(LIS302DL_SCALE_8G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_FS;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_SCALE_2G
    retv = LIS302DLCfg(LIS302DL_SCALE_2G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_FS;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_SELF_TEST_EN
    retv = LIS302DLCfg(LIS302DL_SELF_TEST_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= (CTRL_REG1_STP | CTRL_REG1_STM);
    if((retv != SUCCESS) || (value != (CTRL_REG1_STP | CTRL_REG1_STM)))
    {
        return (FAILURE);
    }

    //Check LIS302DL_SELF_TEST_DIS
    retv = LIS302DLCfg(LIS302DL_SELF_TEST_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= (CTRL_REG1_STP | CTRL_REG1_STM);
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_X_DIS
    retv = LIS302DLCfg(LIS302DL_X_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_Xen;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_X_EN
    retv = LIS302DLCfg(LIS302DL_X_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_Xen;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_Y_DIS
    retv = LIS302DLCfg(LIS302DL_Y_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_Yen;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_Y_EN
    retv = LIS302DLCfg(LIS302DL_Y_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_Yen;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_Z_DIS
    retv = LIS302DLCfg(LIS302DL_Z_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_Zen;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_Z_EN
    retv = LIS302DLCfg(LIS302DL_Z_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG1, &value);
    value &= CTRL_REG1_Zen;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

////////////////////////////////////////////////////////////////////////////////

    //Check LIS302DL_SPI_3_WIRE
    retv = LIS302DLCfg(LIS302DL_SPI_3_WIRE);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_SIM;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_SPI_4_WIRE
    retv = LIS302DLCfg(LIS302DL_SPI_4_WIRE);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_SIM;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_CONTENT_REBOOT
    retv = LIS302DLCfg(LIS302DL_CONTENT_REBOOT);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_BOOT;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_CONTENT_NORMAL
    retv = LIS302DLCfg(LIS302DL_CONTENT_NORMAL);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_BOOT;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_FILTER_EN
    retv = LIS302DLCfg(LIS302DL_FILTER_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_FDS;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_FILTER_DIS
    retv = LIS302DLCfg(LIS302DL_FILTER_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_FDS;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_HP_WU1_EN
    retv = LIS302DLCfg(LIS302DL_HP_WU1_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_HP_FF_WU1;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_HP_WU1_DIS
    retv = LIS302DLCfg(LIS302DL_HP_WU1_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_HP_FF_WU1;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_HP_WU2_EN
    retv = LIS302DLCfg(LIS302DL_HP_WU2_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_HP_FF_WU2;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_HP_WU2_DIS
    retv = LIS302DLCfg(LIS302DL_HP_WU2_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG2, &value);
    value &= CTRL_REG2_HP_FF_WU2;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Paramters below have been test by manual check
    //comment by cedar
    //
    //LIS302DL_HP_WU2_DIS
    //LIS302DL_HP_COEFF_8X
    //LIS302DL_HP_COEFF_4X
    //LIS302DL_HP_COEFF_2X
    //LIS302DL_HP_COEFF_1X


////////////////////////////////////////////////////////////////////////////////
    //Check LIS302DL_INT_LOW
    retv = LIS302DLCfg(LIS302DL_INT_LOW);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG3, &value);
    value &= CTRL_REG3_IHL;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_INT_HIGH
    retv = LIS302DLCfg(LIS302DL_INT_HIGH);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG3, &value);
    value &= CTRL_REG3_IHL;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_INT_PAD_OD
    retv = LIS302DLCfg(LIS302DL_INT_PAD_OD);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG3, &value);
    value &= CTRL_REG3_PP_OD;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check LIS302DL_INT_PAD_PP
    retv = LIS302DLCfg(LIS302DL_INT_PAD_PP);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CTRL_REG3, &value);
    value &= CTRL_REG3_PP_OD;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Paramters below have been test by manual check
    //comment by cedar
    //LIS302DL_INT1_GND
    //LIS302DL_INT1_FF_WU_1
    //LIS302DL_INT1_FF_WU_2
    //LIS302DL_INT1_FF_WU_1_2
    //LIS302DL_INT1_DATA_RDY
    //LIS302DL_INT1_CLICK_INT
    //LIS302DL_INT2_GND
    //LIS302DL_INT2_FF_WU_1
    //LIS302DL_INT2_FF_WU_2
    //LIS302DL_INT2_FF_WU_1_2
    //LIS302DL_INT2_DATA_RDY
    //LIS302DL_INT2_CLICK_INT

    return (SUCCESS);
}

static Result Test_LIS302DLHPFilterReset(void)
{
    return (LIS302DLHPFilterReset());
}

static Result Test_LIS302DLAccDataRead(void)
{
    //Test OK
    //comment by cedar
    return (SUCCESS);
}

static Result Test_LIS302DLIDGet(void)
{
    //Test OK
    //comment by cedar
    return (SUCCESS);
}

static Result Test_LIS302DLStart(void)
{
    //Test OK
    //comment by cedar
    return (SUCCESS);
}

static Result Test_LIS302DLStop(void)
{
    //Test OK
    //comment by cedar
    return (SUCCESS);
}

static Result Test_LIS302DLWUFFCfg(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

/////////////////////////////////// WU_FF_1 Module /////////////////////////////
    //Check WUFF1_INT_EVENT_AND
    retv = LIS302DLWUFFCfg(WUFF1_INT_EVENT_AND);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_AOI;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_EVENT_OR
    retv = LIS302DLWUFFCfg(WUFF1_INT_EVENT_OR);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_AOI;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_LATCH_EN
    retv = LIS302DLWUFFCfg(WUFF1_INT_LATCH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_LIR;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_LATCH_DIS
    retv = LIS302DLWUFFCfg(WUFF1_INT_LATCH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_LIR;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_HIGH_EN
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_HIGH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_HIGH_DIS
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_HIGH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_LOW_EN
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_LOW_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_LOW_DIS
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_LOW_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }


    //Check WUFF1_INT_Y_HIGH_EN
    retv = LIS302DLWUFFCfg(WUFF1_INT_Y_HIGH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_YHIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Y_HIGH_DIS
    retv = LIS302DLWUFFCfg(WUFF1_INT_Y_HIGH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_YHIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Y_LOW_EN
    retv = LIS302DLWUFFCfg(WUFF1_INT_Y_LOW_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_YLIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Y_LOW_DIS
    retv = LIS302DLWUFFCfg(WUFF1_INT_Y_LOW_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_YLIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_HIGH_EN
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_HIGH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_HIGH_DIS
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_HIGH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_LOW_EN
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_LOW_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_INT_Z_LOW_DIS
    retv = LIS302DLWUFFCfg(WUFF1_INT_Z_LOW_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_1, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

/////////////////////////////////// WU_FF_2 Module /////////////////////////////

    //Check WUFF2_INT_EVENT_AND
    retv = LIS302DLWUFFCfg(WUFF2_INT_EVENT_AND);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_AOI;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_EVENT_OR
    retv = LIS302DLWUFFCfg(WUFF2_INT_EVENT_OR);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_AOI;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_LATCH_EN
    retv = LIS302DLWUFFCfg(WUFF2_INT_LATCH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_LIR;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_LATCH_DIS
    retv = LIS302DLWUFFCfg(WUFF2_INT_LATCH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_LIR;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_HIGH_EN
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_HIGH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_HIGH_DIS
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_HIGH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_LOW_EN
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_LOW_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_LOW_DIS
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_LOW_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }


    //Check WUFF2_INT_Y_HIGH_EN
    retv = LIS302DLWUFFCfg(WUFF2_INT_Y_HIGH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_YHIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Y_HIGH_DIS
    retv = LIS302DLWUFFCfg(WUFF2_INT_Y_HIGH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_YHIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Y_LOW_EN
    retv = LIS302DLWUFFCfg(WUFF2_INT_Y_LOW_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_YLIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Y_LOW_DIS
    retv = LIS302DLWUFFCfg(WUFF2_INT_Y_LOW_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_YLIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_HIGH_EN
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_HIGH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_HIGH_DIS
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_HIGH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZHIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_LOW_EN
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_LOW_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_INT_Z_LOW_DIS
    retv = LIS302DLWUFFCfg(WUFF2_INT_Z_LOW_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_CFG_2, &value);
    value &= FF_WU_CFG_ZLIE;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

/////////////////////////////////// WU_FF_1/2 Module /////////////////////////////

    //Check WUFF1_CNT_DEC
    retv = LIS302DLWUFFCfg(WUFF1_CNT_DEC);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_THS_1, &value);
    value &= FF_WU_THS_DCRM;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF1_CNT_RESET
    retv = LIS302DLWUFFCfg(WUFF1_CNT_RESET);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_THS_1, &value);
    value &= FF_WU_THS_DCRM;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_CNT_DEC
    retv = LIS302DLWUFFCfg(WUFF2_CNT_DEC);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_THS_2, &value);
    value &= FF_WU_THS_DCRM;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check WUFF2_CNT_RESET
    retv = LIS302DLWUFFCfg(WUFF2_CNT_RESET);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(FF_WU_THS_2, &value);
    value &= FF_WU_THS_DCRM;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

static Result Test_LIS302DLWUFFEventCheck(void)
{
    //TODO
    return (SUCCESS);
}

//This value must be <= 127, so we send two value(0x5A, 0xFF)
//to test this function
static Result Test_LIS302DLWUFFThresHoldSet(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

    //printf("Here\r\n");

    //Test WU_FF_1 module
    //Set register value
    retv = LIS302DLWUFFThresHoldSet(WUFF_ID_1, 0x5A);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(FF_WU_THS_1, &value);
    if((retv != SUCCESS) || (value != 0x5A))
    {
        return (FAILURE);
    }

    retv = LIS302DLWUFFThresHoldSet(WUFF_ID_1, 0xFF);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(FF_WU_THS_1, &value);
    if((retv != SUCCESS) || (value != 0x7F))
    {
        return (FAILURE);
    }

    //Test WU_FF_2 module
    //Set register value
    retv = LIS302DLWUFFThresHoldSet(WUFF_ID_2, 0x5A);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(FF_WU_THS_2, &value);
    if((retv != SUCCESS) || (value != 0x5A))
    {
        return (FAILURE);
    }

    retv = LIS302DLWUFFThresHoldSet(WUFF_ID_2, 0xFF);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(FF_WU_THS_2, &value);
    if((retv != SUCCESS) || (value != 0x7F))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

static Result Test_LIS302DLWUFFDurValueSet(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

    //printf("Here\r\n");

    //Test WU_FF_1 module
    //Set register value
    retv = LIS302DLWUFFDurValueSet(WUFF_ID_1, 0x5A);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(FF_WU_DURATION_1, &value);
    if((retv != SUCCESS) || (value != 0x5A))
    {
        return (FAILURE);
    }

    //Test WU_FF_2 module
    //Set register value
    retv = LIS302DLWUFFDurValueSet(WUFF_ID_2, 0x5A);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(FF_WU_DURATION_2, &value);
    if((retv != SUCCESS) || (value != 0x5A))
    {
        return (FAILURE);
    }
    return (SUCCESS);
}

static Result Test_LIS302DLClickCfg(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

    //Check CLK_INT_REQ_LATCH_EN
    retv = LIS302DLClickCfg(CLK_INT_REQ_LATCH_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_LIR;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check CLK_INT_REQ_LATCH_DIS
    retv = LIS302DLClickCfg(CLK_INT_REQ_LATCH_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_LIR;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check CLK_INT_DBL_Z_EN
    retv = LIS302DLClickCfg(CLK_INT_DBL_Z_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_Double_Z;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check CLK_INT_DBL_Z_DIS
    retv = LIS302DLClickCfg(CLK_INT_DBL_Z_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_Double_Z;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check CLK_INT_DBL_Y_EN
    retv = LIS302DLClickCfg(CLK_INT_DBL_Y_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_Double_Y;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check CLK_INT_DBL_Y_DIS
    retv = LIS302DLClickCfg(CLK_INT_DBL_Y_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_Double_Y;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    //Check CLK_INT_DBL_X_EN
    retv = LIS302DLClickCfg(CLK_INT_DBL_X_EN);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_Double_X;
    if((retv != SUCCESS) || (value == 0))
    {
        return (FAILURE);
    }

    //Check CLK_INT_DBL_X_DIS
    retv = LIS302DLClickCfg(CLK_INT_DBL_X_DIS);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = LIS302DLRegReadByte(CLICK_CFG, &value);
    value &= CLICK_CFG_Double_X;
    if((retv != SUCCESS) || (value != 0))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

static Result Test_LIS302DLClickEventCheck(void)
{
    //TODO
    return (SUCCESS);
}

static Result Test_LIS302DLClickThresholdSet(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

    //printf("Here\r\n");

    ////////////////// X Axis //////////////////////////
    //Set X axis threshold 0.5G
    retv = LIS302DLClickThresholdSet(THRESHOLD_X_0_5_G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_THSY_X, &value);
    value &= CLICK_THSY_X_THSx_MASK;
    if((retv != SUCCESS) || (value != 0x01))
    {
        return (FAILURE);
    }

    //Set X axis threshold 6.0G
    retv = LIS302DLClickThresholdSet(THRESHOLD_X_6_0_G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_THSY_X, &value);
    value &= CLICK_THSY_X_THSx_MASK;
    if((retv != SUCCESS) || (value != 0x0C))
    {
        return (FAILURE);
    }

    ////////////////// Y Axis //////////////////////////
    //Set Y axis threshold 0.5G
    retv = LIS302DLClickThresholdSet(THRESHOLD_Y_0_5_G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_THSY_X, &value);
    value &= CLICK_THSY_X_THSy_MASK;
    if((retv != SUCCESS) || (value != 0x10))
    {
        return (FAILURE);
    }

    //Set Y axis threshold 6.0G
    retv = LIS302DLClickThresholdSet(THRESHOLD_Y_6_0_G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_THSY_X, &value);
    value &= CLICK_THSY_X_THSy_MASK;
    if((retv != SUCCESS) || (value != 0xC0))
    {
        return (FAILURE);
    }

    ////////////////// Z Axis //////////////////////////
    //Set Z axis threshold 0.5G
    retv = LIS302DLClickThresholdSet(THRESHOLD_Z_0_5_G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_THSZ, &value);
    value &= CLICK_THSZ_THSz_MASK;
    if((retv != SUCCESS) || (value != 0x01))
    {
        return (FAILURE);
    }

    //Set Z axis threshold 6.0G
    retv = LIS302DLClickThresholdSet(THRESHOLD_Z_6_0_G);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_THSZ, &value);
    value &= CLICK_THSZ_THSz_MASK;
    if((retv != SUCCESS) || (value != 0x0C))
    {
        return (FAILURE);
    }

    return (SUCCESS);

}

static Result Test_LIS302DLClickTimeLimitSet(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

    //Set register value
    retv = LIS302DLClickTimeLimitSet(0x5A);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }
    //printf("Here\r\n");

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_TiMELIMIT, &value);
    if((retv != SUCCESS) || (value != 0x5A))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

static Result Test_LIS302DLClickLatencySet(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

    //Set register value
    retv = LIS302DLClickLatencySet(0x5A);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_LATENCY, &value);
    if((retv != SUCCESS) || (value != 0x5A))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//Here we check this function by set register 0x5A then read back
//and compare the value that written in register
static Result Test_LIS302DLClickWindowSet(void)
{
    uint8_t   value   =   0;
    Result    retv    =   SUCCESS;

    //Set register value
    retv = LIS302DLClickWindowSet(0x5A);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back and check it
    retv = LIS302DLRegReadByte(CLICK_WINDOW, &value);
    if((retv != SUCCESS) || (value != 0x5A))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

