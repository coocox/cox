/*****************************************************************************
 *      U S B  -  H I D - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: hid_callback.h
 * @brief	: HID HID call back Definitions
 * @version	: 1.1
 * @date	: 11. Mar. 2011
 * @author	: CooCox
 ****************************************************************************/

#ifndef __HID_CALLBACK_H__
#define __HID_CALLBACK_H__
#include "usb_enumerate.h"

/********************************************************************************************************//**
 * HID Number of Reports
************************************************************************************************************/
#define HID_REPORT_NUM      1

/********************************************************************************************************//**
 * HID call back function definition
************************************************************************************************************/
typedef uint32_t (PFN_HID_REPORT_CALLBACK)(void *dev,uint8_t *report, uint32_t len);

/**
 * @brief USB HID Structure
 */
typedef struct
{
	USB_ENU_Dev     usb_enu;
	PFN_HID_REPORT_CALLBACK *GetInReport;
	PFN_HID_REPORT_CALLBACK *SetOutReport;
	void            *hid_device;
//	void            *hid_para;

	uint8_t         *InReport;
	uint8_t         *OutReport;
	uint8_t         HID_Protocol;
	uint8_t         HID_IdleTime[HID_REPORT_NUM];
} USBHID_Dev;

/********************************************************************************************************//**
 * HID extern Functions
************************************************************************************************************/
extern uint32_t HID_Read  (USBHID_Dev *dev, uint8_t *rbuf, uint32_t len);
extern uint32_t HID_Write (USBHID_Dev *dev, uint8_t *wbuf, uint32_t len);
extern void     HID_Init (USBHID_Dev *dev);
extern void     HID_Connect(USBHID_Dev *dev,uint32_t con);
extern uint8_t  HID_Configurated(USBHID_Dev *dev);
extern void     HID_Event(USBHID_Dev *dev);

#endif  /* __HID_CALLBACK_H__ */
