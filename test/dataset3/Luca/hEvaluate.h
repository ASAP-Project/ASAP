// Author: Luca Carlon
// Info: To have informations go to www.planet-source-code.com and www.sc4free.cjb.net
// Finished: 31.07.2003
// Version: 0.2.1

#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

const int SYMBOLS_NUMBER = 7;
const int MAX_EXPRESSION_LENGTH = 1000;

const int FUNCTIONS_NUMBER = 31;

const char SYMBOLS[SYMBOLS_NUMBER] = {'+', '-', '*', '/', '^', 'e', 'E'};
// N.B. Only commented functions are currently handled by the code.
const char FUNCTIONS[FUNCTIONS_NUMBER][8] =
{
	// Trigonometric functions
	"sin",          // - 1. Sine.
	"cos",          // - 2. Cosine.
	"tan",          // - 3. Tangent.
	"asin",         // - 4. Inverse sine.
	"acos",         // - 5. Inverse cosine.
	"atan",         // - 6. Inverse tangent.
	"sinh",         // - 7. Hyperbolic sine.
	"cosh",         // - 8. Hyperbolic cosine.
	"tanh",         // - 9. Hyperbolic tangent.
	"asinh",        // - 
	"acosh",        // - 
	"atanh",        // - 
	"sec",          // - 
	"csc",          // - 
	"cot",          // - 
	"asec",         // - 
	"acsc",         // -
	"acot",         // -
	"sech",         // - 
	"csch",         // -
	"coth",         // -
	"asech",        // -
	"acsch",        // -
	"acoth",        // -
	"atan2",        // -

	// Exponential
	"exp",          // - 26. Exponential (Nepero).
	"ln",           // - 27. Natural logarithm.
	"logx",         // - 28. Logarithm in a chosen basis (logx(basis, argument)).
	"sqrt",         // - 29. Square root.
	"rt"            // - 30. Root with a chosen index (rt(index, argument)).

};

struct struct_parenthesis
{
	int iOpen;
	int iClose;
	int iLevel;
} parenthesis[500];

// The function Evaluate solve a simple expression where parenthesis do not contain any operator.
// Evaluate do not returns values but modifies the string passed.
void Evaluate                (char sExpression[]);

// The function Solve can simplify any expression caontaining operaotrs and functions if foresee.
void Solve                   (char sExpression[]);

// This functions modifies the stirng passed and simplify the symbols present. --1 is simplified to +1 for
// instance.
void CheckExpression         (char sExpression[]);

// With this function you can know if in the string passed there is unless a separator of parameters (,)
// or not. The function returns true if the separator is passed, otherwise the value returned is false.
// In the Solve function CheckSeparator is used to decide wether to mantain the parenthesis of an expression
// or not.
bool CheckSeparator          (char sExpression[]);

// CheckOperator can be used to decide if it is present an operator in a string like +, -, *, / etc.. This function
// also foresee the presence of signs of number, something like (+1). In this case + is not an operator but it is a sign
// of the number. The function returns true if there is unless one operator and false if there isn't.
bool CheckOperator           (char sExpression[]);

// Replace the string between the element iStart and iEnd of sExpression with the new string sNewString.
void ReplaceString           (char sExpression[], char sNewString[], int iStart, int iEnd);

// Sort the symbols in the expression passed as parameter. Not used.
void SortSymbol              (char sExpression[]);

void SortParenthesis         (char sExpression[]);

// IsNumber returns true if the character passed is a number or false if it is not. The second argument
// allows you to tell the function to consider the point (.) as part of a number.
// The third argument allows you to handle exponential number (ex. 1e-10).
bool IsNumber                (char sExpression[], int iSymbolPosition, bool bConsiderPoint, bool bConsiderExponential);

// IsLetter determines whether the character sExpression[iSymbolPosition] is a letter or not. If the last parameter
// is set to true then in case a letter 'e' is found the function checks if it is intended as a letter or as (*10^).
// This is very useful if you want to use this function to determine whether the letter is part of a function or not.
bool IsLetter                (char sExpression[], int iSymbolPosition, bool CheckE);

// Computes all the powers present in sExpression.
void EvaluatePowers          (char sExpression[]);

// Computes all the multiplications in sExpression. Even divisions are computed in this functions since they are seen as
// a multiplication of the first term for the inverse of the second.
void EvaluateMultiplications (char sExpression[]);

// Computes all the additions present in sExpression. In this case even subtractions are computed since they are seen as
// a sum of the first term with the second multiplide by -1.
void EvaluateAdditions       (char sExpression[]);

// Computes all the functions foreseen in the constant FUNCTIONS.
void EvaluateFunctions       (char sExpression[]);

// FindOperator finds the numbers behind the operator in position iSymbolPosition or after that. bFindFirst should be set to true
// if you want to find the first number and to false if you want the second. cLastSymbol is needed because if it
// is a ^ for example, there are some differences.
double FindOperator          (char sExpression[], int iSymbolPosition, char cLastSymbol, bool bFindFirst);

// FindFunction determine which function has been written. The function confront the function in sExpression with all
// those present in the constant FUNCTIONS.
int FindFunction             (char sExpression[], int iStart);


//extern symbol_structure;
struct symbol_structure
{
	int position;
	char symbol;
}
symbols[1000];

// I need these to pass them to the ReplaceString function as iStart and iEnd
// while their value is calculated in FindOperator.
int iEndSecondOperator = 0;
int iBeginningFirstOperator = 0;


// ==================================================================


void Solve(char sExpression[])
{
	SortParenthesis(sExpression);

	// Finding the max level
	int iMaxLevel = 0;
	int iCounter;

	for (iCounter = 0; parenthesis[iCounter].iClose != 0; iCounter++)
	{
		if (parenthesis[iCounter].iLevel > iMaxLevel) iMaxLevel = parenthesis[iCounter].iLevel;
	}
	// =====================

	// Solving all parenthesis levels
	for (iCounter = iMaxLevel; iCounter >= 0; iCounter--)
	{
		// Solving all levels iCounter
		for (int iCounter2 = 0; parenthesis[iCounter2].iClose != 0; iCounter2++)
		{
			if (parenthesis[iCounter2].iLevel == iCounter)
			{
				// Solving the parenthesis
				char sParenthesis[1000] = {'\0'};

				int iParenthesisIndex = 0;

				for (int iCounter3 = (parenthesis[iCounter2].iOpen + 1); iCounter3 < parenthesis[iCounter2].iClose; iCounter3++)
				{
					sParenthesis[iParenthesisIndex++] = sExpression[iCounter3];
				}

				//if ((CheckSeparator(sParenthesis) && !CheckOperator(sParenthesis)) || !CheckSeparator(sParenthesis)) continue;
				if (!CheckOperator(sParenthesis)) continue;

				cout << "Step: " << sParenthesis << " = ";

				Evaluate(sParenthesis);

				// Insert the value in the expression, if there is a separator in the string, I do not replace the
				// parenthesis and I leave them otherwise I can delete them.
				if (CheckSeparator(sParenthesis)) ReplaceString(sExpression, sParenthesis,
				                                  parenthesis[iCounter2].iOpen + 1, parenthesis[iCounter2].iClose);
				else if (sExpression[parenthesis[iCounter2].iClose + 1] == '^') ReplaceString(sExpression, sParenthesis,
				                                            parenthesis[iCounter2].iOpen + 1, parenthesis[iCounter2].iClose);
				else ReplaceString(sExpression, sParenthesis, parenthesis[iCounter2].iOpen, parenthesis[iCounter2].iClose + 1);

				cout << sParenthesis << '\n' << "Result: " << sExpression << '\n';

				SortParenthesis(sExpression);

				iCounter2 = -1;
			}
		}
	}

	Evaluate(sExpression);

	cout << "\n\t" << sExpression << "\n";

	return;
}

void Evaluate(char sOldExpression[])
 {
	// This function checks the syntax of the expression to evaluate
	CheckExpression(sOldExpression);

	EvaluateFunctions(sOldExpression);

	// Evaluates the powers present in the string
	EvaluatePowers(sOldExpression);

	// Evaluates the multiplications and divisions present in the string
	EvaluateMultiplications(sOldExpression);

	// Evaluates all the sums and subtractions present in the string
	EvaluateAdditions(sOldExpression);

	return;
}

void EvaluateFunctions(char sExpression[])
{
	for (int iCounter = 0; sExpression[iCounter] != '\0'; iCounter++)
	{
		if (IsLetter(sExpression, iCounter, true) == true)
		{
			int iFunction = FindFunction(sExpression, iCounter);

			// sResult contains the result of the function.
			char sResult[100];


			switch (iFunction)
			{
				// Solving function sin.
				case 1:
				{
					double dArgument = FindOperator(sExpression, iCounter + 2, 'n', false);

					double dResult = sin(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving function cosine.
				case 2:
				{
					double dArgument = FindOperator(sExpression, iCounter + 2, 's', false);

					double dResult = cos(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving function tangent.
				case 3:
				{
					double dArgument = FindOperator(sExpression, iCounter + 2, 'n', false);

					double dResult = tan(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving the inverse sine.
				case 4:
				{
					double dArgument = FindOperator(sExpression, iCounter + 3, 'n', false);

					double dResult = asin(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving the inverse cosine.
				case 5:
				{
					double dArgument = FindOperator(sExpression, iCounter + 3, 's', false);

					double dResult = acos(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);
					
					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving the inverse tangent.
				case 6:
				{
					double dArgument = FindOperator(sExpression, iCounter + 3, 'n', false);

					double dResult = atan(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving the hyperbolic sine.
				case 7:
				{
					double dArgument = FindOperator(sExpression, iCounter + 3, 'h', false);

					double dResult = sinh(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving the hyperbolic cosine.
				case 8:
				{
					double dArgument = FindOperator(sExpression, iCounter + 3, 'h', false);

					double dResult = cosh(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving the hyperbolic tangent.
				case 9:
				{
					double dArgument = FindOperator(sExpression, iCounter + 3, 'h', false);

					double dResult = tanh(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving exponential.
				case 26:
				{
					double dArgument = FindOperator(sExpression, iCounter + 2, 'p', false);

					double dResult = exp(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving the natural logarithm.
				case 27:
				{
					double dArgument = FindOperator(sExpression, iCounter + 1, 'n', false);

					double dResult = log(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					break;
				}
				// Solving function logx.
				case 28:
				{
					double dFirstArgument = FindOperator(sExpression, iCounter + 3, 'x', false);
                                        
                                        // Try to find the length of the first argument
                                        char sArgument[50];
                                        
                                        sprintf(sArgument, "%g", dFirstArgument);
                                        int iCipherNumber = strlen(sArgument);
                                        // --------------------------------------------

					//double dSecondArgument = FindOperator(sExpression, (iEndSecondOperator - 4), ',', false);
					double dSecondArgument = FindOperator(sExpression, iCounter + 5 + iCipherNumber, ',', false);

					double dResult = (log(dSecondArgument) / log(dFirstArgument));

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					//ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator + 1);
					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator + 3);

					//cout << "\nResult: " << sExpression;

					break;
				}
				// Solving the square root.
				case 29:
				{
					double dArgument = FindOperator(sExpression, iCounter + 3, 't', false);

					double dResult = sqrt(dArgument);

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator);

					//cout << "\nResult: " << sExpression;

					break;
				}
				// Solving function rt.
				case 30:
				{
					double dFirstArgument = FindOperator(sExpression, iCounter + 1, 't', false);
                                        
                                        // Try to find the length of the first argument
                                        char sArgument[50];
                                        
                                        sprintf(sArgument, "%g", dFirstArgument);
                                        int iCipherNumber = strlen(sArgument);
                                        // --------------------------------------------

					double dSecondArgument = FindOperator(sExpression, iCounter + 3 + iCipherNumber, ',', false);

					double dResult = pow(dSecondArgument, (1.0 / dFirstArgument));

					if (sExpression[iEndSecondOperator] == '^') sprintf(sResult, "%c%g%c", '(', dResult, ')');
					else sprintf(sResult, "%g", dResult);

					ReplaceString(sExpression, sResult, iCounter, iEndSecondOperator + 1);

					//cout << "\nResult: " << sExpression;

					break;
				}
			}
		}
	}

	return;
}

void EvaluateMultiplications(char sExpression[])
{
	for (int iCounter = 0; sExpression[iCounter] != '\0'; iCounter++)
	{
		if (sExpression[iCounter] == '*')
		{
			double dFirst = FindOperator(sExpression, iCounter, '*', 1);

			double dSecond = FindOperator(sExpression, iCounter, '*', 0);

			//cout << "\nResult: " << dFirst * dSecond;

			// Calculating sNewString and iEnd
			char sResult[100] = {'\0'};
			sprintf(sResult, "%g", dFirst * dSecond);
			
			// I have to calculate the beginning and the end of the string to be replaced
			//if (iBeginningFirstOperator < 0) iBeginningFirstOperator = 0;
			ReplaceString(sExpression, sResult, iBeginningFirstOperator, iEndSecondOperator);

			//cout << "\nResult: " << sExpression;

			iCounter = 0;
		}
		if (sExpression[iCounter] == '/')
		{
			// Finds the first operator and ...
			double dFirst = FindOperator(sExpression, iCounter, '/', 1);

			// ... then the second.
			double dSecond = FindOperator(sExpression, iCounter, '/', 0);

			// The division is the multiplication of the first operator with the inverse of the second
			//cout << "\nResult: " << dFirst * (1 / dSecond);

			// Calculating sNewString and iEnd
			char sResult[100] = {'\0'};
			sprintf(sResult, "%g", dFirst * (1 / dSecond));
			
			// I have to calculate the beginning and the end of the string to be replaced
			//if (iBeginningFirstOperator < 0) iBeginningFirstOperator = 0;
			ReplaceString(sExpression, sResult, iBeginningFirstOperator, iEndSecondOperator);

			//cout << "\nResult: " << sExpression;

			// I cannot know the difference of space between the first string and the new string (only result)
			// so it is necessary to restart the cycle to avoid that some other divisions are not solved.
			iCounter = 0;
		}
	}

	return;
}

void EvaluateAdditions(char sExpression[])
{
	for (int iCounter = 0; sExpression[iCounter] != '\0'; iCounter++)
	{
		if (sExpression[iCounter] == '+')
		{
			// Before evaluating a addition I have to check whether the sign is an operator or not
			// If the sign is at the beginning of the string it ain't an operator and then I exit the function
			if (iCounter == 0) continue;
			// If the character before iCounter is a ) then I continue else exit
			if (sExpression[iCounter - 1] != ')')
			{
				// if the sign has no number before it its not an operator
				if (IsNumber(sExpression, iCounter - 1, false, true) == false) continue;
			}

			double dFirst = FindOperator(sExpression, iCounter, '+', 1);

			double dSecond = FindOperator(sExpression, iCounter, '+', 0);

			//cout << "\nResult: " << dFirst + dSecond;

			// Calculating sNewString and iEnd
			char sResult[100] = {'\0'};
			sprintf(sResult, "%g", dFirst + dSecond);
			
			// I have to calculate the beginning and the end of the string to be replaced
			//if (iBeginningFirstOperator < 0) iBeginningFirstOperator = 0;
			ReplaceString(sExpression, sResult, iBeginningFirstOperator, iEndSecondOperator);

			//cout << "\nResult: " << sExpression;

			iCounter = 0;
		}
		if (sExpression[iCounter] == '-')
		{
			// Before evaluating a addition I have to check whether the sign is an operator or not
			// If the sign is at the beginning of the string it ain't an operator and then I exit the function
			if (iCounter == 0) continue;
			// If the character before iCounter is a ) then I continue else exit
			if (sExpression[iCounter - 1] != ')')
			{
				// if the sign has no number before it its not an operator
				if (IsNumber(sExpression, iCounter - 1, false, true) == false) continue;
			}


			double dFirst = FindOperator(sExpression, iCounter, '-', 1);

			double dSecond = FindOperator(sExpression, iCounter, '-', 0);

			// Calculating sNewString and iEnd
			char sResult[100] = {'\0'};
			sprintf(sResult, "%g", dFirst + (-dSecond));
			
			// I have to calculate the beginning and the end of the string to be replaced
			//if (iBeginningFirstOperator < 0) iBeginningFirstOperator = 0;
			ReplaceString(sExpression, sResult, iBeginningFirstOperator, iEndSecondOperator);

			//cout << "\nResult: " << sExpression;

			iCounter = 0;
		}
	}

	return;
}

void EvaluatePowers(char sExpression[])
{
	// Solve all the powers in the string
	for (int iCounter = 0; sExpression[iCounter]; iCounter++)
	{
		if (sExpression[iCounter] == '^')
		{
			// Find the base
			double dBase = FindOperator(sExpression, iCounter, '^', 1);

			// Find the exponent looking for the succeeding symbol after the ^
			double dExponent = FindOperator(sExpression, iCounter, '^', 0);

			// Show the result of the elevation
			//cout << "\nResult: " << pow(dBase, dExponent);

			// Calculating sNewString and iEnd
			char sResult[100] = {'\0'};
			sprintf(sResult, "%g", pow(dBase, dExponent));
			
			// I have to calculate the beginning and the end of the string to be replaced
			//if (iBeginningFirstOperator < 0) iBeginningFirstOperator = 0;
			ReplaceString(sExpression, sResult, iBeginningFirstOperator, iEndSecondOperator);

			//cout << "\nResult: " << sExpression;

			iCounter = 0;
		}
	}

	return;
}

double FindOperator(char sExpression[], int iSymbolPosition, char cLastSymbol, bool bFindFirst)
{
	// If bFindFirst is set to true then the function returns the value of the first operator
	if (bFindFirst)
	{
		// There are two cases, if the number is between parenthesis or not
		if (sExpression[iSymbolPosition - 1] == ')')
		{
			// The number is between parenthesis and I have to find the last open parenthesis
			// int iCounter;
			
			int iCounter;
			
			for (iCounter = iSymbolPosition - 2; iCounter >= 0; iCounter--)
			{
				if (sExpression[iCounter] == '(') break;
			}

			// Position of the first parenthesis
			iBeginningFirstOperator = iCounter;

			// iCounter is the position of the open parenthesis, I have to increment it by one
			iCounter++;

			char sTmp[1000] = {'\0'};
			int iTmpIndex = 0;

			for (int iCounter2 = iCounter; iCounter2 <= iSymbolPosition - 2; iCounter2++)
			{
				sTmp[iTmpIndex++] = sExpression[iCounter2];
			}

			return atof(sTmp);
		}
		else
		{
			// The number is not without parenthesis and I have to find the first character which is no more a number
			int iCounter;
			
			for (iCounter = iSymbolPosition - 1; iCounter >= 0; iCounter--)
			{
				if (IsNumber(sExpression, iCounter, true, true) == true) continue;
				else if (sExpression[iCounter] == 'e' || sExpression[iCounter - 1] == 'e') continue;
				else break;
			}

			// If the operator is a ^ or if I have not reached the beginning of the string I have not to consider the sign
			if ((cLastSymbol == '^' && iCounter == 0 && IsNumber(sExpression, 0, false, false) == false) || iCounter != 0) iCounter++;

			iBeginningFirstOperator = iCounter;

			// Copy in sTmp
			char sTmp[1000];
			int iTmpIndex = 0;

			for (int iCounter2 = iCounter; iCounter2 <= iSymbolPosition; iCounter2++)
			{
				sTmp[iTmpIndex++] = sExpression[iCounter2];
			}

			return atof(sTmp);
		}
	}
	else
	{
		// I have to find the second number
		if (sExpression[iSymbolPosition + 1] == '(')
		{
			// The number is between the parenthesis so I can find the first closed parenthesis
			int iCounter;
			
			for (iCounter = iSymbolPosition + 2; sExpression[iCounter] != '\0'; iCounter++)
			{
				if (sExpression[iCounter] == ')') break;
			}

			iEndSecondOperator = iCounter + 1;

			char sTmp[1000] = {'\0'};
			int iTmpIndex = 0;

			for (int iCounter2 = iSymbolPosition + 2; iCounter2 < iCounter; iCounter2++)
			{
				sTmp[iTmpIndex++] = sExpression[iCounter2];
			}

			return atof(sTmp);
		}
		else
		{
			// The number is not within parenthesis
			int iCounter;
			
			for (iCounter = iSymbolPosition + 1; sExpression[iCounter] != '\0'; iCounter++)
			{
				if (IsNumber(sExpression, iCounter, true, true) == true) continue;
				else if (sExpression[iCounter] == 'e' || sExpression[iCounter - 1] == 'e') continue;
				// We could be in the case: 1^-2 and I have to consider the minus
				else if (iCounter == iSymbolPosition + 1) continue;
				else break;
			}

			// I have to decrement the number because it is the position of the sign after the last number
			iCounter--;

			iEndSecondOperator = iCounter + 1;

			// Copy all in the temporary string
			char sTmp[1000] = {'\0'};
			int iTmpIndex = 0;

			for (int iCounter2 = iSymbolPosition + 1; iCounter2 <= iCounter; iCounter2++)
			{
				sTmp[iTmpIndex++] = sExpression[iCounter2];
			}

			return atof(sTmp);
		}
	}
}

void CheckExpression(char sExpression[])
{
	char plus[2] = "+";
	char minus[2] = "-";
	char per[2] = "*";
	char div[2] = "/";


	// Check if a symbol is present, this variable says if a precedent symbol has been found
	bool bOneFound = false;

	// Iterating through all the array sExpression
	for (int iContatore = 0; sExpression[iContatore] != '\0'; iContatore++)
	{
		// If the character is a number then we can skip and go to the next character
		if (sExpression[iContatore] >= 48 && sExpression[iContatore] <= 57) {bOneFound = false; continue;}
		else
		{
			// Decide what symbol I have to insert
			if (bOneFound)
			{
				// TODO; Complete
				if (sExpression[iContatore - 1] == '+' && sExpression[iContatore] == '+')
				{
					// Replace the two symbols with only one
					ReplaceString(sExpression, plus, iContatore - 1, iContatore + 1);

					// I have to step back by two because there could be more than two symbols
					iContatore -= 2;
					bOneFound = false;
				}
				else if (sExpression[iContatore - 1] == '-' && sExpression[iContatore] == '-')
				{
					ReplaceString(sExpression, plus, iContatore - 1, iContatore + 1);
					iContatore -= 2;
					bOneFound = false;
				}
				else if (sExpression[iContatore - 1] == '+' && sExpression[iContatore] == '-')
				{
					ReplaceString(sExpression, minus, iContatore - 1, iContatore + 1);
					iContatore -= 2;
					bOneFound = false;
				}
				else if (sExpression[iContatore - 1] == '-' && sExpression[iContatore] == '+')
				{
					ReplaceString(sExpression, minus, iContatore - 1, iContatore + 1);
					iContatore -= 2;
					bOneFound = false;
				}
				else if (sExpression[iContatore - 1] == '*' && sExpression[iContatore] == '*'); // Errore
				else if (sExpression[iContatore - 1] == '/' && sExpression[iContatore] == '/'); // Errore
				else if (sExpression[iContatore - 1] == '*' && sExpression[iContatore] == '/'); // Errore
				else if (sExpression[iContatore - 1] == '/' && sExpression[iContatore] == '*'); // Errore
				else
				{
					// In this case I could have found something like *+ and it is ok or a letter and I'll check them with the trigonometrics
					bOneFound = false;

					// Exit the cicle
					continue;
				}
			}
			else
			{
				bOneFound = true;
				continue;
			}
		}
	}

	//CheckParenthesis(sExpression);

	return;
}

void ReplaceString(char sExpression[], char sNewString[], int iStart, int iEnd)
{
	// 1. Copy all the string in a temporary string.
	// 2. Clear the non-temporary string from iStart to the end.
	// 3. Insert the new string starting from iStart.
	// 4. Find iEnd.
	// 5. Copy from iEnd to the end.

	char sTmpExpression[1000] = {'\0'};

	// Copy all the string in a temporary
	int iContatore;
	
	for (iContatore = 0; sExpression[iContatore] != '\0'; iContatore++)
	{
		sTmpExpression[iContatore] = sExpression[iContatore];
	}

	// Clear from iStart (included) to the end ----
	for (iContatore = iStart; sExpression[iContatore] != '\0'; iContatore++)
	{
		sExpression[iContatore] = '\0';
	}

	// Insert the new string
	iContatore = iStart;
	
	int iContatore2;

	for (iContatore2 = 0; sNewString[iContatore2] != '\0'; iContatore2++)
	{
		sExpression[iContatore++] = sNewString[iContatore2];
	}

	sExpression[iContatore] = '\0';

	// Copy the remaining
	for (iContatore2 = iEnd; sTmpExpression[iContatore2] != '\0'; iContatore2++)
	{
		sExpression[iContatore++] = sTmpExpression[iContatore2];
	}

	sExpression[iContatore] = '\0';

	return;
}

bool IsNumber(char sExpression[], int iSymbolPosition, bool bConsiderPoint, bool bConsiderExponential)
{
	if (sExpression[iSymbolPosition] >= 48 && sExpression[iSymbolPosition] <= 57) return 1;
	else if (bConsiderPoint == true && sExpression[iSymbolPosition] == '.') return 1;
	else return 0;
}

bool IsLetter (char sExpression[], int iSymbolPosition, bool CheckE)
{
	if (sExpression[iSymbolPosition] >= 65 && sExpression[iSymbolPosition] <= 90)
	{
		if (sExpression[iSymbolPosition] == 'E')
		{
			if (IsNumber(sExpression, iSymbolPosition - 1, false, false) == true) return false;
			else return true;
		}

		return true;
	}
	else if (sExpression[iSymbolPosition] >= 97 && sExpression[iSymbolPosition] <= 122)
	{
		if (sExpression[iSymbolPosition] == 'e')
		{
			if (IsNumber(sExpression, iSymbolPosition - 1, false, false) == true) return false;
			else return true;
		}

		return true;
	}
	else return false;
}

int FindFunction(char sExpression[], int iStart)
{
	int iExpressionIndex = iStart;

	for (int iCounter = 0; iCounter < FUNCTIONS_NUMBER; iCounter++)
	{
		for (int iCounter2 = 0; FUNCTIONS[iCounter][iCounter2] != '\0'; iCounter2++)
		{
			// If the character is the same, the following character is \0, and the following character
			// of the expression is a number or an open parenthesis or a sign then I've found the function.
			if (FUNCTIONS[iCounter][iCounter2] == sExpression[iExpressionIndex] &&
			    FUNCTIONS[iCounter][iCounter2 + 1] == '\0' &&
			    (IsNumber(sExpression, iExpressionIndex + 1, false, false) ||
			    sExpression[iExpressionIndex + 1] == '(' ||
					sExpression[iExpressionIndex + 1] == '-' || sExpression[iExpressionIndex + 1] == '+')) return (iCounter + 1);

			// If the character is the same but the succeeding character in the expression is not a number or a
			// open parenthesis then change function
			/*if (FUNCTIONS[iCounter][iCounter2] == sExpression[iExpressionIndex] &&
			    FUNCTIONS[iCounter][iCounter2 + 1] == '\0' &&
					IsNumber(sExpression, iExpressionIndex + 1, false, false) == false &&
			    sExpression[iExpressionIndex + 1] != '(' &&
					sExpression[iExpressionIndex + 1] != '+' &&
					sExpression[iExpressionIndex + 1] != '-') break;*/

			else if (FUNCTIONS[iCounter][iCounter2] == sExpression[iExpressionIndex])
			{
				iExpressionIndex++;
				continue;
			}
			else break;
		}

		iExpressionIndex = iStart;
	}

	return 0;
}

bool CheckSeparator(char sExpression[])
{
	// Cycle through the string passed.
	for (int iCounter = 0; sExpression[iCounter] != '\0'; iCounter++)
	{
		// If a separator (,) is found then return true.
		if (sExpression[iCounter] == ',') return true;
	}

	// If the cycle end and we are still in, it means there is no separator.
	return false;
}

bool CheckOperator(char sExpression[])
{
	for (int iCounter = 0; sExpression[iCounter] != '\0'; iCounter++)
	{
		if (!IsNumber(sExpression, iCounter, true, true))
		{
			// It's not a number
			if (sExpression[iCounter] == '+' || sExpression[iCounter] == '-')
			{
				if (IsNumber(sExpression, iCounter - 1, true, true)) return true;
				
				else continue;
			}

			if (sExpression[iCounter] == ',') continue;
			if (sExpression[iCounter] == 'e' || sExpression[iCounter + 1] == 'e') continue;
			return true;
		}
	}

	return false;
}

void SortParenthesis(char sExpression[])
{
  // Declaring variable for the position of each symbol in the expression
  int sym_num = 0;

  // Declaring the variable for the position of each parentesys
  int par_pos[100];
  int par_num = 0;

  int max_record_number = 0;

  // Starting iterating, stops when the finish character is met
  int i;
  
  for (i = 0; (char)sExpression[i] != '\0'; i++)
  {
    // If the symbol is a parentesys, the inserting its position in the array
    if (sExpression[i] == '(' || sExpression[i] == ')') par_pos[par_num++] = i;

    // Checking if a symbol has been entered
    /*for (int a = 0; a < allowed_symb_number; a++)
    {
      if (sExpression[i] == allowed_sym[a]) sym_pos[sym_num++] = i;
    }*/
  }

  // Showing the result
  /*for (i = 0; i <= (par_num - 1); i++) cout << "\nParentesys found in column number: " << par_pos[i];

	for (i = 0; i <= (sym_num - 1); i++) cout << "\nSymbol found in column number: " << sym_pos[i];*/

  // Finding the most internal level of parentesys
  int tmp_level = 0;
  int record = 0;

  // Azzero tutta la struttura
  // Resetting al the structure to zero
  int a;
	
  for (a = 0; a < 100; a++)
  {
    parenthesis[a].iOpen = 0;
    parenthesis[a].iClose = 0;
    parenthesis[a].iLevel = 0;
  }

  for (i = 0; i < par_num; i++)
  {
    if (sExpression[par_pos[i]] == '(')
    {
      tmp_level++;
      parenthesis[max_record_number].iOpen = par_pos[i];
      parenthesis[max_record_number].iLevel = tmp_level;
      max_record_number++;
    }
    else
    {
      tmp_level--;

      // Checking for last not closed parentesys
      for (int a = max_record_number - 1; a >= 0; a--)
      {
        if (parenthesis[a].iClose == 0)
        {
          parenthesis[a].iClose = par_pos[i];
          break;
        }
      }
    }
  }

  // Showing the result
  /*for (i = 0; i < max_record_number; i++)
  {
    cout << "\n" << parenthesis[i].iOpen << " " << parenthesis[i].iClose << " " << parenthesis[i].iLevel;
  }*/
}
