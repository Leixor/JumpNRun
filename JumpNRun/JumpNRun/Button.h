#pragma once

class Button : public RectShape
{
public:
	Button(IntRect buttonRect, String texturePath, function<void(void)> buttonAction);
	~Button();

	void checkMouseButtonCollision(RenderWindow & window);
private:
	function<void(void)> buttonAction;
};

