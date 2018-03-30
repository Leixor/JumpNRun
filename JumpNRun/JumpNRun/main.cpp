#pragma once
#include "standardInclude.h"

void game()
{
	printf("HI");
}

int main()
{
	RenderWindow window(VideoMode(400, 400), "Jump and Run!");
	RectangleShape shape(Vector2f(100.0f, 100.0f));
	shape.setFillColor(Color::Red);

	Button tmp(IntRect(0, 0, 400, 400), game);
	tmp.checkMouseButtonCollision(10, 10);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}