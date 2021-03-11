#include "board.h"

char Board::board[WIDTH][HEIGHT] = { 0 };
//================================================
void Board::initBoard()
{
	/*
	initializes board matrix 
	*/
	for (int i = 0;i < HEIGHT -1;i++)//board rows
	{
		board[i][0] = WALL; //mark left wall
		for (int j = 1;j < WIDTH - 1;j++)//board cols
			board[i][j] = 0;//dectivate board cell
		board[i][WIDTH - 1] = WALL;//mark right wall
	}
	//mark board floor:
	for (int j = 0;j < WIDTH;j++)
		board[HEIGHT - 1][j] = WALL;
}//initBoard
//================================================
void Board::printBoard() const
{
	gotoxy(0, 3);
	for (int i = 0;i < HEIGHT;i++)
	{
		for (int j = 0;j < WIDTH;j++)
			if (board[i][j] == 0)
				cout << " ";
			else
				cout << board[i][j];
		cout << endl;
	}	
}
//================================================
int Board::deleteFullRows()
{
	/*
	locates and deletes all full rows in board matrix
	calculates points the player receives after action
	*/
	int read, write;// board row indicies
	int numOfDeletedRows = 0, numOfJokerRows=0;
	bool isJokerInRow = false;

	for (read = HEIGHT - 2, write = HEIGHT - 2;read >= 0;read--)//scan from last to first row of matrix
	{
		if (!isFullRow(read, isJokerInRow))//if current row not full
			copyRows(write--, read);	//copy current rows content to row in write index 
		else//if row full
		{
			numOfDeletedRows++;
			if (isJokerInRow)
				numOfJokerRows++;
		}//else
		isJokerInRow = false;
	}//for

	return numOfDeletedRows * REGSCORE - numOfJokerRows * JSCORE;
}//deleteFullRows
//================================================
bool Board::isFullRow(int row, bool &isJokerInRow) const
{
	/*
	receives row index and is joker in row flag by ref
	sets joker flag to true if joker is located in row
	returns true if the row is full
	*/
	for (int j = 1;j < WIDTH - 1;j++)//scan row cells
		if (!getBoardCell(row, j))//if cell not active
			return false;
		else//if active
			if (board[row][j] == JOKER)//if joker in cell
				isJokerInRow = true;
	return true;
}//isFullRow
//================================================
void Board::copyRows(int write, int read)
{
	/*
	copy content from row in read index to row in write index
	*/
	for (int j = 1;j < WIDTH - 1;j++)
		board[write][j] = board[read][j];

}//copyRows
//================================================
int Board::explode(int row, int col) const
{
	/*
	receives cell index
	deactivates cells around it in 3X3 radius unless they are walls
	counts and returns num of cells activated
	calculates points to be deducted
	*/
	int numOfExplodedCells = 0;

	if (row - 1 >= 0 && col - 1 > 0 && board[row - 1][col - 1] != WALL && board[row - 1][col - 1] != 0)
	{
		board[row - 1][col - 1] = 0;
		numOfExplodedCells++;
	}
	if (row - 1 >= 0 && board[row - 1][col] != WALL && board[row - 1][col] != 0)
	{
		board[row - 1][col] = 0;
		numOfExplodedCells++;
	}
	if (row - 1 >= 0 && col + 1 < WIDTH && board[row - 1][col + 1] != WALL && board[row - 1][col + 1] != 0)
	{
		board[row - 1][col + 1] = 0;
		numOfExplodedCells++;
	}
	if (col - 1 > 0 && board[row][col - 1] != WALL && board[row][col - 1] != 0)
	{
		board[row][col - 1] = 0;
		numOfExplodedCells++;
	}
	if (col + 1 < WIDTH && board[row][col + 1] != WALL && board[row][col + 1] != 0)
	{
		board[row][col + 1] = 0;
		numOfExplodedCells++;
	}
	if (row + 1 < HEIGHT && col - 1 > 0 && board[row + 1][col - 1] != WALL && board[row + 1][col - 1] != 0)
	{
		board[row + 1][col - 1] = 0;
		numOfExplodedCells++;
	}
	if (row + 1 < HEIGHT && board[row + 1][col] != WALL && board[row + 1][col] != 0)
	{
		board[row + 1][col] = 0;
		numOfExplodedCells++;
	}
	if (row + 1 < HEIGHT &&col + 1 < WIDTH && board[row + 1][col + 1] != WALL && board[row + 1][col + 1] != 0)
	{
		board[row + 1][col + 1] = 0;
		numOfExplodedCells++;
	}
	return numOfExplodedCells * JSCORE;//calculate ponts for deduction
}//explode
//===============================================