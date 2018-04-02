#pragma once
class SceneHandler;

class Scene
{
public:
	Scene(string name, SceneHandler * sceneHandler, RenderWindow* window = nullptr, int visible = ALL);
	~Scene();

	// Mainfunktionaltität der Gameloop -> Möglichkeit keine handleInput Methode zu definieren (z. B. statische Overlays zum Anzeigen von Stats)
	virtual bool setupResources() = 0;
	virtual void handleInput(RenderWindow& window, Event windowEvent);
	virtual void update();
	virtual void render(RenderWindow& window, RenderStates shades);

	// Scenespezifische Funktionen
	string getSceneName();
	SceneHandler* getSceneHandler() const;

	template <typename returnType>
	returnType addResource(string name, returnType toAdd) {
		objects.push(name, toAdd);
		return toAdd;
	}

	// Scenespezifische Variablen
	int visible;

protected:
	//Alle Objekte die eine Szene beinhaltet, werden hier gespeichert
	
	UnorderdMap<String, ObjectBase*> objects;
	RenderWindow* window;
	string sceneName;

private:
	
	// Jede Szene bekommt den Scenehandler damit er es als Interface benutzen kann um die anderen Szenen anzusprechen
	SceneHandler*  sceneHandler;
};

