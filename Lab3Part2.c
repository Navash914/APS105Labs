/*
 *
 * Lab3Part2.c
 *
 * Command based (a,s,m,d) calculator.
 *
 * Author: Naveed Ashfaq
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declare Functions:
bool incorrectOperation(char);
bool divideByZero(double, char);
void printOutput(double, double, char);

int main(int argc, char **argv)
{
	// Declare Variables:
	double firstNum, secondNum;
	char opInput;
	
	// Prompt User Input:
	printf("Enter first number: ");
	scanf(" %lf", &firstNum); // First Number
	
	printf("Enter second number: ");
	scanf(" %lf", &secondNum); // Second Number
	
	printf("Enter calculation command (one of a, s, m, or d): ");
	scanf(" %c", &opInput); // Operator
	
	
	if (incorrectOperation(opInput)) printf("Error, unknown calculation command given"); // Check for invalid operation
	else if (divideByZero(secondNum, opInput)) printf("Error, trying to divide by zero"); // Check for divide by zero
	else printOutput(firstNum, secondNum, opInput); // Inputs are valid, produce output
	
	return 0;
}

bool incorrectOperation(char opInput) {
	if (opInput != 'a' && opInput != 's' && opInput != 'm' && opInput != 'd') return true; // Operation invalid if opInput is not a,s,m or d
	else return false; // Operation valid otherwise
}

bool divideByZero(double num, char opInput) {
	if (num == 0 && opInput == 'd') return true; // Trying to divide by zero
	else return false; // OK otherwise
}

void printOutput(double firstNum, double secondNum, char opInput) {
	double result;
	
	if (opInput == 'a') { // Addition
		result = firstNum + secondNum;
		printf("Sum of %0.2lf and %0.2lf is %0.2lf", firstNum, secondNum, result);
	} else if (opInput == 's') { // Subtraction
		result = firstNum - secondNum;
		printf("Difference of %0.2lf from %0.2lf is %0.2lf", firstNum, secondNum, result);
	} else if (opInput == 'm') { // Multiplication
		result = firstNum * secondNum;
		printf("Product of %0.2lf and %0.2lf is %0.2lf", firstNum, secondNum, result);
	} else { // Division
		result = firstNum / secondNum;
		printf("Division of %0.2lf by %0.2lf is %0.2lf", firstNum, secondNum, result);
	}
}
