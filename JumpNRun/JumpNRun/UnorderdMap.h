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

template<typename Iterator, typename Content, typename Spec>
struct MapContent3V
{
	Iterator iterator;
	Content content;
	Spec spec;

	MapContent3V(Iterator iterator, Content content, Spec spec)
		:iterator(iterator), content(content), spec(spec)
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

	void clear()
	{
		objects.clear();
	}

	void remove(Iterator iterator)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				this->objects.erase(this->objects.begin() + i);
			}
		}
		throw;
	}

	void remove(int index)
	{
		this->objects.erase(this->objects.begin() + i);
	}

	int getIndex(Iterator iterator)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				return i;
			}
		}

		throw;
	}

	void iterswap(int begin, int end)
	{
		iter_swap(objects.begin() + begin, objects.begin() + end);
	}

	void set(int index, Content content)
	{
		objects.at(index).content = content;
	}

	void set(Iterator iterator, Content content)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				objects.at(i).content = content;
			}
		}
		throw;
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
		throw;
	}

	Content get(int index)
	{
		return objects.at(index).content;
	}

	Iterator getIterator(int index)
	{
		return objects.at(index).iterator;
	}

	Iterator getIterator(Content content)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).content == content)
			{
				return objects.at(i).iterator;
			}
		}
		throw;
	}
};

template<typename Iterator, typename Content, typename Spec>
struct UnorderdMap3V
{
private:
	vector<MapContent3V<Iterator, Content, Spec>> objects;

public:
	void push(Iterator iterator, Content content, Spec spec)
	{
		objects.push_back(MapContent3V<Iterator, Content, Spec>(iterator, content, spec));
	}

	unsigned int size()
	{
		return objects.size();
	}

	void clear()
	{
		objects.clear();
	}

	void remove(Iterator iterator)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				this->objects.erase(this->objects.begin() + i);
			}
		}
		throw;
	}

	void remove(int index)
	{
		this->objects.erase(this->objects.begin() + i);
	}

	unsigned int getIndex(Iterator iterator)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				return i;
			}
		}

		throw;
	}

	Iterator getIterator(int index)
	{
		return objects.at(index).iterator;
	}

	void setContent(int iterator, Content content)
	{
		objects.at(iterator).content = content;
	}

	void setContent(Iterator iterator, Content content)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				objects.at(i).content = content;
			}
		}
		throw;
	}

	void setSpec(int index, Spec content)
	{
		objects.at(index).spec = spec;
	}

	void setSpec(Iterator iterator, Spec spec)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				objects.at(i).spec = spec;
			}
		}
		throw;
	}

	Content getContent(Iterator iterator)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				return objects.at(i).content;
			}
		}
		throw;
	}

	Content getContent(int index)
	{
		return objects.at(index).content;
	}

	Spec getSpec(int index)
	{
		return objects.at(index).spec;
	}

	Spec getSpec(Iterator iterator)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).iterator == iterator)
			{
				return objects.at(i).spec;
			}
		}
		throw;
	}
};