/*

 *
 *  Created on: Nov 23, 2023
 *      Author: rahma
 */
#include "STD_TYPES.h"
#include <util/delay.h>


uint8 Calculator(uint8 Local_u8Num1, uint8 Local_u8Num2,uint8 Local_u8Num3 ,uint8 Local_u8RES , uint8 Local_u8OP , uint8 Local_u8OP1)
{
	uint8 Local_u8Num ;
	if(Local_u8RES == '=')
	{

		switch (Local_u8OP)
		{


		case '+':
			Local_u8Num = Local_u8Num1 + Local_u8Num2;
			break;
		case '-':
			Local_u8Num = Local_u8Num1 - Local_u8Num2;
			break;
		case 'x':
			Local_u8Num = Local_u8Num1 * Local_u8Num2;
			break;
		case '/':
			if((Local_u8Num1 ==0 )|| (Local_u8Num2==0))
			{
				CLCD_u8SendString("Infinity");
			}
			else if(Local_u8Num1 % Local_u8Num2 !=0)
			{
				CLCD_voidSendNumber(Local_u8Num1/Local_u8Num2);
				CLCD_voidSendData('.');
				CLCD_voidSendNumber(((Local_u8Num1%Local_u8Num2)*1000)/Local_u8Num2);
			}
			break;


		default:
			CLCD_voidGoToXY(1,4);
			CLCD_u8SendString("Error");
			CLCD_voidSendCmd(1);
			return 1; // Indicate error
		}
		switch (Local_u8OP1)
		{


		case '+':

			CLCD_voidSendNumber(Local_u8Num + Local_u8Num3 );
			break;
		case '-':
			//if(Local_u8Num3>Local_u8Num?(Local_u8Num2>Local_u8Num3? Local_u8Num2:Local_u8Num3):Local_u8Num)

			CLCD_voidSendNumber(Local_u8Num - Local_u8Num3);
			break;
		case 'x':


			CLCD_voidSendNumber(Local_u8Num * Local_u8Num3);
			break;
		case '/':
			if(Local_u8Num3==0)
			{
				CLCD_voidSendNumber(Local_u8Num);
			}


			if((Local_u8Num ==0 )|| (Local_u8Num3==0))
			{
				CLCD_u8SendString("Infinity");
			}
			else if(Local_u8Num % Local_u8Num3 !=0)
			{
				CLCD_voidSendNumber(Local_u8Num/Local_u8Num3);
				CLCD_voidSendData('.');
				CLCD_voidSendNumber(((Local_u8Num%Local_u8Num3)*1000)/Local_u8Num3);
			}
			else
				CLCD_voidSendNumber(Local_u8Num/ Local_u8Num3);
			break;
		case '=':

			CLCD_voidSendNumber(Local_u8Num);
			break;

		default:
			CLCD_voidGoToXY(1,4);
			CLCD_u8SendString("Error");
			CLCD_voidSendCmd(1);
			return 1; // Indicate error
		}
	}
	else if (Local_u8RES == 'C')
	{
		CLCD_u8SendString("CLR");
		_delay_ms(600);
		CLCD_voidSendCmd(1);
	}
	return 0;
}


uint8 u8arrClk[3],arr_index =10,arr_cal[10];

uint8 scan(uint8 arr[])
{

	return ((arr[0])*10)+(arr[1]);



}


void get_Num(uint8 dig)
{

	arr_cal[arr_index]*=10;
	arr_cal[arr_index]+=dig;
}



/*
		Local_u8RES[1]=scan(Local_u8Num);
		//operation0
		do
		{
			Localu8KeyPadKey= KPD_u8GetPressedKey();
		}
		while(Localu8KeyPadKey == 0xff);

		if((Localu8KeyPadKey=='-')||(Localu8KeyPadKey=='x')||(Localu8KeyPadKey=='/')||(Localu8KeyPadKey=='+'))
		{
			arr_index=0;
			flag=0;
			Local_u8OP[0]	=Localu8KeyPadKey;
			CLCD_voidSendData(Local_u8OP[0]);
		}


		//Local_u8Num2
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
			}
			else if (Localu8KeyPadKey == '+' || Localu8KeyPadKey == '-' || Localu8KeyPadKey == '/'|| Localu8KeyPadKey == 'C'|| Localu8KeyPadKey == '=' || Localu8KeyPadKey == 'x')
			{

				flag = 1; // Set the flag to indicate an operator is entered
			}
		}
		Local_u8RES[2]=scan(Local_u8Num);

		//operation1
		do
		{

			Localu8KeyPadKey= KPD_u8GetPressedKey();
		}
		while(Localu8KeyPadKey == 0xff);
		if((Localu8KeyPadKey=='-')||(Localu8KeyPadKey=='x')||(Localu8KeyPadKey=='/')||(Localu8KeyPadKey=='+'))
		{
			arr_index=0;
			flag=0;
			Local_u8OP[2]	=Localu8KeyPadKey;
			CLCD_voidSendData(Local_u8OP[2]);
		}
		else if(Localu8KeyPadKey=='=')
		{
			Local_u8OP[2]	=Localu8KeyPadKey;
			CLCD_voidSendData(Local_u8OP[2]);
			Local_u8RES[4]	=Localu8KeyPadKey;
			//CLCD_voidSendData(Local_u8RES[4]);
			Calculator(Local_u8RES[1],Local_u8RES[2],Local_u8RES[3], Local_u8RES[4],Local_u8OP[1],Local_u8OP[2]);
			_delay_ms(400);
		}
		else
		{
			CLCD_voidSendCmd(1);
		}

		//Local_u8Num3
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
			}
			else if (Localu8KeyPadKey == '+' || Localu8KeyPadKey == '-' || Localu8KeyPadKey == '/'|| Localu8KeyPadKey == 'C'|| Localu8KeyPadKey == '=' || Localu8KeyPadKey == 'x')
			{
				flag = 1; // Set the flag to indicate an operator is entered
			}
		}
		Local_u8RES[3]=scan(Local_u8Num);


		//equal
		do
		{
			Localu8KeyPadKey= KPD_u8GetPressedKey();

		}
		while(Localu8KeyPadKey == 0xff);
		if(Localu8KeyPadKey=='C')
		{
			CLCD_u8SendString("CLR");
			CLCD_voidSendCmd(1);

		}
		else if((Localu8KeyPadKey=='='))
		{
			Local_u8RES[4]	=Localu8KeyPadKey;
			CLCD_voidSendData(Local_u8RES[4]);
		}
		Calculator(Local_u8RES[1],Local_u8RES[2],Local_u8RES[3], Local_u8RES[4],Local_u8OP[1],Local_u8OP[2]);
		_delay_ms(1000);
	}

}
 */


