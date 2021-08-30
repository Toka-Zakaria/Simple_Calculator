/**********************************************************************************
 * [FILE NAME]: app_file.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Aug 28, 2021
 *
 * [Description]: header File to contain the functions of application of the Calculator
 ***********************************************************************************/

#ifndef APP_FILE_H_
#define APP_FILE_H_

#include"std_types.h"
#include"micro_config.h"
#include"common_macros.h"
#include"keyPad.h"
#include"lcd.h"

#define STATEMENT_ARRAY_SIZE              50
#define FIRST_NUMBER_ARRAY_SIZE           20
#define SECOND_NUMBER_ARRAY_SIZE          20
#define INITIAL_VALUE                      0
#define ENTER_KEY_ASCII_VALUE             13
#define FIRST_ROW                          0
#define SECOND_ROW                         1
#define THIRD_ROW                          2
#define FOURTH_ROW                         3
#define FIRST_COLOUMN                      0

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
sint64 Calculator(sint32 first, sint32 second, uint8 op );
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
void display_key(uint8*pressedKey);
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
sint64 convertArrayToNumber(uint8* ptr, uint8 size);
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
bool check_syntaxError(uint8* ptr,const uint8* size);
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
uint8 check_sign(uint8 *number_of_negative);

#endif /* APP_FILE_H_ */
