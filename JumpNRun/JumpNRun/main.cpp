#pragma once
#include "standardInclude.h"

// Merken : https://www.sfml-dev.org/tutorials/2.0/graphics-vertex-array.php

#define MS_PER_UPDATE 50

Int64 getCurrentTime()
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
	);
	return ms.count();
}


int main()
{
	/*
	Das Renderwindow ist für das zeichnen der verschiedenen Formen benutzt. 
	Es können noch weitere Parameter übergeben werden, die dafür verantwortlich sind, 
	ob das Fenster keinen CloseKnopf hat, nicht größenveränderbar ist...
	*/
	RenderWindow window(VideoMode(1600, 900), "Snake"); //Style::Fullscreen);
	SceneHandler *sceneHandler = new SceneHandler();

	// Hier kann und soll eine Einstiegsszene definiert werden, kann auch erst bei einem Event unten stattfinden
	Scene *startMenu = new SceneStartMenu("Menu", sceneHandler, &window);
	sceneHandler->addScene(startMenu);
	
	/* Folgender Testablauf wurde gemacht, die Testszene tut beim klicken auf den Roten 
	Button eine neue Szene selbstständig kreieren und zwar von der anderen Subklasse 
	OverlayTestSzene (diese wird beim adden gleichzeitig nach oben in die Pipeline gestellt), wenn man jetzt auf den grünen 
	Button von OverlayTestSzene klickt, macht man den roten Button  (und die ganze Szene) von TestSzene unsichtbar, mit einem "A" 
	Keyboard klick macht man sie wieder sichtbar. 
	Der ganze Testablauf diente nur zum probieren aller Funktionen des Scenehandlers
	*/




	//Parameter die für die verbesserte Spielschleife notwendig sind.
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
	FPS->setCharacterSize(50);
	FPS->setFillColor(Color::Red);

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
			loop++;
			if (loop == 1000/ MS_PER_UPDATE) {
				loop = 0;
				FPS->setString(to_string(frameCount));
				frameCount = 0;
			}
		}

		//Zeichnen der Objekte
		window.clear();

		sceneHandler->render(window, RenderStates());

		//FPSCOUNTER
		window.draw(*FPS);
		frameCount++;

		window.display();	
	}

	return 0;
}