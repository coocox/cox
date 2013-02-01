//*****************************************************************************
//
//! \file T6963C.h
//! \brief Prototypes for the T6963C Driver.
//! \version V2.1.1.0
//! \date 1/15/2013
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
//!
//*****************************************************************************
#ifndef __T6963C_H__
#define __T6963C_H__
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
//! \addtogroup Displays
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup Text_Displays
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup T6963C
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup T6963C_Driver_Single T6963C Single Driver
//! @{ 
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup T6963C_Hardware_Config T6963C Hardware Config
//! @{
//
//*****************************************************************************

//
//! Define Data Pins and Command Pins
//

#define LCD_DATA_PORT   xGPIO_PORTD_BASE

#define LCD_D0         xGPIO_PIN_0
#define LCD_D1         xGPIO_PIN_1
#define LCD_D2         xGPIO_PIN_2
#define LCD_D3         xGPIO_PIN_3
#define LCD_D4         xGPIO_PIN_4
#define LCD_D5         xGPIO_PIN_5
#define LCD_D6         xGPIO_PIN_6
#define LCD_D7         xGPIO_PIN_7

#define LCD_FS         xGPIO_PIN_8
#define LCD_WR         xGPIO_PIN_9
#define LCD_RD         xGPIO_PIN_10
#define LCD_CS         xGPIO_PIN_11
#define LCD_CD         xGPIO_PIN_12
#define LCD_RESET         xGPIO_PIN_13

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CoX_T6963C_Status CoX T6963C Status
//! @{
//
//*****************************************************************************

//
//! Define Status
//
#define STATUS_RW    0x03
#define STATUS_AUTO_R    0x04
#define STATUS_AUTO_W    0x08

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CoX_T6963C_Status CoX T6963C Status
//! @{
//
//*****************************************************************************

//
//! Allocation of 8K RAM
//
#define DISRAM_SIZE   0x1FFF          //size of RAM: 8K
#define TXTSTART        0x0000         //start address of text area: 2K
#define GRSTART          0x0800         //start address of graphic area: 4K
#define CGRAMSTART 0x1800         //start address of CGRAM: 2K

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CoX_T6963C_Commands CoX T6963C Commands
//! @{
//
//*****************************************************************************

//
//! T6963C Commands
//

//
//! Address pointer
//
#define  LCD_CUR_POS  0x21      /* set the position of cursor */
#define  LCD_CGR_POS  0x22      /* set the offset address of CGRAM */
#define  LCD_ADR_POS  0x24      /* set address pointer */

//
//! Display area
//
#define  LCD_TXT_STP  0x40      /* set text area address */
#define  LCD_TXT_WID  0x41      /* set the width of text area */
#define  LCD_GRH_STP  0x42      /* set graphic area address */
#define  LCD_GRH_WID  0x43      /* set the width of graphic area */

//
//! Display mode
//
#define  LCD_MOD_OR         0x80     /* display mode£ºor */
#define  LCD_MOD_XOR      0x81      /* display mode£ºxor */
#define  LCD_MOD_AND     0x82      /* display mode£ºand */
#define  LCD_MOD_TCH      0x83      /* display mode£ºtext attribute */

//
//! Display status
//
#define  LCD_DIS_SW      0x90      /* display switch£ºD0=1/0£¬cursor blink use/no-blink */
              /*  display switch£º D1=1/0£¬cursor /no-cursor */
              /*  display switch£º D2=1/0£¬text display/not */
              /*  display switch£º D3=1/0£¬graphic display/not */

//
//! Cursor style
//
#define  LCD_CUR_SHP  0xA0      /* cursor set£º0xA0-0xA7, the rows of cursor */

//
//! Auto read/write
//
#define  LCD_AUT_WR      0xB0      /* auto write */
#define  LCD_AUT_RD      0xB1      /* auto read */
#define  LCD_AUT_OVR  0xB2      /* stop auto write/read */

//
//! Data read/write once
//
#define  LCD_INC_WR      0xC0     /* write data once£¬address+1 */
#define  LCD_INC_RD      0xC1      /* read data once£¬address+1 */
#define  LCD_DEC_WR   0xC2       /* write data once£¬address-1 */
#define  LCD_DEC_RD   0xC3        /* read data once£¬address-1 */
#define  LCD_NOC_WR   0xC4      /* write data once£¬address not changed */
#define  LCD_NOC_RD   0xC5       /* read data once£¬address not changed */

//
//!  read screen, one byte
//
#define  LCD_SCN_RD   0xE0

//
//!  copy screen, one line
//
#define  LCD_SCN_CP   0xE8


//
//! bit operation£ºD0-D2--define D0-D7 bit£¬D3--1 set bit£¬0 clear bit
//
#define  LCD_BIT_OP   0xF0

//
//! the width to display
//
#define  LCD_GRH_WID_NUM	16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
// 
//! \addtogroup CoX_T6963C_Exported_APIs CoX T6963C Exported APIs
//! @{
//
//*****************************************************************************
extern void T6963C_Init(void);
extern void T6963C_WriteData(unsigned char data);
extern void T6963C_WriteCMD(unsigned char cmd);
extern void T6963C_WriteOnePara(unsigned char data,
							unsigned char cmd);
extern void T6963C_WriteDoublePara(unsigned char data1,
				unsigned char data2, unsigned char cmd);
extern void T6963C_StatusCheck(unsigned char mode);
extern void T6963C_ShowString(unsigned char row, unsigned char col,
									unsigned char *pDataCode, unsigned char len);
extern void T6963C_Clear_RAM(void);
extern void T6963C_CGRAM(void);
extern void T6963C_Reset(void);
extern void T6963C_Text_Display_Chinese(unsigned char row, unsigned char col,
        unsigned char *pDataCode, unsigned char len);
extern void T6963C_Gph_Display_Chinese(unsigned char row, unsigned char col,
        unsigned char data[][32], unsigned char len);
extern void T6963C_Line(unsigned char y1,unsigned char x1,
		unsigned char y2,unsigned char x2,  unsigned char Mode);
extern void T6963C_Pixel(unsigned char row,unsigned char col,
		unsigned char Mode);
extern void T6963C_Gph_Display_BMP(unsigned char data[]);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__T6963C_H__
