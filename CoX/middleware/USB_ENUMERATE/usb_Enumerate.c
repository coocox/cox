/*****************************************************************************
 *      U S B  -  C O M M O M - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: usb_Enumerate.c
 * @brief	: USB Enumerate Module
 * @version	: 1.1
 * @date	: 3. Mar. 2011
 * @author	: CooCox
 ****************************************************************************/
#include "usb_enumerate.h"

/********************************************************************************************************//**
 * @brief     Reset USB Core
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void USB_ResetCore (USB_ENU_Dev *dev)
{

	dev->USB_DeviceStatus  = 0;
	dev->USB_DeviceAddress = 0;
	dev->USB_Configuration = 0;
	dev->USB_EndPointMask  = 0x00010001;
	dev->USB_EndPointHalt  = 0x00000000;
	dev->USB_EndPointStall = 0x00000000;
}
/********************************************************************************************************//**
 * @brief     USB Request - Setup Stage
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void USB_SetupStage (USB_ENU_Dev *dev)
{
	xUSBEndpointRead(0x00, (uint8_t *)&(dev->SetupPacket));
}

/********************************************************************************************************//**
 * @brief     USB Request - Data In Stage
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void USB_DataInStage (USB_ENU_Dev *dev)
{
	uint32_t cnt;

	if (dev->EP0Data.Count > USB_MAX_PACKET0)
	{
		cnt = USB_MAX_PACKET0;
	} else
	{
		cnt = dev->EP0Data.Count;
	}
	cnt = xUSBEndpointWrite(0x80, dev->EP0Data.pData, cnt);
	dev->EP0Data.pData += cnt;
	dev->EP0Data.Count -= cnt;
}

/********************************************************************************************************//**
 * @brief     USB Request - Data Out Stage
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void USB_DataOutStage (USB_ENU_Dev *dev)
{
	uint32_t cnt;

	cnt = xUSBEndpointRead(0x00, dev->EP0Data.pData);
	dev->EP0Data.pData += cnt;
	dev->EP0Data.Count -= cnt;
}

/********************************************************************************************************//**
 * @brief     USB Request - Status In Stage
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void USB_StatusInStage (USB_ENU_Dev *dev)
{
	xUSBEndpointWrite(0x80, NULL, 0);
}

/********************************************************************************************************//**
 * @brief     USB Request - Status Out Stage
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void USB_StatusOutStage (USB_ENU_Dev *dev)
{
	xUSBEndpointRead(0x00, dev->EP0Buf);
}

/********************************************************************************************************//**
 * @brief     Get Status USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqGetStatus (USB_ENU_Dev *dev)
{
	uint32_t n, m;

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			dev->EP0Data.pData = (uint8_t *)&(dev->USB_DeviceStatus);
			break;
		case REQUEST_TO_INTERFACE:
			if ((dev->USB_Configuration != 0) && (dev->SetupPacket.wIndex.WB.L < dev->USB_NumInterfaces))
			{
				*((uint16_t __attribute__((packed)) *)dev->EP0Buf) = 0;
				dev->EP0Data.pData = dev->EP0Buf;
			}
			else
			{
				return (FALSE);
			}
			break;
		case REQUEST_TO_ENDPOINT:
			n = dev->SetupPacket.wIndex.WB.L & 0x8F;
			m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
			if (((dev->USB_Configuration != 0) || ((n & 0x0F) == 0)) && (dev->USB_EndPointMask & m))
			{
				*((uint16_t __attribute__((packed)) *)dev->EP0Buf) = (dev->USB_EndPointHalt & m) ? 1 : 0;
				dev->EP0Data.pData = dev->EP0Buf;
			}
			else
			{
				return (FALSE);
			}
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     Set/Clear Feature USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @param[in] sc:    0 - Clear,
 *                   1 - Set
 *                   (global SetupPacket)
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqSetClrFeature (USB_ENU_Dev *dev, uint32_t sc)
{
	uint32_t n, m;

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			if (dev->SetupPacket.wValue.W == USB_FEATURE_REMOTE_WAKEUP)
			{
				if (sc)
				{
				        xUSBWakeUpEnable();
					dev->USB_DeviceStatus |=  USB_GETSTATUS_REMOTE_WAKEUP;
				}
				else
				{
				        xUSBWakeUpDisable();
					dev->USB_DeviceStatus &= ~USB_GETSTATUS_REMOTE_WAKEUP;
				}
			}
			else
			{
				return (FALSE);
			}
			break;
		case REQUEST_TO_INTERFACE:
			return (FALSE);
		case REQUEST_TO_ENDPOINT:
			n = dev->SetupPacket.wIndex.WB.L & 0x8F;
			m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
			if ((dev->USB_Configuration != 0) && ((n & 0x0F) != 0) && (dev->USB_EndPointMask & m))
			{
				if (dev->SetupPacket.wValue.W == USB_FEATURE_ENDPOINT_STALL)
				{
					if (sc)
					{
						xUSBEndpointStallSet(n);
						dev->USB_EndPointHalt |=  m;
					}
					else
					{
						if ((dev->USB_EndPointStall & m) != 0)
						{
							return (TRUE);
						}
						xUSBEndpointStallClear(n);
#if (USB_MSC)
						if ((n == MSC_EP_IN) && ((dev->USB_EndPointHalt & m) != 0))
						{
							/* Compliance Test: rewrite CSW after unstall */
//							if (CSW.dSignature == MSC_CSW_Signature)
//							{
//								xUSBEndpointWrite(MSC_EP_IN, (uint8_t *)&CSW, sizeof(CSW));
//							}
						}
#endif
						dev->USB_EndPointHalt &= ~m;
					}
				}
				else
				{
					return (FALSE);
				}
			}
			else
			{
				return (FALSE);
			}
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     Set Address USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqSetAddress (USB_ENU_Dev *dev)
{

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			dev->USB_DeviceAddress = 0x80 | dev->SetupPacket.wValue.WB.L;
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     Get Descriptor USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqGetDescriptor (USB_ENU_Dev *dev)
{
	uint8_t  *pD;
	uint32_t len, n;

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			switch (dev->SetupPacket.wValue.WB.H)
			{
				case USB_DEVICE_DESCRIPTOR_TYPE:
					dev->EP0Data.pData = (uint8_t *)dev->USB_DeviceDescriptor;
					len = USB_DEVICE_DESC_SIZE;
					break;
				case USB_CONFIGURATION_DESCRIPTOR_TYPE:
					pD = (uint8_t *)dev->USB_ConfigDescriptor;
					for (n = 0; n != dev->SetupPacket.wValue.WB.L; n++)
					{
						if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength != 0)
						{
							pD += ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
						}
					}
					if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength == 0)
					{
						return (FALSE);
					}
					dev->EP0Data.pData = pD;
					len = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
					break;
				case USB_STRING_DESCRIPTOR_TYPE:
					pD = (uint8_t *)dev->USB_StringDescriptor;
					for (n = 0; n != dev->SetupPacket.wValue.WB.L; n++)
					{
						if (((USB_STRING_DESCRIPTOR *)pD)->bLength != 0)
						{
							pD += ((USB_STRING_DESCRIPTOR *)pD)->bLength;
						}
					}
					if (((USB_STRING_DESCRIPTOR *)pD)->bLength == 0)
					{
						return (FALSE);
					}
					dev->EP0Data.pData = pD;
					len = ((USB_STRING_DESCRIPTOR *)dev->EP0Data.pData)->bLength;
					break;
				default:
					return (FALSE);
			}
			break;
		case REQUEST_TO_INTERFACE:
			switch (dev->SetupPacket.wValue.WB.H)
			{
#if USB_HID
				case HID_HID_DESCRIPTOR_TYPE:
					if (dev->SetupPacket.wIndex.WB.L != USB_HID_IF_NUM)
					{
						return (FALSE);    /* Only Single HID Interface is supported */
					}
					dev->EP0Data.pData = (uint8_t *)dev->USB_ConfigDescriptor + HID_DESC_OFFSET;
					len = HID_DESC_SIZE;
					break;
				case HID_REPORT_DESCRIPTOR_TYPE:
					if (dev->SetupPacket.wIndex.WB.L != USB_HID_IF_NUM)
					{
						return (FALSE);    /* Only Single HID Interface is supported */
					}
					dev->EP0Data.pData = (uint8_t *)dev->HID_ReportDescriptor;
					len = HID_ReportDescSize;
					break;
				case HID_PHYSICAL_DESCRIPTOR_TYPE:
					return (FALSE);      /* HID Physical Descriptor is not supported */
#endif
				default:
					return (FALSE);
			}
			break;
		default:
		return (FALSE);
	}

	if (dev->EP0Data.Count > len)
	{
		dev->EP0Data.Count = len;
	}

	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     Get Configuration USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqGetConfiguration (USB_ENU_Dev *dev)
{

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			dev->EP0Data.pData = &dev->USB_Configuration;
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     Add a number of bytes to a pointer's address,Call looks like: AddPtr((void **)&myPointer, 8);
 * @param[in] vpptr: void pointer to pointer
 * @param[in] n    : number of bytes to add to pointer
 * @return    None
************************************************************************************************************/
__inline void UsbAddPtr(void **vpptr, uint32_t n)
{
	/* Declare a pointer to a pointer to a byte. Only a byte pointer
	 * can be incremented by a number of bytes. Other pointers will
	 * increment by a multiple of what they point to.
	 */
	uint8_t **bpptr;

	/* Convert our void pointer to a pointer to a byte pointer to a pointer */
	bpptr = (uint8_t **)vpptr;

	/* Add 'n' bytes to our pointer value */
	(*bpptr) += n;
}

/********************************************************************************************************//**
 * @brief     Set Configuration USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqSetConfiguration (USB_ENU_Dev *dev)
{
	USB_COMMON_DESCRIPTOR *pD;
	uint32_t alt = 0;
	uint32_t n, m;

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:

			if (dev->SetupPacket.wValue.WB.L)
			{
				pD = (USB_COMMON_DESCRIPTOR *)dev->USB_ConfigDescriptor;
				while (pD->bLength)
				{
					switch (pD->bDescriptorType)
					{
						case USB_CONFIGURATION_DESCRIPTOR_TYPE:
							if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bConfigurationValue == dev->SetupPacket.wValue.WB.L)
							{
								dev->USB_Configuration = dev->SetupPacket.wValue.WB.L;
								dev->USB_NumInterfaces = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->bNumInterfaces;
								for (n = 0; n < USB_IF_NUM; n++)
								{
									dev->USB_AltSetting[n] = 0;
								}
								for (n = 1; n < 16; n++)
								{
									if (dev->USB_EndPointMask & (1 << n))
									{
										xUSBEndpointDisable(n);
									}
									if (dev->USB_EndPointMask & ((1 << 16) << n))
									{
										xUSBEndpointDisable(n | 0x80);
									}
								}
								dev->USB_EndPointMask = 0x00010001;
								dev->USB_EndPointHalt = 0x00000000;
								dev->USB_EndPointStall= 0x00000000;
								xUSBConfigure(TRUE);
								if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bmAttributes & USB_CONFIG_POWERED_MASK)
								{
									dev->USB_DeviceStatus |=  USB_GETSTATUS_SELF_POWERED;
								}
								else
								{
									dev->USB_DeviceStatus &= ~USB_GETSTATUS_SELF_POWERED;
								}
							}
							else
							{
								UsbAddPtr((void **)&pD, ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength);
								continue;
							}
							break;
						case USB_INTERFACE_DESCRIPTOR_TYPE:
							alt = ((USB_INTERFACE_DESCRIPTOR *)pD)->bAlternateSetting;
							break;
						case USB_ENDPOINT_DESCRIPTOR_TYPE:
							if (alt == 0)
							{
								n = ((USB_ENDPOINT_DESCRIPTOR *)pD)->bEndpointAddress & 0x8F;
								m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
								dev->USB_EndPointMask |= m;
								xUSBEndpointConfig((USB_ENDPOINT_DESCRIPTOR *)pD,0);
								xUSBEndpointEnable(n);
								xUSBEndpointReset(n);
							}
							break;
					}
					UsbAddPtr((void **)&pD, pD->bLength);
				}
			}
			else
			{
				dev->USB_Configuration = 0;
				for (n = 1; n < 16; n++)
				{
					if (dev->USB_EndPointMask & (1 << n))
					{
						xUSBEndpointDisable(n);
					}
					if (dev->USB_EndPointMask & ((1 << 16) << n))
					{
						xUSBEndpointDisable(n | 0x80);
					}
				}
				dev->USB_EndPointMask  = 0x00010001;
				dev->USB_EndPointHalt  = 0x00000000;
				dev->USB_EndPointStall = 0x00000000;
				xUSBConfigure(FALSE);
			}

			if (dev->USB_Configuration != dev->SetupPacket.wValue.WB.L)
			{
				return (FALSE);
			}
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief     Get Interface USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqGetInterface (USB_ENU_Dev *dev)
{

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_INTERFACE:
			if ((dev->USB_Configuration != 0) && (dev->SetupPacket.wIndex.WB.L < dev->USB_NumInterfaces))
			{
				dev->EP0Data.pData = dev->USB_AltSetting + dev->SetupPacket.wIndex.WB.L;
			}
			else
			{
				return (FALSE);
			}
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     Set Interface USB Request
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    TRUE - Success, FALSE - Error
************************************************************************************************************/
__inline uint32_t USB_ReqSetInterface (USB_ENU_Dev *dev)
{
	USB_COMMON_DESCRIPTOR *pD;
	uint32_t ifn = 0, alt = 0, old = 0, msk = 0;
	uint32_t n, m;
	uint32_t set;

	switch (dev->SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_INTERFACE:
			if (dev->USB_Configuration == 0) return (FALSE);
			set = FALSE;
			pD  = (USB_COMMON_DESCRIPTOR *)dev->USB_ConfigDescriptor;
			while (pD->bLength)
			{
				switch (pD->bDescriptorType)
				{
					case USB_CONFIGURATION_DESCRIPTOR_TYPE:
						if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bConfigurationValue != dev->USB_Configuration)
						{
							UsbAddPtr((void **)&pD, ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength);
							continue;
						}
						break;
					case USB_INTERFACE_DESCRIPTOR_TYPE:
						ifn = ((USB_INTERFACE_DESCRIPTOR *)pD)->bInterfaceNumber;
						alt = ((USB_INTERFACE_DESCRIPTOR *)pD)->bAlternateSetting;
						msk = 0;
						if ((ifn == dev->SetupPacket.wIndex.WB.L) && (alt == dev->SetupPacket.wValue.WB.L))
						{
							set = TRUE;
							old = dev->USB_AltSetting[ifn];
							dev->USB_AltSetting[ifn] = (uint8_t)alt;
						}
						break;
					case USB_ENDPOINT_DESCRIPTOR_TYPE:
						if (ifn == dev->SetupPacket.wIndex.WB.L)
						{
							n = ((USB_ENDPOINT_DESCRIPTOR *)pD)->bEndpointAddress & 0x8F;
							m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
							if (alt == dev->SetupPacket.wValue.WB.L)
							{
								dev->USB_EndPointMask |=  m;
								dev->USB_EndPointHalt &= ~m;
								xUSBEndpointConfig((USB_ENDPOINT_DESCRIPTOR *)pD,0);
								xUSBEndpointEnable(n);
								xUSBEndpointReset(n);
								msk |= m;
							}
							else if ((alt == old) && ((msk & m) == 0))
							{
								dev->USB_EndPointMask &= ~m;
								dev->USB_EndPointHalt &= ~m;
								xUSBEndpointDisable(n);
							}
						}
						break;
				}
				UsbAddPtr((void **)&pD, pD->bLength);
			}
			break;
		default:
			return (FALSE);
	}

	return (set);
}

/********************************************************************************************************//**
 * @brief     USB Endpoint 0 Event Callback
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @param[in] event: USB_EVT_SETUP\USB_EVT_OUT\USB_EVT_IN\USB_EVT_OUT_NAK\USB_EVT_IN_NAK
 * @return    None
************************************************************************************************************/
void USB_EndPoint0 (USB_ENU_Dev *dev, uint32_t event,
    unsigned long ulMsgParam,
    void *pvMsgData)
{

	switch (event)
	{
		case USB_EVT_SETUP:
			USB_SetupStage(dev);
			xUSBEndpointDirCtr(dev->SetupPacket.bmRequestType.BM.Dir);
			dev->EP0Data.Count = dev->SetupPacket.wLength;     /* Number of bytes to transfer */
			switch (dev->SetupPacket.bmRequestType.BM.Type)
			{

				case REQUEST_STANDARD:
					switch (dev->SetupPacket.bRequest)
					{
						case USB_REQUEST_GET_STATUS:
							if (!USB_ReqGetStatus(dev))
							{
								goto stall_i;
							}
							USB_DataInStage(dev);
							break;

						case USB_REQUEST_CLEAR_FEATURE:
							if (!USB_ReqSetClrFeature(dev,0))
							{
								goto stall_i;
							}
							USB_StatusInStage(dev);
#if USB_FEATURE_EVENT
							if(dev->g_pfn_feature_callback !=NULL)
							{
								dev->g_pfn_feature_callback(0);
							}
#endif
							break;

						case USB_REQUEST_SET_FEATURE:
							if (!USB_ReqSetClrFeature(dev,1))
							{
								goto stall_i;
							}
							USB_StatusInStage(dev);
#if USB_FEATURE_EVENT
							if(dev->g_pfn_feature_callback !=NULL)
							{
								dev->g_pfn_feature_callback(0);
							}
#endif
							break;

						case USB_REQUEST_SET_ADDRESS:
							if (!USB_ReqSetAddress(dev))
							{
								goto stall_i;
							}
							USB_StatusInStage(dev);
							break;

						case USB_REQUEST_GET_DESCRIPTOR:
							if (!USB_ReqGetDescriptor(dev))
							{
								goto stall_i;
							}
							USB_DataInStage(dev);
							break;

						case USB_REQUEST_SET_DESCRIPTOR:
							/*stall_o:*/
							xUSBEndpointStallSet(0x00);            /* not supported */
							dev->EP0Data.Count = 0;
							break;

						case USB_REQUEST_GET_CONFIGURATION:
							if (!USB_ReqGetConfiguration(dev))
							{
								goto stall_i;
							}
							USB_DataInStage(dev);
							break;

						case USB_REQUEST_SET_CONFIGURATION:
							if (!USB_ReqSetConfiguration(dev))
							{
								goto stall_i;
							}
							USB_StatusInStage(dev);
#if USB_CONFIGURE_EVENT
							if(dev->g_pfn_config_callback != NULL)
							{
								dev->g_pfn_config_callback(0);
							}
#endif
							break;

						case USB_REQUEST_GET_INTERFACE:
							if (!USB_ReqGetInterface(dev))
							{
								goto stall_i;
							}
							USB_DataInStage(dev);
							break;

						case USB_REQUEST_SET_INTERFACE:
							if (!USB_ReqSetInterface(dev))
							{
								goto stall_i;
							}
							USB_StatusInStage(dev);
#if USB_INTERFACE_EVENT
							if(dev->g_pfn_interfacec_callback != NULL)
							{
								dev->g_pfn_interfacec_callback(0);
							}
#endif
							break;

						default:
							goto stall_i;
					}
					break;  /* end case REQUEST_STANDARD */

#if USB_CLASS
				case REQUEST_CLASS:
					switch (dev->SetupPacket.bmRequestType.BM.Recipient)
					{
						case REQUEST_TO_DEVICE:
							goto stall_i;                                              /* not supported */

						case REQUEST_TO_INTERFACE:
#if USB_HID
							if (dev->SetupPacket.wIndex.WB.L == USB_HID_IF_NUM)
							{           /* IF number correct? */
								switch (dev->SetupPacket.bRequest)
								{
									case HID_REQUEST_GET_REPORT:
										if(dev->g_pfn_hid_get_report!=NULL)
										{
											if (dev->g_pfn_hid_get_report(dev->hid_data))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case HID_REQUEST_SET_REPORT:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case HID_REQUEST_GET_IDLE:
										if(dev->g_pfn_hid_get_idle!=NULL)
										{
											if (dev->g_pfn_hid_get_idle(dev->hid_data))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case HID_REQUEST_SET_IDLE:
										if(dev->g_pfn_hid_set_idle!=NULL)
										{
											if (dev->g_pfn_hid_set_idle(dev->hid_data))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case HID_REQUEST_GET_PROTOCOL:
										if(dev->g_pfn_hid_get_procotol!=NULL)
										{
											if (dev->g_pfn_hid_get_procotol(dev->hid_data))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case HID_REQUEST_SET_PROTOCOL:
										if(dev->g_pfn_hid_set_procotol!=NULL)
										{
											if (dev->g_pfn_hid_set_procotol(dev->hid_data))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
								}
							}
#endif  /* USB_HID */
#if USB_MSC
							if (dev->SetupPacket.wIndex.WB.L == USB_MSC_IF_NUM)
							{           /* IF number correct? */
								switch (dev->SetupPacket.bRequest)
								{
									case MSC_REQUEST_RESET:
										if ((dev->SetupPacket.wValue.W == 0) &&	                 /* RESET with invalid parameters -> STALL */
										(dev->SetupPacket.wLength  == 0))
										{
											if(dev->g_pfn_msc_request_reset!=NULL)
											{
												if (dev->g_pfn_msc_request_reset(dev->msc_data,0))
												{
													USB_StatusInStage(dev);
													goto setup_class_ok;
												}
											}
											else
											{
												goto stall_i;
											}
										}
										break;
									case MSC_REQUEST_GET_MAX_LUN:
										if ((dev->SetupPacket.wValue.W == 0) &&	                 /* GET_MAX_LUN with invalid parameters -> STALL */
										(dev->SetupPacket.wLength  == 1))
										{
											if(dev->g_pfn_msc_request_get_max_lun!=NULL)
											{
												if (dev->g_pfn_msc_request_get_max_lun(dev->msc_data,0))
												{
													dev->EP0Data.pData = dev->EP0Buf;
													USB_DataInStage(dev);
													goto setup_class_ok;
												}
											}
											else
											{
												goto stall_i;
											}
										}
										break;
									case MSC_REQUEST_ADSC:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
										break;
									case MSC_REQUEST_GET_REQ:
										if ( (dev->SetupPacket.wValue.W == MSC_REQ_GLI)	)                 /* GET_MAX_LUN with invalid parameters -> STALL */
										{
											if(dev->g_pfn_msc_request_get_req!=NULL)
											{
												if (dev->g_pfn_msc_request_get_req(dev->msc_data,0))
												{
													dev->EP0Data.pData = dev->EP0Buf;
													USB_DataInStage(dev);
													goto setup_class_ok;
												}
											}
											else
											{
												goto stall_i;
											}
										}
										break;
									case MSC_REQUEST_PUT_REQ:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
										break;
								}
							}
#endif  /* USB_MSC */
#if USB_AUDIO
							if ((dev->SetupPacket.wIndex.WB.L == USB_ADC_CIF_NUM)  ||       /* IF number correct? */
							(dev->SetupPacket.wIndex.WB.L == USB_ADC_SIF1_NUM) ||
							(dev->SetupPacket.wIndex.WB.L == USB_ADC_SIF2_NUM))
							{
							switch (dev->SetupPacket.bRequest)
							{
								case AUDIO_REQUEST_GET_CUR:
								case AUDIO_REQUEST_GET_MIN:
								case AUDIO_REQUEST_GET_MAX:
								case AUDIO_REQUEST_GET_RES:
									if(dev->g_pfn_adc_if_getrequestt != NULL)
									{
										if (dev->g_pfn_adc_if_getrequestt(dev->adc_data))
										{
											dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
											USB_DataInStage(dev);                                 /* send requested data */
											goto setup_class_ok;
										}
									}
									else
									{
										goto stall_i;
									}
									break;
								case AUDIO_REQUEST_SET_CUR:
									//                case AUDIO_REQUEST_SET_MIN:
									//                case AUDIO_REQUEST_SET_MAX:
									//                case AUDIO_REQUEST_SET_RES:
									dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received */
									goto setup_class_ok;
								}
							}
#endif  /* USB_AUDIO */
#if USB_CDC
							if ((dev->SetupPacket.wIndex.WB.L == USB_CDC_CIF_NUM)  ||       /* IF number correct? */
							(dev->SetupPacket.wIndex.WB.L == USB_CDC_DIF_NUM))
							{
								switch (dev->SetupPacket.bRequest)
								{
									case CDC_SEND_ENCAPSULATED_COMMAND://out data
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_ENCAPSULATED_RESPONSE://in data
										if(dev->g_pfn_cdc_GetEncapsulatedResponse != NULL)
										{
											if (dev->g_pfn_cdc_GetEncapsulatedResponse(dev->cdc_data,0))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_COMM_FEATURE://out data
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_COMM_FEATURE://in data
										if(dev->g_pfn_cdc_GetCommFeature != NULL)
										{
											if (dev->g_pfn_cdc_GetCommFeature(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_CLEAR_COMM_FEATURE://out none
										if(dev->g_pfn_cdc_ClearCommFeature != NULL)
										{
											if (dev->g_pfn_cdc_ClearCommFeature(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_AUX_LINE_STATE://out none
										if(dev->g_pfn_cdc_SetAuxLineState != NULL)
										{
											if (dev->g_pfn_cdc_SetAuxLineState(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_HOOK_STATE://out none
										if(dev->g_pfn_cdc_SetHookState != NULL)
										{
											if (dev->g_pfn_cdc_SetHookState(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_PULSE_SETUP://out none
										if(dev->g_pfn_cdc_PulseSetup != NULL)
										{
											if (dev->g_pfn_cdc_PulseSetup(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SEND_PULSE://out none
										if(dev->g_pfn_cdc_SendPulse != NULL)
										{
											if (dev->g_pfn_cdc_SendPulse(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_PULSE_TIME://out none
										if(dev->g_pfn_cdc_SetPulseTime != NULL)
										{
											if (dev->g_pfn_cdc_SetPulseTime(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_RING_AUX_JACK://out none
										if(dev->g_pfn_cdc_RingAuxJack != NULL)
										{
											if (dev->g_pfn_cdc_RingAuxJack(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_LINE_CODING:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_LINE_CODING:
										if(dev->g_pfn_cdc_GetLineCoding != NULL)
										{
											if (dev->g_pfn_cdc_GetLineCoding(dev->cdc_data,0))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_CONTROL_LINE_STATE:
										if(dev->g_pfn_cdc_SetControlLineState != NULL)
										{
											if (dev->g_pfn_cdc_SetControlLineState(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SEND_BREAK:
										if(dev->g_pfn_cdc_SendBreak != NULL)
										{
											if (dev->g_pfn_cdc_SendBreak(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_RINGER_PARMS:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_RINGER_PARMS:
										if(dev->g_pfn_cdc_GetRingerParms != NULL)
										{
											if (dev->g_pfn_cdc_GetRingerParms(dev->cdc_data,0))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_OPERATION_PARMS:
										if(dev->g_pfn_cdc_SetOperationParms != NULL)
										{
											if (dev->g_pfn_cdc_SetOperationParms(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_GET_OPERATION_PARMS:
										if(dev->g_pfn_cdc_GetOperationParms != NULL)
										{
											if (dev->g_pfn_cdc_GetOperationParms(dev->cdc_data,0))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_LINE_PARMS:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_LINE_PARMS:
										if(dev->g_pfn_cdc_GetLineParms != NULL)
										{
											if (dev->g_pfn_cdc_GetLineParms(dev->cdc_data,0))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_DIAL_DIGITS:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_SET_UNIT_PARAMETER:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_UNIT_PARAMETER:
										if(dev->g_pfn_cdc_GetUnitParameter != NULL)
										{
											if (dev->g_pfn_cdc_GetUnitParameter(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_CLEAR_UNIT_PARAMETER:
										if(dev->g_pfn_cdc_ClearUnitParameter != NULL)
										{
											if (dev->g_pfn_cdc_ClearUnitParameter(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_GET_PROFILE:
										if(dev->g_pfn_cdc_GetProfile != NULL)
										{
											if (dev->g_pfn_cdc_GetProfile(dev->cdc_data,0))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_ETHERNET_MULTICAST_FILTERS:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_SET_ETHERNET_PMP_FILTER:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_ETHERNET_PMP_FILTER:
										if(dev->g_pfn_cdc_GetEthernetPowerManagementPatternFilter != NULL)
										{
											if (dev->g_pfn_cdc_GetEthernetPowerManagementPatternFilter(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_ETHERNET_PACKET_FILTER:
										if(dev->g_pfn_cdc_SetEthernetPacketFilter != NULL)
										{
											if (dev->g_pfn_cdc_SetEthernetPacketFilter(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_GET_ETHERNET_STATISTIC:
										if(dev->g_pfn_cdc_GetEthernetStatistic != NULL)
										{
											if (dev->g_pfn_cdc_GetEthernetStatistic(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_ATM_DATA_FORMAT:
										if(dev->g_pfn_cdc_SetATMDataFormat != NULL)
										{
											if (dev->g_pfn_cdc_SetATMDataFormat(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												USB_StatusInStage(dev);                               /* send Acknowledge */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_GET_ATM_DEVICE_STATISTICS:
										if(dev->g_pfn_cdc_GetATMDeviceStatistics != NULL)
										{
											if (dev->g_pfn_cdc_GetATMDeviceStatistics(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
									case CDC_SET_ATM_DEFAULT_VC:
										dev->EP0Data.pData = dev->EP0Buf;                              /* data to be received, see USB_EVT_OUT */
										xUSBControlOutEnble();
										goto setup_class_ok;
									case CDC_GET_ATM_VC_STATISTICS:
										if(dev->g_pfn_cdc_GetATMVCStatistics != NULL)
										{
											if (dev->g_pfn_cdc_GetATMVCStatistics(dev->cdc_data,dev->SetupPacket.wValue.W))
											{
												dev->EP0Data.pData = dev->EP0Buf;                            /* point to data to be sent */
												USB_DataInStage(dev);                                 /* send requested data */
												goto setup_class_ok;
											}
										}
										else
										{
											goto stall_i;
										}
										break;
								}
							}
#endif  /* USB_CDC */
							goto stall_i;                                              /* not supported */
							/* end case REQUEST_TO_INTERFACE */

						case REQUEST_TO_ENDPOINT:
#if USB_AUDIO
							switch (dev->SetupPacket.bRequest)
							{
								case AUDIO_REQUEST_GET_CUR:
								case AUDIO_REQUEST_GET_MIN:
								case AUDIO_REQUEST_GET_MAX:
								case AUDIO_REQUEST_GET_RES:
									if(dev->g_pfn_adc_ep_getrequestt != NULL)
									{
										if (dev->g_pfn_adc_ep_getrequestt(dev->adc_data))
										{
											dev->EP0Data.pData = dev->EP0Buf;                              /* point to data to be sent */
											USB_DataInStage(dev);                                   /* send requested data */
											goto setup_class_ok;
										}
									}
									else
									{
										goto stall_i;
									}
									break;
								case AUDIO_REQUEST_SET_CUR:
									//              case AUDIO_REQUEST_SET_MIN:
									//              case AUDIO_REQUEST_SET_MAX:
									//              case AUDIO_REQUEST_SET_RES:
									dev->EP0Data.pData = dev->EP0Buf;                                /* data to be received */
									goto setup_class_ok;
							}
#endif  /* USB_AUDIO */
							goto stall_i;
							/* end case REQUEST_TO_ENDPOINT */

						default:
							goto stall_i;
					}
					setup_class_ok:                                                          /* request finished successfully */
					break;  /* end case REQUEST_CLASS */
#endif  /* USB_CLASS */

#if USB_VENDOR
				case REQUEST_VENDOR:
					switch (dev->SetupPacket.bmRequestType.BM.Recipient)
					{

						case REQUEST_TO_DEVICE:
							if(dev->g_pfn_vender_device != NULL)
							{
								if (!dev->g_pfn_vender_device(dev->vender_data, TRUE))
								{
									goto stall_i;                                            /* not supported */
								}
							}
							else
							{
								goto stall_i;
							}
							break;

						case REQUEST_TO_INTERFACE:
							if(dev->g_pfn_vender_interface != NULL)
							{
								if (!dev->g_pfn_vender_interface(dev->vender_data, TRUE))
								{
									goto stall_i;                                            /* not supported */
								}
							}
							else
							{
								goto stall_i;
							}
							break;

						case REQUEST_TO_ENDPOINT:
							if(dev->g_pfn_vender_endpoint != NULL)
							{
								if (!dev->g_pfn_vender_endpoint(dev->vender_data, TRUE))
								{
									goto stall_i;                                            /* not supported */
								}
							}
							else
							{
								goto stall_i;
							}
							break;

						default:
							goto stall_i;
					}

					if (dev->SetupPacket.wLength)
					{
						if (dev->SetupPacket.bmRequestType.BM.Dir == REQUEST_DEVICE_TO_HOST)
						{
							USB_DataInStage(dev);
						}
					}
					else
					{
						USB_StatusInStage(dev);
					}

					break;  /* end case REQUEST_VENDOR */
#endif  /* USB_VENDOR */

				default:
stall_i:
					xUSBEndpointStallSet(0x80);
					dev->EP0Data.Count = 0;
					break;
			}
			break;  /* end case USB_EVT_SETUP */

		case USB_EVT_OUT:
			if (dev->SetupPacket.bmRequestType.BM.Dir == REQUEST_HOST_TO_DEVICE)
			{
				if (dev->EP0Data.Count)
				{                                             /* still data to receive ? */
					USB_DataOutStage(dev);                                            /* receive data */
					if (dev->EP0Data.Count == 0)
					{                                      /* data complete ? */
						switch (dev->SetupPacket.bmRequestType.BM.Type)
						{

							case REQUEST_STANDARD:
								goto stall_i;                                            /* not supported */

#if (USB_CLASS)
							case REQUEST_CLASS:
								switch (dev->SetupPacket.bmRequestType.BM.Recipient)
								{
									case REQUEST_TO_DEVICE:
										goto stall_i;                                        /* not supported */

									case REQUEST_TO_INTERFACE:
#if USB_MSC
										if (dev->SetupPacket.wIndex.WB.L == USB_MSC_IF_NUM)
										{     /* IF number correct? */
											switch (dev->SetupPacket.bRequest)
											{
												case MSC_REQUEST_ADSC:
													if(dev->g_pfn_msc_request_adsc != NULL)
													{
														if (dev->g_pfn_msc_request_adsc(dev->msc_data,0))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case MSC_REQUEST_PUT_REQ:
													if(dev->g_pfn_msc_request_put_req != NULL)
													{
														if (dev->g_pfn_msc_request_put_req(dev->msc_data,dev->SetupPacket.wValue.W))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
											}
										}
#endif  /* USB_MSC */
#if USB_HID
										if (dev->SetupPacket.wIndex.WB.L == USB_HID_IF_NUM)
										{     /* IF number correct? */
											switch (dev->SetupPacket.bRequest)
											{
												case HID_REQUEST_SET_REPORT:
													if(dev->g_pfn_hid_set_report != NULL)
													{
														if (dev->g_pfn_hid_set_report(dev->hid_data))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
											}
										}
#endif  /* USB_HID */
#if USB_AUDIO
										if ((dev->SetupPacket.wIndex.WB.L == USB_ADC_CIF_NUM)  || /* IF number correct? */
										(dev->SetupPacket.wIndex.WB.L == USB_ADC_SIF1_NUM) ||
										(dev->SetupPacket.wIndex.WB.L == USB_ADC_SIF2_NUM))
										{
											switch (dev->SetupPacket.bRequest)
											{
												case AUDIO_REQUEST_SET_CUR:
													//                      case AUDIO_REQUEST_SET_MIN:
													//                      case AUDIO_REQUEST_SET_MAX:
													//                      case AUDIO_REQUEST_SET_RES:
													if(dev->g_pfn_adc_if_setrequestt != NULL)
													{
														if (dev->g_pfn_adc_if_setrequestt(dev->adc_data))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
											}
										}
#endif  /* USB_AUDIO */
#if USB_CDC
										if ((dev->SetupPacket.wIndex.WB.L == USB_CDC_CIF_NUM)  || /* IF number correct? */
										(dev->SetupPacket.wIndex.WB.L == USB_CDC_DIF_NUM))
										{
											switch (dev->SetupPacket.bRequest)
											{
												case CDC_SEND_ENCAPSULATED_COMMAND:
													if(dev->g_pfn_cdc_SendEncapsulatedCommand != NULL)
													{
														if (dev->g_pfn_cdc_SendEncapsulatedCommand(dev->cdc_data,0))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_COMM_FEATURE:
													if(dev->g_pfn_cdc_SetCommFeature != NULL)
													{
														if (dev->g_pfn_cdc_SetCommFeature(dev->cdc_data,dev->SetupPacket.wValue.W))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_LINE_CODING:
													if(dev->g_pfn_cdc_SetLineCoding != NULL)
													{
														if (dev->g_pfn_cdc_SetLineCoding(dev->cdc_data,0))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_RINGER_PARMS:
													if(dev->g_pfn_cdc_SetLineCoding != NULL)
													{
														if (dev->g_pfn_cdc_SetLineCoding(dev->cdc_data,0))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_LINE_PARMS:
													if(dev->g_pfn_cdc_SetLineParms != NULL)
													{
														if (dev->g_pfn_cdc_SetLineParms(dev->cdc_data,dev->SetupPacket.wValue.W))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_DIAL_DIGITS:
													if(dev->g_pfn_cdc_DialDigits != NULL)
													{
														if (dev->g_pfn_cdc_DialDigits(dev->cdc_data,0))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_UNIT_PARAMETER:
													if(dev->g_pfn_cdc_SetUnitParameter != NULL)
													{
														if (dev->g_pfn_cdc_SetUnitParameter(dev->cdc_data,dev->SetupPacket.wValue.W))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_ETHERNET_MULTICAST_FILTERS:
													if(dev->g_pfn_cdc_SetEthernetMulticastFilters != NULL)
													{
														if (dev->g_pfn_cdc_SetEthernetMulticastFilters(dev->cdc_data,dev->SetupPacket.wValue.W))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_ETHERNET_PMP_FILTER:
													if(dev->g_pfn_cdc_SetEthernetPowerManagementPatternFilter != NULL)
													{
														if (dev->g_pfn_cdc_SetEthernetPowerManagementPatternFilter(dev->cdc_data,dev->SetupPacket.wValue.W))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;
												case CDC_SET_ATM_DEFAULT_VC:
													if(dev->g_pfn_cdc_SetATMDefaultVC != NULL)
													{
														if (dev->g_pfn_cdc_SetATMDefaultVC(dev->cdc_data,0))
														{
															USB_StatusInStage(dev);                         /* send Acknowledge */
															goto out_class_ok;
														}
													}
													else
													{
														goto stall_i;
													}
													break;

											}
										}
#endif  /* USB_CDC */
										goto stall_i;
										/* end case REQUEST_TO_INTERFACE */

									case REQUEST_TO_ENDPOINT:
#if USB_AUDIO
										switch (dev->SetupPacket.bRequest)
										{
											case AUDIO_REQUEST_SET_CUR:
												//                    case AUDIO_REQUEST_SET_MIN:
												//                    case AUDIO_REQUEST_SET_MAX:
												//                    case AUDIO_REQUEST_SET_RES:
												if(dev->g_pfn_adc_ep_setrequestt != NULL)
												{
													if (dev->g_pfn_adc_ep_setrequestt(dev->adc_data))
													{
														USB_StatusInStage(dev);                           /* send Acknowledge */
														goto out_class_ok;
													}
												}
												else
												{
													goto stall_i;
												}
												break;
										}
#endif  /* USB_AUDIO */
										goto stall_i;
										/* end case REQUEST_TO_ENDPOINT */

									default:
										goto stall_i;
								}
out_class_ok:                                                            /* request finished successfully */
								break; /* end case REQUEST_CLASS */
#endif  /* USB_CLASS */

#if USB_VENDOR
							case REQUEST_VENDOR:
								switch (dev->SetupPacket.bmRequestType.BM.Recipient)
								{

									case REQUEST_TO_DEVICE:
										if(dev->g_pfn_vender_device != NULL)
										{
											if (!dev->g_pfn_vender_device(dev->vender_data, TRUE))
											{
												goto stall_i;                                            /* not supported */
											}
										}
										else
										{
											goto stall_i;
										}
										break;

									case REQUEST_TO_INTERFACE:
										if(dev->g_pfn_vender_interface != NULL)
										{
											if (!dev->g_pfn_vender_interface(dev->vender_data, TRUE))
											{
												goto stall_i;                                            /* not supported */
											}
										}
										else
										{
											goto stall_i;
										}
										break;

									case REQUEST_TO_ENDPOINT:
										if(dev->g_pfn_vender_endpoint != NULL)
										{
											if (!dev->g_pfn_vender_endpoint(dev->vender_data, TRUE))
											{
												goto stall_i;                                            /* not supported */
											}
										}
										else
										{
											goto stall_i;
										}
										break;

									default:
										goto stall_i;
								}

								USB_StatusInStage(dev);

								break;  /* end case REQUEST_VENDOR */
#endif  /* USB_VENDOR */

							default:
								goto stall_i;
						}
					}
				}
			}
			else
			{
				USB_StatusOutStage(dev);                                            /* receive Acknowledge */
			}
			break;  /* end case USB_EVT_OUT */

		case USB_EVT_IN :
			if (dev->SetupPacket.bmRequestType.BM.Dir == REQUEST_DEVICE_TO_HOST)
			{
				xUSBControlOutEnble();
				USB_DataInStage(dev);                                               /* send data */
			}
			else
			{
				if (dev->USB_DeviceAddress & 0x80)
				{
					dev->USB_DeviceAddress &= 0x7F;
					xUSBSetAddress(dev->USB_DeviceAddress);
				}
			}
			break;  /* end case USB_EVT_IN */

		case USB_EVT_OUT_STALL:
			xUSBEndpointStallClear(0x00);
			break;

		case USB_EVT_IN_STALL:
			xUSBEndpointStallClear(0x80);
			break;

	}
}

/********************************************************************************************************//**
 * @brief     USB_Init - Initialization of the  USB
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void USB_Init(USB_ENU_Dev *dev)
{
  xUSBEventHandler(0,(xtEventCallback)USB_EndPoint0,(void *)dev );
  xUSBInit();
}

/********************************************************************************************************//**
 * @brief     USB conecet - pull up the USB to conecet to the host
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @param[in] con : TRUE \ FALSE
 * @return    None
************************************************************************************************************/
void USB_conecet(USB_ENU_Dev *dev, uint32_t con)
{
  xUSBConnect(con);
}


