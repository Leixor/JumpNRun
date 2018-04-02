#pragma once
#include "standardInclude.h"

template<typename Iterator, typename Content>
struct MapContent
{
	Iterator iterator;
	Content content;

	MapContent(Iterator iterator, Content content)
		:iterator(iterator), content(content)
	{}
};

template<typename Iterator, typename Content> 
struct UnorderdMap 
{
private:
	vector<MapContent<Iterator, Content>> objects;

public:
	void push(Iterator iterator, Content content)
	{
		objects.push_back(MapContent<Iterator, Content>(iterator, content));
	}

	unsigned int size()
	{
		return objects.size();
	}

	Content get(Iterator iterator)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				return objects.at(i).content;
			}
		}
	}

	Content get(int index)
	{
		return objects.at(index).content;
	}
};
