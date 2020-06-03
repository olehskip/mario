#include "fonts_loader.h"

// ---FontObject---
FontObject::FontObject(const std::string &texturePath): 
	LoaderObjectInterface(texturePath)
{
	object.loadFromFile(texturePath);
}

// ---FontsLoader---
FontsLoader::FontsLoader()
{
	allObjects.insert(std::make_pair(FontsID::PIXEBOY, std::make_unique<FontObject>("data/fonts/pixeboy.ttf")));
	allObjects.insert(std::make_pair(FontsID::DIGITAL7, std::make_unique<FontObject>("data/fonts/digital-7.ttf")));
}

