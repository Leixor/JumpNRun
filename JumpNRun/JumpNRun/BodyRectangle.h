#pragma once
#include "BodyShapeBase.h"

class BodyRectangle : public BodyShapeBase, public b2PolygonShape
{
public:
	BodyRectangle();
	~BodyRectangle();

	b2Shape* updateSize(Vector2f size);
};

