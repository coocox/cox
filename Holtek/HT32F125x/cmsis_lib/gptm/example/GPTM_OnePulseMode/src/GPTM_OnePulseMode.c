#include "ht32f125x.h"
#include "ht32f125x_gptm.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_ckcu.h"

void GPTM_OnePulseMode(void)
{
  GPTM_TimeBaseInitTypeDef TimeBaseInit;
  GPTM_OutputInitTypeDef OutInit;

  /* Enable peripheral clock of AFIO, GPIOB */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_PB, ENABLE);

  /* Config AFIO mode as GT0_ETI and GT0_CH3 function. */
  AFIO_GPBConfig(AFIO_PIN_10 | AFIO_PIN_11, AFIO_MODE_3) ;

  /* Enable peripheral clock of GPTM0 */
  CKCU_APBPerip1ClockConfig(CKCU_APBEN1_GPTM0, ENABLE);

  /* Time base configuration */
  GPTM_TimeBaseStructInit(&TimeBaseInit);
  TimeBaseInit.CounterMode = GPTM_CNT_MODE_UP;
  TimeBaseInit.CounterReload = 65535;
  TimeBaseInit.Prescaler = 1;
  TimeBaseInit.PSCReloadTime = GPTM_PSC_RLD_IMMEDIATE;
  GPTM_TimeBaseInit(GPTM0, &TimeBaseInit);

  /* GPTM0 PWM2 Mode configuration: Channel3 */
  GPTM_OutputStructInit(&OutInit);
  OutInit.Channel = GPTM_CH_3;
  OutInit.OutputMode = GPTM_OM_PWM2;
  OutInit.Control = GPTM_CHCTL_ENABLE;
  OutInit.Polarity = GPTM_CHP_NONINVERTED;
  OutInit.Compare = 16383;
  GPTM_OutputInit(GPTM0, &OutInit);

  /* GPTM0 ETI active at rising edge */
  GPTM_EtiConfig(GPTM0, GPTM_ETIPSC_OFF, GPTM_ETIPOL_NONINVERTED, 0);

  /* One Pulse Mode selection */
  GPTM_OnePulseModeCmd(GPTM0, ENABLE);

  /* Slave Trigger Input selection */
  GPTM_StiConfig(GPTM0, GPTM_TRSEL_ETIF);

  /* Slave Mode selection: Trigger Mode */
  GPTM_SlaveModeConfig(GPTM0, GPTM_SMSEL_TRIGGER);

  while(1);
}

