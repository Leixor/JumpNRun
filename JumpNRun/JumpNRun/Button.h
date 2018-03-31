#pragma once

class Button : public RectangleShape
{
public:
	Button(IntRect buttonRect, function<void(void)> buttonAction);
	~Button();

	void checkMouseButtonCollision(RenderWindow & window);

private:
	

	function<void(void)> buttonAction;
};

