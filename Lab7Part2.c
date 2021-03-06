/*
 *
 * Lab7Part2.c
 *
 * AI for Reversi/Othello.
 * Uses a simplified minimax algorithm to make
 * intelligent moves.
 *
 * Author: Naveed Ashfaq
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

void initializeBoard(char[26][26], int);
void printBoard(char[26][26], int);
void playCpuTurn(char[26][26], int, char, bool);
void playPlayerTurn(char[26][26], int, char, bool);
bool checkMoveAvailable(char[26][26], int, char, char, char);
bool positionInBounds(int, char, char);
bool checkLegalInDirection(char[26][26], int, char, char, char, int, int);
void performMove(char[26][26], int, char, char, char);
int performDummyMove(char[26][26], int, char, char, char);
bool checkEndGame(char[26][26], int);
void endGame(char[26][26], int);
void forceEndGame(char);
bool anyMoveAvailable(char[26][26], int, char);
void createCopyBoard(char[26][26], char[26][26], int);
void findBestMove(char[26][26], int, char, char*, char*);
int findTotalScore(char[26][26], int, char, char, char);
int weakBias(int);
int strongBias(char[26][26], int);
bool pointInCorner(int, int, int);
bool pointInEdge(int, int, int);
bool pointInRisk(int, int ,int);
int mobilityScore(char[26][26], int, char, char, char);
int remainingTiles(char[26][26], int);
bool riskCornerTaken(char[26][26], int, int, int ,char);
char getAntiClr(char);
bool bothPlayersMovesAvailable(char[26][26], int);


int main(int argc, char **argv)
{
	int n;
	char cpuClr, playerClr;
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	char board[26][26];
	initializeBoard(board, n);
	printf("Computer plays (B/W) : ");
	scanf(" %c", &cpuClr);
	playerClr = (cpuClr == 'B')? 'W' : 'B';
	printBoard(board, n);
	if (cpuClr == 'B') playCpuTurn(board, n, cpuClr, false);
	else playPlayerTurn(board, n, playerClr, false);
	return 0;
}

void initializeBoard(char board[26][26], int n) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if ((i == (n/2) - 1 || i == n/2) && (j == n/2 || j == (n/2) - 1))
				if (i == j) board[i][j] = 'W';
				else board[i][j] = 'B';
			else
				board[i][j] = 'U';
		}
	}
}

void printBoard(char board[26][26], int n) {
	HANDLE  hConsole;
    int c;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	char letter;
	for (int row=-1; row<n; row++) {
		if (row == -1) {
			printf("  ");
			for (int i=0; i<n; i++) printf("%c ", i+'a');
			printf("\n");
		} else {
			printf("%c ", row+'a');
			for (int i=0; i<n; i++) {
				letter = board[row][i];
				if (letter == 'W') c = 10; // Green
				else if (letter == 'B') c = 12; // Red
				else c = 15; // White
				SetConsoleTextAttribute(hConsole, c);
				printf("%c ", board[row][i]);
				c = 7; // Normal
				SetConsoleTextAttribute(hConsole, c);
			}
			printf("\n");
		}
	}
}

void playCpuTurn(char board[26][26], int n, char clr, bool passed) {
	char antiClr = getAntiClr(clr);
	bool movesAvailable = anyMoveAvailable(board, n, clr);
	
	if (movesAvailable) {
		char moveRow, moveCol;
		char *ptrRow, *ptrCol;
		ptrRow = &moveRow;
		ptrCol = &moveCol;
		findBestMove(board, n, clr, ptrRow, ptrCol);
		printf("Computer places %c at %c%c.\n", clr, moveRow, moveCol);
		performMove(board, n, moveRow, moveCol, clr);
		printBoard(board, n);
		return playPlayerTurn(board, n, antiClr, false);
	} else {
		if (checkEndGame(board, n)) return endGame(board, n);
		printf("%c player has no valid move.\n", clr);
		if (passed) return endGame(board, n);
		else return playPlayerTurn(board, n, antiClr, true);
	}
}

void createCopyBoard(char copy[26][26], char origin[26][26], int n) {
	int i,j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			copy[i][j] = origin[i][j];
		}
	}
}

bool anyMoveAvailable(char board[26][26], int n, char clr) {
	int i, j;
	char row, col;
	bool movesAvailable = false;
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
	return movesAvailable;
}


int findTotalScore(char board[26][26], int n, char row, char col, char clr) {
	int score, tempScore, maxScore = -9999;
	score = performDummyMove(board, n, row, col, clr);
	int i = row-'a', j = col-'a';
	if (pointInCorner(n, i, j)) score += strongBias(board, n);
	if (pointInEdge(n, i, j)) score += weakBias(n);
	if (pointInRisk(n, i, j)) score -= weakBias(n);
	performMove(board, n, row, col, clr);
	clr = getAntiClr(clr);
	bool cpuTurn = false;
	char moveRow, moveCol;
	
	while (bothPlayersMovesAvailable(board, n) && !checkEndGame(board, n)) {
		if (anyMoveAvailable(board, n, clr)) {
			for (i=0; i<n; i++) {
				for (j=0; j<n; j++) {
					row = i + 'a';
					col = j + 'a';
					if (checkMoveAvailable(board, n, row, col, clr)) {
						tempScore = performDummyMove(board, n, row, col, clr);
						if (pointInCorner(n, i, j)) tempScore += strongBias(board, n);
						if (pointInEdge(n, i, j)) tempScore += weakBias(n);
						if (pointInRisk(n, i, j)) {
							if (!riskCornerTaken(board, n, i, j, clr)) tempScore -= weakBias(n);
						}
						// UNCOMMENT BELOW TO INCLUDE PLAYER'S AVAILABLE MOVES INTO CONSIDERATION.
						//moveScore = mobilityScore(board, n, row, col, clr);
						//if (moveScore <= 0) tempScore += strongBias(board, n);
						//else tempScore -= moveScore;
						if (tempScore > maxScore) {
							maxScore = tempScore;
							moveRow = i;
							moveCol = j;
						}
					}
				}
			}
			performMove(board, n, moveRow, moveCol, clr);
			if (cpuTurn) score += maxScore;
			else score -= maxScore;
		} else {
			if (cpuTurn) score -= strongBias(board, n);
			else score += strongBias(board, n);
		}
		cpuTurn = !cpuTurn;
		maxScore = -9999;
		clr = getAntiClr(clr);
	}
	return score;
}

char getAntiClr(char clr) {
	if (clr == 'W') return 'B';
	else return 'W';
}

bool bothPlayersMovesAvailable(char board[26][26], int n) {
	if (anyMoveAvailable(board, n, 'W') && anyMoveAvailable(board, n, 'B')) return true;
	else return false;
}

void findBestMove(char board[26][26], int n, char clr, char *r, char *c) {
	char cpyBoard[26][26];
	int score, maxScore = -9999;
	char moveRow, moveCol;
	char row, col;
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			row = i + 'a';
			col = j + 'a';
			if (checkMoveAvailable(board, n, row, col, clr)) {
				createCopyBoard(cpyBoard, board, n);
				score = findTotalScore(cpyBoard, n, row, col, clr);
				if (score > maxScore) {
					maxScore = score;
					moveRow = row;
					moveCol = col;
				}
			}
		}
	}
	*r = moveRow;
	*c = moveCol;
}

int performDummyMove(char board[26][26], int n, char row, char col, char clr) {
	int count = 1;
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
						if (board[i+k][j+m] != clr) count++;
						else break;
					}
				}
			}
		}
	}
	return count;
}

void playPlayerTurn(char board[26][26], int n, char clr, bool passed) {
	char antiClr = getAntiClr(clr);
	char moveRow, moveCol;
	bool movesAvailable = false;
	
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
		printf("Enter move for colour %c (RowCol): ", clr);
		scanf(" %c%c", &moveRow, &moveCol);
	
		if (checkMoveAvailable(board, n, moveRow, moveCol, clr)) {
			performMove(board, n, moveRow, moveCol, clr);
			printBoard(board, n);
			return playCpuTurn(board, n, antiClr, false);
		} else {
			printf("Invalid move.\n");
			return forceEndGame(antiClr);
		}
	} else {
		if (checkEndGame(board, n)) return endGame(board, n);
		printf("%c player has no valid move.\n", clr);
		if (passed) return endGame(board, n);
		else return playCpuTurn(board, n, antiClr, true);
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
	if (!positionInBounds(n, row+deltaRow, col+deltaCol)) return false;
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
		} else if (board[i][j] == 'U') {
			foundColour = false;
			break;
		}
	}
	return foundColour;
}

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

bool checkEndGame(char board[26][26], int n) {
	int i,j;
	bool over = true;
	for (i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if (board[i][j] == 'U') {
				over = false;
				break;
			}
		}
		if (!over) break;
	}
	return over;
}

void endGame(char board[26][26], int n) {
	int wPts=0, bPts=0;
	int i,j;
	
	for (i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if (board[i][j] == 'W') wPts++;
			else if (board[i][j] == 'B') bPts++;
		}
	}
	
	if (wPts > bPts) printf("W player wins.");
	else if (bPts > wPts) printf("B player wins.");
	else printf("Draw!");
}

void forceEndGame(char clr) {
	printf("%c player wins", clr);
}

int weakBias(int n) {
	return n/2;
}

int strongBias(char board[26][26], int n) {
	int tilesRemain = remainingTiles(board, n);
	tilesRemain *= 100;
	tilesRemain /= n*n;
	n *= (tilesRemain > 75)? 2 : 1;
	return n;
}

bool pointInCorner(int n, int row, int col) {
	if (row == 0 && col == 0) return true;
	if (row == 0 && col == n-1) return true;
	if (row == n-1 && col == 0) return true;
	if (row == n-1 && col == n-1) return true;
	return false;
}

bool pointInEdge(int n, int row, int col) {
	if (row == 0 && col > 1 && col < n-2) return true;
	if (row > 1 && row < n-2 && col == 0) return true;
	if (row == n-1 && col > 1 && col < n-2) return true;
	if (row > 1 && row < n-2 && col == n-1) return true;
	return false;
}

bool pointInRisk(int n, int row, int col) {
	if (row == 0 && (col == 1 || col == n-2)) return true;
	if (row == 1 && (col < 2 || col > n-3)) return true;
	if (row == n-2 && (col < 2 || col > n-3)) return true;
	if (row == n-1 && (col == 1 || col == n-2)) return true;
	return false;
}

int mobilityScore(char board[26][26], int n, char row, char col, char clr) {
	char antiClr = getAntiClr(clr);
	char copyBoard[26][26];
	createCopyBoard(copyBoard, board, n);
	performMove(copyBoard, n, row, col, clr);
	int i, j;
	char r, c;
	int count=0;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			r = i+'a';
			c = j+'a';
			if (checkMoveAvailable(copyBoard, n, r, c, antiClr)) {
				if (pointInCorner(n, i, j)) count += strongBias(copyBoard, n);
				else if (pointInEdge(n, i, j)) count += weakBias(n);
				else if (pointInRisk(n, i, j)) count -= weakBias(n);
				else count++;
			}
		}
	}
	return count;
}

int remainingTiles(char board[26][26], int n) {
	int i, j;
	int count = 0;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			if (board[i][j] == 'U') count++;
		}
	}
	return count;
}

bool riskCornerTaken(char board[26][26], int n, int row, int col, char clr) {
	if (row == 0 && col == 1) { // Top Left Corner
		if (board[0][0] == clr) return true;
		else return false;
	}
	if (row == 0 && col == n-2) { // Top Right Corner
		if (board[0][n-1] == clr) return true;
		else return false;
	}
	if (row == 1 && col < 2) { // Top Left Corner
		if (board[0][0] == clr) return true;
		else return false;
	}
	if (row == 1 && col > n-3) { // Top Right Corner
		if (board[0][n-1] == clr) return true;
		else return false;
	}
	if (row == n-2 && col < 2) { // Bottom Left Corner
		if (board[n-1][0] == clr) return true;
		else return false;
	}
	if (row == n-2 && col > n-3) { // Bottom Right Corner
		if (board[n-1][n-1] == clr) return true;
		else return false;
	}
	if (row == n-1 && col == 1) { // Bottom Left Corner
		if (board[n-1][0] == clr) return true;
		else return false;
	}
	if (row == n-1 && col == n-2) { // Bottom Right Corner
		if (board[n-1][n-1] == clr) return true;
		else return false;
	}
	return false;
}
