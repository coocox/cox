#include "ht32f125x.h"
#include "ht32f125x_spi.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_ckcu.h"

/************************************************************************************//*
 * @ breif: a simple code segment to show how to config the spi as master mode.
 * @ in:  none
 * @ return:  none
 **************************************************************************************/
void SPI_MasterMode_Init(void)
{
  SPI_InitTypeDef SPI_InitStructure;

  /*  Enable AFIO & SPI SEL pin port & SPI clock  */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_PB | CKCU_APBEN0_SPI, ENABLE);

  /*  Configure SPI SEL pin  */
  GPIO_SetOutBits(GPIOB, GPIO_PIN_7);
  GPIO_DirectionConfig(GPIOB, GPIO_PIN_7, GPIO_DIR_OUT);

  /*  SPI Configuration */
  SPI_InitStructure.SPI_Mode = SPI_MASTER;
  SPI_InitStructure.SPI_FIFO = SPI_FIFO_DISABLE;
  SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
  SPI_InitStructure.SPI_SSMode = SPI_SS_SOFTWARE;
  SPI_InitStructure.SPI_SSPolarity = SPI_SSPOLARITY_LOW;
  SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_HIGH;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_SECOND;
  SPI_InitStructure.SPI_RxFIFOTriggerLevel = 0;
  SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;
  SPI_InitStructure.SPI_ClockPrescaler = 4;
  SPI_Init(SPI, &SPI_InitStructure);

  SPI_SSOutputCmd(SPI, ENABLE);

  SPI_Cmd(SPI, ENABLE);
}
