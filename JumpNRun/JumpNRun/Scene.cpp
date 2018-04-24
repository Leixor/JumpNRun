#include "Scene.h"

Scene::Scene(SceneHandler& sceneHandler, RenderWindow* window, View& view)
	: sceneHandler(sceneHandler), window(window), view(view)
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
	for (int i = this->eventArray.size() - 1; i >= 0; i--)
	{
		this->eventArray.get(i)->handleInputs(window);
	}
}

void Scene::handleEvents(RenderWindow & window, Event& windowEvent)
{
	for (int i = this->eventArray.size() - 1; i >= 0; i--)
	{
		this->eventArray.get(i)->handleEvents(window, windowEvent);
	}
}

void Scene::update()
{
	if (updateCount >= updateRate / MS_PER_UPDATE)
	{
		for (unsigned int i = 0; i < this->updateArray.size(); i++)
		{
			updateArray.get(i)->update();
		}
		updateCount = 1;
		updateSync = true;
	}
	else
	{
		updateCount++;
		updateSync = false;
	}
	/*aniHandler.update();*/
}

void Scene::render(RenderWindow & window, RenderStates& shades, float timeTillUpdate)
{
	window.setView(view);
	for (unsigned int i = 0; i < this->drawArray.size(); i++)
	{
		drawArray.get(i)->draw(window, shades);
	}
}

void Scene::confVarUpdate()
{
}

void Scene::setObjectVisibility(string objectName, int Visibility)
{
	ObjectBase* object = this->objects.get(objectName);

	if ((Visibility & UPDATABLE) == UPDATABLE && !this->updateArray.itemExists(objectName))
		this->updateArray.push(objectName, object);
	else if ((Visibility & UPDATABLE) != UPDATABLE && this->updateArray.itemExists(objectName))
		this->updateArray.remove(objectName);

	if ((Visibility & VISIBLE) == VISIBLE && !this->drawArray.itemExists(objectName))
		this->drawArray.push(objectName, object);
	else if ((Visibility & VISIBLE) != VISIBLE && this->drawArray.itemExists(objectName))
		this->drawArray.remove(objectName);

	if ((Visibility & INPUTABLE) == INPUTABLE && !this->eventArray.itemExists(objectName))
		this->eventArray.push(objectName, object);
	else if ((Visibility & INPUTABLE) != INPUTABLE && this->eventArray.itemExists(objectName))
		this->eventArray.remove(objectName);
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

SceneHandler& Scene::getSceneHandler() const
{
	return this->sceneHandler;
}

ObjectBase* Scene::addObject(string name, DrawableObject * toAdd, int priority)
{
	ObjectBase* tmp = new ObjectBase(toAdd);

	this->objects.push(name, tmp);
	if (priority != -1)
		this->setObjectPriority(name, priority);

	this->setObjectVisibility(name, tmp->shapeVisible);

	return tmp;
}

void Scene::setObjectPriority(string name, int priority)
{
	if (priority >= int(this->objects.size() - 1))
		throw;
	
	int index = this->getObjectPriority(name);
	if(index > priority)
		for (int i = priority; i < index; i++)
		{
			this->objects.iterswap(i, index);
		}
	else if(index < priority)
		for (int i = priority; i > index; i--)
		{
			this->objects.iterswap(i, index);
		}
}

int Scene::getObjectPriority(string name)
{
	return objects.getIndex(name);
}
