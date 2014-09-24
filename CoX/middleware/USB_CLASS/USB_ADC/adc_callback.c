/*****************************************************************************
 *      U S B  -  A D C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: adc_callback.c
 * @brief	: USB Audio Device Class call back componet
 * @version	: 1.1
 * @date	: 13. Mar. 2011
 * @author	: CooCox
 ****************************************************************************/
#include "adc_callback.h"

//void Audio_Event(USBADC_Dev *dev);


/********************************************************************************************************//**
 * @brief     Audio Device Class Interface Get Request Callback
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint8_t ADC_IF_GetRequest (USBADC_Dev *dev) {

	/*
	Interface = SetupPacket.wIndex.WB.L;
	EntityID  = SetupPacket.wIndex.WB.H;
	Request   = SetupPacket.bRequest;
	Value     = SetupPacket.wValue.W;
	...
	*/
	if (dev->usb_enu.SetupPacket.wIndex.W == 0x0200)
	{
		/* Feature Unit: Interface = 0, ID = 2 */
		if (dev->usb_enu.SetupPacket.wValue.WB.L == 0)
		{
		/* Master Channel */
		switch (dev->usb_enu.SetupPacket.wValue.WB.H)
		{
			case AUDIO_FU_MUTE_CONTROL:
				switch (dev->usb_enu.SetupPacket.bRequest)
				{
					case AUDIO_REQUEST_GET_CUR:
						dev->usb_enu.EP0Buf[0] = dev->Mute;
						return (TRUE);
				}
				break;
			case AUDIO_FU_VOLUME_CONTROL:
				switch (dev->usb_enu.SetupPacket.bRequest)
				{
					case AUDIO_REQUEST_GET_CUR:
						*((__attribute__((packed)) uint16_t *)dev->usb_enu.EP0Buf) = dev->VolCur;
						return (TRUE);
					case AUDIO_REQUEST_GET_MIN:
						*((__attribute__((packed)) uint16_t *)dev->usb_enu.EP0Buf) = dev->VolMin;
						return (TRUE);
					case AUDIO_REQUEST_GET_MAX:
						*((__attribute__((packed)) uint16_t *)dev->usb_enu.EP0Buf) = dev->VolMax;
						return (TRUE);
					case AUDIO_REQUEST_GET_RES:
						*((__attribute__((packed)) uint16_t *)dev->usb_enu.EP0Buf) = dev->VolRes;
						return (TRUE);
				}
				break;
			}
		}
	}

	return (FALSE);  /* Not Supported */
}


/********************************************************************************************************//**
 * @brief     Audio Device Class Interface Set Request Callback
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint8_t ADC_IF_SetRequest (USBADC_Dev *dev)
{

	/*
	Interface = SetupPacket.wIndex.WB.L;
	EntityID  = SetupPacket.wIndex.WB.H;
	Request   = SetupPacket.bRequest;
	Value     = SetupPacket.wValue.W;
	...
	*/
	if (dev->usb_enu.SetupPacket.wIndex.W == 0x0200)
	{
		/* Feature Unit: Interface = 0, ID = 2 */
		if (dev->usb_enu.SetupPacket.wValue.WB.L == 0)
		{
			/* Master Channel */
			switch (dev->usb_enu.SetupPacket.wValue.WB.H)
			{
				case AUDIO_FU_MUTE_CONTROL:
					switch (dev->usb_enu.SetupPacket.bRequest)
					{
						case AUDIO_REQUEST_SET_CUR:
							dev->Mute = dev->usb_enu.EP0Buf[0];
							return (TRUE);
					}
					break;
				case AUDIO_FU_VOLUME_CONTROL:
					switch (dev->usb_enu.SetupPacket.bRequest)
					{
						case AUDIO_REQUEST_SET_CUR:
							dev->VolCur = *((__attribute__((packed)) uint16_t *)dev->usb_enu.EP0Buf);
							return (TRUE);
					}
					break;
			}
		}
	}

	return (FALSE);  /* Not Supported */
}


/********************************************************************************************************//**
 * @brief     Audio Device Class EndPoint Get Request Callback
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint8_t ADC_EP_GetRequest (USBADC_Dev *dev)
{

	/*
	EndPoint = SetupPacket.wIndex.WB.L;
	Request  = SetupPacket.bRequest;
	Value    = SetupPacket.wValue.W;
	...
	*/
	//TODO:Not Supported
	return (FALSE);  /* Not Supported */
}


/********************************************************************************************************//**
 * @brief     Audio Device Class EndPoint Set Request Callback
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
uint8_t ADC_EP_SetRequest (USBADC_Dev *dev)
{

	/*
	EndPoint = SetupPacket.wIndex.WB.L;
	Request  = SetupPacket.bRequest;
	Value    = SetupPacket.wValue.W;
	...
	*/
	//TODO:Not Supported
	return (FALSE);  /* Not Supported */
}

/********************************************************************************************************//**
 * @brief     ADC ISO output
 * @param[in] dev :   a point which contains all the global variables which using in this function
 *            Event : event type of endpoint
 * @return    None
************************************************************************************************************/
void  ADC_ISOOut(USBADC_Dev *dev,uint32_t Event)
{
	uint32_t len;
	uint8_t wbuf[ADC_EP_MAXPAKET];
	len = dev->usb_enu.usb->USB_ReadEP(ADC_EP_OUT, wbuf);
	if(dev->Audio_write != NULL)
	{
		dev->Audio_write(dev->Audio_device, wbuf, len);
	}
}

/********************************************************************************************************//**
 * @brief     ADC read,data transfer from host to device
 * @param[in] dev  : a point which contains all the global variables which using in this function
 *            wbuf : buffer of read
 *            len  : byte length of read
 * @return    None
************************************************************************************************************/
uint32_t Audio_Read  (USBADC_Dev *dev, uint8_t *rbuf, uint32_t *len)
{
	//TODO:
	*len = dev->usb_enu.usb->USB_ReadEP(ADC_EP_OUT, rbuf);
	return *len;
}

/********************************************************************************************************//**
 * @brief     ADC write,data transfer from device to host
 * @param[in] dev  : a point which contains all the global variables which using in this function
 *            wbuf : buffer of write
 *            len  : byte length of write
 * @return    None
************************************************************************************************************/
uint32_t Audio_Write (USBADC_Dev *dev, uint8_t *wbuf, uint32_t len)
{
	//TODO:
	uint32_t wlen;
	wlen = dev->usb_enu.usb->USB_WriteEP(ADC_EP_OUT, wbuf, len);
	return wlen;
}

/********************************************************************************************************//**
 * @brief     Initialization of the USB ADC
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void Audio_Init  (USBADC_Dev *dev)
{
	dev->usb_enu.adc_data                 = dev;
	dev->usb_enu.g_pfn_adc_ep_getrequestt = (PFN_ADC_CALLBACK *)ADC_EP_GetRequest;
	dev->usb_enu.g_pfn_adc_ep_setrequestt = (PFN_ADC_CALLBACK *)ADC_EP_SetRequest;
	dev->usb_enu.g_pfn_adc_if_getrequestt = (PFN_ADC_CALLBACK *)ADC_IF_GetRequest;
	dev->usb_enu.g_pfn_adc_if_setrequestt = (PFN_ADC_CALLBACK *)ADC_IF_SetRequest;

	dev->VolCur = 0x0100;
	dev->VolMin = 0x0000;
	dev->VolMax = 0x0100;
	dev->VolRes = 0x0004;
	if (dev->Audio_Init != NULL)
	{
		dev->Audio_Init(dev->Audio_device);
	}

	USB_Init(&dev->usb_enu);
}

/********************************************************************************************************//**
 * @brief     Connect ADC to the host
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            con : TRUE \FALSE
 * @return    None
************************************************************************************************************/
void Audio_Connect(USBADC_Dev *dev,uint32_t con)
{
	dev->usb_enu.usb->USB_Connect(con);
}

/********************************************************************************************************//**
 * @brief     Get ADC Configuration statue
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    Configuration statue
************************************************************************************************************/
uint8_t  Audio_Configurated(USBADC_Dev *dev)
{
	return dev->usb_enu.USB_Configuration;
}

/********************************************************************************************************//**
 * @brief     ADC event callback setup
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void Audio_Event(USBADC_Dev *dev)
{
	dev->usb_enu.usb->USB_Event((ADC_EP_OUT&0xf),(USB_Event_Handler)ADC_ISOOut,(void *)dev);
}
