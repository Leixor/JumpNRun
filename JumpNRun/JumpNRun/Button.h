#pragma once

class Button
{
public:
	Button(IntRect buttonRect, function<void(void)> buttonAction);
	~Button();

	void checkMouseButtonCollision(RenderWindow & window);
	RectangleShape buttonShape;

private:
	

	function<void(void)> buttonAction;
};

