#include "SceneHandler.h"

SceneHandler::SceneHandler()
{
}

SceneHandler::~SceneHandler()
{
}

// Die Wichtigkeitsreihenfolge für handleInput und update sieht wie folgt aus -> von 0 nach vScenes.size()
void SceneHandler::handleEvents(RenderWindow& window, Event& windowEvent)
{
	for(unsigned int i = 0; i < vScenes.size(); i++) 
	{
		if (vScenes.get(i)->visible & INPUTABLE) 
		{
			vScenes.get(i)->handleEvents(window, windowEvent);
		}
	}
}

void SceneHandler::handleInputs(RenderWindow & window)
{
	for (unsigned int i = 0; i < vScenes.size(); i++) 
	{
		if (vScenes.get(i)->visible & INPUTABLE)
		{
			vScenes.get(i)->handleInputs(window);
		}
	}
}

void SceneHandler::update()
{
	for (unsigned int i = 0; i < vScenes.size(); i++) 
	{
		if (vScenes.get(i)->visible & UPDATABLE)
		{
			vScenes.get(i)->updateSync();
		}
	}
}

// Beim Rendern muss jedoch darauf geachtet werden das das wichtigste (also index [0]) als letztes gerendert wird damit es ganz oben sichtbar ist, deswegen eine umgekehrte for Schleife
void SceneHandler::render(RenderWindow& window, RenderStates& shades, float timeTillUpdate)
{
	for (int i = vScenes.size() - 1; i >= 0; i--) 
	{
		if (vScenes.get(i)->visible & VISIBLE)
		{
			vScenes.get(i)->render(window, shades, timeTillUpdate);
		}
	}
	window.setView(View(FloatRect(0, 0, windowDef::get().windowSizeX, windowDef::get().windowSizeY)));
}

void SceneHandler::addScene(string sceneName, Scene * createScene, eVisibilityFlags visible)
{
	if (sceneExists(sceneName))
		return;

	vScenes.push(sceneName, createScene);
	vScenes.get(sceneName)->visible = visible;
}

// Addet nur eine Szene falls sie nicht genauso mit gleichem Namen vorhanden ist
void SceneHandler::addScene(string sceneName, Scene * createScene, bool onTop, eVisibilityFlags visible)
{
	if (sceneExists(sceneName))
		return;

	this->vScenes.push(sceneName, createScene);
	this->vScenes.get(sceneName)->visible = visible;
	// Falls onTop als True mitgegeben worden ist soll die neue Szene direkt ganz oben in der Pipeline stehen
	if (onTop) 
		this->setTopScene(sceneName);
}

// Löscht die Szene 
void SceneHandler::deleteScene(string sceneName)
{
	this->vScenes.remove(sceneName);
}

// Setzt die Szene ganz nach oben in der Pipeline (also [0])
void SceneHandler::setTopScene(string sceneName)
{
	this->vScenes.setPriority(sceneName, 0);
}

void SceneHandler::setScenePriority(string name, int priority)
{
	this->vScenes.setPriority(name, priority);
}

void SceneHandler::setSceneVisibility(string name, eVisibilityFlags visible)
{
	this->vScenes.get(name)->visible = visible;
}

Scene* const SceneHandler::getSceneByName(string name)
{
	return this->vScenes.get(name);
}

// Gibt zurück ob die gesuchte Szene exestiert
bool SceneHandler::sceneExists(string sceneName)
{
	return vScenes.itemExists(sceneName);
}



