#include "StopWatch.h"

static  u8 count_Orig = 10 ;
static  u8 count ;
static	u8 status_flag   = 0 ;
static	u8 status_flag_2 = 0 ;
static	u8 Butt_2_flag   = 0 ;

void StopWatch_Init(void)
{
	DIO_Init();
	count = count_Orig ;	
}

void StopWatch_Prog(void)
{
	if(count > count_Orig)
	{
		count = count_Orig ;
		//
		DIO_WritePin(Buzzer,HIGH);
		while(DIO_ReadPin(But2));
		DIO_WritePin(Buzzer,LOW);
	}
	segmant_Display_BCD (count) ;
	//hena ana mgz2 l delay 1000 sec
	for(u16 i = 0 ; i < 100 ; i++)
	{
		//b3mel check 3ala button 1
		if(!DIO_ReadPin(But1))
		{
			status_flag  = status_flag ^ 1 ;
			while(!DIO_ReadPin(But1));
			if(status_flag)
			{
				while(DIO_ReadPin(But1))
				{
					if(!DIO_ReadPin(But2))
					{
						count = count_Orig ;
						segmant_Display_BCD (count) ;
						while(!DIO_ReadPin(But2));
					}
					if(!DIO_ReadPin(But3))
					{
						break;
						while(!DIO_ReadPin(But3));
					}
				}
			}
		}
		//check 3ala button 2
		if(!DIO_ReadPin(But2))
		{
			while(!DIO_ReadPin(But2));
			if(Butt_2_flag == 0)
			{
				count = count_Orig ;
				segmant_Display_BCD (count) ;
				while(DIO_ReadPin(But1));
				status_flag = 1 ;
				Butt_2_flag = 1 ;
			}
		}
		else
		{
			Butt_2_flag = 0 ;
		}
		//b3mel check 3ala button 3
		if(!DIO_ReadPin(But3))
		{
			status_flag_2  = status_flag_2 ^ 1 ;
			while(!DIO_ReadPin(But3));
			if(status_flag_2)
			{
				while(status_flag_2)
				{
					segmant_Display_BCD (count_Orig) ;

					if(!DIO_ReadPin(But1))
					{
						count_Orig ++ ;
						_delay_ms(400);
					}
					if(!DIO_ReadPin(But2))
					{
						count_Orig -- ;
						_delay_ms(400);
					}
					if(count_Orig > 99)
					{
						count_Orig = 99 ;
					}
					if(!DIO_ReadPin(But3))
					{
						status_flag_2  = status_flag_2 ^ 1 ;
						while(!DIO_ReadPin(But3));
					}
				}
				count = count_Orig ;
			}
		}
		_delay_ms(10);
	}
	count -- ;
}