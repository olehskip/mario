#include "playergameobject.h"


PlayerGameObject::PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _accelaration, sf::Vector2f _deceleration, sf::Vector2f _maxAccelaration, float animationSpeed): 
	LiveGameObject(pos, scale, _texture, _accelaration, _deceleration, _maxAccelaration), ANIMATION_SPEED(animationSpeed)
{
	sprite.setTextureRect(sf::IntRect((64 + 32) * int(frameCounter) + 64, 0, -64, 117));
	sprite.setScale(1, 1);
}

void PlayerGameObject::moveRight(float deltaTime)
{
	if(offset.x == 0)
		frameCounter = 1.f;
	offset.x += accelaration.x * deltaTime * 60;
	if(offset.x > maxAccelaration.x)
		offset.x = maxAccelaration.x;

	isStaying = false;
	direction = Direction::RIGHT;
}
 
void PlayerGameObject::moveLeft(float deltaTime)
{
	if(offset.x == 0)
		frameCounter = 1.f;
	offset.x -= accelaration.x * deltaTime * 60;
	if(abs(offset.x) > maxAccelaration.x)
		offset.x = -maxAccelaration.x;

	isStaying = false;
	direction = Direction::LEFT;
}

void PlayerGameObject::jump(float deltaTime)
{
	if(!isAlowedToJump) return;
	offset.y -= accelaration.y * deltaTime * 60;
	if(abs(offset.y) > maxAccelaration.y) {
		offset.y = -maxAccelaration.y;
		isAlowedToJump = false;
	}
}

void PlayerGameObject::stay(float deltaTime)
{
	isStaying = true;

	if(offset.x == 0 || frameCounter == 0.f || int(frameCounter) >= 24) {
		frameCounter = 0.f;
		return;
	}
	if(int(frameCounter) < 19 && int(frameCounter) > 0)
		frameCounter = 19.f;

	frameCounter += deltaTime * abs(offset.x) * ANIMATION_SPEED;;
}

void PlayerGameObject::setOffset(sf::Vector2f newOffset)
{
	offset = newOffset;
}

void PlayerGameObject::move()
{
	sprite.move(offset);
}

void PlayerGameObject::updateMovement(float deltaTime) // override
{
	if(direction == Direction::LEFT)
		sprite.setTextureRect(sf::IntRect((64 + 32) * int(frameCounter) + 64, 0, -64, 117));
	else
		sprite.setTextureRect(sf::IntRect((64 + 32) * int(frameCounter), 0, 64, 117));
	
	sprite.setScale(1, 1);
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

}

void PlayerGameObject::drawAnimation(sf::RenderWindow &window, float deltaTime)
{
	if(!isStaying) {
		// if there is a hindrance set animation speed to max
		// otherwise we would have a very slow animation
		if(isStacked)
			frameCounter += deltaTime * maxAccelaration.x * ANIMATION_SPEED;

		// if the player is not staying and there is no any hindrance
		else 
			frameCounter += deltaTime * abs(offset.x) * ANIMATION_SPEED;
			
		if(frameCounter >= 20.f)
			frameCounter = 4;
	}
	GameObject::draw(window);
}

// if the player on ground - he can jump
void PlayerGameObject::setStayingOnBlocks(std::list<BlockObject_ptr> stayingOnBlocks)
{
	this->stayingOnBlocks = stayingOnBlocks;
	isOnGround = stayingOnBlocks.size() > 0;
	if(isOnGround)
		isAlowedToJump = true;
}

void PlayerGameObject::die()
{

}
