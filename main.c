/*
 * main.c
 *
 *  Created on: Jan 13, 2021
 *      Author: ZAS
 */

/*lib layer*/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include <util/delay.h>
/*MCAL layer*/
#include "DIO_interface.h"

/*HAL layer*/
#include"LCD_interface.h"
#include"KPD_interface.h"



int main(void)
{
	u8 button =KPD_U8_NOT_PRESSED,operation;
	u32 op1=0,op2=0;
	DIO_voidInit();
	LCD_voidInit();
    u8 flag =0 ;


	while(1)/*get op1*/
	{

		if(button == KPD_U8_NOT_PRESSED)
		{
			KPD_u8GetSwitch(&button);
			while((button !=KPD_U8_NOT_PRESSED))
			{
				if((button != '+')&&(button != '-')&&(button != '*')&&(button != '/')&&(button != '%')&&(button != '='))
				{
				  op1 = (op1 *10) + button ;
				  LCD_voidSendChar(button);
				  KPD_u8GetSwitch(&button);
				}
				else
				{
			     operation = button ;
			     LCD_voidSendChar(button);
		    	 button    = KPD_U8_NOT_PRESSED;
		    	 flag =1;
			     break;
				}
		     }
			if(flag)
			{
				flag =0 ;
				break;
			}
	      }
	 }

	while(1)/*get op2*/
	{

		if(button == KPD_U8_NOT_PRESSED)
		{
			KPD_u8GetSwitch(&button);
			while((button !=KPD_U8_NOT_PRESSED))
			{
				if(button != '=')
				{
				  op2 = (op2 *10) + button ;
				  LCD_voidSendChar(button);
				  KPD_u8GetSwitch(&button);
				}
				else
				{

			     LCD_voidSendChar(button);
		    	 button    = KPD_U8_NOT_PRESSED;
		    	 flag =1;
			     break;
				}
		     }
			if(flag)
			{
				flag =0 ;
				break;
			}
	      }
	 }

	switch(operation)
	{
	case '+' :

		LCD_VidWriteNum(op1 +op2);
	break;
	case '-' :
		if(op1>op2)
		{
		LCD_VidWriteNum(op1 - op2);
		}
		else
		{
			LCD_VidWriteNum(op2 - op1);
		}

	break;
	case '*' :
		LCD_VidWriteNum(op1 * op2);
	break;
	case '/' :
		LCD_VidWriteNum(op1 / op2);
	break;
	case '%' :
		LCD_VidWriteNum(op1 % op2);
	break;



 }
    return 0;

}
