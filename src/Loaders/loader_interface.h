#pragma once
#include <string>
#include <memory>
#include <vector>


template<class T>
class LoaderObjectInterface
{
public:
	LoaderObjectInterface(const std::string & /* objectPath */){};
	T object;
};

template<class T, class E>
class LoaderInterface
{
public:
	LoaderInterface(){};
	T &getObject(E findEnum)
	{
		auto findResult = allObjects.find(findEnum);
		if(findResult == allObjects.end())
			return getObject(0);
		else 
			return findResult->second->object;
	}
	
	T &getObject(size_t objectIndex)
	{
		if(int(objectIndex) > int(std::distance(allObjects.begin(), allObjects.end()) - 1))
			objectIndex = 0;
		auto itt = allObjects.begin();
		std::advance(itt, objectIndex);
		return itt->second->object;
	}

	size_t getCount() const
	{
		return std::distance(allObjects.begin(), allObjects.end());
	}

protected:
	std::unordered_map<E, std::unique_ptr<LoaderObjectInterface<T>>> allObjects;
};
