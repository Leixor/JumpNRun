#pragma once

class SceneStartMenu : public Scene
{
public:
	SceneStartMenu(string name, SceneHandler * sceneHandler, RenderWindow* window);
	~SceneStartMenu();

	bool setupResources();

private:
	void buttonStartAction();
	void buttonEndAction();
	void buttonOptionAction();
};

