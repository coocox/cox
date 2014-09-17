/*****************************************************************************
 *      U S B  - H I D - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: hid_callback.c
 * @brief	: USB HID (Human Interface Device) call back example
 * @version	: 1.1
 * @date	: 11. Mar. 2011
 * @author	: CooCox
 ****************************************************************************/

#include "hid_callback.h"


/********************************************************************************************************//**
 * @brief     HID Get Report Request Callback,Called automatically on HID Get Report Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t HID_GetReport (USBHID_Dev *dev) {

	/* ReportID = SetupPacket.wValue.WB.L; */
	HID_Event(dev);
	switch (dev->usb_enu.SetupPacket.wValue.WB.H)
	{
		case HID_REPORT_INPUT:
			if(dev->GetInReport !=NULL)
			{
				dev->GetInReport(dev->hid_device,dev->InReport,3);
			}
			dev->usb_enu.EP0Buf[0] = dev->InReport[0];
			dev->usb_enu.EP0Buf[1] = dev->InReport[1];
			dev->usb_enu.EP0Buf[2] = dev->InReport[2];
			break;
		case HID_REPORT_OUTPUT:
			return (FALSE);          /* Not Supported */
		case HID_REPORT_FEATURE:
			/* EP0Buf[] = ...; */
			/* break; */
			return (FALSE);          /* Not Supported */
	}
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief     HID Set Report Request Callback,Called automatically on HID Set Report Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t HID_SetReport (USBHID_Dev *dev)
{

	/* ReportID = SetupPacket.wValue.WB.L; */
	switch (dev->usb_enu.SetupPacket.wValue.WB.H)
	{
		case HID_REPORT_INPUT:
			return (FALSE);          /* Not Supported */
		case HID_REPORT_OUTPUT:
			*dev->OutReport = dev->usb_enu.EP0Buf[0];
			if(dev->SetOutReport != NULL)
			{
				dev->SetOutReport(dev->hid_device,dev->OutReport,1);
			}
			break;
		case HID_REPORT_FEATURE:
			return (FALSE);          /* Not Supported */
	}
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief     HID Get Idle Request Callback,Called automatically on HID Get Idle Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t HID_GetIdle (USBHID_Dev *dev)
{

	dev->usb_enu.EP0Buf[0] = dev->HID_IdleTime[dev->usb_enu.SetupPacket.wValue.WB.L];
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief     HID Set Idle Request Callback,Called automatically on HID Set Idle Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t HID_SetIdle (USBHID_Dev *dev)
{

	dev->HID_IdleTime[dev->usb_enu.SetupPacket.wValue.WB.L] = dev->usb_enu.SetupPacket.wValue.WB.H;

	/* Idle Handling if needed */
	/* ... */

	return (TRUE);
}


/********************************************************************************************************//**
 * @brief     HID Get Protocol Request Callback,Called automatically on HID Get Protocol Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t HID_GetProtocol (USBHID_Dev *dev)
{

	dev->usb_enu.EP0Buf[0] = dev->HID_Protocol;
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief     HID Set Protocol Request Callback,Called automatically on HID Set Protocol Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t HID_SetProtocol (USBHID_Dev *dev)
{

	dev->HID_Protocol = dev->usb_enu.SetupPacket.wValue.WB.L;

	/* Protocol Handling if needed */
	/* ... */

	return (TRUE);
}
/********************************************************************************************************//**
 * @brief     HID interrupt input
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            Event : event type of endpoint
 * @return    None
************************************************************************************************************/
void  HID_IntIn (USBHID_Dev *dev,uint32_t Event)
{
	if(dev->GetInReport !=NULL)
	{
		dev->GetInReport(dev->hid_device,dev->InReport, 3);
	}
	dev->usb_enu.usb->USB_WriteEP(HID_INPUT, dev->InReport, 3);
}

/********************************************************************************************************//**
 * @brief     HID interrupt output
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            Event : event type of endpoint
 * @return    None
************************************************************************************************************/
void  HID_IntOut(USBHID_Dev *dev,uint32_t Event)
{
	uint32_t len;
	len = dev->usb_enu.usb->USB_ReadEP(HID_OUTPUT,dev->OutReport);
	if(dev->SetOutReport !=NULL)
	{
		dev->SetOutReport(dev->hid_device,dev->OutReport, len);
	}
}

/********************************************************************************************************//**
 * @brief     Initialization of the USB HID
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void HID_Init (USBHID_Dev *dev)
{
	dev->usb_enu.hid_data               = dev;
	dev->usb_enu.g_pfn_hid_get_idle     = (PFN_HID_CALLBACK *)HID_GetIdle;
	dev->usb_enu.g_pfn_hid_get_procotol = (PFN_HID_CALLBACK *)HID_GetProtocol;
	dev->usb_enu.g_pfn_hid_get_report   = (PFN_HID_CALLBACK *)HID_GetReport;
	dev->usb_enu.g_pfn_hid_set_idle     = (PFN_HID_CALLBACK *)HID_SetIdle;
	dev->usb_enu.g_pfn_hid_set_procotol = (PFN_HID_CALLBACK *)HID_SetProtocol;
	dev->usb_enu.g_pfn_hid_set_report   = (PFN_HID_CALLBACK *)HID_SetReport;

	USB_Init(&dev->usb_enu);
}

/********************************************************************************************************//**
 * @brief     Connect HID to the host
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            con : TRUE \FALSE
 * @return    None
************************************************************************************************************/
void HID_Connect(USBHID_Dev *dev,uint32_t con)
{
	dev->usb_enu.usb->USB_Connect(con);
}

/********************************************************************************************************//**
 * @brief     Get ADC Configuration statue
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    Configuration statue
************************************************************************************************************/
uint8_t HID_Configurated(USBHID_Dev *dev)
{
	return dev->usb_enu.USB_Configuration;
}

/********************************************************************************************************//**
 * @brief     HID read,data transfer from host to device
 * @param[in] dev  : a point which contains all the global variables which using in this function
 *            rbuf : buffer of read
 *            len  : byte length of read
 * @return    None
************************************************************************************************************/
uint32_t HID_Read  (USBHID_Dev *dev, uint8_t *rbuf, uint32_t len)
{
	len=dev->usb_enu.usb->USB_ReadEP(HID_OUTPUT,dev->OutReport);
	if(dev->SetOutReport !=NULL)
	{
		dev->SetOutReport(dev->hid_device,dev->OutReport,len);
	}
	return len;
}

/********************************************************************************************************//**
 * @brief     HID write,data transfer from device to host
 * @param[in] dev  : a point which contains all the global variables which using in this function
 *            wbuf : buffer of write
 *            len  : byte length of write
 * @return    None
************************************************************************************************************/
uint32_t HID_Write (USBHID_Dev *dev, uint8_t *wbuf, uint32_t len)
{
	if(dev->GetInReport != NULL)
	{
		dev->GetInReport(dev->hid_device,dev->InReport,len);
	}
	dev->usb_enu.usb->USB_WriteEP(HID_INPUT, dev->InReport, len);
	return len;
}


/********************************************************************************************************//**
 * @brief     HID event callback setup
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void HID_Event(USBHID_Dev *dev)
{
	dev->usb_enu.usb->USB_Event((HID_OUTPUT&0xf),(USB_Event_Handler)HID_IntOut,(void *)dev);
	dev->usb_enu.usb->USB_Event((HID_INPUT &0xf),(USB_Event_Handler)HID_IntIn, (void *)dev);
}
