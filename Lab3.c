#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declare Functions:
void generateValues(int);
void printValues(int, int, int, int);
char* checkPlural(int);

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
	if (quarters > 0) printf("%d quarter%s, ", quarters, checkPlural(quarters)); // Print number of quarters, if any
	if (dimes > 0) printf("%d dime%s, ", dimes, checkPlural(dimes)); // Print number of dimes, if any
	if (nickels > 0) printf("%d nickel%s, ", nickels, checkPlural(nickels)); // Print number of nickels, if any
	if (cents > 0) printf("%d cent%s, ", cents, checkPlural(cents)); // Print number of cents, if any
	printf("\b\b.\n"); // Conclude sentence by removing extra spaces and commas and adding a full stop
}

char* checkPlural(int value) { //Checks whether to add "s" to make plural or not
	if (value > 1) return "s";
	else return "";
}
