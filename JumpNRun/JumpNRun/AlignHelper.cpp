#pragma once
#include "standardInclude.h"

namespace AlignHelper{

	// Align das Objekt innerhalb von dem Anchorobjekt an der gegeben Stelle
	void alignTo(DrawableObject& toAlign, DrawableObject& anchor, int orientation, int margin) {
		FloatRect anchorBounds = anchor.getGlobalBounds();
		FloatRect toAlignBounds = toAlign.getGlobalBounds();

		Vector2f middleanchor = Vector2f(anchorBounds.left + anchorBounds.width / 2, anchorBounds.top + anchorBounds.height / 2);
		Vector2f middletoAlign = Vector2f(toAlignBounds.width / 2, toAlignBounds.height / 2);

		if (orientation & LEFT) {
			middleanchor.x -= anchorBounds.width / 2 - margin;
			middletoAlign.x -= toAlignBounds.width / 2;
		}

		if (orientation & RIGHT) {
			middleanchor.x += anchorBounds.width / 2 - margin;
			middletoAlign.x += toAlignBounds.width / 2;
		}
		if (orientation & TOP) {
			middleanchor.y -= anchorBounds.height / 2 - margin;
			middletoAlign.y -= toAlignBounds.height / 2;
		}
		if (orientation & BOTTOM) {
			middleanchor.y += anchorBounds.height / 2 - margin;
			middletoAlign.y += toAlignBounds.height / 2;
		}
		toAlign.setPosition(middleanchor - middletoAlign);
	}

	void alignTo(Text & toAlign, DrawableObject & anchor, int orientation, int margin)
	{
		FloatRect anchorBounds = anchor.getGlobalBounds();
		FloatRect toAlignBounds = toAlign.getGlobalBounds();

		Vector2f middleanchor = Vector2f(anchorBounds.left + anchorBounds.width / 2, anchorBounds.top + anchorBounds.height / 2);
		Vector2f middletoAlign = Vector2f(toAlignBounds.width / 2, toAlignBounds.height / 2);

		if (orientation & LEFT) {
			middleanchor.x -= anchorBounds.width / 2 - margin;
			middletoAlign.x -= toAlignBounds.width / 2;
		}

		if (orientation & RIGHT) {
			middleanchor.x += anchorBounds.width / 2 - margin;
			middletoAlign.x += toAlignBounds.width / 2;
		}
		if (orientation & TOP) {
			middleanchor.y -= anchorBounds.height / 2 - margin;
			middletoAlign.y -= toAlignBounds.height / 2;
		}
		if (orientation & BOTTOM) {	
			middleanchor.y += anchorBounds.height / 2 - margin;
			middletoAlign.y += toAlignBounds.height / 2;
		}
		toAlign.setPosition(middleanchor - middletoAlign);
		float difftoAlign = toAlign.getLocalBounds().top - (toAlign.getCharacterSize() - toAlign.getLocalBounds().height);
		toAlign.move(Vector2f(0, -(toAlign.getLocalBounds().top - difftoAlign/2)));
	}

	// Align das Objekt ausserhalb des Anchorobjekts an der gegeben Stelle
	void alignNextTo(DrawableObject & toAlign, DrawableObject & anchor, int orientation, int margin)
	{
		FloatRect anchorBounds = anchor.getGlobalBounds();
		FloatRect toAlignBounds = toAlign.getGlobalBounds();

		Vector2f middleanchor = Vector2f(anchorBounds.left + anchorBounds.width / 2, anchorBounds.top + anchorBounds.height / 2);
		Vector2f middletoAlign = Vector2f(toAlignBounds.width / 2, toAlignBounds.height / 2);

		if (orientation & LEFT) 
		{
			middleanchor.x -= anchorBounds.width / 2 + margin;
			middletoAlign.x += toAlignBounds.width / 2;
		}

		if (orientation & RIGHT) 
		{
			middleanchor.x += anchorBounds.width / 2 + margin;
			middletoAlign.x -= toAlignBounds.width / 2;
		}
		if (orientation & TOP) 
		{
			middleanchor.y -= anchorBounds.height / 2 + margin;
			middletoAlign.y += toAlignBounds.height / 2;
		}
		if (orientation & BOTTOM) 
		{
			middleanchor.y += anchorBounds.height / 2 + margin;
			middletoAlign.y -= toAlignBounds.height / 2;
		}
		toAlign.setPosition(middleanchor - middletoAlign);
		toAlign.move(Vector2f(toAlign.getOutlineThickness(), toAlign.getOutlineThickness()));
	}

	void alignNextTo(Text & toAlign, DrawableObject & anchor, int orientation, int margin)
	{
		FloatRect anchorBounds = anchor.getGlobalBounds();
		FloatRect toAlignBounds = toAlign.getGlobalBounds();

		Vector2f middleanchor = Vector2f(anchorBounds.left + anchorBounds.width / 2, anchorBounds.top + anchorBounds.height / 2);
		Vector2f middletoAlign = Vector2f(toAlignBounds.width / 2, toAlignBounds.height / 2);

		if (orientation & LEFT)
		{
			middleanchor.x -= anchorBounds.width / 2 + margin;
			middletoAlign.x += toAlignBounds.width / 2;
		}

		if (orientation & RIGHT)
		{
			middleanchor.x += anchorBounds.width / 2 + margin;
			middletoAlign.x -= toAlignBounds.width / 2;
		}
		if (orientation & TOP)
		{
			middleanchor.y -= anchorBounds.height / 2 + margin;
			middletoAlign.y += toAlignBounds.height / 2;
		}
		if (orientation & BOTTOM)
		{
			middleanchor.y += anchorBounds.height / 2 + margin;
			middletoAlign.y -= toAlignBounds.height / 2;
		}
		toAlign.setPosition(middleanchor - middletoAlign);
		float difftoAlign = toAlign.getLocalBounds().top - (toAlign.getCharacterSize() - toAlign.getLocalBounds().height);
		toAlign.move(Vector2f(0, -(toAlign.getLocalBounds().top - difftoAlign / 2)));
	}
	void alignNextTo(DrawableObject & toAlign, Text & anchor, int orientation, int margin)
	{
		FloatRect anchorBounds = anchor.getGlobalBounds();
		FloatRect toAlignBounds = toAlign.getGlobalBounds();

		Vector2f middleanchor = Vector2f(anchorBounds.left + anchorBounds.width / 2, anchorBounds.top + anchorBounds.height / 2);
		Vector2f middletoAlign = Vector2f(toAlignBounds.width / 2, toAlignBounds.height / 2);

		if (orientation & LEFT)
		{
			middleanchor.x -= anchorBounds.width / 2 + margin;
			middletoAlign.x += toAlignBounds.width / 2;
		}

		if (orientation & RIGHT)
		{
			middleanchor.x += anchorBounds.width / 2 + margin;
			middletoAlign.x -= toAlignBounds.width / 2;
		}
		if (orientation & TOP)
		{
			middleanchor.y -= anchorBounds.height / 2 + margin;
			middletoAlign.y += toAlignBounds.height / 2;
		}
		if (orientation & BOTTOM)
		{
			middleanchor.y += anchorBounds.height / 2 + margin;
			middletoAlign.y -= toAlignBounds.height / 2;
		}
		toAlign.setPosition(middleanchor - middletoAlign);
	}
	void alignNextTo(Text & toAlign, Text & anchor, int orientation, int margin)
	{
		FloatRect anchorBounds = anchor.getGlobalBounds();
		FloatRect toAlignBounds = toAlign.getGlobalBounds();

		Vector2f middleanchor = Vector2f(anchorBounds.left + anchorBounds.width / 2, anchorBounds.top + anchorBounds.height / 2);
		Vector2f middletoAlign = Vector2f(toAlignBounds.width / 2, toAlignBounds.height / 2);

		if (orientation & LEFT)
		{
			middleanchor.x -= anchorBounds.width / 2 + margin;
			middletoAlign.x += toAlignBounds.width / 2;
		}

		if (orientation & RIGHT)
		{
			middleanchor.x += anchorBounds.width / 2 + margin;
			middletoAlign.x -= toAlignBounds.width / 2;
		}
		if (orientation & TOP)
		{
			middleanchor.y -= anchorBounds.height / 2 + margin;
			middletoAlign.y += toAlignBounds.height / 2;
		}
		if (orientation & BOTTOM)
		{
			middleanchor.y += anchorBounds.height / 2 + margin;
			middletoAlign.y -= toAlignBounds.height / 2;
		}
		toAlign.setPosition(middleanchor - middletoAlign);
		float difftoAlign = toAlign.getLocalBounds().top - (toAlign.getCharacterSize() - toAlign.getLocalBounds().height);
		toAlign.move(Vector2f(0, -(toAlign.getLocalBounds().top - difftoAlign / 2)));
	}
}

