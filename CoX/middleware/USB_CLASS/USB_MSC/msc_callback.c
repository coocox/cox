
#include "msc_callback.h"
#include <stdio.h>


void MSC_SetCSW(USBMSC_Dev *dev);
void MSC_SetStallEP(USBMSC_Dev *dev,uint32_t EPNum);
void MSC_Event(USBMSC_Dev *dev);

/********************************************************************************************************//**
 * @brief     USB MSC data in format
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
uint32_t DataInFormat (USBMSC_Dev *dev)
{

	if (dev->CBW.dDataLength == 0)
	{
		dev->CSW.bStatus = CSW_PHASE_ERROR;
		MSC_SetCSW(dev);
		return (FALSE);
	}
	if ((dev->CBW.bmFlags & 0x80) == 0)
	{
		MSC_SetStallEP(dev,MSC_EP_OUT);
		dev->CSW.bStatus = CSW_PHASE_ERROR;
		MSC_SetCSW(dev);
		return (FALSE);
	}
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     USB MSC data in transfer
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void DataInTransfer (USBMSC_Dev *dev)
{

	if (dev->BulkLen >= dev->CBW.dDataLength)
	{
		dev->BulkLen = dev->CBW.dDataLength;
		dev->BulkStage = MSC_BS_DATA_IN_LAST;
	}
	else
	{
		dev->BulkStage = MSC_BS_DATA_IN_LAST_STALL; /* short or zero packet */
	}

	xUSBEndpointWrite(MSC_EP_IN, dev->BulkBuf, dev->BulkLen);

	dev->CSW.dDataResidue -= dev->BulkLen;
	dev->CSW.bStatus = CSW_CMD_PASSED;
}

/********************************************************************************************************//**
 * @brief     USB MSC read write setup
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
uint32_t MSC_RWSetup (USBMSC_Dev *dev)
{
	uint32_t n;

	/* Logical Block Address of First Block */
	n = (dev->CBW.CB[2] << 24) |
		(dev->CBW.CB[3] << 16) |
		(dev->CBW.CB[4] <<  8) |
		(dev->CBW.CB[5] <<  0);

	dev->Offset = n * MSC_BlockSize;

	/* Number of Blocks to transfer */
	switch (dev->CBW.CB[0])
	{
		case SCSI_READ10:
		case SCSI_WRITE10:
		case SCSI_VERIFY10:
			n = (dev->CBW.CB[7] <<  8) |
			(dev->CBW.CB[8] <<  0);
			break;

		case SCSI_READ12:
		case SCSI_WRITE12:
			n = (dev->CBW.CB[6] << 24) |
			(dev->CBW.CB[7] << 16) |
			(dev->CBW.CB[8] <<  8) |
			(dev->CBW.CB[9] <<  0);
			break;
	}

	dev->Length = n * MSC_BlockSize;

	if (dev->CBW.dDataLength == 0)
	{
		/* host requests no data */
		dev->CSW.bStatus = CSW_CMD_FAILED;
		MSC_SetCSW(dev);
		return (FALSE);
	}

	if (dev->CBW.dDataLength != dev->Length)
	{
		if ((dev->CBW.bmFlags & 0x80) != 0)
		{
			/* stall appropriate EP */
			MSC_SetStallEP(dev,MSC_EP_IN);
		}
		else
		{
			MSC_SetStallEP(dev,MSC_EP_IN);
		}

		dev->CSW.bStatus = CSW_CMD_FAILED;
		MSC_SetCSW(dev);

		return (FALSE);
	}

	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     USB MSC get CSW
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_SetCSW(USBMSC_Dev *dev)
{
	dev->CSW.dSignature = MSC_CSW_Signature;
	xUSBEndpointWrite(MSC_EP_IN, (uint8_t *)&dev->CSW, sizeof(dev->CSW));
	dev->BulkStage = MSC_BS_CSW;
}

/********************************************************************************************************//**
 * @brief     Initialization of USB MSC memory
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_InitFlash(USBMSC_Dev *dev)
{
	dev->flash_init(dev->flash_data);
}

/********************************************************************************************************//**
 * @brief     USB MSC read memory
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_MemoryRead(USBMSC_Dev *dev)
{
	uint32_t n;

	if (dev->Length > MSC_MAX_PACKET)
	{
		n = MSC_MAX_PACKET;
	}
	else
	{
		n = dev->Length;
	}

	if ((dev->Offset + n) > MSC_MemorySize)
	{
		n = MSC_MemorySize - dev->Offset;
		dev->BulkStage = MSC_BS_DATA_IN_LAST_STALL;
	}
	if(dev->flash_read != NULL)
	{
		dev->flash_read(dev->flash_data, dev->Offset, dev->BulkBuf, n);
	}
	xUSBEndpointWrite(MSC_EP_IN, dev->BulkBuf, n);
	dev->Offset += n;
	dev->Length -= n;

	dev->CSW.dDataResidue -= n;

	if (dev->Length == 0)
	{
		dev->BulkStage = MSC_BS_DATA_IN_LAST;
	}

	if (dev->BulkStage != MSC_BS_DATA_IN)
	{
		dev->CSW.bStatus = CSW_CMD_PASSED;
	}
}

/********************************************************************************************************//**
 * @brief     USB MSC write memory
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_MemoryWrite(USBMSC_Dev *dev)
{
	if ((dev->Offset + dev->BulkLen) > MSC_MemorySize)
	{
		dev->BulkLen = MSC_MemorySize - dev->Offset;
		dev->BulkStage = MSC_BS_CSW;
		MSC_SetStallEP(dev,MSC_EP_OUT);
	}
	if(dev->flash_write != NULL)
	{
		dev->flash_write(dev->flash_data, dev->Offset, dev->BulkBuf, dev->BulkLen);
	}
	dev->Offset += dev->BulkLen;
	dev->Length -= dev->BulkLen;
	dev->CSW.dDataResidue -= dev->BulkLen;
	if ((dev->Length == 0) || (dev->BulkStage == MSC_BS_CSW))
	{
		dev->CSW.bStatus = CSW_CMD_PASSED;
		MSC_SetCSW(dev);

	}

}
/********************************************************************************************************//**
 * @brief     USB MSC verify memory
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_MemoryVerify(USBMSC_Dev *dev)
{
	uint32_t n,MemOK;

	if ((dev->Offset + dev->BulkLen) > MSC_MemorySize)
	{
		dev->BulkLen = MSC_MemorySize - dev->Offset;
		dev->BulkStage = MSC_BS_CSW;
		MSC_SetStallEP(dev, MSC_EP_OUT);
	}
	if(dev->flash_read != NULL)
	{
		dev->flash_read(dev->flash_data, dev->Offset, dev->BulkBuf, dev->BulkLen);
	}
	for (n = 0; n < dev->BulkLen; n++)
	{
		if (dev->Memory[n] != dev->BulkBuf[n])
		{
			MemOK = FALSE;
			break;
		}
	}

	dev->Offset += dev->BulkLen;
	dev->Length -= dev->BulkLen;

	dev->CSW.dDataResidue -= dev->BulkLen;

	if ((dev->Length == 0) || (dev->BulkStage == MSC_BS_CSW))
	{
		dev->CSW.bStatus = (MemOK) ? CSW_CMD_PASSED : CSW_CMD_FAILED;
		MSC_SetCSW(dev);
	}
}

/********************************************************************************************************//**
 * @brief     USB MSC set stall end point
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            EPNum : logic number of end point
 * @return    None
************************************************************************************************************/
void MSC_SetStallEP(USBMSC_Dev *dev,uint32_t EPNum)
{

	dev->usb_enu.USB_EndPointHalt  |=  (EPNum & 0x80) ? ((1 << 16) << (EPNum & 0x0F)) : (1 << EPNum);
}

/********************************************************************************************************//**
 * @brief     USB MSC  test unit ready
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_TestUnitReady(USBMSC_Dev *dev)
{
	if (dev->CBW.dDataLength != 0)
	{
		if ((dev->CBW.bmFlags & 0x80) != 0)
		{
			MSC_SetStallEP(dev,MSC_EP_IN);
		}
		else
		{
			MSC_SetStallEP(dev,MSC_EP_OUT);
		}
	}

	dev->CSW.bStatus = CSW_CMD_PASSED;
	MSC_SetCSW(dev);
}

/********************************************************************************************************//**
 * @brief     USB MSC request sense
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_RequestSense(USBMSC_Dev *dev)
{
	if (!DataInFormat(dev)) return;

	dev->BulkBuf[ 0] = 0x70;          /* Response Code */
	dev->BulkBuf[ 1] = 0x00;
	dev->BulkBuf[ 2] = 0x00;//0x02;          /* Sense Key *///DIFF
	dev->BulkBuf[ 3] = 0x00;
	dev->BulkBuf[ 4] = 0x00;
	dev->BulkBuf[ 5] = 0x00;
	dev->BulkBuf[ 6] = 0x00;
	dev->BulkBuf[ 7] = 0x0A;          /* Additional Length */
	dev->BulkBuf[ 8] = 0x00;
	dev->BulkBuf[ 9] = 0x00;
	dev->BulkBuf[10] = 0x00;
	dev->BulkBuf[11] = 0x00;
	dev->BulkBuf[12] = 0x00;//0x30;          /* ASC  *///diff
	dev->BulkBuf[13] = 0x00;//0x01;          /* ASCQ *///diff
	dev->BulkBuf[14] = 0x00;
	dev->BulkBuf[15] = 0x00;
	dev->BulkBuf[16] = 0x00;
	dev->BulkBuf[17] = 0x00;

	dev->BulkLen = 18;
	DataInTransfer(dev);
}

/********************************************************************************************************//**
 * @brief     USB MSC  inquiry
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_Inquiry(USBMSC_Dev *dev)
{
	if (!DataInFormat(dev)) return;

	dev->BulkBuf[ 0] = 0x00;          /* Direct Access Device */
	dev->BulkBuf[ 1] = 0x80;          /* RMB = 1: Removable Medium */
	dev->BulkBuf[ 2] = 0x00;          /* Version: No conformance claim to standard */
	dev->BulkBuf[ 3] = 0x01;

	dev->BulkBuf[ 4] = 36-4;          /* Additional Length */
	dev->BulkBuf[ 5] = 0x80;          /* SCCS = 1: Storage Controller Component */
	dev->BulkBuf[ 6] = 0x00;
	dev->BulkBuf[ 7] = 0x00;

	dev->BulkBuf[ 8] = 'N';           /* Vendor Identification */
	dev->BulkBuf[ 9] = 'O';
	dev->BulkBuf[10] = 'V';
	dev->BulkBuf[11] = 'O';
	dev->BulkBuf[12] = 'T';
	dev->BulkBuf[13] = 'O';
	dev->BulkBuf[14] = 'N';
	dev->BulkBuf[15] = ' ';

	dev->BulkBuf[16] = 'N';           /* Product Identification */
	dev->BulkBuf[17] = 'U';
	dev->BulkBuf[18] = 'C';
	dev->BulkBuf[19] = '1';
	dev->BulkBuf[20] = '4';
	dev->BulkBuf[21] = 'X';
	dev->BulkBuf[22] = 'x';
	dev->BulkBuf[23] = ' ';
	dev->BulkBuf[24] = 'D';
	dev->BulkBuf[25] = 'i';
	dev->BulkBuf[26] = 's';
	dev->BulkBuf[27] = 'k';
	dev->BulkBuf[28] = ' ';
	dev->BulkBuf[29] = ' ';
	dev->BulkBuf[30] = ' ';
	dev->BulkBuf[31] = ' ';

	dev->BulkBuf[32] = '1';           /* Product Revision Level */
	dev->BulkBuf[33] = '.';
	dev->BulkBuf[34] = '0';
	dev->BulkBuf[35] = ' ';

	dev->BulkLen = 36;
	DataInTransfer(dev);
}

/********************************************************************************************************//**
 * @brief     USB MSC  mode sense 6
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_ModeSense6(USBMSC_Dev *dev)
{
	if (!DataInFormat(dev)) return;

	dev->BulkBuf[ 0] = 0x03;
	dev->BulkBuf[ 1] = 0x00;
	dev->BulkBuf[ 2] = 0x00;
	dev->BulkBuf[ 3] = 0x00;

	dev->BulkLen = 4;
	DataInTransfer(dev);
}

/********************************************************************************************************//**
 * @brief     USB MSC mode sense 10
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_ModeSense10(USBMSC_Dev *dev)
{

	if (!DataInFormat(dev)) return;

	dev->BulkBuf[ 0] = 0x00;
	dev->BulkBuf[ 1] = 0x06;
	dev->BulkBuf[ 2] = 0x00;
	dev->BulkBuf[ 3] = 0x00;
	dev->BulkBuf[ 4] = 0x00;
	dev->BulkBuf[ 5] = 0x00;
	dev->BulkBuf[ 6] = 0x00;
	dev->BulkBuf[ 7] = 0x00;

	dev->BulkLen = 8;
	DataInTransfer(dev);
}

/********************************************************************************************************//**
 * @brief     USB MSC read format capacity
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_ReadFormatCapacity(USBMSC_Dev *dev)
{
	if (!DataInFormat(dev)) return;

	dev->BulkBuf[ 0] = 0x00;
	dev->BulkBuf[ 1] = 0x00;
	dev->BulkBuf[ 2] = 0x00;
	dev->BulkBuf[ 3] = 0x08;          /* Capacity List Length */

	/* Block Count */
	dev->BulkBuf[ 4] = (MSC_BlockCount >> 24) & 0xFF;
	dev->BulkBuf[ 5] = (MSC_BlockCount >> 16) & 0xFF;
	dev->BulkBuf[ 6] = (MSC_BlockCount >>  8) & 0xFF;
	dev->BulkBuf[ 7] = (MSC_BlockCount >>  0) & 0xFF;

	/* Block Length */
	dev->BulkBuf[ 8] = 0x02;          /* Descriptor Code: Formatted Media */
	dev->BulkBuf[ 9] = (MSC_BlockSize >> 16) & 0xFF;
	dev->BulkBuf[10] = (MSC_BlockSize >>  8) & 0xFF;
	dev->BulkBuf[11] = (MSC_BlockSize >>  0) & 0xFF;

	dev->BulkLen = 12;
	DataInTransfer(dev);
}

/********************************************************************************************************//**
 * @brief     USB MSC read capacity
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_ReadCapacity(USBMSC_Dev *dev)
{
	if (!DataInFormat(dev)) return;

	/* Last Logical Block */
	dev->BulkBuf[ 0] = ((MSC_BlockCount - 1) >> 24) & 0xFF;
	dev->BulkBuf[ 1] = ((MSC_BlockCount - 1) >> 16) & 0xFF;
	dev->BulkBuf[ 2] = ((MSC_BlockCount - 1) >>  8) & 0xFF;
	dev->BulkBuf[ 3] = ((MSC_BlockCount - 1) >>  0) & 0xFF;

	/* Block Length */
	dev->BulkBuf[ 4] = (MSC_BlockSize >> 24) & 0xFF;
	dev->BulkBuf[ 5] = (MSC_BlockSize >> 16) & 0xFF;
	dev->BulkBuf[ 6] = (MSC_BlockSize >>  8) & 0xFF;
	dev->BulkBuf[ 7] = (MSC_BlockSize >>  0) & 0xFF;

	dev->BulkLen = 8;
	DataInTransfer(dev);
}

/********************************************************************************************************//**
 * @brief     USB MSC get CBW
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_GetCBW(USBMSC_Dev *dev)
{

	uint32_t n;

	for (n = 0; n < dev->BulkLen; n++)
	{
		*((uint8_t *)&dev->CBW + n) = dev->BulkBuf[n];
	}
	if ((dev->BulkLen == sizeof(dev->CBW)) && (dev->CBW.dSignature == MSC_CBW_Signature))
	{
		/* Valid CBW */
		dev->CSW.dTag = dev->CBW.dTag;
		dev->CSW.dDataResidue = dev->CBW.dDataLength;
		if ((dev->CBW.bLUN      != 0) ||
			(dev->CBW.bCBLength <  1) ||
			(dev->CBW.bCBLength > 16)   )
		{
			fail:
			dev->CSW.bStatus = CSW_CMD_FAILED;
			MSC_SetCSW(dev);
		}
		else
		{
			switch (dev->CBW.CB[0])
			{
				case SCSI_TEST_UNIT_READY://SCSI_TEST_UNIT_READY!
					MSC_TestUnitReady(dev);
					break;
				case SCSI_REQUEST_SENSE://SCSI_REQUEST_SENSE!
					MSC_RequestSense(dev);
//					printf("       SCSI_REQUEST_SENSE!\n\r");
					break;
				case SCSI_FORMAT_UNIT:
					goto fail;
				case SCSI_INQUIRY://SCSI_INQUIRY
					MSC_Inquiry(dev);
					break;
				case SCSI_START_STOP_UNIT:
					goto fail;
				case SCSI_MEDIA_REMOVAL://SCSI_MEDIA_REMOVAL!
//					printf("       SCSI_MEDIA_REMOVAL!\n\r");
					dev->CSW.bStatus = CSW_CMD_PASSED;
					MSC_SetCSW(dev);
					break;//goto fail;
				case SCSI_MODE_SELECT6:
					goto fail;
				case SCSI_MODE_SENSE6://SCSI_MODE_SENSE6!
					MSC_ModeSense6(dev);
					break;
				case SCSI_MODE_SELECT10:
					goto fail;
				case SCSI_MODE_SENSE10:
					MSC_ModeSense10(dev);
					break;
				case SCSI_READ_FORMAT_CAPACITIES://READ_FORMAT_CAPACITIES!
					MSC_ReadFormatCapacity(dev);
					break;
				case SCSI_READ_CAPACITY://SCSI_READ_CAPACITY!
					MSC_ReadCapacity(dev);
					break;
				case SCSI_READ10://SCSI_READ10!
				case SCSI_READ12:
//					printf("       SCSI_READ10!\n\r");
					if(MSC_RWSetup(dev))
					{
						if ((dev->CBW.bmFlags & 0x80) != 0)
						{
							dev->BulkStage = MSC_BS_DATA_IN;
							MSC_MemoryRead(dev);
						}
						else
						{
							/* direction mismatch */
							MSC_SetStallEP(dev,MSC_EP_IN);
							dev->CSW.bStatus = CSW_PHASE_ERROR;
							MSC_SetCSW(dev);
						}
					}
					break;
				case SCSI_WRITE10://SCSI_WRITE10!
				case SCSI_WRITE12:
//					printf("       SCSI_WRITE10!\n\r");
					if (MSC_RWSetup(dev))
					{
						if ((dev->CBW.bmFlags & 0x80) == 0)
						{
							dev->BulkStage = MSC_BS_DATA_OUT;
							if(dev->InitOffset!=NULL)
							{
								*dev->InitOffset = dev->Offset;
							}
							if(dev->TotalLength!=NULL)
							{
								*dev->TotalLength = dev->Length;
							}

						}
						else
						{
							/* direction mismatch */
							MSC_SetStallEP(dev,MSC_EP_IN);
							dev->CSW.bStatus = CSW_PHASE_ERROR;
							MSC_SetCSW(dev);
						}
					}
					break;
				case SCSI_VERIFY10:
					if ((dev->CBW.CB[1] & 0x02) == 0)
					{
						dev->CSW.bStatus = CSW_CMD_PASSED;
						MSC_SetCSW(dev);
						break;
					}
					if (MSC_RWSetup(dev))
					{
						if ((dev->CBW.bmFlags & 0x80) == 0)
						{
							dev->BulkStage = MSC_BS_DATA_OUT;
						}
						else
						{
							MSC_SetStallEP(dev,MSC_EP_IN);
							dev->CSW.bStatus = CSW_PHASE_ERROR;
							MSC_SetCSW(dev);
						}
					}
					break;
				default:
					goto fail;
			}
		}
	}
	else
	{
		/* Invalid CBW */
		MSC_SetStallEP(dev,MSC_EP_IN);
		/* set EP to stay stalled */
		dev->usb_enu.USB_EndPointStall |=  (MSC_EP_IN  & 0x80) ? ((1 << 16) << (MSC_EP_IN  & 0x0F)) : (1 << MSC_EP_IN);
		MSC_SetStallEP(dev,MSC_EP_IN);
		/* set EP to stay stalled */
		dev->usb_enu.USB_EndPointStall |=  (MSC_EP_OUT & 0x80) ? ((1 << 16) << (MSC_EP_OUT & 0x0F)) : (1 << MSC_EP_OUT);
		dev->BulkStage = MSC_BS_ERROR;
	}
}

/********************************************************************************************************//**
 * @brief     USB MSC reset
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            Event: NULL
 * @return    None
************************************************************************************************************/
uint32_t MSC_Reset(USBMSC_Dev *dev, uint32_t Event)
{
	dev->usb_enu.USB_EndPointHalt = 0x00000000;
	dev->CSW.dSignature = 0;
	dev->BulkStage = MSC_BS_CBW;

	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     USB MSC get max LUN
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            Event: NULL
 * @return    None
************************************************************************************************************/
uint32_t MSC_GetMaxLUN(USBMSC_Dev *dev, uint32_t Event)
{
	dev->usb_enu.EP0Buf[0] = 0;                           /* No LUN associated with this device */
	MSC_Event(dev);
	return (TRUE);
}

/********************************************************************************************************//**
 * @brief     Initialization of the USB MSC
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_Open(USBMSC_Dev *dev)
{
	//dev->di_usb_e = &di_usb_enumerate;
	dev->usb_enu.msc_data = dev;
	dev->usb_enu.g_pfn_msc_request_reset       = (PFN_MSC_CALLBACK *)MSC_Reset;
	dev->usb_enu.g_pfn_msc_request_get_max_lun = (PFN_MSC_CALLBACK *)MSC_GetMaxLUN;

	if(dev->flash_init != NULL)
	{
		dev->flash_init(dev->flash_data);
	}
	USB_Init(&dev->usb_enu);
}

/********************************************************************************************************//**
 * @brief     Connect MSC to the host
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            con : TRUE \FALSE
 * @return    None
************************************************************************************************************/
void MSC_Connect(USBMSC_Dev *dev,uint32_t con)
{
  xUSBConnect(con);
}

/********************************************************************************************************//**
 * @brief     Get MSC Configuration statue
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    Configuration statue
************************************************************************************************************/
uint8_t MSC_Configurated(USBMSC_Dev *dev)
{
	return dev->usb_enu.USB_Configuration;
}


/********************************************************************************************************//**
 * @brief     MSC bulk in handle
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            event : event type of endpoint
 * @return    None
************************************************************************************************************/
void bulk_in_handle(USBMSC_Dev *dev,uint32_t Event,
    unsigned long ulMsgParam,
    void *pvMsgData)
{
	switch (dev->BulkStage)
	{
		case MSC_BS_DATA_IN:
			switch (dev->CBW.CB[0])
			{
				case SCSI_READ10:
				case SCSI_READ12:
					MSC_MemoryRead(dev);
					break;
			}
			break;
		case MSC_BS_DATA_IN_LAST:
			MSC_SetCSW(dev);
			break;
		case MSC_BS_DATA_IN_LAST_STALL:
			MSC_SetStallEP(dev,MSC_EP_OUT);
			MSC_SetCSW(dev);
			break;
		case MSC_BS_CSW:
			dev->BulkStage = MSC_BS_CBW;
			break;
	}
}
/********************************************************************************************************//**
 * @brief     MSC bulk out handle
 * @param[in] dev : a point which contains all the global variables which using in this function
 *            event : event type of endpoint
 * @return    None
************************************************************************************************************/
void bulk_out_handle(USBMSC_Dev *dev,uint32_t Event,
    unsigned long ulMsgParam,
    void *pvMsgData)
{
	dev->BulkLen = xUSBEndpointRead(MSC_EP_OUT, dev->BulkBuf);
	switch (dev->BulkStage)
	{
		case MSC_BS_CBW:
			MSC_GetCBW(dev);
			break;
		case MSC_BS_DATA_OUT:
			switch (dev->CBW.CB[0])
			{
				case SCSI_WRITE10:
				case SCSI_WRITE12:
					MSC_MemoryWrite(dev);
					break;
				case SCSI_VERIFY10:
					MSC_MemoryVerify(dev);
					break;
			}
			break;
		default:
			MSC_SetStallEP(dev,MSC_EP_OUT);
			dev->CSW.bStatus = CSW_PHASE_ERROR;
			MSC_SetCSW(dev);
			break;
	}
}

/********************************************************************************************************//**
 * @brief     MSC event callback setup
 * @param[in] dev : a point which contains all the global variables which using in this function
 * @return    None
************************************************************************************************************/
void MSC_Event(USBMSC_Dev *dev)
{
  xUSBEventHandler((MSC_EP_OUT&0xf),(xtEventCallback)bulk_out_handle,(void *)dev);
  xUSBEventHandler((MSC_EP_IN &0xf),(xtEventCallback)bulk_in_handle, (void *)dev);
}


