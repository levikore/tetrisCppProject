#ifndef __BOARD_H
#define __BOARD_H

#include "utility.h"

class Board
{
public:
	static const int BOARD_OFFSET = 3;//offset of boards start print location in cmd
	static const int WIDTH = 16;//width of board (2 reserved for walls)
	static const int HEIGHT = 20;//height of board (1 reserved for floor)
private:
	//boart matrix representing its content:
	static char board[WIDTH][HEIGHT];

public:
	enum eWall { WALL = '=' };
	enum eJoker { JOKER = 'J' };
	enum wScore {REGSCORE=100,JSCORE=50};
	int getBoardOffset()const { return BOARD_OFFSET; };
	int getWidth()const { return WIDTH; }
	int getHeight()const { return HEIGHT; }

	char &getBoardCell(int row, int col) { return board[row][col]; }

	void initBoard();
	void printBoard() const;
	int deleteFullRows();
	void copyRows(int write, int read);
	int explode(int row, int col) const;
	bool isFullRow(int row, bool &isJokerInRow) const;
	char getBoardCell(int i, int j) const { return board[i][j]; }
};

#endif //!__BOARD_H