/*****************************************************************************
 *      U S B  -  C D C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: CDC_CALLBACK.c
 * @brief	: USB Communication Device Class Call Back module
 * @version	: 1.1
 * @date	: 10. MAR. 2011
 * @author	: CooCox
 **************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/
#include "usb_Enumerate.h"
#include "cdc_callback.h"

void CDC_Event(USBCDC_Dev *dev);

/**********************************************************************
 *  Buffer masks
 **********************************************************************/
#define CDC_BUF_SIZE               (64)                /*Output buffer in bytes (power 2)*/
                                                       /*large enough for file transfer  */
#define CDC_BUF_MASK               (CDC_BUF_SIZE-1ul)

/**********************************************************************
 *  Buffer read / write macros
 **********************************************************************/
#define CDC_BUF_RESET(cdcBuf)      (cdcBuf->rdIdx = cdcBuf->wrIdx = 0)
#define CDC_BUF_WR(cdcBuf, dataIn) (cdcBuf->data[CDC_BUF_MASK & cdcBuf->wrIdx++] = (dataIn))
#define CDC_BUF_RD(cdcBuf)         (cdcBuf->data[CDC_BUF_MASK & cdcBuf->rdIdx++])
#define CDC_BUF_EMPTY(cdcBuf)      (cdcBuf->rdIdx == cdcBuf->wrIdx)
#define CDC_BUF_FULL(cdcBuf)       (cdcBuf->rdIdx == cdcBuf->wrIdx+1)
#define CDC_BUF_COUNT(cdcBuf)      (CDC_BUF_MASK & (cdcBuf->wrIdx - cdcBuf->rdIdx))

/**********************************************************************
 *  Function declaration
 **********************************************************************/
unsigned short CDC_GetSerialState (USBCDC_Dev *dev);

/********************************************************************************************************//**
 * @brief      read data from CDC_OutBuf
 * @param[out] buffer : buffer for CDC Out data
 * @param[in]  length : buffer length of CDC Out data
 *             buf    : buffer for CDC Out data
 * @return     The length of the read byte
************************************************************************************************************/
int CDC_RdOutBuf (CDC_BUF_T *buf,char *buffer, const int *length)
{
	int bytesToRead, bytesRead;

	/* Read *length bytes, block if *bytes are not avaialable	*/
	bytesToRead = *length;
	bytesToRead = (bytesToRead < (*length)) ? bytesToRead : (*length);
	bytesRead = bytesToRead;


	// ... add code to check for underrun

	while (bytesToRead--)
	{
		*buffer++ = CDC_BUF_RD(buf);
	}
	return (bytesRead);
}

/********************************************************************************************************//**
 * @brief     Write data to CDC_OutBuf
 * @param[out] buffer : buffer for CDC Out data
 * @param[in]  length : buffer length of CDC Out data
 *             buf    : buffer for CDC Out data
 * @return    The length of the write byte
************************************************************************************************************/
int CDC_WrOutBuf (CDC_BUF_T *buf,const char *buffer, int *length)
{
	int bytesToWrite, bytesWritten;

	// Write *length bytes
	bytesToWrite = *length;
	bytesWritten = bytesToWrite;


	// ... add code to check for overwrite

	while (bytesToWrite)
	{
		CDC_BUF_WR(buf, *buffer++);           // Copy Data to buffer
		bytesToWrite--;
	}

	return (bytesWritten);
}


/********************************************************************************************************//**
 * @brief      Check if character(s) are available at CDC_OutBuf
 * @param[out] availChar : The length of the available byte at CDC_OutBuf
 * @param[in]  buf       : buffer for CDC Out data
 * @return     0
************************************************************************************************************/
int CDC_OutBufAvailChar (CDC_BUF_T *buf,int *availChar)
{

	*availChar = CDC_BUF_COUNT(buf);

	return (0);
}
/* end Buffer handling */


/********************************************************************************************************//**
 * @brief      CDC init
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_Init (USBCDC_Dev *dev)
{
	dev->cdc_device_init (dev->cdc_device,(void *)&dev->CDC_LineCoding);
	dev->CDC_DepInEmpty  = 1;
	dev->CDC_SerialState = CDC_GetSerialState(dev);

//	CDC_BUF_RESET((CDC_BUF_T *)(&dev->CDC_OutBuf));
}


/********************************************************************************************************//**
 * @brief      CDC SendEncapsulatedCommand Request Callback,Called automatically on CDC SEND_ENCAPSULATED_COMMAND Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SendEncapsulatedCommand (USBCDC_Dev *dev)
{

	return (TRUE);
}


/********************************************************************************************************//**
 * @brief      CDC GetEncapsulatedResponse Request Callback,Called automatically on CDC Get_ENCAPSULATED_RESPONSE Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetEncapsulatedResponse (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief      CDC SetCommFeature Request Callback,Called automatically on CDC Set_COMM_FATURE Request
 * @param[in]  wFeatureSelector: FeatureSelector
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetCommFeature (USBCDC_Dev *dev, unsigned short wFeatureSelector)
{

	/* ... add code to handle request */
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief      CDC GetCommFeature Request Callback,Called automatically on CDC Get_COMM_FATURE Request
 * @param[in]  wFeatureSelector : FeatureSelector
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetCommFeature (USBCDC_Dev *dev, unsigned short wFeatureSelector)
{

	/* ... add code to handle request */
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief      CDC ClearCommFeature Request Callback,Called automatically on CDC CLEAR_COMM_FATURE Request
 * @param[in]  wFeatureSelector: FeatureSelector
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_ClearCommFeature (USBCDC_Dev *dev, unsigned short wFeatureSelector)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetAuxLineState Request Callback,Called automatically on CDC SET_AUX_LINE_STATE Request
 * @param[in]  wIsConnect:
 *             - 1  Connect
 *             - 0  Disconnect
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetAuxLineState (USBCDC_Dev *dev, unsigned short wIsConnect)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetHookState Request Callback,Called automatically on CDC SET_HOOK_STATE Request
 * @param[in]  wRelayConfig:
 *              每  0  On hook
 *              每  1  Off hook
 *              -  2  SNOOPING
 *              dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetHookState (USBCDC_Dev *dev, unsigned short wRelayConfig)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC PulseSetup Request Callback,Called automatically on CDC PULSE_SETUP Request
 * @param[in]  wIsEnable:
 *                       0 每 Disable
 *                       1 每 Enable
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_PulseSetup (USBCDC_Dev *dev, unsigned short wIsEnable)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SendPulse Request Callback,Called automatically on CDC SEND_PULSE Request
 * @param[in]  wCycles: contains the number of make/break pulse cycles to generate
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SendPulse (USBCDC_Dev *dev, unsigned short wCycles)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetPulseTime Request Callback,Called automatically on CDC SET_PULSE_TIME Request
 * @param[in]  wTiming: specifies the break time period in the high byte and
 *                      the make time period in the low byte
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetPulseTime (USBCDC_Dev *dev, unsigned short wTiming)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC RingAuxJack Request Callback,Called automatically on CDC RING_AUX_JACK Request
 * @param[in]  wFeatureSelector: wNumberOfRings: contains the number of ring signals to generate on
 *                                               a secondary phone jack of the device.
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_RingAuxJack (USBCDC_Dev *dev, unsigned short wNumberOfRings)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetLineCoding Request Callback, Called automatically on CDC SET_LINE_CODING Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetLineCoding (USBCDC_Dev *dev)
{

	dev->CDC_LineCoding.dwDTERate   =   (dev->usb_enu.EP0Buf[0] <<  0)
								 | (dev->usb_enu.EP0Buf[1] <<  8)
								 | (dev->usb_enu.EP0Buf[2] << 16)
								 | (dev->usb_enu.EP0Buf[3] << 24);
	dev->CDC_LineCoding.bCharFormat =  dev->usb_enu.EP0Buf[4];
	dev->CDC_LineCoding.bParityType =  dev->usb_enu.EP0Buf[5];
	dev->CDC_LineCoding.bDataBits   =  dev->usb_enu.EP0Buf[6];

	dev->cdc_device_deinit(dev->cdc_device);
	dev->cdc_device_init (dev->cdc_device,(void *)&dev->CDC_LineCoding);
//	ser_InitPort (dev->CDC_LineCoding.dwDTERate,
//			      dev->CDC_LineCoding.bDataBits,
//			      dev->CDC_LineCoding.bParityType,
//			      dev->CDC_LineCoding.bCharFormat);
	return (TRUE);
}


/********************************************************************************************************//**
 * @brief      CDC GetLineCoding Request Callback,Called automatically on CDC GET_LINE_CODING Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetLineCoding (USBCDC_Dev *dev,uint32_t para)
{

	dev->usb_enu.EP0Buf[0] = (dev->CDC_LineCoding.dwDTERate >>  0) & 0xFF;
	dev->usb_enu.EP0Buf[1] = (dev->CDC_LineCoding.dwDTERate >>  8) & 0xFF;
	dev->usb_enu.EP0Buf[2] = (dev->CDC_LineCoding.dwDTERate >> 16) & 0xFF;
	dev->usb_enu.EP0Buf[3] = (dev->CDC_LineCoding.dwDTERate >> 24) & 0xFF;
	dev->usb_enu.EP0Buf[4] =  dev->CDC_LineCoding.bCharFormat;
	dev->usb_enu.EP0Buf[5] =  dev->CDC_LineCoding.bParityType;
	dev->usb_enu.EP0Buf[6] =  dev->CDC_LineCoding.bDataBits;

	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetControlLineState Request Callback,Called automatically on CDC SET_CONTROL_LINE_STATE Request
 * @param[in]  wControlSignalBitmap:
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetControlLineState (USBCDC_Dev *dev,unsigned short wControlSignalBitmap)
{

	CDC_Event(dev);
	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SendBreak Request Callback,Called automatically on CDC Set_COMM_FATURE Request
 * @param[in]  wDurationOfBreak:
 *             - 0xFFFF  start of Break
 *             - 0x0000  stop  of Break
 *             - 0x####  Duration of Break
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SendBreak (USBCDC_Dev *dev, unsigned short wDurationOfBreak)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetRingerParms Request Callback,Called automatically on CDC SET_RINGER_PARMS Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetRingerParms (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetRingerParms Request Callback,Called automatically on CDC GET_RINGER_PARMS Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetRingerParms (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetOperationParms Request Callback,Called automatically on CDC SET_OPERATION_PARMS Request
 * @param[in]  wOperationMode:
 *             - 0x2  Host Centric Mode
 *             - 0x1  Standalone Mode
 *             - 0x0  Simple Mode
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetOperationParms (USBCDC_Dev *dev, unsigned short wOperationMode)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetOperationParms Request Callback,Called automatically on CDC GET_OPERATION_PARMS Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetOperationParms (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetLineParms Request Callback,Called automatically on CDC SET_LINE_PARMS Request
 * @param[in]  wLineStateChange:
 *             - 0x0000  Drop the active call on the line.
 *             - 0x0001  Start a new call on the line.
 *             - 0x0002  Apply ringing to the line.
 *             - 0x0003  Remove ringing from the line.
 *             - 0x0004  Switch to a specific call on the line. Data is used to
 *                       pass a 1-byte call index that identifies the call.
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetLineParms (USBCDC_Dev *dev, unsigned short wLineStateChange)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetLineParms Request Callback,Called automatically on CDC GET_LINE_PARMS Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetLineParms (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC DialDigits Request Callback,Called automatically on CDC DIAL_DIGITS Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_DialDigits (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetLineParms Request Callback,Called automatically on CDC SET_LINE_PARMS Request
 * @param[in]  wUnitParameter:
 *             - bEntityId        Unit Id
 *             - bParameterIndex  A zero based value indicating Unit parameter index.
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetUnitParameter (USBCDC_Dev *dev, unsigned short wUnitParameter)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetLineParms Request Callback,Called automatically on CDC GET_LINE_PARMS Request
 * @param[in]  wUnitParameter:
 *             - bEntityId        Unit Id
 *             - bParameterIndex  A zero based value indicating Unit parameter index.
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetUnitParameter (USBCDC_Dev *dev, unsigned short wUnitParameter)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC ClearUnitParameter Request Callback,Called automatically on CDC CLEAR_UNIT_PARAMETER Request
 * @param[in]  wUnitParameter:
 *             - bEntityId        Unit Id
 *             - bParameterIndex  A zero based value indicating Unit parameter index.
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_ClearUnitParameter (USBCDC_Dev *dev, unsigned short wUnitParameter)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetProfile Request Callback,Called automatically on CDC GET_PROFILE Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetProfile (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetEthernetMulticastFilters Request Callback,Called automatically on
 *             CDC SET_ETHERNET_MULTICAST_FILTERS Request
 * @param[in]  wNumberOfFilters: Number of filters (N)
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetEthernetMulticastFilters (USBCDC_Dev *dev, unsigned short wNumberOfFilters)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetEthernetPowerManagementPatternFilter Request Callback,Called automatically on
 *             CDC SET_ETHERNET_PMP_FILTER Request
 * @param[in]  wNumberOfFilters: Number of filters (N)
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetEthernetPowerManagementPatternFilter (USBCDC_Dev *dev, unsigned short wNumberOfFilters)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetEthernetPowerManagementPatternFilter Request Callback,Called automatically on
 *             CDC GET_ETHERNET_PMP_FILTER Request
 * @param[in]  wNumberOfFilters: Number of filters (N)
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetEthernetPowerManagementPatternFilter (USBCDC_Dev *dev, unsigned short wNumberOfFilters)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetEthernetPacketFilter Request Callback,Called automatically on
 *             CDC SET_ETHERNET_PACKET_FILTER Request
 * @param[in]  wPacketFilterBitmap:
 *              - D0 PACKET_TYPE_PROMISCUOUS
 *              - D1 PACKET_TYPE_ALL_MULTICAST
 *              - D2 PACKET_TYPE_DIRECTED
 *              - D3 PACKET_TYPE_BROADCAST
 *              - D4 PACKET_TYPE_MULTICAST
 *              dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetEthernetPacketFilter (USBCDC_Dev *dev, unsigned short wPacketFilterBitmap)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetEthernetStatistic Request Callback,Called automatically on
 *             CDC GET_ETHERNET_STATISTIC Request
 * @param[in]  wFeatureSelector:
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetEthernetStatistic (USBCDC_Dev *dev, unsigned short wFeatureSelector)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetATMDataFormat Request Callback,Called automatically on
 *             CDC SET_ATM_DATA_FORMAT Request
 * @param[in]  wDataFormat:
 *              - 1  Type 1 format: concatenated ATM cells
 *              - 2  Type 2 format: ATM header template + concatenated ATM cell payloads
 *              - 3  Type 3 format: AAL 5 SDU
 *              dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetATMDataFormat (USBCDC_Dev *dev, unsigned short wDataFormat)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetATMDeviceStatistics Request Callback,Called automatically on
 *             CDC GET_ATM_DEVICE_STATISTICS Request
 * @param[in]  wFeatureSelector:
 *              - 0  Reserved for future use
 *              - 1  The number of cells that have been sent upstream to the WAN link by the ATM layer.
 *              - 2  The number of cells that have been received downstream from the WAN link by the ATM layer.
 *              - 3  The number of cells that have been received downstream from the WAN link by the ATM layer
 *                   and discarded due to congestion on the USB link.
 *              - 4  The number of cells that have been received downstream from the WAN link by the ATM layer
 *                   and discarded due to AAL5 CRC errors.
 *              - 5  The number of cells that have been received downstream from the WAN link and discarded
 *                   due to HEC errors in the cell header.
 *              - 6  The number of cells that have been received downstream from the WAN link and have been
 *                   detected with HEC errors in the cell header and successfully corrected.
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetATMDeviceStatistics (USBCDC_Dev *dev, unsigned short wFeatureSelector)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC SetATMDefaultVC Request Callback,Called automatically on
 *             CDC SET_ATM_DEFAULT_VC Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_SetATMDefaultVC (USBCDC_Dev *dev)
{

	/* ... add code to handle request */
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief      CDC GetATMVCStatistics Request Callback,Called automatically on
 *             CDC GET_ATM_VC_STATISTICS Request
 * @param[in]  wFeatureSelector :
 *              - 00 Reserved for future use
 *              - 01 The number of cells that have been sent upstream to the WAN link for the specified
 *                   VPI/VCI since the device has been powered on or reset.
 *              - 02 The number of cells that have been received downstream from the WAN link for the
 *                   specified VPI/VCI since the device has been powered on or reset.
 *             dev : a point which contains all the global variables which using in this function
 * @return     TRUE - Success, FALSE - Error
************************************************************************************************************/
uint32_t CDC_GetATMVCStatistics (USBCDC_Dev *dev, unsigned short wFeatureSelector)
{

	/* ... add code to handle request */
	return (TRUE);
}




/********************************************************************************************************//**
 * @brief      CDC_BulkIn call on DataIn Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 *             event : usb endpoint event type
 * @return     None
************************************************************************************************************/
void bulk_in_handle(USBCDC_Dev *dev,uint32_t Event)
{
//	int numBytesRead, numBytesAvail;
//
//	//ser_AvailChar (&numBytesAvail);
//
//	// ... add code to check for overwrite
//
//	//numBytesRead = ser_Read ((char *)&dev->BulkBufIn[0], &numBytesAvail);
//
//	// send over USB
//	if (numBytesRead > 0)
//	{
//		dev->usb_enu.usb->USB_WriteEP (CDC_DEP_IN, &dev->BulkBufIn[0], numBytesRead);
//	}
//	else
//	{
//		dev->CDC_DepInEmpty = 1;
//	}
} 


/********************************************************************************************************//**
 * @brief      CDC_BulkOut call on DataOut Request
 * @param[in]  dev : a point which contains all the global variables which using in this function
 *             event : usb endpoint event type
 * @return     None
************************************************************************************************************/
void bulk_out_handle(USBCDC_Dev *dev,uint32_t Event)
{
	int numBytesRead;

	// get data from USB into intermediate buffer
	numBytesRead = dev->usb_enu.usb->USB_ReadEP(CDC_DEP_OUT, &dev->BulkBufOut[0]);

	// ... add code to check for overwrite

	// store data in a buffer to transmit it over serial interface
	CDC_WrOutBuf (&dev->CDC_OutBuf,(char *)&dev->BulkBufOut[0], &numBytesRead);

}

/********************************************************************************************************//**
 * @brief      Send the NETWORK_CONNECTION notification as defined in CDC120.pdf, 6.3.1.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 *             wIsConnected :
 * @return     None
************************************************************************************************************/
void CDC_NetworkConnection (USBCDC_Dev *dev, unsigned short wIsConnected)
{
	/* ... add code to handle Notifications */
}

/********************************************************************************************************//**
 * @brief      Send the RESPONSE_AVAILABLE notification as defined in CDC120.pdf, 6.3.2.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_ResponseAvailable (USBCDC_Dev *dev)
{
	/* ... add code to handle Notifications */
}

/********************************************************************************************************//**
 * @brief      Send the CONNECTION_SPEED_CHANGE notification as defined in CDC120.pdf, 6.3.3.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_ConnectionSpeedChange (USBCDC_Dev *dev)
{
	/* ... add code to handle Notifications */
}

/********************************************************************************************************//**
 * @brief      Send the AUX_JACK_ HOOK_STATE notification as defined in PSTN120.pdf, 6.5.2.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_AuxJackHookState (USBCDC_Dev *dev)
{
	/* ... add code to handle Notifications */
}

/********************************************************************************************************//**
 * @brief      Send the RING_DETECT notification as defined in PSTN120.pdf, 6.5.3.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_RingDetect (USBCDC_Dev *dev)
{
	/* ... add code to handle Notifications */
}

/********************************************************************************************************//**
 * @brief      Send the CALL_STATE_CHANGE notification as defined in PSTN120.pdf, 6.5.5.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 *             wCallIndex :
 * @return     None
************************************************************************************************************/
void CDC_CallStateChange (USBCDC_Dev *dev, unsigned short wCallIndex)
{
	/* ... add code to handle Notifications */
}

/********************************************************************************************************//**
 * @brief      Send the LINE_STATE_CHANGE notification as defined in PSTN120.pdf, 6.5.6.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_LineStateChange (USBCDC_Dev *dev, unsigned short wLineState)
{
	/* ... add code to handle Notifications */
}



/********************************************************************************************************//**
 * @brief      Get the SERIAL_STATE as defined in PSTN120.pdf, 6.5.4, Table 31.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     SerialState as defined in PSTN120.pdf
************************************************************************************************************/
unsigned short CDC_GetSerialState (USBCDC_Dev *dev)
{
	unsigned short temp;

	dev->CDC_SerialState = 0;
	//ser_LineState (&temp);

	if (temp & 0x8000)  dev->CDC_SerialState |= CDC_SERIAL_STATE_RX_CARRIER;
	if (temp & 0x2000)  dev->CDC_SerialState |= CDC_SERIAL_STATE_TX_CARRIER;
	if (temp & 0x0010)  dev->CDC_SerialState |= CDC_SERIAL_STATE_BREAK;
	if (temp & 0x4000)  dev->CDC_SerialState |= CDC_SERIAL_STATE_RING;
	if (temp & 0x0008)  dev->CDC_SerialState |= CDC_SERIAL_STATE_FRAMING;
	if (temp & 0x0004)  dev->CDC_SerialState |= CDC_SERIAL_STATE_PARITY;
	if (temp & 0x0002)  dev->CDC_SerialState |= CDC_SERIAL_STATE_OVERRUN;

	return (dev->CDC_SerialState);
}


/********************************************************************************************************//**
 * @brief      Send the SERIAL_STATE notification as defined in PSTN120.pdf, 6.5.4.
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_SerialStateFun (USBCDC_Dev *dev)
{

	dev->NotificationBuf[0] = 0xA1;                           // bmRequestType
	dev->NotificationBuf[1] = CDC_NOTIFICATION_SERIAL_STATE;  // bNotification (SERIAL_STATE)
	dev->NotificationBuf[2] = 0x00;                           // wValue
	dev->NotificationBuf[3] = 0x00;
	dev->NotificationBuf[4] = 0x00;                           // wIndex (Interface #, LSB first)
	dev->NotificationBuf[5] = 0x00;
	dev->NotificationBuf[6] = 0x02;                           // wLength (Data length = 2 bytes, LSB first)
	dev->NotificationBuf[7] = 0x00;
	dev->NotificationBuf[8] = (dev->CDC_SerialState >>  0) & 0xFF; // UART State Bitmap (16bits, LSB first)
	dev->NotificationBuf[9] = (dev->CDC_SerialState >>  8) & 0xFF;

	dev->usb_enu.usb->USB_WriteEP (CDC_CEP_IN, &dev->NotificationBuf[0], 10);   // send notification
}

/********************************************************************************************************//**
 * @brief      CDC VCOM open
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_Open(USBCDC_Dev *dev, USBCDC_Dev *user_config)
{
	dev->usb_enu.cdc_data = dev;
	dev->usb_enu.g_pfn_cdc_GetLineCoding       = (PFN_CDC_CALLBACK *)CDC_GetLineCoding;
	dev->usb_enu.g_pfn_cdc_SetLineCoding       = (PFN_CDC_CALLBACK *)CDC_SetLineCoding;
	dev->usb_enu.g_pfn_cdc_SetCommFeature       = (PFN_CDC_CALLBACK *)CDC_SetCommFeature;
	dev->usb_enu.g_pfn_cdc_SendEncapsulatedCommand       = (PFN_CDC_CALLBACK *)CDC_SendEncapsulatedCommand;
	dev->usb_enu.g_pfn_cdc_SendBreak       = (PFN_CDC_CALLBACK *)CDC_SendBreak;
	dev->usb_enu.g_pfn_cdc_SetControlLineState       = (PFN_CDC_CALLBACK *)CDC_SetControlLineState;


	CDC_Init(dev);
	USB_Init(&dev->usb_enu);
}

/********************************************************************************************************//**
 * @brief      connect CDC to usb host
 * @param[in]  dev : a point which contains all the global variables which using in this function
 * @return     None
************************************************************************************************************/
void CDC_Connect(USBCDC_Dev *dev,uint32_t con)
{
	dev->usb_enu.usb->USB_Connect(con);
}

/********************************************************************************************************//**
 * @brief     Get ADC Configuration statue
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    Configuration statue
************************************************************************************************************/
uint8_t CDC_Configurated(USBCDC_Dev *dev)
{
	return dev->usb_enu.USB_Configuration;
}

/********************************************************************************************************//**
 * @brief     ADC event callback setup
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void CDC_Event(USBCDC_Dev *dev)
{
	dev->usb_enu.usb->USB_Event((CDC_DEP_OUT&0xf),(USB_Event_Handler)bulk_out_handle,(void *)dev);
	dev->usb_enu.usb->USB_Event((CDC_DEP_IN &0xf),(USB_Event_Handler)bulk_in_handle, (void *)dev);
}

/********************************************************************************************************//**
 * @brief     ADC read,data transfer from host to device
 * @param[in] dev  : a point which contains all the global variables which using in this function
 *            rbuf : buffer of read
 *            length  : byte length of read
 * @return    None
************************************************************************************************************/
uint32_t CDC_Read(USBCDC_Dev *dev, uint8_t *rbuf, uint32_t length)
{
	dev->cdc_device_read(dev->cdc_device, dev->CDC_InBuf.data, length);
	return length;
}

/********************************************************************************************************//**
 * @brief     CDC write,data transfer from device to host
 * @param[in] dev  : a point which contains all the global variables which using in this function
 *            wbuf : buffer of write
 *            length  : byte length of write
 * @return    None
************************************************************************************************************/
uint32_t CDC_Write(USBCDC_Dev *dev, uint8_t *wbuf, uint32_t length)
{
	dev->cdc_device_write(dev->cdc_device, wbuf, length);
	return length;
}
