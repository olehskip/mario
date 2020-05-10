#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

enum class TexturesID
{
	MARIO_PLAYER,
	SIMLE_BRICK,
	BOTTOM_BRICK,
	GRASS_BRICK,
	SOLID_BRICK,
	SOLID_GRASS_BRICK1,
	SOLID_GRASS_BRICK2,
	SOLID_GRASS_BRICK3,
	SOLID_GRASS_BRICK4,
	SOLID_GRASS_BRICK5,
	ICE_BLOCK,
	LUCKY_BOX,
	CLOUD,
	BUSH1,
	BUSH2,
	BUSH3,
	BUSH4,
	MUSHROOMS,
	STUMP,
	SMALL_TREE1
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
	Textures();

	std::shared_ptr<sf::Texture> getTexture(TexturesID textureID);
private:
	std::vector<GameTexture> allTextures;

};