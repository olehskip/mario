#include "textures_loader.h"

// ---GameTexture---
GameTexture::GameTexture(const std::string &texturePath)
{
	if(!texture->loadFromFile(texturePath))
		texture->create(64, 64);
}

// ---Textures---
TexturesLoader &TexturesLoader::getInstance()
{
	static TexturesLoader instance;
	return instance;
}

TexturesLoader::TexturesLoader()
{
	// ---backgrounds---
	allTextures.push_back(GameTexture("data/textures/backgrounds/mountains_background.png"));
	allTextures.push_back(GameTexture("data/textures/backgrounds/field_background.png"));
	allTextures.push_back(GameTexture("data/textures/backgrounds/forest_background.png"));
	
	// ---player sprite---
	allTextures.push_back(GameTexture("data/textures/sprites/mario_sprite.png"));

	// ---blocks---
	allTextures.push_back(GameTexture("data/textures/blocks/simple_brick.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/bottom_brick.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/grass_brick.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/solid_brick.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/solid_grass_brick1.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/solid_grass_brick2.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/solid_grass_brick3.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/solid_grass_brick4.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/solid_grass_brick5.png"));

	// ---special blocks---
	allTextures.push_back(GameTexture("data/textures/blocks/ice_block.png"));
	allTextures.push_back(GameTexture("data/textures/blocks/lucky_box.png"));

	// ---scenery---
	allTextures.push_back(GameTexture("data/textures/scenery/bush1.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/bush2.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/bush3.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/bush4.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/mushrooms.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/stump.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/small_tree1.png"));
}

const std::shared_ptr<sf::Texture> TexturesLoader::getTexture(TexturesID textureID)
{
	return allTextures[static_cast<int>(textureID)].texture;
}
