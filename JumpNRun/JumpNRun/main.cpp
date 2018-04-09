#pragma once
#include "standardInclude.h"

// Merken : https://www.sfml-dev.org/tutorials/2.0/graphics-vertex-array.php

Int64 getCurrentTime()
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
	);
	return ms.count();
}


void scali(ShapeRectangle& rect, Vector2f origin,  Vector2f scale = Vector2f(1.05f, 1.05f))
{
	// Die Originalposition der linken oberen Ecke herausfinden
	Transform w;
	float rotation = rect.getRotation();
	Vector2f wcale = rect.getScale();
	Vector2f iScale = Vector2f(1.0f / wcale.x, 1.0f / wcale.y);
	w.rotate(rotation);
	w.scale(wcale);
	w.rotate(-rotation, origin);
	w.scale(iScale, origin);
	Vector2f originalGlobalPos = w.transformPoint(rect.getPosition());


	// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
	Vector2f oldPos = rect.getPosition();

	// Die globale Position des Origins herausfinden
	Vector2f globalOrigin = originalGlobalPos + origin;

	// Setze den Shape an den gew�nschten Origin und drehe es um die gew�nschten Grad
	rect.setOrigin(origin);
	rect.setPosition(globalOrigin);
	rect.shape->scale(scale);

	/* Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben*/
	sf::Transform t; 
	wcale = rect.getScale();
	t.rotate(rotation, globalOrigin);
	t.scale(wcale, globalOrigin);
	//t.rotate(rotation, origin);
	Vector2f newPos = t.transformPoint(originalGlobalPos);
	rect.setOrigin(Vector2f(0, 0));
	rect.setPosition(newPos);
}
void rotati(ShapeRectangle& rect, Vector2f origin, float offsetAngle = 10.f)
{
	// Die Originalposition der linken oberen Ecke herausfinden
	Transform w;
	float rotation = rect.getRotation();
	Vector2f scale = rect.getScale();
	Vector2f iScale = Vector2f(1.0f / scale.x, 1.0f / scale.y);
	w.rotate(rotation);
	w.scale(scale);
	w.rotate(-rotation, origin);
	w.scale(iScale, origin);
	Vector2f originalGlobalPos = w.transformPoint(rect.getPosition());

	// Zwischenspeichern wo die linke obere Ecke jetzt gerade ist
	Vector2f oldPos = rect.getPosition();

	// Die globale Position des Origins herausfinden
	Vector2f globalOrigin = originalGlobalPos + origin;

	// Setze den Shape an den gew�nschten Origin und drehe es um die gew�nschten Grad
	rect.setOrigin(origin);
	rect.setPosition(globalOrigin);
	rect.shape->rotate(offsetAngle);

	// Linke obere Ecke wieder ans Origin setzen ohne das Rechteck zu verschieben
	sf::Transform t;
	t.rotate(offsetAngle, globalOrigin);
	Vector2f newPos = t.transformPoint(oldPos);
	rect.setOrigin(Vector2f(0, 0));
	rect.setPosition(newPos);
}




int main()
{
	ConfigHelper conf("test.txt");
	conf.write("GOL", "BackgroundColor", "fff01fff");
	windowDef::get().windowSizeX = stoi(conf.get("Window", "WindowSizeX"));
	windowDef::get().windowSizeY = stoi(conf.get("Window", "WindowSizeY"));
	windowDef::get().windowStyle = stoi(conf.get("Window", "WindowStyle"));

	SavefileHelper s = SavefileHelper();

	s.encryptDecrypt("\x3&.q<\"$q,&?%");
	conf.write("GOL", "BackgroundColor", "fffe8fff");


	/*
	Das Renderwindow ist f�r das zeichnen der verschiedenen Formen benutzt. 
	Es k�nnen noch weitere Parameter �bergeben werden, die daf�r verantwortlich sind, 
	ob das Fenster keinen CloseKnopf hat, nicht gr��enver�nderbar ist...
	*/
	RenderWindow window(VideoMode(windowDef::get().windowSizeX, windowDef::get().windowSizeY), "Snake", windowDef::get().windowStyle);// , Style::Fullscreen);
	SceneHandler *sceneHandler = new SceneHandler();

	// Hier kann und soll eine Einstiegsszene definiert werden, kann auch erst bei einem Event unten stattfinden
	Scene *startMenu = new SceneStartMenu("Menu", sceneHandler, &window);
	sceneHandler->addScene(startMenu);
	
	//Parameter die f�r die verbesserte Spielschleife notwendig sind.
	// Die Loop soll im Update die wahre Position und Geschwindigkeit von Objekten abspeichern, der Renderer tut dann mithilfe der 2 Werte eine extrapolierte Position rendern
	// render(lag / MS_PER_UPDATE);
	Int64 lag = 0;
	Int64 previous = getCurrentTime();

	// Quick FPS Counter
	int frameCount = 0;
	int loop = 0;

	Font* font = new Font();
	font->loadFromFile("Textures/cool.ttf");

	Text* FPS = new Text();
	FPS->setFont(*font);
	FPS->setString(to_string(frameCount));
	FPS->setCharacterSize(20);
	FPS->setFillColor(Color::Cyan);

	ShapeRectangle bg(windowDef::get().windowSizeX, windowDef::get().windowSizeY, Color::Red);
	ShapeRectangle rect(Vector2f(600, 300));
	rect.setFillColor(Color::White);
	alignTo(rect, bg);

	ShapeRectangle porigin(Vector2f(2, 2));
	porigin.setFillColor(Color::Blue);

	//rotati(rect, Vector2f(300, 150));
	//scali(rect, Vector2f(300,150));
	// tests
	

	
	

	while (window.isOpen())
	{
		vector<Event> windowEvents;
		Int64 current = getCurrentTime();
		Int64 elapsed = current - previous;
		previous = current;
		lag += elapsed;

		//Verarbeitung der Eingaben und Events
		Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (windowEvent.key.code == Keyboard::Escape)
					window.close();	
				break;
			}
			sceneHandler->handleEvents(window, windowEvent);
		}
		
		sceneHandler->handleInputs(window);

		//Verarbeitung der Bewegungen und Positionsaktuallisierungen
		while (lag >= MS_PER_UPDATE)
		{
			//Ruft die Aktualisierungsmethode auf
			sceneHandler->update();
			//FPSCOUNTER
			loop++;
			if (loop == 1000 / MS_PER_UPDATE) {
				loop = 0;
				FPS->setString(to_string(frameCount));
				frameCount = 0;
			}

			lag -= MS_PER_UPDATE;

		}
	
		//Zeichnen der Objekte
		window.clear();

		//sceneHandler->render(window, RenderStates(), float(lag) / float(MS_PER_UPDATE));
		bg.draw(window, RenderStates());
		rect.draw(window, RenderStates());
		//FPSCOUNTER
		window.draw(*FPS);
		frameCount++;
		window.display();	
	}

	return 0;
}