#include "DropdownList.h"

DropdownList::DropdownList(ShapeBase* dropdownShape, float partSize)
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
		//for (unsigned int i = 0; i < this->listContent.size(); i++)
		//{
		//	//this->listContent.getContent(i)->handleEvents(window, windowEvent);
		//	//this->listContent.getSpec(i)->handleEvents(window, windowEvent);
		//}
	}
}

void DropdownList::draw(RenderWindow & window, RenderStates & shades)
{
	BaseResource::draw(window, shades);
	if (this->active)
	{
		/*for (unsigned int i = 0; i < this->listContent.size(); i++)
		{
			this->listContent.getContent(i)->draw(window, shades);
			this->listContent.getSpec(i)->draw(window, shades);
		}*/
	}
}

void DropdownList::addContent(string name, BaseResource * contentOne, BaseResource * contentTwo)
{
	contentOne->objectShape->setSize(Vector2f(partSize, this->objectShape->getSize().y));
	contentTwo->objectShape->setSize(Vector2f(this->objectShape->getSize().x - partSize, this->objectShape->getSize().y));
	/*this->listContent.push(name, contentOne, contentTwo);
	for (unsigned int i = 0; i < this->listContent.size(); i++)
	{
		this->listContent.getContent(i)->objectShape->setPosition(Vector2f(this->objectShape->getPosition().x, this->objectShape->getPosition().y + (1 + i) * this->objectShape->getSize().y));
		this->listContent.getSpec(i)->objectShape->setPosition(Vector2f(this->objectShape->getPosition().x + this->partSize, this->objectShape->getPosition().y + (1 + i) * this->objectShape->getSize().y));
	}*/
}

void DropdownList::removeContent(string name)
{
	/*this->listContent.remove(name);
	for (unsigned int i = 0; i < this->listContent.size(); i++)
	{
		this->listContent.getContent(i)->objectShape->setPosition(Vector2f(this->objectShape->getPosition().x, this->objectShape->getPosition().y + (1 + i) * this->objectShape->getSize().y));
		this->listContent.getSpec(i)->objectShape->setPosition(Vector2f(this->objectShape->getPosition().x + this->partSize, this->objectShape->getPosition().y + (1 + i) * this->objectShape->getSize().y));
	}*/
}

