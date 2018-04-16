#pragma once
#include "DrawableObject.h"

enum eOrientation {
	MIDDLE = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 4,
	BOTTOM = 8
};

namespace AlignHelper 
{
	extern void alignTo(DrawableObject& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignTo(Text& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(DrawableObject& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(Text& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(DrawableObject& toAlign, Text& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(Text& toAlign, Text& anchor, int orientation = MIDDLE, int margin = 0);
}
