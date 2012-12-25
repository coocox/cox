#include"lcd_code.h"

unsigned char u8Digital[]={0xEB, 0x60, 0xC7, 0xE5, 0x6C,/*0-4*/
	 									 0xAD, 0xAF, 0xE0, 0xEF, 0xED,/*5-9*/
	 									 0x67, 0x8F, 0x8A, 0x8E, 0xCE,/*d,E,T,F,P*/
	 									 0x27, 0x6B, 0xEE/*O,U,R*/};

unsigned char u8DigLit[] = {0xD7, 0x06, 0xE3, 0xA7, 0x36,/*0-4*/
	 									 0xB5, 0xF5, 0x07, 0xF7, 0xB7};//,/*5-9*/
	 									 //0x67, 0x8F, 0x8A, 0x8E, 0xCE,/*d,E,T,F,P*/
	 									 //0x27, 0x6B, 0xEE/*O,U,R*/};

//display buffer, 16 bytes£¬128 bits
unsigned int lcd_buffer[8]={0,0,0,0,0,0,0,0};

void ht1621b_delay(int iDelayTime)
{
  int i;
  for(i=0; i<iDelayTime; i++);
}

//*****************************************************************************
//
//! \brief Send a command to HT1621B. You maybe need to add delay
//! between operations.
//!
//! \param command command to send
//!
//! \return None.
//
//*****************************************************************************
void send_lcd_command(unsigned char command)
{
     unsigned short int i =0;
     CS_LOW

    WR_LOW          //PRESENT 100 COMMAND CODE
    DATA_HIGH
    WR_HIGH

    WR_LOW
    DATA_LOW
    WR_HIGH

    WR_LOW
    WR_HIGH

    for (i =0;i<=7;i++)
     {
         WR_LOW
         if ((command & 0x80) !=0) DATA_HIGH
          else DATA_LOW
         WR_HIGH
         command = command << 1;
     }

    WR_LOW
    WR_HIGH

    CS_HIGH
}

//*****************************************************************************
//
//! \brief Send a data to HT1621B. You maybe need to add delay
//! between operations.
//!
//! \param address address to write
//! \param data data to send
//!
//! \return None.
//
//*****************************************************************************
void send_lcd_data(unsigned short int address,unsigned short int data)
{
	unsigned short int i =0;

	CS_LOW;
  
    WR_LOW;          //PRESENT 101 DATA CODE
    DATA_HIGH;
    WR_HIGH;

    WR_LOW;
    DATA_LOW;
    WR_HIGH;

    WR_LOW;
    DATA_HIGH;
    WR_HIGH;

    address = address << 2;
    for ( i =0;i<=5;i++)
     {
         WR_LOW;
         if ((address & 0x80) !=0) DATA_HIGH
          else DATA_LOW
         WR_HIGH;
         address = address << 1;
     }

     for (i =0;i<=3;i++)
     {
         WR_LOW;
         if ((data & 0x01) !=0) DATA_HIGH
          else DATA_LOW
         WR_HIGH;
         data = data >> 1;
     }

    CS_HIGH;
}

//*****************************************************************************
//
//! \brief Send display buffer to HT1621B. You maybe need to add delay
//! between operations.
//!
//! \return None.
//
//*****************************************************************************
void flood_lcd_data(void)
{
	unsigned short int i =0;
	unsigned short int j=0;
	unsigned int temp_data;
    CS_LOW;
  
    WR_LOW;          //PRESENT 101 DATA CODE
    DATA_HIGH;
    WR_HIGH;

    WR_LOW;
    DATA_LOW;
    WR_HIGH;

    WR_LOW;
    DATA_HIGH;
    WR_HIGH;

    for (i =0;i<=5;i++)
    {
         WR_LOW;
         DATA_LOW;
         WR_HIGH;
     }

    for (i =0;i<=7;i++)
    {
        temp_data = lcd_buffer[i];
        for (j=0;j<=15;j++)
        {
             WR_LOW;
             if ((temp_data & 0x01) !=0) DATA_HIGH
             else DATA_LOW
             WR_HIGH;
             temp_data = temp_data >> 1;
        }
    }

    CS_HIGH;
}

//*****************************************************************************
//
//! \brief Initialize HT1621B.
//!
//! \return None.
//
//*****************************************************************************
void lcd_init(void)
{
    xGPIODirModeSet(LCDPORT, DATA|CS|WR, xGPIO_DIR_MODE_OUT);

	send_lcd_command(0x28); //1/2bias£¬4comm
	send_lcd_command(0x03); //Open INTOSC
	send_lcd_command(0x01); //Enable Display
}

//*****************************************************************************
//
//! \brief Write a symbol to HT1621B.
//!
//! \param name name of the symbol, like _lcd_BUSY; or an Integer of 0~127.
//! \param display 1:display; 0:clear.
//!
//! \return None.
//
//*****************************************************************************
void lcd_char(unsigned short int name,unsigned short int display)
{
    unsigned short int i,j;
    i= name/16;
    j= name%16;
    if (display == 1) lcd_buffer[i] |= 1<<j;
    else lcd_buffer[i] &= ~(1<<j);
    flood_lcd_data();
}

//*****************************************************************************
//
//! \brief Clear HT1621B and display buffer.
//!
//! \return None.
//
//*****************************************************************************
void lcd_clr()
{
    int i=0;
    for (i=0; i<=7;i++) lcd_buffer[i]=0;
    flood_lcd_data();
}

//*****************************************************************************
//
//! \brief Write the display buffer.
//!
//! \return None.
//
//*****************************************************************************
void Write_lcd_buffer(unsigned short int number,unsigned short int position)
{
	//number position and index of buffer
    int iSpace = 0;// number of space£¬for 0-5
    int iIndex =0;// index of lcd_buffer
	int iOffset=0;//offset of lcd_buffer
	int iTemp;
	unsigned char *pDigCode;
  
    if(position<=5)
    {
    	//there are four bits between every two bits
    	iSpace = position/2;
  	    iSpace *= 4;
  	  //8 bits for 1 number starting from the eighth bit
        iTemp = 8*position + 8 + iSpace;
  		pDigCode = u8Digital;
    }
    else
    {
        iTemp = 8*(position-6) + 92;//(80+12)
  		pDigCode = u8DigLit;
    }

    iIndex  = iTemp/16;
    iOffset = iTemp%16;
    if(iOffset == 12)
    {
        lcd_buffer[iIndex]  |= ((pDigCode[number]&0x0F)<<12);
        lcd_buffer[iIndex+1]  |= ((pDigCode[number]&0xF0)>>4);
    }
    else
    {
        lcd_buffer[iIndex]  |= (pDigCode[number]<<iOffset);
    }
}

//*****************************************************************************
//
//! \brief Write a number to HT1621B.
//!
//! \param number number to write, 0~9.
//! \param position position of number, 0~5 in big size, 6~9 in little size.
//! \param display 1:display; 0:clear.
//!
//! \return None.
//
//*****************************************************************************
void lcd_number(unsigned short int number,unsigned short int position,
		unsigned short int display)
{

    switch (position)
    {
    case 0:
       {
           if (display == 0) lcd_buffer[0] &= 0x10ff;
          else
          {
              lcd_buffer[0] &= 0x10ff;
              Write_lcd_buffer(number, position);
          }
         break;
       }
    case 1:
     {
       if (display == 0) lcd_buffer[1] &= 0xff10;
       else
       {
           lcd_buffer[1] &= 0xff10;
           Write_lcd_buffer(number, position);
       }
       break;
     }
  case 2:
      lcd_buffer[1] &= 0x0fff;
      lcd_buffer[2] &= 0xfff1;

      if (display == 0) break;
      else
     {
    		Write_lcd_buffer(number, position);
     }
     break;
  case 3:
     lcd_buffer[2] &= 0xF10F;
     if (display == 0) break;
     else 
     {
    		Write_lcd_buffer(number, position);
     }
     break;
  case 4:
     lcd_buffer[3] &= 0xFF10;
     if (display == 0) break;
     else
     {
     		Write_lcd_buffer(number, position);
     }
     break;
  case 5:
     lcd_buffer[3] &= 0x10FF;
     if (display == 0) break;
     else
     {
    		Write_lcd_buffer(number, position); 
     }
     break;
  case 6:
      lcd_buffer[5] &= 0x8fff;
      lcd_buffer[6] &= 0xfff0;

      if (display == 0) break;

     else
     {
         Write_lcd_buffer(number, position);
     }
     break;
  case 7:
     lcd_buffer[6] &= 0xF08F;
     if (display == 0) break;
     else
     {
    		Write_lcd_buffer(number, position);
     }
     break;
  case 8:
      lcd_buffer[6] &= 0x8fff;
      lcd_buffer[7] &= 0xfff0;

      if (display == 0) break;
     else
     {
      		Write_lcd_buffer(number, position);
     }
     break;
  case 9:
     lcd_buffer[7] &= 0xF08F;
     if (display == 0) break;
     else
     {
    		Write_lcd_buffer(number, position);
     }
     break;
  }
  flood_lcd_data(); 
}

//*****************************************************************************
//
//! \brief Write number or string, 0~9, dETFPOUR, string is written in big
//! number row(the second row).
//!
//! \param *U8STR number or string to write.
//!
//! \return None.
//
//*****************************************************************************
int DisplayAllSTR( unsigned char *U8STR)
{
	int i,j;
	int iTemp;

	//dis little num
	j=0;
	for(i=9; i>=6; i--)
	{
		iTemp = U8STR[j++]; 
		if(iTemp>='0' && iTemp<='9' )
		{
			iTemp -= 0x30;
			lcd_number(iTemp,i,1);
		}
		else if(iTemp == ' ')
		{
			 lcd_number(iTemp,i,0);
		}
	}

	//dis big num
	for(i=0; i<=5; i++)
	{
		iTemp = U8STR[j++]; 
		if(iTemp>='0' && iTemp<='9' )
		{
			iTemp -= 0x30;
			lcd_number(iTemp,i,1);
		}
		else if(iTemp == ' ')
		{
			 lcd_number(iTemp,i,0);
		}
		else
		{
			switch(iTemp)
			{
		     	case 'd':
					iTemp = 10;
 					break;
				case 'E':
					iTemp = 11;
 					break;
				case 'T':
					iTemp = 12;
 					break;
				case 'F':
					iTemp = 13;
 					break;
				case 'P':
					iTemp = 14;
 					break;
				case 'O':
					iTemp = 15;
 					break;
				case 'U':
					iTemp = 16;
 					break;
				case 'R':
					iTemp = 17; 					
 					break;
				default:
				     continue;
			}
			lcd_number(iTemp,i,1);
		} 				
	}

	//discard the 2 :
	lcd_char(_lcd_COLON0, 0);
	lcd_char(_lcd_COLON1, 0);

	return 1;
}

//*****************************************************************************
//
//! \brief Write number in little number row(the top row), 0~99.
//!
//! \param number number  write.
//!
//! \return None.
//
//*****************************************************************************
int DisplayEFSNum( int number )
{
    int i;

    /*clean the display 6-9*/
    for(i=6; i<=9; i++)
    {
	    lcd_number(0,i,0);
    }

    if( number >= 100 )
    {
	    return -1;
    }
    else
    {
	    lcd_number(number/10,7,1);
	    lcd_number(number%10,6,1);
	    return 1;
    }
}

//*****************************************************************************
//
//! \brief Write power.
//!
//! \param IntPower Integer part, four bits.
//! \param FracPower Fractional  part, tow bits.
//!
//! \return None.
//
//*****************************************************************************
int Display5Power(int IntPower, int FracPower)
{
	int iPosition = 2;
	int iflag = 0;
	int iRadix = 1000;
	int i;
	int    iNumber = IntPower;
	
    //write decimal point
	lcd_char(_lcd_DOT3,1);

	  //clear colon
	  lcd_char(_lcd_COLON0,0);
	  lcd_char(_lcd_COLON1,0);
	  lcd_char(_lcd_COLON2,0);

	  //display the signal strength
	  lcd_char(_lcd_AT0,1);
	  lcd_char(_lcd_AT1,1);
	  lcd_char(_lcd_AT2,1);
	  lcd_char(_lcd_AT3,1);

	  //write w
	  lcd_char(_lcd_W,1);

	  //display battery
	  lcd_char(_lcd_BAT,1);

	  //display 01 in little number row
	  DisplayEFSNum(01);
	  
	//clear big size number row
	for(i=0; i<5; i++)
	{
	    lcd_number(0,i,0);
	}

	if(iNumber > 10000)
	{
		return -1;
	}
	else
	{
		if(iNumber > 1000)
		{
			iPosition = 0;//2;
		}
		else if(iNumber > 100)
		{
			iPosition = 1;//3;
		}
		else if(iNumber > 10)
		{
			iPosition = 2;//4;
		}
		else
		{
			iPosition = 3;//5;
		}
	}

	while( iNumber >= 0 )
	{
		if( iNumber >= iRadix)
		{
			lcd_number(iNumber/iRadix,iPosition++,1);
			iflag = 1;
		}
		else if(iflag)
		{
			lcd_number(iNumber/iRadix,iPosition++,1);
		}
		iNumber = iNumber%iRadix;
		iRadix  = iRadix/10;
		if(iRadix == 0)break;
	}

	lcd_number(FracPower/10,4,1);
	lcd_number(FracPower%10,5,1);
	return 1;
}

//*****************************************************************************
//
//! \brief Write char in first bit of big size number.
//!
//! \param cdORs char to write, d,S,C,E,T,F,P,O,U,R
//!
//! \return None.
//
//*****************************************************************************
int DisplaydORs( char cdORs )
{
	lcd_buffer[0] &= 0x10ff;
	if(cdORs == 'd')
	{
		lcd_buffer[0] |= 0x6700;
	}
	else if(cdORs == 'S')
	{
		lcd_buffer[0] |= 0xAD00;
	}
	else if(cdORs == 'C')
	{
		lcd_buffer[0] |= 0x8B00;
	}
	else if(cdORs == 'E')
	{
		lcd_buffer[0] |= 0xAD00;
	}
	else if(cdORs == 'T')
	{
		lcd_buffer[0] |= 0x8A00;
	}
	else if(cdORs == 'F')
	{
		lcd_buffer[0] |= 0x8E00;
	}
	else if(cdORs == 'P')
	{
		lcd_buffer[0] |= 0xCE00;
	}
	else if(cdORs == 'O')
	{
		lcd_buffer[0] |= 0xEB00;
	}
	else if(cdORs == 'U')
	{
		lcd_buffer[0] |= 0x6B00;
	}
	else if(cdORs == 'R')
	{
		lcd_buffer[0] |= 0xEE00;
	}
	flood_lcd_data();

	return 1;
}

//*****************************************************************************
//
//! \brief test for this driver.
//!
//! \return None.
//
//*****************************************************************************
void lcd_test( void )
{
	int i=0;
	unsigned int j =0;
	int k=0;
	  lcd_init();
	  flood_lcd_data();


	  //decimal point
	  /*lcd_char(_lcd_DOT0,1);
	  lcd_char(_lcd_DOT1,1);*/
	  lcd_char(_lcd_DOT2,1);
	  /*lcd_char(_lcd_DOT3,1);
	  lcd_char(_lcd_DOT4,1);*/

	  //colon
	  //lcd_char(_lcd_COLON0,1);
	  //lcd_char(_lcd_COLON1,1);

	  //signal strength
	  lcd_char(_lcd_AT0,1);
	  lcd_char(_lcd_AT1,1);
	  lcd_char(_lcd_AT2,1);
	  lcd_char(_lcd_AT3,1);

	  //w
	  lcd_char(_lcd_W,1);

	  //battery
	  lcd_char(_lcd_BAT,1);

	  //number
	  DisplayEFSNum(12);
	  //Display5Power(1234);

	  DisplaydORs('S');
	  DisplaydORs('d');
	  DisplaydORs('E');
	  DisplaydORs('F');
	  DisplaydORs('T');
	  DisplaydORs('P');
	  DisplaydORs('O');
	  DisplaydORs('U');
	  DisplaydORs('R');
	  DisplaydORs('C');
	 
	  //DisplaydORs(' ');

	  return;

	  while(1);

	  for( i=0;i<=9;i++)
	  {
		  lcd_number(9,i,1);
	  }

	  while(1)
	  {
	     for(i=0;i<=127;i++)
	     {
			lcd_char(i,1);
			for (j =0;j<=50000;j++);
	     }
	     for (i =0;i<=50000;i++)
	     {
	     	//for (j =0;j<=50000;j++);
	     }

	     lcd_clr();
	     for( k=0;k<=3;k++)
	     {
			for( i=0;i<=9;i++)
			{
			  lcd_number(i,0,1);
			  lcd_number(i,1,1);
			  lcd_number(i,2,1);
			  lcd_number(i,3,1);
			  lcd_number(i,4,1);
			  lcd_number(i,5,1);
			  lcd_number(i,6,1);
			  lcd_number(i,7,1);
			  lcd_number(i,8,1);
			  lcd_number(i,9,1);
			  for (j =0;j<=50000;j++);
			}
		}

	     for (i =0;i<=50000;i++)
	    	{
	    	  // 	for (j =0;j<=50000;j++);
	    	}
	     lcd_clr();

	}
}

