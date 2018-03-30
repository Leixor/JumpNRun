#pragma once
#include "standardInclude.h"

int main()
{
	RenderWindow window(VideoMode(400, 400), "Jump and Run!");
	RectangleShape shape(Vector2f(100.0f, 100.0f));
	shape.setFillColor(Color::Red);

	Button tmp(IntRect(0, 0, 400, 400), [&]
	{
		shape.setFillColor(Color::Yellow);
	});

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

		// Die Loop soll im Update die wahre Position und Geschwindigkeit von Objekten abspeichern, der Renderer tut dann mithilfe der 2 Werte eine extrapolierte Position rendern
		/*double previous = std::chrono::system_clock::now();
		double lag = 0.0;
		while (true)
		{
			double current = getCurrentTime();
			double elapsed = current - previous;
			previous = current;
			lag += elapsed;

			processInput();

			while (lag >= MS_PER_UPDATE)
			{
				update();
				lag -= MS_PER_UPDATE;
			}

			render(lag / MS_PER_UPDATE);
		}*/
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}