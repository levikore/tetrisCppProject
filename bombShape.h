#ifndef __JOKER_H
#define _JOKER_H
#include "shape.h"

class bombShape : public Shape
{
	public:
	enum eINDEX {BOMB = 6 };
	enum eSymb{BMB='@'};
	enum eNUMOFPOS {NUMPOS=1};
	enum eFIRSTCOORD { COL = 8, ROW = 3 };
	enum eDIM { PARAM1 = 1, PARAM2 = 1 };

	bombShape() : Shape(BOMB, NUMPOS, POS1, { COL,ROW })
	{
		std::array<std::array<char, WIDTH_OF_MATRIX>, HEIGHT_OF_MATRIX> pos1 =
		{{ { BMB,0,0,0 },
		   { 0,0,0,0 },
		   { 0,0,0,0 },
		   { 0,0,0,0 } }};

		shapePosVector.push_back(pos1);
		itrShapePos = shapePosVector.begin();

		dimVector.push_back({ PARAM1,PARAM2 });
		itrDim = dimVector.begin();

	}

};

#endif // !#pragma once
