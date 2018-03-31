#pragma once
class SceneHandler;

class Scene
{
public:
	Scene(string name, SceneHandler * sceneHandler);
	~Scene();

	// Mainfunktionaltität der Gameloop -> Möglichkeit keine handleInput Methode zu definieren (z. B. statische Overlays zum Anzeigen von Stats)
	virtual bool setupResources() = 0;
	virtual void handleInput(RenderWindow& window, Event windowEvent) = 0;
	virtual void update() = 0;
	virtual void render(RenderWindow& window) = 0;

	// Scenespezifische Funktionen
	string getSceneName() const;
	SceneHandler* getSceneHandler() const;

	// Scenespezifische Variablen
	bool visible = true;

private:
	string sceneName;
	// Jede Szene bekommt den Scenehandler damit er es als Interface benutzen kann um die anderen Szenen anzusprechen
	SceneHandler *  sceneHandler;
};

