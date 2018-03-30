#pragma once
#include "standardInclude.h"

int main()
{
	RenderWindow window(VideoMode(400, 400), "Jump and Run!");
	RectangleShape shape(Vector2f(100.0f, 100.0f));
	shape.setFillColor(Color::Red);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}