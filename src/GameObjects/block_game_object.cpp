#include "block_game_object.h"
#include "../config.h"

BlockGameObject::BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture, bool _isHasCollision, BlockType blockType): 
	GameObject(pos, scale, _texture), isHasCollision(_isHasCollision), blockType(blockType)
{
}

void BlockGameObject::jumpUp(float deltaTime)
{
	// if(!isStartedJumping)
	// 	offset.y = -6;

	// isStartedJumping = true;
}

void BlockGameObject::updateMovement(float deltaTime) // override
{
	// if(blockType == BlockType::LUCKY_BOX && isStartedJumping) {
	// 	globalOffsetY += offset.y;
	// 	sprite.move(offset);

	// 	// if the block reached the critical point, then we need to return him back
	// 	if(offset.y <= 0.f && globalOffsetY < -(getGlobalBounds().height * config::WINDOW_ZOOM / 2))
	// 		offset.y = 6;

	// 	// if the block returned back, then to stop him
	// 	if(offset.y > 0.f && globalOffsetY == 0) {
	// 		offset.y = 0;
	// 		isStartedJumping = false;
	// 	}
	// 	else if(offset.y > 0.f && globalOffsetY > 0)
	// 		offset.y = -globalOffsetY;
	// }
}
