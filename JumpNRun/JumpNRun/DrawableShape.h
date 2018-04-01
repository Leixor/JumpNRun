#pragma once
#include "standardInclude.h"

template <class DrawableType> class DrawableShape: public DrawableType, public DrawableObject
{
public:
	DrawableShape(bool visibility = false);
	~DrawableShape();

	void draw(RenderWindow& window, RenderStates shader);

	//Für alle Typen vorhanden
	void setSize(Vector2f size);
	void setPosition(Vector2f pos);
	void setScale(Vector2f sclae);
	void setRotation(float angle);
	void setFillColor(Color color);

	void rotate(float offsetAngle);
	void move(Vector2f offset);
	void scale(Vector2f offset);

	Vector2f getSize();
	Vector2f getPosition();
	Vector2f getScale();
	FloatRect getGlobalBounds();
	float getRotation();

	//Existiert nur bei manchen Typen
	void setOutlineColor(Color color);
	void setOutlineThickness(float thickness);

	void setTexture(String texturePath);
	void setTextureRect(IntRect textureRect);
	IntRect getTextureRect();
};

#pragma region Gleiche Funktion für jeden Typ
template<class DrawableType>
inline DrawableShape<DrawableType>::DrawableShape(bool visibility)
	:DrawableObject(visibility)
{
}

template<class DrawableType>
inline DrawableShape<DrawableType>::~DrawableShape()
{
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::draw(RenderWindow & window, RenderStates shader)
{
	window.draw(*this);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setPosition(Vector2f pos)
{
	this->DrawableType::setPosition(pos);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setScale(Vector2f scale)
{
	this->DrawableType::setScale(scale);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setRotation(float angle)
{
	this->DrawableType::setRotation(angle);
}

template<class DrawableType>
inline Vector2f DrawableShape<DrawableType>::getPosition()
{
	return this->DrawableType::getPosition();
}

template<class DrawableType>
inline Vector2f DrawableShape<DrawableType>::getScale()
{
	return this->DrawableType::getScale();
}

template<class DrawableType>
inline FloatRect DrawableShape<DrawableType>::getGlobalBounds()
{
	return this->DrawableType::getGlobalBounds();
}

template<class DrawableType>
inline float DrawableShape<DrawableType>::getRotation()
{
	return this->DrawableType::getRotation();
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::rotate(float offsetAngle)
{
	DrawableType::rotate(offsetAngle);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::move(Vector2f offset)
{
	DrawableType::move(offset);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::scale(Vector2f offset)
{
	this->DrawableType::scale(offset);
}
#pragma endregion

#pragma region Funktionen die nicht alle haben
template<>
inline IntRect DrawableShape<Sprite>::getTextureRect()
{
	return this->Sprite::getTextureRect();
}

template<class DrawableType>
inline IntRect DrawableShape<DrawableType>::getTextureRect()
{
	return IntRect();
}

template<>
inline void DrawableShape<Sprite>::setTexture(String texturePath)
{
	Texture* loadHelper = new Texture();
	loadHelper->loadFromFile(texturePath);

	this->Sprite::setTexture(*loadHelper);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setTexture(String texturePath)
{}

template<>
inline void DrawableShape<Sprite>::setTextureRect(IntRect textureRect)
{
	this->Sprite::setTextureRect(textureRect);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setTextureRect(IntRect textureRect)
{}

template<>
inline void DrawableShape<RectangleShape>::setOutlineColor(Color color)
{
	this->RectangleShape::setOutlineColor(color);
}

template<>
inline void DrawableShape<CircleShape>::setOutlineColor(Color color)
{
	this->CircleShape::setOutlineColor(color);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setOutlineColor(Color color)
{}

template<>
inline void DrawableShape<RectangleShape>::setOutlineThickness(float thickness)
{
	this->RectangleShape::setOutlineThickness(thickness);
}

template<>
inline void DrawableShape<CircleShape>::setOutlineThickness(float thickness)
{
	this->CircleShape::setOutlineThickness(thickness);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setOutlineThickness(float thickness)
{}

template<>
inline void DrawableShape<RectangleShape>::setFillColor(Color color)
{
	this->RectangleShape::setFillColor(color);
}

template<>
inline void DrawableShape<CircleShape>::setFillColor(Color color)
{
	this->CircleShape::setFillColor(color);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setFillColor(Color color)
{}
#pragma endregion

#pragma region Funktionen die bei jedem Typ anderst ist
template<>
inline void DrawableShape<CircleShape>::setSize(Vector2f size)
{
	this->CircleShape::setRadius(size.x);
	this->CircleShape::setPointCount(size_t(size.y));
}

template<>
inline void DrawableShape<RectangleShape>::setSize(Vector2f size)
{
	this->RectangleShape::setSize(size);
}

template<>
inline void DrawableShape<Sprite>::setSize(Vector2f size)
{
	float currentSizeX = float(this->Sprite::getTexture()->getSize().x);
	float currentSizeY = float(this->Sprite::getTexture()->getSize().x);
	auto scale = this->getScale();

	currentSizeX *= scale.x;
	currentSizeY *= scale.y;

	this->Sprite::setScale(size.x / currentSizeX, size.y / currentSizeY);
}

template<>
inline Vector2f DrawableShape<CircleShape>::getSize()
{
	return Vector2f(float(CircleShape::getRadius()), float(CircleShape::getPointCount()));
}

template<>
inline Vector2f DrawableShape<RectangleShape>::getSize()
{
	return RectangleShape::getSize();
}

template<>
inline Vector2f DrawableShape<Sprite>::getSize()
{
	float currentSizeX = float(this->Sprite::getTexture()->getSize().x);
	float currentSizeY = float(this->Sprite::getTexture()->getSize().x);
	auto scale = this->getScale();

	currentSizeX *= scale.x;
	currentSizeY *= scale.y;

	return Vector2f(currentSizeX, currentSizeY);
}
#pragma endregion