#include "textures.h"
#include <iostream>

// ---GameTexture---
GameTexture::GameTexture(std::string texturePath)
{
	if(texture->loadFromFile(texturePath)) {
		if(config::IS_LOGGING_ENABLED)
			std::cout << "[OK] Successfully loaded an image from " << texturePath << std::endl;
	}
	else {
		if(config::IS_LOGGING_ENABLED)
			std::cout << "[ERROR] Not loaded an image from " << texturePath << std::endl;
		texture->create(64, 64);
	}
}

// ---Textures---
Textures &Textures::getInstance()
{
	static Textures instance;
	return instance;
}

Textures::Textures()
{
	// ---backgrounds---
	allTextures.push_back(GameTexture("data/textures/backgrounds/grassy_background.png"));
	
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
	allTextures.push_back(GameTexture("data/textures/scenery/cloud.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/bush1.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/bush2.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/bush3.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/bush4.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/mushrooms.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/stump.png"));
	allTextures.push_back(GameTexture("data/textures/scenery/small_tree1.png"));
}

std::shared_ptr<sf::Texture> Textures::getTexture(TexturesID textureID)
{
	return allTextures[int(textureID)].texture;
}
