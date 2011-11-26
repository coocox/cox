#include "ht32f125x.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_i2c.h"
#include "ht32f125x_gpio.h"

/********************************************************************************************//*
 * @brief  This is a simple example which shows how to Init the i2c.
 * @in     None
 * @return None
 *********************************************************************************************/
void I2C_CfgInit(void)
{
  I2C_InitTypeDef I2C_InitStructure;

  /* Enable AFIO & I2C clock */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_I2C, ENABLE);

  /* Configure I2C SCL pin, I2C SDA pin */
  AFIO_GPAConfig(AFIO_PIN_11, AFIO_MODE_1);
  AFIO_GPAConfig(AFIO_PIN_12, AFIO_MODE_1);

  /* I2C configuration */
  I2C_InitStructure.I2C_GeneralCall = I2C_GENERALCALL_DISABLE;
  I2C_InitStructure.I2C_AddressingMode = I2C_ADDRESSING_7BIT;
  I2C_InitStructure.I2C_Acknowledge = I2C_ACK_DISABLE;
  I2C_InitStructure.I2C_OwnAddress = 0x00;
  I2C_InitStructure.I2C_Speed = 400000;
  I2C_Init(I2C, &I2C_InitStructure);
  while(1);
}



