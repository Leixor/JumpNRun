#include "standardInclude.h"

RectShape::RectShape(IntRect buttonRect, String texturePath)
	: texturePath(texturePath)
{
	this->setPosition(buttonRect.left, buttonRect.top);
	this->setSize(Vector2f(buttonRect.width, buttonRect.height));
}

RectShape::~RectShape()
{
}

void RectShape::unloadTextures()
{
	this->rectTexture.create(1,1);
}

bool RectShape::loadTextures()
{
	if (this->rectTexture.loadFromFile(this->texturePath))
	{
		this->setTexture(&this->rectTexture);
		return true;
	}
	return false;
}
