#include "coin_game_object.h"

CoinGameObject::CoinGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture, CoinState _coinState):
	GameObject(pos, scale, _texture), coinState(_coinState)
{
	animation = std::make_unique<AnimationController>(0, 16, 20.f, sf::Vector2f(34, 38), 32, true);
	sprite.setTextureRect(animation->getSpriteRect(Direction::RIGHT));
	sprite.move(-sprite.getGlobalBounds().width / 2.f, 0);
}

void CoinGameObject::updateMovement(float deltaTime) // override
{
	if(coinState == CoinState::STAND) return;
	if(isJumping && globalOffset.y < -config::coin::JUMP_DISTANCE)
		isJumping = false;
	if(!isJumping) {
		offset.y += config::GRAVITY * deltaTime * 60;
		if(offset.y > config::MAX_FALLING_SPEED)
			offset.y = config::MAX_FALLING_SPEED;
	}
	globalOffset += offset;
}

void CoinGameObject::jumpUp(float deltaTime)
{
	if(!isJumping) {
		globalOffset = sf::Vector2f(0, 0);
		offset.y = int(-config::coin::JUMP_ANIMATION_SPEED * deltaTime * 60);
	}
	isJumping = true;
}

void CoinGameObject::animate(float deltaTime) // override
{
	animation->setCurrentFrame(animation->getCurrentFrame() + deltaTime * animation->animationSpeed);
	sprite.setTextureRect(animation->getSpriteRect(Direction::RIGHT));
}

bool CoinGameObject::isAlreadyEarned() const
{
	return mIsAreladyEarned;
}

void CoinGameObject::earn()
{
	mIsAreladyEarned = true;
}
