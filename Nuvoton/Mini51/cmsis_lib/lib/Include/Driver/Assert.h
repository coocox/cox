/*****************************************************************************
 * @file     Assert.h
 * @author   NuMicro MCU Software Team
 * @version  V1.00
 * @date     23. August 2011
 * @brief    Debug message Header File.
 *           This file contains the definition of assert_param() 
 *           
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef __NU_ASSERT_H__
#define __NU_ASSERT_H__

#ifdef __cplusplus
extern "C" {
#endif


#ifdef USE_ASSERT
#define	assert_param(expr)		{															\
									if (!(expr))											\
									{														\
										assert_error((uint8_t*)__FILE__, __LINE__);	        \
									}														\
								}

void assert_error(uint8_t* file, uint32_t line);
#else
#define	assert_param(expr)
#endif



#ifdef __cplusplus
}
#endif

#endif  // __NU_ASSERT_H__
