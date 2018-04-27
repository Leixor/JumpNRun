#include "ShapeSprite.h"

ShapeSprite::ShapeSprite(string textureName, float scale, Vector2f pos)
{
	this->setTexture(textureName);
	this->setScale(Vector2f(scale, scale));
	this->setPosition(pos);
}

ShapeSprite::ShapeSprite(Texture* texture, float scale, Vector2f pos)
{
	this->setTexture(texture);
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

IntRect ShapeSprite::getTextureRect()
{
	return this->shape->getTextureRect();
}

Vector2f ShapeSprite::getSize()
{
	float currentSizeX = float(this->shape->getTexture()->getSize().x);
	float currentSizeY = float(this->shape->getTexture()->getSize().x);
	auto scale = Vector2f(this->shape->getScale());

	currentSizeX *= scale.x;
	currentSizeY *= scale.y;

	return *(new Vector2f(currentSizeX, currentSizeY));
}

void ShapeSprite::setTexture(string texturePath, bool resetRect)
{
	Texture* loadHelper = new Texture();
	loadHelper->loadFromFile(texturePath);

	this->shape->setTexture(*loadHelper, resetRect);
}

void ShapeSprite::setTexture(const Texture* texture, bool resetRect)
{
	this->shape->setTexture(*texture, resetRect);
}

void ShapeSprite::setTextureRect(IntRect rect)
{
	this->shape->setTextureRect(rect);
}

void ShapeSprite::setSize(Vector2f size)
{
	float currentSizeX = float(this->shape->getTexture()->getSize().x);
	float currentSizeY = float(this->shape->getTexture()->getSize().y);

	this->shape->setScale(size.x / currentSizeX, size.y / currentSizeY);
}
