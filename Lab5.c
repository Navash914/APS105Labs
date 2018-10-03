/*
 *
 * Lab4Part2.c
 *
 * Draws Pascal's triangle upto user inputted number
 * of rows (max 13).
 *
 * Author: Naveed Ashfaq
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void triangle(int);
int choose(int, int);
int factorial(int);
int printInitialSpaces(int);
void printSpaces(int);

int main(int argc, char **argv)
{
	int inputRow;
	bool finished = false;
	
	while (!finished) { // Loop till negative input
	printf("Enter the number of rows: ");
	scanf("%d", &inputRow);
	
	if (inputRow >= 0) triangle(inputRow); // Draw triangle if input is 0 or positive
	else finished = true; // End program if negative input
	}
	return 0;
}

void triangle(int maxRow) {
	int row, initSpace, n, r, num;
	initSpace = 3*maxRow - 2; // Formula for beginning initial space
	
	for (row = 1; row <= maxRow; row++) { // For each row
		initSpace = printInitialSpaces(initSpace); // Print and iterate initial spaces
		n = row - 1; // Value of n
		for (r=0; r<=n; r++) { // For all values of r from 0 to n
			num = choose(n, r); // Get value of nCr
			printf("%d", num); // Print the number
			if (r != n) { // If not last number of row
				/*
				if (num >= 100) printSpaces(3);
				else if (num >= 10) printSpaces(4);
				else printSpaces(5);
				 */
				printSpaces(5 - (int)log10(num)); // Print spaces based on number of digits of nCr
			}
		}
		printf("\n"); // Next line
	}
		
}

int choose(int n, int r) {
	int nFact, rFact, nrFact; // Variables for n!, r! and (n-r)!
	nFact = factorial(n); // n!
	rFact = factorial(r); // r!
	nrFact = factorial(n-r); // (n-r)!
	return (nFact/(rFact * nrFact)); // nCr
}

int factorial(int n) {
	int fact;
	for (fact=1; n>0; n--) // For all numbers n,n-1,...,2,1
		fact *= n;
	return fact; // n!
}

int printInitialSpaces(int spaces) {
	for (int i=0; i<spaces; i++) printf(" ");
	spaces -= 3;
	return spaces;
}

// Print number of spaces:
void printSpaces(int spaces) {
	for (int i=0; i<spaces; i++) printf(" ");
}
