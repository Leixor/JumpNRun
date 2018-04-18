#pragma once
#include "StandardInclude.h"

class ObjectText : public Text
{
public:
	ObjectText(string text, Font& font);
	~ObjectText();

	void rotate(float angle, Vector2f origin);
	void scale(Vector2f offset, Vector2f origin);
	void setText(string text);
	void setTextSize(int size);
};

