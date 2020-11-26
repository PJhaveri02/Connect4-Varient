/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
Name : Pranay Jhaveri     ID: 337019163
This is the file that you will be submitting for marking
Complete the definitions of the functions in this file
DO NOT REMOVE ANY FUNCTION DEFINITIONS - they all must be present when you submit this file
*/

int SecondPlacePrize(int prize1, int prize2, int prize3)
{	// This function takes in three integers and outputs the middle value
	
	if (((prize1 >= prize2) && (prize1 <= prize3)) || ((prize1 <= prize2) && (prize1 >= prize3))) {
		return prize1;
	} else if (((prize2 >= prize1) && (prize2 <= prize3)) || ((prize2 <= prize1) && (prize2 >= prize3))) {
		return prize2;
	} else if (((prize3 >= prize1) && (prize3 <= prize2)) || ((prize3 <= prize1) && (prize3 >= prize2)))  {
		return prize3;
	}
	
	return 0;
}

int FourInARow(int values[], int length)
{ // This function finds the first postion of an integer which is in 4 in a row
	
	for (int i = 0; i < length; i++) {
		if (length < 4) {
			return -1;
		}
		// This statement finds whether there is a four in a row and makes sure that array is not exceeded
		if ((values[i] == values[i+1]) && (values[i] == values[i+2]) && (values[i] == values[i+3]) && (i+3 < length)) {
		return i;
		}
	}
	
	return -1;
}

int BinaryToDecimal(int binary)
{ // This function converts a binary value to a decimal value
	
	int initialBase = 1; 
	int decimal = 0;
	
	while (binary != 0) {
		int remaining = (binary % 10);
		decimal += (remaining * initialBase);
		binary /= 10; // divide by 10 as decimal is base 10
		initialBase *= 2;
	}
	return decimal;
}

double MedianAbility(double abilities[], int length)
{ // This function finds the median value in an array
	
	int position = length/2;
	
	// sorting array from lowest to highest
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length-1; j++) {
			if (abilities[j] > abilities[j+1]) {
				double saveValue = abilities[j];
				abilities[j] = abilities[j+1];
				abilities[j+1] = saveValue;
			}
		}
	}
	
	// Checking whether the length is even or odd and returning median
	if ((length % 2) > 0) {
		return abilities[position];
	} else {
		double median = ((abilities[position] + abilities[position - 1])/2);
		return median;
	}

}

void RemoveSpaces(char *name)
{ // This function removes the unnecessary spaces between words
	int length = strlen(name);
	int j;
	
	for (int i = 0; i < length; i++) {
		if ((name[i] == ' ') && (name[i+1] == ' ')) {
			
			// shifting the array to the right by one
			for (j = i; j < length-1; j++) {
				name[j] = name[j+1];
			}
			name[j] = '\0';
			length--;
			i--;
		}
	
	}
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{ // This function creates a connect four board with fixed positions
	int i, j;
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	} 
	
	
	// checking whether the size of the board is even and placing fixed positions 
	if ((size % 2) > 0) {
		board[size/2][size/2] = 3;
	} else {
		for (i = (size/2); i >= (size/2-1); i--) {
			for (j = (size/2); j >= (size/2-1); j--) {
				board[i][j] = 3;
			}
				
		}
	}
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{ // This function places the "token" on the board based on the persons move and side they have chosen
	int i;

	if ((side == 'N') && (board[0][move] == 0)) {
		i = 0;
		while ((board[i][move] == 0) && (i < size)) {
			i++;
		}
		board[i-1][move] = player;
		*lastRow = i-1;
		*lastCol = move;
	
	} else if ((side == 'E') && (board[move][size-1] == 0)) {
		i = size-1;
		while ((board[move][i] == 0) && (i >= 0)) {
			i--;
		}
		board[move][i+1] = player;
		*lastRow = move;
		*lastCol = i+1;
	
	} else if ((side == 'S') && (board[size-1][move] == 0)) {
		i = size-1;
		while ((board[i][move] == 0) && (i >= 0)) {
			i--;
		}
		board[i+1][move] = player;
		*lastRow = i+1;
		*lastCol = move;
		
	} else if ((side == 'W') && (board[move][0] == 0)) {
		i = 0;
		while ((board[move][i] == 0) && (i < size)) {
			i++;
		}
		board[move][i-1] = player;
		*lastRow = move;
		*lastCol = i-1;
	} else {
		*lastRow = -1;
		*lastCol = -1;	
	}
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{	// This function checks whether a four in a row is achieved
	
	int count = 0;
	int i, j;
	
	/* Checking whether a four in a row is achieved either horizontally (first two statements), 
	   Vertically (statements 3-4) or diagonally. The if statements within if statements check
	   that values are being are within the array/board*/
	if ((board[row][col+1] == player) && (board[row][col+2] == player)) {
		if ((col+3 < size) && (board[row][col+3] == player)) {
			return player;
		} else if ((col-1 >= 0) && (col+2 < size) && (board[row][col-1] == player)) {
			return player;
		}
		
	} else if ((board[row][col-1] == player) && (board[row][col-2] == player)) {
		if ((col-3 >= 0) && (board[row][col-3] == player)) {
			return player;
		} else if ((col+1 < size) && (col-2 >= 0) && (board[row][col+1] == player)) {
			return player;
		}
	
	} else if ((board[row+1][col] == player) && (board[row+2][col] == player)) {
		if ((row+3 < size) && (board[row+3][col] == player)) {
			return player;
		} else if ((row-1 >= 0) && (row+2 < size) && (board[row-1][col] == player)) {
			return player;
		}
	
	} else if ((board[row-1][col] == player) && (board[row-2][col] == player)) {
		if ((row-3 >= 0) && (board[row-3][col] == player)) {
			return player;
		} else if ((row+1 < size) && (row-2 >= 0) && (board[row+1][col] == player)) {
			return player;
		}
	
	} else if ((board[row+1][col+1] == player) && (board[row+2][col+2] == player)) {
		if ((row+3 < size) && (col+3 < size) && (board[row+3][col+3] == player)) {
			return player;
		} else if ((row-1 >= 0) && (col-1 >= 0) && (col+2 < size) && (row+2 < size) && (board[row-1][col-1] == player)) {
			return player;
		}
	
	} else if ((board[row-1][col-1] == player) && (board[row-2][col-2] == player)) {
		if ((row+1 < size) && (col+1 < size) && (col-2 >= 0) && (row-2 >= 0) && (board[row+1][col+1] == player)) {
			return player;
		} else if ((row-3 >= 0) && (col-3 >= 0) && (board[row-3][col-3] == player)) {
			return player;
		}
	
	} if ((board[row-1][col+1] == player) && (board[row-2][col+2] == player)) {
		if ((row+1 < size) && (col-1 >= 0) && (col+2 < size) && (row-2 >= 0) && (board[row+1][col-1] == player)) {
			return player;
		} else if ((row-3 >= 0) && (col+3 < size) && (board[row-3][col+3] == player)) {
			return player;
		}
	
	} 
	
	if ((board[row+1][col-1] == player) && (board[row+2][col-2] == player)) {
		if ((board[row+3][col-3] == player) && (row+3 < size) && (col-3 >= 0)) {
			return player;
		} else if ((board[row-1][col+1] == player) && (row-1 >= 0) && (col+1 < size)) {
			return player;
		}
	}
	
	/* Checking if there is no space left on the board and returning the player
	that placed the last "token" */
	for (i = 0; i < size; (i += (size-1))) {
		for (j = 0; j < size; j++) {
			if (board[i][j] != 0) {
				count++;
			}			
	
		}
	}
	
	for (i = 0; i < size; (i += (size-1))) {
		for (j = 0; j < size; j++) {
			if (board[j][i] != 0) {
				count++;
			}
			if (count == (size*4)) {
				return player;
			}			
		}
	}
	
	return 0;
}

int findBoard(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString, int i, int j);
void boardComplete(int size, char *boardString, int i);

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{ /* This function creates a formated string representation of the connect 4 board
	for the user to play*/
	int i = 2;
	
	boardString[0] = '-';
	boardString[1] = '-';
	boardString[i] = 'N';
	
	while (i < (size + 1)) {
		i++;
		boardString[i] = 'N';
	}
	
	boardString[i+1] = '-';
	boardString[i+2] = '-';
	boardString[i+3] = '\n';
	boardString[i+4] = '-';
    boardString[i+5] = '-';
	i += 5;
	
	// The for loop below adds the column number to the string
	for (int j = 0; j < size; j++) {
		i++;
		boardString[i] = '0'+(char)j;
	}
	
	boardString[i+1] = '-';
	boardString[i+2] = '-';
	boardString[i+3] = '\n';
	boardString[i+4] = 'W';
    boardString[i+5] = '0';
	i += 6;
	int l = 0;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '0';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n';
	boardString[i+4] = 'W';
    boardString[i+5] = '1';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '1';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n';
	boardString[i+4] = 'W';
    boardString[i+5] = '2';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '2';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n';
	boardString[i+4] = 'W';
    boardString[i+5] = '3';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '3';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n'; // 4 by 4 board
	
	if (size == 4) {
		boardComplete(size, boardString, i);
		return;
	}
	boardString[i+4] = 'W';
    boardString[i+5] = '4';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '4';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n'; // 5 by 5 board
	if (size == 5) {
		boardComplete(size, boardString, i);
		return;
	}
	boardString[i+4] = 'W';
    boardString[i+5] = '5';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '5';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n'; // 6 by 6 board
	if (size == 6) {
		boardComplete(size, boardString, i);
		return;
	}
	boardString[i+4] = 'W';
    boardString[i+5] = '6';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '6';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n'; // 7 by 7 board
	if (size == 7) {
		boardComplete(size, boardString, i);
		return;
	}
	boardString[i+4] = 'W';
    boardString[i+5] = '7';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '7';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n'; // 8 by 8 board
	if (size == 8) {
		boardComplete(size, boardString, i);
		return;
	}
	boardString[i+4] = 'W';
    boardString[i+5] = '8';
	i += 6;
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '8';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n'; // 9 by 9 board
	if (size == 9) {
		boardComplete(size, boardString, i);
		return;
	}
	boardString[i+4] = 'W';
    boardString[i+5] = '9';
	i += 6;
	
	
	i = findBoard(board, size, boardString, i, l);
	l++;
	boardString[i+1] = '9';
	boardString[i+2] = 'E';
	boardString[i+3] = '\n'; // 10 by 10
	if (size == 10) {
		boardComplete(size, boardString, i);
		return;
	}
	
}


int findBoard(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString, int i, int j)
{	/* This helper function helps to place the correct characters in the array based on current board
	   based on the current board configuration*/
	int k = 0;
	size += (i);
	
	for (i; i < size; i++) {
		if (board[j][k] == 0) {
			boardString[i] = '.';
		} if (board[j][k] == 1) {
			boardString[i] = 'X';
		} if (board[j][k] == 2) {
			boardString[i] = 'O';
		} if (board[j][k] == 3) {
			boardString[i] = '#';
	    }
		
		k++;
		
	}
	i--;
	return i;
	
}

void boardComplete(int size, char *boardString, int i) 
{	/* This helper function helps to complete the characterised board based on 
		its size by creating the last 2 rows in the string */

	boardString[i+4] = '-';
	boardString[i+5] = '-';
	i += 5;
		for (int j = 0; j < size; j++) {
			i++;
			boardString[i] = '0'+(char)j;
		}
		boardString[i+1] = '-';
		boardString[i+2] = '-';
		boardString[i+3] = '\n';
		boardString[i+4] = '-';
		boardString[i+5] = '-';
		size += (i+6);
		i += 6;
		while (i < (size)) {
			boardString[i] = 'S';
			i++;
		}
		i--;
		boardString[i+1] = '-';
		boardString[i+2] = '-';
		boardString[i+3] = '\n';
		boardString[i+4] = '\0';
	
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{ // This function creates a move for Bot 1 
	
	int i, j;
	int row, col;
	int place;
	int array[MAX_SIZE][MAX_SIZE];
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			array[i][j] = board[i][j];
		}
	}
	

	/* The following for loops below checks whether a winning move can be made
		by the bot. It does this by checking each possible legal move that can be made*/
	i = 0;
	for (j = 0; j < size; j++) {
			while ((array[i][j] == 0) && (i < size)) {
				i++;
			}
			i--;
			if (array[0][j] == 0) {
				row = i;
				col = j;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col); // Checks if bot can win in next move
				array[row][col] = 0; // resetting the "array"
				i = 0;
				if (place > 0) {
					*side = 'N';
					*move = col;
					return;
				}
			} else {
				i = 0;
			}
	}
	
	i = size-1;
	for (j = 0; j < size; j++) {
			while ((array[j][i] == 0) && (i >= 0)) {
				i--;
			}
			i++;
			if (array[j][size-1] == 0) {
				row = j;
				col = i;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col);
				array[row][col] = 0;
				i = size-1;
				if (place > 0) {
					*side = 'E';
					*move = row;
					return;
				}
			} else {
				i = size-1;
			}			
	}
	
	i = size-1;
	for (j = 0; j < size; j++) {
			while ((array[i][j] == 0) && (i >= 0)) {
				i--;
			}
			i++;
			if (array[size-1][j] == 0) {
				row = i;
				col = j;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col);
				array[row][col] = 0;
				i = size-1;
				if (place > 0) {
					*side = 'S';
					*move = col;
					return;
				}
			} else {
				i = size-1;
			}
			
	}
	
	i = 0;
	for (j = 0; j < size; j++) {
			while ((array[j][i] == 0) && (i < size)) {
				i++;
			}
			i--;
			if (array[j][0] == 0) {
				row = j;
				col = i;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col);
				array[row][col] = 0;
				i = 0;
				if (place > 0) {
					*side = 'W';
					*move = row;
					return;
				}
			} else {
				i = 0;
			}
	}
	
	
	
	/* If the bot cannot win in its next move the code bellow will the generate
		a legal for the bot to make*/
	for (i = 0; i< size; i++) {
		if (board[i][size-1] == 0) {
			*move = i;
			*side = 'E';
			return;
		}
	}
	
	for (i = 0; i< size; i++) {
		if (board[0][i] == 0) {
			*move = i;
			*side = 'N';
			return;
		}
	}
	
	
	for (i = 0; i< size; i++) {
		if (board[size-1][i] == 0) {
			*move = i;
			*side = 'S';
			return;
		}
	}
			
	
	
	for (i = 0; i< size; i++) {
		if (board[i][0] == 0) {
			*move = i;
			*side = 'W';
			return;
		}
	}
}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{ // This function creates a legal move for Bot 2
	
	int array[MAX_SIZE][MAX_SIZE];
	int i, j;
	int row, col;
	int place;
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			array[i][j] = board[i][j];
		}
	}
	

	/* The following for loops below checks whether a winning move can be made
		by the bot. It does this by checking each possible legal move that can be made*/
	i = 0;
	for (j = 0; j < size; j++) {
			while ((array[i][j] == 0) && (i < size)) {
				i++;
			}
			i--;
			if (array[0][j] == 0) {
				row = i;
				col = j;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col); // Checks if bot can win in next move
				array[row][col] = 0; // resetting the "array"
				i = 0;
				if (place > 0) {
					*side = 'N';
					*move = col;
					return;
				}
			} else {
				i = 0;
			}
	}
	
	i = size-1;
	for (j = 0; j < size; j++) {
			while ((array[j][i] == 0) && (i >= 0)) {
				i--;
			}
			i++;
			if (array[j][size-1] == 0) {
				row = j;
				col = i;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col);
				array[row][col] = 0;
				i = size-1;
				if (place > 0) {
					*side = 'E';
					*move = row;
					return;
				}
			} else {
				i = size-1;
			}			
	}
	
	i = size-1;
	for (j = 0; j < size; j++) {
			while ((array[i][j] == 0) && (i >= 0)) {
				i--;
			}
			i++;
			if (array[size-1][j] == 0) {
				row = i;
				col = j;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col);
				array[row][col] = 0;
				i = size-1;
				if (place > 0) {
					*side = 'S';
					*move = col;
					return;
				}
			} else {
				i = size-1;
			}
			
	}
	
	i = 0;
	for (j = 0; j < size; j++) {
			while ((array[j][i] == 0) && (i < size)) {
				i++;
			}
			i--;
			if (array[j][0] == 0) {
				row = j;
				col = i;
				array[row][col] = player;
				place = CheckGameOver(array, size, player, row, col);
				array[row][col] = 0;
				i = 0;
				if (place > 0) {
					*side = 'W';
					*move = row;
					return;
				}
			} else {
				i = 0;
			}
	}
	
	/* If the bot cannot win in its next move the code bellow will the generate
		a legal for the bot to make*/
	for (i = 0; i< size; i++) {
		if (board[size-1][i] == 0) {
			*move = i;
			*side = 'S';
			return;
		}
	}
	
	for (i = 0; i< size; i++) {
		if (board[i][0] == 0) {
			*move = i;
			*side = 'W';
			return;
		}
	}
	
	
	for (i = 0; i< size; i++) {
		if (board[0][i] == 0) {
			*move = i;
			*side = 'N';
			return;
		}
	}
			
	
	
	for (i = 0; i< size; i++) {
		if (board[i][size-1] == 0) {
			*move = i;
			*side = 'E';
			return;
		}
	}
			
}