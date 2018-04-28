#pragma once
#include "GlobalVariables.h"
#include "BaseResource.h"
#include "UnorderdMap.h"
#include "ConfigHelper.h"
#include "SceneHandler.h"
#include "Box2DWorld.h"

class SceneHandler;
class Scene
{
public:
	Scene(SceneHandler& sceneHandler, RenderWindow* window = nullptr, View& view = View(FloatRect(0,0, float(windowDef::get().windowSizeX), float(windowDef::get().windowSizeY))));
	~Scene();

	// Mainfunktionaltität der Gameloop -> Möglichkeit keine handleInput Methode zu definieren (z. B. statische Overlays zum Anzeigen von Stats)
	virtual bool setupResources() = 0;
	virtual void handleInputs(RenderWindow& window);
	virtual void handleEvents(RenderWindow& window, Event& windowEvent);
	virtual void update();
	virtual void render(RenderWindow& window, RenderStates& shades, float timeTillUpdate);
	virtual void confVarUpdate();

	// Scenespezifische Funktionen
	void setSceneVisibility(int visible)
	{
		this->visible = visible;
	}
	void setObjectVisibility(string objectName, int Visibility);
	void setView(View& view)
	{
		this->view = view;
	}
	void setSceneScaling(Vector2f& scaling);
	void setSceneViewPort(FloatRect& viewPort);
	void setScenePosition(Vector2f& position);
	void updateSync();

	//string getSceneName();
	SceneHandler& getSceneHandler() const;
	int getSceneVisibility()
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

		this->setObjectVisibility(name, toAdd->shapeVisible);

		return toAdd;
	}
	BaseResource* addObject(string name, DrawableObject* toAdd, int priority = -1);
protected:
	//Alle Objekte die eine Szene beinhaltet, werden hier gespeichert
	UnorderdMap<string, BaseResource*> objects;
	// Hier werden alle Objekte der Szene reingepackt, damit sie Kollision / Gravitation erfahren
	Box2DWorld* sceneWorld;
	RenderWindow* window;
	ConfigHelper* configHelper;
	unsigned int updateRate;

	void setObjectPriority(string name, int priority);
	int getObjectPriority(string name);	
private:
	// Jede Szene bekommt den Scenehandler damit er es als Interface benutzen kann um die anderen Szenen anzusprechen
	SceneHandler&  sceneHandler;
	// Gibt den sichtbaren Teil der Szene an
	View view;
	// Die Frequenz in Millisec wie oft die Szene aktualisieren soll
	unsigned int updateCount;
	// Gibt die Sichtbarkeit und Updatebarkeit der Scene an
	int visible;
};

