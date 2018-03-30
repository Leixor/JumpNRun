#pragma once

class Button
{
public:
	Button(IntRect buttonRect, void(*buttonAction)());
	~Button();

	void checkMouseButtonCollision(float mouseX, float mouseY);
private:
	RectangleShape buttonShape;

	void (*buttonAction)();
};

