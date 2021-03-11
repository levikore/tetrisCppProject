#ifndef __Rectangle_SHAPE_H
#define __Rectangle_SHAPE_H
#include "shape.h"

class rectangleShape : public Shape
{
	public:
	enum eINDEX { RECT = 1 };
	enum eNUMOFPOS { NUMPOS = 2 };
	enum eFIRSTCOORD{COL= 6,ROW=3};
	enum eDIM { PARAM1 = 1, PARAM2 = 4 };

	rectangleShape() : Shape(RECT,NUMPOS, POS1, { COL,ROW })
	{
		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos1 =
		{ {{ REG,0,0,0 },
		{ REG,0,0,0 },
		{ REG,0,0,0 },
		{ REG,0,0,0 } } };

		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos2=
		{ {{ REG,REG,REG,REG },
		 { 0,0,0,0 },
		 { 0,0,0,0 },
		 { 0,0,0,0 }} };

		shapePosVector.push_back(pos1);
		shapePosVector.push_back(pos2);
		itrShapePos = shapePosVector.begin();

		dimVector.push_back({ PARAM1,PARAM2 });
		dimVector.push_back({ PARAM2,PARAM1 });
		itrDim = dimVector.begin();
	}
	
};

#endif // !__Rectangle_SHAPE_H