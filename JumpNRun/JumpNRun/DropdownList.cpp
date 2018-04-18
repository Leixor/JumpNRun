#include "DropdownList.h"

DropdownList::DropdownList(DrawableObject* dropdownShape, float partSize)
	:Button([&] { this->active = !this->active; }, dropdownShape), partSize(partSize)
{
	this->active = false;
}

DropdownList::~DropdownList()
{
}

bool DropdownList::handleEvents(RenderWindow & window, Event & windowEvent)
{
	Button::handleEvents(window, windowEvent);
	if (this->active)
	{
		for (unsigned int i = 0; i < this->listContent.size(); i++)
		{
			this->listContent.getContent(i)->handleEvents(window, windowEvent);
			this->listContent.getSpec(i)->handleEvents(window, windowEvent);
		}
	}
	return false;
}

void DropdownList::draw(RenderWindow & window, RenderStates & shades)
{
	ObjectBase::draw(window, shades);
	if (this->active)
	{
		for (unsigned int i = 0; i < this->listContent.size(); i++)
		{
			this->listContent.getContent(i)->draw(window, shades);
			this->listContent.getSpec(i)->draw(window, shades);
		}
	}
}

void DropdownList::addContent(string name, ObjectBase * contentOne, ObjectBase * contentTwo)
{
	contentOne->getObjectShape()->setSize(Vector2f(partSize, this->getObjectShape()->getSize().y));
	contentTwo->getObjectShape()->setSize(Vector2f(this->getObjectShape()->getSize().x - partSize, this->getObjectShape()->getSize().y));
	this->listContent.push(name, contentOne, contentTwo);
	for (unsigned int i = 0; i < this->listContent.size(); i++)
	{
		this->listContent.getContent(i)->getObjectShape()->setPosition(Vector2f(this->getObjectShape()->getPosition().x, this->getObjectShape()->getPosition().y + (1 + i) * this->getObjectShape()->getSize().y));
		this->listContent.getSpec(i)->getObjectShape()->setPosition(Vector2f(this->getObjectShape()->getPosition().x + this->partSize, this->getObjectShape()->getPosition().y + (1 + i) * this->getObjectShape()->getSize().y));
	}
}

void DropdownList::removeContent(string name)
{
	this->listContent.remove(name);
	for (unsigned int i = 0; i < this->listContent.size(); i++)
	{
		this->listContent.getContent(i)->getObjectShape()->setPosition(Vector2f(this->getObjectShape()->getPosition().x, this->getObjectShape()->getPosition().y + (1 + i) * this->getObjectShape()->getSize().y));
		this->listContent.getSpec(i)->getObjectShape()->setPosition(Vector2f(this->getObjectShape()->getPosition().x + this->partSize, this->getObjectShape()->getPosition().y + (1 + i) * this->getObjectShape()->getSize().y));
	}
}

