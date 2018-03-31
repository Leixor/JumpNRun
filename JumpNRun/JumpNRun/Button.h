#pragma once

template <class Drawable> class Button : public DrawableShape<Drawable>
{
public:
	Button(IntRect buttonRect, function<void(void)> buttonAction, String texturePath = "");
	Button(Vector2f position, int radius, function<void(void)> buttonAction,  String texturePath = "", int corners = 0);
	~Button();

	void checkMouseButtonCollision(RenderWindow & window);
private:
	function<void(void)> buttonAction;
};

template<class Drawable>
inline Button<Drawable>::Button(IntRect buttonRect, function<void(void)> buttonAction, String texturePath)
	: DrawableShape<RectangleShape>(buttonRect, texturePath), buttonAction(buttonAction)
{
}

template<class Drawable>
inline Button<Drawable>::Button(Vector2f position, int radius, function<void(void)> buttonAction, String texturePath, int corners)
	: DrawableShape<CircleShape>(position, radius, corners, texturePath), buttonAction(buttonAction)
{
}

template<class Drawable>
inline Button<Drawable>::~Button()
{
}

template<class Drawable>
inline void Button<Drawable>::checkMouseButtonCollision(RenderWindow & window)
{
	auto mousePosition = Mouse::getPosition(window);
	if (this->getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y)))
		this->buttonAction();
}
