#include "SceneStartMenu.h"

SceneStartMenu::SceneStartMenu(SceneHandler& sceneHandler, RenderWindow* window)
	: Scene(sceneHandler, window)
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
	this->objects.get("Button_Start")->getText()->setCharacterSize(50);
	
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_Option")->addText(new ObjectText("Optionen", *this->font));
	this->objects.get("Button_Option")->getText()->setCharacterSize(50);

	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_End")->addText(new ObjectText("Beenden", *this->font));
	this->objects.get("Button_End")->getText()->setCharacterSize(50);
	
	alignTo(*optionButton->getShape(), *this->objects.get("Background")->getShape());
	optionButton->getShape()->move(Vector2f(0, 100));
	alignNextTo(*startButton->getShape(), *optionButton->getShape(), LEFT, 50);
	alignNextTo(*endButton->getShape(), *optionButton->getShape(), RIGHT, 50);
	alignTo(*this->objects.get("Button_Start")->getText(), *this->objects.get("Button_Start")->getShape());
	alignTo(*this->objects.get("Button_Option")->getText(), *this->objects.get("Button_Option")->getShape());
	alignTo(*this->objects.get("Button_End")->getText(), *this->objects.get("Button_End")->getShape());

	addResource("SnakeCover", new ObjectBase(new ShapeSprite("Textures/Cover_Snake.png")));
	this->objects.get("SnakeCover")->getShape()->setPosition(Vector2f(300, 100));
	this->objects.get("SnakeCover")->getShape()->setSize(Vector2f(1000, 600));

	alignTo(*this->objects.get("SnakeCover")->getShape(), *this->objects.get("Background")->getShape(), TOP, -50);

	return true;
}

void SceneStartMenu::buttonStartAction()
{
	this->setVisibility(INPUTABLE);
	this->getSceneHandler().addScene("GameSelection", new SceneGameSelection(this->getSceneHandler(), window), VISIBLE);
}

void SceneStartMenu::buttonOptionAction()
{
	this->getSceneHandler().addScene("Option", new SceneOption(this->getSceneHandler()), ALL);
	this->setVisibility(UPDATABLE);
}

void SceneStartMenu::buttonEndAction()
{
	/*this->window->close();*/
	/*myAni->run();*/
}
