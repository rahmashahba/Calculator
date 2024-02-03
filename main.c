/*
 * main.c
 *
 *  Created on: Nov 18, 2023
 *      Author: rahma
 */

#include "STD_TYPES.h"
#include <util/delay.h>
#include "ErrType.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "calc.h"

#define size 100



void main(void)
{
	uint8 Localu8KeyPadKey,flag=0;
	uint8 Local_u8OP[size]={0};
	uint8  Local_u8Num[size]={0};
	uint8 Local_u8RES[size];
	uint8 arr_index=0;
	uint8 OP_index=0;
	uint8 i= 1,flagg=0;

	PORT_voidInit();
	CLCD_voidInit();

	while(1)
	{


		_delay_ms(600);
		CLCD_voidSendCmd(1);
		CLCD_u8SendString("Calculator Ready");
		_delay_ms(600);
		CLCD_voidSendCmd(1);
		//Local_u8Num1
		while (flag != 1)
		{
			do
			{
				Localu8KeyPadKey= KPD_u8GetPressedKey();
			}
			while(Localu8KeyPadKey == 0xff);

			// Check if the key is a valid digit
			if ((Localu8KeyPadKey >= 0) &&( Localu8KeyPadKey <= 9))
			{
				CLCD_voidSendNumber(Localu8KeyPadKey);
				Local_u8Num[arr_index] =Localu8KeyPadKey;
				arr_index++;
				flagg=0;

			}
			else if (Localu8KeyPadKey == '+' || Localu8KeyPadKey == '-' || Localu8KeyPadKey == '/'|| Localu8KeyPadKey == 'x')
			{


				flagg++;
				Local_u8RES[i]=scan(Local_u8Num);
				arr_index=0;
				Local_u8OP[i]=Localu8KeyPadKey;
				CLCD_voidSendData(Local_u8OP[i]);
				if(flagg==1)
				{
					i++;
				}



			}
			else if( Localu8KeyPadKey == '=')
			{
				Local_u8OP[i]=Localu8KeyPadKey;
				CLCD_voidSendData(Local_u8OP[i]);
				Local_u8RES[i]=scan(Local_u8Num);
				//CLCD_voidSendData(Localu8KeyPadKey);
				Local_u8RES[4]	='=';
				Calculator(Local_u8RES[1],Local_u8RES[2],Local_u8RES[3], Local_u8RES[4],Local_u8OP[1],Local_u8OP[2]);
				_delay_ms(400);
				i=1;
				arr_index=0;
			}
			else
			{
				CLCD_voidSendCmd(1);
				flag=0;
			}
		}
	}
}
