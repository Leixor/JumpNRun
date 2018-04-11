#pragma once
class SceneHandler;

class Scene
{
public:
	Scene(string name, SceneHandler * sceneHandler, RenderWindow* window = nullptr, View& view = View(FloatRect(0,0, float(windowDef::get().windowSizeX), float(windowDef::get().windowSizeY))));
	~Scene();

	// Mainfunktionaltität der Gameloop -> Möglichkeit keine handleInput Methode zu definieren (z. B. statische Overlays zum Anzeigen von Stats)
	virtual bool setupResources() = 0;
	virtual void handleInputs(RenderWindow& window);
	virtual void handleEvents(RenderWindow& window, Event windowEvent);
	virtual void update();
	virtual void render(RenderWindow& window, RenderStates shades, float timeTillUpdate);
	virtual void confVarUpdate();

	// Scenespezifische Funktionen
	void setVisibility(int visible)
	{
		this->visible = visible;
	}
	void setView(View& view)
	{
		this->view = view;
	}
	void setSceneScaling(Vector2f& scaling);
	void setSceneViewPort(FloatRect& viewPort);
	void setScenePosition(Vector2f& position);

	string getSceneName();
	SceneHandler* getSceneHandler() const;
	int getVisibility()
	{
		return this->visible;
	}
	View& getView()
	{
		return this->view;
	}

	template <typename returnType>
	returnType addResource(string name, returnType toAdd, int priority = -1)
	{
		this->objects.push(name, toAdd);
		if(priority != -1)
			this->setObjectPriority(name,priority);
		return toAdd;
	}
	ObjectBase* addObject(string name, DrawableObject* toAdd, int priority = -1);
protected:
	//Alle Objekte die eine Szene beinhaltet, werden hier gespeichert
	UnorderdMap<string, ObjectBase*> objects;
	RenderWindow* window;
	string sceneName;
	ConfigHelper* conf;
	unsigned int updateRate;

	void setObjectPriority(string name, int priority);
	int getObjectPriority(string name);	
	bool getUpdateSync()
	{
		return updateSync;
	}
	AnimationHandler aniHandler;
private:
	// Jede Szene bekommt den Scenehandler damit er es als Interface benutzen kann um die anderen Szenen anzusprechen
	SceneHandler*  sceneHandler;
	// Die Frequenz in Millisec wie oft die Szene aktualisieren soll
	unsigned int updateCount;
	// Gibt an ob die Szene in diesem Updatecall aktualisieren soll
	bool updateSync;
	// Gibt die Sichtbarkeit und Updatebarkeit der Scene an
	int visible;
	// Gibt den sichtbaren Teil der Szene an
	View view;
};

