//*****************************************************************************
//
//! \file gps.h
//! \brief Prototypes for GPS EB-365 Driver.
//! \version 2.1.1.0
//! \date 10/18/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX 
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

#ifndef _GPS_H_
#define _GPS_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GPS
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup EB-365
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup EB-365_Struct_Define
//!    
//! @{
//
//***************************************************************************** 

typedef struct {
    unsigned int  year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
}DATE_TIME;

typedef struct {
    unsigned char NS;                // North / South
    unsigned char EW;                // East / West
    double latitude;                 // latitude(data format: ddmm.mmmm)
    unsigned char latitude_Degree;   // latitude(d)
    unsigned char latitude_Cent;     // latitude(m)
    unsigned char latitude_Second;   // latitude(s)
    double longitude;                // longitude(data format: dddmm.mmmm)
    unsigned char longitude_Degree;  // longitude(d)
    unsigned char longitude_Cent;    // longitude(m)
    unsigned char longitude_Second;  // longitude(s)
    float speed;                     // speed(unit£ºkm/h)
    float direction;                 // angle / direction
    float height_sea;                // (MSL)
    float height_ground;
    DATE_TIME D;
}GPS_INFO;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GPS_Exported_APIs  GPS Driver APIs
//! \brief API Reference of GPS Driver.
//! @{
//
//*****************************************************************************
extern void GPS_Init(unsigned long ulBaudrate);
extern unsigned char GPS_GPGGA(char *str, GPS_INFO *GPS);
extern unsigned char GPS_GPGLL(char *str, GPS_INFO *GPS);
extern unsigned char GPS_GPGSA(char *str, GPS_INFO *GPS);
extern unsigned char GPS_GPRMC(char *str, GPS_INFO *GPS);
extern unsigned char GPS_GPVTG(char *str, GPS_INFO *GPS);
extern unsigned char GPS_GPGSV(char *str, GPS_INFO *GPS);
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //_GPS_H_
