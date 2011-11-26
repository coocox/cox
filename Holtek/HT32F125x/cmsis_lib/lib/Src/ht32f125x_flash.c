/*********************************************************************************************************//**
 * @file    ht32f125x_flash.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This files provides all the firmware functions about FLASH. 
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_flash.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Private_TypesDefinitions FLASH private types definitions 
  * @{
  */

/**
  * @}
  */  /* End of FLASH_Private_TypesDefinitions group */

/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Private_Define FLASH private definitions
  * @{
  */

/* Delay definition                                                                                         */
#define FLASH_TIMEOUT                 ((u32)0x000FFFFF)
  
/* FLASH OCMR                                                                                               */
#define FLASH_CMD_STADNBY             ((u32)0x00000000)
#define FLASH_CMD_PROGRAM             ((u32)0x00000004)
#define FLASH_CMD_PAGEERASE           ((u32)0x00000008)
#define FLASH_CMD_MASSERASE           ((u32)0x0000000A)

/* FLASH OPCR                                                                                               */
#define FLASH_READY                   ((u32)0x0000000C)
#define FLASH_SEND_MAIN               ((u32)0x00000014)

/* FLASH CFCR                                                                                               */
#define CFCR_WAIT_MASK                ((u32)0xFFFFFFF0)
#define CFCR_PFBE_MASK                ((u32)0xFFFFFFEF)
#define CFCR_IPSE_MASK                ((u32)0xFFFFFFBF)  

/**
  * @}
  */  /* End of FLASH_Private_Define group */  

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Private_Macro FLASH private macros
  * @{
  */

/**
 * @brief Check parameter of the FLASH idle power saving.
 */
#define IS_FLASH_POWERSAVING_STATE(STATE)   ((STATE == FLASH_POWERSAVING_ENABLE) || \
                                             (STATE == FLASH_POWERSAVING_DISABLE))

/**
 * @brief Check parameter of the FLASH pre-fetch buffer.
 */                                             
#define IS_FLASH_PREFETCHBUF_STATE(STATE)   ((STATE == FLASH_PREFETCHBUF_ENABLE) || \
                                             (STATE == FLASH_PREFETCHBUF_DISABLE))
           
/**
 * @brief Check parameter of the FLASH vector mapping.
 */                                              
#define IS_FLASH_VECTOR_MODE(MODE)          ((MODE == FLASH_BOOT_LOADER) || \
                                             (MODE == FLASH_BOOT_SRAM)   || \
                                             (MODE == FLASH_BOOT_MAIN))                                                                                  

/**
 * @brief Check parameter of the FLASH address.
 */ 
#define IS_FLASH_ADDRESS(ADDRESS)     (ADDRESS < 0x20000000)  /* Code 0.5GB Area */                                                                                          

/**
 * @brief Check parameter of the FLASH wait state.
 */ 
#define IS_FLASH_WAITSTATE(WAIT)      ((WAIT == FLASH_WAITSTATE_0) || \
                                       (WAIT == FLASH_WAITSTATE_1) || \
                                       (WAIT == FLASH_WAITSTATE_2))                                       
                
/**
 * @brief Check parameter of the FLASH interrupt status.
 */                                        
#define IS_FLASH_CLEAR_FLAG(FLAG)     ((FLAG & (u32)0x0003001F) != 0)                                       
           
/**
 * @brief Check parameter of the FLASH interrupt flag.
 */                                           
#define IS_FLASH_FLAG(FLAG)           ((FLAG == FLASH_FLAG_ORFF)  || \
                                       (FLAG == FLASH_FLAG_ITADF) || \
                                       (FLAG == FLASH_FLAG_OBEF)  || \
                                       (FLAG == FLASH_FLAG_IOCMF) || \
                                       (FLAG == FLASH_FLAG_OREF)  || \
                                       (FLAG == FLASH_FLAG_RORFF) || \
                                       (FLAG == FLASH_FLAG_PPERF))                           
        
/**
 * @brief Check parameter of the FLASH interrupt.
 */                                        
#define IS_FLASH_INT(IT)              ((IT & (u32)0x0000001F) != 0)                                       

/**
 * @brief Check parameter of the FLASH security.
 */ 
#define IS_FLASH_SEC_TYPE(TYPE)       ((TYPE == FLASH_SEC_OB)   || \
                                       (TYPE == FLASH_SEC_MAIN) || \
                                       (TYPE == FLASH_SEC_BOTH))

/**
  * @}
  */  /* End of FLASH_Private_Macro group */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Private_Variable FLASH private variables
  * @{
  */

/**
  * @}
  */  /* End of FLASH_Private_Variable group */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup FLASH_Private_Function_Prototype FLASH private function prototypes
  * @{
  */

/**
  * @}
  */  /* End of FLASH_Private_Function_Prototype group */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Private_Function FLASH private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Configure the FLASH wait state.
 * @param FLASH_WaitState: Value of FLASH latency.
 *        This parameter can be:
 *        @arg FLASH_WAITSTATE_0: FLASH zero wait clock
 *        @arg FLASH_WAITSTATE_1: FLASH one wait clock
 *        @arg FLASH_WAITSTATE_2: FLASH two wait clock
 * @retval None
 ************************************************************************************************************/
void FLASH_SetWaitState(u32 FLASH_WaitState)
{
  u32 regval = 0;
  
  /* Check the parameters */
  Assert_Param(IS_FLASH_WAITSTATE(FLASH_WaitState));
  
  regval = ( (FLASH->CFCR) & CFCR_WAIT_MASK ) | FLASH_WaitState;
  FLASH->CFCR = regval;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable FLASH power saving mode.
 * @param FLASH_PowerSaving: Setting of FLASH Power saving.
 *        This parameter can be:
 *        @arg FLASH_POWERSAVING_ENABLE : Enables FLASH idle power saving.
 *        @arg FLASH_POWERSAVING_DISABLE: Disables FLASH idle power saving.
 * @retval None
 ************************************************************************************************************/
void FLASH_SetPowerSaving(u32 FLASH_PowerSaving)
{
  /* Check the parameters */
  Assert_Param(IS_FLASH_POWERSAVING_STATE(FLASH_PowerSaving));
  
  FLASH->CFCR = ((FLASH->CFCR) & CFCR_IPSE_MASK) | FLASH_PowerSaving;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable FLASH pre-fetch buffer.
 * @param FLASH_PrefetchBuf: Setting of Pre-fetch buffer.
 *        This parameter can be:
 *        @arg FLASH_PREFETCHBUF_ENABLE : Enables FLASH pre-fetch buffer.
 *        @arg FLASH_PREFETCHBUF_DISABLE: Disables FLASH pre-fetch buffer.
 * @retval None
 ************************************************************************************************************/
void FLASH_SetPrefetchBuffer(u32 FLASH_PrefetchBuf)
{
  /* Check the parameters */
  Assert_Param(IS_FLASH_PREFETCHBUF_STATE(FLASH_PrefetchBuf));
  
  FLASH->CFCR = ((FLASH->CFCR) & CFCR_PFBE_MASK) | FLASH_PrefetchBuf;
}

/*********************************************************************************************************//**
 * @brief Set vector remapping mode.
 * @param RemapMode: Booting mode.
 *        This parameter can be:
 *        @arg FLASH_BOOT_LOADER: Boot loader mode.
 *        @arg FLASH_BOOT_SRAM  : SRAM booting mode.
 *        @arg FLASH_BOOT_MAIN  : Main FLASH mode.
 * @retval None
 ************************************************************************************************************/
void FLASH_SetRemappingMode(FLASH_Vector RemapMode)
{
  /* Check the parameters */
  Assert_Param(IS_FLASH_VECTOR_MODE(RemapMode));

  FLASH->VMCR = RemapMode;
}

/*********************************************************************************************************//**
 * @brief Erase a specific FLASH page.
 * @param PageAddress: Address of the erased page.
 * @retval FLASH_State can be: FLASH_COMPLETE, FLASH_BUSY, FLASH_ERR_ADDR_OUT_OF_RANGE, 
 *         FLASH_ERR_COMMAND, FLASH_ERR_ERROR.
 ************************************************************************************************************/ 
FLASH_State FLASH_ErasePage(u32 PageAddress)
{
  FLASH_State flashstate;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_ADDRESS(PageAddress));

  FLASH->OCMR = FLASH_CMD_PAGEERASE;
  FLASH->TADR = PageAddress;
  
  /* Wait for last operation to be completed                                                              */
  flashstate = FLASH_WaitForOperationEnd();

  return flashstate;
}

/*********************************************************************************************************//**
 * @brief Erase FLASH Option Byte page.
 * @retval FLASH_State can be: FLASH_COMPLETE, FLASH_BUSY, FLASH_ERR_ADDR_OUT_OF_RANGE, 
 *         FLASH_ERR_COMMAND, FLASH_ERR_ERROR, FLASH_ERR_WRITE_PROTECTED.
 ************************************************************************************************************/ 
FLASH_State FLASH_EraseOptionByte(void)
{
  vu32 wpstate;
  FLASH_State flashstate;

  /* Check the write protection status of Option Byte */
  wpstate = FLASH_GetSecurityStatus();
  
  if ( ((~wpstate) & FLASH_SEC_OB) != FLASH_SEC_OB )
  {
    FLASH->OCMR = FLASH_CMD_PAGEERASE;
    FLASH->TADR = OPTION_BYTE_BASE;
    
    /* Wait for last operation to be completed */
    flashstate = FLASH_WaitForOperationEnd();
  }
  else
  {
    flashstate = FLASH_ERR_WRITE_PROTECTED;
  }

  return flashstate;
}

/*********************************************************************************************************//**
 * @brief Erase the entire FLASH.
 * @retval FLASH_State can be: FLASH_COMPLETE, FLASH_BUSY, FLASH_ERR_ADDR_OUT_OF_RANGE, 
 *         FLASH_ERR_COMMAND, FLASH_ERR_ERROR.
 ************************************************************************************************************/ 
FLASH_State FLASH_MassErase(void) 
{
  FLASH_State flashstate;
  
  FLASH->OCMR = FLASH_CMD_MASSERASE;
  
  /* Wait for last operation to be completed                                                              */
  flashstate = FLASH_WaitForOperationEnd();

  return flashstate;
}

/*********************************************************************************************************//**
 * @brief Program one word data.
 * @param Address: The specific FLASH address to be programmed.
 * @param Data: The specific FLASH data to be programmed.
 * @retval FLASH_State can be: FLASH_COMPLETE, FLASH_BUSY, FLASH_ERR_ADDR_OUT_OF_RANGE, 
 *         FLASH_ERR_COMMAND, FLASH_ERR_ERROR.
 ************************************************************************************************************/ 
FLASH_State FLASH_ProgramWordData(u32 Address, u32 Data)
{
  FLASH_State flashstate;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_ADDRESS(Address));
  
  FLASH->OCMR = FLASH_CMD_PROGRAM;
  FLASH->TADR = Address;
  FLASH->WRDR = Data;
  
  /* Wait for last operation to be completed                                                              */
  flashstate = FLASH_WaitForOperationEnd();

  return flashstate;
} 
 
/*********************************************************************************************************//**
 * @brief Enable write protection for the specific pages.
 * @param FLASH_Pages: The specific pages to be write-protected.
 *        This parameter can be:
 *        @arg For HT32F1253: Between FLASH_WP_PAGE00 ~ FLASH_WP_PAGE30.
 *        @arg For HT32F1252: Between FLASH_WP_PAGE00 ~ FLASH_WP_PAGE15.
 *        @arg For HT32F1251: Between FLASH_WP_PAGE00 ~ FLASH_WP_PAGE07.
 *        @arg FLASH_WP_ALLPAGES 
 * @retval FLASH_State can be: FLASH_COMPLETE, FLASH_BUSY, FLASH_ERR_ADDR_OUT_OF_RANGE, 
 *         FLASH_ERR_COMMAND, FLASH_ERR_ERROR.
 ************************************************************************************************************/ 
FLASH_State FLASH_EnablePageWriteProtection(u32 FLASH_Pages)
{
  u32 checksum = 0xFFFFFFFF;
  FLASH_State flashstate = FLASH_COMPLETE;
  
  if (FLASH_Pages != 0)
  {
    FLASH->OCMR = FLASH_CMD_PROGRAM;
    FLASH->TADR = OB_PP0;
    FLASH->WRDR = ~FLASH_Pages;
    
    /* Wait for last operation to be completed                                                              */
    flashstate = FLASH_WaitForOperationEnd();
    
    if (flashstate == FLASH_COMPLETE)
    {
      /* Set Option Byte checksum as the sum of OB_PP0~3 and OB_CP */
      checksum = rw(OB_PP0);
      checksum += (0xFFFFFFFF + 0xFFFFFFFF + 0xFFFFFFFF);
      checksum += rw(OB_CP);
      
      flashstate = FLASH_ProgramWordData(OB_CHECKSUM, checksum);
    }
  }

  return flashstate;
} 
 
/*********************************************************************************************************//**
 * @brief Enable security lock for the option byte or the page of main FLASH.
 * @param SecurityType: The security lock type.
 *        This parameter can be:
 *        @arg FLASH_SEC_MAIN: Main FLASH lock.
 *        @arg FLASH_SEC_OB: Option Byte Page lock.
 *        @arg FLASH_SEC_BOTH: Both Page lock of the Main FLASH and Option Byte.
 * @retval FLASH_State can be: FLASH_COMPLETE, FLASH_BUSY, FLASH_ERR_ADDR_OUT_OF_RANGE, 
 *         FLASH_ERR_COMMAND, FLASH_ERR_ERROR.
 ************************************************************************************************************/ 
FLASH_State FLASH_EnableSecurity(FLASH_Security SecurityType)
{
  u32 checksum = 0xFFFFFFFF;
  FLASH_State flashstate = FLASH_COMPLETE;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_SEC_TYPE(SecurityType));
  
  FLASH->OCMR = FLASH_CMD_PROGRAM;
  FLASH->TADR = OB_CP;
  FLASH->WRDR = ~SecurityType;
  
  /* Wait for last operation to be completed                                                              */
  flashstate = FLASH_WaitForOperationEnd();

  if (flashstate == FLASH_COMPLETE)
  {
    /* Set Option Byte checksum as the sum of OB_PP0~3 and OB_CP */
    checksum = rw(OB_PP0);
    checksum += (0xFFFFFFFF + 0xFFFFFFFF + 0xFFFFFFFF);
    checksum += rw(OB_CP);
    
    flashstate = FLASH_ProgramWordData(OB_CHECKSUM, checksum);
  }

  return flashstate;
} 
 
/*********************************************************************************************************//**
 * @brief Return write-protection status of FLASH page .
 * @retval Write-protection status of the FLASH.
 ************************************************************************************************************/  
u32 FLASH_GetWriteProtectionStatus(void)
{
  /* Returns the register value of the Flash write-protection                                               */
  return (u32)(FLASH->PPSR[0]);
}  
  
/*********************************************************************************************************//**
 * @brief Return security status of the FLASH.
 * @retval security status of the FLASH.
 ************************************************************************************************************/   
u32 FLASH_GetSecurityStatus(void)
{
  return (u32)(FLASH->CPSR);
}  
  
/*********************************************************************************************************//**
 * @brief Enable or Disable the specific FLASH interrupts.
 * @param FLASH_INT: The specific FLASH interrupt.
 *        This parameter can be:
 *        @arg FLASH_INT_ORFIE, FLASH_INT_ITADIE, FLASH_INT_OBEIE, FLASH_INT_IOCMIE, 
 *             FLASH_INT_OREIE, FLASH_INT_ALL.
 * @param Cmd: The status of the FLASH interrupt.
 *        This parameter can be:
 *        @arg DISABLE 
 *        @arg ENABLE 
 * @retval None
 ************************************************************************************************************/  
void FLASH_IntConfig(u16 FLASH_INT, ControlStatus Cmd)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_INT(FLASH_INT));
  Assert_Param(IS_CONTROL_STATUS(Cmd));

  if (Cmd != DISABLE)
  {
    /* Enable the interrupt sources                                                                         */
    FLASH->OIER |= FLASH_INT;
  }
  else
  {
    /* Disable the interrupt sources                                                                        */
    FLASH->OIER &= ~(u32)FLASH_INT;
  }
}  
  
/*********************************************************************************************************//**
 * @brief Return flag status of the FLASH interrupt.
 * @param FLASH_FLAG: Flag of the FLASH interrupt.
 *        This parameter can be:
 *        @arg FLASH_FLAG_ORFF, FLASH_FLAG_ITADF, FLASH_FLAG_OBEF, FLASH_FLAG_IOCMF, 
 *             FLASH_FLAG_OREF, FLASH_FLAG_RORFF, FLASH_FLAG_PPERF
 * @retval FLASH operation flag can be SET or RESET.
 ************************************************************************************************************/  
FlagStatus FLASH_GetIntStatus(u32 FLASH_FLAG)
{ 
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  Assert_Param(IS_FLASH_FLAG(FLASH_FLAG));
  
  if ((FLASH->OISR & FLASH_FLAG) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return (bitstatus);
}  
 
/*********************************************************************************************************//**
 * @brief Clear specific interrupt flags of FLASH.
 * @param FLASH_FLAG: interrupt flag of FLASH.
 * @retval None
 ************************************************************************************************************/ 
void FLASH_ClearIntFlag(u32 FLASH_FLAG)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

  /* Clear the flags                                                                                        */
  FLASH->OISR = FLASH_FLAG;
} 
   
/*********************************************************************************************************//**
 * @brief Wait till the FLASH operation has finished or time-out has occurred.
 * @retval FLASH_State can be: FLASH_COMPLETE, FLASH_BUSY, FLASH_ERR_ADDR_OUT_OF_RANGE, 
 *         FLASH_ERR_COMMAND, FLASH_ERR_ERROR.
 ************************************************************************************************************/ 
FLASH_State FLASH_WaitForOperationEnd(void)
{
  vu32 RegVal;
  u32 Timeout = FLASH_TIMEOUT;
  FLASH_State flashstate = FLASH_COMPLETE;
  
  FLASH->OPCR = FLASH_SEND_MAIN;  
  __NOP();
  __NOP();
  __NOP();
  __NOP();  

  /* Wait till the FLASH operation has finished or time-out has occurred */
  while (Timeout)
  {
    /* Check the FLASH Status                                                                               */
    if (((FLASH->OPCR) & FLASH_READY) == FLASH_READY)
    {
      RegVal = FLASH->OISR;
      if ((RegVal & FLASH_FLAG_ITADF) == FLASH_FLAG_ITADF)
      {
        flashstate = FLASH_ERR_ADDR_OUT_OF_RANGE;
      }
      else if ((RegVal& FLASH_FLAG_IOCMF) == FLASH_FLAG_IOCMF)
      {
        flashstate = FLASH_ERR_COMMAND;
      }
      else if ((RegVal & FLASH_FLAG_OREF) == FLASH_FLAG_OREF)
      {
        flashstate = FLASH_ERR_ERROR;
      }
      break;
    }
    else if (Timeout == 0)
    {
      break;
    }
    Timeout--;
  }
  
  if (Timeout == 0)
  {
     flashstate = FLASH_TIME_OUT;     
  }
  
  FLASH->OPCR = FLASH_READY;
  
  return flashstate;
} 

/**
  * @}
  */  /* End of FLASH_Private_Function group */

/**
  * @}
  */  /* End of FLASH peripheral group */

/**
  * @}
  */  /* End of HT32F125x_Peripheral_Driver group */
