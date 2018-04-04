#pragma once

class SceneHandler
{
public:
	SceneHandler();
	~SceneHandler();

	// Mainfunktionalität der Gameloop
	void handleEvents(RenderWindow& window, Event windowEvent);
	void handleInputs(RenderWindow& window);
	void update();
	void render(RenderWindow& window, RenderStates shades);

	// Verschiedene Helper um Interaktion zwischen Scenes zu erleichtern
	void addScene(Scene * createScene, int visible = ALL);
	void addScene(Scene * createScene, bool onTop, int visible = ALL);
	void deleteScene(string sceneName);
	void setTopScene(string sceneName);
	void setSceneVisibility(string sceneName, int visibility);

	// Helper Scenes mit anderen Scenes interagieren zu lassen
	int getSceneIndexByName(string sceneName);
	bool sceneExists(string sceneName);
	Scene* getSceneByName(string sceneName);

private:
	vector<Scene*> vScenes;
};

