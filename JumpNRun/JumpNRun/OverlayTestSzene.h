#pragma once

class OverlayTestSzene : public Scene
{
public:
	OverlayTestSzene(std::string Name, SceneHandler * sceneHandler);
	~OverlayTestSzene();

	bool setupResources();
	void handleInput(RenderWindow& window, Event windowEvent);
	void update();
	void render(RenderWindow& window);

private:
	Button* OverlayButton;
	void machShit();
	bool isPressed = false;
};

