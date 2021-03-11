#ifndef __JOKER_H
#define _JOKER_H
#include "shape.h"

class jokerShape : public Shape
{
	public:
	enum eINDEX { JOKER= 5 };
	enum eSYMB { J = 'J' };
	enum eNUMOFPOS { NUMPOS = 1 };
	enum eFIRSTCOORD { COL = 7, ROW = 3 };
	enum eDIM { PARAM1 = 1, PARAM2 = 1 };

	jokerShape() : Shape(JOKER, NUMPOS, POS1,{ COL,ROW })
	{
		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos1 =
		{ {{ J,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 } } };

		shapePosVector.push_back(pos1);
		itrShapePos = shapePosVector.begin();

		dimVector.push_back({ PARAM1,PARAM2 });
		itrDim = dimVector.begin();
		
	}

};

#endif // !