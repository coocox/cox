/*****************************************************************************
 *      U S B  - C O M M O M - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: type.h
 * @brief	: Type definition Header file for NOVOTON Family
 *            Microprocessors
 * @version	: 1.0
 * @date	: 28. Dec. 2010
 * @author	: CooCox
 ****************************************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

/**********************************************************************
 *    CodeRed - ifdef for GNU added to avoid potential clash with stdint.h
 **********************************************************************/
#if defined   (  __GNUC__  )
#include <stdint.h>
#else

/**********************************************************************
 *    exact-width signed integer types
 **********************************************************************/

typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

/**********************************************************************
 *    exact-width unsigned integer types
 **********************************************************************/

typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

#endif  /* __GNUC__ */

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#endif  /* __TYPE_H__ */
