#pragma once

 class Button
{
public:
	Button(function<void(void)> buttonAction, DrawableShape<Drawable>* buttonShape);
	~Button();

	void checkMouseButtonCollision(RenderWindow & window);
private:
	DrawableShape<Drawable>* buttonShape;
	function<void(void)> buttonAction;
};
