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
	scanf("%d", &n);
	char board[26][26];
	char *ptrBoard = &board[0][0];
	initializeBoard(ptrBoard, n);
	setUpBoard(ptrBoard, n);
	printBoard(board, n);
	printAvailableMoves(board, n, 'W');
	printAvailableMoves(board, n, 'B');
	printf("Enter a move:\n");
	scanf(" %c%c%c", &moveClr, &moveRow, &moveCol);
	if (checkMoveAvailable(board, n, moveRow, moveCol, moveClr)) {
		printf("Valid move.\n");
		performMove(board, ptrBoard, n, moveRow, moveCol, moveClr);
	} else {
		printf("Invalid move.\n");
	}
	printBoard(board, n);
	return 0;
}

void initializeBoard(char *board, int n) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if ((i == (n/2) - 1 || i == n/2) && (j == n/2 || j == (n/2) - 1))
				if (i == j) *(board+ mC*i + j) = 'W';
				else *(board + mC*i + j) = 'B';
			else
				*(board+ mC*i + j) = 'U';
		}
	}
}

void printBoard(char board[26][26], int n) {
	for (int row=-1; row<n; row++) {
		if (row == -1) {
			printf("  ");
			for (int i=0; i<n; i++) printf("%c", i+'a');
			printf("\n");
		} else {
			printf("%c ", row+'a');
			for (int i=0; i<n; i++) printf("%c", board[row][i]);
			printf("\n");
		}
	}
}

void setUpBoard(char *board, int n) {
	bool done = false;
	char cClr, cRow, cClm;
	printf("Enter board configuration:\n");
	while (!done) {
		scanf(" %c%c%c", &cClr, &cRow, &cClm);
		if (cClr == '!' && cRow == '!' && cClm == '!') done = true;
		else {
			cRow -= 'a';
			cClm -= 'a';
			*(board + mC*cRow + cClm) = cClr;
		}
	}
}

void printAvailableMoves(char board[26][26], int n, char clr) {
	printf("Available moves for %c:\n", clr);
	int i, j;
	char row, col;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			row = i+'a';
			col = j+'a';
			if (checkMoveAvailable(board, n, row, col, clr))
				printf("%c%c\n", row, col);
		}
	}
}

bool checkMoveAvailable(char board[26][26], int n, char row, char col, char clr) {
	int i=row-'a';
	int j=col-'a';
	if (clr != 'B' && clr != 'W') return false;
	if (!positionInBounds(n, row, col)) return false;
	if (board[i][j] != 'U') return false;
	bool available = false;
	int dR, dC;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
				if (checkLegalInDirection(board, n, row, col, clr, dR, dC)) {
						available = true;
						break;
				}
			}
		}
		if (available) break;
	}
	return available;
}

bool positionInBounds(int n, char row, char col){
	int i = row - 'a';
	int j = col - 'a';
	if (i>=n || i<0) return false;
	if (j>=n || j<0) return false;
	return true;
}

bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	row -= 'a';
	col -= 'a';
	char antiColour = (colour == 'W')? 'B' : 'W';
	int i, j;
	if (board[row+deltaRow][col+deltaCol] != antiColour) return false;
	bool foundColour = false;
	for (i=row+deltaRow, j=col+deltaCol; ((i+deltaRow<n+1) && (i+deltaRow>=-1)) && ((j+deltaCol)<n+1 && (j+deltaCol>=-1)); i+=deltaRow, j+=deltaCol) {
		if (board[i][j] == colour) {
			foundColour = true;
			break;
		}
	}
	return foundColour;
}

void performMove(char board[26][26], char *ptrBoard, int n, char row, char col, char clr) {
	int i = row - 'a';
	int j = col - 'a';
	int k,m;
	int dR, dC;
	*(ptrBoard + mC*i + j) = clr;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
				if (checkLegalInDirection(board, n, row, col, clr, dR, dC)) {
					for (k=dR, m=dC; true; k+=dR, m+=dC) {
						if (*(ptrBoard + mC*(i+k) + (j+m)) != clr) *(ptrBoard + mC*(i+k) + (j+m)) = clr;
						else break;
					}
				}
			}
		}
	}	
}
