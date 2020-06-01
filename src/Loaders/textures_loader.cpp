#include "textures_loader.h"

// ---TextureObject---
TextureObject::TextureObject(const std::string &texturePath):
	LoaderObjectInterface(texturePath)
{
	if(!object->loadFromFile(texturePath))
		object->create(64, 64);
}

// ---Textures---
TexturesLoader::TexturesLoader()
{
	// ---backgrounds---
	allObjects.insert(std::make_pair("mountains_background", (TextureObject("data/textures/backgrounds/mountains_background.png"))));
	allObjects.insert(std::make_pair("forest_background", (TextureObject("data/textures/backgrounds/forest_background.png"))));
	allObjects.insert(std::make_pair("field_background", (TextureObject("data/textures/backgrounds/field_background.png"))));
	
	// ---player sprite---
	allObjects.insert(std::make_pair("mario_sprite", (TextureObject("data/textures/sprites/mario_sprite.png"))));

	// ---blocks---
	allObjects.insert(std::make_pair("simple_brick", (TextureObject("data/textures/blocks/simple_brick.png"))));
	allObjects.insert(std::make_pair("bottom_brick", (TextureObject("data/textures/blocks/bottom_brick.png"))));
	allObjects.insert(std::make_pair("grass_brick", (TextureObject("data/textures/blocks/grass_brick.png"))));
	allObjects.insert(std::make_pair("solid_brick", (TextureObject("data/textures/blocks/solid_brick.png"))));
	allObjects.insert(std::make_pair("solid_grass_brick1", (TextureObject("data/textures/blocks/solid_grass_brick1.png"))));
	allObjects.insert(std::make_pair("solid_grass_brick2", (TextureObject("data/textures/blocks/solid_grass_brick2.png"))));
	allObjects.insert(std::make_pair("solid_grass_brick3", (TextureObject("data/textures/blocks/solid_grass_brick3.png"))));
	allObjects.insert(std::make_pair("solid_grass_brick4", (TextureObject("data/textures/blocks/solid_grass_brick4.png"))));
	allObjects.insert(std::make_pair("solid_grass_brick5", (TextureObject("data/textures/blocks/solid_grass_brick5.png"))));

	// ---special blocks---
	allObjects.insert(std::make_pair("ice_block", (TextureObject("data/textures/blocks/ice_block.png"))));
	allObjects.insert(std::make_pair("lucky_box", (TextureObject("data/textures/blocks/lucky_box.png"))));

	// ---scenery---
	allObjects.insert(std::make_pair("cloud1", (TextureObject("data/textures/scenery/cloud1.png"))));
	allObjects.insert(std::make_pair("cloud2", (TextureObject("data/textures/scenery/cloud2.png"))));
	allObjects.insert(std::make_pair("cloud3", (TextureObject("data/textures/scenery/cloud3.png"))));
	allObjects.insert(std::make_pair("cloud4", (TextureObject("data/textures/scenery/cloud4.png"))));
	allObjects.insert(std::make_pair("bush1", (TextureObject("data/textures/scenery/bush1.png"))));
	allObjects.insert(std::make_pair("bush2", (TextureObject("data/textures/scenery/bush2.png"))));
	allObjects.insert(std::make_pair("bush3", (TextureObject("data/textures/scenery/bush3.png"))));
	allObjects.insert(std::make_pair("bush4", (TextureObject("data/textures/scenery/bush4.png"))));
	allObjects.insert(std::make_pair("mushrooms", (TextureObject("data/textures/scenery/mushrooms.png"))));
	allObjects.insert(std::make_pair("stump", (TextureObject("data/textures/scenery/stump.png"))));
	allObjects.insert(std::make_pair("small_tree1", (TextureObject("data/textures/scenery/small_tree1.png"))));
		allObjects.insert(std::make_pair("small_tree1", (TextureObject("data/textures/scenery/plate.png"))));
}
