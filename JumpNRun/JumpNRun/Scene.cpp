#include "Scene.h"

Scene::Scene(SceneHandler& sceneHandler, RenderWindow* window, View& view)
	: sceneHandler(sceneHandler), window(window), view(view), sceneWorld(nullptr)
{
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
		this->objects.get(i)->handleInputs(window);
	}
}

void Scene::handleEvents(RenderWindow & window, Event& windowEvent)
{
	for (int i = this->objects.size() - 1; i >= 0; i--)
	{
		this->objects.get(i)->handleEvents(window, windowEvent);
	}
}

void Scene::update()
{
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.get(i)->update();
	}
}

void Scene::render(RenderWindow & window, RenderStates& shades, float timeTillUpdate)
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
	current.left = position.x;
	current.top = position.y;
	view.setViewport(current);
}

void Scene::updateSync()
{
	if (this->sceneWorld != nullptr)
		this->sceneWorld->update(0.01f);
	if (updateCount >= updateRate / MS_PER_UPDATE)
	{
		this->update();
		updateCount = 1;
	}
	else
	{
		updateCount++;
	}
}

SceneHandler& Scene::getSceneHandler() const
{
	return this->sceneHandler;
}

BaseResource* Scene::addObject(string name, ShapeBase * toAdd, int priority)
{
	BaseResource* tmp = new BaseResource(toAdd);

	this->objects.push(name, tmp);
	if (priority != -1)
		this->setObjectPriority(name, priority);

	return tmp;
}

void Scene::setObjectPriority(string name, int priority)
{
	this->objects.setPriority(name, priority);
}

int Scene::getObjectPriority(string name)
{
	return objects.getPriority(name);
}
