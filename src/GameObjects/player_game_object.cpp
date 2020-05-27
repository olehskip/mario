#include "player_game_object.h"


PlayerGameObject::PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture): 
	GameObject(pos, scale, _texture)
{
	runAnimation = std::make_shared<AnimationController>(0, config::RUN_ANIMATION_FRAMES_COUNT, config::RUN_ANIMATION_SPEED);
	jumpAnimation = std::make_shared<AnimationController>(1, config::JUMP_ANIMATION_FRAMES_COUNT, config::JUMP_ANIMATION_SPEED);
	currentAnimation = runAnimation;

	sprite.setTextureRect(sf::IntRect((64 + 32) * int(currentAnimation->getCurrentFrame()) + 64, 0, -64, 117));
	sprite.setScale(scale);
}

void PlayerGameObject::move(Direction directionToMove, float deltaTime)
{
	const int dx = [](Direction dir)
	{
		if(dir == Direction::LEFT)
			return -1;
		else if(dir == Direction::RIGHT)
			return 1;
		else
			return 0;	
	}(directionToMove);
	
	isStaying = false;
	if(isOnGround) {
		if(offset.x == 0)
			currentAnimation->setCurrentFrame(1.f);
		if(currentAnimation != runAnimation) {
			runAnimation = std::make_shared<AnimationController>(runAnimation->newObject());
			currentAnimation = runAnimation;
		}
		direction = directionToMove;
	}

	// if player is running and suddenly he changed the direction
	if(offset.x * -dx > 0)
		offset.x += config::PLAYER_RUNNING_DECELERATION * deltaTime * 60 * dx;
	else 
		offset.x += config::PLAYER_RUNNING_ACCELERATION * deltaTime * 60 * dx;

	const float maxSpeed = !isOnIce ? config::PLAYER_RUNNING_MAX_SPEED: config::PLAYER_RUNNING_MAX_SPEED_ON_ICE;

	if(std::abs(offset.x) > maxSpeed)
		offset.x = maxSpeed* dx;

	if(!isOnGround && ((direction == Direction::LEFT && offset.x > 0) || (direction == Direction::RIGHT && offset.x < 0)))
		offset.x = 0.f;
}

void PlayerGameObject::move(sf::Vector2f offset)
{
	sprite.move(offset);
}

void PlayerGameObject::jump(float deltaTime)
{
	if(!isAlowedToJump) return;

	isJumped = true;
	offset.y -= config::PLAYER_JUMPING_ACCELERATION * deltaTime * 60;
	if(abs(offset.y) > config::PLAYER_JUMPING_MAX_SPEED) {
		offset.y = -config::PLAYER_JUMPING_MAX_SPEED;
		isAlowedToJump = false;
	}
	if(currentAnimation != jumpAnimation) {
		jumpAnimation = std::make_shared<AnimationController>(jumpAnimation->newObject());
		currentAnimation = jumpAnimation;
	}
}

void PlayerGameObject::stay(float deltaTime)
{
	isStaying = true;
	if(!isOnGround) return;
	if(currentAnimation != runAnimation) {
		runAnimation = std::make_shared<AnimationController>(runAnimation->newObject());
		currentAnimation = runAnimation;
	}

	if(offset.x == 0.f || currentAnimation->getCurrentFrame() == 0.f || int(currentAnimation->getCurrentFrame()) >= currentAnimation->framesCount - 1 || isStacked) {
		currentAnimation->setCurrentFrame(0.f);
		return;
	}
	if(int(currentAnimation->getCurrentFrame()) < config::STOP_RUNNING_FRAME && int(currentAnimation->getCurrentFrame()) > 0)
		currentAnimation->setCurrentFrame(config::STOP_RUNNING_FRAME);
	currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.x) * currentAnimation->animationSpeed);
}

void PlayerGameObject::setOffset(sf::Vector2f newOffset)
{
	offset = newOffset;
}

void PlayerGameObject::updateMovement(float deltaTime) // override
{
	// x
	auto deceleration = config::PLAYER_RUNNING_DECELERATION;
	if(offset.y != 0)
		deceleration /= 4;
	else if(isOnIce)
		deceleration = config::PLAYER_RUNNIMG_DECELARATION_ON_ICE;

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

	// y
	offset.y += config::GRAVITY;
	if(offset.y > config::MAX_FALLING_SPEED)
		offset.y = config::MAX_FALLING_SPEED;
	else if(abs(offset.y) > config::MAX_FALLING_SPEED)
		offset.y = -config::MAX_FALLING_SPEED;

	// if the player is falling too low - than he should die
		// TO DO
 }

void PlayerGameObject::drawAnimation(sf::RenderWindow &window, float deltaTime)
{
	// if the player is on the ground and is running
	if(isOnGround && currentAnimation == runAnimation) {
		if(!isStaying) {
			// if there is a hindrance set animation speed to max
			// otherwise we would have a very slow animation
			if(isStacked)
				// currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * config::PLAYER_RUNNING_MAX_SPEED * currentAnimation->animationSpeed);
				currentAnimation->setCurrentFrame(0.f);

			// if the player is not staying and there is no any hindrance
			else 
				currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.x) * currentAnimation->animationSpeed);
				
			if(currentAnimation->getCurrentFrame() >= config::STOP_RUNNING_FRAME)
				currentAnimation->setCurrentFrame(config::START_RUNNING_FRAME);
		}
	}

	// if the player is falling, but did not jump
	else if(offset.y > 0.f && !isJumped) {
		currentAnimation = jumpAnimation;
		currentAnimation->setCurrentFrame(config::JUMPING_FRAME);
	}
	// if the player is jumping
	else if(currentAnimation == jumpAnimation) {
		// if the player is falling
		if(offset.y > 0) {
			currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.y) * currentAnimation->animationSpeed);
			if(int(currentAnimation->getCurrentFrame()) > currentAnimation->framesCount - 1)
				currentAnimation->setCurrentFrame(currentAnimation->framesCount - 1);
		}
		else {
			if(int(currentAnimation->getCurrentFrame()) < int(config::JUMPING_FRAME)) {
				currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * abs(offset.y) * currentAnimation->animationSpeed);
				if(int(currentAnimation->getCurrentFrame()) > config::JUMPING_FRAME)
					currentAnimation->setCurrentFrame(config::JUMPING_FRAME);
			}
		}
	}
	if(direction == Direction::LEFT)
		sprite.setTextureRect(sf::IntRect((64 + 32) * int(currentAnimation->getCurrentFrame()) + 64, (117 + 32) * currentAnimation->row, -64, 117));
	else
		sprite.setTextureRect(sf::IntRect((64 + 32) * int(currentAnimation->getCurrentFrame()), (117 + 32) * currentAnimation->row, 64, 117));

	sprite.setScale(scale);
	GameObject::draw(window);
}

// if the player on ground - he can jump
void PlayerGameObject::setStayingOnBlocks(std::list<BlockObject_ptr> stayingOnBlocks)
{
	this->stayingOnBlocks = stayingOnBlocks;
	isOnGround = stayingOnBlocks.size() > 0;
	isOnIce = false;
	if(isOnGround) {
		isAlowedToJump = true;
		isJumped = false;
		for(auto block: stayingOnBlocks) {
			if(block->blockType == BlockType::ICE) {
				isOnIce = true;
				break;
			}
		}
	}
}

void PlayerGameObject::die()
{

}
