#include "BodyRectangle.h"

BodyRectangle::BodyRectangle()
{
}

BodyRectangle::~BodyRectangle()
{
}

b2Shape* BodyRectangle::updateSize(Vector2f size)
{
	this->SetAsBox(size.x / 2, size.y / 2);
	return this;
}
