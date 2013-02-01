//*****************************************************************************
//
//! \file T6963C.c
//! \brief the T6963C Driver.
//! \version V2.1.1.0
//! \date 1/15/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "Xhw_spi.h"
#include "xgpio.h"
#include "xhw_gpio.h"
#include "T6963C.h"

unsigned char data_pins[] = {xGPIO_PIN_0, xGPIO_PIN_1, xGPIO_PIN_2, xGPIO_PIN_3,
                        xGPIO_PIN_4, xGPIO_PIN_5, xGPIO_PIN_6, xGPIO_PIN_7};


extern unsigned char CGTAB[64];

unsigned char gph_clr_byte[][32]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

static void delay(int n)
{
    int i;
    for(i=0;i<n;i++);
}

//*****************************************************************************
//
//! \brief Set the data pins as output mode, this's necessary before writing.
//!
//! \return None.
//
//*****************************************************************************
static void setPinMode_Output()
{
    int i;
    for(i=7;i>=0;i--)
    {
        xGPIODirModeSet(LCD_DATA_PORT, data_pins[i], xGPIO_DIR_MODE_OUT);
    }
}

//*****************************************************************************
//
//! \brief Set the data pins as input mode, this's necessary before reading.
//!
//! \return None.
//
//*****************************************************************************
static void setPinMode_Input()
{

    int i;
    for(i=7;i>=0;i--)
    {
        xGPIODirModeSet(LCD_DATA_PORT, data_pins[i], xGPIO_DIR_MODE_IN);
    }
}

//*****************************************************************************
//
//! \brief Write one byte to T6963C.
//!
//! \param data data to write
//!
//! \return None.
//
//*****************************************************************************
static void setData(unsigned char data)
{

    int i;
    setPinMode_Output();
    for(i=7;i>=0;i--)
    {
        GPIOPinWrite(LCD_DATA_PORT, data_pins[i], (data>>i)&1);
    }
}

//*****************************************************************************
//
//! \brief read data from T6963C.
//!
//! \return the data read from T6963C, 8bits.
//
//*****************************************************************************
static unsigned char getData()
{
    unsigned char data=0;
    setPinMode_Input();
    GPIOPinWrite(LCD_DATA_PORT, LCD_CD, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 0);
    GPIOPinWrite(LCD_DATA_PORT, LCD_RD, 0);
    delay(2);
    data = xHWREG(LCD_DATA_PORT + GPIO_PIN);
    GPIOPinWrite(LCD_DATA_PORT, LCD_RD, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 1);
    return data;
}


//*****************************************************************************
//
//! \brief Init the T6963C LCD.
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Init()
{
    //
    // Enable the GPIOx port which is connected with T6963C
    //
    xSysCtlPeripheralEnable(LCD_DATA_PORT);


    xGPIODirModeSet(LCD_DATA_PORT, LCD_FS, xGPIO_DIR_MODE_OUT);
    xGPIODirModeSet(LCD_DATA_PORT, LCD_WR, xGPIO_DIR_MODE_OUT);
    xGPIODirModeSet(LCD_DATA_PORT, LCD_RD, xGPIO_DIR_MODE_OUT);
    xGPIODirModeSet(LCD_DATA_PORT, LCD_CS, xGPIO_DIR_MODE_OUT);
    xGPIODirModeSet(LCD_DATA_PORT, LCD_CD, xGPIO_DIR_MODE_OUT);
    xGPIODirModeSet(LCD_DATA_PORT, LCD_RESET, xGPIO_DIR_MODE_OUT);

    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 0);
    GPIOPinWrite(LCD_DATA_PORT, LCD_RESET, 0);
    delay(10);
    GPIOPinWrite(LCD_DATA_PORT, LCD_RESET, 1);

    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 0);
    GPIOPinWrite(LCD_DATA_PORT, LCD_RD, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_WR, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_FS, 0);

    // set text area address
    T6963C_WriteDoublePara(TXTSTART, TXTSTART>>8, LCD_TXT_STP);
    // set text area width
    T6963C_WriteDoublePara(LCD_GRH_WID_NUM, 0x00, LCD_TXT_WID);
    // set graphic area address
    T6963C_WriteDoublePara(GRSTART, GRSTART>>8, LCD_GRH_STP);
    // set the width of graphic area
    T6963C_WriteDoublePara(LCD_GRH_WID_NUM, 0x00, LCD_GRH_WID);
    // display mode£ºor
    T6963C_WriteCMD(LCD_MOD_OR);
    // graphic display
    T6963C_WriteCMD(LCD_DIS_SW|0x08);
    // cursor with 7 lines
    T6963C_WriteCMD(LCD_CUR_SHP|0x07);
}

//*****************************************************************************
//
//! \brief Write one byte.
//!
//! \param data data to write
//!
//! \return None.
//
//*****************************************************************************
void T6963C_WriteData(unsigned char data)
{
    T6963C_StatusCheck(STATUS_RW);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CD, 0);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 0);
    setData(data);
    GPIOPinWrite(LCD_DATA_PORT, LCD_WR, 0);
    delay(2);
    GPIOPinWrite(LCD_DATA_PORT, LCD_WR, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 1);
}

//*****************************************************************************
//
//! \brief Auto write one byte.
//!
//! \param data data to write
//!
//! \return None.
//
//*****************************************************************************
void T6963C_AutoWriteData(unsigned char data)
{
    T6963C_StatusCheck(STATUS_AUTO_W);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CD, 0);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 0);
    setData(data);
    GPIOPinWrite(LCD_DATA_PORT, LCD_WR, 0);
    delay(2);
    GPIOPinWrite(LCD_DATA_PORT, LCD_WR, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 1);
}

//*****************************************************************************
//
//! \brief Write one command with no parameter.
//!
//! \param cmd the command
//!
//! \return None.
//
//*****************************************************************************
void T6963C_WriteCMD(unsigned char cmd)
{
    T6963C_StatusCheck(STATUS_RW);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CD, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 0);
    setData(cmd);
    GPIOPinWrite(LCD_DATA_PORT, LCD_WR, 0);
    delay(2);
    GPIOPinWrite(LCD_DATA_PORT, LCD_WR, 1);
    GPIOPinWrite(LCD_DATA_PORT, LCD_CS, 1);
}

//*****************************************************************************
//
//! \brief Write one command with one parameter.
//!
//! \param data the parameter
//! \param cmd the command
//!
//! \return None.
//
//*****************************************************************************
void T6963C_WriteOnePara(unsigned char data,
                            unsigned char cmd)
{
    T6963C_WriteData(data);
    T6963C_WriteCMD(cmd);
}

//*****************************************************************************
//
//! \brief Write one command with two parameters.
//!
//! \param data1 parameter one
//! \param data2 parameter two
//! \param cmd the command
//!
//! \return None.
//
//*****************************************************************************
void T6963C_WriteDoublePara(unsigned char data1,
                unsigned char data2, unsigned char cmd)
{
    T6963C_WriteData(data1);
    T6963C_WriteData(data2);
    T6963C_WriteCMD(cmd);
}

//*****************************************************************************
//
//! \brief Check the status.
//!
//! \param mode the status to check
//!
//! \return None.
//
//*****************************************************************************
void T6963C_StatusCheck(unsigned char mode)
{
    unsigned char data=0;
    do
    {
        data = getData();
    }while((data&mode)!=mode);
}

//*****************************************************************************
//
//! \brief RAM char generate
//!
//! \return None.
//
//*****************************************************************************
void T6963C_CGRAM()
{
    unsigned int i;

    //
    // set CGRAM offset address
    //
    T6963C_WriteDoublePara(0x03, 0x00, LCD_CGR_POS);

    //
    // set address pointer: 0x1c00
    //
    T6963C_WriteDoublePara(0x00, 0x1c, LCD_ADR_POS);

     //
     // set  auto write mode
    //
    T6963C_WriteCMD(LCD_AUT_WR);
    for(i=0;i<64;i++)
     {
        T6963C_AutoWriteData(CGTAB[i]);
     }
   T6963C_WriteCMD(LCD_AUT_OVR);
}

//*****************************************************************************
//
//! \brief Display string with data code
//!
//! \param row the row to display
//! \param col the column to display
//! \param pDataCode the data code
//! \param len the length to display
//!
//! \return None.
//
//*****************************************************************************
void T6963C_ShowString(unsigned char row, unsigned char col,
                                    unsigned char *pDataCode, unsigned char len)
{
    int i, addr;
    for(i=0; i<len; i++)
    {
        addr = row*LCD_GRH_WID_NUM + col;
        T6963C_WriteDoublePara(addr, addr>>8, LCD_ADR_POS);
        T6963C_WriteOnePara(pDataCode[i], LCD_NOC_WR);
        col++;
        if(col==LCD_GRH_WID_NUM)
        {
            col = 0;
            row++;
        }
    }
}

//*****************************************************************************
//
//! \brief Display chinese with data code in text area
//!
//! \param row the row to display
//! \param col the column to display
//! \param pDataCode the data code
//! \param len the length to display
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Text_Display_Chinese(unsigned char row, unsigned char col,
        unsigned char *pDataCode, unsigned char len)
{
    int i, addr;
    for(i=0; i<len; i++)
    {
        addr = row*LCD_GRH_WID_NUM + col;
        T6963C_WriteDoublePara(addr, addr>>8, LCD_ADR_POS);
        //write top left
        T6963C_WriteOnePara(pDataCode[i], LCD_INC_WR);
        //write top right
        T6963C_WriteOnePara(pDataCode[i]+2, LCD_INC_WR);

        addr += LCD_GRH_WID_NUM;
        T6963C_WriteDoublePara(addr, addr>>8, LCD_ADR_POS);
        //write bottom left
        T6963C_WriteOnePara(pDataCode[i]+1, LCD_INC_WR);
        //write bottom right
        T6963C_WriteOnePara(pDataCode[i]+3, LCD_INC_WR);

        col+=2;
        if(col==LCD_GRH_WID_NUM)
        {
            col = 0;
            row+=2;
        }
    }
}

//*****************************************************************************
//
//! \brief Display chinese in graphic area
//!
//! \param row the row to display
//! \param col the column to display
//! \param pDataCode the data code
//! \param len the length to display
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Gph_Display_Chinese(unsigned char row, unsigned char col,
        unsigned char data[][32], unsigned char len)
{
    int i, j, addr;
    for(i=0; i<len; i++)
    {
        addr = row*16*LCD_GRH_WID_NUM + col*2 + GRSTART;
        for(j=0; j<32; j+=2)
        {
			T6963C_WriteDoublePara(addr, addr>>8, LCD_ADR_POS);
			T6963C_WriteOnePara(data[i][j], LCD_INC_WR);
			T6963C_WriteOnePara(data[i][j+1], LCD_INC_WR);

			addr += LCD_GRH_WID_NUM;

        }
		col++;
		if(col==(LCD_GRH_WID_NUM/2))
		{
			col = 0;
			row++;
		}
    }
}

//*****************************************************************************
//
//! \brief Display a bmp
//!
//! \param data data of the bmp
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Gph_Display_BMP(unsigned char data[])
{
	int i;
    T6963C_WriteDoublePara(GRSTART, GRSTART>>8, LCD_ADR_POS);
    for(i=0; i<64*16; i++)
    {
			T6963C_WriteOnePara(data[i], LCD_INC_WR);
    }
    T6963C_WriteDoublePara(0, 0, LCD_ADR_POS);
}

//*****************************************************************************
//
//! \brief Display a dot
//!
//! \param row the row to display,0~63
//! \param col the column to display,0~127
//! \param Mode 1:set, 0:clear
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Pixel(unsigned char row,unsigned char col,
		unsigned char Mode)
{
    unsigned int addr;
    unsigned char dat;
    addr=row*LCD_GRH_WID_NUM + col/8 + GRSTART;
    dat=LCD_BIT_OP+7-col%8;
    if(Mode) dat=dat|0x08;
    T6963C_WriteDoublePara(addr, addr>>8, LCD_ADR_POS);
    T6963C_WriteCMD(dat);
}

//*****************************************************************************
//
//! \brief Display a line
//!
//! \param y1 the column of dot1, 0~127
//! \param x1 the row of dot1, 0~63
//! \param y2 the column of dot2, 0~127
//! \param x2 the row of dot2, 0~63
//! \param Mode 1:set, 0:clear
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Line(unsigned char y1,unsigned char x1,
		unsigned char y2,unsigned char x2,  unsigned char Mode)
{
	unsigned char x,y;
	float k,b;
	if( abs(y1-y2) <= abs(x1-x2) ) // |k|<=1
	{
		k=((float)y2-y1) / ((float)x2-x1) ;
		b=y1-k*x1;
		if( x1 <= x2 )
		{
			for(x=x1;x<=x2;x++)
			{
				y=(unsigned char)(k*x+b);
				T6963C_Pixel(x, y, Mode);
			}
		}
		else
		{
			for(x=x2;x<=x1;x++)
			{
				y=(unsigned char)(k*x+b);
				T6963C_Pixel(x, y, Mode);
			}
		}
	}
	else // abs(y1-y2) > abs(x1-x2) |K|>1
	{
		k=((float)x2-x1) / ((float)y2-y1) ;
		b=x1-k*y1;
		if( y1 <= y2 )
		{
			for(y=y1;y<=y2;y++)
			{
				x=(unsigned char)(k*y+b);
				T6963C_Pixel( x , y,Mode );
			}
		}
		else
		{
			for(y=y2;y<=y1;y++)
			{
				x=(unsigned char)(k*y+b);
				T6963C_Pixel( x , y,Mode );
			}
		}
	}
}

//*****************************************************************************
//
//! \brief Clear the 8KB RAM of T6963C LCD.
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Clear_RAM()
{
	int i;
	T6963C_WriteDoublePara(0, 0, LCD_ADR_POS);
    T6963C_WriteCMD(LCD_AUT_WR); // set auto write mode
    for(i=0;i<DISRAM_SIZE;i++)                   // clear 8KB RAM
    {
        T6963C_AutoWriteData(0x00);       // write 0
    }
    T6963C_WriteCMD( LCD_AUT_OVR);  // stop auto write
    T6963C_WriteDoublePara(0, 0, LCD_ADR_POS);
}

void T6963C_Graphic_Clear_CN_Word(unsigned char row, unsigned char col)
{
	T6963C_Gph_Display_Chinese(row, col,gph_clr_byte, 0);
}

//*****************************************************************************
//
//! \brief Reset T6963C LCD.
//!
//! \return None.
//
//*****************************************************************************
void T6963C_Reset()
{
	GPIOPinWrite(LCD_DATA_PORT, LCD_RESET, 0);
	delay(10);
	GPIOPinWrite(LCD_DATA_PORT, LCD_RESET, 1);
}
