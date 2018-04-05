#include "standardInclude.h"

SceneHandler::SceneHandler()
{
}

SceneHandler::~SceneHandler()
{
}

// Die Wichtigkeitsreihenfolge für handleInput und update sieht wie folgt aus -> von 0 nach vScenes.size()
void SceneHandler::handleEvents(RenderWindow& window, Event windowEvent)
{
	for(unsigned int i = 0; i < vScenes.size(); i++) {
		if (vScenes[i]->visible & INPUTABLE) {
			vScenes[i]->handleEvents(window, windowEvent);
		}
	}
}

void SceneHandler::handleInputs(RenderWindow & window)
{
	for (unsigned int i = 0; i < vScenes.size(); i++) {
		if (vScenes[i]->visible & INPUTABLE) {
			vScenes[i]->handleInputs(window);
		}
	}
}

void SceneHandler::update()
{
	for (unsigned int i = 0; i < vScenes.size(); i++) {
		if (vScenes[i]->visible & UPDATABLE) {
			vScenes[i]->update();
		}
	}
}

// Beim Rendern muss jedoch darauf geachtet werden das das wichtigste (also index [0]) als letztes gerendert wird damit es ganz oben sichtbar ist, deswegen eine umgekehrte for Schleife
void SceneHandler::render(RenderWindow& window, RenderStates shades)
{
	for (int i = vScenes.size() - 1; i >= 0; i--) {
		if (vScenes[i]->visible & VISIBLE) {
			vScenes[i]->render(window, shades);
		}
	}
}

void SceneHandler::addScene(Scene * createScene, int visible)
{
	if (!sceneExists(createScene->getSceneName())) {
		vScenes.push_back(createScene);
		vScenes.back()->visible = visible;
	}
}

// Addet nur eine Szene falls sie nicht genauso mit gleichem Namen vorhanden ist
void SceneHandler::addScene(Scene * createScene, bool onTop, int visible)
{
	if (!sceneExists(createScene->getSceneName())) {
		vScenes.push_back(createScene);
		vScenes.back()->visible = visible;
		// Falls onTop als True mitgegeben worden ist soll die neue Szene direkt ganz oben in der Pipeline stehen
		if (onTop) {
			string name = vScenes.back()->getSceneName();
			setTopScene(name);
		}
	}
}

// Löscht die Szene falls sie vorhanden ist
void SceneHandler::deleteScene(string sceneName)
{
	if (sceneExists(sceneName)) {
		int index = getSceneIndexByName(sceneName);
		vScenes.erase(vScenes.begin() + index);
	}
}

// Setzt die Szene ganz nach oben in der Pipeline (also [0])
void SceneHandler::setTopScene(string sceneName)
{
	if (sceneExists(sceneName)) {
		if (vScenes[0] != vScenes[getSceneIndexByName(sceneName)]) {
			int index = getSceneIndexByName(sceneName);
			for (unsigned int i = 0; i < vScenes.size() - index; i++) {
				iter_swap(vScenes.begin() + i, vScenes.end() - index);
			}
		}
		
	}
	
}

// Jede Scene kann die visibility anderer Scenes setzen
void SceneHandler::setSceneVisibility(string sceneName, int visibility)
{
	int index = getSceneIndexByName(sceneName);

	vScenes[index]->visible = visibility;
}

// Returnt den Index der jeweiligen Szene nach Namen, vorher sollte überprüft werden ob die Scene überhaupt exestiert von dem man den Index haben will mithilfe der unteren Funktion
int SceneHandler::getSceneIndexByName(string sceneName)
{
	int counter = 0;
	for (auto& scene : vScenes) {
		if (scene->getSceneName() == sceneName) {
			break;
		}
		counter++;
	}
	return counter;
}

// Gibt zurück ob die gesuchte Szene exestiert
bool SceneHandler::sceneExists(string sceneName)
{
	for (auto& scene : vScenes) {
		if (scene->getSceneName() == sceneName) {
			return true;
		}
	}
	return false;
}

// Vielleicht Redudant
Scene * SceneHandler::getSceneByName(string sceneName)
{
	for (auto& scene : vScenes) {
		if (scene->getSceneName() == sceneName) {
			return scene;
			break;
		}
	}

	return nullptr;
}



