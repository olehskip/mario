#pragma once
#include "gameobject.h"

class BlockGameObject: public GameObject
{
public:
	BlockGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, bool _isHasCollision, sf::Vector2f _jumpUpAcceleration = sf::Vector2f(0, 0));
	void move(sf::Vector2f offset);
	void jumpUp();
	void updateMovement(float time) override;
	const bool isHasCollision;
	bool isAllowedToJump = true;

protected:
	const sf::Vector2f jumpUpAcceleration;
};
typedef std::shared_ptr<BlockGameObject> BlockObject_ptr;
