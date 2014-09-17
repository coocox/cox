/*****************************************************************************
 *      U S B  -  C O M M O M - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: usb_Enumerate.h
 * @brief	: USB Enumerate Definitions
 * @version	: 1.1
 * @date	: 3. Mar. 2011
 * @author	: CooCox
 ****************************************************************************/
#ifndef __USB_ENUMERATE_H__
#define __USB_ENUMERATE_H__
#include "xusb.h"
#include "usb.h"
#include "type.h"
#include "usb_desc.h"
#include "usb_com_config.h"

#if (USB_CLASS)

#if (USB_AUDIO)
typedef uint32_t (PFN_ADC_CALLBACK)(void *data);
#include "usb_audio.h"
#include "usb_adc_config.h"
#endif

#if (USB_HID)
typedef uint32_t (PFN_HID_CALLBACK)(void *data);
#include "usb_hid.h"
#include "usb_hid_config.h"
#endif

#if (USB_MSC)
typedef uint32_t (PFN_MSC_CALLBACK)(void *data,uint32_t para);
#include"usb_msc_config.h"
#include"usb_msc.h"
#endif

#if (USB_CDC)
typedef uint32_t (PFN_CDC_CALLBACK)(void *data,uint32_t para);
#include "usb_cdc.h"
#include "usb_cdc_config.h"
#endif

#endif

#if (USB_VENDOR)
//#include "vendor.h"
typedef uint32_t (PFN_VENDOR_CALLBACK)(void *data,uint32_t para);
#endif

/***********************************************************************
 * USB BUS event call back function definition
 **********************************************************************/
typedef void (PFN_CONFIG_CALLBACK)(uint32_t event);

/***********************************************************************
 * USB end point event call back function definition
 **********************************************************************/
typedef void (PFN_EP_CALLBACK)(void *data,uint32_t event);

/**
 * @brief USB End Point Data Structure
 */
typedef struct _USB_EP_DATA {
	uint8_t  *pData;                         /**< point of EP data            */
	uint16_t Count;                          /**< count of EP data            */
} USB_EP_DATA;

/**
 * @brief USB Enumerate Structure
 */
typedef struct
{
	//COX_USB_PI  *usb;                        /**< USB Peripheral Interface Used */

	PFN_CONFIG_CALLBACK *g_pfn_config_callback;
	PFN_CONFIG_CALLBACK *g_pfn_reset_callback;
	PFN_CONFIG_CALLBACK *g_pfn_suspend_callback;
	PFN_CONFIG_CALLBACK *g_pfn_resume_callback;
	PFN_CONFIG_CALLBACK *g_pfn_wakeup_callback;
	PFN_CONFIG_CALLBACK *g_pfn_interfacec_callback;
	PFN_CONFIG_CALLBACK *g_pfn_feature_callback;

	const uint8_t  *USB_DeviceDescriptor;
	const uint8_t  *USB_ConfigDescriptor;
	const uint8_t  *USB_StringDescriptor;

#if (USB_AUDIO)

	void             *adc_data;
	PFN_ADC_CALLBACK *g_pfn_adc_if_getrequestt;
	PFN_ADC_CALLBACK *g_pfn_adc_if_setrequestt;
	PFN_ADC_CALLBACK *g_pfn_adc_ep_getrequestt;
	PFN_ADC_CALLBACK *g_pfn_adc_ep_setrequestt;

#endif
#if (USB_HID)
	const uint8_t    *HID_ReportDescriptor;
	void             *hid_data;
	PFN_HID_CALLBACK *g_pfn_hid_get_report;
	PFN_HID_CALLBACK *g_pfn_hid_set_report;
	PFN_HID_CALLBACK *g_pfn_hid_get_idle;
	PFN_HID_CALLBACK *g_pfn_hid_set_idle;
	PFN_HID_CALLBACK *g_pfn_hid_get_procotol;
	PFN_HID_CALLBACK *g_pfn_hid_set_procotol;

#endif

#if (USB_MSC)
	void *msc_data;
	PFN_MSC_CALLBACK *g_pfn_msc_request_adsc;
	PFN_MSC_CALLBACK *g_pfn_msc_request_get_req;
	PFN_MSC_CALLBACK *g_pfn_msc_request_put_req;
	PFN_MSC_CALLBACK *g_pfn_msc_request_reset;
	PFN_MSC_CALLBACK *g_pfn_msc_request_get_max_lun;
#endif
#if (USB_CDC)
	void *cdc_data;
	PFN_CDC_CALLBACK *g_pfn_cdc_SendEncapsulatedCommand;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetEncapsulatedResponse;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetCommFeature;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetCommFeature;
	PFN_CDC_CALLBACK *g_pfn_cdc_ClearCommFeature ;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetAuxLineState;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetHookState;
	PFN_CDC_CALLBACK *g_pfn_cdc_PulseSetup;
	PFN_CDC_CALLBACK *g_pfn_cdc_SendPulse;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetPulseTime;
	PFN_CDC_CALLBACK *g_pfn_cdc_RingAuxJack ;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetLineCoding;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetLineCoding;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetControlLineState;
	PFN_CDC_CALLBACK *g_pfn_cdc_SendBreak;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetRingerParms;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetRingerParms;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetOperationParms;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetOperationParms;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetLineParms;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetLineParms;
	PFN_CDC_CALLBACK *g_pfn_cdc_DialDigits;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetUnitParameter;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetUnitParameter;
	PFN_CDC_CALLBACK *g_pfn_cdc_ClearUnitParameter;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetProfile;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetEthernetMulticastFilters;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetEthernetPowerManagementPatternFilter;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetEthernetPowerManagementPatternFilter;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetEthernetPacketFilter;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetEthernetStatistic ;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetATMDataFormat ;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetATMDeviceStatistics ;
	PFN_CDC_CALLBACK *g_pfn_cdc_SetATMDefaultVC  ;
	PFN_CDC_CALLBACK *g_pfn_cdc_GetATMVCStatistics ;

#endif

#if (USB_VENDOR)
	void *vender_data;
	PFN_VENDOR_CALLBACK *g_pfn_vender_device;
	PFN_VENDOR_CALLBACK *g_pfn_vender_interface;
	PFN_VENDOR_CALLBACK *g_pfn_vender_endpoint;
#endif

	uint16_t USB_DeviceStatus;
	uint8_t  USB_DeviceAddress;
	uint8_t  USB_Configuration;
	uint32_t USB_EndPointMask;
	uint32_t USB_EndPointHalt;
	uint32_t USB_EndPointStall;
	uint8_t  USB_NumInterfaces;
	uint8_t  USB_AltSetting[1];
	uint8_t  EP0Buf[USB_MAX_PACKET0];
	USB_EP_DATA EP0Data;
	USB_SETUP_PACKET SetupPacket;

} USB_ENU_Dev;


/***********************************************************************
 * extern API of this component
 **********************************************************************/
extern void USB_Init(USB_ENU_Dev *dev);

#endif  /* __USB_ENUMERATE_H__ */
