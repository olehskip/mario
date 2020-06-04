#pragma once
#include "game_object.h"

enum class BlockType
{
	DEFAULT, 
	LUCKY_BOX
};

class BlockGameObject: public GameObject
{
public:
	BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture, bool _isHasCollision, BlockType blockType = BlockType::DEFAULT);

	void jumpUp(float deltaTime);
	void updateMovement(float deltaTime) override;
	const bool isHasCollision;
	const BlockType blockType;

protected:
	bool isStartedJumping = false;
	
	float globalOffsetY = 0.f;
	const sf::Vector2f jumpUpAcceleration;
};
typedef std::shared_ptr<BlockGameObject> BlockObject_ptr;

