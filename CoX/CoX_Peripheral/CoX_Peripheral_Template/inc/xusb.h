//*****************************************************************************
//
//! \file      xusb.h
//! \brief     Prototypes for the USB Driver.
//! \version V2.3
//! \date 08/01/2014
//! \author    CooCox
//! \copyright
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
//! THE POSPIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef __XUSB_H__
#define __XUSB_H__

//#include "usb.h"
//#include "xPort.h"
#include "xhw_types.h"

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
//! \addtogroup CoX_Peripheral_Interface
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUSB
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUSB_Event xUSB Event
//!
//! more please refer to [xUSB Event in MD file](@ref xUSB_Event_md).
//!
//! @{
//
//*****************************************************************************

//
// Setup Packet 
//
#define xUSB_EVENT_SETUP        1

//
// OUT Packet
//
#define xUSB_EVENT_OUT          2

//
// In Packet 
//
#define xUSB_EVENT_IN           3

//
// OUT Packet - Not Acknowledged
//
#define xUSB_EVENT_OUT_NAK      4

//
// IN Packet - Not Acknowledged
//
#define xUSB_EVENT_IN_NAK       5

//
// OUT Packet - Stalled 
//
#define xUSB_EVENT_OUT_STALL    6

//
// IN Packet - Stalled 
//
#define xUSB_EVENT_IN_STALL     7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUSB_Endpoint_Descriptor xUSB Standard Endpoint Descriptor
//! \brief      Define the type of Standard Endpoint Descriptor
//!
//! more please refer to [xUSB Standard Endpoint Descriptor](@ref xUSB_Endpoint_Descriptor_md).
//!
//! @{
//
//*****************************************************************************

typedef struct _USB_ENDPOINT_DESCRIPTOR {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned char  bEndpointAddress;
	unsigned char  bmAttributes;
	unsigned short wMaxPacketSize;
	unsigned char  bInterval;
} __attribute__((packed)) USB_ENDPOINT_DESCRIPTOR;

#define USB_EVENT_EP0           0
#define USB_EVENT_EP1           1
#define USB_EVENT_EP2           2
#define USB_EVENT_EP3           3
#define USB_EVENT_EP4           4
#define USB_EVENT_EP5           5
#define USB_EVENT_EP6           6
#define USB_EVENT_EP7           7
#define USB_EVENT_EP8           8
#define USB_EVENT_EP9           9
#define USB_EVENT_EP10          10
#define USB_EVENT_EP11          11

#define USB_EVT_SETUP       1   /* Setup Packet                             */
#define USB_EVT_OUT         2   /* OUT Packet                               */
#define USB_EVT_IN          3   /*  IN Packet                               */
#define USB_EVT_OUT_NAK     4   /* OUT Packet - Not Acknowledged            */
#define USB_EVT_IN_NAK      5   /*  IN Packet - Not Acknowledged            */
#define USB_EVT_OUT_STALL   6   /* OUT Packet - Stalled                     */
#define USB_EVT_IN_STALL    7   /*  IN Packet - Stalled                     */
#define USB_EVT_OUT_DMA_EOT 8   /* DMA OUT EP - End of Transfer */
#define USB_EVT_IN_DMA_EOT  9   /* DMA  IN EP - End of Transfer */
#define USB_EVT_OUT_DMA_NDR 10  /* DMA OUT EP - New Descriptor Request */
#define USB_EVT_IN_DMA_NDR  11  /* DMA  IN EP - New Descriptor Request */
#define USB_EVT_OUT_DMA_ERR 12  /* DMA OUT EP - Error */
#define USB_EVT_IN_DMA_ERR  13  /* DMA  IN EP - Error */

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUSB_Exported_APIs xUSB API
//! \brief      xUSB API Reference.
//!
//! \section    xUSB_Exported_APIs_Port CoX Port Details
//!
//! |       xUSB API                     |     CoX      |
//! |------------------------------------|--------------|
//! | \ref  xUSBIOClkConfig              |  Mandatory   |
//! | \ref  xUSBInit                     |  Mandatory   |
//! | \ref  xUSBConnect                  |  Mandatory   |
//! | \ref  xUSBReset                    |  Mandatory   |
//! | \ref  xUSBSuspend                  |  Mandatory   |
//! | \ref  xUSBResume                   |  Mandatory   |
//! | \ref  xUSBWakeUp                   |  Mandatory   |
//! | \ref  xUSBWakeUpEnable             |  Mandatory   |
//! | \ref  xUSBWakeUpDisable            |  Mandatory   |
//! | \ref  xUSBSetAddress               |  Mandatory   |
//! | \ref  xUSBConfigure                |  Mandatory   |
//! | \ref  xUSBEndpointConfig           |  Mandatory   |
//! | \ref  xUSBEndpointDirCtr           |  Mandatory   |
//! | \ref  xUSBEndpointEnable           |  Mandatory   |
//! | \ref  xUSBEndpointDisable          |  Mandatory   |
//! | \ref  xUSBEndpointReset            |  Mandatory   |
//! | \ref  xUSBEndpointStallSet         |  Mandatory   |
//! | \ref  xUSBEndpointStallClear       |  Mandatory   |
//! | \ref  xUSBControlOutEnble          |  Mandatory   |
//! | \ref  xUSBEndpointBufferClear      |  Mandatory   |
//! | \ref  xUSBEndpointRead             |  Mandatory   |
//! | \ref  xUSBEndpointWrite            |  Mandatory   |
//! | \ref  xUSBFrameGet                 |  Mandatory   |
//! | \ref  xUSBEventHandler             |  Mandatory   |
//! more please refer to [xUSB API in MD file](@ref xUSB_Exported_APIs_md).
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  USB and IO Clock configuration only.
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
extern xtBoolean xUSBIOClkConfig(void);

//*****************************************************************************
//
//! \brief  USB Initialize Function
//!
//! \return None.
//
//*****************************************************************************
extern void xUSBInit(void);

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
extern xtBoolean xUSBConnect(unsigned long ulConnect);

//*****************************************************************************
//
//! \brief USB Reset Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
extern xtBoolean xUSBReset(void);

//*****************************************************************************
//
//! \brief USB Suspend Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
extern xtBoolean xUSBSuspend(void);

//*****************************************************************************
//
//! \brief USB Wakeup Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
extern xtBoolean xUSBWakeUp(void);

//*****************************************************************************
//
//! \brief USB Resume Function
//!
//! \param  None
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
extern xtBoolean xUSBResume(void);

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
extern xtBoolean xUSBWakeUpEnable(void);

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
extern xtBoolean xUSBWakeUpDisable(void);

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
extern xtBoolean xUSBSetAddress(unsigned long ulAddr);

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
extern xtBoolean xUSBConfigure(unsigned long ulConfig);

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
extern xtBoolean xUSBEndpointConfig(USB_ENDPOINT_DESCRIPTOR *epConfig, unsigned long ulDir);

extern xtBoolean xUSBEndpointDirCtr(unsigned long ulDir);

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
extern xtBoolean xUSBEndpointEnable(unsigned long ulNum);

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
extern xtBoolean xUSBEndpointDisable(unsigned long ulNum);

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
extern xtBoolean xUSBEndpointReset(unsigned long ulNum);

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
extern xtBoolean xUSBEndpointStallSet(unsigned long ulNum);

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
extern xtBoolean xUSBEndpointStallClear(unsigned long ulNum);

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
extern xtBoolean xUSBControlOutEnble(void);

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
extern xtBoolean xUSBEndpointBufferClear(unsigned long ulNum);

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
extern unsigned long xUSBEndpointRead(unsigned long ulNum,unsigned char *ucpData);

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
extern unsigned long xUSBEndpointWrite(unsigned long ulNum,unsigned char *ucpData,
                                       unsigned long ulLen);

//*****************************************************************************
//
//! \brief  Get USB Last Frame Number
//!
//! \param  [in] None
//!
//! \return  number of last frame
//
//*****************************************************************************
extern unsigned long xUSBFrameGet(void);
                                       
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
extern xtBoolean xUSBEventHandler(unsigned char event, xtEventCallback handler, void *data);



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

#endif // __XUSB_H__
