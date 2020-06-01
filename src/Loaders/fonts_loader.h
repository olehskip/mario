#pragma once
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <unordered_map>

#include "loader_interface.h"


/*
 * All fonts
 * pixeboy
 * digital7
 */

class FontObject: public LoaderObjectInterface<sf::Font>
{
public:
	FontObject(const std::string &texturePath);
};


class FontsLoader: public LoaderInterface<sf::Font>
{
public:
	FontsLoader();
};
