#pragma once

class SceneGameSelection : public Scene
{
public:
	SceneGameSelection(string name, SceneHandler * sceneHandler, RenderWindow* window);
	~SceneGameSelection();

	void snakeStart();
	void golStart();
private:
	bool setupResources();
};

