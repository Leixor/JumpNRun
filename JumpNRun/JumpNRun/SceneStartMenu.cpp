#include "SceneStartMenu.h"

SceneStartMenu::SceneStartMenu(string name, SceneHandler& sceneHandler, RenderWindow* window)
	: Scene(name, sceneHandler, window)
{
	this->setupResources();
}

SceneStartMenu::~SceneStartMenu()
{
}

void SceneStartMenu::handleEvents(RenderWindow & window, Event& windowEvent)
{
	Scene::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::MouseButtonReleased && this->getSceneHandler().sceneExists("GameSelection"))
	{
		this->setVisibility(UPDATABLE);
		this->getSceneHandler().getSceneByName("GameSelection")->setVisibility(ALL);
	}
}

bool SceneStartMenu::setupResources()
{
	configHelper = new ConfigHelper("test.txt");
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");
	
	string bgColor = configHelper->get("Menu","BackgroundColor");
	addObject("Background", new ShapeRectangle(float(windowDef::get().windowSizeX), float(windowDef::get().windowSizeY), Color::Color(stoul(bgColor, nullptr, 16))));

	startButton = addResource<Button*>("Button_Start", new Button([&] {buttonStartAction();}, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_Start")->addText(new ObjectText("Start", *this->font));
	this->objects.get("Button_Start")->getObjectText()->setCharacterSize(50);
	
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_Option")->addText(new ObjectText("Optionen", *this->font));
	this->objects.get("Button_Option")->getObjectText()->setCharacterSize(50);

	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_End")->addText(new ObjectText("Beenden", *this->font));
	this->objects.get("Button_End")->getObjectText()->setCharacterSize(50);
	
	alignTo(*optionButton->getObjectShape(), *this->objects.get("Background")->getObjectShape());
	optionButton->getObjectShape()->move(Vector2f(0, 100));
	alignNextTo(*startButton->getObjectShape(), *optionButton->getObjectShape(), LEFT, 50);
	alignNextTo(*endButton->getObjectShape(), *optionButton->getObjectShape(), RIGHT, 50);
	alignTo(*this->objects.get("Button_Start")->getObjectText(), *this->objects.get("Button_Start")->getObjectShape());
	alignTo(*this->objects.get("Button_Option")->getObjectText(), *this->objects.get("Button_Option")->getObjectShape());
	alignTo(*this->objects.get("Button_End")->getObjectText(), *this->objects.get("Button_End")->getObjectShape());

	addResource("SnakeCover", new ObjectBase(new DrawableShape<Sprite>()));
	this->objects.get("SnakeCover")->getObjectShape()->setTexture("Textures/Cover_Snake.png");
	this->objects.get("SnakeCover")->getObjectShape()->setPosition(Vector2f(300, 100));
	this->objects.get("SnakeCover")->getObjectShape()->setSize(Vector2f(1000, 600));

	alignTo(*this->objects.get("SnakeCover")->getObjectShape(), *this->objects.get("Background")->getObjectShape(), TOP, -50);

	return true;
}

void SceneStartMenu::buttonStartAction()
{
	this->setVisibility(INPUTABLE);
	this->getSceneHandler().addScene(new SceneGameSelection("GameSelection", this->getSceneHandler(), window), VISIBLE);
}

void SceneStartMenu::buttonOptionAction()
{
	this->getSceneHandler().addScene(new SceneOption("Option", this->getSceneHandler()), ALL);
	this->setVisibility(UPDATABLE);
}

void SceneStartMenu::buttonEndAction()
{
	/*this->window->close();*/
	/*myAni->run();*/
}
