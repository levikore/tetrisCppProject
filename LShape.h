#ifndef __L_SHAPE_H
#define __L_SHAPE_H
#include "shape.h"

class LShape : public Shape
{
	public:
	enum eINDEX { L = 2 };
	enum eNUMOFPOS { NUMPOS = 4 };
	enum eFIRSTCOORD { COL = 6, ROW = 3 };
	enum eDIM { PARAM1 = 3, PARAM2 = 2 };

	LShape() : Shape(L, NUMPOS, POS1, { COL,ROW })
	{
		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos1 =
		{ {{ REG,REG,REG,0},
			  {SPACE,SPACE,REG,0 },
			  { 0,0,0,0 },
			  { 0,0,0,0 } } };

		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos2 =
		{ { { SPACE,REG,0,0},
		  { SPACE,REG,0,0 },
		  { REG,REG,0,0},
		{ 0,0,0,0 } } };

		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos3 =
		{ { { REG,SPACE,SPACE,0 },
		{ REG,REG,REG,0},
		{ 0,0,0,0 },
		{0,0,0,0 } } };

		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos4 =
		{ {{ REG,REG,0,0 },
			{ REG,SPACE,0,0 },
			{ REG,SPACE,0,0 },
			{ 0,0,0,0 } } };


		shapePosVector.push_back(pos1);
		shapePosVector.push_back(pos2);
		shapePosVector.push_back(pos3);
		shapePosVector.push_back(pos4);
		itrShapePos = shapePosVector.begin();

		dimVector.push_back({ PARAM1,PARAM2 });
		dimVector.push_back({ PARAM2,PARAM1 });
		dimVector.push_back({ PARAM1,PARAM2 });
		dimVector.push_back({ PARAM2,PARAM1 });
		itrDim = dimVector.begin();
	}

};

#endif // !__LSHAPE_H