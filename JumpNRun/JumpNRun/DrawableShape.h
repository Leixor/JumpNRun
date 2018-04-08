#pragma once
#include "standardInclude.h"

template <class DrawableType> class DrawableShape : public DrawableObject
{
public:
	DrawableShape();
	~DrawableShape();

	void draw(RenderWindow& window, RenderStates shader);

	//Für alle Typen vorhanden
	void setSize(Vector2f size);
	void setPosition(Vector2f pos);
	void setOrigin(Vector2f origin);
	void setScale(Vector2f sclae);
	void setRotation(float angle);
	void setFillColor(Color color);

	void rotate(float offsetAngle, Vector2f origin = Vector2f(0,0));
	void move(Vector2f offset);
	void scale(Vector2f offset);

	Vector2f getSize();
	Vector2f getPosition();
	Vector2f getOrigin();
	Vector2f getScale();
	FloatRect getGlobalBounds();
	float getRotation();

	//Existiert nur bei manchen Typen
	void setOutlineColor(Color color);
	void setOutlineThickness(float thickness);
	void setTexture(String texturePath);
	void setTextureRect(IntRect textureRect);

	IntRect getTextureRect();
	float getOutlineThickness();

	DrawableType* shape;
};

#pragma region Gleiche Funktion für jeden Typ
template<class DrawableType>
inline DrawableShape<DrawableType>::DrawableShape() : shape(new DrawableType())
{
}

template<class DrawableType>
inline DrawableShape<DrawableType>::~DrawableShape()
{
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::draw(RenderWindow & window, RenderStates shader)
{
		window.draw(*shape, shader);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setPosition(Vector2f pos)
{
	this->shape->setPosition(pos);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setOrigin(Vector2f origin)
{
	this->shape->setOrigin(origin);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setScale(Vector2f scale)
{
	this->shape->setScale(scale);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setRotation(float angle)
{
	this->shape->setRotation(angle);
}

template<class DrawableType>
inline Vector2f DrawableShape<DrawableType>::getPosition()
{
	return this->shape->getPosition();
}

template<class DrawableType>
inline Vector2f DrawableShape<DrawableType>::getOrigin()
{
	return this->shape->getOrigin();
}

template<class DrawableType>
inline Vector2f DrawableShape<DrawableType>::getScale()
{
	return this->shape->getScale();
}

template<class DrawableType>
inline FloatRect DrawableShape<DrawableType>::getGlobalBounds()
{
	return this->shape->getGlobalBounds();
}

template<class DrawableType>
inline float DrawableShape<DrawableType>::getRotation()
{
	return this->shape->getRotation();
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::rotate(float offsetAngle, Vector2f origin)
{
	// Die Originalposition der linken oberen Ecke herausfinden
	sf::Transform w;
	float rotation = this->shape->getRotation();
	w.rotate(rotation);
	w.rotate(-rotation, origin);
	Vector2f originalGlobalPos = w.transformPoint(this->getPosition());

	// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
	Vector2f oldPos = this->getPosition();

	// Die globale Position des Origins herausfinden
	Vector2f globalOrigin = originalGlobalPos + origin;

	// Setze den Shape an den gewünschten Origin und drehe es um die gewünschten Grad
	this->setOrigin(origin);
	this->setPosition(globalOrigin);
	this->shape->rotate(offsetAngle);

	// Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben
	sf::Transform t;
	t.rotate(offsetAngle, globalOrigin);
	Vector2f newPos = t.transformPoint(oldPos);
	this->setOrigin(Vector2f(0, 0));
	this->setPosition(newPos);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::move(Vector2f offset)
{
	this->shape->move(offset);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::scale(Vector2f offset)
{
	this->shape->scale(offset);
}
#pragma endregion

#pragma region Funktionen die nicht alle haben
template<>
inline IntRect DrawableShape<Sprite>::getTextureRect()
{
	return this->shape->getTextureRect();
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

	this->shape->setTexture(*loadHelper);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setTexture(String texturePath)
{}

template<>
inline void DrawableShape<Sprite>::setTextureRect(IntRect textureRect)
{
	this->shape->setTextureRect(textureRect);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setTextureRect(IntRect textureRect)
{}

template<>
inline void DrawableShape<RectangleShape>::setOutlineColor(Color color)
{
	this->shape->setOutlineColor(color);
}

template<>
inline void DrawableShape<CircleShape>::setOutlineColor(Color color)
{
	this->shape->setOutlineColor(color);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setOutlineColor(Color color)
{}

template<>
inline void DrawableShape<RectangleShape>::setOutlineThickness(float thickness)
{
	this->shape->setOutlineThickness(thickness);
}

template<>
inline void DrawableShape<CircleShape>::setOutlineThickness(float thickness)
{
	this->shape->setOutlineThickness(thickness);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setOutlineThickness(float thickness)
{}

template<>
inline void DrawableShape<RectangleShape>::setFillColor(Color color)
{
	this->shape->setFillColor(color);
}

template<>
inline void DrawableShape<CircleShape>::setFillColor(Color color)
{
	this->shape->setFillColor(color);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setFillColor(Color color)
{}

template<>
inline float DrawableShape<CircleShape>::getOutlineThickness()
{
	return this->shape->getOutlineThickness();
}

template<>
inline float DrawableShape<RectangleShape>::getOutlineThickness()
{
	return this->shape->getOutlineThickness();
}

template<class DrawableType>
inline float DrawableShape<DrawableType>::getOutlineThickness()
{
	return 0.0f;
}

#pragma endregion

#pragma region Funktionen die bei jedem Typ anderst ist
template<>
inline void DrawableShape<CircleShape>::setSize(Vector2f size)
{
	this->shape->setRadius(size.x);
	this->shape->setPointCount(size_t(size.y));
}

template<>
inline void DrawableShape<RectangleShape>::setSize(Vector2f size)
{
	this->shape->setSize(size);
}

template<>
inline void DrawableShape<Sprite>::setSize(Vector2f size)
{
	float currentSizeX = float(this->shape->getTexture()->getSize().x);
	float currentSizeY = float(this->shape->getTexture()->getSize().y);

	this->shape->setScale(size.x / currentSizeX, size.y / currentSizeY);
}

template<>
inline Vector2f DrawableShape<CircleShape>::getSize()
{
	return Vector2f(float(this->shape->getRadius()), float(this->shape->getPointCount()));
}

template<>
inline Vector2f DrawableShape<RectangleShape>::getSize()
{
	return this->shape->getSize();
}

template<>
inline Vector2f DrawableShape<Sprite>::getSize()
{
	float currentSizeX = float(this->shape->getTexture()->getSize().x);
	float currentSizeY = float(this->shape->getTexture()->getSize().x);
	auto scale = this->shape->getScale();

	currentSizeX *= scale.x;
	currentSizeY *= scale.y;

	return Vector2f(currentSizeX, currentSizeY);
}
#pragma endregion