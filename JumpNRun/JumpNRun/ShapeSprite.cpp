#include "standardInclude.h"

ShapeSprite::ShapeSprite(string textureName, float scale, Vector2f pos)
{
	this->setTexture(textureName);
	this->setScale(Vector2f(scale, scale));
	this->setPosition(pos);
}

ShapeSprite::ShapeSprite(string textureName, Vector2f size, Vector2f pos)
{
	this->setTexture(textureName);
	this->setSize(size);
	this->setPosition(pos);
}

ShapeSprite::ShapeSprite(string textureName)
{
	this->setTexture(textureName);
}

ShapeSprite::ShapeSprite(string textureName, FloatRect rect)
{
	this->setTexture(textureName);
	this->setSize(Vector2f(rect.width, rect.height));
	this->setPosition(Vector2f(rect.left, rect.top));
}



ShapeSprite::~ShapeSprite()
{
}
