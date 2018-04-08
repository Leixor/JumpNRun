#pragma once

class SceneGameSelection : public Scene
{
public:
	SceneGameSelection(string name, SceneHandler * sceneHandler);
	~SceneGameSelection();

private:
	bool setupResources();
};

