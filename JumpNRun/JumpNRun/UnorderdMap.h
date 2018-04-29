#pragma once
#include "StandardInclude.h"

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
	vector<Content> objects;
	map<Iterator, int> iteratorIndex;
	vector<int> priorityIndex;

public:
	void push(Iterator iterator, Content content)
	{
		this->objects.push_back(content);
		this->iteratorIndex.emplace(iterator, objects.size() - 1);
		this->priorityIndex.push_back(objects.size() - 1);
	}

	unsigned int size()
	{
		return this->objects.size();
	}

	void clear()
	{
		this->objects.clear();
		this->iteratorIndex.clear();
		this->priorityIndex.clear();
	}

	void remove(Iterator iterator)
	{
		int index = this->iteratorIndex.at(iterator);
		this->objects.erase(this->objects.begin() + index);
		this->iteratorIndex.erase(iterator);

		for (unsigned int i = 0; i < this->priorityIndex.size(); i++)
		{
			if (this->priorityIndex.at(i) == index)
			{
				this->priorityIndex.erase(this->priorityIndex.begin() + i);
				break;
			}
		}
	}

	void remove(int index)
	{
		this->objects.erase(this->objects.begin() + index);

		map<Iterator, int>::iterator it;
		it = this->iteratorIndex.begin();
		for (int i = 0; i < index; i++)
			it++;
		this->iteratorIndex.erase(it->first);
		
		for (unsigned int i = 0; i < this->priorityIndex.size(); i++)
		{
			if (this->priorityIndex.at(i) == index)
			{
				this->priorityIndex.erase(this->priorityIndex.begin() + i);
				break;
			}
		}
	}

	int getIndex(Iterator iterator)
	{
		return this->iteratorIndex.at(iterator);
	}

	void set(int index, Content content)
	{
		this->objects.at(index) = content;
	}

	void set(Iterator iterator, Content content)
	{
		this->objects.at(this->iteratorIndex.at(iterator)) = content;
	}
	
	Content get(Iterator iterator)
	{
		return this->objects.at(this->iteratorIndex.at(iterator));
	}

	Content get(int index)
	{
		return this->objects.at(index);
	}

	Iterator getIterator(int index)
	{
		map<Iterator, int>::iterator it;
		it = this->iteratorIndex.begin();
		for (int i = 0; i < index; i++)
			it++;
		return it->first;
	}

	Iterator getIterator(Content content)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i) == content)
			{
				map<Iterator, int>::iterator it;
				it = this->iteratorIndex.begin();
				for (int j = 0; j < i; j++)
					it++;
				return this->iteratorIndex.at(it->first);
			}
		}
		throw;
	}

	bool itemExists(Iterator iterator)
	{
		try
		{
			this->iteratorIndex.at(iterator);
			return true;
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	int getPriority(Iterator iterator)
	{
		int index = this->iteratorIndex.at(iterator);

		for (unsigned int i = 0; i < this->priorityIndex.size(); i++)
		{
			if (this->priorityIndex.at(i) == index)
			{
				return (int)i;
			}
		}
		throw;
	}

	int getPriority(int index)
	{
		for (unsigned int i = 0; i < this->priorityIndex.size(); i++)
		{
			if (this->priorityIndex.at(i) == index)
			{
				return i;
			}
		}
		throw;
	}

	void setPriority(Iterator iterator, int priority)
	{
		int indexInVector = this->iteratorIndex.at(iterator);

		int currentPriorityIndex = 0;
		for (unsigned int i = 0; i < this->priorityIndex.size(); i++)
		{
			if (this->priorityIndex.at(i) == indexInVector)
			{
				currentPriorityIndex = i;
				break;
			}
		}

		this->priorityIndex.erase(this->priorityIndex.begin() + currentPriorityIndex);
		this->priorityIndex.insert(this->priorityIndex.begin() + priority, indexInVector);
	}

	void setPriority(int index, int priority)
	{
		int currentPriorityIndex = 0;
		for (unsigned int i = 0; i < this->priorityIndex.size(); i++)
		{
			if (this->priorityIndex.at(i) == index)
			{
				currentPriorityIndex = i;
				break;
			}
		}

		this->priorityIndex.erase(this->priorityIndex.begin() + currentPriorityIndex);
		this->priorityIndex.insert(this->priorityIndex.begin() + priority, index);
	}

	Content getContentByPriority(int priority)
	{
		return this->objects.at(this->priorityIndex.at(priority));
	}

	int getIndexByPriority(int priority)
	{
		return this->priorityIndex.at(priority);
	}
};