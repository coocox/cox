/*****************************************************************************
 *      U S B  -  M S C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: usb_msc.h
 * @brief	: USB Mass Storage Class Definitions
 * @version	: 1.0
 * @date	: 28. Dec. 2010
 * @author	: CooCox
 ****************************************************************************/

#ifndef __USB_MSC_H__
#define __USB_MSC_H__


/***********************************************************************
 * MSC Subclass Codes
 **********************************************************************/
#define MSC_SUBCLASS_RBC                0x01
#define MSC_SUBCLASS_SFF8020I_MMC2      0x02
#define MSC_SUBCLASS_QIC157             0x03
#define MSC_SUBCLASS_UFI                0x04
#define MSC_SUBCLASS_SFF8070I           0x05
#define MSC_SUBCLASS_SCSI               0x06
#define MSC_SUBCLASS_LSD_FS             0x07
#define MSC_SUBCLASS_IEEE_1667          0x08

/***********************************************************************
 * MSC Protocol Codes
 **********************************************************************/
#define MSC_PROTOCOL_CBI_INT            0x00
#define MSC_PROTOCOL_CBI_NOINT          0x01
#define MSC_PROTOCOL_OBSKLETE           0x02
#define MSC_PROTOCOL_BULK_ONLY          0x50
#define MSC_PROTOCOL_UAS                0x62

/***********************************************************************
 * MSC Request Codes
 **********************************************************************/
#define MSC_REQUEST_ADSC                0x00
#define MSC_REQUEST_GET_REQ             0xFC
#define MSC_REQUEST_PUT_REQ             0xFD
#define MSC_REQUEST_RESET               0xFF
#define MSC_REQUEST_GET_MAX_LUN         0xFE

/***********************************************************************
 * MSC Bulk-only Stage
 **********************************************************************/
#define MSC_BS_CBW                      0       /* Command Block Wrapper */
#define MSC_BS_DATA_OUT                 1       /* Data Out Phase */
#define MSC_BS_DATA_IN                  2       /* Data In Phase */
#define MSC_BS_DATA_IN_LAST             3       /* Data In Last Phase */
#define MSC_BS_DATA_IN_LAST_STALL       4       /* Data In Last Phase with Stall */
#define MSC_BS_CSW                      5       /* Command Status Wrapper */
#define MSC_BS_ERROR                    6       /* Error */


/**
 * @brief Bulk-only Command Block Wrapper
 */
typedef struct _MSC_CBW {
  uint32_t dSignature;
  uint32_t dTag;
  uint32_t dDataLength;
  uint8_t  bmFlags;
  uint8_t  bLUN;
  uint8_t  bCBLength;
  uint8_t  CB[16];
} __attribute__((packed)) MSC_CBW;


/**
 * @brief Bulk-only Command Status Wrapper
 */
typedef  struct _MSC_CSW {
  uint32_t dSignature;
  uint32_t dTag;
  uint32_t dDataResidue;
  uint8_t  bStatus;
} __attribute__((packed)) MSC_CSW;

#define MSC_CBW_Signature               0x43425355
#define MSC_CSW_Signature               0x53425355

/***********************************************************************
 * CSW Status Definitions
 **********************************************************************/
#define CSW_CMD_PASSED                  0x00
#define CSW_CMD_FAILED                  0x01
#define CSW_PHASE_ERROR                 0x02

/***********************************************************************
 * SCSI Commands
 **********************************************************************/
#define SCSI_TEST_UNIT_READY            0x00
#define SCSI_REQUEST_SENSE              0x03
#define SCSI_FORMAT_UNIT                0x04
#define SCSI_INQUIRY                    0x12
#define SCSI_MODE_SELECT6               0x15
#define SCSI_MODE_SENSE6                0x1A
#define SCSI_START_STOP_UNIT            0x1B
#define SCSI_MEDIA_REMOVAL              0x1E
#define SCSI_READ_FORMAT_CAPACITIES     0x23
#define SCSI_READ_CAPACITY              0x25
#define SCSI_READ10                     0x28
#define SCSI_WRITE10                    0x2A
#define SCSI_VERIFY10                   0x2F
#define SCSI_READ12                     0xA8
#define SCSI_WRITE12                    0xAA
#define SCSI_MODE_SELECT10              0x55
#define SCSI_MODE_SENSE10               0x5A

/***********************************************************************
 * UFI Commands
 **********************************************************************/
#define UFI_TEST_UNIT_READY             0x00
#define UFI_REZORE_UNIT                 0x01
#define UFI_REQUEST_SENSE               0x03
#define UFI_FORMAT_UNIT                 0x04
#define UFI_INQUIRY                     0x12
#define UFI_START_STOP_UNIT             0x1B
#define UFI_SEND_DIAGNOSTIC             0x1D
#define UFI_MEDIA_REMOVAL               0x1E
#define UFI_READ_FORMAT_CAPACITIES      0x23
#define UFI_READ_CAPACITY               0x25
#define UFI_READ10                      0x28
#define UFI_WRITE10                     0x2A
#define UFI_SEEK10                      0x2B
#define UFI_WRITE1_VERIFY               0x2E
#define UFI_VERIFY                      0x2F
#define UFI_READ12                      0xA8
#define UFI_WRITE12                     0xAA
#define UFI_MODE_SELECT                 0x55
#define UFI_MODE_SENSE                  0x5A

/***********************************************************************
 * Assigned wValue Codes
 **********************************************************************/
#define MSC_REQ_GLI                     0x00
#define MSC_REQ_SPO                     0x01
#define MSC_REQ_MPO                     0x02
#define MSC_REQ_CPO                     0x03
#define MSC_REQ_EPO                     0x04
#define MSC_REQ_EFP                     0x05
#define MSC_REQ_LA                      0x06
#define MSC_REQ_CIAO                    0x07


#endif  /* __USB_MSC_H__ */
