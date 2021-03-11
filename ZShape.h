#ifndef __Z_SHAPE_H
#define __Z_SHAPE_H
#include "shape.h"

class ZShape : public Shape
{
  public:
	enum eINDEX { Z= 4};
	enum eNUMOFPOS { NUMPOS = 2 };
	enum eFIRSTCOORD { COL = 6, ROW = 3 };
	enum eDIM{PARAM1=3,PARAM2=2};
	ZShape() : Shape(Z, NUMPOS, POS1, { COL,ROW })
	{
		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos1 =
		{ {{ REG,REG,SPACE,0},
		{ SPACE,  REG,REG,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 } } };

		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos2 =
		{ {    { SPACE,REG,0,0 },
			 { REG,REG,0,0 },
			 { REG,SPACE,0,0 },
			 { 0,0,0,0 } } };

		shapePosVector.push_back(pos1);
		shapePosVector.push_back(pos2);
		itrShapePos = shapePosVector.begin();


		dimVector.push_back({ PARAM1,PARAM2 });
		dimVector.push_back({ PARAM2,PARAM1 });
		itrDim = dimVector.begin();
	}


};

#endif // __Z_SHAPE_H!