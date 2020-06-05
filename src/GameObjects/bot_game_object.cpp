#include "bot_game_object.h"

BotGameObject::BotGameObject(sf::Vector2f pos, sf::Vector2f scale, sf::Texture &texture, Direction spawnDirection): 
	GameObject(pos, scale, texture)
{
	animation = std::make_unique<AnimationController>(0, 18, 4, sf::Vector2f(60, 72), 32, true);
	direction = spawnDirection;
}

void BotGameObject::updateMovement(float deltaTime) // override
{
	const int dx = getDX(direction);
	if(isStandingOnAnyBlock) {
		offset.x += config::goomba::RUN_ACCELERATION * dx;
		if(std::abs(offset.x) > config::goomba::RUN_MAX_SPEED)
			offset.x = config::goomba::RUN_MAX_SPEED * dx;
	}
	else {
		if(offset.x > 0) {
			offset.x -= config::goomba::RUN_ACCELERATION;
			if(offset.x < 0)
				offset.x = 0;
		}
		else if(offset.x < 0) {
			offset.x += config::goomba::RUN_ACCELERATION;
			if(offset.x > 0)
				offset.x = 0;
		}
	}

	offset.y += config::GRAVITY;
	if(offset.y > config::MAX_FALLING_SPEED)
		offset.y = config::MAX_FALLING_SPEED;
}

void BotGameObject::drawWithAnimation(sf::RenderWindow &window, float deltaTime)
{
	animation->setCurrentFrame(animation->getCurrentFrame() + deltaTime * std::abs(offset.x) * 10);
	sprite.setTextureRect(animation->getSpriteRect(direction));
	draw(window);
}

void BotGameObject::changeDirection()
{
	if(direction == Direction::LEFT)
		direction = Direction::RIGHT;
	else
		direction = Direction::LEFT;
}