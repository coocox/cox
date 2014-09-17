/*****************************************************************************
 *      U S B  -  H I D - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: usb_hid_config.h
 * @brief	: USB hid Configuration
 * @version	: 1.1
 * @date	: 11. Mar. 2011
 * @author	: CooCox
 ****************************************************************************/


#ifndef __USB_HID_CONFIG_H__
#define __USB_HID_CONFIG_H__

/**********************************************************************
 *  CDC vendor ID and product ID
 **********************************************************************/
#define USB_VENDOR_ID       0x1234 	// Vendor ID
#define USB_PROD_ID         0x0003	// Product ID
#define USB_DEVICE          0x0100	// Device ID
#define HID_FUNCTION        HID_PROTOCOL_MOUSE   /*!< hid function             <0-2> */


/**********************************************************************
 *  CDC Communication In\Out Endpoint Address
 **********************************************************************/
#define HID_INPUT           0x81
#define HID_OUTPUT          0x02

#endif  /* __USB_MSC_CONFIG_H__ */
