#ifndef __GAME_H
#define __GAME_H

#include <Windows.h>
#include <typeinfo>
#include <conio.h>
#include <stdio.h>
#include "shape.h"
#include "squareShape.h"
#include "ZShape.h"
#include "bombShape.h"
#include "jokerShape.h"
#include "LShape.h"
#include "plusShape.h"
#include "rectangleShape.h"
#include "board.h"
#include "utility.h"

class Game
{
private:
	Board board;
	Shape *shape;
	int numOfShapes=0;//counter for the ammount of fallen shapes
	int score=0;//game score

public:
	enum eKEYS { LEFT = 'a', RIGHT = 'd', ROTATE = 'w', STOP_JOKER = 's', START='1', PAUSE='2', ACCELERATE = '3', SLOW='4', Exit = '9'};
	enum eCHANCE{REG=5, SPEC=14, END=3};
	enum eSPEED{SPEED=400, FASTER=0, SLOWER=800};
	enum eSPECRAND { SPEC1 = 0, SPEC2, SPEC3 };

	Game(){randomizeShape();}
	~Game(){delete shape;}

	void start(bool &start);
	void run();
	void printScore();
	void printMenu();
	void title();
	void gameOverTitle();
	bool control(eKEYS key, int &acceleration, bool &stopJoker, bool &start, bool &pause);
	void updateShape(int shapeIndex);

	void checkRotation();
	void checkBoundariesAfterRotation();
	bool isOverlay() const;

	bool isOcupiedUnderShape() const;
	bool isOcupiedLeftOfShape() const;
	bool isOcupiedRightOfShape() const;

	void initGame(bool &stopJoker);
	void initGameFrame();
	bool handleShapeStop(bool &stopJoker, int &acceleration);
	void handleExplosion(int &acceleration);
	void randomizeShape();

	void coverShapeSpaces();
	void addToBoard();
	bool isGameOver() const;

};

#endif //!__GAME_H
