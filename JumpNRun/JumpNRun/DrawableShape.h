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
	void setRotation(float angle, bool additional = false);
	void setFillColor(Color color);

	Vector2f getSize();
	Vector2f getPosition();
	FloatRect getGlobalBounds();

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
inline void DrawableShape<DrawableType>::setRotation(float angle, bool additional)
{
	if (additional)
		this->DrawableType::setRotation(this->DrawableType::getRotation() + angle);
	else
		this->DrawableType::setRotation(angle);
}

template<class DrawableType>
inline Vector2f DrawableShape<DrawableType>::getPosition()
{
	return this->DrawableType::getPosition();
}

template<class DrawableType>
inline FloatRect DrawableShape<DrawableType>::getGlobalBounds()
{
	return this->DrawableType::getGlobalBounds();
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

	this->setScale(size.x / currentSizeX, size.y / currentSizeY);
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