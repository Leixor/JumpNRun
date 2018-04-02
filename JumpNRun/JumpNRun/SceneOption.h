#pragma once

class SceneOption : public Scene
{
public:
	SceneOption(string name, SceneHandler * sceneHandler);
	~SceneOption();

	bool setupResources();
private:
	void checkAction(bool checked, ObjectBase* sender);
};

