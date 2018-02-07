#include <stdio.h>
#include <stdlib.h>

// Declare Functions:
void drawTriangle(int);
int printInitialSpaces(int);
void printMidCharacters(int, char);

int main(int argc, char **argv)
{
	int inputRow; // Variable for user input of rows
	printf("Enter the number of rows in the triangle: ");
	scanf("%d", &inputRow);
	
	drawTriangle(inputRow); // Draw triangle with user's row number
	return 0;
}

void drawTriangle(int maxRow) {
	int row, initSpace;
	initSpace = maxRow - 1;
	
	for (row = 1; row <= maxRow; row++) { // For each row
		initSpace = printInitialSpaces(initSpace); // Print and iterate initial spaces
		printf("^"); // Print first character
		if (row != maxRow) printMidCharacters(row, ' '); // Print spaces if not last row.
		else printMidCharacters(row, '^'); // Print '^'s if last row
		
		if (row == 1) printf("\n"); // Dont print '^' if first row
		else if (row != maxRow) printf("^\n"); // Move to next line
		else printf("^");
	}
}

int printInitialSpaces(int spaces) {
	for (int i=0; i<spaces; i++) printf(" "); // Print initial spaces
	spaces--; // Iterate initial spaces
	return spaces;
}

void printMidCharacters(int row, char letter) {
	int spaces = 2*row - 3; // Formula for middle spaces
	for (int i=0; i<spaces; i++) printf("%c", letter);
}
