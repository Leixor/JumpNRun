#pragma once
#include "standardInclude.h"

int main()
{
	RenderWindow window(VideoMode(400, 400), "Jump and Run!");
	RectangleShape shape;

	
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