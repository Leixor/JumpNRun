#include "SceneGameSelection.h"

SceneGameSelection::SceneGameSelection(SceneHandler& sceneHandler, RenderWindow* window)
	:Scene(sceneHandler, window)
{
	this->setupResources();
}

SceneGameSelection::~SceneGameSelection()
{
}

void SceneGameSelection::snakeStart()
{
	this->getSceneHandler().setSceneVisibility("GOL", NONE);
	this->getSceneHandler().setSceneVisibility("SnakeGame", ALL);
	this->getSceneHandler().setSceneVisibility("GameSelection", NONE);
	this->getSceneHandler().getSceneByName("SnakeGame")->setView(View(FloatRect(0, 0, windowDef::get().windowSizeX, windowDef::get().windowSizeY)));
}

void SceneGameSelection::golStart()
{
	this->getSceneHandler().setSceneVisibility("GOL", ALL);
	this->getSceneHandler().setSceneVisibility("SnakeGame", NONE);
	this->getSceneHandler().setSceneVisibility("GameSelection", NONE);
	this->getSceneHandler().getSceneByName("GOL")->setView(View(FloatRect(0, 0, windowDef::get().windowSizeX, windowDef::get().windowSizeY)));
}

bool SceneGameSelection::setupResources()
{
	configHelper = new ConfigHelper("Test.txt");

	addObject("BackGround", new ShapeRectangle(FloatRect(0.0f, 0.0f, windowDef::get().windowSizeX, windowDef::get().windowSizeY), Color(200,200,200,255)));

	addResource("SnakeButton", new Button([&] {snakeStart(); }, new ShapeRectangle(FloatRect(0.0f, 0.0f, windowDef::get().windowSizeX / 2.0f, windowDef::get().windowSizeY), Color::Transparent, -10.0f, Color::White)));
	alignTo(*this->objects.get("SnakeButton")->getShape(), *this->objects.get("BackGround")->getShape(), LEFT);
	addResource("GOLButton", new Button([&] {golStart(); }, new ShapeRectangle(FloatRect(0.0f, 0.0f, windowDef::get().windowSizeX / 2.0f, windowDef::get().windowSizeY), Color::Transparent, -10.0f, Color::White)));
	alignTo(*this->objects.get("GOLButton")->getShape(), *this->objects.get("BackGround")->getShape(), RIGHT);

	this->getSceneHandler().addScene("SnakeGame", new SceneSnakeGame(this->getSceneHandler(), Vector2u(15, 15), 6));
	this->getSceneHandler().setTopScene("SnakeGame");
	this->getSceneHandler().setSceneVisibility("SnakeGame", VISIBLE);
	this->getSceneHandler().getSceneByName("SnakeGame")->setView(View(FloatRect(50, 50, 600, 600)));
	this->getSceneHandler().getSceneByName("SnakeGame")->setScenePosition(Vector2f(0.0f,0.0f));
	this->getSceneHandler().getSceneByName("SnakeGame")->setSceneScaling(Vector2f(0.5f, 1.0f));

	this->getSceneHandler().addScene("GOL", new SceneGOL(this->getSceneHandler(), window));
	this->getSceneHandler().setTopScene("GOL");
	this->getSceneHandler().setSceneVisibility("GOL", VISIBLE);
	this->getSceneHandler().getSceneByName("GOL")->setView(View(FloatRect(0, 0, windowDef::get().windowSizeX / 2, windowDef::get().windowSizeY)));
	this->getSceneHandler().getSceneByName("GOL")->setScenePosition(Vector2f(0.5f, 0.0f));
	this->getSceneHandler().getSceneByName("GOL")->setSceneScaling(Vector2f(0.5f, 1.0f));
	
	return false;
}
