#include "game.h"
//=================================================================
void Game::start(bool &start)
{
	/*
	receives start flag
	prompts player to start game
	*/
	int acceleration = SPEED;
	bool temp1 = false, temp2 = false;
	char keyPressed;

	this->title();//printt title
	//wait for player to start game:
	while (start == false)
	{
		keyPressed = _getch();
		control((eKEYS)keyPressed, acceleration, temp1, start, temp2);
	}
	clrscr();
}//start
//=================================================================
void Game:: title()
{
	/*
	prints title and new game button prompt
	*/
	clrscr();
	cout << "#==============================================================================#\n";

	cout << "####### ####### ####### ######    ###    #####\n";
	cout << "   #    #          #    #     #    #    #     #\n";
	cout << "   #    #          #    #     #    #    #\n";
	cout << "   #    #####      #    ######     #     #####\n";
	cout << "   #    #          #    #   #      #          #\n";
	cout << "   #    #          #    #    #     #    #     #\n";
	cout << "   #    #######    #    #     #   ###    #####\t\t\n";
	cout << "\n\nPress '1' to start...\n\n";
	cout << "#==============================================================================#\n";
}
//========================================================
void Game::run()
{
	bool isGameOverFlag = false;
	int acceleration = SPEED; //acceleration of shape movement
	bool stopJoker = false, start=false, pause=false; //action flags
	char keyPressed; //key pressed by player

	//strat game:
	this->start(start);

	initGame(stopJoker);
	
	while (!isGameOverFlag)//whule game is not over
	{	
		
		if (_kbhit()) // checks if there is anything in the buffer
		{
			keyPressed = _getch();
			clearKeyboardBuffer();
			isGameOverFlag=control((eKEYS)keyPressed, acceleration, stopJoker, start, pause);
		}//if (_kbhit())
		
		if (!pause) //if game not paused
		{
			initGameFrame();
			Sleep(acceleration);//accelerate/decelerate shape movement
			if (_kbhit()) // checks if there is anything in the buffer
			{
				keyPressed = _getch();
				clearKeyboardBuffer();
				isGameOverFlag = control((eKEYS)keyPressed, acceleration, stopJoker, start, pause);
			}//if (_kbhit())

			switch (shape->getShapeIndex())
			{
			case jokerShape::JOKER://current shape is joker
				if (!stopJoker)//if stop joker button wasnt pressed
				{
					if (!isOcupiedUnderShape()) //if cell under shape not ocupied
						shape->setShapeCoord({ shape->getShapeCoord().X ,  shape->getShapeCoord().Y + 1 });//move shape down
					else//if ocupied
						isGameOverFlag = handleShapeStop(stopJoker, acceleration);
				}//if (!stopJoker)
				else//if stop joker pressed
					isGameOverFlag = handleShapeStop(stopJoker, acceleration);//stop joker
				break;

			case bombShape::BOMB://if current shape is bomb
				if (!isOcupiedUnderShape())//if cell under shape isnt ocupied
					shape->setShapeCoord({ shape->getShapeCoord().X ,  shape->getShapeCoord().Y + 1 });//move shape down
				else//if ocupied
					//explode cells arround bomb
					handleExplosion(acceleration);
				break;

			default://if regular shape
				if (!isOcupiedUnderShape())//if cell under shape is ocupied
					shape->setShapeCoord({ shape->getShapeCoord().X ,  shape->getShapeCoord().Y + 1 });//move shape down
				else//if not ocupied
					isGameOverFlag = handleShapeStop(stopJoker, acceleration);//stop shape
				break;
			}//switch
		}//if (!pause)
	}//while (!isGameOverFlag)
	this->gameOverTitle();//print game over title
}//run
//========================================================
void Game::initGame(bool &stopJoker)
{
	/*
	initialize game
	*/
	score = 0;
	numOfShapes = 0;
	stopJoker = false;
	board.initBoard();
	randomizeShape();
	numOfShapes++;
}//initGame
//========================================================
void Game::initGameFrame()
{
	/*
	initialize game frame
	*/
	hidecursor();
	printScore();
	printMenu();
	board.printBoard();
	shape->printShape();
	coverShapeSpaces();
}//initGameFrame
//========================================================
void Game::coverShapeSpaces()
{
	/*
	prints content of board over shape spaces
	*/
	int boardI = shape->getShapeCoord().Y - Board::BOARD_OFFSET;
	int boardJ = shape->getShapeCoord().X;

	int i, j;
	for (i = 0;i < Shape::HEIGHT_OF_MATRIX; i++)//scan rows
	{
		for (j = 0; j < Shape::WIDTH_OF_MATRIX; j++)//scan cols
		{
			if (shape->getCellContent(i, j) == Shape::SPACE)//if space in shape matrix cell
			{
				gotoxy(shape->getShapeCoord().X + j, shape->getShapeCoord().Y + i);//go over space coord
				cout << board.getBoardCell(boardI + i, boardJ + j);//print board contents
			}//if...
		}//for (j ...
	}//for (i ...
}//coverShapeSpaces
//========================================================
void Game::printScore()
{
	/*
	print score on top of game screen
	*/
	gotoxy(0, 0);
	cout << "Shapes: " << numOfShapes<<" Score: "<<score<<"       ";
}//printScore
//========================================================
void Game::printMenu()
{
	/*
	print game menu and button prompts right of game board
	*/
	int row = 3;
	gotoxy(board.getWidth() + 2, row++);//go right of board
	cout << "Menu:";
	gotoxy(board.getWidth() + 2, row++);
	cout << "Controls: a-Left  b-Right  w-Rotate";
	gotoxy(board.getWidth() + 2, row++);
	cout << "1)New Game";
	gotoxy(board.getWidth() + 2, row++);
	cout << "2)Pause/Continue";
	gotoxy(board.getWidth() + 2, row++);
	cout << "3)Accelerate";
	gotoxy(board.getWidth() + 2, row++);
	cout << "4)Slow";
	gotoxy(board.getWidth() + 2, row++);
	cout<< "9)Exit";
}//printMenu
//========================================================
bool Game::handleShapeStop(bool &stopJoker, int &acceleration) 
{
	/*
	handles shape stop
	returns if game is over after shape stop
	*/
	addToBoard();
	score+=board.deleteFullRows();
	stopJoker = false;
	randomizeShape();
	numOfShapes++;
	acceleration = SPEED;
	return isGameOver();
}//handleShapeStop
//========================================================
void Game::handleExplosion(int &acceleration)
{
	//explode bomb in 3X3 radius and detract points for every cell deactivated
	score -= board.explode(shape->getShapeCoord().Y - board.getBoardOffset(), shape->getShapeCoord().X);
	if (score < 0)//if negtive score
		score = 0;
	acceleration = SPEED;
	randomizeShape();
	numOfShapes++;
}//handleExplosion
//========================================================
bool Game::control(eKEYS key, int &acceleration, bool &stopJoker, bool &start, bool &pause)
{
	/*
	key pressed by player, shape acceleration by ref, stop joker flag by ref, start new game flag by ref, pause game by ref
	executes the action acording to the button pressed
	*/
	if (pause==false)//if game not paused
	{
		switch (key)
		{
		case LEFT:
			if (!isOcupiedLeftOfShape())//if cell left of shape not ocupied
				//move shape left
				shape->setShapeCoord({ shape->getShapeCoord().X - 1,shape->getShapeCoord().Y });
			else//if ocupied
				if (shape->getShapeIndex() == bombShape::BOMB)//if shape is bomb
					handleExplosion(acceleration);
			break;
		case RIGHT:
			if (!isOcupiedRightOfShape())//if cell right of cell not ocupied
				//move shape right
				shape->setShapeCoord({ shape->getShapeCoord().X + 1,shape->getShapeCoord().Y });
			else//if ocupied
				if (shape->getShapeIndex() == bombShape::BOMB)//if shape is bomb
					handleExplosion(acceleration);
			break;
		case ROTATE:
			checkRotation();//rotate shape if possible
			break;
		case STOP_JOKER:
			if (shape->getShapeIndex() == jokerShape::JOKER)//if current shape is joker
				stopJoker = true;
			break;
		case START:
			if (start == true)//if game in progres
			{
				acceleration = SPEED;
				initGame(stopJoker);//start new game
			}
			else
				start = true;
			break;
		case PAUSE:
			if (start == true)//if game in progres
			{
				pause = true;
				gotoxy(0, 2);
				cout << "Game Paused";
			}
			break;
		case ACCELERATE:
			acceleration = FASTER;
			break;
		case SLOW:
			if (acceleration == SLOWER)
				acceleration = SPEED;
			else
				acceleration = SLOWER;
			break;
		case Exit:
			//exit game
			return true;
			break;
		}//switch
	}//if
	else//if game paused
	{
		switch (key)
		{
		case PAUSE:
			//unpause game
			pause = false;
			gotoxy(0, 2);
			cout << "           ";
			break;
		case Exit:
			//exit game
			return true;
			break;
		}//switch
	}//else
	return false;

}//control
//========================================================
void Game::checkRotation()
{
	/*
	checks if its possible to rotate and rotates it
	*/
	Shape::ePOS prevPos = shape->getShapePosIndex(); //save current shape possition
	COORD prevCoord = shape->getShapeCoord();//save current shape coord

	shape->nextShapePos();//set shape pos to next shape pos
	
	checkBoundariesAfterRotation();

	if (isOverlay())//if there is overlay with active cells on board after rotation
	{
		//revert shape to previous characteristics
		shape->setShapePos(prevPos);
		shape->setShapeCoord(prevCoord);
	}
}//checkRotation
//========================================================
bool Game::isOverlay() const
{
	//------------------
	/*
	Name: isOverlay, Class:Game
	receive shape by reference, 
	checks if there is overlay between the shape and the active cells in board
	*/
	//------------------
	int boardI = shape->getShapeCoord().Y - board.getBoardOffset(), boardJ = shape->getShapeCoord().X;//shape will be copied to these coordinates
	int wasActive = 0;//flag- is it the first slot in shape mat row to be active
	int shapeColOffset = 0;//offset of slot in curr row from left wall of shape matrix

	for (int i = 0;i < shape->getHeightOfMatrix();i++)//scan shape mat row
	{
		wasActive = 0;
		for (int j = 0;j < shape->getWidthOfMatrix();j++)//scan shape mat col
			
			//if (shape->getCellContent(i, j))//if slot in shape matrix active
			if (shape->getCellContent(i, j))//if slot in shape matrix active

		{
				if (!wasActive)//if its the first slot active in row
				{
					shapeColOffset = j; //make it's col index the offset
					wasActive = 1;
				}//if (!wasActive)
				if (board.getBoardCell(boardI + i, boardJ + j - shapeColOffset))//if there is overlay
					return true;
			}
	}//for (int i ...
	return false;
}//isOverlay
 //========================================================
void Game::checkBoundariesAfterRotation()
{
	/*
	check if shape stays in boundaries after rotation
	*/
	
	COORD sizeOfShapes = shape->getDimByPos(shape->getShapePosIndex());
	COORD shapeCoord = shape->getShapeCoord();//curr shape coord on cmd
	short BoardWidth = board.getWidth();
	short BoardHeight = board.getWidth();
	short boardOffset = board.getBoardOffset();
	
	if (shapeCoord.X + sizeOfShapes.X >= BoardWidth)//if out of right boundary
	{
		//calculate the offset of shape
		//offset = shape's most right coord - board width - board wall
		short shapeCoordXOffset = shapeCoord.X+ sizeOfShapes.X - (BoardWidth -1);
		shape->setShapeCoord({ shapeCoord.X - shapeCoordXOffset ,shapeCoord.Y });//move shape to the left
	}
	if (shapeCoord.Y + sizeOfShapes.Y >= BoardHeight + boardOffset)//if fell through floor
	{
		//calculate the offset of shape:
		short shapeCoordYOffset = shapeCoord.Y + sizeOfShapes.Y - (BoardHeight - 1 + boardOffset);
		shape->setShapeCoord({ shapeCoord.X ,shapeCoord.Y- shapeCoordYOffset });//move shape up
	}

}//checkBoundariesAfterRotation
//=======================================================
bool Game::isOcupiedUnderShape() const
{
	/*
	checks if cell under shape is ocupied
	*/
	//converts shape coords on cmd to coords on board matrix:
	int boardI = shape->getShapeCoord().Y - board.getBoardOffset();
	int boardJ = shape->getShapeCoord().X;
	int shapeHeight = shape->getDimByPos(shape->getShapePosIndex()).Y;
	int shapeWidth = shape->getDimByPos(shape->getShapePosIndex()).X;
	
	for (int j = 0; j < shapeWidth; j++)//scan board cols
	{
		char cellContent = board.getBoardCell(boardI + shapeHeight, boardJ + j);//content of cell under shape

		//handle shape spaces:
		if (shape->getCellContent(shapeHeight - 1, j) == Shape::SPACE)
		{
			//handle L shape:
			if (shape->getShapeIndex() == LShape::L &&  shape->getShapePosIndex() == Shape::POS4)
			{
				if (board.getBoardCell(boardI + shapeHeight - 2, boardJ + j) != 0)
					return true;
			}//if
			else
				if (board.getBoardCell(boardI + shapeHeight - 1, boardJ + j) != 0)
					return true;
		}//if (shape->...
		else if (cellContent)
		   {
			if (cellContent !=Board::WALL && shape->getShapeIndex() == jokerShape::JOKER)
				return false;
			return true;
		    }
	}//for (int j ...
	return false;
}//isOcupiedUnderShape
//=======================================================
bool Game::isOcupiedLeftOfShape() const
{
	/*
	checks if cell left of shape is ocupied
	*/
	//converts shape coords on cmd to coords on board matrix:
	int boardI = shape->getShapeCoord().Y - board.getBoardOffset();
	int boardJ = shape->getShapeCoord().X;
	//shape height:
	int shapeHeight = shape->getDimByPos(shape->getShapePosIndex()).Y;

	for (int i = 0; i < shapeHeight; i++)//scan board rows
	{
		if (shape->getShapeIndex() == jokerShape::JOKER)//iif current shape is joker
		{
			//return that cell is ocupied left of joker only if its the floor
			if (board.getBoardCell(boardI + i, boardJ - 1) == Board::WALL)
				return true;
		}
		
		//if regular shape, return if cell left of it is ocupied:
		else
		{
			//handle shape spaces:
			if (shape->getCellContent(i, 0) == Shape::SPACE)
			{
				//handle L shape:
				if (shape->getShapeIndex() == LShape::L &&  shape->getShapePosIndex() == Shape::POS1)
				{
					if (board.getBoardCell(boardI + i, boardJ+1) != 0)
						return true;
				}
				else
					if (board.getBoardCell(boardI + i, boardJ) != 0)
						return true;
			}//if
			else
				if (board.getBoardCell(boardI + i, boardJ - 1))
					return true;
		}//else
	}//for (int i = 0...
	return false;
}//isOcupiedLeftOfShape
//=======================================================
bool Game::isOcupiedRightOfShape()  const
{
	/*
	check if cells right of current shapes are ocupied
	*/
	//convert shape coord on cmd to coord on board matrix
	int boardI = shape->getShapeCoord().Y - board.getBoardOffset();
	int boardJ = shape->getShapeCoord().X;
	//shape matrix dimensions:
	int shapeHeight = shape->getDimByPos(shape->getShapePosIndex()).Y;
	int shapeWidth = shape->getDimByPos(shape->getShapePosIndex()).X;

	for (int i = 0; i < shapeHeight; i++)//scan shape rows
	{
		if (shape->getShapeIndex() == jokerShape::JOKER)//if current shape is joker
		{
			//return that cell is ocupied only if its a wall
			if (board.getBoardCell(boardI + i, boardJ + shapeWidth) == Board::WALL)
				return true;
		}
		//if its a regular shape, return if shape is ocupied
		else
		{
			//handle shape spaces:
			//if (shape->getCellContent(i, shapeWidth-1) == Shape::SPACE)
			if (shape->getCellContent(i, shapeWidth - 1) == Shape::SPACE)
			{
				//handle L shape:
				if (shape->getShapeIndex() == LShape::L &&  shape->getShapePosIndex() == Shape::POS3)
				{
					if (board.getBoardCell(boardI + i, boardJ + shapeWidth -2) != 0)
						return true;
				}//if
				else
					if (board.getBoardCell(boardI + i, boardJ + shapeWidth -1) != 0)
						return true;
			}//if (shape->...
			else
				if (board.getBoardCell(boardI + i, boardJ + shapeWidth))
					return true;
		}//else
	}//for
	return false;
}//isOcupiedRightOfShape
//=======================================================
void Game::randomizeShape()
{
	/*
	randomizes shape type and position
	revers it back to default position
	*/
	//the chance to get joker is 1/14,
	//and the chance to get bomb is 1/14
	int randSpecialShape = rand() % SPEC;
	int randShapeIndex = rand() % REG;
	
	//handele bomb and jocker:
    if (randSpecialShape == jokerShape::JOKER|| randSpecialShape == bombShape::BOMB)
		randShapeIndex = randSpecialShape;
	//update shape:
	updateShape(randShapeIndex);

	//handle overlay after reverting shape to default coords:
	if (isOverlay())
	{
		//randonize between horizontal rectangle, bomb and jocker
		int num = rand() % END;
		if (num == SPEC1)
			randShapeIndex = jokerShape::JOKER;
		else if (num == SPEC2)
			randShapeIndex = bombShape::BOMB;
		else
			randShapeIndex = rectangleShape::RECT;
		updateShape(randShapeIndex);

		if(num==SPEC3)
			shape->setShapePos(Shape::POS2);
	}
}//randomizeShape
//======================================================
void Game::updateShape(int shapeIndex)
{
	if (shape != nullptr)
		delete shape;
	switch (shapeIndex)
	{
	case squareShape::SQR:
		shape = new squareShape();
		break;
	case rectangleShape::RECT:
		shape = new rectangleShape();
		break;
	case LShape::L:
		shape = new LShape();
		break;
	case plusShape::PLUS:
		shape = new plusShape();
		break;
	case ZShape::Z:
		shape = new ZShape();
		break;
	case jokerShape::JOKER:
		shape = new jokerShape();
		break;
	case bombShape::BOMB:
		shape = new bombShape();
		break;
	default:
		break;
	}
	//shape->randomizeShapePos();
	shape->randomizeShapePos();

}
//======================================================
bool Game::isGameOver() const
{
	int boardWidth = board.getWidth();

	for (int j = 1;j < boardWidth-1;j++)
		if (board.getBoardCell(0, j))
			return true;
	return false;
}
//======================================================
void Game::addToBoard()
{
	//------------------
	/*
	Name: addToBoard, Class:Board
	adds shape to board matrix
	*/
	//------------------
	int boardI = (shape->getShapeCoord()).Y - board.getBoardOffset(), boardJ = (shape->getShapeCoord()).X;//shape will be copied to these coordinates
	int wasActive = 0;//flag- is it the first slot in shape mat row to be active
	int shapeColOffset = 0;//offset of slot in curr row from left wall of shape matrix

	///
	char CellContent;
	//
	for (int i = 0; i < shape->getHeightOfMatrix(); i++)//scan shape mat row
	{
		wasActive = 0;
		for (int j = 0; j < shape->getWidthOfMatrix(); j++)
		{//scan shape mat col
			 CellContent=shape->getCellContent(i, j);
			
			 if (CellContent)//if slot in shape matrix active
			{
				if (!wasActive)//if its the first slot active in row
				{
					shapeColOffset = j; //make it's col index the offset
					wasActive = 1;
				}//if (!wasActive)
				//board[boardI+ i][boardJ + j - shapeColOffset] = shape.getCellContent(i, j);//activate corresponding slot in board matrix
				if (CellContent != Shape::SPACE)
					board.getBoardCell(boardI + i, boardJ + j - shapeColOffset) = CellContent;//activate corresponding slot in board matrix

			}//if (shape.isActive(i, j))
		}//for (int i ...
	}
}//addToBoard
//======================================================
void Game::gameOverTitle()
{
	/*
	prints game over title
	*/
	system("cls");
	cout << " #####     #    #     # ####### ####### #     # ####### ######\n";
	cout << "#     #   # #   ##   ## #       #     # #     # #       #     #\n";
	cout << "#        #   #  # # # # #       #     # #     # #       #     #\n";
	cout << "#  #### #     # #  #  # #####   #     # #     # #####   ######\n";
	cout << "#     # ####### #     # #       #     #  #   #  #       #   #\n";
	cout << "#     # #     # #     # #       #     #   # #   #       #    #\n";
	cout << " #####  #     # #     # ####### #######    #    ####### #     #\n";
}//gameOverTitle
//======================================================
