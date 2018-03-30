#pragma once

class Button
{
public:
	Button(IntRect buttonRect, function<void(void)> buttonAction);
	~Button();

	void checkMouseButtonCollision(float mouseX, float mouseY);
private:
	RectangleShape buttonShape;

	function<void(void)> buttonAction;
};

