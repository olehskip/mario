#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

#include "config.h"

enum class TexturesID
{
	// ---backgrounds---
	GRASSY_BACKGROUND,

	// ---player sprite---
	MARIO_PLAYER,

	// ---blocks---
	SIMLE_BRICK,
	BOTTOM_BRICK,
	GRASS_BRICK,
	SOLID_BRICK,
	SOLID_GRASS_BRICK1,
	SOLID_GRASS_BRICK2,
	SOLID_GRASS_BRICK3,
	SOLID_GRASS_BRICK4,
	SOLID_GRASS_BRICK5,

	// ---special blocks---
	ICE_BLOCK,
	LUCKY_BOX,

	// ---scenery---
	CLOUD,
	BUSH1,
	BUSH2,
	BUSH3,
	BUSH4,
	MUSHROOMS,
	STUMP,
	SMALL_TREE1,
};

class GameTexture
{
public:
	GameTexture(std::string texturePath);
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
};

class Textures
{
public:
	static Textures &getInstance();
	std::shared_ptr<sf::Texture> getTexture(TexturesID textureID);

private:
	Textures();

	std::vector<GameTexture> allTextures;
};
static Textures &textures = Textures::getInstance();
