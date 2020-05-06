#include "blockgameobject.h"


BlockGameObject::BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, bool _isHasCollision, sf::Vector2f _jumpUpAcceleration): 
	GameObject(pos, scale, _texture), isHasCollision(_isHasCollision), jumpUpAcceleration(_jumpUpAcceleration)
{

}

void BlockGameObject::move(sf::Vector2f offset)
{
	sprite.move(sf::Vector2f(offset.x - this->offset.x, offset.y - this->offset.y));
}

void BlockGameObject::jumpUp()
{
}

void BlockGameObject::updateMovement(float time) // override
{
}
