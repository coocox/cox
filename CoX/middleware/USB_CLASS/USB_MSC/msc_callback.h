/*****************************************************************************
 *      U S B  -  M S C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: msc_callback.h
 * @brief	: Mass Storage Class call back Definitions
 * @version	: 1.0
 * @date	: 28. Dec. 2010
 * @author	: CooCox
 ****************************************************************************/

#ifndef __MSC_CALLBACK_H__
#define __MSC_CALLBACK_H__
#include "usb_enumerate.h"

/***********************************************************************
 * USB MSC call back function definition
 **********************************************************************/
typedef uint32_t (PFN_FLASH_Init_CALLBACK) (void *dev);
typedef uint32_t (PFN_FLASH_READ_CALLBACK) (void *dev, uint32_t addr, uint8_t *rbuf, uint32_t rlen);
typedef uint32_t (PFN_FLASH_WRITE_CALLBACK)(void *dev, uint32_t addr, uint8_t *wbuf, uint32_t wlen);
typedef uint32_t (PFN_FLASH_ERASE_CALLBACK)(void *dev, uint32_t addr);


/**
 * @brief USB MSC Structure
 */
typedef struct
{
	USB_ENU_Dev usb_enu;

	PFN_FLASH_Init_CALLBACK *flash_init;
	PFN_FLASH_READ_CALLBACK *flash_read;
	PFN_FLASH_WRITE_CALLBACK *flash_write;
	uint32_t  *TotalLength;                            /* R/W Length */
	uint32_t  *InitOffset;                             /* R/W Offset */
	void   *flash_data;

	MSC_CBW  CBW;                                 /* Command Block Wrapper */
	MSC_CSW  CSW;                                 /* Command Status Wrapper */
	uint8_t   BulkStage;                          /* Bulk Stage */
	uint8_t   BulkBuf[MSC_MAX_PACKET];            /* Bulk In/Out Buffer */
	uint8_t   BulkLen;                            /* Bulk In/Out Length */
	uint32_t  Length;                             /* R/W Length */

	uint32_t  Offset;                             /* R/W Offset */
	uint8_t   Memory[65];
} USBMSC_Dev;

/***********************************************************************
 * extern API of this component
 **********************************************************************/
extern void MSC_Open(USBMSC_Dev *dev);
extern void MSC_Connect(USBMSC_Dev *dev,uint32_t con);
extern uint8_t MSC_Configurated(USBMSC_Dev *dev);
extern void MSC_Event(USBMSC_Dev *dev);

#endif  /* __MSC_CALLBACK_H__ */
