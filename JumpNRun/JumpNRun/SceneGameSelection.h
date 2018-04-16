#pragma once
#include "Scene.h"
#include "SceneSnakeGame.h"
#include "SceneGOL.h"
#include "ShapeRectangle.h"
#include "Button.h"

class SceneGameSelection : public Scene
{
public:
	SceneGameSelection(string name, SceneHandler& sceneHandler, RenderWindow* window);
	~SceneGameSelection();

	void snakeStart();
	void golStart();
private:
	bool setupResources();
};

