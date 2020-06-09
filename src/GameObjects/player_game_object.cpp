#include "player_game_object.h"

PlayerGameObject::PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture): 
	GameObject(pos, scale, _texture)
{
	runAnimation = std::make_shared<AnimationController>(0, config::player::RUN_ANIMATION_FRAMES_COUNT, 
		config::player::RUN_ANIMATION_SPEED, config::player::frameSize, config::ANIMATION_SPACE_SIZE);
	jumpAnimation = std::make_shared<AnimationController>(1, config::player::JUMP_ANIMATION_FRAMES_COUNT, 
		config::player::JUMP_ANIMATION_SPEED, config::player::frameSize, config::ANIMATION_SPACE_SIZE);
	dieAnimation = std::make_shared<AnimationController>(2, 1, 0.f, config::player::frameSize, config::ANIMATION_SPACE_SIZE);
	
	currentAnimation = runAnimation;

	sprite.setTextureRect(currentAnimation->getSpriteRect(direction));
}

void PlayerGameObject::move(Direction directionToMove, float deltaTime)
{	
	const int dx = getDX(directionToMove);
	float acceleration = config::player::RUN_ACCELERATION;
	if(!isStandingOnAnyBlock)
		acceleration /= 1.5f;

	isStaying = false;
	if(isStandingOnAnyBlock) {
		if(offset.x == 0)
			currentAnimation->setCurrentFrame(1.f);
		if(currentAnimation != runAnimation) {
			runAnimation = std::make_unique<AnimationController>(runAnimation->newObject());
			currentAnimation = runAnimation;
		}
		direction = directionToMove;
	}

	offset.x += acceleration * deltaTime * 60 * dx;

	if(std::abs(offset.x) > config::player::RUN_MAX_SPEED)
		offset.x = config::player::RUN_MAX_SPEED * dx;

	if(!isStandingOnAnyBlock && ((direction == Direction::LEFT && offset.x > 0) || (direction == Direction::RIGHT && offset.x < 0)))
		offset.x = 0.f;
}

void PlayerGameObject::move(sf::Vector2f offset)
{
	sprite.move(offset);
}

bool PlayerGameObject::jump(float deltaTime)
{
	if(!isAlowedToJump)
		return false;

	const bool output = (offset.y == 0);
	isJumpingNow = true;
	
	offset.y -= config::player::JUMPING_ACCELERATION * deltaTime * 60;

	if(abs(offset.y) > config::player::JUMPING_MAX_SPEED) {
		isAlowedToJump = false;
		offset.y = -config::player::JUMPING_MAX_SPEED;
	}
	if(currentAnimation != jumpAnimation) {
		jumpAnimation = std::make_unique<AnimationController>(jumpAnimation->newObject());
		currentAnimation = jumpAnimation;
	}

	return output;
}

void PlayerGameObject::stay(float deltaTime)
{
	if(!mIsAlive) return;
	isStaying = true;
	if(!isStandingOnAnyBlock) return;
	if(currentAnimation != runAnimation) {
		runAnimation = std::make_unique<AnimationController>(runAnimation->newObject());
		currentAnimation = runAnimation;
	}

	if(offset.x == 0.f || currentAnimation->getCurrentFrame() == 0.f || 
	   int(currentAnimation->getCurrentFrame()) >= currentAnimation->framesCount - 1 || isStacked) {
		currentAnimation->setCurrentFrame(0.f);
		return;
	}
	if(int(currentAnimation->getCurrentFrame()) < config::player::STOP_RUN_FRAME && int(currentAnimation->getCurrentFrame()) > 0)
		currentAnimation->setCurrentFrame(config::player::STOP_RUN_FRAME);
	currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.x) * currentAnimation->animationSpeed);
}

void PlayerGameObject::updateMovement(float deltaTime) // override
{
	if(mIsAlive) {
		// x
		auto deceleration = config::player::RUN_DECELERATION;
		if(offset.y != 0)
			deceleration /= 4;

		if(isStaying) {
			if(offset.x > 0) {
				offset.x -= deceleration * deltaTime * 60;

				if(offset.x < 0)
					offset.x = 0;
			}
			else if(offset.x < 0) {
				offset.x += deceleration * deltaTime * 60;

				if(offset.x > 0)
					offset.x = 0;
			}
		}
	}
	else 
		offset.x = 0;

	// y
	offset.y += config::GRAVITY;
	if(offset.y > config::MAX_FALLING_SPEED)
		offset.y = config::MAX_FALLING_SPEED;
	else if(abs(offset.y) > config::MAX_FALLING_SPEED)
		offset.y = -config::MAX_FALLING_SPEED;

	if(!isStandingOnAnyBlock && (!isAlowedToJump && offset.y > 0 || isAlowedToJump && !isJumpingNow)) {
		isAlowedToJump = false;
	}
	else if(isStandingOnAnyBlock)
		isAlowedToJump = true;
 }

void PlayerGameObject::drawWithAnimation(sf::RenderWindow &window, float deltaTime)
{
	if(currentAnimation == dieAnimation)
		currentAnimation->setCurrentFrame(0.f);

	// if the player is on the ground and is RUN
	else if(isStandingOnAnyBlock && currentAnimation == runAnimation) {
		if(!isStaying) {
			if(isStacked)
				currentAnimation->setCurrentFrame(0.f);
			else 
				currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.x) * 
					currentAnimation->animationSpeed);
				
			if(currentAnimation->getCurrentFrame() >= config::player::STOP_RUN_FRAME)
				currentAnimation->setCurrentFrame(config::player::START_RUN_FRAME);
		}
	}
	// if the player is falling, but did not jump
	else if(offset.y > 0.f && isAlowedToJump) {
		currentAnimation = jumpAnimation;
		currentAnimation->setCurrentFrame(config::player::JUMPING_FRAME);
	}
	// if the player is jumping
	else if(currentAnimation == jumpAnimation) {
		// if the player is falling
		if(offset.y > 0) {
			currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.y) * 
				currentAnimation->animationSpeed);
			if(int(currentAnimation->getCurrentFrame()) > currentAnimation->framesCount - 1)
				currentAnimation->setCurrentFrame(currentAnimation->framesCount - 1);
		}
		else {
			if(int(currentAnimation->getCurrentFrame()) < int(config::player::JUMPING_FRAME)) {
				currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.y) * 
					currentAnimation->animationSpeed);
				if(int(currentAnimation->getCurrentFrame()) > config::player::JUMPING_FRAME)
					currentAnimation->setCurrentFrame(config::player::JUMPING_FRAME);
			}
		}
	}

	sprite.setTextureRect(currentAnimation->getSpriteRect(direction));
	draw(window);
}

void PlayerGameObject::die()
{
	mIsAlive = false;
	isAlowedToJump = true;
	offset = sf::Vector2f(0.f, 0.f);
	jump(1.f);
	currentAnimation = dieAnimation;
}

bool PlayerGameObject::isAlive() const
{
	return mIsAlive;
}
