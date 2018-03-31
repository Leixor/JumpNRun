#pragma once
#include "standardInclude.h"

#define MS_PER_UPDATE 16

long getCurrentTime()
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds >(
		chrono::system_clock::now().time_since_epoch()
	);
	return ms.count();
}

int main()
{
	/*
	Das Renderwindow ist f�r das zeichnen der verschiedenen Formen benutzt. 
	Es k�nnen noch weitere Parameter �bergeben werden, die daf�r verantwortlich sind, 
	ob das Fenster keinen CloseKnopf hat, nicht gr��enver�nderbar ist...
	*/
	RenderWindow window(VideoMode(400, 400), "Jump and Run!");


	RectangleShape shape(Vector2f(100.0f, 100.0f));
	shape.setFillColor(Color::Red);

	Button tmp(IntRect(0, 0, 400, 400), [&]
	{
		shape.setFillColor(Color::Yellow);
	});

	tmp.checkMouseButtonCollision(10, 10);

	//Parameter die f�r die verbesserte Spielschleife notwendig sind.
	long lag = 0;
	long previous = getCurrentTime();

	while (window.isOpen())
	{
		long current = getCurrentTime();
		long elapsed = current - previous;
		previous = current;
		lag += elapsed;

		//Verarbeitung der Eingaben und Events
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

		//Verarbeitung der Bewegungen und Positionsaktuallisierungen
		while (lag >= MS_PER_UPDATE)
		{
			//Ruft sp�ter die Aktualisierungsmethode auf
			printf("Lag: %ld\nSystemTime: %ld\n", lag, getCurrentTime());
			
			//update();
			lag -= MS_PER_UPDATE;
		}

		//Zeichnen der Objekte
		window.clear();
		window.draw(shape);
		window.display();



		// Die Loop soll im Update die wahre Position und Geschwindigkeit von Objekten abspeichern, der Renderer tut dann mithilfe der 2 Werte eine extrapolierte Position rendern
		
		/*double lag = 0.0;
		double previous = std::chrono::system_clock::now();
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
	}

	return 0;
}