/*****************************************************************************
 *      U S B  -  C D C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: USB_CDC_CONFIG.h
 * @brief	: USB CDC Custom Configuration
 * @version	: 1.1
 * @date	: 10. MAR. 2010
 * @author	: CooCox
 ****************************************************************************/
#ifndef __USB_CDC_CONFIG_H__
#define __USB_CDC_CONFIG_H__

/**********************************************************************
 *  CDC vendor ID and product ID
 **********************************************************************/
#define USB_CDC_BUFSIZE     64                             /*!<Max Communication Device Buffer Size*/
#define USB_VENDOR_ID       0x1FC9 	// Vendor ID
#define USB_PROD_ID         0x0003	// Product ID
#define USB_DEVICE          0x0100	// Device ID

/**********************************************************************
 *  CDC Data In/Out Endpoint Address
 **********************************************************************/
#define CDC_DEP_IN       0x84
#define CDC_DEP_OUT      0x03
#define USB_CDC_BUFSIZE  64
#define CDC_BUF_SIZE     (64)                /*Output buffer in bytes (power 2)*/

/**********************************************************************
 *  CDC Communication In Endpoint Address
 **********************************************************************/
#define CDC_CEP_IN       0x82

#endif  /* __USB_CDC_CONFIG_H__ */
