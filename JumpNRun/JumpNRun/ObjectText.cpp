#include "ObjectText.h"

ObjectText::ObjectText(string text, Font & font)
{
	this->setString(text);
	this->setFont(font);
}

ObjectText::~ObjectText()
{
}

void ObjectText::rotate(float angle, Vector2f origin)
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
		rotation = this->getRotation();
		oScale = this->getScale();
		iScale = Vector2f(1.0f / oScale.x, 1.0f / oScale.y);
		originPosT.rotate(rotation);
		originPosT.scale(oScale);
		originPosT.rotate(-rotation, origin);
		originPosT.scale(iScale, origin);
		originalGlobalPos = originPosT.transformPoint(this->getPosition());

		// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
		oldPos = this->getPosition();

		// Die globale Position des Origins herausfinden
		globalOrigin = originalGlobalPos + origin;

		// Setze den Shape an den gewünschten Origin und drehe es um die gewünschten Grad
		this->setOrigin(origin);
		this->setPosition(globalOrigin);
	}

	this->Text::rotate(angle);

	// Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden
	if (origin != Vector2f(0, 0))
	{
		// Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben
		newPosT.rotate(angle, globalOrigin);
		Vector2f newPos = newPosT.transformPoint(oldPos);
		this->setOrigin(Vector2f(0, 0));
		this->setPosition(newPos);
	}
}

void ObjectText::scale(Vector2f offset, Vector2f origin)
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
		rotation = this->getRotation();
		oScale = this->getScale();
		iScale = Vector2f(1.0f / oScale.x, 1.0f / oScale.y);
		originPosT.rotate(rotation);
		originPosT.scale(oScale);
		originPosT.rotate(-rotation, origin);
		originPosT.scale(iScale, origin);
		originalGlobalPos = originPosT.transformPoint(this->getPosition());


		// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
		oldPos = this->getPosition();

		// Die globale Position des Origins herausfinden
		globalOrigin = originalGlobalPos + origin;

		// Setze den Shape an den gewünschten Origin und drehe es um die gewünschten Grad
		this->setOrigin(origin);
		this->setPosition(globalOrigin);
	}

	this->Text::scale(offset);

	/* Wenn der origin die linke obere Ecke ist sollen die ganzen Berechnungen ausgelassen werden*/
	if (origin != Vector2f(0, 0))
	{
		/* Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben*/
		oScale = this->getScale();
		newPosT.rotate(rotation, globalOrigin);
		newPosT.scale(oScale, globalOrigin);
		newPos = newPosT.transformPoint(originalGlobalPos);
		this->setOrigin(Vector2f(0, 0));
		this->setPosition(newPos);
	}
}

void ObjectText::setText(string text)
{
	this->setString(text);
}

void ObjectText::setTextSize(int size)
{
	this->setCharacterSize(size);
}
