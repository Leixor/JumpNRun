#pragma once

class SceneStartMenu : public Scene
{
public:
	SceneStartMenu(string name, SceneHandler * sceneHandler, RenderWindow* window);
	~SceneStartMenu();

	bool setupResources();
	void handleEvents(RenderWindow & window, Event windowEvent);

private:
	Font* font;
	Texture m_texture;

	void buttonStartAction();
	void buttonEndAction();
	void buttonOptionAction();

	Button* startButton;
	Button* optionButton; 
	Button* endButton;
	Animation* myAni;
	Animation* myAniReverse;
};

