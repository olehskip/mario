#include "playergameobject.h"


PlayerGameObject::PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _accelaration, sf::Vector2f _deceleration, sf::Vector2f _maxAccelaration): 
	LiveGameObject(pos, scale, _texture, _accelaration, _deceleration, _maxAccelaration)
{
	runAnimation = std::make_shared<AnimationController>(0, 26);
	jumpAnimation = std::make_shared<AnimationController>(1, 7);
	currentAnimation = runAnimation;

	sprite.setTextureRect(sf::IntRect((64 + 32) * int(currentAnimation->currentFrame) + 64, 0, -64, 117));
	sprite.setScale(scale);
}

void PlayerGameObject::moveRight(float deltaTime)
{
	if(isOnGround) {
		if(offset.x == 0)
			currentAnimation->currentFrame = 1.f;
		if(currentAnimation != runAnimation) {
			runAnimation = std::make_shared<AnimationController>(runAnimation->newObject());
			currentAnimation = runAnimation;
		}
	}
	offset.x += accelaration.x * deltaTime * 60;
	if(offset.x > maxAccelaration.x)
		offset.x = maxAccelaration.x;

	isStaying = false;
	direction = Direction::RIGHT;
}
 
void PlayerGameObject::moveLeft(float deltaTime)
{
	if(isOnGround) {
		if(offset.x == 0)
			currentAnimation->currentFrame = 1.f;
		if(currentAnimation != runAnimation) {
			runAnimation = std::make_shared<AnimationController>(runAnimation->newObject());
			currentAnimation = runAnimation;
		}
	}
	offset.x -= accelaration.x * deltaTime * 60;
	if(abs(offset.x) > maxAccelaration.x)
		offset.x = -maxAccelaration.x;

	isStaying = false;
	direction = Direction::LEFT;

	if(offset.x < 0)
		offsetFromCenter += offset.x;
}

void PlayerGameObject::jump(float deltaTime)
{
	if(!isAlowedToJump) return;
	isJumped = true;
	offset.y -= accelaration.y * deltaTime * 60;
	if(abs(offset.y) > maxAccelaration.y) {
		offset.y = -maxAccelaration.y;
		isAlowedToJump = false;
	}
	if(currentAnimation != jumpAnimation) {
		jumpAnimation = std::make_shared<AnimationController>(jumpAnimation->newObject());
		currentAnimation = jumpAnimation;
	}
}

void PlayerGameObject::stay(float deltaTime)
{
	if(!isOnGround) return;
	if(currentAnimation == jumpAnimation) {
		runAnimation = std::make_shared<AnimationController>(runAnimation->newObject());
		currentAnimation = runAnimation;
	}
	isStaying = true;

	if(offset.x == 0.f || currentAnimation->currentFrame == 0.f || int(currentAnimation->currentFrame) >= currentAnimation->framesCount - 1 || isStacked) {
		currentAnimation->currentFrame = 0.f;
		return;
	}
	if(int(currentAnimation->currentFrame) < config::STOP_RUNNING_FRAME && int(currentAnimation->currentFrame) > 0)
		currentAnimation->currentFrame = config::STOP_RUNNING_FRAME;

	currentAnimation->currentFrame += deltaTime * abs(offset.x) * config::RUN_ANIMATION_SPEED;
}

void PlayerGameObject::setOffset(sf::Vector2f newOffset)
{
	offset = newOffset;
}

void PlayerGameObject::move(sf::Vector2f offset)
{
	sprite.move(offset);
}

void PlayerGameObject::updateMovement(float deltaTime) // override
{
	if(direction == Direction::LEFT)
		sprite.setTextureRect(sf::IntRect((64 + 32) * int(currentAnimation->currentFrame) + 64, (117 + 32) * currentAnimation->row, -64, 117));
	else
		sprite.setTextureRect(sf::IntRect((64 + 32) * int(currentAnimation->currentFrame), (117 + 32) * currentAnimation->row, 64, 117));
	
	sprite.setScale(scale);
	auto deceleration = this->deceleration;
	if(!isOnGround)
		deceleration.x /= 2; 
	// x
	if(offset.x > 0) {
		offset.x -= deceleration.x;
		if(offset.x < 0)
			offset.x = 0;
	}
	else if(offset.x < 0) {
		offset.x += deceleration.x;
		if(offset.x > 0)
			offset.x = 0;
	}

	// y
	offset.y += deceleration.y;
	if(offset.y > maxAccelaration.y)
		offset.y = maxAccelaration.y;
	else if(abs(offset.y) > maxAccelaration.y)
		offset.y = -maxAccelaration.y;

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
				currentAnimation->currentFrame += deltaTime * maxAccelaration.x * config::RUN_ANIMATION_SPEED;

			// if the player is not staying and there is no any hindrance
			else 
				currentAnimation->currentFrame += deltaTime * abs(offset.x) * config::RUN_ANIMATION_SPEED;
				
			if(currentAnimation->currentFrame >= config::STOP_RUNNING_FRAME)
				currentAnimation->currentFrame = config::START_RUNNING_FRAME;
		}
	}

	// if the player is falling, but did not jump
	if(offset.y > 0.f && !isJumped) {
		currentAnimation = jumpAnimation;
		currentAnimation->currentFrame = config::JUMPING_FRAME;
	}
	// if the player is jumping
	else if(currentAnimation == jumpAnimation) {
		// if the player is falling
		if(offset.y > 0) {
			if(int(currentAnimation->currentFrame) < int(config::START_FALLING_FRAME))
				currentAnimation->currentFrame = config::START_FALLING_FRAME;
			else {
				currentAnimation->currentFrame += deltaTime * abs(offset.y) * config::JUMP_ANIMATION_SPEED;
				if(int(currentAnimation->currentFrame) > currentAnimation->framesCount - 1)
					currentAnimation->currentFrame = currentAnimation->framesCount - 1;
			}
		}
		else {
			if(int(currentAnimation->currentFrame) < int(config::JUMPING_FRAME)) {
				currentAnimation->currentFrame += deltaTime * abs(offset.y) * config::JUMP_ANIMATION_SPEED;
				if(int(currentAnimation->currentFrame) > config::JUMPING_FRAME)
					currentAnimation->currentFrame = config::JUMPING_FRAME;
			}
		}
	}

	// std::cout << currentAnimation->currentFrame << std::endl;
	GameObject::draw(window);
	
}

// if the player on ground - he can jump
void PlayerGameObject::setStayingOnBlocks(std::list<BlockObject_ptr> stayingOnBlocks)
{
	this->stayingOnBlocks = stayingOnBlocks;
	isOnGround = stayingOnBlocks.size() > 0;
	if(isOnGround) {
		isAlowedToJump = true;
		isJumped = false;
	}
}

void PlayerGameObject::die()
{

}
