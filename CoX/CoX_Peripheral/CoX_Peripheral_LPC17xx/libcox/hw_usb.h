//*****************************************************************************
//
//! \file      xhw_usb.h
//! \brief     Macros used when accessing the usb control hardware.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
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

#ifndef __XHW_USB_H__
#define __XHW_USB_H__

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup USBD
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_usb_Register usb Register Hardware Layer.
//! \brief      Here are detail register information.
//!             it contains:
//!                 - Register offset.
//!                 - detailed bit-field of the registers.
//!                 - Enum and mask of the registers.
//!
//! \note        Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_usb_Register_Offsets usb Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>usbx_BASE + offset</b>, (x=A/B/C...).
//! @{
//
//*****************************************************************************

//! USB Clock Control
#define USB_CLK_CTRL                   ((unsigned long)0x5000CFF4)

//! USB Clock Status
#define USB_CLK_ST                     ((unsigned long)0x5000CFF8)

//! USB Interrupt Status
#define USB_INT_ST                     ((unsigned long)0x400FC1C0)

//! USB Device Interrupt Status
#define USB_DEV_INT_ST                 ((unsigned long)0x5000C200)

//! USB Device Interrupt Enable
#define USB_DEV_INT_EN                 ((unsigned long)0x5000C204)

//! USB Device Interrupt Clear
#define USB_DEV_INT_CLR                ((unsigned long)0x5000C208)

//! USB Device Interrupt Set
#define USB_DEV_INT_SET                ((unsigned long)0x5000C20C)

//! USB Device Interrupt Priority
#define USB_DEV_INT_PRI                ((unsigned long)0x5000C22C)

//! USB Endpoint Interrupt Status
#define USB_EP_INT_ST                  ((unsigned long)0x5000C230)

//! USB Endpoint Interrupt Enable
#define USB_EP_INT_EN                  ((unsigned long)0x5000C234)

//! USB Endpoint Interrupt Clear
#define USB_EP_INT_CLR                 ((unsigned long)0x5000C238)

//! USB Endpoint Interrupt Set
#define USB_EP_INT_SET                 ((unsigned long)0x5000C23C)

//! USB Endpoint Priority
#define USB_EP_INT_PRI                 ((unsigned long)0x5000C240)

//! USB Realize Endpoint
#define USB_RE_EP                      ((unsigned long)0x5000C244)

//! USB Endpoint Index
#define USB_EP_INDEX                   ((unsigned long)0x5000C248)

//! USB MaxPacketSize
#define USB_MAX_PSIZE                  ((unsigned long)0x5000C24C)

//! USB Receive Data
#define USB_RX_DATA                    ((unsigned long)0x5000C218)

//! USB Receive Packet Length
#define USB_RX_PLEN                    ((unsigned long)0x5000C220)

//! USB Transmit Data
#define USB_TX_DATA                    ((unsigned long)0x5000C21C)

//! USB Transmit Packet Length
#define USB_TX_PLEN                    ((unsigned long)0x5000C224)

//! USB Control
#define USB_CTRL                       ((unsigned long)0x5000C228)


//! USB Command Code
#define USB_CMD_CODE                   ((unsigned long)0x5000C210)

//! USB Command Data
#define USB_CMD_DATA                   ((unsigned long)0x5000C214)

//! USB DMA Request Status
#define USB_DMA_RST                    ((unsigned long)0x5000C250)

//! USB DMA Request Clear
#define USB_DMA_RCLR                   ((unsigned long)0x5000C254)

//! USB DMA Request Set
#define USB_DMA_RSET                   ((unsigned long)0x5000C258)

//! USB UDCA Head
#define USB_UDCAH                      ((unsigned long)0x5000C280)

//! USB Endpoint DMA Status
#define USB_EP_DMA_ST                  ((unsigned long)0x5000C284)

//! USB Endpoint DMA Enable
#define USB_EP_DMA_EN                  ((unsigned long)0x5000C288)

//! USB Endpoint DMA Disable
#define USB_EP_DMA_DIS                 ((unsigned long)0x5000C28C)

//! USB DMA Interrupt Status
#define USB_DMA_INT_ST                 ((unsigned long)0x5000C290)

//! USB DMA Interrupt Enable
#define USB_DMA_INT_EN                 ((unsigned long)0x5000C294)

//! USB End of Transfer Interrupt Status
#define USB_EOT_INT_ST                 ((unsigned long)0x5000C2A0)

//! USB End of Transfer Interrupt Clear
#define USB_EOT_INT_CLR                ((unsigned long)0x5000C2A4)

//! USB End of Transfer Interrupt Set
#define USB_EOT_INT_SET                ((unsigned long)0x5000C2A8)

//! USB New DD Request Interrupt Status
#define USB_NDDR_INT_ST                ((unsigned long)0x5000C2AC)

//! USB New DD Request Interrupt Clear
#define USB_NDDR_INT_CLR               ((unsigned long)0x5000C2B0)

//! USB New DD Request Interrupt Set
#define USB_NDDR_INT_SET               ((unsigned long)0x5000C2B4)

//! USB System Error Interrupt Status
#define USB_SYS_ERR_INT_ST             ((unsigned long)0x5000C2B8)

//! USB System Error Interrupt Clear
#define USB_SYS_ERR_INT_CLR            ((unsigned long)0x5000C2BC)

//! USB System Error Interrupt Set
#define USB_SYS_ERR_INT_SET            ((unsigned long)0x5000C2C0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_usb_Register_Mcrio usb Register usefull mcrio
//! @{
//
//*****************************************************************************

/* Device Interrupt Bit Definitions */
#define FRAME_INT           0x00000001
#define EP_FAST_INT         0x00000002
#define EP_SLOW_INT         0x00000004
#define DEV_STAT_INT        0x00000008
#define CCEMTY_INT          0x00000010
#define CDFULL_INT          0x00000020
#define RxENDPKT_INT        0x00000040
#define TxENDPKT_INT        0x00000080
#define EP_RLZED_INT        0x00000100
#define ERR_INT             0x00000200

/* Rx & Tx Packet Length Definitions */
#define PKT_LNGTH_MASK      0x000003FF
#define PKT_DV              0x00000400
#define PKT_RDY             0x00000800

/* USB Control Definitions */
#define CTRL_RD_EN          0x00000001
#define CTRL_WR_EN          0x00000002

/* Command Codes */
#define CMD_SET_ADDR        0x00D00500
#define CMD_CFG_DEV         0x00D80500
#define CMD_SET_MODE        0x00F30500
#define CMD_RD_FRAME        0x00F50500
#define DAT_RD_FRAME        0x00F50200
#define CMD_RD_TEST         0x00FD0500
#define DAT_RD_TEST         0x00FD0200
#define CMD_SET_DEV_STAT    0x00FE0500
#define CMD_GET_DEV_STAT    0x00FE0500
#define DAT_GET_DEV_STAT    0x00FE0200
#define CMD_GET_ERR_CODE    0x00FF0500
#define DAT_GET_ERR_CODE    0x00FF0200
#define CMD_RD_ERR_STAT     0x00FB0500
#define DAT_RD_ERR_STAT     0x00FB0200
#define DAT_WR_BYTE(x)     (0x00000100 | ((x) << 16))
#define CMD_SEL_EP(x)      (0x00000500 | ((x) << 16))
#define DAT_SEL_EP(x)      (0x00000200 | ((x) << 16))
#define CMD_SEL_EP_CLRI(x) (0x00400500 | ((x) << 16))
#define DAT_SEL_EP_CLRI(x) (0x00400200 | ((x) << 16))
#define CMD_SET_EP_STAT(x) (0x00400500 | ((x) << 16))
#define CMD_CLR_BUF         0x00F20500
#define DAT_CLR_BUF         0x00F20200
#define CMD_VALID_BUF       0x00FA0500

/* Device Address Register Definitions */
#define DEV_ADDR_MASK       0x7F
#define DEV_EN              0x80

/* Device Configure Register Definitions */
#define CONF_DVICE          0x01

/* Device Mode Register Definitions */
#define AP_CLK              0x01
#define INAK_CI             0x02
#define INAK_CO             0x04
#define INAK_II             0x08
#define INAK_IO             0x10
#define INAK_BI             0x20
#define INAK_BO             0x40

/* Device Status Register Definitions */
#define DEV_CON             0x01
#define DEV_CON_CH          0x02
#define DEV_SUS             0x04
#define DEV_SUS_CH          0x08
#define DEV_RST             0x10

/* Error Code Register Definitions */
#define ERR_EC_MASK         0x0F
#define ERR_EA              0x10

/* Error Status Register Definitions */
#define ERR_PID             0x01
#define ERR_UEPKT           0x02
#define ERR_DCRC            0x04
#define ERR_TIMOUT          0x08
#define ERR_EOP             0x10
#define ERR_B_OVRN          0x20
#define ERR_BTSTF           0x40
#define ERR_TGL             0x80

/* Endpoint Select Register Definitions */
#define EP_SEL_F            0x01
#define EP_SEL_ST           0x02
#define EP_SEL_STP          0x04
#define EP_SEL_PO           0x08
#define EP_SEL_EPN          0x10
#define EP_SEL_B_1_FULL     0x20
#define EP_SEL_B_2_FULL     0x40

/* Endpoint Status Register Definitions */
#define EP_STAT_ST          0x01
#define EP_STAT_DA          0x20
#define EP_STAT_RF_MO       0x40
#define EP_STAT_CND_ST      0x80

/* Clear Buffer Register Definitions */
#define CLR_BUF_PO          0x01


/* DMA Interrupt Bit Definitions */
#define EOT_INT             0x01
#define NDD_REQ_INT         0x02
#define SYS_ERR_INT         0x04


/* USB RAM Definitions */
#define USB_RAM_ADR     0x20080000  /* USB RAM Start Address */
#define USB_RAM_SZ      0x00004000  /* USB RAM Size (4kB) */

/* DMA Endpoint Descriptors */
#define DD_NISO_CNT             16  /* Non-Iso EP DMA Descr. Count (max. 32) */
#define DD_ISO_CNT               8  /* Iso EP DMA Descriptor Count (max. 32) */
#define DD_NISO_SZ    (DD_NISO_CNT * 16)    /* Non-Iso DMA Descr. Size */
#define DD_ISO_SZ     (DD_ISO_CNT  * 20)    /* Iso DMA Descriptor Size */
#define DD_NISO_ADR   (USB_RAM_ADR + 128)   /* Non-Iso DMA Descr. Address */
#define DD_ISO_ADR    (DD_NISO_ADR + DD_NISO_SZ) /* Iso DMA Descr. Address */
#define DD_SZ                 (128 + DD_NISO_SZ + DD_ISO_SZ) /* Descr. Size */

/* DMA Buffer Memory Definitions */
#define DMA_BUF_ADR   (USB_RAM_ADR + DD_SZ) /* DMA Buffer Start Address */
#define DMA_BUF_SZ    (USB_RAM_SZ  - DD_SZ) /* DMA Buffer Size */

/* USB Error Codes */
#define USB_ERR_PID         0x0001  /* PID Error */
#define USB_ERR_UEPKT       0x0002  /* Unexpected Packet */
#define USB_ERR_DCRC        0x0004  /* Data CRC Error */
#define USB_ERR_TIMOUT      0x0008  /* Bus Time-out Error */
#define USB_ERR_EOP         0x0010  /* End of Packet Error */
#define USB_ERR_B_OVRN      0x0020  /* Buffer Overrun */
#define USB_ERR_BTSTF       0x0040  /* Bit Stuff Error */
#define USB_ERR_TGL         0x0080  /* Toggle Bit Error */

/* USB DMA Status Codes */
#define USB_DMA_INVALID     0x0000  /* DMA Invalid - Not Configured */
#define USB_DMA_IDLE        0x0001  /* DMA Idle - Waiting for Trigger */
#define USB_DMA_BUSY        0x0002  /* DMA Busy - Transfer in progress */
#define USB_DMA_DONE        0x0003  /* DMA Transfer Done (no Errors)*/
#define USB_DMA_OVER_RUN    0x0004  /* Data Over Run */
#define USB_DMA_UNDER_RUN   0x0005  /* Data Under Run (Short Packet) */
#define USB_DMA_ERROR       0x0006  /* Error */
#define USB_DMA_UNKNOWN     0xFFFF  /* Unknown State */

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
//! @}
//
//*****************************************************************************
#endif // __XHW_usb_H__

