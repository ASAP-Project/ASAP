package chapter13;

public class Chap13 {
	public static int power(int x, int n)
	//	Returns x raised to the power n
	//	Assumption:  x is a valid integer and n is greater than 0
	//	Note: Large exponents may result in integer overflow
	{
		if (n == 1)
			return x;                   // Base case
		else
			return x * power(x, n - 1); // Recursive call
	}

	public static int factorial(int number)
//	Returns the factorial of number
//	Assumption: number is greater than or equal to 0
//	Note: Large values of number may cause integer overflow
	{
		if (number == 0)
			return 1;                              // Base case
		else
			return number * factorial(number - 1); // General case
	}

	public static void convert(int number)
//	Converts number to binary and prints it
//	Assumption:  number >= 0
	{
		if (number > 0)
		{
			convert(number / 2);   // Recursive call
			System.out.print(number % 2);
		}
		// Empty else clause is the base case
	}

}
