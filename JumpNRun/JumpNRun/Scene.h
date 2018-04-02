#pragma once
class SceneHandler;

class Scene
{
public:
	Scene(string name, SceneHandler * sceneHandler, RenderWindow* window = nullptr);
	~Scene();

	// Mainfunktionaltit�t der Gameloop -> M�glichkeit keine handleInput Methode zu definieren (z. B. statische Overlays zum Anzeigen von Stats)
	virtual bool setupResources() = 0;
	virtual void handleInput(RenderWindow& window, Event windowEvent);
	virtual void update();
	virtual void render(RenderWindow& window, RenderStates shades);

	// Scenespezifische Funktionen
	string getSceneName() const;
	SceneHandler* getSceneHandler() const;

	// Scenespezifische Variablen
	bool visible = true;

protected:
	//Alle Objekte die eine Szene beinhaltet, werden hier gespeichert
	
	UnorderdMap<String, ObjectBase*> objects;
	RenderWindow* window;

private:
	string sceneName;
	// Jede Szene bekommt den Scenehandler damit er es als Interface benutzen kann um die anderen Szenen anzusprechen
	SceneHandler*  sceneHandler;
};

