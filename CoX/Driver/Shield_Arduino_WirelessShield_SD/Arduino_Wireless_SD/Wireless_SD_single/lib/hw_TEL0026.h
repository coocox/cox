//*****************************************************************************
//
//! \file hw_TEL0026.h
//! \brief Commands for TEL0026 Arduino Bluetooth Bee driver.
//! \version V2.2.1.0
//! \date 3/5/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2013, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
//!
//!     * Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     * Neither the name of the <ORGANIZATION> nor the names of its
//! contributors may be used to endorse or promote products derived
//! from this software without specific prior written permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
#ifndef __HW_BLUETOOTHBEE_H__
#define __HW_BLUETOOTHBEE_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//
//! \addtogroup Wireless
//! @{
//
//! \addtogroup Bluetooth
//! @{
//
//! \addtogroup TEL0026
//! @{
//
//! \addtogroup TEL0026_Driver_Single
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup TEL0026_Bluetooth_Cmd_Table TEL0026 Bluetooth Command Table
//! \note These commands are all not contain "\r\n" because they are auto added
//! while sent.
//! @{
//
//*****************************************************************************
const static char BtCmdAt[] = "AT";
const static char BtCmdReset[] = "AT+RESET";
const static char BtCmdVersion[] = "AT+VERSION?";
const static char BtCmdRestore[] = "AT+ORGL";
const static char BtCmdAddr[] = "AT+ADDR?";
const static char BtCmdNameGet[] = "AT+NAME?";
const static char BtCmdNameSet[] = "AT+NAME=";
const static char BtCmdRemoteDevNameGet[] = "AT+RNAME?";
const static char BtCmdRoleGet[] = "AT+ROLE?";
const static char BtCmdRoleSet[] = "AT+ROLE=";
const static char BtCmdClassGet[] = "AT+CLASS";
const static char BtCmdClassSet[] = "AT+CLASS=";
const static char BtCmdInqAccCodeGet[] = "AT+IAC?";
const static char BtCmdInqAccCodeSet[] = "AT+IAC=";
const static char BtCmdInqModeGet[] = "AT+INQM?";
const static char BtCmdInqModeSet[] = "AT+INQM=";
const static char BtCmdPassWordGet[] = "AT+PSWD?";
const static char BtCmdPassWordSet[] = "AT+PSWD=";
const static char BtCmdUartParaGet[] = "AT+UART?";
const static char BtCmdUartParaSet[] = "AT+UART=";
const static char BtCmdConnectModeGet[] = "AT+CMODE?";
const static char BtCmdConnectModeSet[] = "AT+CMODE=";
const static char BtCmdBindAddrGet[] = "AT+BIND?";
const static char BtCmdBindAddrSet[] = "AT+BIND=";
const static char BtCmdLedDriverGet[] = "AT+DEFAULT";
const static char BtCmdLedDriverSet[] = "AT+POLAR=";
const static char BtCmdPIOOutSet[] = "AT+PIO=";
const static char BtCmdMPIOOutGet[] = "AT+MPIO?";
const static char BtCmdMPIOOutSet[] = "AT+MPIO=";
const static char BtCmdInqParaGet[] = "AT+IPSCAN?";
const static char BtCmdInqParaSet[] = "AT+IPSCAN=";
const static char BtCmdEnrgSaveGet[] = "AT+SNIFF?";
const static char BtCmdEnrgSaveSet[] = "AT+SNIFF=";
const static char BtCmdSecurityEncryptionGet[] = "AT+SENM?";
const static char BtCmdSecurityEncryptionSet[] = "AT+SENM=";
const static char BtCmdDelSelDev[] = "AT+RMSAD=";
const static char BtCmdDelAllDev[] = "AT+RMSAD";
const static char BtCmdLocSelDev[] = "AT+FSAD=";
const static char BtCmdTotalDevCnt[] = "AT+ADCN?";
const static char BtCmdLastDevAddrGet[] = "AT+MRAD?";
const static char BtCmdStatusGet[] = "AT+STATE?";
const static char BtCmdInitSppLib[] = "AT+INIT";
const static char BtCmdInqNearbyDev[] = "AT+INQ";
const static char BtCmdInqCancel[] = "AT+INQC";
const static char BtCmdDevicePairing[] = "AT+PAIR=";
const static char BtCmdDevConnect[] = "AT+LINK=";
const static char BtCmdDevDisConn[] = "AT+DISC";
const static char BtCmdEnterEnerSav[] = "AT+ENSNIFF";
const static char BtCmdExitEnerSav[] = "AT+EXSNIFF";
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup TEL0026_Bluetooth_Error_Code TEL0026 Bluetooth Error Code Define
//! @{
//
//*****************************************************************************
#define BT_ERR_OK                     0
#define BT_ERR_FAIL                   1
#define BT_ERR_SUCCESS                2
#define BT_ERR_NORESPONSE             3
#define BT_ERR_AT_CMD_ERR             4              //0
#define BT_ERR_DEFAULT_VALUE          5
#define BT_ERR_PSKEY_WRITE_ERROR      6
#define BT_ERR_DEVICE_NAME_TOO_LONG   7
#define BT_ERR_DEVICE_NAME_LEN_0      8
#define BT_ERR_NAP_TOO_LONG           9
#define BT_ERR_UAP_TOO_LONG           10
#define BT_ERR_LAP_TOO_LONG           11
#define BT_ERR_PIO_MASK_LEN_0         12
#define BT_ERR_INVALID_PIO_PORT       13
#define BT_ERR_DEVICE_CLASS_LEN_0     14
#define BT_ERR_DEVICE_CLASS_TOO_LONG  15
#define BT_ERR_INQ_CLASS_LEN_0        16
#define BT_ERR_INQ_CLASS_TOO_LONG     17
#define BT_ERR_INVALID_ACCESS_CODE    18
#define BT_ERR_PAIRING_PSWD_LEN_0     19
#define BT_ERR_PAIRING_PSWD_TOO_LONG  20
#define BT_ERR_INVALID_ROLE_SET       21
#define BT_ERR_INVALID_BAUDRATE       22
#define BT_ERR_INVALID_STOPBIT        23
#define BT_ERR_INVALID_PARITYBIT      24
#define BT_ERR_PAIRING_LIST_EMPTY     25
#define BT_ERR_SPP_NOT_INITIALIZED    26
#define BT_ERR_SPP_REPEAT_INIT        27
#define BT_ERR_INVALID_INQ_MODE       28
#define BT_ERR_INQUIRY_TIMEOUT        29
#define BT_ERR_ADDRESS_IS_0           30
#define BT_ERR_INVALID_SECURITY_MODE  31
#define BT_ERR_INVALID_ENCRYP_MODE    32
#define BT_ERR_UNKNOW_ERROR           33
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#define BT_ROLE_SLAVE                 '0'
#define BT_ROLE_MASTER                '1'
#define BT_ROLE_SLAVE_LOOP            '2'

#define BT_PIO2                       "2"
#define BT_PIO3                       "3"
#define BT_PIO4                       "4"
#define BT_PIO5                       "5"
#define BT_PIO6                       "6"
#define BT_PIO7                       "7"
//
//! PI08 drives the working status, and PI09 drives the link status.
//
#define BT_PIO10                      "10"

#define BT_PIO_LEVEL_HIGH             "1"
#define BT_PIO_LEVEL_LOW              "0"
//*****************************************************************************
//! \addtogroup TEL0026_Bluetooth_Res_Table TEL0026 Result and state Table
//! @{
//
//*****************************************************************************
const static char BtResOk[] = "OK";
const static char BtResFail[] = "FAIL";
const static char BtResSuccess[] = "SUCCESS";
const static char BtResError[] = "ERROR";
const static char BtStateInit[] = "INITIALIZED";
const static char BtStateReady[] = "READY";
const static char BtStatePairable[] = "PAIRABLE";
const static char BtStatePaired[] = "PAIRD";
const static char BtStateInquiring[] = "INQUIRING";
const static char BtStateConnecting[] = "CONNECTING";
const static char BtStateConnected[] = "CONNECTED";
const static char BtStateDisconnected[] = "DISCONNECTED";
const static char BtStateUnknow[] = "UNKNOW";
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************
#endif
