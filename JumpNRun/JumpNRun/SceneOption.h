#pragma once

class SceneOption : public Scene
{
public:
	SceneOption(string name, SceneHandler& sceneHandler);
	~SceneOption();

	bool setupResources();
	void update();

private:
	Color color;
};

