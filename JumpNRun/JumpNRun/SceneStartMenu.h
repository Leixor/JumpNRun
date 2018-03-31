#pragma once

class SceneStartMenu : public Scene
{
public:
	SceneStartMenu(string name, SceneHandler * sceneHandler);
	~SceneStartMenu();

	bool setupResources();
	void handleInput(RenderWindow& window, Event windowEvent);
	void update();
	void render(RenderWindow& window);

private:
	map<String, Button> vButton;

	void buttonStartAction();
};

