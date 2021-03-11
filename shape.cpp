#include "shape.h"
//=================================================================
void Shape::setShapePos(ePOS pos)
{
	this->shapePos = pos;
	itrShapePos = shapePosVector.begin() + shapePos;
	itrDim = dimVector.begin() + shapePos;
}
//=================================================================
void Shape::nextShapePos()
{
	/*
	change shapes position to next position in shape array
	if current position is the last position in shape, reverts back to position 0
	*/
	if (itrShapePos == shapePosVector.end() - 1)//if current pos is last pos
	{
		this->itrShapePos = this->shapePosVector.begin();
		this->itrDim = this->dimVector.begin();
		setShapePos(POS1);
	}//revert to first position
	else //if current pos isnt last
	{
		++itrShapePos; //set position to next position
		++itrDim;
		setShapePos((ePOS)(this->shapePos + 1));
	}
}//nextShapePos
//=================================================================
void Shape::randomizeShapePos()
{
	int randPosIndex = rand() % numOfPos;
	setShapePos((ePOS)randPosIndex);
	itrShapePos = shapePosVector.begin() + randPosIndex;
	itrDim = dimVector.begin() + randPosIndex;

}
//=================================================================
void Shape::printShape() const
{
	/*
	prints shape in its position
	*/
	for (int i = 0; i < HEIGHT_OF_MATRIX; i++) //shape matrix rows
	{
		gotoxy(shapeCoord.X, shapeCoord.Y + i);

		for (int j = 0; j < WIDTH_OF_MATRIX; j++)//shape matrix cols
			if ((*itrShapePos)[i][j])
			{
				if(((*itrShapePos)[i][j]) == SPACE)
					cout << " ";
				else
					cout <<(*itrShapePos)[i][j];//print apropriate char to number in shape matrix
			}
	}//for (int i = 0...
}//printShape
