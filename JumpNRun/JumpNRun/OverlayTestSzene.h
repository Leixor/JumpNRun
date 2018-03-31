#pragma once

#include "standardInclude.h"
#include "Scene.h"
class OverlayTestSzene : public Scene
{
public:
	OverlayTestSzene(std::string Name, SceneHandler * sceneHandler);
	~OverlayTestSzene();

	bool setupResources();
	void handleInput(RenderWindow& window);
	void update();
	void render(RenderWindow& window);

private:
	Button* OverlayButton;
	void machShit();
	bool isPressed = false;
};

