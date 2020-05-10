#include "textures.h"
#include <iostream>

// ---GameTexture---
GameTexture::GameTexture(std::string texturePath)
{
	if(texture->loadFromFile(texturePath))
		std::cout << "[OK] Successfully loaded an image from " << texturePath << std::endl;
	else {
		std::cout << "[ERROR] Not loaded an image from " << texturePath << std::endl;
		texture->create(64, 64);
	}
}

// ---Textures---

Textures::Textures()
{
	allTextures.push_back(GameTexture("data/textures/mario_sprite.png"));
	allTextures.push_back(GameTexture("data/textures/simple_brick.png"));
	allTextures.push_back(GameTexture("data/textures/bottom_brick.png"));
	allTextures.push_back(GameTexture("data/textures/grass_brick.png"));
	allTextures.push_back(GameTexture("data/textures/solid_brick.png"));
	allTextures.push_back(GameTexture("data/textures/solid_grass_brick1.png"));
	allTextures.push_back(GameTexture("data/textures/solid_grass_brick2.png"));
	allTextures.push_back(GameTexture("data/textures/solid_grass_brick3.png"));
	allTextures.push_back(GameTexture("data/textures/solid_grass_brick4.png"));
	allTextures.push_back(GameTexture("data/textures/solid_grass_brick5.png"));
	allTextures.push_back(GameTexture("data/textures/ice_block.png"));
	allTextures.push_back(GameTexture("data/textures/lucky_box.png"));
	allTextures.push_back(GameTexture("data/textures/cloud.png"));
	allTextures.push_back(GameTexture("data/textures/bush1.png"));
	allTextures.push_back(GameTexture("data/textures/bush2.png"));
	allTextures.push_back(GameTexture("data/textures/bush3.png"));
	allTextures.push_back(GameTexture("data/textures/bush4.png"));
	allTextures.push_back(GameTexture("data/textures/mushrooms.png"));
	allTextures.push_back(GameTexture("data/textures/stump.png"));
	allTextures.push_back(GameTexture("data/textures/small_tree1.png"));
}

std::shared_ptr<sf::Texture> Textures::getTexture(TexturesID textureID)
{
	// if(int(textureID) > allTextures.size() - 1) {
	// 	std::shared_ptr<sf::Texture> emptyTexture = std::make_shared<sf::Texture>();
	// 	emptyTexture->create(64, 64);
	// 	return emptyTexture;
	// }
	return allTextures[int(textureID)].texture;
}
