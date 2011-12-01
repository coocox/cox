//*****************************************************************************
// 
//! \file adt75.c
//! \brief Temperature Sensor(AD7416) and Four Single-Channel ADC drver
//! \version 1.0
//! \date 25. Aug. 2011
//! \author CooCox
//!
//! \copy
//!
//! Copyright(c)  2011, CooCox 
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
//! AND ANY ExPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, ExEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xi2c.h"
#include "xhw_adt75.h"
#include "adt75.h"

//*****************************************************************************
//
//! \brief Read the register of the ADT75 device.
//!
//! \param reg Register selected, it should be :
//!        - ADT75_REGISTER_TEMP Temperature Register
//!        - ADT75_REGISTER_CFG Configuration Register
//!        - ADT75_REGISTER_THYS Hysteresis Register
//!        - ADT75_REGISTER_TOS Over-Limit Signal Temperature register
//!        - ADT75_REGISTER_ONTSHOT One shot register
//!
//! \return  - Register value success 
//!          - -1 fail
//
//*****************************************************************************
long ADT75RegRead(unsigned char ucReg)
{
    xtI2CMasterTransferCfg cfg;
    unsigned char ucTemp = ucReg;
    unsigned char ucFlag;
    char ucRcv[2];    
    short ulRegData;  
    
    cfg.ulSlave = ADT75_I2C_ADDRESS;
    cfg.pvWBuf = &ucTemp;
    cfg.ulWLen = 1;
    cfg.ulRLen = 0;
    cfg.pvRBuf = ucRcv;
  
    //
    // different register has different receive length
    //
    switch(ucReg) 
    {
        //
        // Temperature Register
        //
        case ADT75_REGISTER_TEMP:  
          cfg.ulRLen = 2;
          break;
          
        //
        // Configuration Register1
        //
        case ADT75_REGISTER_CFG:  
          cfg.ulRLen = 1; 
          break;
   
        //
        // THYST SETPOINT REGISTER
        //
        case ADT75_REGISTER_THYS:  
          cfg.ulRLen = 2; 
          break; 
  
        //
        // TOS SETPOINT REGISTER
        //
        case ADT75_REGISTER_TOS:   
          cfg.ulRLen = 2; 
          break;
  
        default :        
          break;
    }    
    
    //
    // Data transfering
    //
    ucFlag = xI2CMasterTransfer(ADT75_MASTER_BASE, &cfg, I2C_TRANSFER_POLLING);
    if(ucFlag == xfalse)
    {
        //
        // if date transfer fail, return 0
        //
        return -1;
    }
      
    //
    // Deal with the receive buffer and return the register
    //
    switch(ucReg) 
    { 
        //
        // Return the MSB 12 bits of the 16 bits register
        //
        case ADT75_REGISTER_TEMP:    
        case ADT75_REGISTER_THYS:  
        case ADT75_REGISTER_TOS: 
          ulRegData = ucRcv[0];
          ulRegData = ulRegData << 8 ;
          ulRegData = ulRegData & 0xff00;
          ulRegData |= ucRcv[1];
          ulRegData = ulRegData >> 4; 
          break;
  
        //
        // Return the 8 bits config register
        //
        case ADT75_REGISTER_CFG: 
          ulRegData = ucRcv[0];
          break;
      
        default :     
          break;
    }
    
    //
    // return the select register value
    //
    return ulRegData;
}

//*****************************************************************************
//
//! \brief Write the register of the ADT75 device.
//!
//! \param reg Register selected, it should be :
//!        - ADT75_REGISTER_TEMP Temperature Register
//!        - ADT75_REGISTER_CFG Configuration Register
//!        - ADT75_REGISTER_THYS Hysteresis Register
//!        - ADT75_REGISTER_TOS Over-Limit Signal Temperature register
//!        - ADT75_REGISTER_ONTSHOT One shot register
//!
//! \return - 0 success
//!         - -1 fail
//*****************************************************************************
long ADT75RegWrite(unsigned char ucReg, short ulValue)
{
    xtI2CMasterTransferCfg cfg;
    unsigned char ucFlag;        
    unsigned char ucSendLength;
    unsigned char ucSendBuf[3]; 
    short ulRegValue = ulValue;   
    
    //
    // Send the register address first
    // 
    ucSendBuf[0] = ucReg;
    
    //
    //deal with the receive buffer and return the register
    //
    switch(ucReg) 
    {
        //
        // Write the two bytes register
        //
        case ADT75_REGISTER_TEMP: 
        case ADT75_REGISTER_THYS:  
        case ADT75_REGISTER_TOS: 
          ulRegValue = ulRegValue << 4;
          ucSendBuf[1] = ulRegValue >> 8;
          ucSendBuf[2] = ulRegValue & 0xff;
          ucSendLength = 3;
          break;        
  
        //
        // Write the one byte register
        //
        case ADT75_REGISTER_CFG: 
          ucSendBuf[1] = ulRegValue & 0xff;
          ucSendLength = 2;
          break;
          
        //
        // Write 0x04 to one-shot register
        //  
        case ADT75_REGISTER_ONTSHOT:  
          ucSendLength = 1;
        default :     
          break;
    }  
    
    cfg.ulSlave = ADT75_I2C_ADDRESS;
    cfg.pvWBuf = ucSendBuf;
    cfg.ulWLen = ucSendLength;
    cfg.ulRLen = 0;
    cfg.pvRBuf = 0;
   
    //
    // data transfering
    //
    ucFlag = xI2CMasterTransfer(ADT75_MASTER_BASE, &cfg, I2C_TRANSFER_POLLING);
    if(ucFlag == xfalse)
    {
        //
        // if transfer fail, return -1
        //
        return -1;
    }
    
    //
    // if transfer sucess, return 0
    //
    return 0;
}

//*****************************************************************************
//
//! \brief Initializes the i2c master, select the power mode.
//!
//! \param rate The master baud rate  
//!
//! \ulMode - ADT75_POWER_SHOTDOWN Shut down mode
//!         - ADT75_POWER_NORMAL Power normal mode
//!
//! \return None
//
//*****************************************************************************
void ADT75Init(unsigned long ulRate, unsigned long ulPowerMode)
{
    unsigned long ulTemp;
    
    //
    // Config the I2C master
    //
    if(ADT75_MASTER_BASE == I2C0_BASE)
    {
        //
        // Congigure the i2c pin
        //
        xSPinTypeI2C(I2C0SCK, ADT75_PIN_I2CSCK);
        xSPinTypeI2C(I2C0SDA, ADT75_PIN_I2CSDA);
    }
    else if(ADT75_MASTER_BASE == I2C1_BASE)
    {
        //
        // Congigure the i2c pin
        //
        xSPinTypeI2C(I2C1SCK, ADT75_PIN_I2CSCK);
        xSPinTypeI2C(I2C1SDA, ADT75_PIN_I2CSDA);     
    }
    else
    {
        //
        // more i2c to be enable
        //
    }
    
    //
    // Config the I2C master
    //
    xSysCtlPeripheralEnable2(ADT75_MASTER_BASE);
    
    //
    // Init the device rate
    //
    xI2CMasterInit(ADT75_MASTER_BASE, ulRate);
   
    //
    // Config the shut down mode
    //
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
    if(ulPowerMode == ADT75_POWER_SHOTDOWN)
    {
        ulTemp |= ADT75_CFG_POWER_SHOTDOWN; 
    }
    else
    {
        ulTemp &= ~ADT75_CFG_POWER_SHOTDOWN;
    }
    
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);
  
}

//*****************************************************************************
//
//! \brief Enable the sensor's shut dowm mode
//! 
//! \param None
//! 
//! \return None
//
//*****************************************************************************
void ADT75ShutDown(void)
{
    unsigned long ulTemp;
    //
    // Enable shut down mode
    //
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
    ulTemp |= ADT75_CFG_POWER_SHOTDOWN;
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);
}

//*****************************************************************************
//
//! \brief Disable the sensor's shut dowm mode
//! 
//! \param None
//! 
//! \return None
//
//*****************************************************************************
void ADT75WakeUp(void)
{
    unsigned long ulTemp;
    //
    // Disable shut down mode
    //
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
    ulTemp &= ~ADT75_CFG_POWER_SHOTDOWN;
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);
}

//*****************************************************************************
//
//! \brief Configure the device Int mode
//!
//! \param ulIntMode - ADT75_OPEMODE_CMP Select compare mode
//!                  - ADT75_OPEMODE_INT Select int mode
//!
//! \return None
//
//*****************************************************************************
void ADT75IntModeConfig(unsigned long ulIntMode)
{
    unsigned long ulTemp;
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
   
    if(ulIntMode == ADT75_OPEMODE_INT)
    {
        ulTemp |= ADT75_CFG_OPEMODE_INT;
    }
    else
    {
        ulTemp &= ~ADT75_CFG_OPEMODE_INT;
    }
   
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);
}

//*****************************************************************************
//
//! \brief Enable OTI mode corresponding pin interrupt.
//!
//! \param None
//! 
//! \return None
//
//*****************************************************************************
void ADT75IntEnable(void)
{
    unsigned long ulBase;
    
    xGPIOSPinTypeGPIOInput(ADT75_PIN_OS);
    xGPIOSPinIntEnable(ADT75_PIN_OS, ADT75_LEVEL_OS);
    ulBase = xGPIOSPinToPort(ADT75_PIN_OS);
    xIntEnable(xSysCtlPeripheraIntNumGet(ulBase)); 
}

//*****************************************************************************
//
//! \brief Disable OTI mode corresponding pin interrupt.
//!
//! \param None
//! 
//! \return None
//
//*****************************************************************************
void ADT75IntDisable(void)
{
    unsigned long ulBase;
    
    xGPIOSPinIntDisable(ADT75_PIN_OS);
    ulBase = xGPIOSPinToPort(ADT75_PIN_OS);
    xIntDisable(xSysCtlPeripheraIntNumGet(ulBase));       
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified OTI connected pin.
//!
//! \param xtI2CCallback is callback for the specified Port.
//!
//! Init interrupts callback for the specified Port.
//!
//! \return None.
//
//*****************************************************************************
void ADT75IntCallbackInit(xtEventCallback xtI2CCallback)
{
    //
    // A read operation reset the OTI pin level
    //
    ADT75RegRead(ADT75_REGISTER_CFG);
    
    //
    // Init interrupts callback for the specified Port.
    //
    xGPIOPinIntCallbackInit(xGPIOSPinToPort(ADT75_PIN_OS),
                             xGPIOSPinToPin(ADT75_PIN_OS), xtI2CCallback);
    
}

//*****************************************************************************
//
//! \brief Configure the device OS active level
//!
//! \param ulIntMode - ADT75_OSALERT_LEVEL_LOW OS Active low level
//!                  - ADT75_OSALERT_LEVEL_HIGH OS Active high level
//! \return None
//
//*****************************************************************************
void ADT75OSActiveLevelConfig(unsigned long ulOSLevel)
{   
    unsigned long ulTemp;
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
   
    if(ulOSLevel == ADT75_OSALERT_LEVEL_HIGH)
    {
        ulTemp |= ADT75_CFG_OSALERT_HIGH;
    }
    else
    {
        ulTemp &= ~ADT75_CFG_OSALERT_HIGH;
    }
   
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp); 
}

//*****************************************************************************
//
//! \brief Configure the device Fault queue value
//!
//! \param ulIntMode It's used to configure Overtemperature Fault Queue
//!        - ADT75_FAULTQUE_1 1 fault
//!        - ADT75_FAULTQUE_2 2 fault
//!        - ADT75_FAULTQUE_4 4 fault
//!        - ADT75_FAULTQUE_6 6 fault
//!
//! \return None
//
//*****************************************************************************
void ADT75FaultQueueConfig(unsigned long ulFaultQueue)
{
    unsigned long ulTemp;
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
    
    //
    // Clear the fault queue bits first
    //
    ulTemp &= ~ADT75_CFG_FAULTQUE_MASK;
    
    //
    // Set new fault queue bits value 
    //
    ulTemp |= ulFaultQueue;   
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);      
}

//*****************************************************************************
//
//! \brief Enable the device one shot mode 
//!  
//! \return None
//!
//! \note The device must in normal power mode before enable one shot mode
//
//*****************************************************************************
void ADT75OneShotEnable(void)
{
    unsigned long ulTemp;
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
    
    //
    // Set the OneShot bit
    //
    ulTemp |= ADT75_CFG_MODE_ONTSHOT;
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);  
}

//*****************************************************************************
//
//! \brief Disable the device one shot mode 
//!  
//! \return None
//
//*****************************************************************************
void ADT75OneShotDisable(void)
{
    unsigned long ulTemp;
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
    
    //
    // Clear the OneShot bit
    //
    ulTemp &= ~ADT75_CFG_MODE_ONTSHOT;
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);  
}

//*****************************************************************************
//
//! \brief One shot convert 
//!  
//! \return None
//
//*****************************************************************************
void ADT75OneShotConvst(void)
{
    //
    // Write 0x04 to address register to trigger one convert
    //
    ADT75RegWrite(ADT75_REGISTER_ONTSHOT, 0);  
    
    //
    // Wait for a minimum of 60 ms after writing to the one-shot register before 
    // reading back the temperature. This time ensures the ADT75 has time to 
    // power up and do a conversion.
    //
    xSysCtlDelay(100);
}

//*****************************************************************************
//
//! \brief Configure the device SMBus ALERT  
//!  
//! \param ulSMBusAlert Enable or disable SMBus Alert
//!        - ADT75_CFG_ALERT_ENABLE Enable SMBus Alert
//!        - ADT75_CFG_ALERT_DISABLE Disable SMBus Alert
//!
//! \note SMBus alert function mode can be Enabled in interrupt mode only
//!
//! \return None
//
//*****************************************************************************
void ADT75AlertConfig(unsigned long ulSMBusAlert)
{
    unsigned long ulTemp;
    ulTemp = ADT75RegRead(ADT75_REGISTER_CFG);
    
    if(ulSMBusAlert == ADT75_CFG_ALERT_ENABLE)
    {
        ulTemp |= ADT75_CFG_ALERT_ENABLE;
    }
    else
    {
        ulTemp &= ~ADT75_CFG_ALERT_ENABLE;
    }
    
    ADT75RegWrite(ADT75_REGISTER_CFG, ulTemp);   
}

//*****************************************************************************
//
//! \brief Read the temperature value in integer degree celsius(°„C)
//!
//! \return temperature in integer mode
//
//*****************************************************************************
long ADT75TempReadLDC(void)
{
    short sTemp;
    
    //
    // Read the temperature register
    //
    sTemp = ADT75RegRead(ADT75_REGISTER_TEMP);
    
    //
    // Conveter the temperature register data to degree celsius(°„C)
    //
    sTemp = (short)(sTemp * 0.0625);

    return sTemp;
}

//*****************************************************************************
//
//! \brief Read the temperature value in float degree celsius(°„C)
//!
//! \return temperature in float mode
//
//*****************************************************************************
float ADT75TempReadFDC(void)
{
    short sTemp;
    float fTemp;   
    //
    // Read the temperature register
    //
    sTemp = ADT75RegRead(ADT75_REGISTER_TEMP);
     
    //
    // Conveter the temperature register data to degree celsius(°„C)
    //
    fTemp =(float)(sTemp * 0.25);   
    return fTemp;
}


//*****************************************************************************
//
//! \brief Read the temperature value in original register data
//!
//! \return temperature register value
//
//*****************************************************************************
long ADT75TempReadMSB10Bit(void)
{
    short sTemp;
    //
    // Read the temperature register
    //
    sTemp = ADT75RegRead(ADT75_REGISTER_TEMP);
    
    return sTemp;
}

//*****************************************************************************
//
//!
//! \brief Set THYST setpoint register in float degree celsius(°„C)
//!
//! \param fTemp Temperature value in degree celsius(-40°„C ~127 °„C)
//!
//! \return None
//
//*****************************************************************************
void ADT75UpLimitSetFloat(float fTemp)
{   
    short sTemp;
    
    //
    // 1 bit corresponding to 0.0625
    //  
    sTemp =(short)(fTemp / 0.0625);  
    
    ADT75RegWrite(ADT75_REGISTER_TOS, sTemp);
}

//*****************************************************************************
//
//!
//! \brief Set THYST setpoint register  in long degree celsius(°„C)
//!
//! \param lTemp Temperature value in  degree celsius(-40°„C ~127 °„C)
//!
//! \return None
//
//*****************************************************************************
void ADT75UpLimitSetLong(long lTemp)
{   
    short sTemp;
    //
    // 1 bit corresponding to 0.0625
    //  
    sTemp =(short)(lTemp / 0.0625);  
    
    ADT75RegWrite(ADT75_REGISTER_TOS, sTemp);
}

//*****************************************************************************
//
//!
//! \brief Set TOS setpoint register in float degree celsius(°„C)
//!
//! \param fTemp Temperature value in degree celsius(-40°„C ~127 °„C)
//!
//! \return None
//
//*****************************************************************************
void ADT75LowLimitSetFloat(float fTemp)
{   
    short sTemp;
    
    //
    // 1 bit corresponding to 0.0625
    //  
    sTemp =(short)(fTemp / 0.0625);  
    
    ADT75RegWrite(ADT75_REGISTER_THYS, sTemp);
}

//*****************************************************************************
//
//! \brief Set THYST setpoint register  in long degree celsius(°„C)
//!
//! \param lTemp Temperature value in  degree celsius(-40°„C ~127 °„C)
//!
//! \return None
//
//*****************************************************************************
void ADT75LowLimitSetLong(long lTemp)
{   
    short sTemp;
    
    //
    // 1 bit corresponding to 0.0625
    //  
    sTemp =(short)(lTemp / 0.0625);  
    
    ADT75RegWrite(ADT75_REGISTER_THYS, sTemp);
}

//*****************************************************************************
//
//! \brief de-init the ADT75 device
//!
//! \return None
//
//*****************************************************************************
void ADT75DeInit(void)
{
    xSysCtlPeripheralDisable2(ADT75_MASTER_BASE);
}
