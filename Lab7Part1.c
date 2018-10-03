/*
 *
 * Lab7Part1.c
 *
 * AI for Reversi/Othello.
 * This is the simple AI implementation where the
 * computer plays the move with the most points.
 *
 * Author: Naveed Ashfaq
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define mC 26

void initializeBoard(char[26][26], int);
void printBoard(char[26][26], int);
void playCpuTurn(char[26][26], int, char, bool);
void playPlayerTurn(char[26][26], int, char, bool);
bool checkMoveAvailable(char[26][26], int, char, char, char);
bool positionInBounds(int, char, char);
bool checkLegalInDirection(char[26][26], int, char, char, char, int, int);
void performMove(char[26][26], int, char, char, char);
int performDummyMove(char[26][26], int, char, char, char);
char getAntiClr(char);
bool checkEndGame(char[26][26], int);
void endGame(char[26][26], int);
void forceEndGame(char);

int main(int argc, char **argv)
{
	int n;
	char cpuClr, playerClr;
	printf("Enter the board dimension: ");
	scanf("%d", &n); // Dimensions for board.
	char board[26][26];
	initializeBoard(board, n); // Set up initial center pieces.
	printf("Computer plays (B/W) : ");
	scanf(" %c", &cpuClr); // Computer color.
	playerClr = getAntiClr(cpuClr);
	printBoard(board, n);
	// Start turn with B:
	if (cpuClr == 'B') playCpuTurn(board, n, cpuClr, false);
	else playPlayerTurn(board, n, playerClr, false);
	
	return 0;
}

// Function for preparing board with Ws and Bs in center and Us everywhere else
void initializeBoard(char board[26][26], int n) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if ((i == (n/2) - 1 || i == n/2) && (j == n/2 || j == (n/2) - 1)) // Center Area
				if (i == j) board[i][j] = 'W';
				else board[i][j] = 'B';
			else // Everywhere else
				board[i][j] = 'U';
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

// Function for processing the computer's turn
void playCpuTurn(char board[26][26], int n, char clr, bool passed) {
	int score = 0, maxScore = 0;
	char antiClr = (clr == 'B')? 'W' : 'B';
	char moveRow, moveCol;
	bool movesAvailable = false;
	
	int i,j;
	char row, col;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			row = i + 'a';
			col = j + 'a';
			if (checkMoveAvailable(board, n, row, col, clr)) { // If move is available
				movesAvailable = true;
				score = performDummyMove(board, n, row, col, clr); // Get score for move
				if (score > maxScore) { // If greater than previous max score
				maxScore = score; // Update max score
				// Store move row and col:
				moveRow = row;
				moveCol = col;
				}
			}
		}
	}
	
	if (movesAvailable) { // If at least one move available
		printf("Computer places %c at %c%c.\n", clr, moveRow, moveCol);
		performMove(board, n, moveRow, moveCol, clr); // Perform move
		printBoard(board, n);
		return playPlayerTurn(board, n, antiClr, false); // Switch to player turn with successful move
	} else {
		if (checkEndGame(board, n)) return endGame(board, n); // End game if board is full
		printf("%c player has no valid move.\n", clr); // No valid moves
		if (passed) return endGame(board, n); // End game if previous player move was unsuccesful
		else return playPlayerTurn(board, n, antiClr, true); // Switch to player turn with unsuccessful move
	}
}

// Function for getting score of move
int performDummyMove(char board[26][26], int n, char row, char col, char clr) {
	int count=0;
	int i = row - 'a';
	int j = col - 'a';
	int dR, dC;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
				if (checkLegalInDirection(board, n, row, col, clr, dR, dC)) {
					for (int k=0, m=0; true; k+=dR, m+=dC) {
						if (board[i+k][j+m] != clr) count++;
						else break;
					}
				}
			}
		}
	}
	return count;
}

// Function for handling player move
void playPlayerTurn(char board[26][26], int n, char clr, bool passed) {
	char antiClr = (clr == 'B')? 'W' : 'B';
	char moveRow, moveCol;
	bool movesAvailable = false;
	
	// Check if any valid move is available:
	int i, j;
	char row, col;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			row = i+'a';
			col = j+'a';
			if (checkMoveAvailable(board, n, row, col, clr)) {
				movesAvailable = true;
				break;
			}
		}
		if (movesAvailable) break;
	}
	
	if (movesAvailable) {
		// At least one valid move is available
		printf("Enter move for colour %c (RowCol): ", clr);
		scanf(" %c%c", &moveRow, &moveCol);
	
		if (checkMoveAvailable(board, n, moveRow, moveCol, clr)) { // Check if input move is valid
			performMove(board, n, moveRow, moveCol, clr); // Perform the move
			printBoard(board, n);
			return playCpuTurn(board, n, antiClr, false); // Switch to computer turn with successful move
		} else {
			printf("Invalid move.\n"); // Move is invalid
			return forceEndGame(antiClr); // Force end game and give computer the win
		}
	} else {
		// No moves are available
		if (checkEndGame(board, n)) return endGame(board, n); // End game if board is full
		printf("%c player has no valid move.\n", clr); // No moves available for player
		if (passed) return endGame(board, n); // End game if previous player's move was unsuccessful
		else return playCpuTurn(board, n, antiClr, true); // Switch to computer turn with unsuccessful move
	}
}

// Function for checking validity of any given move
bool checkMoveAvailable(char board[26][26], int n, char row, char col, char clr) {
	int i=row-'a';
	int j=col-'a';
	if (clr != 'B' && clr != 'W') return false;// False if incorrect colour
	if (!positionInBounds(n, row, col)) return false; // False if out of bounds
	if (board[i][j] != 'U') return false; // False if position is not empty
	bool available = false;
	int dR, dC;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
				if (checkLegalInDirection(board, n, row, col, clr, dR, dC)) {
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
bool positionInBounds(int n, char row, char col){
	int i = row - 'a';
	int j = col - 'a';
	if (i>=n || i<0) return false;
	if (j>=n || j<0) return false;
	return true;
}

// Function for checking if move is legal in a given direction
bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	if (!positionInBounds(n, row+deltaRow, col+deltaCol)) return false;
	row -= 'a';
	col -= 'a';
	char antiColour = getAntiClr(colour); // Opposite colour
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
void performMove(char board[26][26], int n, char row, char col, char clr) {
	int i = row - 'a';
	int j = col - 'a';
	int k,m;
	int dR, dC;
	board[i][j] = clr;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
				if (checkLegalInDirection(board, n, row, col, clr, dR, dC)) {
					for (k=dR, m=dC; true; k+=dR, m+=dC) {
						if (board[i+k][j+m] != clr) board[i+k][j+m] = clr;
						else break;
					}
				}
			}
		}
	}	
}

// Get opponent's colour:
char getAntiClr(char clr) {
	if (clr == 'W') return 'B';
	else return 'W';
}

// Check if board is full signalling the end of the game
bool checkEndGame(char board[26][26], int n) {
	int i,j;
	bool over = true;
	for (i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if (board[i][j] == 'U') {
				// At least one space is empty, so board is not full
				over = false;
				break;
			}
		}
		if (!over) break;
	}
	return over;
}

// Function for ending the game and declaring the winner
void endGame(char board[26][26], int n) {
	int wPts=0, bPts=0;
	int i,j;
	
	for (i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if (board[i][j] == 'W') wPts++; // Points for W
			else if (board[i][j] == 'B') bPts++; // Points for B
		}
	}
	
	// Declare winner
	if (wPts > bPts) printf("W player wins.");
	else if (bPts > wPts) printf("B player wins.");
	else printf("Draw!");
}

// Function for forcing the end of the game with a predefined winner
void forceEndGame(char clr) {
	printf("%c player wins", clr);
}
