/*****************************************************************************
 *      U S B  -  C O M M O M - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: usb_desc.h
 * @brief	: USB Descriptors Definitions
 * @version	: 1.0
 * @date	: 28. Dec. 2010
 * @author	: CooCox
 ****************************************************************************/

#ifndef __USB_DESC_H__
#define __USB_DESC_H__

#include "usb_com_config.h"


#define WBVAL(x) ((x) & 0xFF),(((x) >> 8) & 0xFF)                       /*!16 bit number to two 8 bit number   */
#define B3VAL(x) (x & 0xFF),((x >> 8) & 0xFF),((x >> 16) & 0xFF)        /*!24 bit number to three 8 bit number */

#define USB_DEVICE_DESC_SIZE        (sizeof(USB_DEVICE_DESCRIPTOR))        /*!<size of device descriptor       */
#define USB_CONFIGUARTION_DESC_SIZE (sizeof(USB_CONFIGURATION_DESCRIPTOR)) /*!<size of configuration descriptor*/
#define USB_INTERFACE_DESC_SIZE     (sizeof(USB_INTERFACE_DESCRIPTOR))     /*!<size of interface descriptor    */
#define USB_ENDPOINT_DESC_SIZE      (sizeof(USB_ENDPOINT_DESCRIPTOR))      /*!<size of end point descriptor    */

#if USB_HID
#define HID_DESC_OFFSET              0x0012                                /*!<offset of hid descriptor        */
#define HID_DESC_SIZE               (sizeof(HID_DESCRIPTOR))               /*!<size of hid descriptor          */
#define HID_REPORT_DESC_SIZE        (sizeof(HID_ReportDescriptor))         /*!<size of report descriptor       */

extern const uint8_t HID_ReportDescriptor[];                               /*!<hid report descriptor           */
extern const uint16_t HID_ReportDescSize;                                  /*!<size of hid report descriptor   */

#endif  /* USB_HID */

//extern const uint8_t USB_DeviceDescriptor[];                               /*!<usb device descriptor           */
//extern const uint8_t USB_ConfigDescriptor[];                               /*!<usb configuration descriptor    */
//extern const uint8_t USB_StringDescriptor[];                               /*!<usb string descriptor           */


#endif  /* __USB_DESC_H__ */
