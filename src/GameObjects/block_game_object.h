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
	BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture, bool _isHasCollision, 
		BlockType blockType = BlockType::DEFAULT, unsigned int coinCount = 0);

	void jumpUp(float deltaTime);
	void updateMovement(float /* deltaTime */) override;
	const bool isHasCollision;
	const BlockType blockType;
	bool isStartedJumping() const;

	bool getCoin();

private:
	using GameObject::finalMove;
	using GameObject::animate;
	
	bool mIsStartedJumping = false;
	float globalOffsetY = 0.f;
	
	unsigned int coinCount = 0;

};
typedef std::shared_ptr<BlockGameObject> BlockObject_ptr;

