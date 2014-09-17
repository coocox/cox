//*****************************************************************************
//
//! \file xusb.c
//! \brief Driver for the USB driver.
//! \version V2.2.1.0
//! \date 09/20/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2014, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "hw_usb.h"
#include "xhw_gpio.h"
#include "xusb.h"
#include "usb_com_config.h"
#include "cox_config.h"
#include "xhw_types.h"

xtBoolean xUSBReset (void);
xtBoolean xUSBSetAddress (unsigned long ulAddr);

static xtEventCallback g_pfnUSBEndPointEvent[USB_LOGIC_EP_NUM] = {0};

static xtEventCallback g_pfnUSBWakeUpEvent = NULL;
static xtEventCallback g_pfnUSBResetEvent = NULL;
static xtEventCallback g_pfnUSBSuspendEvent = NULL;
static xtEventCallback g_pfnUSBResumeEvent = NULL;
static xtEventCallback g_pfnUSBErrorEvent = NULL;
static xtEventCallback g_pfnUSBSOFEvent = NULL;

static void *vpUSBEndPointEventData[USB_LOGIC_EP_NUM]={NULL};

#define EP_MSK_CTRL 0x0001      /* Control Endpoint Logical Address Mask */
#define EP_MSK_BULK 0xC924      /* Bulk Endpoint Logical Address Mask */
#define EP_MSK_INT  0x4492      /* Interrupt Endpoint Logical Address Mask */
#define EP_MSK_ISO  0x1248      /* Isochronous Endpoint Logical Address Mask */

//*****************************************************************************
//
//! \brief Get Endpoint Physical Address
//!
//! \param ulEPNum Endpoint Number.
//!        ulEPNum.0..3: Address
//!        ulEPNum.7:    Dir
//!
//! \return Endpoint Physical Address.
//
//*****************************************************************************
unsigned long EndPointAddressGet (unsigned long ulEPNum) {
    unsigned long ulVal;

    ulVal = (ulEPNum & 0x0F) << 1;
    if (ulEPNum & 0x80) {
        ulVal += 1;
    }
    return (ulVal);
}

/*
 *  Write Command
 *    Parameters:      cmd:   Command
 *    Return Value:    None
 */
//*****************************************************************************
//
//! \brief Write Command
//!
//! \param cmd:   Command
//!
//! \return None
//
//*****************************************************************************
void USBCommandCodeWrite (unsigned long cmd) {

  xHWREG(USB_DEV_INT_CLR) = CCEMTY_INT;
  xHWREG(USB_CMD_CODE) = cmd;
  while ((xHWREG(USB_DEV_INT_ST) & CCEMTY_INT) == 0);
}

void USBCommandDataWrite (unsigned long cmd, unsigned long val) {

  xHWREG(USB_DEV_INT_CLR) = CCEMTY_INT;
  xHWREG(USB_CMD_CODE) = cmd;
  while ((xHWREG(USB_DEV_INT_ST) & CCEMTY_INT) == 0);
  xHWREG(USB_DEV_INT_CLR) = CCEMTY_INT;
  xHWREG(USB_CMD_CODE) = val;
  while ((xHWREG(USB_DEV_INT_ST) & CCEMTY_INT) == 0);
}

void USBCommandEndPointWrite (unsigned long EPNum, unsigned long cmd){

  xHWREG(USB_DEV_INT_ST) = CCEMTY_INT;
  xHWREG(USB_CMD_CODE)= CMD_SEL_EP(EndPointAddressGet(EPNum));
  while ((xHWREG(USB_DEV_INT_ST) & CCEMTY_INT) == 0);
  xHWREG(USB_DEV_INT_CLR) = CCEMTY_INT;
  xHWREG(USB_CMD_CODE) = cmd;
  while ((xHWREG(USB_DEV_INT_ST) & CCEMTY_INT) == 0);
}
unsigned long USBCommandDataRead (unsigned long cmd) {

  xHWREG(USB_DEV_INT_CLR) = CCEMTY_INT | CDFULL_INT;
  xHWREG(USB_CMD_CODE) = cmd;
  while ((xHWREG(USB_DEV_INT_ST) & CDFULL_INT) == 0);
  return (xHWREG(USB_CMD_DATA));
}

xtBoolean xUSBIOClkConfig(void)
{
  xHWREG(SCS)       = 0x20;
  if (xHWREG(SCS) & (1 << 5)) {             /* If Main Oscillator is enabled  */
    while ((xHWREG(SCS) & (1<<6)) == 0);/* Wait for Oscillator to be ready    */
  }

  xHWREG(CCLKCFG)   = 0x07;      /* Setup Clock Divider                */
  /* Periphral clock must be selected before PLL0 enabling and connecting
   * - according errata.lpc1768-16.March.2010 -
   */
  xHWREG(PCLKSEL0)  = 0;     /* Peripheral Clock Selection         */
  xHWREG(PCLKSEL1)  = 0;

  xHWREG(CLKSRCSEL) = 1;    /* Select Clock Source for PLL0       */

  xHWREG(PLL0CFG)   = 0x2003f;      /* configure PLL0                     */
  xHWREG(PLL0FEED)  = 0xAA;
  xHWREG(PLL0FEED)  = 0x55;

  xHWREG(PLL0CON)   = 0x01;             /* PLL0 Enable                        */
  xHWREG(PLL0FEED)  = 0xAA;
  xHWREG(PLL0FEED)  = 0x55;
  while (!(xHWREG(PLL0STAT) & (1<<26)));/* Wait for PLOCK0                    */

  xHWREG(PLL0CON)   = 0x03;             /* PLL0 Enable & Connect              */
  xHWREG(PLL0FEED)  = 0xAA;
  xHWREG(PLL0FEED)  = 0x55;
  while (!(xHWREG(PLL0STAT) & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

    /* Enable AHB clock to the GPIO domain. */
  xHWREG(PLL1CFG)  = 0x00000023;
  xHWREG(PLL1FEED)  = 0xAA;
  xHWREG(PLL1FEED)  = 0x55;

  xHWREG(PLL1CON)   = 0x01;             /* PLL1 Enable                        */
  xHWREG(PLL1FEED)  = 0xAA;
  xHWREG(PLL1FEED)  = 0x55;
  while (!(xHWREG(PLL1STAT) & (1<<10)));/* Wait for PLOCK1                    */

  xHWREG(PLL1CON)   = 0x03;             /* PLL1 Enable & Connect              */
  xHWREG(PLL1FEED)  = 0xAA;
  xHWREG(PLL1FEED)  = 0x55;
  while (!(xHWREG(PLL1STAT) & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */


  xHWREG(PCONP)     = 0x042887DE;        /* Power Control for Peripherals      */

  xHWREG(CLKOUTCFG) = 0;    /* Clock Output Configuration         */
    return xtrue;
}

//*****************************************************************************
//
//! \brief  USB Initialize Function
//!
//! \return None.
//
//*****************************************************************************
void xUSBInit(void)
{
    //! P0.29 D+, P0.30 D-
    xHWREG(PIN_CON_BASE + PINSEL1) &= ~((3<<26)|(3<<28));
    // PINSEL1 26.27, 28.29  = 01
    xHWREG(PIN_CON_BASE + PINSEL1) |=  ((1<<26)|(1<<28));


    // P1.18 GoodLink, P1.30 VBUS
    xHWREG(PIN_CON_BASE + PINSEL3) &= ~((3<< 4)|(3<<28));
    // PINSEL3 4.5 = 01, 28.29 = 10
    xHWREG(PIN_CON_BASE + PINSEL3) |=  ((1<< 4)|(2<<28));


    // P2.9 SoftConnect
    xHWREG(PIN_CON_BASE + PINSEL4) &= ~((3<<18)        );
    xHWREG(PIN_CON_BASE + PINSEL4) |=  ((1<<18)        );

    // USB PCLK -> enable USB Per.
    xHWREG(PCONP) |= (1UL<<31);
    xHWREG(USB_CLK_CTRL) = 0x1A;
    while ((xHWREG(USB_CLK_ST) & 0x1A) != 0x1A);

    xIntEnable(xINT_USB);

    xUSBReset();
    xUSBSetAddress(0);
}

//*****************************************************************************
//
//! \brief  Disables the USB master block.
//!         This function will disable operation of the USB Master block.
//!
//! \param  [in] ulBase is the USB Connect/Disconnect.
//!              - \ref xUSB_CONNECT
//!              - \ref xUSB_DISCONNECT
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
xtBoolean xUSBConnect (unsigned long ulConnect) {
    USBCommandDataWrite(CMD_SET_DEV_STAT, DAT_WR_BYTE(ulConnect ? DEV_CON : 0));
    return xtrue;
}

//*****************************************************************************
//
//! \brief USB Reset Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
xtBoolean xUSBReset(void)
{

  xHWREG(USB_EP_INDEX) = 0;
  xHWREG(USB_MAX_PSIZE) = USB_MAX_PACKET0;
  xHWREG(USB_EP_INDEX) = 1;
  xHWREG(USB_MAX_PSIZE) = USB_MAX_PACKET0;
  while ((xHWREG(USB_DEV_INT_ST) & EP_RLZED_INT) == 0);

  xHWREG(USB_EP_INT_CLR)  = 0xFFFFFFFF;
  xHWREG(USB_EP_INT_EN)   = 0xFFFFFFFF ^ 0;
  xHWREG(USB_DEV_INT_CLR) = 0xFFFFFFFF;
  xHWREG(USB_DEV_INT_EN)  = DEV_STAT_INT    | EP_SLOW_INT    |
                            (USB_SOF_EVENT   ? FRAME_INT : 0) |
                            (USB_ERROR_EVENT ? ERR_INT   : 0);
  return xtrue;

}
//*****************************************************************************
//
//! \brief USB Suspend Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
xtBoolean xUSBSuspend(void)
{
  return xtrue;
}

//*****************************************************************************
//
//! \brief USB Resume Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
xtBoolean xUSBResume(void)
{
  return xtrue;
}

//*****************************************************************************
//
//! \brief USB Wakeup Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
xtBoolean xUSBWakeUp(void)
{

//  if (USB_DeviceStatus & USB_GETSTATUS_REMOTE_WAKEUP) {
    USBCommandDataWrite(CMD_SET_DEV_STAT, DAT_WR_BYTE(DEV_CON));
//  }
  return xtrue;
}

//*****************************************************************************
//
//! \brief  USB Remote Wakeup Enbale Function
//!
//! \param  None
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBWakeUpEnable(void)
{
  return xtrue;
}

//*****************************************************************************
//
//! \brief  USB Remote Wakeup Disable Function
//!
//! \param  None
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBWakeUpDisable(void)
{
  return xtrue;
}

//*****************************************************************************
//
//! \brief  USB Set Address Function.
//!
//! \param  [in] ulBase is the USB Address.
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBSetAddress(unsigned long ulAddr)
{
  USBCommandDataWrite(CMD_SET_ADDR, DAT_WR_BYTE(DEV_EN | ulAddr));
  USBCommandDataWrite(CMD_SET_ADDR, DAT_WR_BYTE(DEV_EN | ulAddr));
  return xtrue;
}

//*****************************************************************************
//
//! \brief  USB Set Configure Function.
//!
//! \param  [in] ulBase is the USB Configure/Deconfigure.
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBConfigure(unsigned long ulConfig)
{
  USBCommandDataWrite(CMD_CFG_DEV, DAT_WR_BYTE(ulConfig ? CONF_DVICE : 0));

  xHWREG(USB_RE_EP) = 0x00000003;
  while ((xHWREG(USB_DEV_INT_ST) & EP_RLZED_INT) == 0);
  xHWREG(USB_DEV_INT_CLR) = EP_RLZED_INT;
  return xtrue;
}


//*****************************************************************************
//
//! \brief  Configure USB Endpoint according to Descriptor
//!
//! \param  [in] ulBase Pointer to Endpoint Descriptor
//!              ulDir:   Out (dir == 0), In (dir <> 0)
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEndpointConfig(USB_ENDPOINT_DESCRIPTOR *epConfig, unsigned long ulDir)
{
  unsigned long num;

  num = EndPointAddressGet(epConfig->bEndpointAddress);
  xHWREG(USB_RE_EP) |= (1 << num);
  xHWREG(USB_EP_INDEX) = num;
  xHWREG(USB_MAX_PSIZE) = epConfig->wMaxPacketSize;
  while ((xHWREG(USB_DEV_INT_ST) & EP_RLZED_INT) == 0);
  xHWREG(USB_DEV_INT_CLR) = EP_RLZED_INT;
  return xtrue;
}
xtBoolean xUSBEndpointDirCtr(unsigned long ulDir)
{
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Enable USB Endpoint
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEndpointEnable(unsigned long ulNum)
{
  USBCommandDataWrite(CMD_SET_EP_STAT(EndPointAddressGet(ulNum)), DAT_WR_BYTE(0));
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Disable USB Endpoint
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEndpointDisable(unsigned long ulNum)
{
  USBCommandDataWrite(CMD_SET_EP_STAT(EndPointAddressGet(ulNum)), DAT_WR_BYTE(EP_STAT_DA));
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Reset USB Endpoint
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEndpointReset(unsigned long ulNum)
{
  USBCommandDataWrite(CMD_SET_EP_STAT(EndPointAddressGet(ulNum)), DAT_WR_BYTE(0));
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Set Stall for USB Endpoint
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEndpointStallSet(unsigned long ulNum)
{
  USBCommandDataWrite(CMD_SET_EP_STAT(EndPointAddressGet(ulNum)), DAT_WR_BYTE(EP_STAT_ST));
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Clear Stall for USB Endpoint
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEndpointStallClear(unsigned long ulNum)
{
  USBCommandDataWrite(CMD_SET_EP_STAT(EndPointAddressGet(ulNum)), DAT_WR_BYTE(0));
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Set max packet size for control out
//!
//! \param  [in] None
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBControlOutEnble(void)
{
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Clear USB Endpoint Buffer
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEndpointBufferClear(unsigned long ulNum)
{
  return xtrue;
}

//*****************************************************************************
//
//! \brief  Read USB Endpoint Data
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!              ucpData: Pointer to Data Buffer
//!
//! \return Number of bytes read
//
//*****************************************************************************
unsigned long xUSBEndpointRead(unsigned long ulNum,unsigned char *ucpData)
{
  unsigned long cnt, n;

   xHWREG(USB_CTRL) = ((ulNum & 0x0F) << 2) | CTRL_RD_EN;

   do {
     cnt = xHWREG(USB_RX_PLEN);
   } while ((cnt & PKT_RDY) == 0);
   cnt &= PKT_LNGTH_MASK;

   for (n = 0; n < (cnt + 3) / 4; n++) {
     *((__attribute__((packed)) unsigned long *)ucpData) = xHWREG(USB_RX_DATA);
     ucpData += 4;
   }
   xHWREG(USB_CTRL) = 0;

   if (((EP_MSK_ISO >> ulNum) & 1) == 0) {   /* Non-Isochronous Endpoint */
     USBCommandCodeWrite(CMD_SEL_EP(EndPointAddressGet(ulNum)));
     USBCommandCodeWrite(CMD_CLR_BUF);
   }
   return (cnt);
}

//*****************************************************************************
//
//! \brief  Write USB Endpoint Data
//!
//! \param  [in] ulBase Endpoint Number.
//!              bit 0-3 Address
//!              bit 7 Dir
//!              ucpData: Pointer to Data Buffer
//!              ulLen Number of bytes
//!
//! \return Number of bytes written
//
//*****************************************************************************
unsigned long xUSBEndpointWrite(unsigned long ulNum,unsigned char *ucpData,
                                       unsigned long ulLen)
{
  unsigned long n;

  xHWREG(USB_CTRL) = ((ulNum & 0x0F) << 2) | CTRL_WR_EN;

  xHWREG(USB_TX_PLEN) = ulLen;

  for (n = 0; n < (ulLen + 3) / 4; n++) {
      xHWREG(USB_TX_DATA) = *((__attribute__((packed)) unsigned long  *)ucpData);
      ucpData += 4;
  }
  xHWREG(USB_CTRL) = 0;

  USBCommandCodeWrite(CMD_SEL_EP(EndPointAddressGet(ulNum)));
  USBCommandCodeWrite(CMD_VALID_BUF);
  return (ulLen);
}

//*****************************************************************************
//
//! \brief  Get USB Last Frame Number
//!
//! \param  [in] None
//!
//! \return  number of last frame
//
//*****************************************************************************
unsigned long xUSBFrameGet(void)
{
  unsigned long val;

  USBCommandCodeWrite(CMD_RD_FRAME);
  val = USBCommandDataRead(DAT_RD_FRAME);
  val = val | (USBCommandDataRead(DAT_RD_FRAME) << 8);
  return (val);
}


//*****************************************************************************
//
//! \brief  Set max packet size for control out
//!
//! \param  [in] event:   The logic number of USB endpoint
//!              handler: The callback function of USB endpoint
//!              data:    The extern type which is using here
//!
//! \return The status:
//!         - xtrue
//!         - xfalse
//
//*****************************************************************************
xtBoolean xUSBEventHandler(unsigned char event, xtEventCallback handler, void *data)
{
  xtBoolean err = xfalse;
  if(event == 0)
  {
          g_pfnUSBEndPointEvent[0] = handler;
          vpUSBEndPointEventData[0] = data;
          err = xtrue;
          return err;
  }
  switch(event)
  {
          case USB_EVENT_EP1 :
                  g_pfnUSBEndPointEvent[1] = handler;
                  vpUSBEndPointEventData[1] = data;
                  err = xtrue;
                  break;
          case USB_EVENT_EP2 :
                  g_pfnUSBEndPointEvent[2] = handler;
                  vpUSBEndPointEventData[2] = data;
                  err = xtrue;
                  break;
          case USB_EVENT_EP3 :
                  g_pfnUSBEndPointEvent[3] = handler;
                  vpUSBEndPointEventData[3] = data;
                  err = xtrue;
                  break;
          case USB_EVENT_EP4 :
                  g_pfnUSBEndPointEvent[4] = handler;
                  vpUSBEndPointEventData[4] = data;
                  err = xtrue;
                  break;
          case USB_EVENT_EP5 :
                  g_pfnUSBEndPointEvent[5] = handler;
                  vpUSBEndPointEventData[5] = data;
                  err = xtrue;
                  break;
          case USB_EVENT_EP6 :
                  g_pfnUSBEndPointEvent[6] = handler;
                  vpUSBEndPointEventData[6] = data;
                  err = xtrue;
                  break;
          case USB_EVENT_EP7 :
                  g_pfnUSBEndPointEvent[7] = handler;
                  vpUSBEndPointEventData[7] = data;
                  err = xtrue;
                  break;
  }
  return err;

}

unsigned long ulTest[100] = {0};
int testIndex = 0;

void USBIntHandler(void) {
  unsigned long disr, val, n, m;
  unsigned long episr, episrCur;

  disr = xHWREG(USB_DEV_INT_ST);       /* Device Interrupt Status */
  xHWREG(USB_DEV_INT_CLR) = disr;
  if(testIndex<100)
  ulTest[testIndex++] = disr;

  /* Device Status Interrupt (Reset, Connect change, Suspend/Resume) */
  if (disr & DEV_STAT_INT) {
//    LPC_USB->DevIntClr = DEV_STAT_INT;
    USBCommandCodeWrite(CMD_GET_DEV_STAT);
    val = USBCommandDataRead(DAT_GET_DEV_STAT);       /* Device Status */
    if (val & DEV_RST) {                    /* Reset */
        ulTest[testIndex++] = 0xFF01;
      xUSBReset();
#if   USB_RESET_EVENT
      USB_Reset_Event();
#endif
    }
    if (val & DEV_CON_CH) {                 /* Connect change */
#if   USB_POWER_EVENT
      USB_Power_Event(val & DEV_CON);
#endif
    }
    if (val & DEV_SUS_CH) {                 /* Suspend/Resume */
      if (val & DEV_SUS) {                  /* Suspend */
          ulTest[testIndex++] = 0xFF02;
          xUSBSuspend();
#if     USB_SUSPEND_EVENT
        USB_Suspend_Event();
#endif
      } else {                              /* Resume */
          ulTest[testIndex++] = 0xFF03;
          xUSBResume();
#if     USB_RESUME_EVENT
        USB_Resume_Event();
#endif
      }
    }
    goto isr_end;
  }

#if USB_SOF_EVENT
  /* Start of Frame Interrupt */
  if (disr & FRAME_INT) {
    USB_SOF_Event();
  }
#endif

#if USB_ERROR_EVENT
  /* Error Interrupt */
  if (disr & ERR_INT) {
    USBCommandCodeWrite(CMD_RD_ERR_STAT);
    val = USBCommandDataRead(DAT_RD_ERR_STAT);
    USB_Error_Event(val);
  }
#endif

  /* Endpoint's Slow Interrupt */
  if (disr & EP_SLOW_INT) {
//      while (LPC_USB->USBEpIntSt) {                   /* Endpoint Interrupt Status */
    episrCur = 0;
    episr    = xHWREG(USB_EP_INT_ST);
    for (n = 0; n < USB_EP_NUM; n++) {      /* Check All Endpoints */
      if (episr == episrCur) break;         /* break if all EP interrupts handled */
      if (episr & (1 << n)) {
        episrCur |= (1 << n);
        m = n >> 1;

        xHWREG(USB_EP_INT_CLR) = (1 << n);
        while ((xHWREG(USB_DEV_INT_ST) & CDFULL_INT) == 0);
        val = xHWREG(USB_CMD_DATA);

        if ((n & 1) == 0) {                 /* OUT Endpoint */
          if (n == 0) {                     /* Control OUT Endpoint */
            if (val & EP_SEL_STP) {         /* Setup Packet */
              if (g_pfnUSBEndPointEvent[0]) {
                  g_pfnUSBEndPointEvent[0](vpUSBEndPointEventData[0],USB_EVT_SETUP,0,0);
                continue;
              }
            }
          }
          if (g_pfnUSBEndPointEvent[m]) {
              g_pfnUSBEndPointEvent[m](vpUSBEndPointEventData[m],USB_EVT_OUT,0,0);
          }
        } else {                            /* IN Endpoint */
          if (g_pfnUSBEndPointEvent[m]) {
              g_pfnUSBEndPointEvent[m](vpUSBEndPointEventData[m],USB_EVT_IN,0,0);
          }
        }
      }
    }
    xHWREG(USB_DEV_INT_CLR) = EP_SLOW_INT;
  }



isr_end:
  return;
}
