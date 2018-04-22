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
	for(unsigned int i = 0; i < vScenes.size(); i++) {
		if (vScenes.get(i)->getVisibility() & INPUTABLE) {
			vScenes.get(i)->handleEvents(window, windowEvent);
		}
	}
}

void SceneHandler::handleInputs(RenderWindow & window)
{
	for (unsigned int i = 0; i < vScenes.size(); i++) {
		if (vScenes.get(i)->getVisibility() & INPUTABLE) {
			vScenes.get(i)->handleInputs(window);
		}
	}
}

void SceneHandler::update()
{
	for (unsigned int i = 0; i < vScenes.size(); i++) 
	{
		if (vScenes.get(i)->getVisibility() & UPDATABLE)
		{
			vScenes.get(i)->update();
		}
	}
}

// Beim Rendern muss jedoch darauf geachtet werden das das wichtigste (also index [0]) als letztes gerendert wird damit es ganz oben sichtbar ist, deswegen eine umgekehrte for Schleife
void SceneHandler::render(RenderWindow& window, RenderStates& shades, float timeTillUpdate)
{
	for (int i = vScenes.size() - 1; i >= 0; i--) 
	{
		if (vScenes.get(i)->getVisibility() & VISIBLE)
		{
			vScenes.get(i)->render(window, shades, timeTillUpdate);
		}
	}
	window.setView(View(FloatRect(0, 0, windowDef::get().windowSizeX, windowDef::get().windowSizeY)));
}

void SceneHandler::addScene(string sceneName, Scene * createScene, int visible)
{
	if (!sceneExists(sceneName)) 
	{
		vScenes.push(sceneName, createScene);
		vScenes.get(sceneName)->setVisibility(visible);
	}
}

// Addet nur eine Szene falls sie nicht genauso mit gleichem Namen vorhanden ist
void SceneHandler::addScene(string sceneName, Scene * createScene, bool onTop, int visible)
{
	if (!sceneExists(sceneName))
	{
		vScenes.push(sceneName, createScene);
		vScenes.get(sceneName)->setVisibility(visible);
		// Falls onTop als True mitgegeben worden ist soll die neue Szene direkt ganz oben in der Pipeline stehen
		if (onTop) 
			setTopScene(sceneName);
	}
}

// Löscht die Szene falls sie vorhanden ist
void SceneHandler::deleteScene(string sceneName)
{
	this->vScenes.remove(sceneName);
}

// Setzt die Szene ganz nach oben in der Pipeline (also [0])
void SceneHandler::setTopScene(string sceneName)
{
	if (sceneExists(sceneName)) {
		if (vScenes.get(0) != vScenes.get(sceneName))
		{
			int index = this->vScenes.getIndex(sceneName);
			for (unsigned int i = 0; i < vScenes.size() - index; i++) 
			{
				this->vScenes.iterswap(i, this->vScenes.size() - index);
			}
		}
		
	}
	
}

// Jede Scene kann die visibility anderer Scenes setzen
void SceneHandler::setSceneVisibility(string sceneName, int visibility)
{
	this->vScenes.get(sceneName)->setVisibility(visibility);
}

void SceneHandler::setScenePriority(string name, int priority)
{
	if (priority >= int(this->vScenes.size() - 1))
		throw;

	int index = this->vScenes.getIndex(name);
	if (index > priority)
		for (int i = priority; i < index; i++)
			this->vScenes.iterswap(i, index);
	else if (index < priority)
		for (int i = priority; i > index; i--)
			this->vScenes.iterswap(i, index);
}

Scene* const SceneHandler::getSceneByName(string name)
{
	return this->vScenes.get(name);
}

// Gibt zurück ob die gesuchte Szene exestiert
bool SceneHandler::sceneExists(string sceneName)
{
	for (unsigned int i = 0; i < this->vScenes.size(); i++) 
	{
		if (vScenes.getIterator(i) == sceneName) 
		{
			return true;
		}
	}
	return false;
}



