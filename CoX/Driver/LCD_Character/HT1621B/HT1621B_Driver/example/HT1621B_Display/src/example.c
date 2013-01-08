#include"HT1621B.h"

void HT1621B_test( void )
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
