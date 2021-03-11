#ifndef __SHAPE_H
#define __SHAPE_H

#include <Windows.h>
#include <vector>
#include "utility.h"
#include <array>

class Shape
{
public:
	enum ePOS { POS1, POS2, POS3, POS4 };
	enum eSymb{SPACE=1, REG='#',EMPTY=0};
	static const int WIDTH_OF_MATRIX = 4;//width of shape matrix 
	static const int HEIGHT_OF_MATRIX = 4;//height of shape matrix

protected:
	int numOfPos;
	vector <std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX>> shapePosVector;
	vector <std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX>>::iterator itrShapePos;
	vector <COORD> dimVector;
	vector <COORD>::iterator itrDim;
	ePOS shapePos;
	COORD shapeCoord;
	int shapeIndex;

public:
	Shape() = delete;
	Shape(Shape &other) = delete;
	Shape(int shapeIndex, int numOfPos, ePOS shapePos, COORD shapeCoord) :shapeIndex(shapeIndex), numOfPos(numOfPos), shapePos(shapePos), shapeCoord(shapeCoord) { };
	virtual ~Shape() {}
	
	virtual int getWidthOfMatrix() const { return this->WIDTH_OF_MATRIX; }
	virtual int getHeightOfMatrix() const { return this->HEIGHT_OF_MATRIX; }
	virtual COORD getShapeCoord()const { return this->shapeCoord; }
	virtual ePOS getShapePosIndex()const { return this->shapePos; }
	virtual COORD getDimByPos(ePOS pos)const { return dimVector[pos]; }//****
	virtual char getCellContent(int i, int j) const {return (*itrShapePos)[i][j]; } //get content of cell in shape matrix																					
	virtual int getShapeIndex() const { return shapeIndex; }
	virtual void setShapeCoord(COORD newShpaeCoord) { this->shapeCoord = newShpaeCoord; }
	virtual void setShapePos(ePOS pos);

	virtual void randomizeShapePos();
	virtual void nextShapePos();

	virtual void printShape() const;
};

#endif // !__SHAPE_H
