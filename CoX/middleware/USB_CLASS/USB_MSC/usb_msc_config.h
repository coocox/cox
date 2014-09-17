/*****************************************************************************
 *      U S B  -  M S C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: usb_msc_config.h
 * @brief	: USB Custom Configuration
 * @version	: 1.0
 * @date	: 28. Dec. 2010
 * @author	: CooCox
 ****************************************************************************/


#ifndef __USB_MSC_CONFIG_H__
#define __USB_MSC_CONFIG_H__

/***********************************************************************
 * Mass Storage Memory Layout
 **********************************************************************/
#define MSC_MemorySize  2048*1024
#define MSC_BlockSize   512
#define MSC_BlockCount  (MSC_MemorySize / MSC_BlockSize)

/***********************************************************************
 * MSC In/Out Endpoint Logic Address
 **********************************************************************/
#define MSC_EP_IN       0x81
#define MSC_EP_OUT      0x02

/***********************************************************************
 * Max In/Out Packet Size
 **********************************************************************/
#define MSC_MAX_PACKET  64
#define USB_VENDOR_ID       0x1FC9 	// Vendor ID
#define USB_PROD_ID         0x0003	// Product ID
#define USB_DEVICE          0x0100	// Device ID


#endif  /* __USB_MSC_CONFIG_H__ */
