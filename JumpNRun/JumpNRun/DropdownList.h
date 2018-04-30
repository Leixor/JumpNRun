#pragma once
#include "Button.h"
#include "UnorderdMap.h"

class DropdownList : public Button
{
public:
	DropdownList(ShapeBase* dropdownShape, float partSize = -1.0f);
	~DropdownList();

	void handleEvents(RenderWindow& window, Event& windowEvent);
	void draw(RenderWindow& window, RenderStates& shades);
	void addContent(string name, BaseResource* contentOne, BaseResource* contentTwo);
	void removeContent(string name);
	BaseResource* getFirstObject(string name)
	{
		//return this->listContent.getContent(name);
		return new BaseResource();
	}
	BaseResource* getSecondObject(string name)
	{
		//return this->listContent.getSpec(name);
		return new BaseResource();
	}
private:
	//UnorderdMap3V<string, ObjectBase*, ObjectBase*> listContent;
	float partSize;
	bool active;
};

