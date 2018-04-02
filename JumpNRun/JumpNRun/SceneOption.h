#pragma once

class SceneOption : public Scene
{
public:
	SceneOption(string name, SceneHandler * sceneHandler);
	~SceneOption();

	bool setupResources();
private:
	CheckBox* colorCheckbox;
	CheckBox* otherCheckbox;
	void checkAction(bool checked, ObjectBase* sender);
	void otherAction();
};

