#include "DropdownList.h"

DropdownList::DropdownList(DrawableObject* dropdownShape, float partSize)
	:Button([&] { this->active = !this->active; }, dropdownShape), partSize(partSize)
{
	this->active = false;
}

DropdownList::~DropdownList()
{
}

void DropdownList::handleEvents(RenderWindow & window, Event & windowEvent)
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
	contentOne->getShape()->setSize(Vector2f(partSize, this->getShape()->getSize().y));
	contentTwo->getShape()->setSize(Vector2f(this->getShape()->getSize().x - partSize, this->getShape()->getSize().y));
	this->listContent.push(name, contentOne, contentTwo);
	for (unsigned int i = 0; i < this->listContent.size(); i++)
	{
		this->listContent.getContent(i)->getShape()->setPosition(Vector2f(this->getShape()->getPosition().x, this->getShape()->getPosition().y + (1 + i) * this->getShape()->getSize().y));
		this->listContent.getSpec(i)->getShape()->setPosition(Vector2f(this->getShape()->getPosition().x + this->partSize, this->getShape()->getPosition().y + (1 + i) * this->getShape()->getSize().y));
	}
}

void DropdownList::removeContent(string name)
{
	this->listContent.remove(name);
	for (unsigned int i = 0; i < this->listContent.size(); i++)
	{
		this->listContent.getContent(i)->getShape()->setPosition(Vector2f(this->getShape()->getPosition().x, this->getShape()->getPosition().y + (1 + i) * this->getShape()->getSize().y));
		this->listContent.getSpec(i)->getShape()->setPosition(Vector2f(this->getShape()->getPosition().x + this->partSize, this->getShape()->getPosition().y + (1 + i) * this->getShape()->getSize().y));
	}
}

