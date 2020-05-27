#include "fonts_loader.h"

// ---GameFont---
GameFont::GameFont(const std::string &texturePath)
{
	font->loadFromFile(texturePath);
}

// ---FontsLoader---
FontsLoader::FontsLoader()
{
	allFonts.push_back(GameFont("data/fonts/pixeboy.ttf"));
	allFonts.push_back(GameFont("data/fonts/digital-7.ttf"));
}

FontsLoader &FontsLoader::getInstance()
{
	static FontsLoader instance;
	return instance;
}

const std::shared_ptr<sf::Font> FontsLoader::getFont(FontsID fontID) const
{
	return allFonts[static_cast<int>(fontID)].font;
}
