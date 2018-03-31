#include "standardInclude.h"

RectShape::RectShape(IntRect buttonRect, String texturePath)
{
	this->setPosition(buttonRect.left, buttonRect.top);
	this->setSize(Vector2f(buttonRect.width, buttonRect.height));
	this->setTexture(&this->rectTexture);
}

RectShape::~RectShape()
{
}

void RectShape::unloadTextures()
{
	this->rectTexture.create(0, 0);
}

bool RectShape::loadTextures()
{
	return this->rectTexture.loadFromFile(this->texturePath);
}
