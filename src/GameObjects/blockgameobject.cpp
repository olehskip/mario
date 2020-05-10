#include "blockgameobject.h"


BlockGameObject::BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, bool _isHasCollision, BlockType blockType, sf::Vector2f _jumpUpAcceleration): 
	GameObject(pos, scale, _texture), isHasCollision(_isHasCollision), jumpUpAcceleration(_jumpUpAcceleration), blockType(blockType)
{
}

void BlockGameObject::jumpUp(float deltaTime)
{
	// if(jumpUpAcceleration.x == 0 && jumpUpAcceleration.y == 0) return;
	// if(!isJumpedUp)
	// 	offset.y -= 9;
	// isJumpedUp = true;
}

void BlockGameObject::updateMovement(float deltaTime) // override
{
	// sprite.move(offset);

	// if(isJumpedUp && offset.y < 9) {
	// 	offset.y += 1;
	// }
	// else if(offset.y >= 9) {
	// 	offset.y = 0.f;
	// 	isJumpedUp = false;
	// }
}
