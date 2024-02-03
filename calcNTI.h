/*
 * CALcNTI.h
 *
 *  Created on: Nov 24, 2023
 *      Author: rahma
 */


#include "STD_TYPES.h"
#include <util/delay.h>




#include"DIO_Interface.h"
#include"CLCD_Interface.h"
#include"KPD_interface.h"


#include<util/delay.h>

/************************Preprocessor********************/
#define arr_size 100

/************************Global Variables****************/
uint16 arr_cal[arr_size]={0};
uint8 arr_index=0;
uint8 key=0;
uint8 flagResult=0;
uint8 rowNum=0;
uint8 colNum=0;

/********************************************************
 *
 * 				Function Definitions
 *
 ********************************************************/
/********************************************************
 *
 * 				Cal_Init Function
 *
 ********************************************************/
/*void Cal_Init(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
}
 */
/********************************************************
 *
 * 				ShiftArray Function
 *
 ********************************************************/
void ShiftArray(uint8 index)
{
	for(uint8 i=index;i<=arr_index;i++)
	{
		arr_cal[i]=arr_cal[i+2];
	}
	arr_index-=2;
}
/********************************************************
 *
 * 				Cal_Result Function
 *
 ********************************************************/
void Cal_Result(void)
{
	/*******Multiplication and Division operators********/
	for(uint8 i=0;i<=arr_index;i++)
	{
		if(arr_cal[i]=='*')
		{
			arr_cal[i-1] *= arr_cal[i+1];
			ShiftArray(i);
			i=0;
		}
		else if(arr_cal[i]=='/')
		{
			arr_cal[i-1] /= arr_cal[i+1];
			ShiftArray(i);
			i=0;
		}
	}
	/***********Addition and subtraction*****************/
	for(uint8 i=0;i<=arr_index;i++)
	{
		if(arr_cal[i]=='+')
		{
			arr_cal[i-1]+=arr_cal[i+1];
			ShiftArray(i);
			i=0;
		}
		else if(arr_cal[i]=='-')
		{
			/*******To handle the sign negative********/
			if(arr_cal[i-1]>=arr_cal[i+1])
			{
				arr_cal[i-1]-=arr_cal[i+1];
			}
			else
			{
				arr_cal[i-1]=arr_cal[i+1]-arr_cal[i-1];
			}
			ShiftArray(i);
			i=0;
		}
	}
}

/********************************************************
 *
 * 				DisplayResult Function
 *
 ********************************************************/
void DisplayResult(void)
{
	rowNum=0;
	colNum=0;

	CLCD_voidSendCmd(1);
	CLCD_voidGoToXY(rowNum, colNum);

	CLCD_u8SendString("Result = ");
	CLCD_voidGoToXY(0, 9);

	/******Result will display in 7 digits******/
	//7
	CLCD_voidSendData((arr_cal[arr_index]/1000000)+'0');
	//6
	CLCD_voidSendData(((arr_cal[arr_index]%1000000)/100000)+'0');
	//5
	CLCD_voidSendData(((arr_cal[arr_index]%100000)/10000)+'0');
	//4
	CLCD_voidSendData(((arr_cal[arr_index]%10000)/1000)+'0');
	//3
	CLCD_voidSendData(((arr_cal[arr_index]%1000)/100)+'0');
	//2
	CLCD_voidSendData(((arr_cal[arr_index]%100)/10)+'0');
	//1
	CLCD_voidSendData(((arr_cal[arr_index]%10)/1)+'0');

	flagResult=1;
}

/********************************************************
 *
 * 				get_Num Function
 *
 ********************************************************/
void get_Num(uint8 dig)
{
	dig-='0';
	arr_cal[arr_index]*=10;
	arr_cal[arr_index]+=dig;
}


/********************************************************
 *
 * 				CheckNum Function
 *
 ********************************************************/
void CheckNum(uint8 num)
{
	if((num!='*') && (num!='/') && (num!='+') && (num!='-'))
	{
		/***this means that the input is a number not an operator and store in in the array***/
		get_Num(num);
	}
	else
	{
		/****store the taken operator in the array****/
		arr_index++;
		arr_cal[arr_index]=num;
		arr_index++;
	}
}


/********************************************************
 *
 * 				Calculator Function
 *
 ********************************************************/
void Calculator(void)
{
	do
	{
		key= KPD_u8GetPressedKey();

	}
	while(key == 0xff);

	if(key==0xff)
	{
		if(key=='=')
		{
			Cal_Result();
			DisplayResult();
		}
		if(key!='=')
		{
			/***when this flag =1 ,this means that the result was displayed on the LCD***/
			if(flagResult==1)
			{
				CLCD_voidSendCmd(1);
				arr_index=0;
				flagResult=0;
				for(uint8 i=0;i<arr_size;i++)
				{
					arr_cal[i]=0;
				}
			}
			CheckNum(key);
			CLCD_voidGoToXY(rowNum, colNum);
			CLCD_voidSendData(key);
			colNum++;
			if(colNum==21)
			{
				rowNum++;
			}


		}
	}
}
