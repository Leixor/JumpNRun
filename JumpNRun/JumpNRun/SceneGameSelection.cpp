#include "StandardInclude.h"

SceneGameSelection::SceneGameSelection(string name, SceneHandler * sceneHandler)
	:Scene(name, sceneHandler)
{
	this->setupResources();
}

SceneGameSelection::~SceneGameSelection()
{
}

bool SceneGameSelection::setupResources()
{
	conf = new ConfigHelper("Test.txt");

	addObject("BackGround", new ShapeRectangle(FloatRect(0.0f, 0.0f, float(windowDef::get().windowSizeX), float(windowDef::get().windowSizeY)), Color(200,200,200,255)));

	addObject("SnakeButton", new ShapeRectangle(FloatRect(0.0f, 0.0f, float(windowDef::get().windowSizeX) / 2.0f, float(windowDef::get().windowSizeY)), Color::Transparent, 10.0f, Color::White));
	alignTo(*this->objects.get("SnakeButton")->shape, *this->objects.get("BackGround")->shape, LEFT, 10);

	this->getSceneHandler()->addScene(new SceneSnakeGame("SnakeGame", this->getSceneHandler(), Vector2u(15, 15), 6));
	this->getSceneHandler()->setTopScene("SnakeGame");
	this->getSceneHandler()->getSceneByName("SnakeGame")->setVisibility(VISIBLE);
	this->getSceneHandler()->getSceneByName("SnakeGame")->setView(View(FloatRect(50, 50, 600, 600)));
	this->getSceneHandler()->getSceneByName("SnakeGame")->setSceneScaling(Vector2f(1, 0.5));

	return false;
}
