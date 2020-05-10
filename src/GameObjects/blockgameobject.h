#pragma once
#include "gameobject.h"

enum class BlockType
{
	DEFAULT, 
	ICE
};

class BlockGameObject: public GameObject
{
public:
	BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, bool _isHasCollision, BlockType blockType = BlockType::DEFAULT, sf::Vector2f _jumpUpAcceleration = sf::Vector2f(0, 0));

	void jumpUp(float deltaTime);
	void updateMovement(float deltaTime) override;
	const bool isHasCollision;
	const BlockType blockType;

protected:
	bool isJumpedUp = false;
	const sf::Vector2f jumpUpAcceleration;
};
typedef std::shared_ptr<BlockGameObject> BlockObject_ptr;

