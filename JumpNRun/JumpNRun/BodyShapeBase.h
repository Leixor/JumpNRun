#pragma once
#include "StandardInclude.h"

class BodyShapeBase
{
public:
	BodyShapeBase()
	{}
	~BodyShapeBase() 
	{}

	virtual b2Shape* updateSize(Vector2f size) = 0;
};

