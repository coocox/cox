/*****************************************************************************
 *      U S B  -  N U C - C O X - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: cox_config.h
 * @brief	: config file
 * @version	: 1.0
 * @date	: 28. Dec. 2010
 * @author	: CooCox
 ****************************************************************************/

#ifndef __COX_CONFIG_H
#define __COX_CONFIG_H


#define USB_EP_NUM          32                    /*!< Max Number of Endpoints  <1-32>*/
#define USB_LOGIC_EP_NUM    16                    /*!<Max Number of Endpoints  <1-32> */
#define USB_MAX_PACKET0     64
//#define USB_DMA             1
#define USB_DMA_EP          0x00000000

#define CTRL_EP_NUM         0                    /*!< control Endpoint number  <0>   */


#define USB_POWER_EVENT     0
#define USB_RESET_EVENT     0
#define USB_SUSPEND_EVENT   0
#define USB_RESUME_EVENT    0
#define USB_WAKEUP_EVENT    0
#define USB_SOF_EVENT       0
#define USB_ERROR_EVENT     0
#define USB_EP_EVENT        0x0005
#define USB_CONFIGURE_EVENT 0
#define USB_INTERFACE_EVENT 0
#define USB_FEATURE_EVENT   0




#endif  /* __COX_CONFIG_H */
