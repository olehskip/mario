#include "textures_loader.h"

// ---std::make_unique<TextureObject>---
TextureObject::TextureObject(const std::string &texturePath):
	LoaderObjectInterface(texturePath)
{
	if(!object.loadFromFile(texturePath))
		object.create(64, 64);
}

// ---Textures---
TexturesLoader::TexturesLoader()
{
	// ---backgrounds---
	allObjects.insert(std::make_pair(TexturesID::MOUNTAINS_BACKGROUND, std::make_unique<TextureObject>("data/textures/backgrounds/mountains_background.png")));
	allObjects.insert(std::make_pair(TexturesID::FOREST_BACKGROUND, std::make_unique<TextureObject>("data/textures/backgrounds/forest_background.png")));
	allObjects.insert(std::make_pair(TexturesID::FIELD_BACKGROUND, std::make_unique<TextureObject>("data/textures/backgrounds/field_background.png")));
	// ---backgrounds---
	
	// ---sprites---
	allObjects.insert(std::make_pair(TexturesID::MARIO_PLAYER_SPRITE, std::make_unique<TextureObject>("data/textures/sprites/mario_sprite.png")));
	allObjects.insert(std::make_pair(TexturesID::GOMBA_SPRITE, std::make_unique<TextureObject>("data/textures/sprites/goomba_sprite.png")));
	allObjects.insert(std::make_pair(TexturesID::COIN_SPRITE, std::make_unique<TextureObject>("data/textures/sprites/coin_sprite.png")));
	// ---sprites---

	// ---blocks---
	allObjects.insert(std::make_pair(TexturesID::SIMLE_BRICK, std::make_unique<TextureObject>("data/textures/blocks/simple_brick.png")));
	allObjects.insert(std::make_pair(TexturesID::BOTTOM_BRICK, std::make_unique<TextureObject>("data/textures/blocks/bottom_brick.png")));
	allObjects.insert(std::make_pair(TexturesID::GRASS_BRICK, std::make_unique<TextureObject>("data/textures/blocks/grass_brick.png")));
	allObjects.insert(std::make_pair(TexturesID::SOLID_BRICK, std::make_unique<TextureObject>("data/textures/blocks/solid_brick.png")));
	allObjects.insert(std::make_pair(TexturesID::SOLID_GRASS_BRICK1, std::make_unique<TextureObject>("data/textures/blocks/solid_grass_brick1.png")));
	allObjects.insert(std::make_pair(TexturesID::SOLID_GRASS_BRICK2, std::make_unique<TextureObject>("data/textures/blocks/solid_grass_brick2.png")));
	allObjects.insert(std::make_pair(TexturesID::SOLID_GRASS_BRICK3, std::make_unique<TextureObject>("data/textures/blocks/solid_grass_brick3.png")));
	allObjects.insert(std::make_pair(TexturesID::SOLID_GRASS_BRICK4, std::make_unique<TextureObject>("data/textures/blocks/solid_grass_brick4.png")));
	allObjects.insert(std::make_pair(TexturesID::SOLID_GRASS_BRICK5, std::make_unique<TextureObject>("data/textures/blocks/solid_grass_brick5.png")));
	// ---blocks---

	// ---special blocks---
	allObjects.insert(std::make_pair(TexturesID::LUCKY_BOX, std::make_unique<TextureObject>("data/textures/blocks/lucky_box.png")));
	// ---special blocks---

	// ---scenery---
	allObjects.insert(std::make_pair(TexturesID::CLOUD1, std::make_unique<TextureObject>("data/textures/scenery/cloud1.png")));
	allObjects.insert(std::make_pair(TexturesID::CLOUD2, std::make_unique<TextureObject>("data/textures/scenery/cloud2.png")));
	allObjects.insert(std::make_pair(TexturesID::CLOUD3, std::make_unique<TextureObject>("data/textures/scenery/cloud3.png")));
	allObjects.insert(std::make_pair(TexturesID::CLOUD4, std::make_unique<TextureObject>("data/textures/scenery/cloud4.png")));
	allObjects.insert(std::make_pair(TexturesID::BUSH1, std::make_unique<TextureObject>("data/textures/scenery/bush1.png")));
	allObjects.insert(std::make_pair(TexturesID::BUSH2, std::make_unique<TextureObject>("data/textures/scenery/bush2.png")));
	allObjects.insert(std::make_pair(TexturesID::BUSH3, std::make_unique<TextureObject>("data/textures/scenery/bush3.png")));
	allObjects.insert(std::make_pair(TexturesID::BUSH4, std::make_unique<TextureObject>("data/textures/scenery/bush4.png")));
	allObjects.insert(std::make_pair(TexturesID::MUSHROOMS, std::make_unique<TextureObject>("data/textures/scenery/mushrooms.png")));
	allObjects.insert(std::make_pair(TexturesID::STUMP, std::make_unique<TextureObject>("data/textures/scenery/stump.png")));
	allObjects.insert(std::make_pair(TexturesID::SMALL_TREE1, std::make_unique<TextureObject>("data/textures/scenery/small_tree1.png")));
	allObjects.insert(std::make_pair(TexturesID::PLATE, std::make_unique<TextureObject>("data/textures/scenery/plate.png")));
	// ---scenery---
}
