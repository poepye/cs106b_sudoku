/* Sudoku Problem */
#include <iostream>
#include "grid.h"
using namespace std;

void InitBoard(Grid<int>& board);
bool Sudoku(Grid<int>& board);
bool NextEmpty(Grid<int>& board);
int NextEmptyRow(Grid<int>& board);
int NextEmptyCol(Grid<int>& board);
bool NoConflict(Grid<int>& board, int row, int col, int i);

int main() {
	Grid<int> board (9, 9);
	InitBoard(board);
	Sudoku(board);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
	return 0;
}

// Create a borad with initial values
void InitBoard(Grid<int>& board) {
	board.set(0, 2, 6); board.set(0, 3, 5);
	board.set(0, 5, 8);	board.set(0, 6, 4);
	board.set(1, 0, 5);	board.set(1, 1, 2);
	board.set(2, 1, 8);	board.set(2, 2, 7);
	board.set(2, 7, 3);	board.set(2, 8, 1);
	board.set(3, 2, 3);	board.set(3, 4, 1);
	board.set(3, 7, 8);	board.set(4, 0, 9);
	board.set(4, 3, 8);	board.set(4, 4, 6);
	board.set(4, 5, 3);	board.set(4, 8, 5);
	board.set(5, 1, 5);	board.set(5, 4, 9);
	board.set(5, 6, 6);	board.set(6, 0, 1);
	board.set(6, 1, 3);	board.set(6, 6, 2);
	board.set(6, 7, 5);	board.set(7, 7, 7);
	board.set(7, 8, 4); board.set(8, 2, 5);
	board.set(8, 3, 2);	board.set(8, 5, 6);
	board.set(8, 6, 3);
}

bool Sudoku(Grid<int>& board) {
	int row, col;
	// If there is no empty tile, all numbers are filled correctly
	if (!NextEmpty(board))
		return true;
	// Find the next empty tile
	row = NextEmptyRow(board);
	col = NextEmptyCol(board);
	for (int i = 1; i <= 9; i++) {
		if (NoConflict(board, row, col, i)) {
			board.set(row, col, i);
			if (Sudoku(board)) return true;
			board.set(row, col, 0);
		}
	}
	return false;
}

bool NextEmpty(Grid<int>& board) {
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (board[row][col] == 0) return true;
	return false;
}

int NextEmptyRow(Grid<int>& board) {
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (board[row][col] == 0)
				return row;
}

int NextEmptyCol(Grid<int>& board) {
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (board[row][col] == 0)
				return col;
}

bool NoConflict(Grid<int>& board, int row, int col, int i) {
	// Row Conflict
	for (int r = 0; r < 9; r++)
		if (board[row][r] == i)
			return false;
	// Col Conflict
	for (int r = 0; r < 9; r++)
		if (board[r][col] == i)
			return false;
	// Block Conflict
	int rowStart = row - row % 3, colStart = col - col % 3;
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			if (board[r+rowStart][c+colStart] == i)
				return false;
	return true;
}