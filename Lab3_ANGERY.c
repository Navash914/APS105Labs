#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declare Functions:
void generateValues(int);
void printValues(int, int, int, int);

int main(int argc, char **argv)
{
	// Declare Variables:
	int inputNum;
	bool finished=false;
	
	while (!finished) { // Loop while finished is false
		// Prompt User Input:
		printf("Please give an amount in cents less than 100: ");
		scanf("%d", &inputNum); // User Input
	
		if (inputNum < 1 || inputNum > 99) finished = true; // End Loop Operation
		else generateValues(inputNum); // Carry out calculations, then loop again
	}
	
	printf("Goodbye."); // End of program
	return 0;
}

void generateValues(int inputNum) {
	int quarters = 0, dimes = 0, nickels = 0, cents = 0; // Initialize values
	printf("%d cents: ", inputNum); // Print user number
	
	while (inputNum > 0) { // Loop while change remains
		if (inputNum >= 25) { // Quarter addition possible
			quarters++;
			inputNum -= 25;
		} else if (inputNum >= 10) { // Dime addition possible
			dimes++;
			inputNum -=10;
		} else if (inputNum >= 5) { // Nickel addition possible
			nickels++;
			inputNum -= 5;
		} else { // Cent addition possible
			cents++;
			inputNum--;
		}
	} // End of Loop
	
	printValues(quarters, dimes, nickels, cents); // Print out output
}

void printValues(int quarters, int dimes, int nickels, int cents) {
	if (quarters > 0) { // Print number of quarters, if any
		printf("%d %s", quarters, (quarters>1)? "quarters" : "quarter");
		
		// Check if any output after quarters:
		if (dimes == 0 && nickels == 0 && cents == 0)
			printf(".\n");
		else
			printf(", ");
	}
	
	if (dimes > 0) { // Print number of dimes, if any
		printf("%d %s", dimes, (dimes>1)? "dimes" : "dime");
		
		// Check if any output after dimes:
		if (nickels == 0 && cents == 0)
			printf(".\n");
		else
			printf(", ");
	}
	
	if (nickels > 0) { // Print number of nickels, if any
		printf("%d %s", nickels, (nickels>1)? "nickels" : "nickel");
		
		// Check if any output after nickels:
		if (cents == 0)
			printf(".\n");
		else
			printf(", ");
	}
	
	if (cents > 0) // Print number of cents, if any
		printf("%d %s.", cents, (cents>1)? "cents" : "cent");
	
	printf("\n"); // Conclude output by moving to next line.
}
