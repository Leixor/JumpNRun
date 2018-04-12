#pragma once
class DropdownList : public Button
{
public:
	DropdownList(DrawableObject* dropdownShape, float partSize = -1.0f);
	~DropdownList();

	bool handleEvents(RenderWindow& window, Event& windowEvent);
	void draw(RenderWindow& window, RenderStates& shades);
	void addContent(string name, ObjectBase* contentOne, ObjectBase* contentTwo);
	void removeContent(string name);
	ObjectBase* getFirstObject(string name)
	{
		return this->listContent.getContent(name);
	}
	ObjectBase* getSecondObject(string name)
	{
		return this->listContent.getSpec(name);
	}
private:
	UnorderdMap3V<string, ObjectBase*, ObjectBase*> listContent;
	float partSize;
	bool active;
};

