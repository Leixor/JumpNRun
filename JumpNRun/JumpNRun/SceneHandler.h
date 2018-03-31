#pragma once

class SceneHandler
{
public:
	SceneHandler();
	~SceneHandler();

	// Mainfunktionalität der Gameloop
	void handleInput(RenderWindow& window, Event windowEvent);
	void update();
	void render(RenderWindow& window);

	// Verschiedene Helper um Interaktion zwischen Scenes zu erleichtern
	void addScene(Scene * createScene, bool onTop = false);
	void deleteScene(string sceneName);
	void setTopScene(string sceneName);
	void setSceneVisibility(string sceneName, bool visibility);

	// Helper Scenes mit anderen Scenes interagieren zu lassen
	int getSceneIndexByName(string sceneName);
	bool sceneExists(string sceneName);
	Scene* getSceneByName(string sceneName);

private:
	vector<Scene*> vScenes;
};

