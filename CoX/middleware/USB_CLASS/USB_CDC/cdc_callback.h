/*****************************************************************************
 *      U S B  -  C D C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: CDC_CALLBACK.h
 * @brief	: USB Communication Device Class Call Back module Definitions
 * @version	: 1.1
 * @date	: 10. MAR. 2010
 * @author	: CooCox
 ****************************************************************************/

#ifndef __CDC_CALLBACK_H__
#define __CDC_CALLBACK_H__

#include "usb_enumerate.h"

/***********************************************************************
 * USB CDC call back function definition
 **********************************************************************/
typedef uint32_t (PFN_CDCD_Init_CALLBACK)  (void *dev,void *para);
typedef uint32_t (PFN_CDCD_READ_CALLBACK)  (void *dev, uint8_t *rbuf, uint32_t rlen);
typedef uint32_t (PFN_CDCD_WRITE_CALLBACK) (void *dev, uint8_t *wbuf, uint32_t wlen);
typedef uint32_t (PFN_CDCD_DeInit_CALLBACK)(void *dev);

/**
 * @brief CDC output buffer
 */
typedef struct __CDC_BUF_T
{
	uint8_t data[CDC_BUF_SIZE];
	unsigned int wrIdx;
	unsigned int rdIdx;
} CDC_BUF_T;

/**
 * @brief USB CDC Structure
 */
typedef struct
{
	USB_ENU_Dev     usb_enu;
	CDC_LINE_CODING CDC_LineCoding;
	CDC_BUF_T       CDC_OutBuf;
	CDC_BUF_T       CDC_InBuf;
	unsigned short  CDC_DepInEmpty;
	unsigned char   BulkBufIn[USB_CDC_BUFSIZE];
	unsigned char   BulkBufOut[USB_CDC_BUFSIZE];
	unsigned short  CDC_SerialState;
	unsigned char   NotificationBuf [10];

	PFN_CDCD_Init_CALLBACK   *cdc_device_init;
	PFN_CDCD_READ_CALLBACK   *cdc_device_read;
	PFN_CDCD_WRITE_CALLBACK  *cdc_device_write;
	PFN_CDCD_DeInit_CALLBACK *cdc_device_deinit;
	void *cdc_device;
	void *cdc_para;
} USBCDC_Dev;

/**********************************************************************
 *  CDC buffer handling
 **********************************************************************/
extern int CDC_RdOutBuf        (CDC_BUF_T *buf,char *buffer, const int *length);
extern int CDC_WrOutBuf        (CDC_BUF_T *buf,const char *buffer, int *length);
extern int CDC_OutBufAvailChar (CDC_BUF_T *buf,int *availChar);


/***********************************************************************
 * extern API of this component
 **********************************************************************/
extern void     CDC_Open(USBCDC_Dev *dev, USBCDC_Dev *user_config);
extern void     CDC_Connect(USBCDC_Dev *dev,uint32_t con);
extern uint8_t  CDC_Configurated(USBCDC_Dev *dev);
extern void CDC_Event(USBCDC_Dev *dev);
extern uint32_t CDC_Read(USBCDC_Dev *dev, uint8_t *rbuf, uint32_t length);
extern uint32_t CDC_Write(USBCDC_Dev *dev, uint8_t *wbuf, uint32_t length);



#endif  /* __CDC_CALLBACK_H__ */

