#pragma once
#include "gameobject.h"

enum class Direction
{
	LEFT,
	RIGHT
};

class PlayerGameObject: public LiveGameObject
{
public:
	PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _accelaration, sf::Vector2f _deceleration, sf::Vector2f _maxAccelaration, float animationSpeed);
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	void jump(float deltaTime);
	void stay(float deltaTime);
	void setOffset(sf::Vector2f newOffset);
	void move(sf::Vector2f offset){sprite.move(offset);}
	void updateMovement(float deltaTime) override;
	void drawAnimation(sf::RenderWindow &window, float deltaTime);

	void setOnGround(bool isOnGround);
	bool isStaying = true;
	bool isStacked = false;

	const float ANIMATION_SPEED;

private:
	bool isAlowedToJump = true;
	bool isOnGround = false;
	float frameCounter = 0.f;
	Direction direction = Direction::RIGHT;
};
typedef std::shared_ptr<PlayerGameObject> PlayerObject_ptr;
