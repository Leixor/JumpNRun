#pragma once
#include "Scene.h"
#include "DropdownList.h"
#include "ShapeRectangle.h"
#include "Slider.h"

class SceneOption : public Scene
{
public:
	SceneOption(string name, SceneHandler& sceneHandler);
	~SceneOption();

	bool setupResources();
	void update();
private:
	string colorOrigin;
	Font* fonts;
	DropdownList* snakeOption;
};

