#include "block_game_object.h"
#include "../config.h"

BlockGameObject::BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture, bool _isHasCollision, 
	BlockType blockType, unsigned int coinCount): 
	GameObject(pos, scale, _texture), isHasCollision(_isHasCollision), blockType(blockType)
{
	this->coinCount = coinCount;
}

void BlockGameObject::jumpUp(float deltaTime)
{
	if(!mIsStartedJumping)
		offset.y = int(-config::block::JUMP_SPEED * deltaTime * 60);

	mIsStartedJumping = true;
}

void BlockGameObject::updateMovement(float /* deltaTime */) // override
{
	if(blockType == BlockType::LUCKY_BOX && mIsStartedJumping) {
		globalOffsetY += offset.y;
		sprite.move(offset);

		// if the block reached the critical point, then we need to return it back
		if(offset.y <= 0.f && globalOffsetY < -getGlobalBounds().height)
			offset.y = int(config::block::JUMP_SPEED);

		// if the block returned back
		if(globalOffsetY == 0.f) {
			offset.y = 0;
			mIsStartedJumping = false;
		}
		if(offset.y > 0.f && globalOffsetY > 0)
			offset.y = -globalOffsetY;
	}
}

bool BlockGameObject::isStartedJumping() const
{
	return mIsStartedJumping;
}

bool BlockGameObject::getCoin()
{
	if(coinCount > 0) {
		coinCount--;
		return true;
	}
	else
		return false;
}
