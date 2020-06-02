#pragma once
#include <string>
#include <memory>
#include <vector>


template<class T>
class LoaderObjectInterface
{
public:
	LoaderObjectInterface(const std::string &objectPath){};
	std::unique_ptr<T> object = std::make_unique<T>();
};

template<class T>
class LoaderInterface
{
public:
	LoaderInterface(){};
	T &getObject(const std::string &objectName)
	{
		auto findResult = allObjects.find(objectName);
		if(findResult == allObjects.end())
			return getObject(0);
		else 
			return *findResult->second.object;
	}
	
	T &getObject(size_t objectIndex)
	{
		if(objectIndex > std::distance(allObjects.begin(), allObjects.end()) - 1)
			objectIndex = 0;
		auto itt = allObjects.begin();
		std::advance(itt, objectIndex);
		return *itt->second.object;
	}

	size_t getCount() const
	{
		return std::distance(allObjects.begin(), allObjects.end());
	}

protected:
	std::unordered_map<std::string, LoaderObjectInterface<T>> allObjects;
};
