#include "fonts_loader.h"

// ---FontObject---
FontObject::FontObject(const std::string &texturePath): 
	LoaderObjectInterface(texturePath)
{
	object->loadFromFile(texturePath);
}

// ---FontsLoader---
FontsLoader::FontsLoader()
{
	allObjects.insert(std::make_pair("pixeboy", FontObject("data/fonts/pixeboy.ttf")));
	allObjects.insert(std::make_pair("digital7", FontObject("data/fonts/digital-7.ttf")));
}

