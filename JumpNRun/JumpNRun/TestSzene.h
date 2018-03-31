#pragma once
#include "standardInclude.h"
#include "Scene.h"
#include "Scenes.h"
class TestSzene : public Scene
{
public:
	TestSzene(std::string Name, SceneHandler * sceneHandler);
	~TestSzene();

	bool setupResources();
	void handleInput(RenderWindow& window);
	void update();
	void render(RenderWindow& window);

private:
	// Paar Testresourcen
	Button* movePlayer;
	void machShit();
	bool isPressed = false;
};

