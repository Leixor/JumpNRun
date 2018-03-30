#pragma once
#include "standardInclude.h"

int main()
{
	sf::RenderWindow window(VideoMode(400, 400), "Jump and Run!");
	sf::RectangleShape shape(Vector2f(100.0f, 100.0f));
	shape.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}