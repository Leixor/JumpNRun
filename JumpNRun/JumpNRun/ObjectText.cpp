#include "ObjectText.h"

ObjectText::ObjectText(string text, Font & font)
{
	this->setString(text);
	this->setFont(font);
}

ObjectText::~ObjectText()
{
}
