#pragma once
#include "Scene.h"

class Scene;
class SceneHandler
{
public:
	SceneHandler();
	~SceneHandler();

	// Mainfunktionalität der Gameloop
	void handleEvents(RenderWindow& window, Event& windowEvent);
	void handleInputs(RenderWindow& window);
	void update();
	void render(RenderWindow& window, RenderStates& shades, float timeTillUpdate);

	// Verschiedene Helper um Interaktion zwischen Scenes zu erleichtern
	void addScene(string name, Scene * createScene, eVisibilityFlags visible = ALL);
	void addScene(string name, Scene * createScene, bool onTop, eVisibilityFlags visible = ALL);
	void deleteScene(string sceneName);
	void setTopScene(string sceneName);
	void setScenePriority(string name, int priority);
	void setSceneVisibility(string name, eVisibilityFlags visible);

	Scene* const getSceneByName(string name);

	// Helper Scenes mit anderen Scenes interagieren zu lassen
	bool sceneExists(string sceneName);
protected:
	UnorderdMap<string, Scene*> vScenes;
};

