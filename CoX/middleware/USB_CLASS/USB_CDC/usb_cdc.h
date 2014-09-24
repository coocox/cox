/*****************************************************************************
 *      U S B  -  C D C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: USB_CDC.h
 * @brief	: USB Communication Device Class Definitions
 * @version	: 1.0
 * @date	: 10. MAR. 2011
 * @author	: CooCox
 ****************************************************************************/

#ifndef __USB_CDC_H
#define __USB_CDC_H

/**********************************************************************
 *    Definitions  based on CDC120.pdf (www.usb.org)
 **********************************************************************/

/**********************************************************************
 * Communication device class specification version 1.20
 **********************************************************************/
#define CDC_V1_20                               0x0120     /*!<version 1.20                       */

/**********************************************************************
*  Communication interface class code
*  (CDC120.pdf, 4.2, Table 3)
**********************************************************************/
#define CDC_COMMUNICATION_INTERFACE_CLASS       0x02       /*!<Communication interface class code */


/**********************************************************************
 *  Communication interface class subclass codes
 *  (CDC120.pdf, 4.3, Table 4)
 **********************************************************************/
#define CDC_DIRECT_LINE_CONTROL_MODEL           0x01       /*!<Direct Line Control Model           */
#define CDC_ABSTRACT_CONTROL_MODEL              0x02       /*!<Abstract Control Model              */
#define CDC_TELEPHONE_CONTROL_MODEL             0x03       /*!<Telephone Control Model             */
#define CDC_MULTI_CHANNEL_CONTROL_MODEL         0x04       /*!<Multi-Channel Control Model         */
#define CDC_CAPI_CONTROL_MODEL                  0x05       /*!<CAPI Control Model                  */
#define CDC_ETHERNET_NETWORKING_CONTROL_MODEL   0x06       /*!<Ethernet Networking Control Model   */
#define CDC_ATM_NETWORKING_CONTROL_MODEL        0x07       /*!<ATM Networking Control Model        */
#define CDC_WIRELESS_HANDSET_MODEL              0x08       /*!<Wireless Handset Control Model      */
#define CDC_DEVICE_MANAGEMENT_MODEL             0x09       /*!<Device Management                   */
#define CDC_MOBILE_DIRECT_LINE_MODEL            0x0A       /*!<Mobile Direct Line Model            */
#define CDC_OBEX_MODEL                          0x0B       /*!<OBEX                                */
#define CDC_ENTHERNET_EMULATION_MODEL           0x0C       /*!<Ethernet Emulation Model            */

/**********************************************************************
 *  Communication interface class control protocol codes
 *  (CDC120.pdf, 4.4, Table 5)
 **********************************************************************/
#define CDC_PROTOCOL_COMMON_AT_COMMANDS         0x01       /*!<AT Commands: V.250 etc             */
#define CDC_PROTOCOL_COMMON_PCCA_101            0x02       /*!<AT Commands defined by PCCA-101    */
#define CDC_PROTOCOL_COMMON_PCCA_101_AO         0x03       /*!<AT Commands defined by PCCA-101 & Annex O*/
#define CDC_PROTOCOL_COMMON_AT_GSM_707          0x04       /*!<AT Commands defined by GSM 07.07    */
#define CDC_PROTOCOL_COMMON_3GPP27_07           0x05       /*!<AT Commands defined by 3GPP 27.007  */
#define CDC_PROTOCOL_COMMON_C_S0017_0           0x06       /*!<AT Commands defined by TIA for CDMA */
#define CDC_PROTOCOL_COMMON_USB_EEM             0x07       /*!<Ethernet Emulation Model            */
#define CDC_PROTOCOL_COMMON_EXTEN_PROTOCOL      0xFE       /*!<External Protocol: Commands defined
                                                              by Command Set Functional Descriptor */
#define CDC_PROTOCOL_COMMON_VENDOR_SPECIFIC     0xFF       /*!<Vendor-specific                     */

/**********************************************************************
 *  Data interface class code
 *  (CDC120.pdf, 4.5, Table 6)
 **********************************************************************/
#define CDC_DATA_INTERFACE_CLASS                0x0A       /*!<Data interface class code          */


/**********************************************************************
 *  Data interface class protocol codes
 *   (CDC120.pdf, 4.7, Table 7)
 **********************************************************************/
#define CDC_PROTOCOL_NONE                       0x00       /*!<No class specific protocol required*/
#define CDC_PROTOCOL_ISDN_BRI                   0x30       /*!<Physical interface protocol for ISDN BRI*/
#define CDC_PROTOCOL_HDLC                       0x31       /*!<HDLC                               */
#define CDC_PROTOCOL_TRANSPARENT                0x32       /*!<Transparent                        */
#define CDC_PROTOCOL_Q921_MANAGEMENT            0x50       /*!<Management protocol for Q.921 data link protocol*/
#define CDC_PROTOCOL_Q921_DATA_LINK             0x51       /*!<DData link protocol for Q.931      */
#define CDC_PROTOCOL_Q921_MULTIPLEXOR           0x52       /*!<TEI-multiplexor for Q.921 data link protocol*/
#define CDC_PROTOCOL_V42                        0x90       /*!<Data compression procedures        */
#define CDC_PROTOCOL_EURO_ISDN                  0x91       /*!<Euro-ISDN protocol control         */
#define CDC_PROTOCOL_V24_RATE_ADAPTATION        0x92       /*!<V.24 rate adaptation to ISDN       */
#define CDC_PROTOCOL_CAPI                       0x93       /*!<CAPI Commands                      */
#define CDC_PROTOCOL_HOST_BASED_DRIVER          0xFD       /*!<Host based driver.                 */
#define CDC_PROTOCOL_DESCRIBED_IN_PUFD          0xFE       /*!<The protocol(s) are described using
                                                               a Protocol Unit Functional Descriptors
                                                               on Communications Class Interface  */
#define CDC_PROTOCOL_DESCRIBED_VENDOR           0xFE       /*!<Vendor-specific                    */


/**********************************************************************
 *  Type values for bDescriptorType field of functional descriptors
 *  (CDC120.pdf, 5.2.3, Table 12)
 **********************************************************************/
#define CDC_CS_INTERFACE                        0x24       /*!<INTERFACE,                        */
#define CDC_CS_ENDPOINT                         0x25       /*!<ENDPOINT                          */

/**********************************************************************
 *  Type values for bDescriptorSubtype field of functional descriptors
 *   (CDC120.pdf, 5.2.3, Table 13)
 **********************************************************************/
#define CDC_HEADER                              0x00       /*!<Header Functional Descriptor, which
                                                              marks the beginning of the concatenated
                                                              set of functional descriptors for the interface.*/
#define CDC_CALL_MANAGEMENT                     0x01       /*!<Call Management Functional Descriptor.*/
#define CDC_ABSTRACT_CONTROL_MANAGEMENT         0x02       /*!<Abstract Control Management Functional Descriptor.*/
#define CDC_DIRECT_LINE_MANAGEMENT              0x03       /*!<Direct Line Management Functional Descriptor.*/
#define CDC_TELEPHONE_RINGER                    0x04       /*!<Telephone Ringer Functional Descriptor.*/
#define CDC_REPORTING_CAPABILITIES              0x05       /*!<Telephone Call and Line State Reporting
                                                              Capabilities Functional Descriptor.*/
#define CDC_UNION                               0x06       /*!<Union Functional Descriptor       */
#define CDC_COUNTRY_SELECTION                   0x07       /*!<Country Selection Functional Descriptor*/
#define CDC_TELEPHONE_OPERATIONAL_MODES         0x08       /*!<Telephone Operational Modes Functional Descriptor*/
#define CDC_USB_TERMINAL                        0x09       /*!<USB Terminal Functional Descriptor*/
#define CDC_NETWORK_CHANNEL                     0x0A       /*!<Network Channel Terminal Descriptor*/
#define CDC_PROTOCOL_UNIT                       0x0B       /*!<Protocol Unit Functional Descriptor*/
#define CDC_EXTENSION_UNIT                      0x0C       /*!<Extension Unit Functional Descriptor*/
#define CDC_MULTI_CHANNEL_MANAGEMENT            0x0D       /*!<Multi-Channel Management Functional Descriptor*/
#define CDC_CAPI_CONTROL_MANAGEMENT             0x0E       /*!<CAPI Control Management Functional Descriptor*/
#define CDC_ETHERNET_NETWORKING                 0x0F       /*!<Ethernet Networking Functional Descriptor*/
#define CDC_ATM_NETWORKING                      0x10       /*!<ATM Networking Functional Descriptor*/
#define CDC_WIRELESS_HANDSET                    0x11       /*!<Wireless Handset Control Model Functional Descriptor*/
#define CDC_MOBILE_DIRECT_LINE                  0x12       /*!<Mobile Direct Line Model Functional Descriptor*/
#define CDC_MDLM_DETIAL                         0x13       /*!<MDLM Detail Functional Descriptor */
#define CDC_DEVICE_MANAGEMENT                   0x14       /*!<Device Management Model Functional Descriptor*/
#define CDC_OBEX                                0x15       /*!<OBEX Functional Descriptor        */
#define CDC_COMMAND_SET                         0x16       /*!<Command Set Functional Descriptor */
#define CDC_COMMAND_SET_DETAIL                  0x17       /*!<Command Set Detail Functional Descriptor*/
#define CDC_TELEPHONE_CONTROL                   0x18       /*!<Telephone Control Model Functional Descriptor*/
#define CDC_OBEX_SERVICE                        0x19       /*!<OBEX Service Identifier Functional Descriptor*/


/**********************************************************************
 *  CDC class-specific request codes
 *  (CDC120.pdf, 6.2, Table 19)
 *  see Table 18 for info about the specific requests.
 **********************************************************************/
#define CDC_SEND_ENCAPSULATED_COMMAND           0x00       /*!<CDC120.pdf 6.2.1                  */
#define CDC_GET_ENCAPSULATED_RESPONSE           0x01       /*!<CDC120.pdf 6.2.2                  */
#define CDC_SET_COMM_FEATURE                    0x02       /*!<[USBPSTN1.2]                      */
#define CDC_GET_COMM_FEATURE                    0x03       /*!<[USBPSTN1.2]                      */
#define CDC_CLEAR_COMM_FEATURE                  0x04       /*!<[USBPSTN1.2]                      */
#define CDC_SET_AUX_LINE_STATE                  0x10       /*!<[USBPSTN1.2]                      */
#define CDC_SET_HOOK_STATE                      0x11       /*!<[USBPSTN1.2]                      */
#define CDC_PULSE_SETUP                         0x12       /*!<[USBPSTN1.2]                      */
#define CDC_SEND_PULSE                          0x13       /*!<[USBPSTN1.2]                      */
#define CDC_SET_PULSE_TIME                      0x14       /*!<[USBPSTN1.2]                      */
#define CDC_RING_AUX_JACK                       0x15       /*!<[USBPSTN1.2]                      */
#define CDC_SET_LINE_CODING                     0x20       /*!<[USBPSTN1.2]                      */
#define CDC_GET_LINE_CODING                     0x21       /*!<[USBPSTN1.2]                      */
#define CDC_SET_CONTROL_LINE_STATE              0x22       /*!<[USBPSTN1.2]                      */
#define CDC_SEND_BREAK                          0x23       /*!<[USBPSTN1.2]                      */
#define CDC_SET_RINGER_PARMS                    0x30       /*!<[USBPSTN1.2]                      */
#define CDC_GET_RINGER_PARMS                    0x31       /*!<[USBPSTN1.2]                      */
#define CDC_SET_OPERATION_PARMS                 0x32       /*!<[USBPSTN1.2]                      */
#define CDC_GET_OPERATION_PARMS                 0x33       /*!<[USBPSTN1.2]                      */
#define CDC_SET_LINE_PARMS                      0x34       /*!<[USBPSTN1.2]                      */
#define CDC_GET_LINE_PARMS                      0x35       /*!<[USBPSTN1.2]                      */
#define CDC_DIAL_DIGITS                         0x36       /*!<[USBPSTN1.2]                      */
#define CDC_SET_UNIT_PARAMETER                  0x37       /*!<[USBISDN1.2]                      */
#define CDC_GET_UNIT_PARAMETER                  0x38       /*!<[USBISDN1.2]                      */
#define CDC_CLEAR_UNIT_PARAMETER                0x39       /*!<[USBISDN1.2]                      */
#define CDC_GET_PROFILE                         0x3A       /*!<[USBISDN1.2]                      */
#define CDC_SET_ETHERNET_MULTICAST_FILTERS      0x40       /*!<[USBECM1.2]                       */
#define CDC_SET_ETHERNET_PMP_FILTER             0x41       /*!<[USBECM1.2]                       */
#define CDC_GET_ETHERNET_PMP_FILTER             0x42       /*!<[USBECM1.2]                       */
#define CDC_SET_ETHERNET_PACKET_FILTER          0x43       /*!<[USBECM1.2]                       */
#define CDC_GET_ETHERNET_STATISTIC              0x44       /*!<[USBECM1.2]                       */
#define CDC_SET_ATM_DATA_FORMAT                 0x50       /*!<[USBATM1.2]                       */
#define CDC_GET_ATM_DEVICE_STATISTICS           0x51       /*!<[USBATM1.2]                       */
#define CDC_SET_ATM_DEFAULT_VC                  0x52       /*!<[USBATM1.2]                       */
#define CDC_GET_ATM_VC_STATISTICS               0x53       /*!<[USBATM1.2]                       */


/**********************************************************************
 *  Communication feature selector codes
 *  (CDC120.pdf, 6.2.2..6.2.4, Table 47)
 **********************************************************************/
#define CDC_ABSTRACT_STATE                      0x01       /*!<ENDPOINT                          */
#define CDC_COUNTRY_SETTING                     0x02       /*!<ENDPOINT                          */


/**********************************************************************
 *  Feature Status returned for ABSTRACT_STATE Selector
 *  (PSTN120.pdf, 6.3.2, Table 15)
 **********************************************************************/
#define CDC_IDLE_SETTING                        (1 << 0)   /*!<Idle Setting                      */
#define CDC_DATA_MULTPLEXED_STATE               (1 << 1)   /*!<Data Multiplexed State            */

/**********************************************************************
 *  This request is used to set the necessary PSTN line relay code for
 *  on-hook, off-hook, and caller ID states.
 *  (PSTN120.pdf, 6.3.5, Table 16)
 **********************************************************************/
#define CDC_ON_HOOK                             (0 << 0)   /*!<Idle Setting                      */
#define CDC_OFF_HOOK                            (1 << 0)   /*!<Data Multiplexed State            */
#define CDC_SNOOPING                            (1 << 1)   /*!<Data Multiplexed State            */

/**********************************************************************
 *  Sets the operational mode for the device, between a simple mode,
 *  standalone mode and a host centric mode.
 *  (PSTN120.pdf, 6.3.16, Table 20)
 **********************************************************************/
#define CDC_SIMPLE_MODE                         0x00       /*!<Simple Mode                       */
#define CDC_SDANDALONE_MODE                     0x01       /*!<Standalone Mode                   */
#define CDC_HOST_MODE                           0x02       /*!<Host Centric Mode                 */

/**********************************************************************
 *  This request is used to change the state of the line, corresponding
 *  to the interface or master interface of a union to which the command was sent.
 *  (PSTN120.pdf, 6.3.18, Table 21)
 **********************************************************************/
#define CDC_DROP_CALL                           0x00       /*!<Drop the active call on the line. */
#define CDC_START_CALL                          0x01       /*!<Start a new call on the line.     */
#define CDC_APPLY_RING                          0x02       /*!<Apply ringing to the line.        */
#define CDC_REMOVE_RING                         0x02       /*!<Remove ringing from the line.     */
#define CDC_SWITCH_CALL                         0x02       /*!<Switch to a specific call on the line.*/

/**********************************************************************
 *  This request is used to set the data format selected by the host
 *  in the wValue field.
 *  (ATM120.pdf, 6.2.1, Table 20)
 **********************************************************************/
#define CDC_TYTE_1_FORMAT                       0x01       /*!<concatenated ATM cells            */
#define CDC_TYTE_2_FORMAT                       0x02       /*!<ATM header template               */
#define CDC_TYTE_3_FORMAT                       0x03       /*!<AAL 5 SDU                         */


/**********************************************************************
 *  Control signal bitmap values for the SetControlLineState request
 *  (CDC120.pdf, 6.2.14, Table 51)
 **********************************************************************/
#define CDC_DTE_PRESENT                         (1 << 0)   /*!<ENDPOINT                          */
#define CDC_ACTIVATE_CARRIER                    (1 << 1)   /*!<ENDPOINT                          */


/**********************************************************************
 *  CDC class-specific notification codes UART State Bitmap Values
 *   (CDC120.pdf, 6.3, Table 20)
 **********************************************************************/
#define CDC_NOTIFICATION_NETWORK_CONNECTION     0x00       /*!<CDC120.pdf 6.3.1                  */
#define CDC_RESPONSE_AVAILABLE                  0x01       /*!<CDC120.pdf 6.3.2                  */
#define CDC_AUX_JACK_HOOK_STATE                 0x08       /*!<[USBPSTN1.2]                      */
#define CDC_RING_DETECT                         0x09       /*!<[USBPSTN1.2]                      */
#define CDC_NOTIFICATION_SERIAL_STATE           0x20       /*!<[USBPSTN1.2]                      */
#define CDC_CALL_STATE_CHANGE                   0x28       /*!<[USBPSTN1.2]                      */
#define CDC_LINE_STATE_CHANGE                   0x29       /*!<[USBPSTN1.2]                      */
#define CDC_CONNECTION_SPEED_CHANGE             0x2A       /*!<CDC120.pdf 6.3.3                  */


/**********************************************************************
 *  UART state bitmap values (Serial state notification).
 *   (PSTN120.pdf, 6.5.4, Table 31)
 **********************************************************************/
#define CDC_SERIAL_STATE_OVERRUN                (1 << 6)   /*!<receive data overrun error has occurred*/
#define CDC_SERIAL_STATE_PARITY                 (1 << 5)   /*!<parity error has occurred          */
#define CDC_SERIAL_STATE_FRAMING                (1 << 4)   /*!<framing error has occurred         */
#define CDC_SERIAL_STATE_RING                   (1 << 3)   /*!<state of ring signal detection     */
#define CDC_SERIAL_STATE_BREAK                  (1 << 2)   /*!<state of break detection           */
#define CDC_SERIAL_STATE_TX_CARRIER             (1 << 1)   /*!<state of transmission carrier      */
#define CDC_SERIAL_STATE_RX_CARRIER             (1 << 0)   /*!<state of receiver carrier          */

/*----------------------------------------------------------------------------
 *      Definitions  based on ECM120.pdf (www.usb.org)
 *---------------------------------------------------------------------------*/


/**********************************************************************
 *  Ethernet Statistics Feature Selector Codes
 *   (ECM120.pdf, 6.2.5, Table 9)
 **********************************************************************/
#define CDC_XMIT_OK                             0x01
#define CDC_RCV_OK                              0x02
#define CDC_XMIT_ERROR                          0x03
#define CDC_RCV_ERROR                           0x04
#define CDC_RCV_NO_BUFFER                       0x05
#define CDC_DIRECTED_BYTES_XMIT                 0x06
#define CDC_DIRECTED_FRAMES_XMIT                0x17
#define CDC_MULTICAST_BYTES_XMIT                0x08
#define CDC_MULTICAST_FRAMES_XMIT               0x09
#define CDC_BROADCAST_BYTES_XMIT                0x0A
#define CDC_BROADCAST_FRAMES_XMIT               0x0B
#define CDC_DIRECTED_BYTES_RCV                  0x0C
#define CDC_DIRECTED_FRAMES_RCV                 0x0D
#define CDC_MULTICAST_BYTES_RCV                 0x0E
#define CDC_MULTICAST_FRAMES_RCV                0x0F
#define CDC_BROADCAST_BYTES_RCV                 0x10
#define CDC_BROADCAST_FRAMES_RCV                0x11
#define CDC_RCV_CRC_ERROR                       0x12
#define CDC_TRANSMIT_QUEUE_LENGTH               0x13
#define CDC_RCV_ERROR_ALIGNMENT                 0x14
#define CDC_XMIT_ONE_COLLISION                  0x15
#define CDC_XMIT_MORE_COLLISIONS                0x16
#define CDC_XMIT_DEFERRED                       0x17
#define CDC_XMIT_MAX_COLLISIONS                 0x18
#define CDC_RCV_OVERRUN                         0x19
#define CDC_XMIT_UNDERRUN                       0x1A
#define CDC_XMIT_HEARTBEAT_FAILURE              0x1B
#define CDC_XMIT_TIMES_CRS_LOST                 0x1C
#define CDC_XMIT_LATE_COLLISIONS                0x1D


/** USB CDC configuration structure */
/***********************************************************************
 * USB CDC functional descriptor
 **********************************************************************/

/**
 * @brief Header functional descriptor                               0x00
 *  (CDC120.pdf, 5.2.3.1 Table 15)
 *  This header must precede any list of class-specific descriptors.
 */
typedef struct _CDC_HEADER_DESCRIPTOR{
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Header functional descriptor subtype          */
  uint16_t bcdCDC;                             /**< USB CDC specification release version         */
} __attribute__((packed)) CDC_HEADER_DESCRIPTOR;


/**
 * @brief Call management functional descriptor                      0x01
 *  (PSTN120.pdf, 5.3.1 Table 3)
 *  Describes the processing of calls for the communication class interface.
 */
typedef struct _CDC_CALL_MANAGEMENT_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< call management functional descriptor subtype */
  uint8_t bmCapabilities;                      /**< capabilities that this configuration supports */
  uint8_t bDataInterface;                      /**< interface number of the data class interface
                                                    used for call management (optional)           */
} __attribute__((packed)) CDC_CALL_MANAGEMENT_DESCRIPTOR;

/**
 * @brief Abstract control management functional descriptor          0x02
 *  (PSTN120.pdf, 5.3.2 Table 4)
 *  Describes the command supported by the communication interface class with the Abstract Control Model subclass code.
 */
typedef struct _CDC_ABSTRACT_CONTROL_MANAGEMENT_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< abstract control management functional
                                                    descriptor subtype                            */
  uint8_t bmCapabilities;                      /**< capabilities supported by this configuration  */
} __attribute__((packed)) CDC_ABSTRACT_CONTROL_MANAGEMENT_DESCRIPTOR;


/**
 * @brief Direct Line Management Functional Descriptor               0x03
 *  (PSTN120.pdf, 5.3.3 Table 5)
 *  Describes the command supported by the communication interface class with the Direct Line Control Model subclass code.
 */
typedef struct _CDC_DIRECT_LINE_MANAGEMENT_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Direct Line Management functional descriptor subtype*/
  uint8_t bmCapabilities;                      /**< capabilities supported by this configuration  */
} __attribute__((packed)) CDC_DIRECT_LINE_MANAGEMENT_DESCRIPTOR;

/**
 * @brief Telephone Ringer Functional Descriptor                     0x04
 *  (PSTN120.pdf, 5.3.4 Table 6)
 *  Describes the command supported by the communication interface class with the Telephone Control Model subclass code.
 */
typedef struct _CDC_TELEPHONE_RINGER_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Telephone Ringer functional descriptor subtype*/
  uint8_t bRingerVolSteps;                     /**< Number of discrete steps in volume supported by the ringer*/
  uint8_t bNumRingerPatterns;                  /**< Number of ringer patterns supported           */
} __attribute__((packed)) CDC_TELEPHONE_RINGER_DESCRIPTOR;

/**
 * @brief Telephone Call and Line State Reporting Capabilities Descriptor  0x05
 *  (PSTN120.pdf, 5.3.6 Table 8)
 *  Describes the command supported by the communication interface class with the Telephone Control Model subclass code.
 */
typedef struct _CDC_TELEPHONE_CALL_LINE_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes             */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                 */
  uint8_t bDescriptorSubtype;                  /**< Telephone Call and Line State Reporting
                                                    Capabilities descriptor subtype              */
  uint8_t bmCapabilities;                      /**< capabilities supported by this configuration */
} __attribute__((packed)) CDC_TELEPHONE_CALL_LINE_DESCRIPTOR;

/**
 * @brief Union functional descriptors                               0x06
 *  (CDC120.pdf, 5.2.3.2 Table 16)
 *  Describes the relationship between a group of interfaces that can be considered to form a functional unit.
 */
typedef struct _CDC_UNION_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< union functional descriptor subtype           */
  uint8_t bMasterInterface;                    /**< interface number designated as master         */
} __attribute__((packed)) CDC_UNION_DESCRIPTOR;

// Union functional descriptors with one slave interface
// (CDC120.pdf, 5.2.3.2 Table 16)
/**
 * @brief Union functional descriptors with one slave interface
 *  (CDC120.pdf, 5.2.3.2 Table 16)
 */
typedef struct _CDC_UNION_1SLAVE_DESCRIPTOR {
  CDC_UNION_DESCRIPTOR sUnion;                 /**< Union functional descriptor                   */
  uint8_t              bSlaveInterfaces[1];    /**< Slave interface 0                             */
} __attribute__((packed)) CDC_UNION_1SLAVE_DESCRIPTOR;

/**
 * @brief Country Selection Functional Descriptor                    0x07
 *  (CDC120.pdf, 5.2.3.3 Table 17)
 *  The Country Selection Functional Descriptor identifies the countries in which the communications device is qualified to operate.
 */
typedef struct _CDC_COUNTRY_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Country Selection Functional Descriptor Subtype
                                                    as defined in Table 13.                       */
  uint8_t iCountryCodeRelDate;                 /**< Index of a string giving the release date for
                                                    the implemented ISO 3166 Country Codes.       */
} __attribute__((packed)) CDC_COUNTRY_DESCRIPTOR;

/**
 * @brief Country Selection Functional Descriptor  with one Country Codes
 *  (CDC120.pdf, 5.2.3.2 Table 16)
 */
typedef struct _CDC_COUNTRY_1CCODEE_DESCRIPTOR {
  CDC_COUNTRY_DESCRIPTOR sCountry;             /**< Union functional descriptor                   */
  uint16_t               wCountryCode[1];      /**< Country Codes 0                               */
} __attribute__((packed)) CDC_COUNTRY_1CCODEE_DESCRIPTOR;

/**
 * @brief Telephone Operational Modes Functional Descriptor          0x08
 *  (PSTN120.pdf, 5.3.5 Table 7)
 *  Describes the command supported by the communication interface class with the Telephone Control Model subclass code.
 */
typedef struct _CDC_TELEPHONE_OPERAT_MODE_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Telephone Operational Modes functional descriptor subtype*/
  uint8_t bmCapabilities;                      /**< capabilities supported by this configuration  */
} __attribute__((packed)) CDC_TELEPHONE_OPERAT_MODE_DESCRIPTOR;

/**
 * @brief USB Terminal Functional Descriptor                         0x09
 *   (ISDN120.pdf, 5.3.1 Table 4)
 *  The USB Terminal Functional Descriptor provides a means to indicate a relationship between a Unit and an USB Interface.
 *  It also defines parameters specific to the interface between the device and the host. It can only occur within the
 *  class-specific portion of an Interface descriptor.
 */
typedef struct _CDC_USB_TERMINAL_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< USB Terminal Functional Descriptor Subtype as
                                                    defined in [USBCDC1.2]                        */
  uint8_t bEntityId;                           /**< Constant uniquely identifying the Terminal    */
  uint8_t bInInterfaceNo;                      /**< The input interface number of the associated USB interface.*/
  uint8_t bOutInterfaceNo;                     /**< The output interface number of the associated USB interface.*/
  uint8_t bmOptions;                           /**< Wrapper used or not                           */
} __attribute__((packed)) CDC_USB_TERMINAL_DESCRIPTOR;

// USB Terminal Functional Descriptor with one lower Terminal
// (ISDN120.pdf, 5.3.1 Table 4)
/**
 * @brief USB Terminal Functional Descriptor with one lower Terminal
 *  (ISDN120.pdf, 5.3.1 Table 4)
 */
typedef struct _CDC_TERMINAL_1ID_DESCRIPTOR {
  CDC_USB_TERMINAL_DESCRIPTOR sTerminal;       /**< Union functional descriptor                   */
  uint8_t                     bChildId[1];     /**< First ID of lower Terminal or Unit to which
                                                    this Terminal is connected.                   */
} __attribute__((packed)) CDC_TERMINAL_1ID_DESCRIPTOR;

/**
 * @brief Network Channel Terminal Functional Descriptor             0x0A
 *  (ISDN120.pdf, 5.3.2 Table 5)
 *  The Network Channel Terminal Functional descriptor provides a means to indicate a relationship between a Unit and
 *  a Network Channel. It can only occur within the class-specific portion of an Interface descriptor.
 */
typedef struct _CDC_NETWORK_TERMINAL_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Network Channel Terminal Functional Descriptor
                                                    Subtype as defined in [USBCDC1.2]             */
  uint8_t bEntityId;                           /**< Constant uniquely identifying the Terminal    */
  uint8_t iName;                               /**< Index of string descriptor, describing the name
                                                    of the Network Channel Terminal.              */
  uint8_t bChannelIndex;                       /**< The channel index of the associated network
                                                    channel according to indexing rules below.    */
  uint8_t bPhysicalInterface;                  /**< Type of physical interface:                   */
} __attribute__((packed)) CDC_NETWORK_TERMINAL_DESCRIPTOR;

/**
 * @brief Protocol Unit Functional Descriptor                        0x0B
 *  (ISDN120.pdf, 5.3.3 Table 6)
 *  A communication protocol stack is a combination of communication functions (protocols) into a layered structure. Each layer in the
 *  stack presents some abstract function for the layer above according to some layer-interface-standard, making it possible to replace
 *  a function with another as long as it conforms to the standard.A Protocol Unit Functional Descriptor identifies with bEntityId a
 *  specific protocol instance of bProtocol in a stack. It can only occur within the class-specific portion of an Interface descriptor.
 */
typedef struct _CDC_PROTOCOL_UNIT_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Protocol Unit Functional Descriptor Subtype as
                                                     defined in [USBCDC1.2]                       */
  uint8_t bEntityId;                           /**< Constant uniquely identifying the Unit        */
  uint8_t bProtocol;                           /**< Protocol code as defined in [USBCDC1.2]       */
} __attribute__((packed)) CDC_PROTOCOL_UNIT_DESCRIPTOR;

/**
 * @brief Protocol Unit Functional Descriptor with one lower Terminal
 *  (ISDN120.pdf, 5.3.3 Table 6)
 */
typedef struct _CDC_PROTOCOL_UNIT_1ID_DESCRIPTOR {
  CDC_PROTOCOL_UNIT_DESCRIPTOR sTerminal;      /**<  Protocol Unit functional descriptor          */
  uint8_t                      bChildId[1];    /**<  First ID of lower Terminal or Unit to which
                                                     this Terminal is connected.                  */
} __attribute__((packed)) CDC_PROTOCOL_UNIT_1ID_DESCRIPTOR;

/**
 * @brief Extension Unit Functional Descriptor                       0x0C
 *  (ISDN120.pdf, 5.3.4 Table 7)
 *  The Extension Unit Functional Descriptor provides minimal information about the Extension Unit for a generic driver
 *  at least to notice the presence of vendor-specific components within the protocol stack. The bExtensionCode field may
 *  contain a vendor-specific code that further identifies the Extension Unit. If it is not used, it should be set to zero.
 *  The Unit may have a set of vendor specific parameters to configure it for proper operation in the actual environment
 *  and the parameters may be retrieved and/or modified.The descriptor can only occur within the class-specific portion
 *  of an Interface descriptor.
 */
typedef struct _CDC_EXTENSION_UNIT_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Extension Unit Functional Descriptor Subtype
                                                    as defined in [USBCDC1.2]                     */
  uint8_t bEntityId;                           /**< Constant uniquely identifying the Unit        */
  uint8_t bExtensionCode;                      /**< Vendor specific code identifying the Extension Unit.*/
  uint8_t iName;                               /**< Index of string descriptor, describing the name
                                                    of the Extension Unit.                        */
} __attribute__((packed)) CDC_EXTENSION_UNIT_DESCRIPTOR;

/**
 * @brief Extension Unit Functional Descriptor with one lower Terminal
 *  (ISDN120.pdf, 5.3.4 Table 7)
 */
typedef struct _CDC_EXTENSION_UNIT_1ID_DESCRIPTOR {
  CDC_EXTENSION_UNIT_DESCRIPTOR sTerminal;     /**< Extension Unit functional descriptor          */
  uint8_t                      bChildId[1];    /**< First ID of lower Terminal or Unit to which
                                                    this Terminal is connected.                   */
} __attribute__((packed)) CDC_EXTENSION_UNIT_1ID_DESCRIPTOR;

/**
 * @brief Multi-Channel Management Functional Descriptor             0x0D
 *  (ISDN120.pdf, 5.3.5 Table 8)
 *  The Multi-Channel Management functional descriptor describes the commands supported by the Communications Class
 *  interface, as defined in CDC , with the SubClass code of Multi-Channel. It can only occur within the class-specific
 *  portion of an Interface descriptor.
 */
typedef struct _CDC_MULTI_CHANNEL_MANAG_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Multi-Channel Management functional descriptor
                                                    subtype, as defined in [USBCDC1.2]            */
  uint8_t bmCapabilities;                      /**< The capabilities that this configuration supports.*/
} __attribute__((packed)) CDC_MULTI_CHANNEL_MANAG_DESCRIPTOR;


/**
 * @brief CAPI Control Management Functional Descriptor              0x0E
 *  (ISDN120.pdf, 5.3.6 Table 9)
 *  The CAPI control management functional descriptor describes the commands supported by the CAPI Control Model
 *  over the Data Class interface with the protocol code of CAPI control. It can only occur within the class
 *  specific portion of Communications Class Interface descriptor.
 */
typedef struct _CDC_CAPI_CONTROL_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< CAPI Control Management Functional Descriptor
                                                    Subtype as defined in [USBCDC1.2]             */
  uint8_t bmCapabilities;                      /**< The capabilities that this configuration supports.*/
} __attribute__((packed)) CDC_CAPI_CONTROL_DESCRIPTOR;

/**
 * @brief Ethernet Networking Functional Descriptor                  0x0F
 *  (ECM120.pdf, 5.4 Table 3)
 *  Describes the command supported by the communication interface class with the Ethernet Networking Control Model subclass code.
 */
typedef struct _CDC_ETHERNET_NETWORKING_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Ethernet Networking functional descriptor subtype*/
  uint8_t iMACAddress;                         /**< Index of string descriptor. The string descriptor
                                                    holds the 48bit Ethernet MAC address.         */
  uint32_t bmEthernetStatistics;               /**< Indicates which Ethernet statistics functions the
                                                    device collects.                              */
  uint16_t wMaxSegmentSize;                    /**< The maximum segment size that the Ethernet
                                                    device is capable of supporting.              */
  uint16_t wNumberMCFilters;                   /**< Contains the number of multicast filters that
                                                    can be configured by the host.                */
  uint8_t bNumberPowerFilters;                 /**< Contains the number of pattern filters that are
                                                    available for causing wake-up of the host.    */
} __attribute__((packed)) CDC_ETHERNET_NETWORKING_DESCRIPTOR;

/**
 * @brief ATM Networking Functional Descriptor                       0x10
 *  (ATM120.pdf, 5.4 Table 3)
 *  Describes the command supported by the communication interface class with the ATM Networking Control Model subclass code.
 */
typedef struct _CDC_ATM_NETWORKING_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< ATM Networking functional descriptor subtype  */
  uint8_t iEndSystemIdentifier;                /**< Index of string descriptor.                   */
  uint8_t bmDataCapabilities;                  /**< The ATM data types the device supports:       */
  uint8_t bmATMDeviceStatistics;               /**< Indicates which optional statistics functions
                                                    the device collects.                          */
  uint16_t wType2MaxSegmentSize;               /**< The maximum segment size that the Type 2 device
                                                    is capable of supporting                      */
  uint16_t wType3MaxSegmentSize;               /**< The maximum segment size that the Type 3 device
                                                    is capable of supporting                      */
  uint16_t wMaxVC;                             /**< The maximum number of simultaneous virtual
                                                    circuits the device is capable of supporting  */
} __attribute__((packed)) CDC_ATM_NETWORKING_DESCRIPTOR;

/**
 * @brief Wireless Handset Control Model Functional Descriptor       0x11
 *  (WMC110.pdf, 6.1.2.3 Table 6-2)
 *  This descriptor is mandatory after a Communications Interface, if that Communication Interface¡¯s bInterfaceProtocol
 *  code is ¡°External Protocol¡±, as defined in Table 5-2. Otherwise, this descriptor is forbidden.
 */
typedef struct _CDC_WIRELESS_HANDSET_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< ID for Wireless Handset Control Model
                                                    functional descriptor.                        */
  uint16_t bcdVersion;                         /**< Version number for this subclass specification.
                                                     Initially 0x0100.                            */
} __attribute__((packed)) CDC_WIRELESS_HANDSET_DESCRIPTOR;

/**
 * @brief Mobile Direct Line Model Functional Descriptor             0x12
 *  (WMC110.pdf, 6.7.2.3 Table 6-36)
 *  This descriptor is mandatory. It conveys the GUID that uniquely identifies the kind of MDLM interface that is being provided.
 */
typedef struct _CDC_MOBILE_DIRECT_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Mobile Direct Line Model Functional Descriptor
                                                    subtype, as given in Table 5-3 above          */
  uint16_t bcdVersion;                         /**< Version number for this subclass specification.
                                                    Initially 0x0100.                             */
  uint8_t bGUID[16];                           /**< Uniquely identifies the detailed transport
                                                    protocol provided by this MDLM interface.     */
} __attribute__((packed)) CDC_MOBILE_DIRECT_DESCRIPTOR;

/**
 * @brief MDLM Detail Functional Descriptor                          0x13
 *  (WMC110.pdf, 6.7.2.4 Table 6-37)
 *  This descriptor is optional, and may be repeated as necessary. It conveys any additional information required by the MDLM transport
 *  specification identified by the MDLM Functional Descriptor. If present, it must occur after the MDLM Functional Descriptor, in the
 *  same group of functional descriptors.
 */
typedef struct _CDC_MDLM_DETAIL_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< MDLM Detail Functional Descriptor subtype, as
                                                    given in Table 5-3 above                      */
  uint8_t bGuidDescriptorType;                 /**< Discriminator, interpreted according to the
                                                    semantic model specified by the GUID in the
                                                    MDLM Functional Descriptor                    */
  uint8_t bDetailData[];                       /**< Information associated with this GUID and discriminator.*/
} __attribute__((packed)) CDC_MDLM_DETAIL_DESCRIPTOR;

/**
 * @brief Device Management Functional Descriptor                    0x14
 *  (WMC110.pdf, 6.6.2.3 Table 6-33)
 *  This conveys subclass version information and device design decision information to the host.
 */
typedef struct _CDC_DEVICE_MANAGEMENT_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< ID for Device Management Control Model
                                                    functional descriptor.                        */
  uint16_t bcdVersion;                         /**< Version number for this subclass specification.
                                                     Initially 0x0100.                            */
  uint16_t wMaxCommand;                        /**< The buffer size allocated in the device for data
                                                    sent from the host using SendEncapsulatedCommand.*/
} __attribute__((packed)) CDC_DEVICE_MANAGEMENT_DESCRIPTOR;

/**
 * @brief OBEX Functional Descriptor                                 0x15
 *  (WMC110.pdf, 6.5.2.3 Table 6-24)
 *  This conveys subclass version information. Because the mode switching logic is opaque to the layer that manages this interface,
 *  mode-switching capabilities are not presented here.
 */
typedef struct _CDC_OBEX_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< ID for OBEX Control Model functional descriptor.*/
  uint16_t bcdVersion;                         /**< Version number for this subclass specification.
                                                    Initially 0x0100.                             */
} __attribute__((packed)) CDC_OBEX_DESCRIPTOR;

/**
 * @brief Command Set Functional Descriptor                          0x16
 *  (WMC110.pdf, 8.1.2.2 Table 8-1)
 *  This descriptor is mandatory after a Communications Interface, if that Communication Interface¡¯s bInterfaceProtocol
 *  code is ¡°External Protocol¡±, as defined in Table 5-2. Otherwise, this descriptor is forbidden.
 */
typedef struct _CDC_COMMAND_SET_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Command Set Functional Descriptor subtype, as
                                                    given in Table 5-3 above                      */
  uint16_t bcdVersion;                         /**< Version number for this subclass specification.
                                                    Initially 0x0100.                             */
  uint8_t iCommandSet;                         /**< Sndex of string that describes this command set*/
  uint8_t bGUID[16];                           /**< Uniquely identifies the command set to be used
                                                    when communicating with this interface.       */
} __attribute__((packed)) CDC_COMMAND_SET_DESCRIPTOR;

/**
 * @brief Command Set Detail Functional Descriptor                   0x17
 *  (WMC110.pdf, 8.1.2.3 Table 8-2)
 *  This descriptor is optional, and may be repeated as necessary. It conveys any additional information required by the
 *  command set identified by the Command Set Functional Descriptor. If present, it must occur after a Communications
 *  Class Interface Descriptor, with bInterfaceProtocol == EXTERNAL_PROTOCOL (as defined in Table 5-2: Communications
 *  Class Protocol Codes), and after the Command Set Functional Descriptor, in the same group of functional descriptors.
 */
typedef struct _CDC_COMMAND_SET_DETAIL_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Command Set Detail Functional Descriptor
                                                    subtype, as given in Table 5-3 above          */
  uint8_t bcdVersion;                          /**< Discriminator, interpreted according to the
                                                    command set model specified by the            */
                                               /**< GUID in the Command Set Functional Descriptor */
  uint8_t bDetailData[];                       /**< Information associated with this GUID and discriminator*/
} __attribute__((packed)) CDC_COMMAND_SET_DETAIL_DESCRIPTOR;


/**
 * @brief Telephone Control Model Functional Descriptor              0x18
 *  (WMC110.pdf, 6.3.2.3 Table 6-15)
 *  This descriptor is mandatory. This descriptor is defined by this document, and is an extension to [USBPSTN1.2]
 */
typedef struct _CDC_TELEPHONE_CONTROL_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< Telephone Control Model Functional Descriptor
                                                    subtype, as given in Table 5-3.               */
  uint16_t bcdVersion;                         /**< Version number for this subclass specification.
                                                    Initially 0x0100.                             */
  uint16_t wMaxCommand;                        /**< Describes the maximum number of characters    */
} __attribute__((packed)) CDC_TELEPHONE_CONTROL_DESCRIPTOR;

/**
 * @brief OBEX Service Identification Functional Descriptor          0x19
 *  (WMC110.pdf, 6.5.2.5 Table 6-26)
 *  This descriptor is mandatory. This descriptor is defined by this document, and is an extension to [USBPSTN1.2]
 */
typedef struct _CDC_OEX_SERVICE_DESCRIPTOR {
  uint8_t bFunctionLength;                     /**< size of this descriptor in bytes              */
  uint8_t bDescriptorType;                     /**< CS_INTERFACE descriptor type                  */
  uint8_t bDescriptorSubtype;                  /**< ID for OBEX Service Identification Functional Descriptor*/
  uint16_t bmOBEXRole;                         /**< Represents the OBEX role to be played by the function*/
  uint8_t bOBEXServiceUUID[16];                /**< A 16 byte UUID value used to indicate the
                                                    particular OBEX service                       */
  uint16_t wOBEXServiceVersion;                /**< A 16 bit value indicating the version of the
                                                    OBEX service associated with this function.   */
} __attribute__((packed)) CDC_OEX_SERVICE_DESCRIPTOR;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief Unit Parameter Structure
 *  Format of the data returned when a GetUnitParameter request is received
 *  (ISDN120.pdf, 6.2.11 Table 13)
 */
typedef struct _CDC_UNIT_PARAMETER {
  uint8_t  bEntityId;                          /**< Unit Id                                       */
  uint8_t  bParameterIndex;                    /**< A zero based value indicating Unit parameter index.*/
} __attribute__((packed)) CDC_UNIT_PARAMETER;


/**
 * @brief Line coding structure
 *  Format of the data returned when a GetLineCoding request is received
 *  (PSTN120.pdf, 6.3.11 Table 17)
 */
typedef struct _CDC_LINE_CODING {
  uint32_t dwDTERate;                          /**< Data terminal rate in bits per second         */
  uint8_t  bCharFormat;                        /**< Number of stop bits                           */
  uint8_t  bParityType;                        /**< Parity bit type                               */
  uint8_t  bDataBits;                          /**< Number of data bits                           */
} __attribute__((packed)) CDC_LINE_CODING;



// NCM Functional Descriptor
// (NCM10.pdf, 5.2.1 Table 5-2)
// This descriptor provides information about the implementation of the NCM function. It is mandatory, and must appear
//after the Header Functional Descriptor.
/**
 * @brief Header functional descriptor                            0x00
 *  (CDC120.pdf, 5.2.3.1 Table 15)
 *  This header must precede any list of class-specific descriptors.
 */
typedef struct _CDC_NCM_FUNCTIONAL_DESCRIPTOR {
  uint8_t bFunctionLength;                     // size of this descriptor in bytes
  uint8_t bDescriptorType;                     // CS_INTERFACE descriptor type
  uint8_t bDescriptorSubtype;                  // NCM Functional Descriptor subtype, as defined in Table 4-4
  uint16_t bcdNcmVersion;                      // Release number of this specification in BCD.
  uint8_t bmNetworkCapabilities;               // Specifies the capabilities of this function.
} __attribute__((packed)) CDC_NCM_FUNCTIONAL_DESCRIPTOR;


/**
 * @brief Unit Parameter Structure
 *  Format of the data returned when a GetProfile request is received
 *  (CAPI20.pdf, 8.0 )
 */
typedef struct _CDC_CAPI_PROFILE {
  uint16_t  bContolNum;                        /**< Number of controllers installed, least
                                                    significant byte first                        */
  uint16_t  bBChannelNum;                      /**< Number of supported B-channels, least
                                                    significant byte first                        */
  uint32_t  bGlobalOption;                     /**< Global Options                                */
  uint32_t  bB1Pocotol;                        /**< B1 protocols support                          */
  uint32_t  bB2Pocotol;                        /**< B2 protocols support                          */
  uint32_t  bB3Pocotol;                        /**< B3 protocols support                          */
  uint8_t   bISDNAPI[24];                      /**< reserved for COMMON-ISDN-API use              */
  uint8_t   bManufInfo[20];                    /**< Manufacturer-specific information             */
} __attribute__((packed)) CDC_CAPI_PROFILE;

// Notification header
// Data sent on the notification endpoint must follow this header.
// see  USB_SETUP_PACKET in file usb.h
typedef USB_SETUP_PACKET CDC_NOTIFICATION_HEADER;

#endif /* __USB_CDC_H */

