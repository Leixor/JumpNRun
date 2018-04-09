#include "standardInclude.h"

Scene::Scene(string Name, SceneHandler * sceneHandler, RenderWindow* window, View& view)
	: sceneName(Name), sceneHandler(sceneHandler), window(window),  view(view)
{
	this->updateSync = false; 
	this->updateCount = 1;
	this->updateRate = 10;
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
	window.setView(view);
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.get(i)->draw(window, shades);
	}
}

void Scene::confVarUpdate()
{
}

void Scene::setSceneScaling(Vector2f & scaling)
{
	FloatRect current = view.getViewport();
	current.width = scaling.x;
	current.height = scaling.y;
	view.setViewport(current);
}

void Scene::setSceneViewPort(FloatRect & viewPort)
{
	FloatRect current;
	current.width = viewPort.width;
	current.height = viewPort.height;
	current.top = viewPort.top;
	current.left = viewPort.left;
	view.setViewport(current);
}

void Scene::setScenePosition(Vector2f & position)
{
	FloatRect current = view.getViewport();
	current.top = position.x;
	current.left = position.y;
	view.setViewport(current);
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



