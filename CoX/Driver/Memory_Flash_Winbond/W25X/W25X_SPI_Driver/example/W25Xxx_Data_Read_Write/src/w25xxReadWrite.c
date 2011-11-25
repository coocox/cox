//*****************************************************************************
//
//! \file w25xxReadWrite.c
//! \brief Get temperature from TC77.
//! \version 1.0
//! \date 9/11/2011
//! \author CooCox
//
//*****************************************************************************

#include "xhw_types.h"
#include "w25x.h"
#include "w25xxReadWrite.h"
#include "xsysctl.h"

unsigned char ucWriteData[] = "I stand on this rostrum with a sense of deep hu \
humility in the weight of those great American architects of our history who h \
the purest form yet devised. Here are centered the hopes and aspirations and f \
entire human race. I do not stand here as advocate for any partisan cause, for \
are fundamental and reach quite beyond the realm of partisan consideration.The \
our future protected. I trust, therefore,that you will do me the justice of re \
that which I have to say as solely expressing the considered viewpoint of a fe \
humility in the weight of those great American architects of our history who h \
pride in the reflection that this home of legislative debate represents human  \
Do you love it,Put all eggs in one basket?Fall in love at first sight!";

//
//! Get the Length of data will be oparated
//
#define Length sizeof(ucWriteData)

unsigned char ucReadData[Length];

//*****************************************************************************
//
//! \brief The example of reading and writintg data of W25Xxx.
//!
//! \param None
//!
//! This function is to tell you how to use W25Xxx
//!
//! \return none
//
//*****************************************************************************
void W25XxxReadWrite(void)
{   

    //
    // Step 1, you should set system clock.
    // 
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Step 2, you should initialize W25Xxx
    // 
    W25XInit(10000);
    
    //
    // Step 3, you should check whether W25Xxx is existent and usable or not
    // 
    if(0xEF14 == W25XIDcodeGet())
    {
      
    //
    // Step 4, you should erase chip,a block or a sector.
    //
        W25XChipErase();
    
    //
    // Step 5, you can write some data to W25Xxx.
    //
        W25XWrite(ucWriteData, 138, Length);
    
    
    //
    // Step 6, you can read some data from W25Xxx.
    //
        W25XRead(ucReadData, 138, Length);
    }
}
