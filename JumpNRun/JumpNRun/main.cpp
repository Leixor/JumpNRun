#pragma once
#include "ConfigHelper.h"
#include "GlobalVariables.h"
#include "AnimationHandler.h"
#include "AniRotate.h"
#include "AniMove.h"
#include "SceneHandler.h"
#include "SceneStartMenu.h"
#include "ShapeRectangle.h"


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


	/*//Test Box2D
	b2Vec2 gravity(0, -10.0f);
	b2World world(gravity);

	//Setup Static Body
	//SetPos
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	//Create BodyObject with world
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	//Define Size and Shape
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	//create fixture of Body			Weight of Box
	groundBody->CreateFixture(&groundBox,	0.0f);

	//Setup Dynamic Body
	//set Pos and cast dynamic
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	//create bodyObject with world
	b2Body* body = world.CreateBody(&bodyDef);
	//Define Size and shape
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	//set Friction and density
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	//cast fixture to body
	body->CreateFixture(&fixtureDef);

	float32 timeStep = 1.0f / 100.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	ShapeRectangle ground(FloatRect(300.0f, 450.0f, 1000.0f, 200.0f), Color::White);
	ShapeRectangle box(FloatRect(780.0f, 450.0f - 40.0f - 10.0f, 20.0f, 20.0f), Color::White);



	/*
	Das Renderwindow ist für das zeichnen der verschiedenen Formen benutzt.
	Es können noch weitere Parameter übergeben werden, die dafür verantwortlich sind,
	ob das Fenster keinen CloseKnopf hat, nicht größenveränderbar ist...
	*/
	RenderWindow window(VideoMode(int(windowDef::get().windowSizeX), int(windowDef::get().windowSizeY)), "Engine", windowDef::get().windowStyle);// , Style::Fullscreen);
	SceneHandler &sceneHandler = SceneHandler();

	// Hier kann und soll eine Einstiegsszene definiert werden, kann auch erst bei einem Event unten stattfinden
	Scene *startMenu = new SceneStartMenu("Menu", sceneHandler, &window);
	sceneHandler.addScene(startMenu);

	AnimationHandler handler;
	Animation animation;
	ObjectBase block1(new ShapeRectangle(FloatRect(100.0f, 500.0f, 200.0f, 100.0f), Color::Blue));

	Font* f = new Font();
	f->loadFromFile("Textures/cool.ttf");
	block1.addText(new ObjectText("BasisText", *f));

	animation.addSubAnimation("rotate1", new AniRotate(7000, -720, Vector2f(150, 50)));
	animation.addObject(&block1);

	handler.addAnimation("rotate", &animation);

	handler.run("rotate", true);


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
			//world.Step(timeStep, velocityIterations, positionIterations);
			//float positionY = 450.0f - body->GetPosition().y * 10.0f - 10.0f;
			//box.setPosition(Vector2f(780.0f, positionY));
			handler.update();

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
		//window.draw(*ground.shape);
		//window.draw(*box.shape);
		block1.draw(window, RenderStates());
		window.draw(*FPS);
		frameCount++;
		window.display();
	}

	return 0;
}