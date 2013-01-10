//*****************************************************************************
//
//! \file Example.c
//! \brief Example
//! \version 1.0
//! \date 9/1/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xi2c.h"
#include "xhw_i2c.h"
#include "xgpio.h"
#include "24LC64.h"
#include "hw_24LC64.h"

const int DATA_LEN=35;
void  _24LC64_Write_Read(void)
{
	int i;
  char testRst[] = {1,1,1,1,1};
	unsigned short usWriteAddr = 0x15;
	unsigned char w_data[35];
	unsigned char r_data[35] = {0};

	for(i=0;i<DATA_LEN;i++)
		w_data[i] = i;

	_24LC64_Init();



	//bytewrite test
	_24LC64_ByteWrite(&w_data[10], usWriteAddr);
	_24LC64_BufferRead(r_data, usWriteAddr, 1);
	if(r_data[0] != w_data[10])
		testRst[0] = 0;



	//pagewrite test
	_24LC64_PageWrite(w_data,usWriteAddr,20);
	_24LC64_BufferRead(r_data, usWriteAddr, 20);
	for(i=0;i<11;i++)
	{
		if(r_data[i] != w_data[i])
		{
			testRst[1] = 0;
			break;
		}
	}


	//buffer write test
	_24LC64_BufferWrite(w_data,usWriteAddr,DATA_LEN);
	_24LC64_BufferRead(r_data, usWriteAddr, DATA_LEN);
	for(i=0;i<DATA_LEN;i++)
	{
		if(r_data[i] != w_data[i])
		{
			testRst[2] = 0;
			break;
		}
	}

    while(1);
};
