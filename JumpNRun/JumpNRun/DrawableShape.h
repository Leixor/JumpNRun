#pragma once
#include "DrawableObject.h"

template <class DrawableType> class DrawableShape : public DrawableObject
{
public:
	DrawableShape();
	~DrawableShape();

	void draw(RenderWindow& window, RenderStates shader);

	void setPosition(Vector2f pos);
	void setOrigin(Vector2f origin);
	void setScale(Vector2f scale, Vector2f origin = Vector2f(0, 0));
	void setRotation(float angle, Vector2f origin = Vector2f(0, 0));

	void rotate(float offsetAngle, Vector2f origin = Vector2f(0,0));
	void move(Vector2f offset);
	void scale(Vector2f offset, Vector2f origin = Vector2f(0, 0));

	Vector2f getPosition();
	Vector2f getOrigin();
	Vector2f getScale();
	FloatRect getGlobalBounds();
	float getRotation();

protected:
	DrawableType* shape;
};

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
inline void DrawableShape<DrawableType>::setScale(Vector2f scale, Vector2f origin)
{
	Vector2f oScale;
	Vector2f iScale;
	Transform originPosT;
	Transform newPosT;
	Vector2f originalGlobalPos;
	Vector2f newPos;
	Vector2f oldPos;
	Vector2f globalOrigin;
	float rotation;
	// Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden
	if (origin != Vector2f(0, 0))
	{
		// Die Originalposition der linken oberen Ecke herausfinden
		rotation = this->shape->getRotation();
		oScale = this->shape->getScale();
		iScale = Vector2f(1.0f / oScale.x, 1.0f / oScale.y);
		originPosT.rotate(rotation);
		originPosT.scale(oScale);
		originPosT.rotate(-rotation, origin);
		originPosT.scale(iScale, origin);
		originalGlobalPos = originPosT.transformPoint(this->shape->getPosition());


		// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
		oldPos = this->shape->getPosition();

		// Die globale Position des Origins herausfinden
		globalOrigin = originalGlobalPos + origin;

		// Setze den Shape an den gewünschten Origin und drehe es um die gewünschten Grad
		this->shape->setOrigin(origin);
		this->shape->setPosition(globalOrigin);
	}

	this->shape->setScale(scale);

	/* Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden*/
	if (origin != Vector2f(0, 0))
	{
		/* Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben*/
		oScale = this->shape->getScale();
		newPosT.rotate(rotation, globalOrigin);
		newPosT.scale(oScale, globalOrigin);
		newPos = newPosT.transformPoint(originalGlobalPos);
		this->shape->setOrigin(Vector2f(0, 0));
		this->shape->setPosition(newPos);
	}
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::setRotation(float angle, Vector2f origin)
{
	Vector2f oScale;
	Vector2f iScale;
	Transform originPosT;
	Transform newPosT;
	Vector2f originalGlobalPos;
	Vector2f newPos;
	Vector2f oldPos;
	Vector2f globalOrigin;
	float rotation;
	// Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden
	if (origin != Vector2f(0, 0))
	{
		// Die Originalposition der linken oberen Ecke herausfinden
		rotation = this->shape->getRotation();
		oScale = this->shape->getScale();
		iScale = Vector2f(1.0f / oScale.x, 1.0f / oScale.y);
		originPosT.rotate(rotation);
		originPosT.scale(oScale);
		originPosT.rotate(-rotation, origin);
		originPosT.scale(iScale, origin);
		originalGlobalPos = originPosT.transformPoint(this->shape->getPosition());

		// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
		oldPos = this->shape->getPosition();

		// Die globale Position des Origins herausfinden
		globalOrigin = originalGlobalPos + origin;

		// Setze den Shape an den gewünschten Origin und drehe es um die gewünschten Grad
		this->shape->setOrigin(origin);
		this->shape->setPosition(globalOrigin);
	}

	this->shape->setRotation(angle);

	// Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden
	if (origin != Vector2f(0, 0))
	{
		// Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben
		newPosT.rotate(angle, globalOrigin);
		Vector2f newPos = newPosT.transformPoint(oldPos);
		this->shape->setOrigin(Vector2f(0, 0));
		this->shape->setPosition(newPos);
	}
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
	Vector2f oScale;
	Vector2f iScale;
	Transform originPosT;
	Transform newPosT;
	Vector2f originalGlobalPos;
	Vector2f newPos;
	Vector2f oldPos;
	Vector2f globalOrigin;
	float rotation;
	// Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden
	if (origin != Vector2f(0, 0))
	{
		// Die Originalposition der linken oberen Ecke herausfinden
		rotation = this->shape->getRotation();
		oScale = this->shape->getScale();
		iScale = Vector2f(1.0f / oScale.x, 1.0f / oScale.y);
		originPosT.rotate(rotation);
		originPosT.scale(oScale);
		originPosT.rotate(-rotation, origin);
		originPosT.scale(iScale, origin);
		originalGlobalPos = originPosT.transformPoint(this->shape->getPosition());

		// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
		oldPos = this->shape->getPosition();

		// Die globale Position des Origins herausfinden
		globalOrigin = originalGlobalPos + origin;

		// Setze den Shape an den gewünschten Origin und drehe es um die gewünschten Grad
		this->shape->setOrigin(origin);
		this->shape->setPosition(globalOrigin);
	}
	
	this->shape->rotate(offsetAngle);

	// Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden
	if (origin != Vector2f(0, 0))
	{
		// Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben
		newPosT.rotate(offsetAngle, globalOrigin);
		Vector2f newPos = newPosT.transformPoint(oldPos);
		this->shape->setOrigin(Vector2f(0, 0));
		this->shape->setPosition(newPos);
	}
}
	
template<class DrawableType>
inline void DrawableShape<DrawableType>::move(Vector2f offset)
{
	this->shape->move(offset);
}

template<class DrawableType>
inline void DrawableShape<DrawableType>::scale(Vector2f offset, Vector2f origin)
{
	Vector2f oScale;
	Vector2f iScale;
	Transform originPosT;
	Transform newPosT;
	Vector2f originalGlobalPos;
	Vector2f newPos;
	Vector2f oldPos;
	Vector2f globalOrigin;
	float rotation;
	// Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden
	if (origin != Vector2f(0, 0))
	{
		// Die Originalposition der linken oberen Ecke herausfinden
		rotation = this->shape->getRotation();
		oScale = this->shape->getScale();
		iScale = Vector2f(1.0f / oScale.x, 1.0f / oScale.y);
		originPosT.rotate(rotation);
		originPosT.scale(oScale);
		originPosT.rotate(-rotation, origin);
		originPosT.scale(iScale, origin);
		originalGlobalPos = originPosT.transformPoint(this->shape->getPosition());


		// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
		oldPos = this->shape->getPosition();

		// Die globale Position des Origins herausfinden
		globalOrigin = originalGlobalPos + origin;

		// Setze den Shape an den gewünschten Origin und drehe es um die gewünschten Grad
		this->shape->setOrigin(origin);
		this->shape->setPosition(globalOrigin);
	}

	this->shape->scale(offset);

	/* Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden*/
	if (origin != Vector2f(0, 0))
	{
		/* Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben*/
		oScale = this->shape->getScale();
		newPosT.rotate(rotation, globalOrigin);
		newPosT.scale(oScale, globalOrigin);
		newPos = newPosT.transformPoint(originalGlobalPos);
		this->shape->setOrigin(Vector2f(0, 0));
		this->shape->setPosition(newPos);
	}
}