#pragma once
#include "blockgameobject.h"
#include <list>

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
	void move();
	void updateMovement(float deltaTime) override;
	void drawAnimation(sf::RenderWindow &window, float deltaTime);

	void setStayingOnBlocks(std::list<BlockObject_ptr> stayingOnBlocks);
	bool isStacked = false; // stacked means stacked of the left side of screen (when the player is running back)
	bool getIsStaying() const;

	const float ANIMATION_SPEED;

private:
	std::list<BlockObject_ptr> stayingOnBlocks;
	bool isStaying = true;
	bool isAlowedToJump = true;
	bool isOnGround = false;
	float frameCounter = 0.f;
	unsigned int animationRow = 0;
	Direction direction = Direction::RIGHT;

	void die();
	bool isAlive;
};
typedef std::shared_ptr<PlayerGameObject> PlayerObject_ptr;
