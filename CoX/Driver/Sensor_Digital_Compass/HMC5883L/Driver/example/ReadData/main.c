//*****************************************************************************
//
//! \file main.c
//! \brief Show how to read Compass data.
//! \version 1.0
//! \date 7/1/2013
//! \author CooCox
//
//*****************************************************************************

#include "HMC5883L.h"

extern void ReadData(void);

void main(void)
{
    //Run the demo
    ReadData();
    while(1);
}


