#pragma once

class TestSzene : public Scene
{
public:
	TestSzene(std::string Name, SceneHandler * sceneHandler);
	~TestSzene();

	bool setupResources();
	void handleInput(RenderWindow& window, Event windowEvent);
	void update();
	void render(RenderWindow& window);

private:
	// Paar Testresourcen
	Button* toggleOverlay;
	void toggleOverlayAction();
	bool isPressed = false;
};

