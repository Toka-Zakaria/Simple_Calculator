/**********************************************************************************
 * [FILE NAME]: app_file.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Aug 28, 2021
 *
 * [Description]: File to contain the functions of application of the Calculator
 ***********************************************************************************/
#include"app_file.h"

/***************************************************************************************************
 * [Function Name]: Calculator
 *
 * [Description]:  function to do the basic operations of the calculator
 *
 * [Args]:            sint32 first
 *                    sint32 second
 *                    uint8  op
 *
 *
 * [In]:            first: to carry the value of the first operand
 *                  second: to carry the value of the second operand
 *                  op: to carry the desired operation user want
 *
 * [Out]:           result: tio carry the result of the desired operation
 *
 * [Returns]:      signed integer of 64 byte to return the result of the operation
 ***************************************************************************************************/
sint64 Calculator(sint32 first, sint32 second, uint8 op )
{
	sint64 result;

	switch(op)
	{
	case '+':
		result = (first + second);
		break;

	case '-':
		result = (first - second);
		break;

	case'*':
		result = (first * second);
		break;

	case'%':

			result = (first % second);

		break;

	default:
		result = 0;
		break;
	}

	return result;
}
/***************************************************************************************************
 * [Function Name]: display_key
 *
 * [Description]:  function to display a passed digit on LCD, every digit by its type
 *
 * [Args]:         uint8 pressedKey
 *
 *
 * [In]:           pressedKey: to carry the value of the entered key to decide its type
 *                              and display it on LCD depending on its type
 *
 * [Out]:            NONE
 *
 * [Returns]:        NONE
 ***************************************************************************************************/
void display_key(uint8*pressedKey)
{
	if (( (*pressedKey) >= 0) && ( (*pressedKey) <= 9))
	{
		LCD_intgerToString( (*pressedKey) );
	}
	else
	{
		LCD_displayCharacter( (*pressedKey) );
	}
}
/***************************************************************************************************
 * [Function Name]: convertArrayToNumber
 *
 * [Description]:  function to convert the passed array to it to a number
 *                 considering the first element in the array has the most exponent
 *                 and the last element in the array has the least exponent
 *
 * [Args]:            uint8*ptr
 *                    uint8 size
 *
 *
 * [In]:            ptr:  to carry the address of first element in the passed array
 *                  size: to carry the size of the passed array to do the operation on this size only
 *
 * [Out]:           operand: to return the converted number from the entered array
 *
 * [Returns]:      sint64 operand
 ***************************************************************************************************/
sint64 convertArrayToNumber(uint8*ptr, uint8 size)
{
	uint8 count=0;
	uint8 exponent;
	uint64 tens=1;
	sint64 operand=0;
	for(count=0; count<size; count++)
	{
		tens =1;
		for (exponent= (size-count-1); exponent>0; exponent--)
		{
			tens = tens * 10;
		}

		operand += (ptr[count])* tens;
	}

return operand;
}
/***************************************************************************************************
 * [Function Name]: check_syntaxError
 *
 * [Description]:  function to check if the array contain some certain operators or not
 *
 * [Args]:            uint8*ptr
 *                    uint8 size
 *
 *
 * [In]:            ptr:  to carry the address of first element in the passed array
 *                  size: to carry the size of the passed array to do the operation on this size only
 *
 * [Out]:           erorr: to return the status of the variable if the array contains this operator or not
 *
 * [Returns]:      bool error
 ***************************************************************************************************/
bool check_syntaxError(uint8* ptr,const uint8* size)
{
	uint8 count=0;
	bool error= FALSE;
	for(count=0; count< (*size); count++)
	{

		if(     (ptr[0] == '*') /*|| (ptr[0] == '=')*/ || (ptr[0] == '%') ||
				( (ptr[count] == '-') && (ptr[count+1] == '*') ) ||
				( (ptr[count] == '*') && (ptr[count+1] == '*') ) ||
				( (ptr[count] == '+') && (ptr[count+1] == '*') ) ||
				( (ptr[count] == '*') && (ptr[count+1] == '%') ) ||
				( (ptr[count] == '%') && (ptr[count+1] == '*') ) ||
				( (ptr[count] == '%') && (ptr[count+1] == '%') ) ||
				( (ptr[count] == '%') && (ptr[count+1] == '+') ) ||
				( (ptr[count] == '+') && (ptr[count+1] == '%') ) ||
				( (ptr[count] == '-') && (ptr[count+1] == '=') ) ||
				( (ptr[count] == '+') && (ptr[count+1] == '=') ) ||
				( (ptr[count] == '%') && (ptr[count+1] == '=') ) ||
				( (ptr[count] == '*') && (ptr[count+1] == '=') )

		)
		{

			error = TRUE;
		}


	}

	return error;
}
/***************************************************************************************************
 * [Function Name]: check_sign
 *
 * [Description]:  function to check the number of negative signs and decide if the number is
 *                 negative or not
 *
 * [Args]:            uint8 *number_of_negative
 *
 *
 * [In]:            number_of_negative: to carry the number of negative signs before the number
 *
 * [Out]:           sign: to return the final decision if the number is negative or positive
 *
 * [Returns]:      uint8 sign
 ***************************************************************************************************/
uint8 check_sign(uint8 *number_of_negative)
{
	uint8 sign =0;

	if( ( (*number_of_negative)%2) == 1)
	{
		sign = -1;
	}
	else
	{
		sign = 1;
	}
	return sign;
}
/****************************************************************************************************/
