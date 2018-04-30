#pragma once
#include "ShapeBase.h"

enum eOrientation {
	MIDDLE = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 4,
	BOTTOM = 8
};

namespace AlignHelper 
{
	extern void alignTo(ShapeBase& toAlign, ShapeBase& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignTo(Text& toAlign, ShapeBase& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(ShapeBase& toAlign, ShapeBase& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(Text& toAlign, ShapeBase& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(ShapeBase& toAlign, Text& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(Text& toAlign, Text& anchor, int orientation = MIDDLE, int margin = 0);
}
