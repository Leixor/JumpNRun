#pragma once

namespace AlignHelper {
	extern void alignTo(DrawableObject& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignTo(Text& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(DrawableObject& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(Text& toAlign, DrawableObject& anchor, int orientation = MIDDLE, int margin = 0);
	extern void alignNextTo(DrawableObject& toAlign, Text& anchor, int orientation = MIDDLE, int margin = 0);
}
