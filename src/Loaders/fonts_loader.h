#pragma once
#include <SFML/Graphics/Font.hpp>
#include <memory>


enum class FontsID
{
	PIXEBOY,
	DIGITAL7
};

class GameFont
{
public:
    GameFont(const std::string &texturePath);
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
};


class FontsLoader
{
public:
	static FontsLoader &getInstance();
	const std::shared_ptr<sf::Font> getFont(FontsID fontID) const;

private:
	FontsLoader();
	std::vector<GameFont> allFonts;
};
static FontsLoader &fontsLoader = FontsLoader::getInstance();