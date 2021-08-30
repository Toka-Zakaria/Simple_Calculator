/**********************************************************************************
 * [FILE NAME]: main.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Aug 28, 2021
 *
 * [Description]: File to contain the application of the Calculator
 ***********************************************************************************/


#include"app_file.h"

int main(void)
{
	/*******************************************************************************
	 *                  Variables decelerations and definitions                    *
	 *******************************************************************************/
	/*
	 * Variable to use it as a counter in loops
	 */
	uint8 counter;
	/*
	 * Variable to use it as 2 states to use it as condition to check if
	 *the state of it changes or not, and that  to avoid using 'break' in the loop
	 * which responsible to store the whole statement,
	 */
	bool SW_flag = FALSE;
	/*
	 * Variable to use it as 2 states to use it as condition to check if
	 *the entered statement in the right way or not
	 */
	bool syntaxError = FALSE;
	/*
	 * array to store the whole statement that contain numbers
	 * and numbers element by element from the user
	 */
	uint8 statementArray[STATEMENT_ARRAY_SIZE];
	/*
	 * array to store the first number in the statement number by
	 * number without any signs or operations element by element
	 */
	uint8 first_numberArray[FIRST_NUMBER_ARRAY_SIZE];
	/*
	 * array to store the second number in the statement number by
	 * number without any signs or operations element by element
	 */
	uint8 second_numberArray[SECOND_NUMBER_ARRAY_SIZE];
	/*
	 * variable to use it to determine the actual size
	 * which is the used size from the total size of the
	 * statement array
	 */
	uint8 statementArray_size = INITIAL_VALUE;
	/*
	 * variable to use it to determine the actual size
	 * which is the used size from the total size of the
	 * first number array
	 */
	uint8 firstNumber_size   = INITIAL_VALUE;
	/*
	 * variable to use it to determine the actual size
	 * which is the used size from the total size of the
	 * second number array
	 */
	uint8 secondNumber_size  = INITIAL_VALUE;
	/*
	 * variable to use it to store the required operation
	 * between the two operands
	 */
	uint8 operation;
	/*
	 * variable to store the first number after convert
	 * first number array to number, concatenate all its element
	 * together to implement the right entered number
	 */
	sint64 first_operand = INITIAL_VALUE;
	/*
	 * variable to store the second number after convert
	 * second number array to number, concatenate all its element
	 * together to implement the right entered number
	 */
	sint64 second_operand= INITIAL_VALUE;
	/*
	 * variable to store the first operand after detecting
	 * its actual sign
	 */
	sint64 first_number_signed= INITIAL_VALUE;
	/*
	 * variable to store the sign of the first number
	 */
	sint8 firstNumber_sign;
	/*
	 * variable to store the sign of the second number
	 */
	sint8 secondNumber_sign;
	/*
	 * variable to store the number of negative sign before or
	 * after the number
	 */
	uint8 negative = INITIAL_VALUE;
	/*
	 * variable to check if there is math error or not
	 */
	bool errorFlag= FALSE;
	/*******************************************************************************
	 *                           Modules Initialization                            *
	 *******************************************************************************/
	LCD_init();
	/*******************************************************************************
	 *                                 Application                                 *
	 *******************************************************************************/
	while(1)
	{
		/*
		 * force the cursor to got to the first row & first column position
		 * display message "Simple Calculator" to user to be the default message
		 * force the cursor to got to the second row & first column position
		 */
		LCD_goToRowColumn(FIRST_ROW, FIRST_COLOUMN);
		LCD_displayString("Simple Calculator");
		LCD_goToRowColumn(SECOND_ROW, FIRST_COLOUMN);
		/*******************************************************************************
		 *  Receive the whole statement from user which contain numbers & operations   *
		 *******************************************************************************/
		for(counter = 0;  SW_flag != TRUE ; counter++)
		{
			/*store all the entered keys from the user*/
			statementArray[counter]  = KeyPad_getPressedKey();

			/*
			 * call the function displayKey to display each char by its
			 * right specific way
			 */
			display_key( &statementArray[counter] );

			/*
			 * increment the size of the statement array with
			 * every press on the keypad till reach reach '=' char
			 */
			statementArray_size++;

			/*condition to make the statement ends when the user enters '=' */
			if(statementArray[counter] == '=')
			{
				/*
				 * change the statement of the variable SW_flag to
				 * exit from the loop when the user enters '='
				 */
				SW_flag = TRUE;
			}
			if(statementArray[counter] == ENTER_KEY_ASCII_VALUE)
			{

				counter = -1;
				statementArray_size = INITIAL_VALUE;

				/*
				 * clear the screen & return to the main program
				 */
				LCD_clearScreen();
				/*
				 * force the cursor to got to the first row & first column position
				 * display message "Simple Calculator" to user to be the default message
				 * force the cursor to got to the second row & first column position
				 */
				LCD_goToRowColumn(FIRST_ROW, FIRST_COLOUMN);
				LCD_displayString("Simple Calculator");
				LCD_goToRowColumn(SECOND_ROW, FIRST_COLOUMN);

			}
			/*
			 * wait some seconds before storing the next press on the keypad
			 * to avoid repeated press with one press only
			 * due to sensitivity of one  press
			 */
			_delay_ms(300);
		}
		/*******************************************************************************/
		/*
		 * Check the syntax of the entered numbers & operations
		 */
		syntaxError = check_syntaxError(statementArray, &statementArray_size);
		/*******************************************************************************
		 *                           A-Wrong Syntax Stage                               *
		 *******************************************************************************/
		if (syntaxError == TRUE)
		{
			/*
			 * Return the variable to be false again to be ready for the
			 * next check & do this operation in the right way
			 */
			syntaxError = FALSE;

			/*
			 * force the cursor to got to the third row & first column position
			 * display message "Syntax Error" to user
			 * force the cursor to got to the fourth row & first column position
			 * display message "Press Enter to CONT." to user
			 */
			LCD_goToRowColumn(THIRD_ROW, FIRST_COLOUMN);
			LCD_displayString("Syntax Error!");
			LCD_goToRowColumn(FOURTH_ROW, FIRST_COLOUMN);
			LCD_displayString("Press Enter to CONT.");

			while((KeyPad_getPressedKey()) != ENTER_KEY_ASCII_VALUE);
			LCD_clearScreen();

		}
		/*******************************************************************************
		 *                           B-right Syntax Stage                               *
		 *******************************************************************************/
		else if ( syntaxError == FALSE )
		{
			/*
			 * return the value of the counter to be 0
			 * to start reading the statement array from the first
			 */
			counter =0;

			/*
			 * this loop to make sure that the first element will be stored in the
			 * first array number will be number not sign and to calculate the
			 * number of negative signs before the first number if exist
			 */
			while( (statementArray[counter] == '+') ||
					(statementArray[counter] == '-') )
			{

				if( statementArray[counter] == '-')
				{
					/*
					 * increment the variable of the negative number
					 * if the sign before the number is negative ONLY
					 */
					negative++;
				}
				/*
				 * increment the value of the counter till reach the first digit of the number
				 */
				counter++;
			}

			/*
			 * detect the final sign of the first operand
			 * store it in a variable
			 */
			firstNumber_sign =  check_sign(&negative);
			/*
			 * start to get the first number element by element
			 * store it in first number array till reach the next sign
			 */
			while ( (statementArray[counter] != '+') &&
					(statementArray[counter] != '-') &&
					(statementArray[counter] != '*') &&
					(statementArray[counter] != '/') &&
					(statementArray[counter] != '%') &&
					(statementArray[counter] != '=')
			)
			{
				/*
				 * store the first number in the first number array
				 * element by element from the statement array
				 */
				first_numberArray[firstNumber_size] = statementArray[counter];
				/*
				 * increment the size of the first number array
				 * to get the actual size of the array till reach
				 * the next sign
				 */
				firstNumber_size++;
				/*
				 * increment the counter till reach the first sign
				 */
				counter++;
			}
			/*
			 * Concatenate the first number array to be a number and store it
			 * in the first operand variable
			 */
			first_operand = convertArrayToNumber(first_numberArray, firstNumber_size);
			/*
			 * get the first operand with its right sign
			 */
			first_number_signed = first_operand * firstNumber_sign;

			/*
			 * detect the operation and store it in a variable
			 * to be ready to do the operation
			 */
			operation = statementArray[counter];

			/*
			 * increment the counter to point at the element after the operation
			 */
			counter = counter+1;
			/*******************************************************************************
			 *                   (B-1) Check size of the counter Stage                     *
			 *         (B-1-1) this condition means that there aren't operation            *
			 *                     and this is (number = ) case                            *
			 *******************************************************************************/
			if(counter >= statementArray_size)
			{
				/*
				 * in the (number = ) case we have to display the same number only
				 * then return to the main program
				 */
				LCD_intgerToString(first_number_signed);
				/*
				 * force the cursor to got to the fourth row & first column position
				 * display message "Press Enter to CONT." to user
				 */
				LCD_goToRowColumn(FOURTH_ROW, FIRST_COLOUMN);
				LCD_displayString("Press Enter to CONT.");
				/*
				 * wait until using the user press enter button
				 */
				while((KeyPad_getPressedKey()) != ENTER_KEY_ASCII_VALUE);
				/*
				 * clear the screen & return to the main program
				 */
				LCD_clearScreen();
			}
			/*******************************************************************************
			 * (B-1-2) this condition means that there are operations in the statement      *
			 *******************************************************************************/
			else if(counter < statementArray_size)
			{
				do
				{
					/*
					 * return the value of the negative to be zero to be
					 * ready to use itin another check
					 */
					negative = INITIAL_VALUE;

					/*
					 * this loop to make sure that the first element will be stored in the
					 * first array number will be number not sign and to calculate the
					 * number of negative signs before the first number if exist
					 */
					while( (statementArray[counter] == '+') ||
							(statementArray[counter] == '-') )
					{

						if( statementArray[counter] == '-')
						{
							/*
							 * increment the variable of the negative number
							 * if the sign before the number is negative ONLY
							 */
							negative++;
						}
						/*
						 * increment the value of the counter till reach the first digit of the number
						 */
						counter++;
					}

					/*
					 * detect the final sign of the second operand
					 * store it in a variable
					 */
					secondNumber_sign =  check_sign(&negative);
					/*
					 * start to get the second number element by element
					 * store it in first second array till reach the next sign
					 */
					while ( (statementArray[counter] != '+') &&
							(statementArray[counter] != '-') &&
							(statementArray[counter] != '*') &&
							(statementArray[counter] != '/') &&
							(statementArray[counter] != '%') &&
							(statementArray[counter] != '=')
					)
					{
						/*
						 * store the second number in the second number array
						 * element by element from the statement array
						 */
						second_numberArray[secondNumber_size] = statementArray[counter];
						/*
						 * increment the size of the second number array
						 * to get the actual size of the array till reach
						 * the next sign
						 */
						secondNumber_size++;
						/*
						 * increment the counter till reach the first sign
						 */
						counter++;
					}

					/*
					 * Concatenate the second number array to be a number and store it
					 * in the second operand variable
					 */
					second_operand = convertArrayToNumber(second_numberArray, secondNumber_size);
					/*
					 * do the required operation between the two numbers detected
					 * then store the value of the operation in the first operand
					 * to make second operand equals zero to be ready to contain the next number
					 */
					first_number_signed = Calculator( (first_number_signed), (second_operand*secondNumber_sign), operation);


					if( (second_operand == 0) && (operation == '%'))
					{
						errorFlag = TRUE;
					}
					/*
					 * store the operation after the next number to be ready for the next operation
					 */
					operation = statementArray[counter];

					/*
					 * reinitialize the second operand to be ready to the next number
					 */
					second_operand = INITIAL_VALUE;
					/*
					 * reinitialize the second number size to be ready to the next number
					 * to detect the next number size without corruption
					 */
					secondNumber_size = INITIAL_VALUE;
					/*
					 * increment the counter to get all elements in the statement array
					 * till reach the size of the array exactly
					 */
					counter++;

				}while(statementArray[counter-1] != '='); /*repeat all the previous section till reach '='*/


				if(errorFlag == TRUE)
				{
					errorFlag = FALSE;

					/*
					 * force the cursor to got to the third row & first column position
					 * display message "Math Error" to user
					 */
					LCD_goToRowColumn(THIRD_ROW, FIRST_COLOUMN);
					LCD_displayString("Math Error!");
				}
				else if(errorFlag == FALSE)
				{
					/*
					 * display the final value of the statement which
					 * contain numbers and signs
					 */
					LCD_intgerToString(first_number_signed);
				}

				/*
				 * force the cursor to got to the fourth row & first column position
				 * display message "Press Enter to CONT." to user
				 */
				LCD_goToRowColumn(FOURTH_ROW, FIRST_COLOUMN);
				LCD_displayString("Press Enter to CONT.");
				/*
				 * wait until using the user press enter button
				 */
				while((KeyPad_getPressedKey()) != ENTER_KEY_ASCII_VALUE);
				/*
				 * clear the screen & return to the main program
				 */
				LCD_clearScreen();

			}/*end of counter < basicArray_usedSize*/


		}/*end of else Syntax Error condition = false*/

		/*
		 * reinitialize all statements to be ready for the
		 * next entered statement which contains numbers and signs
		 */
		statementArray_size =  INITIAL_VALUE;
		firstNumber_size=      INITIAL_VALUE;
		secondNumber_size=     INITIAL_VALUE;
		first_operand =        INITIAL_VALUE;
		second_operand=        INITIAL_VALUE;
		negative =             INITIAL_VALUE;
		SW_flag =              FALSE;

	}/*end of super loop*/

}/*end of main*/






