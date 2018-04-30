#pragma once
#include "AnimationInclude.h"
#include "ConfigHelper.h"
#include "GlobalVariables.h"
#include "SceneHandler.h"
#include "SceneStartMenu.h"
#include "ShapeRectangle.h"
#include "ShapeCircle.h"

Int64 getCurrentTime()
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
		);
	return ms.count();
}

int main()
{
	vector<function<void(void)>> func;

	for (unsigned int i = 0; i < 10; i++)
	{
		func.push_back([i]() {printf("%d\n", i); });
	}

	for (unsigned int i = 0; i < 10; i++)
	{
		func.at(i)();
	}

	vector<Vertex> vert;

	for (unsigned int i = 0; i < 100000; i++)
	{
		/*vert.push_back(Vertex(Vector2f(i * 10 - (i / 100) * 1000		, (i / 100) * 10)));
		vert.push_back(Vertex(Vector2f(i * 10 - (i / 100) * 1000 + 10	, (i / 100) * 10)));
		vert.push_back(Vertex(Vector2f(i * 10 - (i / 100) * 1000 + 10	, (i / 100) * 10 + 10)));
		vert.push_back(Vertex(Vector2f(i * 10 - (i / 100) * 1000		, (i / 100) * 10 + 10)));*/
	}



	UnorderdMap<string, ShapeRectangle> myObjects2;

	for (unsigned int i = 0; i < 10; i++)
	{
		myObjects2.push(to_string(i), ShapeRectangle(FloatRect(i * 150, 100, 100, 100), Color::Green));
	}



	ConfigHelper conf("Test.txt");
	windowDef::get().windowSizeX = float(stoi(conf.get("Window", "WindowSizeX")));
	windowDef::get().windowSizeY = float(stoi(conf.get("Window", "WindowSizeY")));
	windowDef::get().windowStyle = stoi(conf.get("Window", "WindowStyle"));

	//Test Box2D
	b2Vec2 gravity(0, -10.0f);
	Box2DWorld world(gravity);

	//Setup Static Body
	//SetPos
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -100.0f);
	//Create BodyObject with world
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	//Define Size and Shape
	b2PolygonShape groundBox;
	groundBox.SetAsBox(500.0f, 100.0f);
	//create fixture of Body			Weight of Box
	groundBody->CreateFixture(&groundBox,	0.0f);

	b2BodyDef kDef;
	kDef.type = b2_kinematicBody;
	kDef.position.Set(-130.0f, 10.0f);
	//Create BodyObject with world
	b2Body* kBody = world.CreateBody(&kDef);
	//Define Size and Shape
	b2PolygonShape kBox;
	kBox.SetAsBox(10.0f, 10.0f);
	//create fixture of Body			Weight of Box
	kBody->CreateFixture(&kBox, 0.0f);
	//kBody->SetLinearVelocity(b2Vec2(50.0f,0.0f));

	//Setup Dynamic Body
	//set Pos and cast dynamic
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 440.0f);
	//create bodyObject with world
	b2Body* body = world.CreateBody(&bodyDef);
	//Define Size and shape
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(10.0f, 10.0f);
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
	ShapeRectangle box(FloatRect(0.0f, 0.0f, 20.0f, 20.0f), Color::White);
	ShapeRectangle enemy(FloatRect(0.0f, 0.0f, 20.0f, 20.0f), Color::White);


	/*
	Das Renderwindow ist für das zeichnen der verschiedenen Formen benutzt.
	Es können noch weitere Parameter übergeben werden, die dafür verantwortlich sind,
	ob das Fenster keinen CloseKnopf hat, nicht größenveränderbar ist...
	*/

	CircleShape punkt = CircleShape(4);
	punkt.setFillColor(Color::Red);

	RenderWindow window(VideoMode(int(windowDef::get().windowSizeX), int(windowDef::get().windowSizeY)), "Engine");// , windowDef::get().windowStyle);
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(0);
	SceneHandler &sceneHandler = SceneHandler();

	// Hier kann und soll eine Einstiegsszene definiert werden, kann auch erst bei einem Event unten stattfinden
	Scene *startMenu = new SceneStartMenu(sceneHandler, &window);
	sceneHandler.addScene("Menu", startMenu);

	AnimationHandler handler;
	Animation animation(20);
	BaseResource block1(new ShapeCircle(100.0f, Color::Blue));
	BaseResource block2(new ShapeRectangle(FloatRect(700.0f, 700.0f, 200.0f, 100.0f), Color::Red));
	Font* f = new Font();
	f->loadFromFile("Textures/cool.ttf");
	block1.addText(new ObjectText("BasisText", *f));

	//animation.addSubAnimation("rotate", new AniSetRotation(5000, -200, Vector2f(block1.objectText->getLocalBounds().width / 2.0f - block1.objectText->getLocalBounds().left, block1.objectText->getLocalBounds().height / 2.0f - block1.objectText->getLocalBounds().width / 2.0f - block1.objectText->getLocalBounds().top)));
	//animation.addSubAnimation("move", new AniSetPosition(5000, Vector2f(1400, 400), BezierHandles(0.1f, 0.9f, 0.1f,0.9f)));
	animation.addSubAnimation("Scale4", new AniScale(10000, Vector2f(1.0f, 2.0f), Vector2f(100,100)));
	//animation.addSubAnimation("rotate2", new AniMove(10000, Vector2f(1.0f, 4.0f)));
	//animation.addSubAnimation("rotate", new AniRotate(2000, 150, Vector2f(100, 50)));
	//animation.addSubAnimation("scale", new AniSetScale(2000, Vector2f(2, 2), Vector2f(100, 50)));
	//animation.addSubAnimation("scale", new AniSetScale(2000, Vector2f(3, 3), Vector2f(100, 50)),2000);
	//animation.addSubAnimation("scale", new AniSetScale(2000, Vector2f(1, 1), Vector2f(100, 50)),4000);
	//animation.addSubAnimation("scale2", new AniScale(2000, Vector2f(-2, -2), Vector2f(100, 50)), 2000);

	animation.addObject(&block1);
	animation.addObject(&block2, ObjectOnly);
	animation.addKeyFrame("Scale4", eKeyFrameAction::ANIPAUSE, 1000);
	animation.addKeyFrame("Scale4", eKeyFrameAction::ANIRESUME, 2000);

	handler.addAnimation("rotate", &animation);
	handler.run("rotate");

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

	Vector2f k;

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
			world.update(timeStep);
			float positionY = windowDef::get().windowSizeY / 2 - body->GetPosition().y - 10.0f;
			float positionX = windowDef::get().windowSizeX / 2 + body->GetPosition().x - 10.0f;
			box.setPosition(Vector2f(positionX, positionY));

			positionY = windowDef::get().windowSizeY / 2 - kBody->GetPosition().y - 10.0f;
			positionX = windowDef::get().windowSizeX / 2 + kBody->GetPosition().x - 10.0f;
			enemy.setPosition(Vector2f(positionX, positionY));
			handler.update();

			//FPSCOUNTER
			loop++;
			if (loop == 1000 / MS_PER_UPDATE) {
				loop = 0;
				FPS->setString(to_string(frameCount));
				frameCount = 0;
			}

			lag -= MS_PER_UPDATE;
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			//{
			//	/*body->SetActive(false);
			//	p = block1.objectText->getPosition() - block1.objectShape->getPosition();
			//	Transform t;
			//	t.scale(Vector2f(1.f / scaleText.x, 1.f / scaleText.y));
			//	t.rotate(-block1.objectText->getRotation());
			//	k = t.transformPoint(p);

			//	
			//	scaleText = block1.objectText->getScale();
			//	Vector2f textOrigin = Vector2f((-k.x + 100.f) / (scaleText.x/scaleShape.x), (-k.y + 50.f) / (scaleText.y/scaleShape.y));
			//	punkt.setPosition(textOrigin + block1.objectText->getPosition());
			//	block1.objectText->rotate(1.f, textOrigin);
			//	block1.objectShape->rotate(1.f, Vector2f(100, 50));

			//	
			//	cout << textOrigin.x <<  " " << textOrigin.y << "\n";*/
			//}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			//{
			//	body->SetActive(true);
			//	block1.objectText->rotate(1.f, Vector2f(-37.5f , -30.f));
			//	block1.objectShape->rotate(1.f, Vector2f(0, 0));
			//}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			//{
			//	block1.objectText->scale(Vector2f(1.1f, 1.1f), Vector2f(0,0));
			//}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			//{
			//	p = block1.objectText->getPosition() - block1.objectShape->getPosition();
			//	Transform t;
			//	t.rotate(-block1.objectText->getRotation());
			//	k = t.transformPoint(p);


			//	Vector2f scaleText = block1.objectText->getScale();
			//	block1.objectText->scale(Vector2f(1.1f, 1.1f), Vector2f(-k.x / scaleText.x + 200.f, -k.y / scaleText.y + 100.f));
			//	block1.objectShape->scale(Vector2f(1.1f, 1.1f), Vector2f(200, 100));
			//}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			//{
			//	/*long long i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	i = myObjects.getQueObject("99998");
			//	myObjects.functions.at(i).render = machwas2;*/
			//}
		}

		//Zeichnen der Objekte
		window.clear();
		sceneHandler.render(window, RenderStates(), float(lag) / float(MS_PER_UPDATE));
		//FPSCOUNTER
		//ground.draw(window, RenderStates());
		//box.draw(window, RenderStates());
		//enemy.draw(window, RenderStates());

		//block1.draw(window, RenderStates());
		//block2.draw(window, RenderStates());

		//window.draw(&vert[0], vert.size(), sf::Quads);
		window.draw(*FPS);
		frameCount++;
		window.display();
	}

	return 0;
}