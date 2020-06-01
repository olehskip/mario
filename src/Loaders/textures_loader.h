#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <memory>
#include <unordered_map>

#include "loader_interface.h"

// TO DO
// WRITE ALL TEXTURES LIST

class TextureObject: public LoaderObjectInterface<sf::Texture>
{
public:
	TextureObject(const std::string &texturePath);
};

class TexturesLoader: public LoaderInterface<sf::Texture>
{
public:
	TexturesLoader();
};
