#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <memory>
#include <unordered_map>

#include "loader_interface.h"


enum class TexturesID
{
	// ---backgrounds parts---
	MOUNTAINS_BACKGROUND,
	FIELD_BACKGROUND,
	FOREST_BACKGROUND,
	// ---backgrounds parts---

	// ---sprites---
	MARIO_PLAYER_SPRITE,
	GOMBA_SPRITE,
	COIN_SPRITE,
	// ---sprites---

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
	// ---blocks---

	// ---special blocks---
	LUCKY_BOX,
	// ---special blocks---

	// ---scenery---
	CLOUD1,
	CLOUD2,
	CLOUD3,
	CLOUD4,
	BUSH1,
	BUSH2,
	BUSH3,
	BUSH4,
	MUSHROOMS,
	STUMP,
	SMALL_TREE1,
	PLATE,
	// ---scenery---
};

class TextureObject: public LoaderObjectInterface<sf::Texture>
{
public:
	TextureObject(const std::string &texturePath);
};

class TexturesLoader: public LoaderInterface<sf::Texture, TexturesID>
{
public:
	TexturesLoader();
};
