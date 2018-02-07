#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Declare Functions:
void convertBinaryToDecimal(int);
void convertDecimalToBinary(int);

int main(int argc, char **argv)
{
	char operation;
	int num;
	
	// User Input:
	printf("Enter B for conversion of Binary to Decimal, OR\n");
	printf("Enter D for conversion of Decimal to Binary: ");
	scanf(" %c", &operation);
	
	printf("Enter your number: ");
	if (operation != 'B' && operation != 'D') { // Check for incorrect input
		printf("Invalid input; Goodbye");
		return 0;
	}
	scanf("%d", &num);
	
	if (operation == 'B') convertBinaryToDecimal(num); // Binary to Decimal Conversion
	else if (operation == 'D') convertDecimalToBinary(num); // Decimal to Binary Conversion
	return 0;
}

void convertBinaryToDecimal(int num) {
	int binary = num; // Binary Value
	double decimal=0; // Decimal Value
	
	/* To convert from binary to decimal, check remainder 
	 * when divided by 10. If remainder is 1, add the value of 2 to 
	 * the power of the place value of the digit.
	 * The place value of the digit is stored in the variable i. The number 
	 * is divided by 10 to move the number one place to the right
	 */
	 
	for (int i=0; num; num/=10, i++)
		if (num%10) decimal += pow(2,i);
		
	printf("%d in binary = %.lf in decimal", binary, decimal);
}

void convertDecimalToBinary(int num) {
	double binary=0; // Binary Value
	int decimal = num; // Decimal Value
	
	/* To convert from decimal to binary, check remainder 
	 * when divided by 2. If remainder is 1, add the value of 10 to 
	 * the power of the place value of the digit.
	 * The place value of the digit is stored in the variable i. The number 
	 * is divided by 2 to move the number one place to the right on the binary scale
	 */
	 
	 for (int i=0; num; num/=2, i++)
		if (num%2) binary += pow(10,i);
	printf("%d in decimal = %.lf in binary", decimal, binary);
}
