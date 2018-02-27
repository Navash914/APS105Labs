#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define mC 26

void initializeBoard(char*, int);
void printBoard(char[26][26], int);
void setUpBoard(char*, int);
void printAvailableMoves(char[26][26], int, char);
bool checkMoveAvailable(char[26][26], int, char, char, char);
bool positionInBounds(int, char, char);
bool checkLegalInDirection(char[26][26], int, char, char, char, int, int);
void performMove(char[26][26], char*, int, char, char, char);

int main(int argc, char **argv)
{
	int n;
	char moveClr, moveRow, moveCol;
	printf("Enter the board dimension: ");
	scanf("%d", &n); // Dimensions for board.
	char board[26][26];
	char *ptrBoard = &board[0][0];
	initializeBoard(ptrBoard, n); // Set W and B pieces in center
	setUpBoard(ptrBoard, n); // Configuration phase
	printBoard(board, n); // Print board after configuration
	printAvailableMoves(board, n, 'W'); // Available moves for W
	printAvailableMoves(board, n, 'B'); // Available moves for B
	printf("Enter a move:\n");
	scanf(" %c%c%c", &moveClr, &moveRow, &moveCol); // Accept Move Input
	if (checkMoveAvailable(board, n, moveRow, moveCol, moveClr)) { // Check for validity
		// Valid Move:
		printf("Valid move.\n");
		performMove(board, ptrBoard, n, moveRow, moveCol, moveClr);
	} else {
		// Invalid Move:
		printf("Invalid move.\n");
	}
	printBoard(board, n); // Print Final Board
	return 0;
}

// Function for preparing board with Ws and Bs in center and Us everywhere else
void initializeBoard(char *board, int n) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if ((i == (n/2) - 1 || i == n/2) && (j == n/2 || j == (n/2) - 1)) // Center Area
				if (i == j) *(board+ mC*i + j) = 'W';
				else *(board + mC*i + j) = 'B';
			else // Everywhere Else
				*(board+ mC*i + j) = 'U';
		}
	}
}

// Function for printing current board state
void printBoard(char board[26][26], int n) {
	for (int row=-1; row<n; row++) {
		if (row == -1) { // First row prints letters for board coordinates
			printf("  ");
			for (int i=0; i<n; i++) printf("%c", i+'a');
			printf("\n");
		} else { // Print board pieces
			printf("%c ", row+'a');
			for (int i=0; i<n; i++) printf("%c", board[row][i]);
			printf("\n");
		}
	}
}

// Function for configuration of board
void setUpBoard(char *board, int n) {
	bool done = false;
	char clr, row, col;
	printf("Enter board configuration:\n");
	while (!done) {
		scanf(" %c%c%c", &clr, &row, &col);
		if (clr == '!' && row == '!' && col == '!') done = true; // End if !!!
		else {
			row -= 'a';
			col -= 'a';
			*(board + mC*row + col) = clr; // Set board piece
		}
	}
}

// Function for printing available moves for a colour
void printAvailableMoves(char board[26][26], int n, char clr) {
	printf("Available moves for %c:\n", clr);
	int i, j;
	char row, col;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) { // For every point in the board
			row = i+'a';
			col = j+'a';
			if (checkMoveAvailable(board, n, row, col, clr)) // Print row and col if move available
				printf("%c%c\n", row, col);
		}
	}
}

// Function for checking validity of any given move
bool checkMoveAvailable(char board[26][26], int n, char row, char col, char clr) {
	int i=row-'a';
	int j=col-'a';
	if (clr != 'B' && clr != 'W') return false; // False if incorrect colour
	if (!positionInBounds(n, row, col)) return false; // False if out of bounds
	if (board[i][j] != 'U') return false; // False if position is not empty
	bool available = false;
	int dR, dC;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) { // For all directions
			if (!(dR == 0 && dC == 0)) { // Skip for direction 0,0
				if (checkLegalInDirection(board, n, row, col, clr, dR, dC)) { // Checks legal in given direction
					// Move is valid at this point
					available = true;
					break;
				}
			}
		}
		if (available) break;
	}
	return available;
}

// Function to check if position is within board dimensions
bool positionInBounds(int n, char row, char col) {
	int i = row - 'a';
	int j = col - 'a';
	if (i>=n || i<0) return false; // False for incorrect row
	if (j>=n || j<0) return false; // False for incorrect column
	return true; // True at this point
}

// Function for checking if move is legal in a given direction
bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	row -= 'a';
	col -= 'a';
	char antiColour = (colour == 'W')? 'B' : 'W'; // Opposite colour
	int i, j;
	if (board[row+deltaRow][col+deltaCol] != antiColour) return false; // False if immediate piece is not opposite colour
	bool foundColour = false;
	//for (i=row+deltaRow, j=col+deltaCol; ((i+deltaRow<n+1) && (i+deltaRow>=-1)) && ((j+deltaCol)<n+1 && (j+deltaCol>=-1)); i+=deltaRow, j+=deltaCol) { // Loop till next position is out of bounds
	for (i=row+deltaRow, j=col+deltaCol; positionInBounds(n, i+'a', j+'a'); i+=deltaRow, j+=deltaCol) { // Loop till position is out of bounds
		if (board[i][j] == colour) { // True if colour is found in the line
			foundColour = true;
			break;
		} else if (board[i][j] == 'U') { // False if U found before colour
			foundColour = false;
			break;
		}
	}
	return foundColour;
}

// Function for performing a given move. The move in this function is already valid.
void performMove(char board[26][26], char *ptrBoard, int n, char row, char col, char clr) {
	int i = row - 'a';
	int j = col - 'a';
	int k,m;
	int dR, dC;
	*(ptrBoard + mC*i + j) = clr;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) { // For all directions.
			if (!(dR == 0 && dC == 0)) { // Skip for direction 0,0
				if (checkLegalInDirection(board, n, row, col, clr, dR, dC)) {
					// Pieces can be flipped in this direction.
					for (k=dR, m=dC; true; k+=dR, m+=dC) { // Keep flipping pieces
						if (*(ptrBoard + mC*(i+k) + (j+m)) != clr) *(ptrBoard + mC*(i+k) + (j+m)) = clr;
						else break; // End when clr is found
					}
				}
			}
		}
	}	
}
