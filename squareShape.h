#ifndef __SQUARE_SHAPE_H
#define __SQUARE_SHAPE_H
#include "shape.h"

class squareShape : public Shape
{
	public:
	enum eINDEX { SQR = 0 };
	enum eNUMOFPOS { NUMPOS = 1 };
	enum eFIRSTCOORD { COL = 7, ROW = 3 };
	enum eDIM { PARAM1 = 2, PARAM2 = 2 };

	squareShape() : Shape(SQR,NUMPOS, POS1, { COL,ROW })
	{
		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos1 =
		{ { { REG,REG,0,0 },
		  {REG,REG,0,0 },
		  { 0,0,0,0 },
		  { 0,0,0,0 } } };

		shapePosVector.push_back(pos1);
		itrShapePos = shapePosVector.begin();

		dimVector.push_back({ PARAM1,PARAM2 });
		itrDim = dimVector.begin();
	}
};

#endif // !__SQUARE_SHAPE_H