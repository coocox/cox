/*****************************************************************************
 *      U S B  - C O M M O M - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: usb_com_config.h
 * @brief	: usb_com_config
 *            Microprocessors
 * @version	: 1.0
 * @date	: 28. Dec. 2010
 * @author	: CooCox
 ****************************************************************************/
#ifndef __USB_COM_CONFIG_H__
#define __USB_COM_CONFIG_H__

#define USB_POWER           0                              /*!<0=> Bus-powered,1=> Self-powered    */
#define USB_IF_NUM          1                              /*!<Max Number of Interfaces <1-256>    */
#define USB_LOGIC_EP_NUM    16                              /*!<Max Number of Endpoints  <1-32>     */
#define USB_MAX_PACKET0     64                             /*!<Max Endpoint 0 Packet Size          */

#define USB_CLASS           1                              /*!<enables USB Class specific Requests */
#define USB_HID             0                              /*!<Human Interface Device (HID)        */
#define USB_HID_IF_NUM      0                              /*!<Interface Number <0-255>            */
#define USB_MSC             1                              /*!<Mass Storage                        */
#define USB_MSC_IF_NUM      0                              /*!<Interface Number <0-255>            */
#define USB_AUDIO           0                              /*!<Audio Device                        */
#define USB_ADC_CIF_NUM     0                              /*!<Control Interface Number <0-255>    */
#define USB_ADC_SIF1_NUM    1                              /*!<Streaming Interface 1 Number <0-255>*/
#define USB_ADC_SIF2_NUM    2                              /*!<Streaming Interface 2 Number <0-255>*/
#define USB_CDC  			0                              /*!<Communication Device                */
#define USB_CDC_CIF_NUM     0                              /*!<Control Interface Number <0-255>    */
#define USB_CDC_DIF_NUM     1                              /*!<Bulk Interface Number <0-255>       */

#define USB_VENDOR          0


#endif  /* __USB_COM_CONFIG_H__ */
