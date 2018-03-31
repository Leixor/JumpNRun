#pragma once
#include "standardInclude.h"
#include "Scenes.h"
int main()
{
	RenderWindow window(VideoMode(400, 400), "Jump and Run!");
	SceneHandler *sceneHandler = new SceneHandler();


	// Hier kann und soll eine Einstiegsszene definiert werden, kann auch erst bei einem Event unten stattfinden
	Scene *test = new TestSzene("Test", sceneHandler);
	sceneHandler->addScene(test);

	/* Folgender Testablauf wurde gemacht, die Testszene tut beim klicken auf den Roten 
	Button eine neue Szene selbstständig kreieren und zwar von der anderen Subklasse 
	OverlayTestSzene (diese wird beim adden gleichzeitig nach oben in die Pipeline gestellt), wenn man jetzt auf den grünen 
	Button von OverlayTestSzene klickt, macht man den roten Button  (und die ganze Szene) von TestSzene unsichtbar, mit einem "A" 
	Keyboard klick macht man sie wieder sichtbar. 
	Der ganze Testablauf diente nur zum probieren aller Funktionen des Scenehandlers
	*/


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

		sceneHandler->handleInput(window);
		sceneHandler->update();
		window.clear();
		sceneHandler->render(window);
		window.display();
	}

	return 0;
}