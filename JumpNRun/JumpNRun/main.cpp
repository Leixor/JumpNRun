#pragma once
#include "standardInclude.h"


Int64 getCurrentTime()
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
	);
	return ms.count();
}

int main()
{
	ConfigHelper conf("Test.txt");
	windowDef::get().windowSizeX = float(stoi(conf.get("Window", "WindowSizeX")));
	windowDef::get().windowSizeY = float(stoi(conf.get("Window", "WindowSizeY")));
	windowDef::get().windowStyle = stoi(conf.get("Window", "WindowStyle"));

	/*
	Das Renderwindow ist für das zeichnen der verschiedenen Formen benutzt. 
	Es können noch weitere Parameter übergeben werden, die dafür verantwortlich sind, 
	ob das Fenster keinen CloseKnopf hat, nicht größenveränderbar ist...
	*/
	RenderWindow window(VideoMode(int(windowDef::get().windowSizeX), int(windowDef::get().windowSizeY)), "Snake", windowDef::get().windowStyle);// , Style::Fullscreen);
	SceneHandler &sceneHandler = SceneHandler();

	// Hier kann und soll eine Einstiegsszene definiert werden, kann auch erst bei einem Event unten stattfinden
	Scene *startMenu = new SceneStartMenu("Menu", sceneHandler, &window);
	sceneHandler.addScene(startMenu);
	
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
	FPS->setCharacterSize(20);
	FPS->setFillColor(Color::Cyan);	

	while (window.isOpen())
	{
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
			}
			sceneHandler.handleEvents(window, windowEvent);
		}
		
		sceneHandler.handleInputs(window);

		//Verarbeitung der Bewegungen und Positionsaktuallisierungen
		while (lag >= MS_PER_UPDATE)
		{
			//Ruft die Aktualisierungsmethode auf
			sceneHandler.update();
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
		sceneHandler.render(window, RenderStates(), float(lag) / float(MS_PER_UPDATE));
		//FPSCOUNTER
		window.draw(*FPS);
		frameCount++;
		window.display();	
	}

	return 0;
}