#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

enum class TexturesID
{
	// ---backgrounds parts---
	MOUNTAINS_BACKGROUND,
	FIELD_BACKGROUND,
	FOREST_BACKGROUND,
	// ---backgrounds parts---

	// ---player sprite---
	MARIO_PLAYER,
	// ---player sprite---

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
	ICE_BLOCK,
	LUCKY_BOX,
	// ---special blocks---

	// ---scenery---
	BUSH1,
	BUSH2,
	BUSH3,
	BUSH4,
	MUSHROOMS,
	STUMP,
	SMALL_TREE1,
	// ---scenery---
};

class GameTexture
{
public:
	GameTexture(const std::string &texturePath);
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
};

class TexturesLoader
{
public:
	static TexturesLoader &getInstance();
	const std::shared_ptr<sf::Texture> getTexture(TexturesID textureID);

private:
	TexturesLoader();

	std::vector<GameTexture> allTextures;
};
static TexturesLoader &texturesLoader = TexturesLoader::getInstance();
