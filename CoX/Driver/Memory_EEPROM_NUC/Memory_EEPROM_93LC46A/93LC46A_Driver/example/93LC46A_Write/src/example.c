#include"93LC46A.h"

void test( void )
{
	eep_93LC46A_Init();
		char data_w[3] = {26, 37, 99};
		char data_r[3] = {0, 0, 0 };
		char addr[3] = {16, 45, 11};
		int  result=1;
		int i;
		for(i=0; i<3; i++)
		{
			eep_93LC46A_Write(data_w[i], addr[i]);
		}

		for(i=0; i<3; i++)
		{
			eep_93LC46A_Read(&data_r[i], addr[i]);
		}

		for(i=0; i<3; i++)
		{
			if(data_w[i] != data_r[i])
			{
				result = 0;
				break;
			}
		}

		//erase all
		eep_93LC46A_Cmd(_93LC46A_EraseAll);
		eep_93LC46A_Read(&data_r[0], addr[0]);

		//erase
		eep_93LC46A_Write(data_w[0], addr[0]);
		eep_93LC46A_Read(&data_r[0], addr[0]);
		eep_93LC46A_Erase(addr[0]);
		eep_93LC46A_Read(&data_r[0], addr[0]);

		//write all
		eep_93LC46A_Write(56, -1);

		for(i=0; i<3; i++)
		{
			eep_93LC46A_Read(&data_r[i], addr[i]);
		}
}
