#include "standardInclude.h"

Scene::Scene(string Name, SceneHandler * sceneHandler, RenderWindow* window, int visible)
	: sceneName(Name), sceneHandler(sceneHandler), window(window), visible(visible)
{
	updateSync = false; 
	updateCount = 1;
	updateRate = 10;
}

Scene::~Scene()
{
}

void Scene::handleInputs(RenderWindow & window)
{
	for (int i = this->objects.size() - 1; i >= 0; i--)
	{
		objects.get(i)->handleInputs(window);
	}
}

void Scene::handleEvents(RenderWindow & window, Event windowEvent)
{
	for (int i = this->objects.size() - 1; i >= 0; i--)
	{
		if(objects.get(i)->handleEvents(window, windowEvent))
				break;
	}
}

void Scene::update()
{
	if (updateCount >= updateRate / MS_PER_UPDATE)
	{
		for (unsigned int i = 0; i < this->objects.size(); i++)
		{
			objects.get(i)->update();
		}
		updateCount = 1;
		updateSync = true;
	}
	else
	{
		updateCount++;
		updateSync = false;
	}
}

void Scene::render(RenderWindow & window, RenderStates shades, float timeTillUpdate)
{
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.get(i)->draw(window, shades);
	}
}
string Scene::getSceneName()
{
	return this->sceneName;
}

SceneHandler * Scene::getSceneHandler() const
{
	return this->sceneHandler;
}

ObjectBase* Scene::addObject(string name, DrawableObject * toAdd)
{
	ObjectBase* tmp = new ObjectBase(toAdd);
	objects.push(name, tmp);
	return tmp;
}



